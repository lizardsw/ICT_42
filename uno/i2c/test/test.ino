#define OLED 3


void setup()
{
	pinMode(OLED, OUTPUT);
	pinMode(4, OUTPUT);
	digitalWrite(OLED, LOW);
}

void loop()
{
	digitalWrite(3, HIGH);
	my_delay(1000);
	digitalWrite(3, LOW);
	delay(2000);

}



void my_delay(int time)
{
	int i = 0;
	while(i < time)
	{
		delay(1);
		i++;
	}
}