const int trigPin = 4;
const int echoPin = 3;
long duration;
int distanceCm;
int right = 1;
int left = 2;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  
  if(distanceCm < 200) {
      digitalWrite(right, LOW);
      digitalWrite(left, HIGH);
    }
  else {
    digitalWrite(right, HIGH);
    digitalWrite(left, HIGH);
  }
  delay(100);
}