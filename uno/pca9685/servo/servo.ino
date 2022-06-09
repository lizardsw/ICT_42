#include "servo.h"


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

char contain = 0;
int servoangle[4] = {50, 80, 0 , 0};
int servo[4] = {50,80,0,0};
int prev_servo[4] = {0,0,0,0};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");// Analog servos run at ~50 Hz updates
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50); 
  
  control_motor(&pwm, 1, servo, prev_servo);
  prev_servo[0] = 50;
  prev_servo[1] = 80;

  pinMode(3, OUTPUT);
  Wire.begin(SLAVE);
	Wire.onReceive(receiveFromMaster);
	Wire.onRequest(sendToMaster);

  digitalWrite(3, LOW);
}

//// 고개값 -> 50도가 정면 30도가 땅 70도가 사람.
//// 

int input_x = 0;
int input_y = 0;
int x = 0;
int random_time = 0;

void loop() {
  // Drive each servo one at a time using setPWM()
  if(contain == 0)
  {
    servo[0] = random_head(random(100));
    servo[1] = random_neck(random(100));
    random_time = random(4);
    control_motor(&pwm, 0, servo, prev_servo);
    control_ear(&pwm);
    my_delay(3000 + random_time * 1000);
    prev_servo[0] = servo[0];
    prev_servo[1] = servo[1];
  }
  else if (contain == '1')
  {
    sleeping(&pwm, prev_servo);
    contain = 0;
  }
  else if (contain == '2')
  {
    sading(&pwm, prev_servo);
    contain = 0;
  }
  else if (contain == '3')
  {
    angrying(&pwm, prev_servo);
    contain = 0;
  }


  if (stop_time[motor] && millis >= stop_time[motor])
  {
    stop_motor(pwm, motor);
    stop_time[motor] = 0;
  }
  if 
}

void receiveFromMaster(int bytes) {
	char ch[2];
	for (int i = 0 ; i < bytes ; i++) {
		// 수신 버퍼 읽기
		ch[i] = Wire.read(); 
	}
	contain = ch[0];
	Serial.println(contain);
	digitalWrite(3, HIGH);
	delay(300);
	digitalWrite(3, LOW);
}

void sendToMaster() {
	// 자신의 슬레이브 주소를 담은 메세지를 마스터에게 보냅니다. 슬레이브 주소에 맞게 수정해야 합니다.
	Wire.write("4th Arduino ");
}


void my_delay(int time)
{
	int i = 0;
	while(i < time)
	{
		if (contain != 0)
			break;
		delay(1);
		i++;
	}
}


/*
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  //pwm.setPWM(n, 0, pulse);
}
*/

