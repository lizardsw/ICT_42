#define SOUND_PIN1 A0
#define SOUND_PIN2 A1
#define SOUND_PIN3 A2
#define SOUND_PIN4 A3






void setup()
{
    Serial.begin(9600);

}

int sensorvalue1 = 0;
int sensorvalue2 = 0;
int sensorvalue3 = 0;
int sensorvalue4 = 0;

void loop()
{
    sensorvalue1 = analogRead(SOUND_PIN1);
    sensorvalue2 = analogRead(SOUND_PIN2);
    sensorvalue3 = analogRead(SOUND_PIN3);
    sensorvalue4 = analogRead(SOUND_PIN4);
    Serial.print(sensorvalue1);
    Serial.print(" ");
    //Serial.print(sensorvalue2);
    //Serial.print(" ");
    //Serial.print(sensorvalue3);
    //Serial.print(" ");
    Serial.print(sensorvalue4);
    Serial.println(" ");

    delay(20);
}