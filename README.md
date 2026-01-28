# Blueprint-Overdrive

**Description:**
Hey! Our team of 3 (with me submitting) will spend this school year working on a robot for RoboCup Junior's Rescue Line challenge. Our competition will take place in April, and our goal is to secure first place, allowing us to compete internationally at the RCJ 2026 event in South Korea. 
Here's a rough timeline for us so far:
**August:** Planning Stage
**September–October:** 3D Modeling
**October–December:** Building
**January–April:** Coding and Testing


**Why:**
We're interested in being involved with robotics without needing an FRC-level commitment, but without control over what gets done. RoboCup Junior is the perfect solution to this, as we can stay a team of 3, contribute to all parts of development, and focus our software on AI-powered models for line following and victim detection. We want to participate in Blueprint to secure funding for some of the components that go into making this robot, including motors, a Jetson Nano, batteries, and other external supplies.

**How:**
Our robot is specifically designed to be able to traverse the full RoboCup Junior Rescue Line map. To use the motors and various sensors on our robot, you have to turn on the main switch that gives power to the motors and Jetson Orin Nano. We extended the HDMI and USB hubs using extender cables to access them when the robot is fully built. From here, since we're using a Seeed Studio for PWM, the servos and motors can technically be accessed through VS Code on the Jetson interface. As for all of the sensors connected directly to its 40-pin header, those need to be accessed using terminal commands. We're working out a better solution soon to make this easier (all of us are still learning). 





Pictures of 3D Model:


<img width="535" height="368" alt="Screenshot 2025-10-27 at 3 07 02 PM" src="https://github.com/user-attachments/assets/ca8dc2f1-a8a2-4d18-9ffc-c030ba8af144" />
<img width="504" height="368" alt="Screenshot 2025-10-27 at 3 07 27 PM" src="https://github.com/user-attachments/assets/7fdedc08-5a18-4657-9bc5-da9c1ceba4ac" />
<img width="504" height="368" alt="Screenshot 2025-10-27 at 3 07 40 PM" src="https://github.com/user-attachments/assets/860bc3d2-b84f-4d2d-96dc-f955df1290b1" />



Wiring Diagram:
<img width="1371" height="630" alt="Screenshot 2026-01-27 at 7 05 13 PM" src="https://github.com/user-attachments/assets/5d4e65d1-0fde-4e04-aa95-dab584fe946b" />



Bill of Materials in Table Format:
bom.csv reference: [Overdrive Bill of Materials (CSV)](https://github.com/user-attachments/files/24839998/Overdrive.Bill.of.Materials.-.BillOfMaterials.3.csv)
## Overdrive Bill of Materials (Updated)

| Category | Part Name | Bought? | Part Link | Units | Unit Cost | Cost |
|:--|:--|:--|:--|--:|--:|--:|
| Batteries & Power | HOOVO 3S LiPo Battery 4200mAh 120C 11.4V | Bought Already | [Link](https://www.amazon.com/dp/B0CC91GJFN?ref=ppx_yo2ov_dt_b_fed_asin_title) | 6 | $38.00 | $228.00 |
| Batteries & Power | DROK Boost Converter 9–36V to 12V 5A 60W | Bought Already | [Link](https://www.amazon.com/dp/B0D7H7RMK1?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_1) | 2 | $19.00 | $38.00 |
| Batteries & Power | DC-DC Buck Converter 4–38V to 1.25–36V 5A | Bought Already | [Link](https://www.amazon.com/Diitao-Adjustable-Step-Down-Regulator-Converter/dp/B0BBFD6NVZ/ref=sr_1_53?crid=3F3QFWL0B9CLP&dib=eyJ2IjoiMSJ9.4rch2lvAeyc6Z6CXNl42RQ406iOT32CbFb8pEYXf6VjGjHj071QN20LucGBJIEps.8x9RuAQdt79zsJ9qvJGY8PB6tgYQrIsHZsvFW2z4DUA&dib_tag=se&keywords=step+up+converter+5a+with+cooling&qid=1754080628&sprefix=step+up+converter+5a+with+cooling%2Caps%2C172&sr=8-53&xpid=k5RNzKOset16H) | 1 | $8.49 | $8.49 |
| Batteries & Power | USB Mini LED Light Strip | Bought Already | [Link](https://www.amazon.com/PAUTIX-Dimmable-Backlight-Flexible-Lighting/dp/B08X1QMRKK/ref=sr_1_17?dib=eyJ2IjoiMSJ9.SR0S1YPfpsAxPOvVuk26ojwVTbgujTVyGXMGUOhocjDaLHeN60xe0x-VJPz_41h_Wk3FMT4ZzKeq1a9d8QAqtXkkukmrOoCoVV7eQtuBm7Fb5-LHW32E_a3uV7DHBFS3eutP719CmWBYQ_UeFtvvnxH96IxyrE_R6iBZNpUhHvS8B4kKNVu6RUw40l8b6N9veM5mAS_COTmVZHAKxSdsYjzSfw1_-Cw3SrDaN50W-tlxkOQnp3_IR9s5tpb-_xw3QoFCZpgp1-x2ix-6Y4MKwyGtdVDyCaZ6JnoreRbMxUc.dPxkSnfub1dljlcoQeg36_2r6Ct1gMaPnUgxY-ISHAY&dib_tag=se&keywords=light+strip+strong&qid=1761594740&sr=8-17) | 1 | $10.00 | $10.00 |
| Batteries & Power | Screw Terminal | Bought Already | [Link](https://www.amazon.com/dp/B093PWRJS9?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_6) | 1 | $14.00 | $14.00 |
| Batteries & Power | Voltage detectors | Bought Already | [Link](https://www.amazon.com/Aoicrie-Battery-Checker-Detector-Indicator/dp/B07VR4SV8C?ie=UTF8&th=1) | 2 | $3.00 | $6.00 |
| Motors & Actuators | Greartisan 12V 20RPM DC Gear Motor | Bought Already | [Link](https://www.amazon.com/dp/B071KFT4PC?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_1&th=1) | 4 | $15.00 | $60.00 |
| Motors & Actuators | Adafruit DRV8871 DC Motor Driver Breakout Board (3.6A max) | Need to Buy | [Link](https://www.adafruit.com/product/3190) | 4 | $7.50 | $30.00 |
| Motors & Actuators | MG90s microservo | Bought Already | [Link](https://www.amazon.com/MG90S-Servo-Motor-Helicopter-Arduino/dp/B01JY3H4MA/ref=sr_1_1_sspa?crid=2Y68CMGWUMZK8&dib=eyJ2IjoiMSJ9.Ob8kzKrp-maqOMgCtxQJwM9MSR90LW6-Hmrg7EFqs6I.eXq8BULKm09DFfVs5NwK4n9n9ParIjJypa-bcVCDwDY&dib_tag=se&keywords=6+pack+microservo&qid=1761597978&sprefix=6+pack+microservo%2Caps%2C90&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1) | 8 | $2.50 | $20.00 |
| Motors & Actuators | 25KG High Torque RC Servo | Bought Already | [Link](https://www.amazon.com/Miuzei-Waterproof-Compatible-Steering-Horn%EF%BC%88270%C2%B0%EF%BC%89/dp/B0C5LWHTQ1/ref=sr_1_2?crid=2L50FJTWW8LGM&dib=eyJ2IjoiMSJ9.4gQlLnVL64R4rCvHH7G2zc7y-D2geU2xHJOrlskCWdDpbwS77mImyNg0SeViuFwnLOG8RmvelCQaz9IbNPlCUJ_hqE3fATvTFSrVKC5A093tb3xXBPpCml8OdEanRNLdFlPlPPtbQV_lKJyFVi5yXPwubgfqGJLZ8PVcL-249pn3L1rML3ynZ05-4NW8iG9kXt6MdlA2ErOw2dE9qDLpavC-KQM9gq9TZEiE7X_m--puFrE4R-zjkcOSKVesQ_o7TKQ3AT2AjQGVaCHh29rzkkJNYEaPwGnc3ERg-nRFHns.1m4ZFQZXkst3ZExsZb4_29TN86lY2U3KI4DFnVIYIPc&dib_tag=se&keywords=eso8ma%2Bservo%2Breadytoski&qid=1761597918&sprefix=eso8ma%2Bservo%2Breadytoski%2Caps%2C65&sr=8-2&th=1) | 1 | $16.99 | $16.99 |
| Control Boards | NVIDIA Jetson Orin Nano 8GB | Bought Already | [Link](https://www.amazon.com/NVIDIA-Jetson-Orin-Nano-Developer/dp/B0BZJTQ5YP?th=1) | 1 | $250.00 | $250.00 |
| Control Boards | Seeed Studio XIAO RP2040 (v1.0) | Need to Buy | [Link](https://www.seeedstudio.com/XIAO-RP2040-v1-0-p-5026.html) | 1 | $3.99 | $3.99 |
| Sensors/devices | MPU-6050 Gyroscope Accelerometer Module | Bought Already | [Link](http://amazon.com/HiLetgo-MPU-6050-Accelerometer-Gyroscope-Converter/dp/B01DK83ZYQ/ref=sr_1_4?dib=eyJ2IjoiMSJ9.17CgYbfJeLaKBTknvMMfsxPPQVLmfP4RI9hGN7HD_fi7J3VQzgjUTgghFuXdxplvcYuGCb5gIyO9P0pFnVyHerk_ai7k2wtlEQvJQZXwq2BzOvPEggPqI2GQH5D3vmhOIqlfCsr2zLtsWWft4OeGK_CeRsSOu7WEgZesnHNaPSJ0jr45TiTXt85AB34Q_HpHQ-RFMgwNK0JojOB9S3bThL0nxdZpiIWbsUyHY8jGg18._uSEmocByBL4_tIE-b3kG6gLKeNOjPZJv7WnabBOBU0&dib_tag=se&keywords=mpu6050&qid=1761614660&sr=8-4) | 1 | $6.99 | $6.99 |
| Sensors/devices | VL6180X Time-of-Flight Sensor | Bought Already | [Link](https://www.amazon.com/VL6180X-TOF050C-Ranging-Modules-Distance/dp/B0F4XBZ998?crid=XYQSMHTSPIRM&dib=eyJ2IjoiMSJ9.zLn9XQg8ko5KSx59x5Bpmjdc-QKpAOcKn9-w8dP1UT9jB7y47emsy_IuZVqkM-klCmC-Aj_RMPR_rA3czrHRkaeVH5pGuhFaXUgPxzCUGDwO3tuE0K4geNjtpXn4IajOYfCjv1CyCfOzWu__nZsZo_-BQv2uR5gNHHL4Gf3pRFFGn5w0sss63YnNVUANThCvx5CFKie75nlxhorzCFhQnOy5OTRXqYbAUdPJc9Rm_9zNe9uN0W5wXFEKrDUX9QQRZ_b3qFePx7FFUGVXm3DInv9E2a77gXCR0B2DxwBntqk.4pMiuUYK6p8Y1aWNEjc8B910JqMq5hVy8-T4e3OqqPQ&dib_tag=se&keywords=VL6180X&qid=1754161326&sprefix=vl53l0x%2Caps%2C395&sr=8-6) | 2 | $4.50 | $9.00 |
| Sensors/devices | VL53L4CD Time-of-Flight Sensor | Bought Already | [Link](https://www.adafruit.com/product/5396) | 5 | $15.00 | $75.00 |
| Sensors/devices | 5V Relay Module (Single Channel) | Bought Already | [Link](https://www.amazon.com/dp/B00LW15A4W?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_7&th=1) | 1 | $4.00 | $4.00 |
| Sensors/devices | OLED Display Screen | Bought Already | [Link](https://www.amazon.com/Dorhea-Display-3-3V-5V-Arduino-Raspberry/dp/B07FK8GB8T/ref=sr_1_3?crid=2XOZQLQCWR19&dib=eyJ2IjoiMSJ9.gmjYYgZs428_vTrOMwdxYSK-ALIioWA287Dy29JHnzCqsYO3Jn2qcbK_xrkjgMJHNt9gM4nXidDz2qyuvImYKFcujmmYJ69WmRl1FVGiA22xkHAJoD6cklwX-RKAoAVIxx5fkoL4xCT2vXq3MKSJVqPriC8fK3Cwimtb_w2G0uT191Tu6Aoc9qIZ34N8QfJaAzyBidc-lNxQgp3fo1iJinc7AO1BE4y5l5XSUq1jjrtokgzyBJp3N_yBBoy56BP6YPkzFea6R0M9aFZ72E9CVqXlj7OWfmV5CwQ4ObUBkPU._ynAxlAylfKVpWsS6qInIAPab1VJagOGECU0_OJ53bY&dib_tag=se&keywords=OLED+display+screen&qid=1761595105&s=industrial&sprefix=oled+display+scree%2Cindustrial%2C136&sr=1-3) | 1 | $6.00 | $6.00 |
| Sensors/devices | USB Camera 1 | Bought Already | [Link](https://www.amazon.com/ELP-Embedded-100degree-Distortion-Raspberry/dp/B0BHWHMPKH/ref=sr_1_9?crid=2BH4K6E4KN6KY&dib=eyJ2IjoiMSJ9.9FmZjp5PISg3BqTNKQSAfKnNtqavnhcifD0zRqvrlzWqjxWOquN-KMeXEXgwYHuf6c4sAah4yYthRrNNEImFQPHz1edeVvp_91IfnHACG6EN6TskFv2AWJ7XPaQZh0peZfEW86HQEePWAh4JGsps2SIpp6agvmwo-DJpPB5o1UrA7H7htziLZqa1mc-x4fGZQKKMpz8T2K5O-h7tF97aRe3rUdZKbhuOaFbfXP71QyJfNKfSTq9X1pr3hergiqg5kFWCanViRE-BgdX8n4cz9d33KCTtdf23RC3I_Y5ajAM.TGqOJ8LhrOAt668YLrkew7hg_eYKRdfIRVO4EwVdczM&dib_tag=se&keywords=usb+camera+60fps&qid=1755141181&s=electronics&sprefix=usb+camera+60fp%2Celectronics%2C145&sr=1-9) | 1 | $69.99 | $69.99 |
| Sensors/devices | USB Camera 2 | Bought Already | [Link](https://www.amazon.com/ELP-Raspberry-118degree-Distortion-Industrial/dp/B0C289GYVZ/ref=sr_1_16?crid=193RY57F7X2IR&dib=eyJ2IjoiMSJ9.inJBKkGeN9qOrzJgb6M9Cp_vlaZac7NskM81M5a_wFGAXk03eNVxWq-SpU4SP24qxUoNT5GwLKe_dyuiybuT5ZdCubgefjDEL-vQ7o3zxzGWQs0CphyFYEYnVhQH542ui0zLsNAy8T0vLZM266Q5W2tOG_O5SkzSklsvWoq57DxdvTUS1xu5krL9PsGhTTMtPVUTVZGi3VUr6h1dS6TCZdb8zpDXB21aSRac8u-BTyOVjMR77bTUc7BaWoGFqha6o32TYoRQRPc5ml7xmFIl3Q7ap6dp2ztmxmDAvJ0o3Fo.L3ikXBz4nFR1b33Yz79cRHyXvX3WnOL6PLhVhbWMG5w&dib_tag=se&keywords=high%2Bquality%2Bwide%2Bangle%2Busb%2Bcamera&qid=1755143200&s=electronics&sprefix=high%2Bquality%2Bwide%2Bangle%2Busb%2Bcamera%2Celectronics%2C90&sr=1-16&th=1) | 1 | $74.99 | $74.99 |
| Cables | HDMI Extension Cable (Male to Male) | Bought Already | [Link](https://www.amazon.com/dp/B0DB168WTN?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_1&th=1) | 1 | $15.00 | $15.00 |
| Cables | USB Extension Cable (Type-A Male to Female) | Bought Already | [Link](https://www.amazon.com/dp/B0C653NV2Q?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_3&th=1) | 2 | $4.00 | $8.00 |
| Cables | Arduino Nano Blue Cable | Bought Already | [Link](https://www.amazon.com/DIYables-Mini-Cable-Arduino-Pieces/dp/B0C7BMS5FG/ref=sr_1_2?crid=37VGKR0QC6INL&dib=eyJ2IjoiMSJ9.v1tzJDSy1bp48ogqVHIitl-V79n4CyZZ3LOifvzNvyoN53LhvwLe8PqXbF5MSHHrex4coi_G_GvN3IyHiy8TLlc50ZGbAUFsyX_yH3IsEnyLgoRVloPGn81UcZzGcfdV1KyFQt_VeQb3OrBWvcllTxIQTuhQkMB0vBT0sLpxw-t3a1SOrS58n0ed81-82CHDKdNOZRumBtvznb_iIrMMIrpS0BSi3ZpR0FMXb4nFD-MDAzNMNXtprAQXrU8IOhxE9yUtAWJG-SZVFjwo6Oz0ip2ifQbeXPkK6O9ADGVM7tE.EjReWGOaMPEAnR-BP_jD4xO-kbwx-yYT520nlUvEfBM&dib_tag=se&keywords=arduino%2Bnano%2Bcable&qid=1761595338&s=industrial&sprefix=arduuino%2Bnano%2Bcabl%2Cindustrial%2C132&sr=1-2&th=1) | 1 | $4.00 | $4.00 |
| Cables | NVIDIA Jetson Orin Nano Cable | Bought Already | [Link](https://www.amazon.com/GINTOOYUN-Extension-Adapter-Cable%EF%BC%8C3FT-Monitors/dp/B0B6HT38QD/ref=pd_rhf_se_s_pd_sbs_rvi_d_sccl_2_3/130-2715981-6500301?pd_rd_w=m4zHR&content-id=amzn1.sym.6640a844-ab24-4352-ac9b-78899e683a5e&pf_rd_p=6640a844-ab24-4352-ac9b-78899e683a5e&pf_rd_r=TWDSD8CQ80DWP7R5GBNP&pd_rd_wg=K9Yf1&pd_rd_r=79dcc2d2-e879-479c-bc0b-f50622ba9f4a&pd_rd_i=B0B6HT38QD&psc=1) | 1 | $9.99 | $9.99 |
| Other | Wires, chargers, 3D prints, screws, heatshrink, mechanical parts, etc | Bought Already | N/A | N/A | N/A | $268.00 |
| **Total** |  |  |  |  |  | **$1,236.43** |
