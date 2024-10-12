/*
Taken from Jolly basic Servo sketch
Used to calibrate servo motors for Nerf car
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(110);
}

void loop() {
  /*
  // uncomment this to test the Nerf shot
  myservo.write(60);
  delay(200);
  myservo.write(110);
  delay(200);
  */
}
