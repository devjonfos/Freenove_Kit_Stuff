/**********************************************************************
* Filename    : Blink-break.c
* Description : Basic usage of GPIO. Blink LED 0 (#18).
*               Added catching break signal and turning off LED
* Authors     : www.freenove.com and
*               Jon Foster (jonfos@devjonfos.net)
* Modification: 9-Oct-2020
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// See http://wiringpi.com/pins/
#define  ledPin    0	//define the led pin number

// Catch the CTRL-C interrupt and turn LED off
void interruptHandler(int signal)
{
  wiringPiSetup();
	pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  printf("Caught break: LED now off\n");

  exit(0);
}

void main(void)
{	
	printf("Program is starting ... \n");
	
	wiringPiSetup();	                //Initialize wiringPi.

  signal(SIGINT, interruptHandler); //Catch the CTRL-C
	
	pinMode(ledPin, OUTPUT);          //Set the pin mode
	printf("Using pin%d\n",ledPin);	  //Output information on terminal

	while(1)
  {
		digitalWrite(ledPin, HIGH);     //Make GPIO output HIGH level
		printf("led turned on >>>\n");	//Output information on terminal
		delay(1000);						        //Wait for 1 second
		digitalWrite(ledPin, LOW);      //Make GPIO output LOW level
		printf("led turned off <<<\n");	//Output information on terminal
		delay(1000);						        //Wait for 1 second
	}
}

