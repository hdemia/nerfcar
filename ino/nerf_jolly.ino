/* nerf_jolly.ino
 *
 * This example shows how to access digital and analog pins
 * of the board through REST calls. It demonstrates how you
 * can create your own API when using REST style calls through
 * the browser.
 *
 * Possible commands created in this shetch:
 *
 * "/jolly/forward"       -> goForward()
 * "/jolly/backward"      -> goBackward()
 * "/jolly/left"          -> goLeft()
 * "/jolly/right"         -> goRight()
 * "/jolly/shoot"         -> shoot()
 * 

 * Connect to the board's web panel through a browser (type the
 * board's ip if the board is already connected to a network or
 * connect your computer to the board's SSID and type the default
 * address 192.168.240.1 in order to access the web panel). Open
 * the tab "Wi-Fi Pin Control" to send commands to the board by
 * pressing the related buttons.
 * Alternatively you can directly send the REST command by typing
 * on a browser the board's address and the desired command.
 * e.g. http://yourIpAddress:8080/jolly/digital/9/1
 
 WIRING
 - Right motor: OUT2 Vcc - OUT1 GND
 - Left motor: OUT3 Vcc - OUT4 GND 
 */


#include "WiFi.h"
#include "L298N.h"
#include "Servo.h"

#define ENA 2
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define ENB 7

#define SPEED 255
#define DELAY_SHOOT 200
#define DELAY_MOVE 1000
#define DELAY_TURN 1000

#define SERVO_PIN 9
#define ANGLE_REST 110
#define ANGLE_SHOOT 60

Servo servo;

L298N rightMotor(ENA, IN1, IN2);
L298N leftMotor(ENB, IN3, IN4);

// server will listen on port 8080
WiFiServer server(8080);
WiFiClient client;


void setup() {
  
  servo.attach(SERVO_PIN);
  servo.write(ANGLE_REST);

  rightMotor.setSpeed(SPEED);
  leftMotor.setSpeed(SPEED);

  Serial.begin(115200);
  Serial.println("Checking WiFi linkage");

  /*
	  begin ESP8266 chip: these functions perform the chip reset and
	  initialization to ensure that the communication between ESP8266
	  and the main mcu starts in a known fashion.
  */
  WiFi.reset();
  WiFi.init(AP_STA_MODE);


  if (WiFi.status() == WL_NO_WIFI_MODULE_COMM) {
    /*
       notify the user if the previous sequence of operations to establish
       the communication between the ESP and the 328P fail.
    */
    Serial.println("Communication with WiFi module not established.");
  }
  else {
	/*
       otherwise we have a correct communication between the two chips
       and we can connect to a preferred network
    */
    Serial.println("WiFi module linked!");

    Serial.println("Attempting to connect to a stored network");

	/*
       In this case we are trying to connect to a stored network.
	   Look at ConnectToASavedNetwork example to have further information.
    */
    if (WiFi.begin() != WL_CONNECTED) {

      if (WiFi.status() != WL_CONNECTED) {
		/*
           if the connection fails due to an error...
        */
        Serial.println("Connection error! Check ssid and password and try again.");
      }
    }
    server.begin();
  }


}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  while (client.connected()) {
    // Process request
    process(client);
    // Close connection and free resources.
    delay(1);
    client.stop();
  }

  /*
     In the case of a connect event, notify it to the user.
  */
  if (WiFi.connectionStatus == WL_CONNECTED && WiFi.notify == true) {
    WiFi.notify = false;
    Serial.print("You're connected to the network ");
    printWifiStatus();
  }
  /*
     In the case of a disconnect event, notify it to the user.
  */
  else if (WiFi.connectionStatus == WL_DISCONNECTED && WiFi.notify == true) {
    WiFi.notify = false;
    Serial.println("You've been disconnected");
  }

}


void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

bool listen_service(WiFiClient client, String service)
{
  //check service
  String currentLine = "";
  while (client.connected()) {
    if (client.available() > 0) {
      char c = client.read();
      currentLine += c;
      if (c == '\n') {
        client.println("HTTP/1.1 200 OK");
        client.println();
        return 0;
      }
      else if (currentLine.endsWith(service + "/")) {
        
        return 1;
      }
    }
  }
}

// -----------------------------------------------------------------
void process(WiFiClient client)
{
  // read the command//
  if (listen_service(client, "jolly")) {
    String command = client.readStringUntil('/');

    if (command == "forward") {
      goForward();
    }
    else if (command == "backward") {
      goBackward();
    }
    else if (command == "left") {
      goLeft();
    }
    else if (command == "right") {
      goRight();
    }
    else if (command == "shoot") {
      shoot();
    }
    else {
      // flush input before replying - needed by some browser
      client.flush();
      client.print(String("HTTP/1.1 200 OK\r\n\r\nError!\r\nUnknown command : " + command + "\r\n\r\n"));
    }

    client.println("HTTP/1.1 200 OK");
    client.println();
  }
}

void goForward(){
  rightMotor.forward();
  leftMotor.forward();
  delay(DELAY_MOVE);
  rightMotor.stop();
  leftMotor.stop();
  Serial.println("forward");
}

void goBackward(){
  rightMotor.backward();
  leftMotor.backward();
  delay(DELAY_MOVE);
  rightMotor.stop();
  leftMotor.stop();
  Serial.println("backward");
}

void goLeft(){
  rightMotor.forward();
  leftMotor.backward();
  delay(DELAY_TURN);
  rightMotor.stop();
  leftMotor.stop();
  Serial.println("left");
}

void goRight(){
  rightMotor.backward();
  leftMotor.forward();
  delay(DELAY_TURN);
  rightMotor.stop(); 
  leftMotor.stop();
  Serial.println("right");
}

void shoot(){
  servo.write(ANGLE_SHOOT);
  delay(DELAY_SHOOT);
  servo.write(ANGLE_REST);
  Serial.println("shoot");
}