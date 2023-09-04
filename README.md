# Weather Monitoring using DHT-11 and ESP8266 WiFi Transmitter

## Introduction

Welcome to the Weather Monitoring project using the DHT-11 sensor and ESP8266 WiFi transmitter! This project allows you to collect temperature and humidity data using the DHT-11 sensor and transmit it to the ThingSpeak cloud for storage and visualization. The Arduino board is used to process the sensor data and control the ESP8266 module for data transmission.

## Prerequisites

Before you begin, ensure you have the following components ready:

- Arduino board (e.g., Arduino Uno)
- DHT-11 temperature and humidity sensor
- ESP8266 WiFi module (e.g., ESP-01, ESP-12E)
- Jumper wires
- USB cable for programming Arduino
- Access to a computer with Arduino IDE installed

## Installation and Setup

1. **Hardware Setup:**

   - Connect the DHT-11 sensor to the Arduino board as follows:
     - DHT-11 VCC to Arduino 5V
     - DHT-11 GND to Arduino GND
     - DHT-11 DATA to Arduino digital pin

   - Connect the ESP8266 to the Arduino board as follows:
     - ESP8266 VCC to Arduino 3.3V
     - ESP8266 GND to Arduino GND
     - ESP8266 TX to Arduino RX (you may need a voltage divider for this connection)
     - ESP8266 RX to Arduino TX

   - Double-check your connections and ensure everything is securely connected.

2. **Software Setup:**

   - Open the Arduino IDE on your computer.

   - Download and install the necessary libraries:
     - Adafruit DHT library for the DHT-11 sensor.
     - ESP8266WiFi library for ESP8266 communication.
     - ThingSpeak library for sending data to ThingSpeak.

   - Clone or download this project's repository to your computer.

   - Open the Arduino sketch (`WiFi_code.ino`) from the project repository in the Arduino IDE.

   - Modify the following lines in the code to match your WiFi network credentials:

     
        ssid = "YOUR_WIFI_SSID";
        password = "YOUR_WIFI_PASSWORD";
   

3. **Upload Code:**

   - Connect your Arduino to your computer using the USB cable.

   - Select the correct board type (e.g., Arduino Uno) and COM port in the Arduino IDE.

   - Click the "Upload" button to upload the code to the Arduino board.

   - Once the code is uploaded, disconnect the USB cable from the Arduino.

4. **Operation:**

   - Power up your project, and it will start collecting temperature and humidity data using the DHT-11 sensor.

   - The ESP8266 will connect to your WiFi network and send the data to the ThingSpeak cloud.

   - You can monitor the data on the ThingSpeak dashboard by logging into your ThingSpeak account.

## Troubleshooting

If you encounter any issues or need further assistance, please refer to the project's documentation or consult the Arduino and ESP8266 community forums.

## License

This project is released under the [MIT License](LICENSE).

## Acknowledgments

- Thanks to the Arduino, ESP8266, and ThingSpeak communities for their support and resources.

Happy weather monitoring!
