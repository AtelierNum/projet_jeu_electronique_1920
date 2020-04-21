/*
 Ce code écrit les puces RFID captées avec
 une certaine nomanclature permettant de créer un tableau d'identifiants
 de puces RFID facilement

 1 - lancez le code, 
 2 - positionnez votre capteur au-dessus des puces dont
 vous voulez écrire les identifiants
 3 - Ouvrez le moniteur série pour observer les identifiants
 s'écrire tous seuls avec la nomanclature de la configuration
 d'un tableau
 4 - Il nous reste plus qu'à copier la liste d'identifiants
 */

/*
  bonne puce = tag : F4:29:05:6F
  mauvaise puce = tag : 8E:D3:24:A3
  mauvaise puce = tag : C0:8F:C8:49
*/

#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

//transformer les codes des cartes en array
char *myStrings[] = {"BC:AD:CA:31", "EC:D0:C8:31", "AC:2F:CB:31",
                     "1C:EA:C9:31", "1C:6A:C9:31", "3C:8C:CA:31", "3C:AB:C8:31",
                     "CC:47:C9:31", "1C:0B:CA:31"
                    };
int PG = 2; //PG signifie : "Puce Goal"

int lt = 5; //valeur blanche lt signifie "largeur triangle"
int ht = 5; //valeur blanche lt signifie "hauteur triangle"


void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(A0));

  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.println("I am waiting for card...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    //Serial.println(F("Your tag is not of type MIFARE Classic."));
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
  Serial.print('"');
  Serial.print(strID);
  Serial.print('"');
  Serial.print(", ");
  delay(3000);

  if (strID.indexOf(myStrings[PG]) >= 0) {  //put your own tap card key;
    //Serial.println("********************");
    //Serial.println("**Bonjour**");
    //Serial.println("********************");
    //digitalWrite(4, HIGH);
    //digitalWrite(3, LOW);
    PG = random(0, 2);
    // return;
  }
  else {
    //Serial.println("****************");
    //Serial.println("**En revoir**");
    //Serial.println("****************");

    for (int PAC = 0; PAC < 9 ; PAC++) //boucle qui permet de déterminer le numéro de la PAC (puce actuellement captée)
    {
      if (strID.indexOf(myStrings[PAC]) >= 0) {
         //Serial.println("le numéro de la puce actuellement captée est :");
         //Serial.println(PAC);
         //Serial.println("et le numéro de PG est :");
         //Serial.println(PG);

                  // DÉBUT formule calcul distance
                  //calcul des coordonnées de PAC
                    int xPAC = PAC%3;
                    int yPAC = int(PAC/3);
                    //calcul des coordonnées de PG
                    int xPG = PG%3;
                    int yPG = int(PG/3);
                    
                    //Serial.println(xPAC);
                    //Serial.println(yPAC);
                  
                    //Serial.println(xPG);
                    //Serial.println(yPG);
                  
                    //cacul de la hauteur du triangle
                    if (xPAC > xPG) 
                    {
                      ht = xPAC - xPG;
                      //Serial.println(ht);
                    } else {
                      ht = xPG - xPAC;
                      //Serial.println(ht);
                    }
                    //calcul de la largeur du triangle
                     if (yPAC > yPG) 
                    {
                      lt = yPAC - yPG;
                      //Serial.println(lt);
                    } else {
                      lt = yPG - yPAC;
                      //Serial.println(lt);
                    }
                  
                    //calcul de la distance entre les deux puces
                    int dist = sqrt(ht*ht+lt*lt);
                    //Serial.println("la distance entre les deux points est égale à :");
                    //Serial.println(dist);
                    // FIN formule calcul distance
      }
    }



    //digitalWrite(3, HIGH);
    //digitalWrite(4, LOW);
    //return;
  }

  // delay(5000);
  // digitalWrite(3, LOW);
  // digitalWrite(4, LOW);


}
