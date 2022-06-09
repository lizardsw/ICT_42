#include <Servo.h> 
 
int servoPin = 9;

Servo servo; 
String temp;

int angle = 0; // servo position in degrees 

void setup() 
{ 
    servo.attach(servoPin); 
	Serial.begin(9600);
}



void loop() 
{ 
  servo.write(0);
  Serial.println("0");
  delay(1000);
  servo.write(90);
  Serial.println("90");
  delay(1000);
  servo.write(180);
  Serial.println("180");
  delay(1000);
  /*
  for(angle = 0; angle < 180; angle++) 
  { 
    servo.write(angle); 
    delay(15); 
  }  
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--) 
  { 
    servo.write(angle); 
    delay(15); 
  } 
  */
} 