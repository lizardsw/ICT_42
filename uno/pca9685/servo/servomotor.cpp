#include "servo.h"

///900 - 180도
void slow_motor_control(Adafruit_PWMServoDriver *pwm,int motor, int angle, int *prev_angle, int speed = 50)
{
	
	if(*prev_angle >= angle)
	{
		for (int i = *prev_angle; i >= angle; i--) 
		{
				Serial.println(i);
    			pwm -> setPWM(motor, 0, angleToPulse(i));
				delay(speed);
		}
	}
	else
	{
		for(int i = *prev_angle; i < angle; i++)
		{
			Serial.println(i);
    		pwm -> setPWM(motor, 0, angleToPulse(i));
			delay(speed);
		}

	}
	pwm -> setPWM(0, 0, 4096);
	*prev_angle = angle;
}

void sleeping(Adafruit_PWMServoDriver *pwm, int *prev_angle)
{
	int rand_switch = random(2);

	if (rand_switch == 0)
		slow_motor_control(pwm, 0, 10, &prev_angle[0], 30);
	else
	{	
		pwm -> setPWM(1, 0, angleToPulse(80));
		slow_motor_control(pwm, 0, 10, &prev_angle[0], 30);
	}
	pwm -> setPWM(2, 0, angleToPulse(180));
	pwm -> setPWM(3, 0, angleToPulse(0));	
	delay(4000);

}

void sading(Adafruit_PWMServoDriver *pwm, int *prev_angle)
{
	pwm -> setPWM(2, 0, angleToPulse(180));
	pwm -> setPWM(3, 0, angleToPulse(0));	

	pwm -> setPWM(0, 0, angleToPulse(20));
	slow_motor_control(pwm, 1, 30, &prev_angle[1], 10);
	slow_motor_control(pwm, 1, 130, &prev_angle[1], 10);
	slow_motor_control(pwm, 1, 80, &prev_angle[1], 10);
	
	delay(4000);
}

void angrying(Adafruit_PWMServoDriver *pwm, int *prev_angle)
{
	int rand_switch = random(2);

	if (rand_switch == 0)
		slow_motor_control(pwm, 0, 10, &prev_angle[0], 30);
	else
	{	
		pwm -> setPWM(1, 0, angleToPulse(80));
		slow_motor_control(pwm, 0, 10, &prev_angle[0], 30);
	}
	pwm -> setPWM(2, 0, angleToPulse(180));
	pwm -> setPWM(3, 0, angleToPulse(0));	
	delay(4000);
}

void happying()
{


}


void control_motor(Adafruit_PWMServoDriver *pwm, int motor, int *angle, int *prev_angle)
{
	
	int pulse_0 = angleToPulse(angle[0]);
	int time_0 = initial_time(angle[0], prev_angle[0]);
	int pulse_1 = angleToPulse(angle[1]);
	int time_1 = initial_time(angle[0], prev_angle[1]);
	int time = (time_0 > time_1) ? time_0 : time_1;
	
	pwm -> setPWM(0, 0, pulse_0);
	pwm -> setPWM(1, 0, pulse_1);
	control_ear(pwm);
	delay(time);
	pwm -> setPWM(0, 0, 4096);
	pwm -> setPWM(1, 0, 4096);
}

void control_motor(Adafruit_PWMServoDriver *pwm, int motor, int tar_angle, int cur_angle)
{
	int time = initial_time(tar_angle, cur_angle);

	pwm -> setPWM(motor, 0, angleToPulse(tar_angle));
	
	// 일정 등록 -> (현재시간 + time) - pwm -> setPWM(motor, 0, 4096);
}

void stop_motor(Adafruit_PWMServoDriver *pwm, int motor)
{
	pwm -> setPWM(motor, 0, 4096);
}

void control_ear(Adafruit_PWMServoDriver *pwm, int angle = 0)
{
	int count = random(0, 4);

	int rand_angle = 0;
	for(int i = 0; i < count; i++)
	{
		rand_angle = random(0,  180);
		pwm -> setPWM(2, 0, angleToPulse(rand_angle));
		pwm -> setPWM(3, 0, angleToPulse(abs(180 - rand_angle)));	
		delay(100);
	}
}


int angleToPulse(int angle)
{
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

int initial_time(int angle, int prev_angle)
{
	int temp;

	temp = angle - prev_angle;
	if (temp < 0)
		temp = -temp;
	temp = temp *5; 
	if (temp < 300)
		temp = 300;
	return temp;
}

int random_head(int random_number)
{
	if(random_number <= 30)
		return 40;
	else if(random_number <= 40)
		return 20;
	else if(random_number <= 50)
		return 60;
	else if(random_number <= 70)
		return 30;
	else if(random_number <= 900)
		return 50;
	else if(random_number <= 100)
		return 70;
	return 40;
}

int random_neck(int random_number)
{
	if(random_number <= 30)
		return 80;
	else if(random_number <= 40)
		return 40;
	else if(random_number <= 50)
		return 120;
	else if(random_number <= 70)
		return 100;
	else if(random_number <= 90)
		return 60;
	else if(random_number <= 95)
		return 20;
	else if(random_number <= 100)
		return 140;
	return 80;


}