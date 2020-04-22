#include <Wire.h>               // appel de la bibliothèque Wire
#include <Adafruit_MPR121.h>    // appel de la bibliothèque MPR121

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

#define LED0        6       // definition des pin pour les leds et les vies
#define LED1        12
#define LED2        4
#define LED3       13
#define LED4        8
#define vie1        3
#define vie2        5
#define vie3        7

boolean etat_led[5];               // tableau pour led
boolean etat_bouton[5];           // tableau pour bouton

int zone_active;                  // zone à toucher
int vies = 4;                    // nombre de vie au début de la partie
int niveau = 1;                  // debut au niveau 1

boolean nouvelle_zone = true;    // la nouvelle zone est vrai

long prevMillis = 0;             // initialisation du temps
int led_delay = 5000;            // definition de la durer des niveaux
int led_delay1 = 4000;
int led_delay2 = 3000;
int led_delay3 = 2000;

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  // les led sont en digital
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  // initialisation du MPR121
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

}

void loop() {


  if (vies == 4) {                            // lorsque la variable vies est égale à 4 alors on lance l'animation du début et on diminue de 1 la valeur de la variable vie
    animedebut();
    vies--;
  }

  if (vies > 0) {                            // lorsque la variable vies est supérieur à 0 on lance la principe du jeu
    currtouched = cap.touched();
    if (nouvelle_zone) {                     // si la variable nouvelle zone est vérifiée alors choisir un nombre aléatoire de 0 à 4
      zone_active = random(5);
      Serial.print("nouvelle zone définie : ");
      Serial.println(zone_active);
      nouvelle_zone = false;                //Permet de sortir de la boucle et activer une nouvelle zone
    }

    // definition du fil à toucher avec le bouton
    etat_bouton[0] = (currtouched & _BV(0)) && !(lasttouched & _BV(0));
    etat_bouton[1] = (currtouched & _BV(1)) && !(lasttouched & _BV(1));
    etat_bouton[2] = (currtouched & _BV(2)) && !(lasttouched & _BV(2));
    etat_bouton[3] = (currtouched & _BV(3)) && !(lasttouched & _BV(3));
    etat_bouton[4] = (currtouched & _BV(4)) && !(lasttouched & _BV(4));

    jeu();                                // on appelle la void jeu

    Niveau();                             // on appelle la void niveau

    // si il y a 3 vie alors allumer toutes les leds vies
    if (vies == 3) {
      digitalWrite(vie1, HIGH);
      digitalWrite(vie2, HIGH);
      digitalWrite(vie3, HIGH);
    }
    // si il y a 2 vie alors allumer deux led vies
    if (vies == 2) {
      digitalWrite(vie1, HIGH);
      digitalWrite(vie2, HIGH);
      digitalWrite(vie3, LOW);
    }
    // si il y a 1 vie alors allumer une led
    if (vies == 1) {
      digitalWrite(vie1, HIGH);
      digitalWrite(vie2, LOW);
      digitalWrite(vie3, LOW);
    }
  }
  // si vie = 0 alors allumer toutes leds et puis les etiendres
  else  if (vies == 0) {
    animefin();
  }

  if (vies < 0) {     // si l'utilisateur n'a plus de vie (vie = -1)  alors aller vers arretjeu
    arretjeu();
  }

  lasttouched = currtouched;      // la dernière branche toucher devient celle qui est entraint d'être touché


}


void animedebut() {             // annimation du debut, alumer led 1 attendre 0,3 seconde puis l'eteindre et ainsi de suite
  digitalWrite(vie1, HIGH);
  delay(300);
  digitalWrite(vie1, LOW);
  delay(300);
  digitalWrite(vie2, HIGH);
  delay(300);
  digitalWrite(vie2, LOW);
  delay(300);
  digitalWrite(vie3, HIGH);
  delay(300);
  digitalWrite(vie3, LOW);
  delay(300);
  digitalWrite(vie1, HIGH);
  digitalWrite(vie2, HIGH);
  digitalWrite(vie3, HIGH);
  digitalWrite(vie1, LOW);
  digitalWrite(vie2, LOW);
  digitalWrite(vie3, LOW);
}

void jeu() {
  // reprendre la valeur du aléatoire
  for (int i = 0; i < 5; i++) {
    if ((etat_bouton[i] == HIGH) || millis() - prevMillis > led_delay) {   // si le bouton est touché et / ou le temps est respecté,
      Serial.print("bouton appuyé : ");
      Serial.println(i);
      prevMillis = millis();
      if ((i == zone_active) || millis() - prevMillis > led_delay) { // changement de niveau si le bon bouton est touché et que le temps est respecté
        Serial.print("gagné !");
        Serial.print(" vies : ");
        Serial.println(vies);
        Serial.print("vous êtes au niveau : ");
        Serial.println(niveau);
        niveau ++;
        nouvelle_zone = true; // création d'une nouvelle zone
        delay(500);
        prevMillis = millis();
      } else { // si l'une des deux condition n'est pas respecté alors perte de vie et changement de zone
        vies --;
        Serial.print("perdu !");
        Serial.print(" vies : ");
        Serial.println(vies);
        nouvelle_zone = true;
        delay(500);
      }
    }
  }

  // toutes les led sont éteinte
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(vie1, LOW);
  digitalWrite(vie2, LOW);
  digitalWrite(vie3, LOW);

  // si la zone est 0 alors allume la led 0

  if (zone_active == 0 ) {
    digitalWrite(LED0, HIGH);
  }
  // si la zone est 1 alors allume la led 1
  if (zone_active == 1 ) {
    digitalWrite(LED1, HIGH);
  }
  // si la zone est 2 alors allume la led 2
  if (zone_active == 2 ) {
    digitalWrite(LED2, HIGH);
  }
  // si la zone est 3 alors allume la led 3
  if (zone_active == 3 ) {
    digitalWrite(LED3, HIGH);
  }
  // si la zone est 4 alors allume la led 4
  if (zone_active == 4 ) {
    digitalWrite(LED4, HIGH);
  }
}


void Niveau() {
  // si le niveau est inférieur à 10 alors prendre led_delay
  if (niveau < 10) {
    led_delay = led_delay;
  }
  // si le niveau est compris entre 10 et 20 alors prendre led_delay1
  if ((niveau > 10) && (niveau < 20)) {
    led_delay = led_delay1;
  }
  // si le niveau est compris entre 20 et 30 alors prendre led_delay2
  if ((niveau > 20) && (niveau < 30)) {
    led_delay = led_delay2;
  }
  // si le niveau est compris entre 30 et 40 alors prendre led_delay3
  if ((niveau > 30) && (niveau < 40)) {
    led_delay = led_delay3;
  }
  if (niveau == 40) {   // si le niveau est de 40 alors allumer toutes les leds et écrire vous avez gagner
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(500);
    Serial.print("vous avez gagner");
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(500);
  }
}

void animefin() {
  // Quand l'utilisateur perd, allumer toute les leds 2 secondes puis les éteindres
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(vie1, LOW);
  digitalWrite(vie2, LOW);
  digitalWrite(vie3, LOW);
  delay(2000);
  Serial.print("vous avez perdu");

  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(2000);
  vies --;        // sortir du void animefin et aller vers arretjeu
}

void arretjeu() {     // éteindre toutes les leds
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}
