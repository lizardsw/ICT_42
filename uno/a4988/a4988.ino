#define dirPin 2
#define stepPin 3 
#define enPin 4
#define stepsPerRevolution 200



int change_degree(double x, double y);


void setup() {
  // Declare pins as output:
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);

  digitalWrite(enPin, LOW);
}

String temp;
boolean input_x;
boolean input_y;
int x;
int y;
int degree;
int prev_degree;
/// 4000 - 205가 360도
int pulse;
void loop() {
  step_angle(180);
  delay(1000);
  step_angle(90);
  delay(1000);
  /*
  if(Serial.available() > 0)
  {
    temp = Serial.readStringUntil('\n');
    Serial.println(temp);
    if(input_x == false && input_y == false)
    {
      x = temp.toDouble();
      input_x = true;
    }
    else if(input_x == true && input_y == false)
    {
      y = temp.toDouble();
      input_y = true;
    }

    if (input_x == true && input_y == true)
    {
      Serial.print("x : ");
      Serial.print(x);
      Serial.print("y : ");
      Serial.println(y);
      degree = change_degree(y, x);
      Serial.println(degree);
      step_angle(0, degree);
      input_x = false;
      input_y = false;
    }
  }
*/
}

int change_degree(double x, double y)
{
  int bx = round( (atan2(x, y) * 180)/3.14159265 ); 
  return (bx);
}

void step_angle(int angle)
{
  
  int pulse = angle;
  pulse = angle * 5 / 9;
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < pulse; i++) 
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(4000);
    }
}