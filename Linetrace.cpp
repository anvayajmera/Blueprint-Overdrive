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


#include "Linetrace.h"
#include "serial_comm.h"
int getBlackLineOffset(cv::Mat& frame, double minContourArea) {
    cv::Mat blurred;
    GaussianBlur(frame, blurred, cv::Size(5, 5), 0);

    std::vector<cv::Mat> channels;
    split(blurred, channels);

    int threshB = 50, threshG = 50, threshR = 50;

    cv::Mat maskB = channels[0] < threshB;
    cv::Mat maskG = channels[1] < threshG;
    cv::Mat maskR = channels[2] < threshR;

    cv::Mat binary = maskB & maskG & maskR;

    std::vector<std::vector<cv::Point>> contours;
    findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::cvtColor(binary, binary, cv::COLOR_GRAY2BGR); 

    if (contours.empty()) {
        return 0;
    }

    int largestIdx = -1;
    double maxArea = 1000;
    for (int i = 0; i < contours.size(); ++i) {
        double area = contourArea(contours[i]);
        if (area > minContourArea && area > maxArea) {
            maxArea = area;
            largestIdx = i;
        }
    }

    if (largestIdx == -1) {
        return 0;
    }


    cv::Moments m = moments(contours[largestIdx]);
    if (m.m00 == 0) {
        return 0;
    }

    int cx = static_cast<int>(m.m10 / m.m00);
    int centerX = frame.cols / 2;
    int offset = cx - centerX;

  
    return offset;
}


int detectIntersection(const cv::Mat& inputImage) {
    using namespace cv;

    const int width = 640;
    const int height = 360;
    const int smallW = width / 8;
    const int smallH = height / 8;
Mat resizedInput=inputImage;
    Mat channels[3];
    split(resizedInput, channels);
    Mat blackMask = (channels[0] < 50) & (channels[1] < 50) & (channels[2] < 50);
    
    Mat morph=blackMask;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(blackMask, morph, MORPH_CLOSE, kernel, Point(-1, -1), 2);
    // Find contours
    std::vector<std::vector<Point>> contours;
    findContours(morph, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    if (contours.empty()) return 0;

    int largestIdx = -1;
    double maxArea = 0;
    for (int i = 0; i < contours.size(); ++i) {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            largestIdx = i;
        }
    }
    if (largestIdx == -1) return 0;

    // Create binary mask of the largest contour
    Mat contourMask = Mat::zeros(height, width, CV_8UC1);
    drawContours(contourMask, contours, largestIdx, Scalar(255), FILLED);

    // Region masks
    Mat leftMask = Mat::zeros(height, width, CV_8UC1);
    Mat rightMask = Mat::zeros(height, width, CV_8UC1);
    Mat bottomMask = Mat::zeros(height, width, CV_8UC1);
    Mat topMask = Mat::zeros(height, width, CV_8UC1);
    Mat centerMask = Mat::zeros(height, width, CV_8UC1);
// Side rectangles for intersection detection
Rect topRect((width - smallW * 2) / 2, 0, smallW * 2, smallH);
Rect bottomRect((width - smallW * 2) / 2, height - smallH, smallW * 2, smallH);
Rect leftRect(0, (height - smallW * 2) / 2, smallH, smallW * 2);
Rect rightRect(width - smallH, (height - smallW * 2) / 2, smallH, smallW * 2);


    // Center square
    int centerSize = static_cast<int>(sqrt(2 * smallW * smallH));
    Rect centerRect((width - centerSize) / 2, (height - centerSize) / 2, centerSize, centerSize);

    // Draw rectangles
    rectangle(topMask, topRect, Scalar(255), FILLED);
    rectangle(bottomMask, bottomRect, Scalar(255), FILLED);
    rectangle(leftMask, leftRect, Scalar(255), FILLED);
    rectangle(rightMask, rightRect, Scalar(255), FILLED);
    rectangle(centerMask, centerRect, Scalar(255), FILLED);

    // Overlap checking
    int leftOverlap = countNonZero(contourMask & leftMask);
    int rightOverlap = countNonZero(contourMask & rightMask);
    int bottomOverlap = countNonZero(contourMask & bottomMask);
    int topOverlap = countNonZero(contourMask & topMask);
    int centerOverlap = countNonZero(contourMask & centerMask);
// Thresholds for boxes
const int intersectionThresh = 1500;
const int turnThresh = 3000;  
const int centerThresh = 2000;

bool intersectsLeft = leftOverlap > intersectionThresh;
bool intersectsRight = rightOverlap > intersectionThresh;
bool intersectsTop = topOverlap > intersectionThresh;
bool intersectsBottom = bottomOverlap > intersectionThresh;
bool intersectsCenter = centerOverlap > centerThresh;

bool leftTurnDetected = (leftOverlap > turnThresh) && (bottomOverlap > turnThresh) && (centerOverlap > turnThresh) &&
                        (rightOverlap < intersectionThresh) && (topOverlap < intersectionThresh);

bool rightTurnDetected = (rightOverlap > turnThresh) && (bottomOverlap > turnThresh) && (centerOverlap > turnThresh) &&
                         (leftOverlap < intersectionThresh) && (topOverlap < intersectionThresh);

    // Count how many side regions are intersected
    int sideIntersectionCount = intersectsLeft + intersectsRight + intersectsTop + intersectsBottom;

    Mat debugDisplay;
    cvtColor(contourMask, debugDisplay, COLOR_GRAY2BGR);
    rectangle(debugDisplay, topRect, Scalar(255, 255, 0), 2);
    rectangle(debugDisplay, bottomRect, Scalar(0, 255, 255), 2);
    rectangle(debugDisplay, leftRect, Scalar(0, 255, 0), 2);
    rectangle(debugDisplay, rightRect, Scalar(0, 0, 255), 2);
    rectangle(debugDisplay, centerRect, Scalar(255, 0, 255), 2);  
    imshow("Intersection Detection", debugDisplay);
    waitKey(1);

if ((sideIntersectionCount >= 3) && intersectsCenter) {
    return 1; // Normal intersection
}
  if (leftTurnDetected) {
    return 2; // 90-degree left turn
}
if (rightTurnDetected) {
    return 3; // 90-degree right turn
}


    return 0; //No real green squares keep moving forward
}



int greenSquareDetection(const cv::Mat& inputImage) {
    using namespace cv;

    // Resize input image
    Mat image=inputImage;

    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    Scalar lowerGreen(0, 110, 0);
    Scalar upperGreen(255, 255, 170);
    Mat greenMask;
    inRange(hsv, lowerGreen, upperGreen, greenMask);

    // Create black line mask
    Mat gray, blackMask;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    threshold(gray, blackMask, 70, 255, THRESH_BINARY_INV);

    // Find contours in green mask
    std::vector<std::vector<Point>> contours;
    findContours(greenMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    const double minArea = 900.0;
    const int radius = 5;

    bool foundLeft = false;
    bool foundRight = false;
    std::string navDirection = "Forward";

    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > minArea) {
            Rect rect = boundingRect(contour);
            Point center(rect.x + rect.width / 2, rect.y + rect.height / 2);

            int xOffset = 30;
            int yOffset = 30;

            Point top(center.x, rect.y - yOffset);
            Point bottom(center.x, rect.y + rect.height + yOffset);
            Point left(rect.x - xOffset, center.y);
            Point right(rect.x + rect.width + xOffset, center.y);

            auto inBounds = [&](const Point& pt) {
                return pt.x >= 0 && pt.x < blackMask.cols && pt.y >= 0 && pt.y < blackMask.rows;
            };

            bool topOnBlack = inBounds(top) && blackMask.at<uchar>(top) == 255;
            bool bottomOnBlack = inBounds(bottom) && blackMask.at<uchar>(bottom) == 255;
            bool rightOnBlack = inBounds(right) && blackMask.at<uchar>(right) == 255;
            bool leftOnBlack = inBounds(left) && blackMask.at<uchar>(left) == 255;

            std::string resultText = "Fake";

            if (topOnBlack && !bottomOnBlack) {
                if (rightOnBlack) {
                    resultText = "Left";
                    foundLeft = true;
                } else if (leftOnBlack) {
                    resultText = "Right";
                    foundRight = true;
                } else {
                    resultText = "Legit";
                }
            }

            rectangle(image, rect, Scalar(0, 0, 255), 2);
            circle(image, center, radius, Scalar(0, 0, 255), -1);       // Center: Red
            circle(image, top, radius, Scalar(255, 0, 0), -1);          // Top: Blue
            circle(image, right, radius, Scalar(0, 255, 0), -1);        // Right: Green
            circle(image, bottom, radius, Scalar(0, 255, 255), -1);     // Bottom: Yellow
            circle(image, left, radius, Scalar(255, 0, 255), -1);       // Left: Purple

            putText(image, resultText, Point(center.x - 30, center.y - 10),
                    FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 2);
        }
    }

    // Final navigation decision
    if (foundLeft && foundRight) {
        navDirection = "U-Turn";
    } else if (foundLeft) {
        navDirection = "Turn Left";
    } else if (foundRight) {
        navDirection = "Turn Right";
    }

    putText(image, "Decision: " + navDirection,
            Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 255, 255), 3);

    imshow("Green Square Debug", image);
    waitKey(1);

    if (foundLeft && foundRight)
        return 3;
    else if (foundLeft)
        return 2;
    else if (foundRight)
        return 1;

    return 0;
putText(image, "Decision: " + navDirection,
        Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 255, 255), 3);

imshow("Green Square Debug", image);
imshow("Green Mask", greenMask);  
waitKey(1);

}
