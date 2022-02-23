
#include <SoftwareSerial.h>

////// pin 모음 ////////
#define trigPin 7
#define echoPin 6
#define speakerPin 5

SoftwareSerial app(10, 11); // 블루투스 모듈 RX, TX

char notes[] = "c  ";
int beats = 1;
int tempo = 300;

unsigned count[4];////// count[0] - 턱걸이 [1] - 팔굽 [2] - 스쿼트 [3] - 플랭크
void playTone(int tone, int duration);
void playNote(char note, int duration);
long check_distance();
void app_send(int count);

/////////////// setup ///////////////////////
void setup() {

  Serial.begin(9600);

  app.begin(9600);
  app.write(10000);

  pinMode(echoPin, INPUT); /// 초음파 받는것.
  pinMode(trigPin, OUTPUT); /// 초음파 쏴주는것 같음.
  pinMode(speakerPin, OUTPUT); /// 부저 소리 내주기 output
}
///////////////// loop //////////////////////
void loop() { 

    long distance;
    long prev_distance;
    long mg_distance_max;
    long mg_distance_min;
    int flag = 0;


    prev_distance = check_distance();

    if (prev_distance < )
    {
        ///// 부저 올리고 팔굽 시작!

    }


}

///////playTone output넣어주는거?
void playTone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

//////playNote 음계 설정해주느거?
void playNote(char note, int duration)
{
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };  //음계 함수 설정
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };   // 음계 톤 설정
    for (int i = 0; i < 8; i++)
    {
    if (names[i] == note)
    {
        playTone(tones[i], duration);
    }
    }
}

/////// 거리 확인해주는 함수.
long check_distance()
{
    long duration;
    long distance;

    digitalWrite(trigPin, HIGH);
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = ((float)(340*duration)/1000)/2
    return (distance);
}

////// 앱으로 count 보내주기.
void app_send(int count)
{
    app.println(count);
    Serial.println(count);
}

/////
void init_HC()
{
  long duration, distance;
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340*duration)/1000)/2;

  if (distance < 100 || distance > 3000)
    Serial.print("error, init_HC / make margin distacne");
  mg_distance_max = distance + 100;
  mg_distance_min = distance - 100;
}