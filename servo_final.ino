#include<Servo.h>
#include <MsTimer2.h>
#include <

Servo servoVer; //Vertical Servo
Servo servoHor; //Horizontal Servo

int x;
int y;
int servoX = 90;
int servoY = 90;

int prevX;
int prevY;

int cP=0;
int cI=0;
int cD=0;

int error = 0;
int prevError = 0;
int kP = 0.9;
int kI = 0.2;
int kD = 0.05;

int prevTime = 0;
int currTime = 0;


void setup()
{
  Serial.begin(9600);
  servoVer.attach(5); //Attach Vertical Servo to Pin 5
  servoHor.attach(6); //Attach Horizontal Servo to Pin 6
  //servoVer.write(90);
  //servoHor.write(90);
}

void Pos()
{
  if(prevX != x || prevY != y)
  {
    //int servoX = map(x, 640, 0, 70, 179);
    //int servoY = map(y, 475, 0, 95, 179);
    int dx = x - 320;
    error = dx;
    currTime = millis();
    int deltaTime = currTime-prevTime;
    int deltaError = error - prevError;
    cP = error;
    cI += error * deltaTime;
    if(deltaTime>0){
      cD = (deltaError/deltaTime);
    }
    else cD = 0;
    prevTime = currTime;
    prevError = error;
    int sum = kP*cP+kI*cI+kD*cD;
    servoX = servoX - sum;
    int dy = y - 474/2;
    servoY = servoY - dy*0.01;
    
    
    servoX = min(servoX, 179);
    servoX = max(servoX, 0);
    servoY = min(servoY, 179);
    servoY = max(servoY, 0);
    
    servoHor.write(servoX);
    servoVer.write(servoY);
  }
}

void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
      x = Serial.parseInt();
      if(Serial.read() == 'Y')
      {
        y = Serial.parseInt();
       delay(200);
       Pos();
      }
    }
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
}
  

