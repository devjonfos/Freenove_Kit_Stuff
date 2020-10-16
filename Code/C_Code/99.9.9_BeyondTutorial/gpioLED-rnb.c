/**********************************************************************
*
* Filename: gpioLED-rnb.c
*
* Description: Rotate LEDs and Blink LEDs (rnb)
*              with GPIO low-state to activate (gpioL)
*              or GPIO high-state to activate (gpioH)
*
* Author: Jon Foster (jonfos@devjonfos.net)
*
* License: CC BY-NC-SA 4.0
*          https://creativecommons.org/licenses/by-nc-sa/4.0/
*
* Modification: 15-Oct-2020
*
* Compile: gcc -Wall gpioLED-rnb.c -o gpioLED-rnb -lwiringPi
*
* Usage: gpioLED-rnb <blinkDelay> <gpioL|gpioH>
*
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define numLEDs 10

// use 'gpio readall' for pinouts
// GPIO: 17,18,27,22,23,24,25,2(SDA),3(SCL),8(CE0)
int gpioPins[numLEDs] = {0,1,2,3,4,5,6,8,9,10};

// Initialize as 300
unsigned int blinkDelay = 300;

// Initialize as gpioL
bool setLOW = true;
bool setHIGH = false;

// Rotate LEDs
void rotateLEDs(void)
{
  int i;

  for( i=0; i<numLEDs; i++ )
  {
    digitalWrite(gpioPins[i], setLOW);
    delay(blinkDelay);
    digitalWrite(gpioPins[i], setHIGH);
  }
}

// Blink LEDs
void blinkLEDs(void)
{
  int i;

  for( i=0; i<numLEDs; i++ )
    digitalWrite(gpioPins[i], setLOW);

  delay(blinkDelay);

  for( i=0; i<numLEDs; i++ )
    digitalWrite(gpioPins[i], setHIGH);

  delay(blinkDelay);
}

// Reset LEDs
void resetLEDs(void)
{
  int i;

  wiringPiSetup(); // Initialize wiringPi.

  for( i=0; i<numLEDs; i++ ) // Set pinMode to output; all pins on
  {
    pinMode(gpioPins[i], OUTPUT);
    digitalWrite(gpioPins[i], setLOW);
  }

  delay(blinkDelay);

  for( i=0; i<numLEDs; i++) // All pins off
  {
    digitalWrite(gpioPins[i], setHIGH);
  }
}

// Catch the CTRL-C interrupt and reset the LEDs
void interruptHandler(int signal)
{
  printf("Caught break: Resetting LEDs\n");

  resetLEDs();

  exit(0);
}

// Check arguments passed in
void checkArguments(int argc, char *argv[])
{
  switch( argc )
  {
    case 1 :
      break;

    case 2 :
      if( strcmp(argv[1], "--help") == 0 )
      {
        printf("Usage: gpioLED-rnb <blinkDelay> <gpioL|gpioH>\n");
        exit(1);
      }

      blinkDelay = atoi(argv[1]);
      if( blinkDelay < 100 || blinkDelay > 1000 )
      {
        printf("Blink delay is out of range: %d\n", blinkDelay);
        printf("Argument range is 100 to 1000\n");
        printf("Setting blink delay to 300\n");
        blinkDelay = 300;
      }
      break;

    case 3 :
      blinkDelay = atoi(argv[1]);
      if( blinkDelay < 100 || blinkDelay > 1000 )
      {
        printf("Blink delay is out of range: %d\n", blinkDelay);
        printf("Argument 1 range is 100 to 1000\n");
        printf("Setting blink delay to 300\n");
        blinkDelay = 300;
      }

      if( strcmp(argv[2], "gpioL") == 0 )
      {
        setLOW = true;
        setHIGH = false;
      }
      else if( strcmp(argv[2], "gpioH") == 0 )
      {
        setLOW = false;
        setHIGH = true;
      }
      else
      {
        printf("Argument 2 is activate 'gpioL' for low-state or 'gpioH' for high-state\n");
        printf("Setting 'gpioL' for low-state to activate\n");
      }
      break;

    default :
      printf("Usage: gpioLED-rnb <blinkDelay> <gpioL|gpioH>\n");
      exit(1);
  }
}

int main(int argc, char *argv[])
{
  int i;

  checkArguments(argc, argv);

  signal(SIGINT, interruptHandler); // Catch the CTRL-C
  signal(SIGHUP, interruptHandler); // If process is backgrounded

  resetLEDs();

  while(true)
  {
    for( i=0; i<3; i++ )
      rotateLEDs();

    delay(blinkDelay*2);

    for( i=0; i<3; i++ )
      blinkLEDs();
  }
}

