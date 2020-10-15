/**********************************************************************
* Filename    : LightWater-break.c
* Description : Use LEDBar Graph(10 LED) 
*               Added code to catch CTRL-C break and reset LEDBar
* Authors     : www.freenove.com and
*               Jon Foster (jonfos@devjonfos.net)
* License     : CC BY-NC-SA 3.0
* Modification: 14-Oct-2020
*
* Note - If wired according to the Tutorial, the LEDs turn ON
*        when the GPIO output is sent LOW in the program. 
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>

#define ledCounts 10
int pins[ledCounts] = {0,1,2,3,4,5,6,8,9,10}; //use 'gpio readall' for pinouts

// Reset LED bar
void resetLEDbar(void)
{
  int i;

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
}

// Catch the CTRL-C interrupt and reset LED bar
void interruptHandler(int signal)
{
  printf("Caught break: Resetting LED Bar\n");

  resetLEDbar();

  exit(0);
}

int main(void)
{
  int i;

  signal(SIGINT, interruptHandler); //Catch the CTRL-C

  printf("Program is starting ... \n");

  resetLEDbar();

/* Duplicated code in reset function
  wiringPiSetup(); //Initialize wiringPi.
  
  for(i=0;i<ledCounts;i++) //Set pinMode for all led pins to output
  {
    pinMode(pins[i], OUTPUT);    
  }
*/

  // Infinite loop sequencing LEDs
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

