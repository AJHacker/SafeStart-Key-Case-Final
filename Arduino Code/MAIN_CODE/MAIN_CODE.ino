/*
	FPS_Enroll.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	Created by Josh Hawley, July 23rd 2013
	Licensed for non-commercial use, must include this license message
	basically, Feel free to hack away at it, but just give me credit for my work =)
	TLDR; Wil Wheaton's Law

	This sketch will attempt to identify a previously enrolled fingerprint.
*/

#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
#include <Servo.h>

Servo myservo;
// Hardware setup - FPS connected to:
//	  digital pin 4(arduino rx, fps tx)
//	  digital pin 5(arduino tx - 560ohm resistor fps tx - 1000ohm resistor - ground)
//		this brings the 5v tx line down to about 3.2v so we dont fry our fps
int pos = 160;
FPS_GT511C3 fps(4, 5);

void setup()
{
  
  myservo.attach(9);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  fps.Open();
  myservo.write(pos);
  fps.SetLED(true);
 
}

void loop()
{

  // Identify fingerprint test
  if (fps.IsPressFinger())
  {

    digitalWrite(3, HIGH);
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id < 200)
    {
      digitalWrite(6, HIGH);
      Serial.print("Verified ID:");
      Serial.println(id);
      digitalWrite(6, HIGH);
      delay(100);
      digitalWrite(6, LOW);
      delay(50);
      digitalWrite(6, HIGH);
      delay(100);
      digitalWrite(6, LOW);
      digitalWrite(3, LOW);
      digitalWrite(6, HIGH);
      for(pos = 160; pos >= 110; pos -= 4)
      {
       myservo.write(pos);
       delay(15);
      }
      fps.SetLED(false);
      delay(10000);
      for(pos = 110; pos <= 160; pos += 4)
      {
        myservo.write(pos);
       delay(15);
      }
      digitalWrite(6, LOW);
      fps.SetLED(true);
    }
    else
    {
      Serial.println("Error, User Not Recognized");
      fps.SetLED(false);
      delay(100);
      fps.SetLED(true);
      delay(100);
      fps.SetLED(false);
      delay(100);
      fps.SetLED(true);
      delay(100);
      digitalWrite(3, LOW);
      fps.SetLED(false);
      delay(5000);
      fps.SetLED(true);
    }
  }
  else
  {
    //Serial.println("");
  }
  delay(1000);
}


  
       
  

      

