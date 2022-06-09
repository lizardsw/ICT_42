#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/////// A4 - SDA A5 - SCL

// called this way, it uses the default address 0x40

// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);


#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define SLAVE 3



void sleeping(Adafruit_PWMServoDriver *pwm, int *prev_angle);
void sading(Adafruit_PWMServoDriver *pwm, int *prev_angle);
void angrying(Adafruit_PWMServoDriver *pwm, int *prev_angle);


int angleToPulse(int angle);
int initial_time(int angle, int prev_angle);
void control_motor(Adafruit_PWMServoDriver *pwm, int motor, int *angle, int *prev_angle);
int random_head(int random_number);
int random_neck(int random_number);
void control_ear(Adafruit_PWMServoDriver *pwm, int angle = 0);
void slow_motor_control(Adafruit_PWMServoDriver *pwm,int motor, int angle, int *prev_angle, int speed = 50);