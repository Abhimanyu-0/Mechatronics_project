#include <Servo.h>

//Defined servo objects 
Servo rservo;
Servo lservo;

// Setting pins 
int pingPin = 7;
int IRSensorRight = 3; 
int IRSensorLeft = 4;

// Function prototypes
void moveForward();
void moveBackward();
void moveLeft();
void moveRight();
void stop();
void moveaBIT();
void moveBackwardRight();
void moveBackwardLeft();
void executeCommand(char command);
long centi(long microseconds);


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  //attaching servos to pin 9 and 11
  rservo.attach(9);
  lservo.attach(11);
  pinMode(IRSensorRight, INPUT); 
  pinMode(IRSensorLeft, INPUT);
}

void loop() {
   // Serial communication control
  if (Serial.available() > 0) {
  char command = Serial.read();
  executeCommand(command);
  }
  
  // Ultrasonic sensor measurements
  long duration, inches, cm;
  float i =0;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  // Triggering the PING))) sensor
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = centi(duration);

  //Serial.print(inches);
  //Serial.print("in, ");
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();

  int Rstatus = digitalRead(IRSensorRight); 
  int Lstatus = digitalRead(IRSensorLeft);

  // Printing sensor readings only when necessary
  if ( cm < 10 || cm <= 15 || Rstatus == 1 || Lstatus == 1) {
    Serial.print("Distance: ");
    Serial.print(cm);
    Serial.println("cm");
  }
  
  // Robot movement control based on sensor readings

 if (cm >= 16) {
    moveForward();
  } else if (cm < 10) {
    stop();
  } else if (cm <= 15) {
    moveRight();
    moveaBIT();
    moveLeft();
  }

  // If the right IR sensor detects white lane, the robot will go backwards 
  if (Rstatus==0)
  {
   stop();
   moveBackwardRight();
  }
 //If the left IR sensor detects white line, the robot will go backward and left 
  if (Lstatus==0){
    stop();
    moveBackwardLeft();
  }


 
  
}


// Function to execute serial commands
void executeCommand(char command) {
  switch (command) {
    case 'F':
      moveForward();
      break;
    case 'L':
      moveLeft();
      break;
    case 'R':
      moveRight();
      break;
    case 'S':
      stop();
      break;
    // Add more commands as needed
  }
}


long centi(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

// Employed to make the bot move forward endlessly
void moveForward(){
  rservo.attach(9);
  lservo.attach(11);
  float i=0;
  for (i=0;i<=3;i++)
  {rservo.write(0);
  lservo.write(180-i);}
}

//Employed to move the bot to the right 
void moveRight(){
  rservo.detach();
  lservo.attach(11);
  float i=0;
  for (i=0;i<=1;i++)
  {
  lservo.write(180);
  Serial.println(i);
  delay(500);
  // When i=1, the function stops executing
  if (i==1){
  lservo.detach();
  }
  }
}

//Employed to move the boebot to the left 
void moveLeft(){
  lservo.detach();
  rservo.attach(9);
  float i=0;
  for (i=0;i<=2;i++)
  {
  rservo.write(0);
  //Serial.println(i);
  delay(500);
  //Function stops after i=2
  if (i==2){
  rservo.detach();}
  }
}

//Disconnects the servos
void stop(){
  rservo.detach();
  lservo.detach();  
}

//Moves the bot until i=4 unlike moveForward function that is endless 
void moveaBIT(){
  rservo.attach(9);
  lservo.attach(11);

  float i=0;
  for (i=0;i<=4;i++)
  {rservo.write(i);
  lservo.write(180-i);}
  Serial.println(i);
  delay(500);
  if (i==4)
  {
  rservo.detach();
  lservo.detach();
  }
}

// This makes the bot move backwards and right, employed when a (right)lane is encounted by the IR sensor(right)
void moveBackwardRight(){
  rservo.detach();
  lservo.attach(11);
  float i=0;
  for (i=0;i<=2;i++){
  lservo.write(0);
  Serial.println(i);
  delay(500);
  if (i==2)
  {
  lservo.detach();
  }
}
}

//This function makes the bot move backwards and to the left, employed when a (left)lane is encountered by the IR sensor(left)
void moveBackwardLeft(){
  lservo.detach();
  rservo.attach(9);
  float i=0;
  for (i=0;i<=2;i++)
  {
  rservo.write(180);
  //Serial.println(i);
  delay(500);
  if (i==2){
  rservo.detach();}
  }
}
