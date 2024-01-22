#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right          GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right          GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left           GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left           GPIO0(D3)

// Define LED pins
#define WHITE_LED 16    // GPIO16 (D0)
#define RED_LED 5       // GPIO5 (D1)
#define GREEN_LED1 4    // GPIO4 (D2)
#define GREEN_LED2 3    // GPIO3 (D3)

int speedCar = 800;     // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "ZahidRobotCar";
ESP8266WebServer server(80);

String command;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  pinMode(WHITE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED1, OUTPUT);
  pinMode(GREEN_LED2, OUTPUT);

  Serial.begin(115200);

  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void ledController(bool white, bool red, bool green1, bool green2) {
  digitalWrite(WHITE_LED, white);
  digitalWrite(RED_LED, red);
  digitalWrite(GREEN_LED1, green1);
  digitalWrite(GREEN_LED2, green2);
}

void moveCar(bool in1, bool in2, bool in3, bool in4) {
  digitalWrite(IN_1, in1);
  digitalWrite(IN_2, in2);
  digitalWrite(IN_3, in3);
  digitalWrite(IN_4, in4);
}

void goAhead() {
  ledController(true, false, false, false); // White LED blinks when going forward
  moveCar(false, true, false, true);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goBack() {
  ledController(false, true, false, false); // Red LED blinks when going backward
  moveCar(true, false, true, false);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goLeft() {
  ledController(false, false, true, false); // Green LED 1 blinks when going left
  moveCar(false, true, true, false);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goRight() {
  ledController(false, false, false, true); // Green LED 2 blinks when going right
  moveCar(true, false, false, true);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goAheadRight() {
  ledController(true, false, false, false); // White LED blinks when going ahead-right
  moveCar(false, true, false, true);
  analogWrite(ENA, speedCar / speed_Coeff);
  analogWrite(ENB, speedCar);
}

void goAheadLeft() {
  ledController(true, false, false, true); // White and Green LEDs blink when going ahead-left
  moveCar(false, true, true, false);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goBackRight() {
  ledController(false, true, true, false); // Red and Green LEDs blink when going back-right
  moveCar(true, false, false, true);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goBackLeft() {
  ledController(false, true, false, true); // Red and Green LEDs blink when going back-left
  moveCar(true, false, true, false);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void stopRobot() {
  ledController(false, true, false, false); // Red LED blinks when stopping
  moveCar(false, false, false, false);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void loop() {
  server.handleClient();

  command = server.arg("State");

  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "0") speedCar = 400;
  else if (command == "1") speedCar = 470;
  else if (command == "2") speedCar = 540;
  else if (command == "3") speedCar = 610;
  else if (command == "4") speedCar = 680;
  else if (command == "5") speedCar = 750;
  else if (command == "6") speedCar = 820;
  else if (command == "7") speedCar = 890;
  else if (command == "8") speedCar = 960;
  else if (command == "9") speedCar = 1023;
  else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}
