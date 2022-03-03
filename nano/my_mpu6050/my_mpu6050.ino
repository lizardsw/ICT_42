#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	#include "Wire.h"
#endif

MPU6050 mpu;

// uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
// pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.
// Also note that yaw/pitch/roll angles suffer from gimbal lock (for
// more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
//#define OUTPUT_READABLE_YAWPITCHROLL

// uncomment "OUTPUT_READABLE_REALACCEL" if you want to see acceleration
// components with gravity removed. This acceleration reference frame is
// not compensated for orientation, so +X is always +X according to the
// sensor, just without the effects of gravity. If you want acceleration
// compensated for orientation, us OUTPUT_READABLE_WORLDACCEL instead.
 #define OUTPUT_READABLE_REALACCEL

#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };


// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
	mpuInterrupt = true;
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
	// join I2C bus (I2Cdev library doesn't do this automatically)
	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
		Wire.begin();
		Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
	#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
		Fastwire::setup(400, true);
	#endif

	Serial.begin(9600);
	while (!Serial); // wait for Leonardo enumeration, others continue immediately
	// initialize device
	mpu.initialize();
	Serial.println(F("Testing device connections..."));
	Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
	Serial.println(F("Initializing DMP..."));
	devStatus = mpu.dmpInitialize();

	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); 

	if (devStatus == 0) {
		mpu.CalibrateAccel(6);
		mpu.CalibrateGyro(6);
		mpu.PrintActiveOffsets();
		Serial.println(F("Enabling DMP..."));
		mpu.setDMPEnabled(true);

		Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
		Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
		Serial.println(F(")..."));
		attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();

		Serial.println(F("DMP ready! Waiting for first interrupt..."));
		dmpReady = true;

		packetSize = mpu.dmpGetFIFOPacketSize();
	} else {
		// ERROR!
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(devStatus);
		Serial.println(F(")"));
	}
}


int	get_accel();
void	set_high_low(long long data);
// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

int count = 0;
int condition = 0;
int data = 0;
long long time = 0;
long long time_zero = 0;
long long highest = 0;
long long lowest = 0;
void loop() {
	if (!dmpReady) return;
	if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet 
		data = get_accel();
		Serial.print(data);
		Serial.print(" ");
		Serial.print(count);
		Serial.print(" ");
		Serial.println(condition);

		if ( (-100 < aaReal.x < 100) && condition == 0)
		{
			time_zero = time;
		}

		if (data > 2500 && condition == 0)
		{
			condition = 1000;
		}
		else if (condition == 1000 && data > -100 && data < 259)
		{
			Serial.print("condition_up! ");
			Serial.println(data);
			condition = 2000;
		}
		else if (condition == 2000 && data > 2500)
		{
			count = count + 100;
			condition = 0;
		}
		if (time - time_zero > 30)
		{
			condition = 0;
		}
		delay(50);
	}
}

int get_accel()
{
	mpu.dmpGetQuaternion(&q, fifoBuffer);
	mpu.dmpGetAccel(&aa, fifoBuffer);
	mpu.dmpGetGravity(&gravity, &q);
	mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
	time++;
	return (aaReal.x);
}

void set_high_low(long long data)
{
	if (highest < data)
		highest = data;
	else if (lowest < data)
		lowest = data;
}