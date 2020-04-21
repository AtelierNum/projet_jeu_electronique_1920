// On commence par incorporer la librairy pour utiliser les afficheurs à 4 digits
#include <SevenSegmentFun.h>
#include <SevenSegmentTM1637.h>
#include <SevenSegmentExtended.h>


// SevenSegmentTM1637 afficheur(BROCHE_CLK, BROCHE_DIO) pour conntecter les afficheurs;
SevenSegmentTM1637 afficheur_joueur1(4, 5);
SevenSegmentTM1637 afficheur_joueur2(6, 7);

// On connecte la LED à la pin 9
#define LED   9

// On connecte les boutons de chaque joueur
int pinBouton1 = 3;
int pinBouton2 = 2;

// On déclare 2 variables liées à l'intensité lumineuse de la LED
float T = 0;
float incr = 0.005;

// On crée un bouleén pour chaque bouton , cela sert à lancer une fonction lorsque l'on presse le bouton 1 fois
boolean bouton1Appui = false;
boolean bouton2Appui = false;

// On crée 2 variables de score, une pour chaque joueur et on les initialise à 0
int scoreP1 = 0;
int scoreP2 = 0;


void setup() {

// On renseigne les rôles des différentes pins et on démarre la communication avec le moniteur série
  pinMode(pinBouton1, INPUT);
  pinMode(pinBouton2, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  
// On initialise les afficheurs des 2 joueurs
  afficheur_joueur1.begin();
  afficheur_joueur1.setBacklight(100);
  afficheur_joueur2.begin();
  afficheur_joueur2.setBacklight(100);

// On utilise une randomSeed sur la pin A0 pour qu'elle capte une donnée naturelle et base sa génération de nombres aléatoires dessus 
// Cette ligne nous permet d'avoir une vraie notion d'aléatoire à chaque lancement du programme
  randomSeed(analogRead(0));

}


void loop() {


  T  += incr;

 // On fait varier l'intensité lumineuse grâce au sinus, sa courbe sinusoïdale permet d'avoir une variation de lumière progressive
  double fadeValue = (sin(T) + 1 ) * 127;
  analogWrite(LED, fadeValue);


 // On change la valeur de la variation a chaque boucle = On change le rythme d'éclairage à chaque boucle
  if (fadeValue < 1) {
    incr = random(2, 100) / 100000.0;
  }

// On lit l'état des boutons de chaque joueur à chaque boucle
  int etatBouton1 = digitalRead(pinBouton1);
  int etatBouton2 = digitalRead(pinBouton2);

// On lance la boucle à l'instant où le bouton de joueur 1 est pressé
  if (etatBouton1 == 1 && bouton1Appui == false) {
    scoreP1 = round(fadeValue);   // Le score prend la valeur de la luminosité de la LED à l'instant T
    scoreP1 = map(scoreP1, 0, 255, 0, 1001);    // On reporte ce chiffre pour avoir un score entre 0 et 1000
    afficheur_joueur1.print(scoreP1);     // On affiche le score sur l'écran du joueur 1
    bouton1Appui = true;      // On change la valeur de la variable : On ne peut pas changer son score, il faut donc relance une partie pour retenter sa chance
  }

// Exactement la même fonction que le joueur 1, pour le joueur 2
  if (etatBouton2 == 1 && bouton2Appui == false) {
    scoreP2 = round(fadeValue);
    scoreP2 = map(scoreP2, 0, 255, 0, 1001);
    afficheur_joueur2.print(scoreP2);
    bouton2Appui = true;
  }

}
