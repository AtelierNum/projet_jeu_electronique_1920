// Inclure bibliothèque Adafruit NeoPixel : https://github.com/adafruit/Adafruit_NeoPixel
#include <Adafruit_NeoPixel.h>

// Inclure bibliothèque Virtual Delay : https://github.com/avandalen/VirtualDelay
#include "avdweb_VirtualDelay.h"

// Inclure bibliothèque Arduino :  
#include <Arduino.h>

// Inclure bibliothèque SPI.h et MFRC522.h
#include "SPI.h"
#include "MFRC522.h"

// ANNEAUX DE LED
#define PIN        6 //
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int npixelAllume = 0;

// SYTEME RFID
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // On déclare l'utilisation du module RFID
MFRC522::MIFARE_Key key;

// LED UV
#define led 5

// BUZZER
#define buzzer  2

// On stocke les identifiants des tags/stickers RFID dans un tableau
//C'est la liste que vous devrez changer en mettant la liste de puces que vous aurez généré à l'aide du programme : "generateur_de_tableau_de_puces_RFID.ino"
char *myStrings[] = {
"EC:38:6D:31", "FC:1A:6D:31", "4C:F2:6C:31", "0C:C2:6C:31", "1C:8F:6C:31", "CC:5A:6C:31", "3C:1B:6C:31", "5C:E7:6B:31", "2C:A3:6A:31", "9C:69:6D:31", 
"CC:8C:6D:31", "AC:41:6D:31", "FC:18:6D:31", "AC:45:6D:31", "1C:65:6D:31",  "FC:60:69:31", "CC:0D:69:31", "BC:C9:68:31", "BC:C3:68:31", "1C:3A:6D:31", 
"5C:6A:6D:31", "DC:38:7C:D6", "BC:C6:7C:D6", "7C:3D:67:31", "2C:E7:66:31", "AC:37:67:31", "0C:D2:67:31", "AC:28:68:31", "BC:6E:68:31", "7C:6F:6D:31", 
"2C:DD:6D:31", "DC:AF:7B:D6", "3C:34:7C:D6", "4C:CC:7C:D6", "5C:CC:7C:D6", "CC:C6:7C:D6", "8C:36:7C:D6", "FC:B2:7B:D6", "EC:AC:7B:D6", "0C:42:6D:31", 
"1C:D4:6D:31", "6C:3F:82:D6", "9C:46:82:D6", "0C:FC:82:D6", "EC:4E:84:D6", "6C:53:82:D6", "EC:AB:81:D6", "FC:9B:81:D6", "AC:53:82:D6", "7C:63:6D:31", 
"1C:CE:6D:31", "9C:95:83:D6", "7C:59:82:D6", "AC:E7:82:D6", "6C:39:84:D6", "3C:3F:82:D6", "2C:9F:81:D6", "EC:AF:81:D6", "6C:E7:82:D6", "7C:69:6D:31", 
"FC:AC:6D:31", "7C:A7:83:D6", "4C:ED:82:D6", "5C:AC:81:D6", "EC:53:82:D6", "DC:A3:83:D6", "2C:43:82:D6", "7C:57:82:D6", "CC:FB:82:D6", "EC:91:6D:31",  
};

//
int PG = 0; // On défini une variable "Puce Goal" avec une valeur de départ = 0
int lt = 5; // On défini une variable "largeur triangle" avec une valeur de départ = 5
int ht = 5; // On défini une variable "hauteur traingle" avec une valeur de départ = 5

double dist = 8; // On défini une variable "distance" avce une valeur de départ = 8
int del = 500; // On défini une variable "delay" avec une valeur de déprat = 500
int incr = 0; // On défini une variable "incrémentation" avec une valeur de départ = 0
int intensite = 255; // On défini une vavriable qui correspond à l'intensité lumineuse des leds UV, avec la valeur maximale de départ
bool b; // On défini une variable boolean

void setup() {

  // On précise pin buzzer et pin des leds UV comme des sorties
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);



  Serial.begin(9600); // On ouvre une connexion série via le câble USB pour récuperer des valeurs dans notre ordinateur
  SPI.begin(); // On initialise la communication SPI
  rfid.PCD_Init(); // On initialise le module RFID


  Serial.println("Je suis prêt à recvoir une puce...");
  pixels.begin();
  randomSeed(analogRead(A0));

}

void loop() {

  static VirtualDelay singleDelay;
  static VirtualDelay delayLum;

  delayLum.start(100); // delay virtuel pour ralentir intensite qui baisse
  if (delayLum.elapsed()) {
    intensite = intensite - 1;
    intensite = constrain(intensite, 0, 255);
    //Serial.println(intensite);
  }
  analogWrite(led, intensite); 


  singleDelay.start(del); //
  

  if (singleDelay.elapsed()) {
    incr++;
    if (incr % 2 == 0) {
      tone(buzzer, 100); // On envoie une fréquence comme suit tone(pin, frequency)
      Serial.println("là");
    } else {
      noTone(buzzer);
    }
  }
  
// On allume une led de l'anneau de leds quand une puce est trouvée, grâce à npixelAllume
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
    if (i < npixelAllume) {

      pixels.setPixelColor(i, pixels.Color(1, 1, 1)); // On allume la led RGB
    }
    else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Sinon on met en noir donc éteint
    }
    pixels.show();   // Send the updated pixel colors to the hardware.
  }

Pour mieux comprendre le fonctionnement le branchement et la programmation d'un lecteur RFID, voici https://randomnerdtutorials.com/security-access-using-mfrc522-rfid-reader-with-arduino/

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  strID.toUpperCase();
  Serial.print("Tap card key: ");
  Serial.println(strID);

  // Si "PG" est supérieur à 0, donc si on trouve une puce (voir le bo
  if (strID.indexOf(myStrings[PG]) >= 0) {
    
    Serial.println("**************");
    Serial.println("Bonjour");
    
    // Alors on augmente l'intensité de 50 des leds UV (led)
    intensite = intensite + 50;

// On contraint cette valeur de intensité entre 0 et 255 le maximum d'intensité lumineuse possible 
    intensite = constrain(intensite, 0, 255);

    Serial.println("**************");

    PG = random(0, 70); // On redéfinit le nouvel endroit de PG aléatoirement sur toute les puces présentent ici il y en a 70
    noTone(buzzer); // On éteint le buzzer
    npixelAllume += 1; // Et on allume une led de plus sur l'anneau de leds

  } else {
    Si on ne trouve pas de puce : 
    Serial.println("**********");
    Serial.println("En revoir");

    Serial.println("**********");


    // Boucle qui permet de déterminer le numéro de la "PAC", la puce actuellement captée
    for (int PAC = 0; PAC < 100 ; PAC++)
    {
      if (strID.indexOf(myStrings[PAC]) >= 0) {
        Serial.println("le numéro de la puce actuellement captée est :");
        Serial.println(PAC);
        Serial.println("et le numéro de PG est :");
        Serial.println(PG);

        // DÉBUT formule calcul distance
        //calcul des coordonnées de PAC
        /*
          Les formules suivantes permettent de calculer la position (x ; y)
          de la PAC (Puce actuellement captée) si elle a bien été enregistrée dans le tableau "char *myStrings[]" les formules utilisent leur numéro d'apparition
          dans le tableau pour obtenir leur coordonnées. 
        */        

        int xPAC = PAC % 10;
        int yPAC = int(PAC / 10);
        //calcul des coordonnées de PG
        int xPG = PG % 10;
        int yPG = int(PG / 10);

        /*
         Pour calculer la distance entre les deux puces (PAC et PG), nous utilisons le théorème de pytagore qui énonce que le l'hypoténuse 
         d'un triangle à angle droit est égal la somme des deux autres côtés du triangle au carré. 
         L'idée est que PAC et PG sont les sommets d'un triangle à angle droit
         */
         //cacul de la hauteur du triangle
         
        if (xPAC > xPG)
        {
          ht = xPAC - xPG;
        } else {
          ht = xPG - xPAC;
        }
        //calcul de la largeur du triangle
        if (yPAC > yPG)
        {
          lt = yPAC - yPG;
        } else {
          lt = yPG - yPAC;
        }


        // Calcul de la distance entre les deux puces avec les variables 
        dist = sqrt(ht * ht + lt * lt); //voici la formule qui permet de donner la distance entre les deux points, la fonction sqrt() permet d'extraire la racine d'un nombre
        Serial.println("la distance entre les deux points est égale à :");
        Serial.println(dist);
        // FIN formule calcul distance

        del = map(dist , 0, 7, 1, 100);
        break;

      }

    }

  }

}
