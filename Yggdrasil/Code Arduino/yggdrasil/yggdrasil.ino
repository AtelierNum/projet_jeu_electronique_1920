/********************************INCLURE BIBLIOTHEQUE*************************************/

//SevenSegmentTM1637
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"


//Adafruit_MPR121.h
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif


//avdweb_VirtualDelay.h
#include "avdweb_VirtualDelay.h"
#include <Arduino.h>


//IRremote.h
#include <IRremote.h>


//Servo.h
#include <Servo.h>

/********************************PARAMETRES*************************************/

/*LED*/
int ledPin = 7;


/*MPR121(sensor)*/
Adafruit_MPR121 cap = Adafruit_MPR121();

// Garder la trace de la dernière pin touchée
uint16_t lasttouched = 0;
uint16_t currtouched = 0;


/*CHRONOMETRE*/
const byte PIN_CLK = 3;   // definir CLK pin
const byte PIN_DIO = 2;   // definir DIO pin

SevenSegmentExtended
display(PIN_CLK, PIN_DIO);

VirtualDelay delay1;
int incr = 0;
bool timerStarted = false;
int score_modifieur = 0;


/*INFRAROUGE*/
#define RECV_PIN 11


/*SERVOMOTEUR*/
Servo myservo; //servomoteur rotation structure
Servo myservopiege; //servomoteur piège

int pos = 0;

String mode = "" ;
String valueColor = "" ;
String hexIr = "" ;
IRrecv irrecv(RECV_PIN);
decode_results results;

long declenchement_moteur_structure = 0;
int cible_moteur_structure = 90; // moteur au point 0


/********************************SETUP*************************************/
void setup() {

  /*SERVOMOTEURS*/

  Serial.begin(9600);
  irrecv.enableIRIn(); // Recevoir le signal
  pinMode(11, INPUT);

  myservo.attach(9);  // attacher le servomoteur rotation structure au Pin digital 9
  myservopiege.attach(5); //attacher le servomoteur piège au Pin digital 5


  /*LED*/
  pinMode(ledPin, OUTPUT);


  /*CHRONOMETRE*/
  Serial.begin(9600);         // initialiser la connexion 9600 baud
  display.begin();            // initialiser l'affichage
  display.setBacklight(50);  // controler la luminosité 50 %
  display.print("INIT");    // afficher "INIT"
  delay(1000);                // attendre 1000 ms = 1s
  display.clear();

  /*CAPTEUR MPR121*/
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }

  Serial.println("MPR121 found!");

};


/********************************LOOP*************************************/

void loop() {

  /*CHRONOMETRE*/

  //création du timer avec un delay d'une seconde
  if (timerStarted) {
    delay1.start(1000);
    if (delay1.elapsed()) {
      incr = incr + 1 ;
      Serial.println(incr); //afficher le temps
    }
  }

  //création du malus de temps si structure touchée
  incr = incr + score_modifieur;
  int minutes = (incr) / 60;
  int secondes = (incr) % 60;
  display.printTime(minutes, secondes, true);

  /*CAPTEUR SENS*/

  // Get the currently touched pads
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {  //Pour les capteurs de sens allant de 0 à 12

    //si il "est" touché et "n'est pas" touché avant : message d'alerte
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
      Serial.print(i); Serial.println(" touched");

      // Si le sensor 1 est touché alors le timer est égale à 0
      // Début de la partie
      if (i == 1) {
        incr = 0;
        timerStarted = false;
      }

      // Si le sensor 2 est touché alors le timer s'arrete
      // Fin de la partie
      if (i == 2) {
        timerStarted = false;
      }

      // Si les sensors sup ou égal à 3 sont touchés alors on rajoute 4 secondes au timer
      if (i >= 3) {
        score_modifieur = 4;
        digitalWrite(ledPin, HIGH); //Led s'allume
      }
    }


    // si il "est" touché et maintenant "n'est pas" touché alors message d'alerte
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");

      // Si le sensor 1 n'est pas touché alors le timer se lance (à partir de 0)
      if (i == 1) {
        incr = 0;
        timerStarted = true;
      }

      // Si les sensors sup ou égal à 3 ne sont pas touché alors rien ne se passe
      if (i >= 3) {
        score_modifieur = 0;
        digitalWrite(ledPin, LOW); //Led éteinte
      }
    }
  }

  // reset our state
  lasttouched = currtouched;


  /*SERVOMOTEUR ROTATION STRUCTURE*/

  // Réception de la télécommande infrarouge
  if (irrecv.decode(&results))
  {
    hexIr = String(results.value, HEX);
    Serial.print("ValueIr ");
    Serial.println(hexIr);

    //Si bouton de droite touché, servomoteur est déclanché
    if (hexIr == "ffc23d") {
      Serial.println("droite");
      declenchement_moteur_structure = millis();
      cible_moteur_structure = 92;
    }

    //Si bouton de gauche touché, servomoteur est déclanché
    if (hexIr == "ff22dd") {
      Serial.println("gauche");
      declenchement_moteur_structure = millis();
      cible_moteur_structure = 87;
    }
    irrecv.resume();
  }

  // action sur le servomoteur structure
  //Durant 3 secondes, le servomoeteur passe de la position 90 à 92 (droite) ou 87 (gauche)
  if (millis() - declenchement_moteur_structure < 3000) {
    myservo.write(cible_moteur_structure);
  } else { // Puis revient à son point de départ : position 90
    myservo.write(90);
  }

  /*SERVOMOTEUR PIEGE*/
  //servomoteur fait des vas et vient continuellement 
  myservopiege.write((float)sin(radians(millis() / 10)) * 30 + 20);

};
