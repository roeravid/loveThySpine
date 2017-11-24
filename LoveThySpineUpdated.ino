#include <Adafruit_CircuitPlayground.h>

/*
  THE ACCELEROMETER AT REST RECORDS A VALUE OF 1G, OR 9.8 m/s^2
  ACCELERATION IN ANY DIRECTION IS REFLECTED IN THE CONCURRENT VALUE
*/

   double wahFreq[]={261.626/2.0, 246.942/2.0, 233.082/2.0, 220.000/2.0};
   int wahDuration[]={500, 500, 500, 1250};

void setup()
{
  CircuitPlayground.begin();
}


void loop()
{

  bool slideSwitch = CircuitPlayground.slideSwitch(); 

  double motionX = CircuitPlayground.motionX(); 

  double motionZ = CircuitPlayground.motionZ(); // don't want it global, it's a constantly changing value

  if (slideSwitch == 0)
  {
    CircuitPlayground.redLED(LOW);  //turn off LED at pin D13, to show that the switch is to the left
    
    if (abs(motionZ) < 3) //if person is within '3 units' of proper posture
    {
      for (int led = 0; led <= 9; led++)
      {
        CircuitPlayground.setPixelColor(led, 0, 255, 0); //all leds light up green
      }
    }
//=====================================================================================================    
    if (abs(motionZ) >= 3 && abs(motionZ) <= 5) //if person moves at least '3 units' forward or back
    {
      for (int led = 0; led <= 4; led++)
      {
        CircuitPlayground.setPixelColor(led, 255, 0, 0); //all leds light up red
      }
      
      /*I FIGURED OUT THAT PLAYING THIS FREQUENCY ON THIS KIND OF SPEAKER FOR THIS DURATION
        WILL OUTPUT A SOUND SIMILAR TO 'TSK TSK',
        ...AND MUCH PREFER THIS TO AN ANNOYING CHIRP. IT IS LITERALLY A LOW FREQUENCY VIBRATION
      */
      CircuitPlayground.playTone(27.5, 100); //play very low A
      /*for(int blk=2500; blk>0; blk--){
        CircuitPlayground.clearPixels();
      }*/
    }

//===================================================================================================
    if (abs(motionZ) > 5) //if person moves at least '5 units' forward or back
    {
      for (int led = 0; led <= 9; led++)
      {
        CircuitPlayground.setPixelColor(led, 255, 0, 0); //all leds light up red
      }

      for(int x = 0; x < 4; x++)
      {
        CircuitPlayground.playTone(wahFreq[x],wahDuration[x]);
      }
     }


//=================================================================    
  Serial.println("X\tZ");
  Serial.print(motionX);
  Serial.print("\t");
  Serial.println(motionZ);
  }

  else if (slideSwitch == 1) //if the slide switch is to the left
  {
    CircuitPlayground.clearPixels(); //turn off all LEDs so as to not annoy wearer
    CircuitPlayground.redLED(HIGH);  //turn on only LED at pin D13, to show that the switch is to the left
  }

}
