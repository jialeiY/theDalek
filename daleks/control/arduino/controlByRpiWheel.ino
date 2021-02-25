#include <Servo.h>


String incomingVal="";

int motorFrontRightPin1=46;
int motorFrontRightPin2=48;

int motorBackRightPin1=50;
int motorBackRightPin2=52;

int motorFrontLeftPin1=38;
int motorFrontLeftPin2=40;

int motorBackLeftPin1=42;
int motorBackLeftPin2=44;

int cameraServoPin=34;

Servo cameraServo;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);  
  pinMode(motorFrontRightPin1,OUTPUT);
  pinMode(motorFrontRightPin2,OUTPUT);

  pinMode(motorBackRightPin1,OUTPUT);
  pinMode(motorBackRightPin2,OUTPUT);

  pinMode(motorFrontLeftPin1,OUTPUT);
  pinMode(motorFrontLeftPin2,OUTPUT);

  pinMode(motorBackLeftPin1,OUTPUT);
  pinMode(motorBackLeftPin2,OUTPUT);
  
  cameraServo.attach(cameraServoPin);
}

void forward(){
  analogWrite(motorFrontRightPin1,0);
  analogWrite(motorFrontRightPin2,180);
  
  analogWrite(motorBackRightPin1,0);
  analogWrite(motorBackRightPin2,180);

  analogWrite(motorFrontLeftPin1,180);
  analogWrite(motorFrontLeftPin2,0);
  
  analogWrite(motorBackLeftPin1,180);
  analogWrite(motorBackLeftPin2,0);
}

void backward(){
  analogWrite(motorFrontRightPin1,180);
  analogWrite(motorFrontRightPin2,0);
  
  analogWrite(motorBackRightPin1,180);
  analogWrite(motorBackRightPin2,0);

  analogWrite(motorFrontLeftPin1,0);
  analogWrite(motorFrontLeftPin2,180);
  
  analogWrite(motorBackLeftPin1,0);
  analogWrite(motorBackLeftPin2,180);
  
}

void right(){
  analogWrite(motorFrontRightPin1,180);
  analogWrite(motorFrontRightPin2,0);
  
  analogWrite(motorBackRightPin1,0);
  analogWrite(motorBackRightPin2,180);

  analogWrite(motorFrontLeftPin1,180);
  analogWrite(motorFrontLeftPin2,0);
  
  analogWrite(motorBackLeftPin1,0);
  analogWrite(motorBackLeftPin2,180);
  
}

void left(){
  analogWrite(motorFrontRightPin1,0);
  analogWrite(motorFrontRightPin2,180);
  
  analogWrite(motorBackRightPin1,180);
  analogWrite(motorBackRightPin2,0);

  analogWrite(motorFrontLeftPin1,0);
  analogWrite(motorFrontLeftPin2,180);
  
  analogWrite(motorBackLeftPin1,180);
  analogWrite(motorBackLeftPin2,0);
  
}

void stop(){
  analogWrite(motorFrontRightPin1,0);
  analogWrite(motorFrontRightPin2,0);
  
  analogWrite(motorBackRightPin1,0);
  analogWrite(motorBackRightPin2,0);
  
  analogWrite(motorFrontLeftPin1,0);
  analogWrite(motorFrontLeftPin2,0);
  
  analogWrite(motorBackLeftPin1,0);
  analogWrite(motorBackLeftPin2,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    incomingVal=Serial.readString();
    
    if(incomingVal.equals("forward")){
      forward();
      delay(1000);
    }
    else if (incomingVal.equals("backward")){
      backward();
      delay(1000);
    }
    else if(incomingVal.equals("left")){
      left();
      delay(1000);
    }
    else if(incomingVal.equals("right")){
      right();
      delay(1000);
    }else if(incomingVal.toInt()>=0){
      cameraServo.write(incomingVal.toInt());
    }
    else{
      stop();  
    }
    stop();

  }


}
