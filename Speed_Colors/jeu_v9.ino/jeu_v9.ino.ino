
#include <Adafruit_NeoPixel.h>

//On définit l'emplacement de nos composants
#define BROCHE_LED  8
#define NUMPIXELS   18

//On appelle la bibliothèque pour les rubans de LED
Adafruit_NeoPixel pixels = Adafruit_NeoPixel (NUMPIXELS, BROCHE_LED, NEO_GRB  + NEO_KHZ800);

//On définit l'emplacement de nos boutons
#define BROCHE_BOUTON_0   2
#define BROCHE_BOUTON_1   3
#define BROCHE_BOUTON_2   4
#define BROCHE_BOUTON_3   5
#define BROCHE_BOUTON_4   6
#define BROCHE_BOUTON_5   7
#define LED 13

// a t'on pressé ou pas le bouton ?
boolean etat_bouton[6];

// quelle couleur est associée à tel bouton ?
int couleur_bouton[6];

// couleur à trouver
int couleur;

// initialiser une nouvelle partie (choix d'une nouvelle couleur)
boolean nouvelle_partie = true;

// moment ou a démarré la partie
long depart_partie;

// une partie dure 5000 ms
long duree = 5000;

// entier correspondant à la luminosité  - Vérifier si on l'utilise !!!!!!
int luminosite = 250;
int luminosite_variation = 1;
int intervalle = 500;


long randNumber;


// On définit nos couleurs
int RED[3] = {133, 6, 6}; // Couleur Rouge sang
int GREEN[3] = {0, 255, 0}; // Couleur Vert
int BLUE[3] = {0, 0, 255}; // Couleur Bleu
int CYAN[3] = {0, 255, 255}; // Couleur Cyan
int YELLOW[3] = {255, 125, 0}; // Couleur Jaune
int PINK[3] = {255, 0, 255}; // Couleur Rose
int PURPLE[3] = {105, 24, 180}; //Couleur Violet
int DARKGREEN[3] = {0, 102, 0}; //Couleur vert foncé
int BROWN[3] = {170, 142, 116}; //Couleur marron

// On place nos couleurs dans un tableau à neuf colonnes, composé de 3 valeurs
int COULEURS [9][3] = {
  {133, 6, 6}, // Couleur Rouge sang
  {0, 255, 0}, // Couleur Vert
  {0, 0, 255}, // Couleur Bleu
  {0, 255, 255}, // Couleur Cyan
  {255, 125, 0}, // Couleur Jaune
  {255, 0, 255}, // Couleur Rose
  {105, 24, 180}, //Couleur Violet
  {0, 102, 0}, //Couleur vert foncé
  {170, 142, 116} //Couleur marron
};



void setup() {
  Serial.begin(9600);

  // On définit les broches associées aux boutons en entrée
  pinMode (BROCHE_BOUTON_0, INPUT);
  pinMode (BROCHE_BOUTON_1, INPUT);
  pinMode (BROCHE_BOUTON_2, INPUT);
  pinMode (BROCHE_BOUTON_3, INPUT);
  pinMode (BROCHE_BOUTON_4, INPUT);
  pinMode (BROCHE_BOUTON_5, INPUT);

  randomSeed(analogRead(0));

  pixels.begin();
  pixels.show();
}

// On reserve la boucle "Loop" pour le fonctionnement du jeu
void loop() {

  //On initialise une nouvelle partie
  if (nouvelle_partie) {
    initialiser();
    nouvelle_partie = false;
  }

  pixels.show();

  // On lit l'état des broches associées aux boutons
  etat_bouton[0] = digitalRead(BROCHE_BOUTON_0);
  etat_bouton[1] = digitalRead(BROCHE_BOUTON_1);
  etat_bouton[2] = digitalRead(BROCHE_BOUTON_2);
  etat_bouton[3] = digitalRead(BROCHE_BOUTON_3);
  etat_bouton[4] = digitalRead(BROCHE_BOUTON_4);
  etat_bouton[5] = digitalRead(BROCHE_BOUTON_5);
  // Serial.println(etat_bouton);

  //La partie de l'ecran principal : on affiche nos couleurs, l'écran diminue en fonction de la durée

  // On utilise "map" pour dire que entre deux valeurs on va prendre deux autres valeurs puis on prend la valeur 17 de la led et la 9.
  int npixel = map(millis(), depart_partie , depart_partie + duree , 17, 9);

  npixel = constrain(npixel, 10,  17);  // L'entier npixel, ne sort pas de 10 et 17 grâce à "constrain".
  Serial.println(npixel);
  if (npixel >= 10) {
    pixels.setPixelColor ( 10, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 10 allumée
  }
  else {  // Pour chaque LED, on indique que si l'intervalle de temps est depassé, dans ce cas elle s'allume en noir
    pixels.setPixelColor ( 10, pixels.Color(0, 0, 0)); //LED 10 éteinte
  }

  if (npixel >= 11) {
    pixels.setPixelColor ( 11, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 11 allumée
  }
  else {
    pixels.setPixelColor ( 11, pixels.Color(0, 0, 0)); //LED 11 éteinte
  }

  if (npixel >= 12) {
    pixels.setPixelColor ( 12, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 12 allumée
  }
  else {
    pixels.setPixelColor ( 12, pixels.Color(0, 0, 0)); //LED 12 éteinte
  }
  if (npixel >= 13) {
    pixels.setPixelColor ( 13, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 13 allumée
  }
  else {
    pixels.setPixelColor ( 13, pixels.Color(0, 0, 0)); //LED 13 éteinte
  }
  if (npixel >= 14) {
    pixels.setPixelColor ( 14, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 14 allumée
  }
  else {
    pixels.setPixelColor ( 14, pixels.Color(0, 0, 0)); //LED 14 éteinte
  }
  if (npixel >= 15) {
    pixels.setPixelColor ( 15, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 15 allumée
  }
  else {
    pixels.setPixelColor ( 15, pixels.Color(0, 0, 0)); //LED 15 éteinte
  }
  if (npixel >= 16) {
    pixels.setPixelColor ( 16, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 16 allumée
  }
  else {
    pixels.setPixelColor ( 16, pixels.Color(0, 0, 0));//LED 16 éteinte
  }

  if (npixel >= 17) {
    pixels.setPixelColor ( 17, pixels.Color(COULEURS[couleur][0], COULEURS[couleur][1] , COULEURS[couleur][2])); //LED 17 allumée
  }
  else {
    pixels.setPixelColor ( 17, pixels.Color(0, 0, 0)); //LED 17 éteinte
  }



  if (millis() - depart_partie > duree ) { // Le temps de la partie s'est il écoulé ?
    // Si oui, TOUT LE MONDE A PERDU !
    for (int i = 0; i < pixels.numPixels(); i++) { // L'ecran prendra la couleur rouge
      pixels.setPixelColor(i, 255, 0, 0);
    }
    pixels.show(); // Allumer l'ensemble des LED en rouge
  } else {
    // Si non, LA PARTIE CONTINUE !
    for (int i = 0; i < 6; i++) {
      if (etat_bouton[i] == true ) {
        if (couleur_bouton[i] == couleur) {
          // GAGNE, On passe à une nouvelle partie
          nouvelle_partie = true;
          delay(1000);
          Serial.println("YEAH");

          duree = duree - 250; // A chaque tour, le temps diminu de 250ms
          duree = constrain( duree, 1000, 5000); // Nous fixons une limite de temps à 1000ms et un temps maximum a 5000ms

        } else {
          // PERDU, définir que l'ensemble des LED seront en rouge
          if ( i < 3) { // joueur1 a perdu
            for (int i = 0; i < 5; i++) {
              pixels.setPixelColor(i, 255, 0, 0);
            }
            for (int i = 5; i < 10; i++) {
              pixels.setPixelColor(i, 255, 255, 255);
            }
          }
          else { // joueur2 a perdu
            for (int i = 0; i < 5; i++) {
              pixels.setPixelColor(i, 255, 255, 255);
            }
            for (int i = 5; i < 10; i++) {
              pixels.setPixelColor(i, 255, 0, 0);
            }

          }

          pixels.show(); // Afficher les LED en rouge
          nouvelle_partie = false;
          Serial.println("NON");
        }
      }
    }
  }


}

void initialiser() { //Fonction nous permettant d'initialiser notre jeu à chaque boucle
  Serial.println("nouvelle partie");

  couleur = random(9); // On tire au sort une couleur principale parmis les 9 pré-définis

  Serial.print("couleur principale : ");
  Serial.print(couleur);



  // bouton joueur 1
  // Déterminer les trois couleurs tirées au sort pour un joueur dont celle à trouver (de l'écran principal)
  for (int i = 0; i < 3; i++) {
    couleur_bouton[i] = random(9);
  }
  int pos = random(3);
  couleur_bouton[pos] = couleur; // Couleur à trouver



  // bouton joueur 2
  // Déterminer les trois couleurs tirées au sort pour un joueur dont celle à trouver (de l'écran principal)
  for (int i = 3; i < 6; i++) {
    couleur_bouton[i] = random(9);
  }
  pos = random(3);
  couleur_bouton[pos + 3] = couleur; // Couleur à trouver


  // Afficher les codes couleurs dans le controller
  Serial.print(" --- couleurs pour le joueur 1 : ");
  Serial.print(couleur_bouton[0]);
  Serial.print(" ");
  Serial.print(couleur_bouton[1]);
  Serial.print(" ");
  Serial.print(couleur_bouton[2]);
  Serial.print(" ");

  Serial.print(" --- couleurs pour le joueur 2 : ");
  Serial.print(couleur_bouton[3]);
  Serial.print(" ");
  Serial.print(couleur_bouton[4]);
  Serial.print(" ");
  Serial.print(couleur_bouton[5]);
  Serial.println();



  // Afficher les couleurs tirées au sort et les affiché sur le ruban de LED

  //Manette des deux joueurs
  pixels.setPixelColor ( 0, pixels.Color(COULEURS[couleur_bouton[0]][0],
                                         COULEURS[couleur_bouton[0]][1],
                                         COULEURS[couleur_bouton[0]][2] )); //LED 1 JOUEUR 1


  pixels.setPixelColor ( 2, pixels.Color(COULEURS[couleur_bouton[1]][0],
                                         COULEURS[couleur_bouton[1]][1],
                                         COULEURS[couleur_bouton[1]][2] )); //LED 2 JOUEUR 1

  pixels.setPixelColor ( 4, pixels.Color(COULEURS[couleur_bouton[2]][0],
                                         COULEURS[couleur_bouton[2]][1],
                                         COULEURS[couleur_bouton[2]][2] )); //LED 3 JOUEUR 1

  pixels.setPixelColor ( 5, pixels.Color(COULEURS[couleur_bouton[3]][0],
                                         COULEURS[couleur_bouton[3]][1],
                                         COULEURS[couleur_bouton[3]][2] )); //LED 4 JOUEUR 2

  pixels.setPixelColor ( 7, pixels.Color(COULEURS[couleur_bouton[4]][0],
                                         COULEURS[couleur_bouton[4]][1],
                                         COULEURS[couleur_bouton[4]][2] )); //LED 5 JOUEUR 2

  pixels.setPixelColor ( 9, pixels.Color(COULEURS[couleur_bouton[5]][0],
                                         COULEURS[couleur_bouton[5]][1],
                                         COULEURS[couleur_bouton[5]][2] )); //LED 6 JOUEUR 2





  depart_partie = millis();

  pixels.show();

  //delay(5);
}
