#include <FastLED.h>
#include <EasyButton.h>


int r = 252;
int g = 0;
int b = 0;
int pinBouton = 8;
int buzzer = 9;

#define LED_PIN     7
#define NUM_LEDS   16

CRGB leds[NUM_LEDS];

int s = 0;


EasyButton button(pinBouton);

boolean updateLights = true;
boolean pupdateLights = true;


void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  for (int i = 8; i >= 0; i--)
  {
    leds[i] = CRGB ( r, g, b);
    leds[3 - i] = CRGB (r, g, b );
    //delay(40);

  }
  FastLED.show();
  Serial.begin(9600);
  pinMode(pinBouton, INPUT);
  button.begin();
  // Add the callback function to be called when the button is pressed.
  button.onPressed(onPressed);

}

void onPressed() {
  updateLights = !updateLights;
  // goal1 = npix;
  //  if (i = 5) {
  //    tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
  //    delay(500);
  //    tone(buzzer, 2000); // You can also use noTone() to stop the sound it takes 1 parametere which is the buzzer pin
  //    delay(500);
  //  }

}
void loop() {


  button.read();

  s = analogRead(A0);
  // Serial.println(s);

  //  if((s>=535)&&(s<=540))
  //  {
  //    leds[8]=CRGB (20, 135, 217);
  //    leds[9]=CRGB (20, 135, 217);
  //  }
  //  else if((s>=530)&&(s<=535))
  //   {
  //     leds[8]=CRGB (20, 217, 30);
  //    leds[9]=CRGB (20, 217, 30);
  //   }
  //  else
  //  {
  //     leds[8] = CRGB ( r,g,b);
  //     leds[9] = CRGB ( r,g,b);
  //  }







  if (updateLights == true) {
    int npix = map(s, 0, 800, 0 , NUM_LEDS);
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      if (i < npix) leds[i] = CRGB ( 255, 0, 0);
      else leds[i] = CRGB ( 255, 97, 0);

    }
    FastLED.show();
  } else {
    // int goal = 0;
    if (pupdateLights != updateLights) {
      int goal = map(analogRead(0), 0, 800, 0 , NUM_LEDS);

      Serial.println("button just pressed");
      Serial.println(goal);

      if (goal >= 14 || goal == 15 || goal == 13) {
        //gagne = true;
        Serial.println("gagne");
        tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
        delay(100);
        tone(buzzer, 2000); // You can also use noTone() to stop the sound it takes 1 parametere which is the buzzer pin
        delay(100);
        tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
        delay(100);
        tone(buzzer, 2000); // You can also use noTone() to stop the sound it takes 1 parametere which is the buzzer pin
        delay(100);
        tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
        delay(500);
        tone(buzzer, 2000); // You can also use noTone() to stop the sound it takes 1 parametere which is the buzzer pin
        delay(500);
        noTone(buzzer);
        Serial.println(goal);
      }
      else {
        Serial.println("perdu");
        noTone(buzzer);
      }



    }


  }

  pupdateLights = updateLights;





  //delay(30);
}
