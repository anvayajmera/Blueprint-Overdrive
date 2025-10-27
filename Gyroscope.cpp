#include <opencv2/opencv.hpp>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <chrono> 


using namespace std;
using namespace cv;
#include <sstream>
#include "Gyroscope.h"
#include "serial_comm.h"
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }

    return tokens;
}
bool getGyroDataFromMPU6050(int& gx, int& gy, int& gz) {
    static int gyro_serial = -1;
    static bool initialized = false;

    if (!initialized) {
        const char* port = "/dev/ttyUSB0";  
        gyro_serial = open(port, O_RDWR | O_NOCTTY);
        if (gyro_serial < 0) {
            std::cerr << "Error: could not open gyro serial port\n";
            return false;
        }

        termios tty{};
        tcgetattr(gyro_serial, &tty);
        cfsetospeed(&tty, B9600);
        cfsetispeed(&tty, B9600);
        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
        tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_iflag = tty.c_oflag = tty.c_lflag = 0;
        tty.c_cc[VMIN] = 1;
        tty.c_cc[VTIME] = 0;
        tcsetattr(gyro_serial, TCSANOW, &tty);

        initialized = true;
    }

    std::string line;
    char ch;
    while (read(gyro_serial, &ch, 1) == 1) {
        if (ch == '\n') break;
        line += ch;
    }
    if (!line.empty() && line.back() == '\r')
        line.pop_back();

    std::vector<std::string> tokens = split(line, ',');

    if (tokens.size() >= 3) {
        try {
            gx = std::stoi(tokens[0]);
            gy = std::stoi(tokens[1]);
            gz = std::stoi(tokens[2]);
            return true;
        } catch (...) {
            std::cerr << "[warning] Invalid gyro data (parse error): " << line << "\n";
        }
    } else {
        std::cerr << "[warning] Incomplete gyro data: " << line << "\n";
    }

    return false;
}



void detectRampSlope() {
    const float xSensitivity = 131.0;     
    const int xBias = -100;               // Gyro X-axis bias
    const float rampUpMin = 20.0;         
    const float rampDownMin = -20.0;     
    const float rampThreshold = 5.0;      

    float xAngle = 0.0;
    auto lastTime = std::chrono::high_resolution_clock::now();
    cv::namedWindow("Ramp Debug", cv::WINDOW_AUTOSIZE);

    while (true) {
        int gx, gy, gz;

        if (getGyroDataFromMPU6050(gx, gy, gz)) {
            gx -= xBias;

            auto now = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float>(now - lastTime).count();
            lastTime = now;

            float xRate = gx / xSensitivity;
            xAngle += xRate * dt;

            std::cout << "Pitch Angle: " << xAngle << " degrees\n";

            // Debug visualization
            cv::Mat img(200, 400, CV_8UC3, cv::Scalar(30, 30, 30));
            int barLen = static_cast<int>((std::abs(xAngle) / 25.0) * 300);
            barLen = std::min(std::max(barLen, 0), 300);

            cv::rectangle(img, cv::Point(50, 100), cv::Point(50 + barLen, 150), cv::Scalar(255, 0, 0), cv::FILLED);
            cv::putText(img, "Pitch: " + std::to_string(xAngle), cv::Point(50, 80),
                        cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);

            cv::imshow("Ramp Debug", img);
            cv::waitKey(1);

           
            if (xAngle >= rampUpMin && xAngle <= (rampUpMin + rampThreshold)) {
                std::cout << "Ramp climb detected!\n";
                sendInteger(100000);
                break;
            }
            
            if (xAngle <= rampDownMin && xAngle >= (rampDownMin - rampThreshold)) {
                std::cout << "Ramp descent detected!\n";
                sendInteger(1000001);
                break;
            }
        }

        usleep(2000);  
    }

    cv::destroyWindow("Ramp Debug");
}

void gyroTurnDegrees(int targetAngle, bool clockwise) {
    float sensitivity = 131.0;  
    int biasY = -50;            // Gyro Y-axis bias
    int turnPower = 10000;      

    float yAngle = 0.0;
    auto lastTime = std::chrono::high_resolution_clock::now();

    int command = (clockwise ? turnPower : -turnPower);
    sendInteger(command);  

    std::cout << "Turning " << (clockwise ? "clockwise" : "counter-clockwise")
              << " for ~" << targetAngle << " degrees...\n";

    cv::namedWindow("Gyro Debug", cv::WINDOW_AUTOSIZE);

    while (true) {
        int gx, gy, gz;
        if (getGyroDataFromMPU6050(gx, gy, gz)) {
            gz -= biasY;

            auto now = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float>(now - lastTime).count();
            lastTime = now;

            float yRate = gz / sensitivity;  
            yAngle += yRate * dt;

            std::cout << "Y Angle: " << yAngle << " deg" << std::endl;

            cv::Mat debugImage(200, 400, CV_8UC3, cv::Scalar(30, 30, 30));
            int barLength = static_cast<int>((std::abs(yAngle) / std::abs(targetAngle)) * 300);
            barLength = std::min(std::max(barLength, 0), 300);

            cv::rectangle(debugImage, cv::Point(50, 100), cv::Point(50 + barLength, 150), cv::Scalar(0, 255, 0), cv::FILLED);
            cv::putText(debugImage, "Y Angle: " + std::to_string(yAngle), cv::Point(50, 80),
                        cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
            cv::putText(debugImage, "Target: " + std::to_string(targetAngle), cv::Point(50, 180),
                        cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);

            cv::imshow("Gyro Debug", debugImage);
            cv::waitKey(1);
            // ----------------------------

            if (std::abs(yAngle) >= std::abs(targetAngle) - 5){
                std::cout << "Turn completed at ~" << yAngle << " degrees\n";
                break;
            }
        }

        usleep(2000);  
    }
    sendInteger(0);
    cv::destroyWindow("Gyro Debug");
}


void gyroTurnLeft90()  { gyroTurnDegrees(70, false); }
void gyroTurnRight90() { gyroTurnDegrees(70, true); }
void gyroTurn180()     { gyroTurnDegrees(160, true); }
