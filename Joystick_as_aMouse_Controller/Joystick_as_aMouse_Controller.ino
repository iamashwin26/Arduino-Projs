/*
  Joystick as a Mouse Controller 

 Controls the mouse from a joystick on an Arduino Leonardo, Micro or Due.
 Uses pushbutton to click the left mouse button and when long clicked prodces a right click
 and blinnks an led in either case.

 Hardware:
 * 2-axis joystick connected to pins A0 and A1
 * pushbuttons connected to pin D3
 *  led(+ leade) connected to D2 and (- lead) connected to ground.

 The mouse movement is always relative. This sketch reads
 two analog inputs that range from 0 to 1023 (or less on either end)
 and translates them into ranges of -5 to 5.
 Use the variable velocity to controll the cursor speed.
 The sketch assumes that the joystick resting values are around the
 middle of the range, but that they vary within a threshold.

 WARNING:  When you use the Mouse.move() command, the Arduino takes
 over your mouse!  Make sure you have control before you use the command.
 This sketch includes a pushbutton to toggle the mouse control state, so
 you can turn on and off mouse control.

 created 06 July  2017

 by Ashwin Kumar K
 this code is in the public domain

 */
#include "Mouse.h"
const int xpin=A0,ypin=A1,btn=3,led=2;//pin number for x,y axis and led and button
float velocity = 0.6;//velocity controlls the speed of cursor mobvement , it should be beteween 1 and 0
int  range = (10 * velocity) , wait = 5 , threshold = (range / 3) , center = (range / 2) ;// paramenters

int readAxis(int ipin)
{
  int reading = analogRead(ipin);
  reading = map(reading,0,1023,0,range);// map the reading from the analog input range to the output range:
  int distance = reading - center;
  if (abs(distance)<threshold)
  {distance= 0;}
  return distance;
  }

void setup() 
{
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(btn,INPUT_PULLUP);
  Serial.begin(9600);
  Mouse.begin();
}

void loop() 
{
  int t = 0;
  int xreading = readAxis(xpin);// read the x and y distances
  int yreading = readAxis(ypin);
  Mouse.move(xreading,yreading,0); // move the cursor according to xreading and yreading


// The following code is for mouse(button) click 
  
  while (digitalRead(btn)== LOW && t<10)
  {
    delay(100);
    t++;
    }
  
  
  if(t>0) Serial.print(t);
  
  if (t<10 && t>0)
  {
    Serial.write("Left clicked \n");
    digitalWrite(led, HIGH);
    Mouse.press(MOUSE_LEFT);
    delay(wait*4);
    Mouse.release(MOUSE_LEFT);
    digitalWrite(led, LOW);
    }
   if (t >= 10) 
   {
    Serial.write("Right clicked \n");
    digitalWrite(led, HIGH);
    Mouse.press(MOUSE_RIGHT);
    delay(wait*4);
    Mouse.release(MOUSE_RIGHT);
    digitalWrite(led, LOW);
    delay(200);// this timing is important
    
    }
   delay(wait);
  
}
