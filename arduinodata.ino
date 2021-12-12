#define echoPinleft 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinleft 3 //attach pin D3 Arduino to pin Trig of HC-SR04

#define echoPinright 4 // attach pin D4 Arduino to pin Echo of HC-SR04
#define trigPinright 5 //attach pin D5 Arduino to pin Trig of HC-SR04

#define left 8
#define right 10

// defines variables
long durationleft; // variable for the duration of sound wave travel
int distanceleft; // variable for the distance measurement

// defines variables
long durationright; // variable for the duration of sound wave travel
int distanceright; // variable for the distance measurement

void setup() {
  pinMode(trigPinleft, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinleft, INPUT); // Sets the echoPin as an INPUT
  
  pinMode(trigPinright, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinright, INPUT); // Sets the echoPin as an INPUT
  
  pinMode(right,OUTPUT);
  pinMode(left,OUTPUT);
  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPinleft, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinleft, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationleft = pulseIn(echoPinleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinright, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinright, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinright, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationright = pulseIn(echoPinright, HIGH);
  // Calculating the distance
  distanceleft = durationleft * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  distanceright = durationright * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  if (distanceleft < 20) {
    digitalWrite(right,HIGH);
    digitalWrite(left,LOW);
    
  } else if (distanceright < 20) {
    digitalWrite(right,LOW);
    digitalWrite(left,HIGH);
    
  } else {
    digitalWrite(left,HIGH);
    digitalWrite(right,HIGH);
  }
  
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distanceleft);
  Serial.println(" cm");
  
  Serial.print("Distance: ");
  Serial.print(distanceright);
  Serial.println(" cm");
}
