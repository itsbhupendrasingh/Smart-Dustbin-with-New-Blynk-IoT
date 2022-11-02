/*
 * This program is property of SME Dehradun. for any query related to this program, 
 * contact us at www.smedehradn.com
 * if your want any soluiton related for any IoT Customized Boards and Sensor, 
 * then contact to www.nuttyengineer.com 
 */
// Fill-in information from your Blynk Template here

#define BLYNK_TEMPLATE_ID "TMPL4yDpPzsU"
#define BLYNK_DEVICE_NAME "Smart Dustbin"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#include "BlynkEdgent.h"

#define echoPin 32
#define trigPin 33
#include<Servo.h>
Servo servo;
long duration;
int distance; 
int binLevel=0;

void sendSensor()
{
  int ir=digitalRead(34);
  if(ir==LOW)
  {    
    servo.write(90);
    for(int i=0; i<50; i++) // it will be open dustbin flap for 5 second
    {
      Blynk.virtualWrite(V2, 90);
      ultrasonic(); 
      delay(100);
    }
    servo.write(0);
    Blynk.virtualWrite(V2, 0);
  }
  if(ir==HIGH)
  {
    
    ultrasonic();
    delay(200);
  }
}
void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel=map(distance, 21, 0, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0, distance);
    Blynk.virtualWrite(V1, binLevel);
}
void setup()
{
  Serial.begin(9600);
  servo.attach(13);
  pinMode(34, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  BlynkEdgent.begin();
  delay(2000); 
  timer.setInterval(1000L, sendSensor); 
}

void loop() 
{
  BlynkEdgent.run();
  timer.run(); // Initiates SimpleTimer
}
