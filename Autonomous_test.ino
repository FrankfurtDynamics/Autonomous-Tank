
// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 3
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9
#define echoPinfront 50
#define trigPinfront 51
#define echoPinleft 52
#define trigPinleft 53
#define echoPinright 48
#define trigPinright 49

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;
long durationfront; 
int distancefront = 46; 
long durationleft; 
int distanceleft; 
long durationright; 
int distanceright; 
int Dreher = 0;
int ruck = 0;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup()
{
  pinMode(trigPinfront, OUTPUT); 
  pinMode(echoPinfront, INPUT); 
  pinMode(trigPinleft, OUTPUT); 
  pinMode(echoPinleft, INPUT);
  pinMode(trigPinright, OUTPUT); 
  pinMode(echoPinright, INPUT);  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}


void loop()
{
  while (distancefront <= 45){
  brake(motor1, motor2);
  digitalWrite(trigPinleft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinleft, LOW);
  durationleft = pulseIn(echoPinleft, HIGH);
  distanceleft = durationleft * 0.034 / 2;
  
  digitalWrite(trigPinright, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinright, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinright, LOW);
  durationright = pulseIn(echoPinright, HIGH);
  distanceright = durationright * 0.034 / 2;

  if (distanceleft <= distanceright){
    Dreher = 0;
    Serial.print("Turn right");
    right(motor1, motor2, 180);
    right(motor1, motor2, 180);
    delay(1000);
  digitalWrite(trigPinfront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinfront, LOW);
  durationfront = pulseIn(echoPinfront, HIGH);
  distancefront = durationfront * 0.034 / 2;
  Serial.print("Distancefront: ");
  Serial.print(distancefront);
  Serial.println(" cm");
  delay(250);
  }
  else{
    Dreher = 0;
    Serial.print("Turn left");
    left(motor1, motor2, 180);
    left(motor1, motor2, 180); 
    delay(1000);
  digitalWrite(trigPinfront, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinfront, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationfront = pulseIn(echoPinfront, HIGH);
  // Calculating the distance
  distancefront = durationfront * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distancefront: ");
  Serial.print(distancefront);
  Serial.println(" cm");
  delay(250);
  }
  }  
  while (distancefront > 45){
 forward(motor1, motor2, 100);
 Serial.print("Forward");
  digitalWrite(trigPinfront, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinfront, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationfront = pulseIn(echoPinfront, HIGH);
  // Calculating the distance
  distancefront = durationfront * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distancefront: ");
  Serial.print(distancefront);
  Serial.println(" cm");
  delay(250);
  }
}
