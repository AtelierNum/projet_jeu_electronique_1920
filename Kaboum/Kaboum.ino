/////////K A B O U M///////////////
//E D N A//////////////////////////
//////////////// J U L I E T T E///
////P A U L////////////////////////


////////LIBRAIRIE/////////////////
#include "avdweb_VirtualDelay.h"
#include <Arduino.h>
#include <TM1637Display.h>
////////-----------------//////////

////VARIABLE DELAY///
VirtualDelay delay1;
////---------------////

////DETERMINATION PIN BOUTON JOUEUR 1///////
int pinBoutonRJ1 = 8;
int pinBoutonVJ1 = 10;
////---------------------////////////

////DETERMINATION PIN BOUTON JOUEUR 2///////
int pinBoutonRJ2 = 11;
int pinBoutonVJ2 = 12;
////---------------------////////////

///DEF VARIABLE BOUTON////
//RJ1 = bouton rouge Joueur 1
//VJ1 = bouton vert Joueur1 1
//RJ2 = bouton rouge Joueur 2
//VJ2 = bouton vert Joueur 2

//VARIABLE VRAI OU FAUX BOUTON///
boolean etatBoutonRJ1;
boolean etatBoutonVJ1;

boolean etatBoutonRJ2;
boolean etatBoutonVJ2;
//--------------------------//


///VARIABLE VRAI OU FAUX EFFET LED CHENILLARD/////
boolean chenillardRougeP1 = false;
boolean chenillardRougeP2 = false;
boolean chenillardVertP1 = false;
boolean chenillardVertP2 = false;
//---------------------------------///

//VARIABLE SCORE//
int scorebase = 5; //score de base
int scoreP1 = scorebase; //score joueur 1 de base
int scoreP2 = scorebase; //score joueur 1 de base
//---------------///

//LIBRAIRIE ET VARIABLE NEOPIXEL BANDE LED///
#include <Adafruit_NeoPixel.h>
#define PIN 9 //PIN CONNECTION BANDE LED
//------------------//////

//DEFINIR PIN CONNECTION AFFICHEUR SCORE//

//afficheur 1
#define CLK1 2
#define DIO1 3
TM1637Display display1(CLK1, DIO1);

//afficheur 2
#define CLK2 6
#define DIO2 5
TM1637Display display2(CLK2, DIO2);
//-------------------------//


//DECLARATION BANDE LED//
Adafruit_NeoPixel strip = Adafruit_NeoPixel(92, 9, NEO_GRB + NEO_KHZ800);
//------------------//


//DECLARATION VARIABLE LED VERTE//
int i1v = 0;
int i2v = 92;
//--------------------///

//DECLARATION VARIABLE LED ROUGE//
int i1r = 0;
int i2r = 92;
//--------------------//


unsigned long previousMicros = 0;        // stockera info la dernière fois que le LED a été mis à jour
// constants won't change:
const long interval = 10;           // interval clignottement

long dernier_bouton_pressed = 0;


void setup() {

  strip.begin();// Initialise les LED !!!BIEN BRANCHER LA BANDE LED DANS LE SENS DES FLECHES!!!!
  strip.show(); // Initialise toute les led à 'off'

  //OUVRIR PIN BOUTON//
  pinMode(pinBoutonRJ1, INPUT);
  pinMode(pinBoutonVJ1, INPUT);
  pinMode(pinBoutonRJ2, INPUT);
  pinMode(pinBoutonVJ2, INPUT);
  //-----------------//


  Serial.begin(9600); // demarrer une communication serie

  //ACTIVER LUMINOSITE AFFICHEUR//
  display1.setBrightness(0x0f);
  display2.setBrightness(0x0f);
  //----------------------------//

}

void loop() {

  // gestion des boutons et enclenchement des action via des booléens
  etatBoutonRJ1 = digitalRead(pinBoutonRJ1);
  etatBoutonVJ1 = digitalRead(pinBoutonVJ1);
  etatBoutonRJ2 = digitalRead(pinBoutonRJ2);
  etatBoutonVJ2 = digitalRead(pinBoutonVJ2);

  // Personne n'a appuyé sur un bouton depuis x secondes, la partie se reset
  if (etatBoutonRJ1 || etatBoutonVJ1 || etatBoutonRJ2 || etatBoutonVJ2) {
    dernier_bouton_pressed = millis();
  }
  if ( (millis() - dernier_bouton_pressed) > 20000) {
    reinitialiser_scores();
  }




  // gestion  du timing, delay virtuel
  unsigned long currentMicros = millis();

  if (currentMicros - previousMicros >= interval) {
    // save the last time you blinked the LED
    previousMicros = currentMicros;



    //CONDITION GAIN DE SCORE//
    if (chenillardVertP1 == true) {
      i1v++;
    }
    if (chenillardVertP2 == true) {
      i2v--;
    }

    if (chenillardRougeP1 == true) {
      i1r++;
    }
    if (chenillardRougeP2 == true) {
      i2r--;
    }
  }

  //-------------------//

  //couleur des LEDS selon les boutons activés//
  chenillard(i1v, i2v, 0, 255, 0);
  chenillard(i1r, i2r, 255, 0, 0);
  //----------------------//


  // gestion de l'affichage//
  display1.showNumberDec(scoreP1);
  display2.showNumberDec(scoreP2);
  //-----------------------//

  strip.clear();

  // rencontre des deux chennillards
  if (i1v <= i2v + 1 && i1v >= i2v - 1) {
    Serial.println("boom");

    //CONDITION GAIN DE SCORE VERT//
    if (i1v < 40) {
      scoreP1 = scoreP1 - (40 - i1v);
    }
    if (i1v > 92 - 40) {
      scoreP2 = scoreP2 + ((92 - i1v) - 40) ;
    }



    i1v = 0;
    i2v = 92;

    chenillardVertP1 = false;
    chenillardVertP2 = false;
    //affichage_scores();
    strip.clear();
  }

  // si un de deux chenillard arrive au bout
  if (i1v > 92) {
    i1v = 0;
    chenillardVertP1 = false;
  }
  if (i2v < 0) {
    i2v = 92;
    chenillardVertP2 = false;

  }

  //------------------------//

  //CONDITION GAIN DE SCORE ROUGE//
  if (i1r <= i2r + 1 && i1r >= i2r - 1) {
    Serial.println("boom");

    if (i1r < 40) {
      scoreP1 = scoreP1 - (1 - i1r);
    }
    if (i1r > 92 - 40) {
      scoreP2 = scoreP2 + ((92 - i1r) - 40) ;
    }

    i1r = 0;
    i2r = 92;

    chenillardRougeP1 = false;
    chenillardRougeP2 = false;
    //affichage_scores();
    strip.clear();
  }

  // si un de deux chenillard arrive au bout
  if (i1r > 92) {
    i1r = 0;
    chenillardRougeP1 = false;
  }

  if (i2r < 0) {
    i2r = 92;
    chenillardRougeP2 = false;
  }


  //CONDITION SI UN DES JOUEURS ARRIVENT A UN EN DESSOUS DE 0//
  if (scoreP2 < 0) { //si le score est inferieur à 0 alors...
    winJ1(92 , 255, 0, 0);
    reinitialiser_scores();
  }

  if (scoreP1 < 0) {
    winJ2(92 , 255, 0, 0);
    reinitialiser_scores();
  }
  //------------------------------------------//



  //CONDITIONS ACTIVATION CHENILLARD SELON LE BOUTON ACTIVE//
  if (etatBoutonRJ1 == 1) {
    chenillardRougeP1 = true;
  }

  if (etatBoutonVJ1 == 1) {
    chenillardVertP1 = true;
  }

  if (etatBoutonRJ2 == 1) {
    chenillardRougeP2 = true;
  }

  if (etatBoutonVJ2 == 1) {
    chenillardVertP2 = true;
  }
  //------------------------//


}

//FONCTION CHENILLARD LED//
void chenillard( int index1, int index2, int r, int v, int b) {
  strip.setPixelColor(index1, r, v, b);
  strip.setPixelColor(index2, r, v, b);
  strip.show();
}
//-----------------------///


//FONCTION LED SI JOUEUR 2 GAGNE///
void winJ2(int temps, int r, int v, int b) {
  for (int i = 0 ; i < 20 ; i++) {
    strip.setPixelColor(i, r, v, b);
  }
  strip.show();
  delay(2000);
}
//------------------------///


//FONCTION LED SI JOUEUR 1 GAGNE//
void winJ1(int temps, int r, int v, int b) {
  for (int i = 00 ; i < 92 ; i++) {    //toutes les LEDS vont s'allumer en rouge
    strip.setPixelColor(i, r, v, b);
  }
  strip.show();
  delay(2000);
}
//-----------------------///


//FONCTION REINITIALISER PARTIE//
void reinitialiser_scores() {
  scoreP1 = scorebase;
  scoreP2 = scorebase;
  chenillardVertP1 = false;
  chenillardVertP2 = false;
  chenillardRougeP1 = false;
  chenillardRougeP2 = false;
  i1v = 0;
  i2v = 92;
  i1r = 0;
  i2r = 92;
}
//-------------------------------//

/*
  void affichage_scores() {
  display1.showNumberDec(scoreP1);
  display2.showNumberDec(scoreP2);
  }*/
