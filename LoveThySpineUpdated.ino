#include <Adafruit_CircuitPlayground.h>

/*
  THE ACCELEROMETER AT REST RECORDS A VALUE OF 1G, OR 9.8 m/s^2
  ACCELERATION IN ANY DIRECTION IS REFLECTED IN THE CONCURRENT VALUE
*/

void setup()
{
  CircuitPlayground.begin();
}


void loop()
{

  bool slideSwitch = CircuitPlayground.slideSwitch(); 

  double motionZ = CircuitPlayground.motionZ(); // don't want it global, it's a constantly changing value

  if (slideSwitch == 0)
  {
    if (abs(motionZ) > 3) //if person moves at least '3 units' forward or back
    {
      for (int led = 0; led <= 9; led++)
      {
        CircuitPlayground.setPixelColor(led, 255, 0, 0); //all leds light up red
      }

      /*I FIGURED OUT THAT PLAYING THIS FREQUENCY ON THIS KIND OF SPEAKER FOR THIS DURATION
        WILL OUTPUT A SOUND SIMILAR TO 'TSK TSK',
        ...AND MUCH PREFER THIS TO AN ANNOYING CHIRP. IT IS LITERALLY A LOW FREQUENCY VIBRATION
      */
      CircuitPlayground.playTone(27.5, 100); //play very low A
    }

    if (abs(motionZ) < 3) //if person is within '3 units' of proper posture
    {
      CircuitPlayground.clearPixels(); //clear all LEDs
    }

    Serial.println(motionZ); //print out value for motionZ, bending forwards or backwards
    delay(250);
  }

  else if (slideSwitch == 1) //if the slide switch is to the left
  {
    CircuitPlayground.clearPixels(); //turn off all LEDs so as to not annoy wearer
    CircuitPlayground.redLED(HIGH);  //turn on only LED at pin D13, to show that the switch is to the left
  }






  //bool rButton = CircuitPlayground.rightButton();
  //bool lButton = CircuitPlayground.leftButton();
  //INSERT ON/OFF SWITCH, AND SLIDESWITCH possibly

}
