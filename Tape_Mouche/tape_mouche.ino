//-----AFFICHEUR A 4 DIGITS-----//


#include "TM1637.h"     // inclure la bibliothèque
#define CLK 6     // on définit la connexion de la broche CLK sur le pin 6
#define DIO 7     // on définit la connexion de la broche DIO sur le pin 7
TM1637 tm1637(CLK, DIO);     // on attache de manière effective nos pins et notre écran
int8_t NumTab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};     // on définit les caractères disponibles


//----------LEDS---------//


int ledPin1 = 2;     // on indique que "ledPin1" est branché sur le pin 2
int ledPin2 = 3;     // on indique que "ledPin2" est branché sur le pin 3
int ledPin3 = 4;     // on indique que "ledPin3" est branché sur le pin 4
int ledPin4 = 5;     // on indique que "ledPin4" est branché sur le pin 5


//----------BOUTONS---------//


int bouton1 = 8;     // on indique que "bouton1" est branché sur le pin 8
int bouton2 = 9;     // on indique que "bouton2" est branché sur le pin 9
int bouton3 = 10;     // on indique que "bouton3" est branché sur le pin 10
int bouton4 = 11;     // on indique que "bouton4" est branché sur le pin 11
int boutonReset = 12;     // on indique que "boutonReset" est branché sur le pin 12
boolean etatBouton1;     // on crée une variable que l'on nomme "etatBouton1"
boolean etatBouton2;     // on crée une variable que l'on nomme "etatBouton2"
boolean etatBouton3;     // on crée une variable que l'on nomme "etatBouton3"
boolean etatBouton4;     // on crée une variable que l'on nomme "etatBouton4"
boolean hasTapped = false;     // on crée une variable de type boolean nommée "hasTapped", et on lui donne la valeur "false"


//----------VARIABLES----------//


int nombreAleatoireTemps;     // on crée une variable qui servira à stocker la valeur aléatoire de temps
int nombreAleatoireLed;     // on crée une variable qui servira à stocker la valeur aléatoire de led
int interval = 1000;     // on définit une variable "interval" dans laquelle on stocke la valeur 1000 (qui correspondra à 1sec)
int gameTime = 120000; // on définit une variable "gameTime" dans laquelle on stocke la valeur 120000 (qui correspondra à 2 min)
int score = 0;


//------------------------------------//
//           FONCTION SETUP           //
//------------------------------------//


void setup() {

    pinMode(ledPin1, OUTPUT);     // on indique que "ledPin1" est une sortie
    pinMode(ledPin2, OUTPUT);     // on indique que "ledPin2" est une sortie
    pinMode(ledPin3, OUTPUT);     // on indique que "ledPin3" est une sortie
    pinMode(ledPin4, OUTPUT);     // on indique que "ledPin4" est une sortie

    pinMode(bouton1, INPUT);     // on indique que "bouton1" est une entrée
    pinMode(bouton2, INPUT);     // on indique que "bouton2" est une entrée
    pinMode(bouton3, INPUT);     // on indique que "bouton3" est une entrée
    pinMode(bouton4, INPUT);     // on indique que "bouton4" est une entrée

    digitalWrite(ledPin1, LOW);     // on éteint "ledPin1"
    digitalWrite(ledPin2, LOW);     // on éteint "ledPin2"
    digitalWrite(ledPin3, LOW);     // on éteint "ledPin3"
    digitalWrite(ledPin4, LOW);     // on éteint "ledPin4"

    randomSeed(analogRead(0));     // on initialise la séquence aléatoire
    Serial.begin(9600);     // on initialise le moniteur série
    tm1637.init();     // on initialise l'écran de l'afficheur à 4 digits
    tm1637.set(BRIGHTEST);     // on définit la luminosité de l'afficheur à 4 digits

}


//------------------------------------//
//          FONCTION TESTLED          //
//------------------------------------//


// au début de chaque partie, les leds vont s'allumer une à une. Cela permettra de vérifier que chaque led fonctionne correctement, mais également de faire un compte à rebours avant le départ.

void testLed() {

    digitalWrite(ledPin1, HIGH);     // on allume "ledPin1"
    delay(1000);     // on arrête le programme pendant 1 sec
    digitalWrite(ledPin2, HIGH);     // on allume "ledPin2"
    delay(1000);     // on arrête le programme pendant 1 sec
    digitalWrite(ledPin3, HIGH);     // on allume "ledPin3"
    delay(1000);     // on arrête le programme pendant 1 sec
    digitalWrite(ledPin4, HIGH);     // on allume "ledPin4"
    delay(1000);     // on arrête le programme pendant 1 sec

    digitalWrite(ledPin1, LOW);     // on éteint "ledPin1"
    digitalWrite(ledPin2, LOW);     // on éteint "ledPin2"
    digitalWrite(ledPin3, LOW);     // on éteint "ledPin3"
    digitalWrite(ledPin4, LOW);     // on éteint "ledPin4"

}


//------------------------------------//
//      FONCTION GIMMEMYSCORE         //
//------------------------------------//


// la fonction "gimmemyscore" permet de vérifier lorsqu'une led est allumée, si on appuie bien sur le bouton correspondant. Dans ce cas, la fonction retourne la valeur 1, et dans le cas contraire, si on clique sur un bouton dont la led correspondante n'est pas allumée, la fonction retourne -1. Pour rappel, dans mon montage, j'ai décidé d'associer "ledPin1" (pin 2) et "bouton1" (pin 8), "ledPin2" (pin 3) et "bouton2" (pin 9), "ledPin3" (pin 4) et" bouton3" (pin 10), "ledPin4" (pin 5) et "bouton4" (pin 11).

int gimmemyscore(int led) {     // pour la fonction "gimmemyscore" on utilise une variable (un entier) "led"
    
    if (led == 2) {     // si la variable "led" est égale à 2
        if (digitalRead(bouton1) == 1) {     // si la valeur de "bouton1" est égal à 1
            return 1;     // alors la fonction "gimmemyscore" retourne 1
        } else if (digitalRead(bouton2) == 1 || digitalRead(bouton3) == 1 || digitalRead(bouton4) == 1) {     // sinon, si "bouton2" ou "bouton3" ou "bouton4" est égale à 1
            return -1;     // alors la fonction "gimmemyscore" retourne -1
        }
    }

    if (led == 3) {     // si la variable "led" est égale à 3
        if (digitalRead(bouton2) == 1) {     // si la valeur de "bouton2" est égale à 1
            return 1;     // alors la fonction "gimmemyscore" retourne 1
        } else if (digitalRead(bouton1) == 1 || digitalRead(bouton3) == 1 || digitalRead(bouton4) == 1) {     // sinon, si "bouton1" ou "bouton3" ou "bouton4" est égale à 1
            return -1;     // alors la fonction "gimmemyscore" retourne -1
        }
    }

    if (led == 4) {     // si la variable "led" est égale à 4
        if (digitalRead(bouton3) == 1) {     // si la valeur de "bouton3" est égale à 1
            return 1;     // alors la fonction "gimmemyscore" retourne 1
        } else if (digitalRead(bouton1) == 1 || digitalRead(bouton2) == 1 || digitalRead(bouton4) == 1) {     // sinon, si "bouton1" ou "bouton2" ou "bouton4" est égale à 1
            return -1;     // alors la fonction "gimmemyscore" retourne -1
        }
    }

    if (led == 5) {     // si la variable "led" est égale à 5
        if (digitalRead(bouton4) == 1) {     // si la valeur de "bouton4" est égale à 1
            return 1;     // alors la fonction "gimmemyscore" retourne 1
        } else if (digitalRead(bouton1) == 1 || digitalRead(bouton2) == 1 || digitalRead(bouton3) == 1) {     // sinon, si "bouton1" ou "bouton2" ou "bouton3" est égale à 1
            return -1;     // alors la fonction "gimmemyscore" retourne -1
        }
    }

    return 0;     // si on appuie sur aucun bouton alors qu'une led est allumée, la fonction "gimmemyscore" retourne 0
    
}


//------------------------------------//
//          FONCTION DISPLAY          //
//------------------------------------//


// cette fonction permet d'afficher le score du joueur sur l'afficheur à 4 digits

void display(int number) {     // pour la fonction "display", on utilise une variable "number"

  int num = abs(number);     // on stocke dans la variable "num" la valeur absolue de la variable "number"
  tm1637.display(0, (int(num/1000)%10));     // affiche le chiffre des unités de la variable "number"
  tm1637.display(1, (int(num/100)%10));     // affiche le chiffre des dizaines de la variable "number"
  tm1637.display(2, (int(num/10)%10));     // affiche le chiffre des centaines de la variable "number"
  tm1637.display(3, (num%10));     // affiche le chiffre des milliers de la variable "number"

}


//------------------------------------//
//           FONCTION LOOP            //
//------------------------------------//


void loop() {

    score = 0;     // on remet la valeur de la variable "score" à 0
    display(0);     // on effectue la fonction "display" avec la variable "number" égale à 0, c'est à dire qu'on va afficher 0 sur l'afficheur à 4 digits

    while (digitalRead(boutonReset) == 0 ) { }     // tant que l'on appuie pas sur le "boutonReset", le programme attend avant de poursuivre

    unsigned long gameStart = millis();     // on place dans la variable "gameStart" la valeur correspondante au temps depuis lequel la carte arduino a été allumée
    testLed();     // on effectue la fonction "testLed", c'est à dire le compte à rebours avant le départ

    while( gameStart + gameTime > millis() ) {     // tant que la valeur de la variable "gameStart" plus celle de la variable "gameTime" (2min) est supérieure au temps depuis lequel la carte arduino a été allumée, on continue d'effectuer la boucle "while", c'est à dire que pendant 2min, on effectue "while" en boucle

        nombreAleatoireTemps = random(5000);     // on place un nombre aléatoire entre 0 et 5000 dans la variable "nombreAleatoire" (entre 0 et 5sec)
        nombreAleatoireLed = random(2, 6);     // on place un nombre aléatoire entre 2 et 5 dans la variable "nombreAleatoireLed"
    
        unsigned long start = millis();     // on place dans la variable "start" la valeur correspondante au temps depuis lequel la carte arduino a été allumée
    
        while ( start + nombreAleatoireTemps > millis() ) {     // tant que la valeur de la variable "start" plus celle de la variable "nombreAleatoireTemps" est supérieure au temps depuis lequel la carte arduino a été allumée, on continue d'effectuer la boucle "while"
    
            boolean tappedThisFrame = digitalRead(bouton1) == 1 || digitalRead(bouton2) == 1 || digitalRead(bouton3) == 1 || digitalRead(bouton4) == 1;     // on vérifie si le joueur a appuyé sur un des 4 boutons
    
            if (tappedThisFrame && !hasTapped) {     // si le joueur a tapé un bouton à ce passage de boucle mais pas à celui d'avant
                score += -1;     // alors on ajoute -1 à la variable "score"
                if (score < 0) {     // si le score est inférieur à 0
                    score = 0;     // alors le score est égal à zéro, de ce fait, on empêche le joueur d'avoir un score négatif
                }
                display(score);     // on effectue la fonction "display" avec la variable "score", c'est à dire que l'on va afficher le score du joueur sur l'afficheur à 4 digits
                hasTapped = true;     // on change la valeur de la variable "hasTapped" par true
            }
    
            if (!tappedThisFrame) {     // si on n'a pas appuyé sur un bouton lors de ce passage de la boucle
                hasTapped = false;     // alors on change la valeur de la variable "hasTapped" par "false"
            }
        }
    
        start = millis();     // on place dans la variable "start" la valeur correspondante au temps depuis lequel la carte arduino a été allumée
        boolean hasPointGagner = false;     // on impose la valeur "false" à la variable "hasPointGangner"
        boolean hasPointPerdu = false;     // on impose la valeur "false" à la variable "hasPointGangner"
    
        digitalWrite(nombreAleatoireLed, HIGH);     // on allume la led correspondante au pin "nombreAleatoireLed"
    
        while (start + interval > millis() && !hasPointGagner) {     // tant que la valeur de la variable "start" plus celle de la variable "interval" (1sec) est supérieure au temps depuis lequel la carte arduino a été allumée et que la valeur de la variable "hasPointGagner" est égale à "false"
    
            int point = gimmemyscore(nombreAleatoireLed);     // on effectue la fonction "gimmemyscore" avec la valeur de la variable "nombreAleatoireLed"
                
            if (point != 0 && !hasTapped) {     // si la valeur de la variable "point" est différente de 0, et que on a appuyé sur un bouton
                score += point;     // alors on ajoute la valeur de la variable "point" à la valeur de la variable "score"
                if (score < 0) {     // si la valeur de la variable "score" est inférieure à zéro
                    score = 0;     // alors la valeur de la variable "score" est égale à zéro, de ce fait, on empêche le joueur d'avoir un score négatif
                }
                hasTapped = true;     // alors on change la valeur de la variable "hasTapped" par "true"
                display(score);     // on effectue la fonction "display" avec la variable "score", c'est à dire que l'on va afficher le score du joueur sur l'afficheur à 4 digits
            }
    
            if (point == 0) {     // si la valeur de la variable "point" est égale à zéro
                hasTapped = false;     // alors on change la valeur de la variable "hasTapped" par "false"
            }
    
            if (point == 1) {     // si la valeur de la variable "point" est égale à 1
                hasPointGagner = true;     // alors on change la valeur de la variable "hasPointGagner" par "true"
            }
    
            if (point == -1) {     // si la valeur de la variable "point" est égale à -1
                hasPointPerdu = true;     // alors on change la valeur de la variable "hasPointPerdu" par "true"
            }
        }
    
        digitalWrite(nombreAleatoireLed, LOW);     // on éteint la led correspondante au pin "nombreAleatoireLed"
    
        if (!hasPointGagner && !hasPointPerdu && score < 0) {     // si la valeur de la variable "hasPointGagner" est égale à false et que la valeur de la variable "hasPointPerdu" est égale à false et que la valeur de la variable "score" est inférieure à zéro
            score -= 1;     // alors on enlève 1 à la valeur de la variable "score"
        }
    
        display(score);     // on effectue la fonction "display" avec la valeur de la variable "score"

    }

}