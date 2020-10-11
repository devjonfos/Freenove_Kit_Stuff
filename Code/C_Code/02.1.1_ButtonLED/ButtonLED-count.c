/**********************************************************************
* Filename    : ButtonLED-count.c
* Description : Control LED by button press.
*               Added TRUE/FALSE logic to toggle terminal message
*               Added code to count button presses
* Authors     : www.freenove.com and
*               Jon Foster (jonfos@devjonfos.net)
* License     : CC BY-NC-SA 3.0
* Modification: 11-Oct-2020
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>

#define ledPin    0    //define the ledPin
#define buttonPin 1    //define the buttonPin

static unsigned int buttonCount = 0;

// Catch the CTRL-C interrupt and print button count
void interruptHandler(int signal)
{
  printf("Caught break: Button count: %d\n", buttonCount);

  exit(0);
}

int main(void)
{
  bool buttonPressed = false;

  signal(SIGINT, interruptHandler); //Catch the CTRL-C

  printf("Program is starting ... \n");
  
  wiringPiSetup(); //Initialize wiringPi 
  
  pinMode(ledPin, OUTPUT);   //Set ledPin to output
  pinMode(buttonPin, INPUT); //Set buttonPin to input

  pullUpDnControl(buttonPin, PUD_UP); //pull up to HIGH level

  //Infinite loop; CTRL-C to stop
  while(true)
  {
    //The terminal message is only printed when the 
    //button transitions because of the buttonPressed
    //logic which acts as a toggle.

    if(digitalRead(buttonPin) == LOW && !buttonPressed)
    {
      buttonPressed = true;
      buttonCount += 1;
      digitalWrite(ledPin, HIGH);
      printf("Button is pressed, LED turned on >>>\n");
    }

    if(digitalRead(buttonPin) == HIGH && buttonPressed)
    {
      buttonPressed = false;
      digitalWrite(ledPin, LOW); 
      printf("Button is released, LED turned off <<<\n");
    }
  }
}

