# ESP8266 Robot Car Control

This project provides code for controlling a robot car using an ESP8266 microcontroller. The car can be remotely controlled through a web interface.

## Features

- **Forward Movement**: The robot car can move forward with the white LED blinking.
- **Backward Movement**: The red LED blinks when the car moves backward.
- **Left and Right Movement**: The two green LEDs blink when the car moves left or right.
- **Diagonal Movement**: The car can move diagonally with the white LED blinking in the respective direction.
- **Variable Speed**: The speed of the car can be adjusted using commands.

## Hardware Requirements

- ESP8266 microcontroller (NodeMCU or similar)
- L298N motor driver module
- Four LEDs (white, red, and two green)
- DC motors and wheels for the robot car
- Power source for the motors and ESP8266

## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/zahidprvz/robot-car-code.git
   ```

2. Open the Arduino IDE and install the ESP8266 board package. Add the following URL to the "Additional Boards Manager URLs" in Arduino Preferences:

   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```

   Install the ESP8266 board package using the Boards Manager.

3. Connect the hardware components according to the wiring specified in the code.

4. Upload the code to your ESP8266 board.

5. Open the serial monitor to view the IP address assigned to the access point. Connect your device to this access point.

6. Open a web browser and enter the IP address in the address bar to access the control interface.

## Mobile App

You can download the mobile app to control the robot car using the following link:

[Download Mobile App](https://www.electroniclinic.com/wp-content/uploads/2021/12/NodeMCU-Car-Make-DIY.zip)

## Usage

1. Power on the robot car.

2. Connect your device to the Wi-Fi access point hosted by the ESP8266.

3. Open a web browser and enter the IP address provided in the serial monitor.

4. Use the web interface to control the movement and speed of the robot car.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
