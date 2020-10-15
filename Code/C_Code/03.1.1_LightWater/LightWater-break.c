/**********************************************************************
* Filename    : LightWater-break.c
* Description : Use LEDBar Graph(10 LED) 
*               Added code to reset LEDBar
* Authors     : www.freenove.com and
*               Jon Foster (jonfos@devjonfos.net)
* License     : CC BY-NC-SA 3.0
* Modification: 14-Oct-2020
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>

#define ledCounts 10
int pins[ledCounts] = {0,1,2,3,4,5,6,8,9,10};

// Catch the CTRL-C interrupt and reset LED bar
void interruptHandler(int signal)
{
  int i;
  printf("Caught break: Resetting LED Bar\n");

  wiringPiSetup(); //Initialize wiringPi.

  for(i=0;i<ledCounts;i++) //Set pinMode output; pins on
  {
    pinMode(pins[i], OUTPUT);    
    digitalWrite(pins[i],LOW);
  }

  delay(300);

  for(i=0;i<ledCounts;i++) //Set pins off
  {
    digitalWrite(pins[i],HIGH);
  }

  exit(0);
}

int main(void)
{
  int i;

  signal(SIGINT, interruptHandler); //Catch the CTRL-C

  printf("Program is starting ... \n");

  wiringPiSetup(); //Initialize wiringPi.
  
  for(i=0;i<ledCounts;i++) //Set pinMode for all led pins to output
  {
    pinMode(pins[i], OUTPUT);    
  }

  while(true)
  {
    for(i=0;i<ledCounts;i++) //Move led(on) from left to right
    {
      digitalWrite(pins[i],LOW);
      delay(100);
      digitalWrite(pins[i],HIGH);
    }

    for(i=ledCounts-1;i>-1;i--) //Move led(on) from right to left
    {
      digitalWrite(pins[i],LOW);
      delay(100);
      digitalWrite(pins[i],HIGH);
    }
  }
}

