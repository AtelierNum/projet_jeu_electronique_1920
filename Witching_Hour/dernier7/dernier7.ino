#include <SevenSegmentFun.h>           // on inclut 3 bibliothèque pour faire fonctionner le chrono 
#include <SevenSegmentTM1637.h>
#include <SevenSegmentExtended.h>
#include <Adafruit_NeoPixel.h>        // on inclut une bibliothèque pour faire fonctionner la jauge

#define BROCHE_CLK    13   //on définit les branchements du défileur de points
#define BROCHE_DIO    12   //on définit les branchements du défileur de points
SevenSegmentTM1637 afficheur(BROCHE_CLK, BROCHE_DIO);

int pinBouton = 2;    // on créer les variables des boutons des 5 lampes
int pinBouton1 = 3;
int pinBouton2 = 10;
int pinBouton3 = A3;
int analogPin = A5;
int boutonPlay = A4;  // on créer la variable du bouton play
int pinLed = 5;
int pinLed1 = 6;
int pinLed2 = 7;
int pinLed3 = 8;
int pinLed4 = 9;
int pinLedlampe = 11;


int score = 1200;// on créer une variable pour le score que l'on met à 1200




int   etatlumiere;       //On créer une variable pour chaque système de led et bouton
int   etatlumiere11;
int   etatlumiere2;
int   etatlumiere3;
int   etatlumiere4;
boolean etatBouton;     //On donne un état boolean pour chaque bouton de chaque led pour que l'on puissent récupérer sa valeur "fermé" ou "ouvert"
boolean etatBouton11;
boolean etatBouton2;
boolean etatBouton3;
boolean etatBouton4;
boolean etatanalogPin;
boolean etatboutonPlay;   //On donne un état boolean pour le bouton play pour que l'on puissent récupérer sa valeur "fermé" ou "ouvert"




#define PIN        4   // on définit l'entrée de la jauge en 4

#define NUMPIXELS 6   // Elle a 6 pixels


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  // 


unsigned long previousMillis = 0;    // le temps que le programme est en route commence à être compté
bool led1Allume = false;   // on donne la variable led1Allume qui aura 2 valeurs
bool led1Valide = false;   // on donne la variable led1Valide qui aura 2 valeurs
bool led1Erreur = false;   // on donne la variable led1Erreur qui aura 2 valeurs
bool led11Allume = false;   
bool led11Valide = false;   
bool led11Erreur = false;   
bool led2Allume = false;   
bool led2Valide = false;   
bool led2Erreur = false;   
bool led3Allume = false;   
bool led3Valide = false;   
bool led3Erreur = false;   
bool led4Allume = false;   
bool led4Valide = false;   
bool led4Erreur = false;   



bool nouvelle_partie = true;  // on définit un état boolean true ou faulse pour commencer la partie
int chrono = 0;  // on définit la valeur initiale du chrono à 0
long debut_partie; // conserver le moment ou a commencé la partie


void setup() {
  pinMode(pinBouton, INPUT);    // on déclare le bouton en tant qu'une entrée
  pinMode(pinLed, OUTPUT);      // on déclare la led en tant qu'une entrée
  pinMode(pinBouton1, INPUT);    // on déclare le bouton en tant qu'une entrée
  pinMode(pinLed1, OUTPUT);      // on déclare la led en tant qu'une entrée
  pinMode(pinBouton2, INPUT);    // on déclare le bouton en tant qu'une entrée
  pinMode(pinLed2, OUTPUT);      // on déclare la led en tant qu'une entrée
  pinMode(pinBouton3, INPUT);    // on déclare le bouton en tant qu'une entrée
  pinMode(pinLed3, OUTPUT);      // on déclare la led en tant qu'une entrée

  pinMode(pinLed4, OUTPUT);      // on déclare la led en tant qu'une sortie
    pinMode(pinLedlampe, OUTPUT);      // on déclare la led en tant qu'une sortie
  pinMode(analogPin, INPUT);    // on déclare le bouton en tant qu'une entrée

  Serial.begin(9600);
  pixels.begin();
  
  


  
    afficheur.begin();            // initializes the display
    
  afficheur.setBacklight(100);  // set the brightness to 100 %
  afficheur.print("WITCHING HOUR");      // display INIT on the display
  delay(1000);                // wait 1000 ms
  afficheur.clear();          // l'afficheur réaffiche
 
}
void loop() {
  
 
  ////////////////////////////// affichage chrono ////////////////////////////
  if (nouvelle_partie) {
    debut_partie = millis();      // on commence à compter le temps
    chrono = 0;
    nouvelle_partie = false;     // on redonne la valeur false à nouvelle partie
  } else {
    chrono = (millis() - debut_partie) / 100;    // on calcul le nombre de seconde écoulée depuis le début de la partie
  }
  afficheur.clear();      // on rénitalise le chrono
  afficheur.print(chrono);   // on affiche la nouvelle valeur

  ///////////////////////////////////// 1ère lumière//////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////

  etatlumiere = random(0, 2000  );       // L'etat de la lumière est définit de façon random par des chiffres de 0 à 2000
  //Serial.println (etatlumiere);
  unsigned long currentMillis = millis();  // on compte le temps qui s'est écoulé depuis le début du programme juqu'ici
  etatBouton = digitalRead(pinBouton);
  // Serial.println(etatBouton);


  if (etatlumiere == 0 && led1Allume == false) {  // Si l'etat de la lumière est sur 0 et que la lumière est bien fermée
    digitalWrite(pinLed, HIGH);                 // Alors la lumière s'allume
    previousMillis = currentMillis;             //  
    led1Allume = true;                          // la led est bien allumée
    led1Erreur = false;                         // il n'y a pas d'erreur
    led1Valide = false;                        //
  }


  ////////////////////////////  ON GERE LES POINTS  ////////////////////////////////////////////

  else if (currentMillis - previousMillis >= 3000 && led1Allume == true ) {  //Si le temps depuis que le programme fonctionne moins le temps écoulé depuis la nouvelle boucle est supérieur à 3s et que la lumière est allumée
    if (led1Valide == false) {   // si la led est bien ouverte
      score = score - 100;         // on baisse le score de 1 point
    }
    else if (led1Erreur == true) {    // si la led était déjà fermée
      score = score - 100;             // on baisse le score de 1 point
    }
    digitalWrite(pinLed, LOW);       // alors dans tout les cas on éteint la led
    led1Allume = false;              // la led est bien fermée
    led1Erreur = false;              // il n'y a plus d'erreur
  }


  ////////////////////////////  ON GERE LE BOUTON  ////////////////////////////////////////////

  if (etatBouton == 0 && led1Allume == false && currentMillis - previousMillis <= 3000 && led1Erreur == false) {           // si on appuie sur le bouton, que la led n'est pas allumée et que les 3s ne sont pas passées et qu'il n'y a pas d'erreur
    score = score - 100;
    led1Valide = false;                                                                                                    // la lumière est bien éteinte
    led1Erreur = true;                                                                                                     // il n'y a plus d'erreur

  }
  else if (etatBouton == 0 && led1Allume == true && currentMillis - previousMillis <= 3000) {                              // si on appuie sur le bouton, que la est pas allumée et que les 3s ne sont pas passées
    digitalWrite(pinLed, LOW);                                                                                             // alors la lumière s'éteind
    led1Allume = false;                                                                                                    // la led est bien fermée        pour les 3 derniers c remmettre tout à 0 avant de recommencer
    led1Valide = true;                                                                                                     // la led est bien allumée
    led1Erreur = false;                                                                                                    // il n'y a pas d'erreur

  }

   // c le même système pour toutes les lumières qui suivent
  ///////////////////////////////////// 2ème lumière//////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////

  etatlumiere11 = random(0, 400);       // L'etat de la lumière est définit de façon random par des chiffres de 0 à 400
  // Serial.println (etatlumiere11);
  // unsigned long currentMillis = millis();  // on compte le temps qui s'est écoulé depuis le début du programme juqu'ici
  etatBouton11 = digitalRead(pinBouton1);
  // Serial.println(etatBouton11);


  if (etatlumiere11 == 0 && led11Allume == false) {  
    digitalWrite(pinLed1, HIGH);                 
    previousMillis = currentMillis;            
    led11Allume = true;                          
    led11Erreur = false;                       
    led11Valide = false;                        
  }


  ////////////////////////////  ON GERE LES POINTS  ////////////////////////////////////////////

  else if (currentMillis - previousMillis >= 3000 && led11Allume == true ) {   
    if (led11Valide == false) {   
      score = score - 100;        
    }
    else if (led11Erreur == true) {    
      score = score - 100;             
    }
    digitalWrite(pinLed1, LOW);       
    led11Allume = false;             
    led11Erreur = false;              
  }


  ////////////////////////////  ON GERE LE BOUTON  ////////////////////////////////////////////

  if (etatBouton11 == 0 && led11Allume == false && currentMillis - previousMillis <= 3000 && led11Erreur == false) {           
    score = score - 100;
    led11Valide = false;                                                                                                   
    led11Erreur = true;                                                                                                     

  }
  else if (etatBouton11 == 0 && led11Allume == true && currentMillis - previousMillis <= 3000) {                              
    digitalWrite(pinLed1, LOW);                                                                                             
    led11Allume = false;                                                                                               
    led11Valide = true;                                                                                                     
    led11Erreur = false;                                                                                                    

  }

  ///////////////////////////////////// 3ème lumière//////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////

  etatlumiere2 = random(0, 2000);       // L'etat de la lumière est définit de façon random par des chiffres de 0 à 2000
  //Serial.println (etatlumiere2);
  // unsigned long currentMillis = millis();  // on compte le temps qui s'est écoulé depuis le début du programme juqu'ici
  etatBouton2 = digitalRead(pinBouton2);
  //Serial.println(etatBouton2);


  if (etatlumiere2 == 0 && led2Allume == false) {  
    digitalWrite(pinLed2, HIGH);                 
    previousMillis = currentMillis;             
    led2Allume = true;                          
    led2Erreur = false;                         
    led2Valide = false;                        
  }


  ////////////////////////////  ON GERE LES POINTS  ////////////////////////////////////////////

  else if (currentMillis - previousMillis >= 3000 && led2Allume == true ) {   
    if (led2Valide == false) {   
      score = score - 100;        
    }
    else if (led2Erreur == true) {   
      score = score - 100;             
    }
    digitalWrite(pinLed2, LOW);       
    led2Allume = false;              
    led2Erreur = false;            
  }


  ////////////////////////////  ON GERE LE BOUTON  ////////////////////////////////////////////

  if (etatBouton2 == 0 && led2Allume == false && currentMillis - previousMillis <= 3000 && led2Erreur == false) {          
    score = score - 100;
    led2Valide = false;                                                                                                   
    led2Erreur = true;                                                                                                     

  }
  else if (etatBouton2 == 0 && led2Allume == true && currentMillis - previousMillis <= 3000) {                              
    digitalWrite(pinLed2, LOW);                                                                                             
    led2Allume = false;                                                                                                    
    led2Valide = true;                                                                                                     
    led2Erreur = false;                                                                                                  

  }

  ///////////////////////////////////// 4ème lumière//////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////

  etatlumiere3 = random(0, 2000);       // L'etat de la lumière est définit de façon random par des chiffres de 0 à 2000
  //Serial.println (etatlumiere3);
  // unsigned long currentMillis = millis();  // on compte le temps qui s'est écoulé depuis le début du programme juqu'ici
  etatBouton3 = digitalRead(pinBouton3);
  // Serial.println(etatBouton3);


  if (etatlumiere3 == 0 && led3Allume == false) {  
    digitalWrite(pinLed3, HIGH);                 
    previousMillis = currentMillis;             
    led3Allume = true;                        
    led3Erreur = false;                         
    led3Valide = false;                        
  }


  ////////////////////////////  ON GERE LES POINTS  ////////////////////////////////////////////

  else if (currentMillis - previousMillis >= 3000 && led3Allume == true ) {   
    if (led3Valide == false) {
      score = score - 100;         
    }
    else if (led3Erreur == true) {    
      score = score - 100;            
    }
    digitalWrite(pinLed3, LOW);       
    led3Allume = false;              
    led3Erreur = false;           
  }


  ////////////////////////////  ON GERE LE BOUTON  ////////////////////////////////////////////

  if (etatBouton3 == 0 && led3Allume == false && currentMillis - previousMillis <= 3000 && led3Erreur == false) {           
    score = score - 100;
    led3Valide = false;                                                                                                    
    led3Erreur = true;                                                                                                     

  }
  else if (etatBouton3 == 0 && led3Allume == true && currentMillis - previousMillis <= 3000) {                              
    digitalWrite(pinLed3, LOW);                                                                                             
    led3Allume = false;                                                                                                   
    led3Valide = true;                                                                                                    
    led3Erreur = false;                                                                                                   

  }

  ///////////////////////////////////// 5ème lumière//////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////

  etatlumiere4 = random(0, 2000);       // L'etat de la lumière est définit de façon random par des chiffres de 0 à 2000
  //Serial.println (etatlumiere4);
  // unsigned long currentMillis = millis();  // on compte le temps qui s'est écoulé depuis le début du programme juqu'ici
  etatanalogPin = digitalRead(analogPin);
  //Serial.println(etatanalogPin);


  if (etatlumiere4 == 0 && led4Allume == false) {  
    digitalWrite(pinLed4, HIGH);                
    previousMillis = currentMillis;             
    led4Allume = true;                          
    led4Erreur = false;                        
    led4Valide = false;                        
  }


  ////////////////////////////  ON GERE LES POINTS  ////////////////////////////////////////////

  else if (currentMillis - previousMillis >= 3000 && led4Allume == true ) {   
    if (led4Valide == false) {  
      score = score - 100;         
    }
    else if (led4Erreur == true) {    
      score = score - 100;             
    }
    digitalWrite(pinLed4, LOW);       
    led4Allume = false;              
    led4Erreur = false;            
  }


  ////////////////////////////  ON GERE LE BOUTON  ////////////////////////////////////////////

  if (etatanalogPin == 0 && led4Allume == false && currentMillis - previousMillis <= 3000 && led4Erreur == false) {          
    score = score - 100;
    led4Valide = false;                                                                                                    
    led4Erreur = true;                                                                                                   

  }
  else if (etatanalogPin == 0 && led4Allume == true && currentMillis - previousMillis <= 3000) {                              
    digitalWrite(pinLed4, LOW); // alors la lumière s'éteind
    led4Allume = false;                                                                                                 
    led4Valide = true;                                                                                                     
    led4Erreur = false;                                                                                                  

  }

  
  ///////////////////////////////// jauge lumineuse ////////////////
  
  pixels.clear(); // Set all pixel colors to 'off'
  int nPixel = map(score, 0, 1200, 0, NUMPIXELS + 1);       // On déclare une variable qui transforme le score de 0 à 1200 en 0 pixel à 6 pixels +1
  for (int i = 0; i < nPixel; i++) {
    if (nPixel < 2) {                                        // si le nombre de pixels est plus petit que 2 alors les pixels deviennent rouge                
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    } else {                                                 // Sinon ils sont verts
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));          
    }
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

  
  
  ////////////////////////////////  score //////////////////////////
  
  Serial.print("chrono : ");
  Serial.println(score);

  if (score <= 0) {                               // Si la jauge est plus petit ou égale à 0
    afficheur.clear();                            // l'afficheur s'arrête
    afficheur.print("score");                      // l'afficheur affiche le chrono
    delay(1000);
    afficheur.clear();
    afficheur.print(chrono);                     // l'afficheur affiche le chrono optenu
    afficheur.blink();} 
  etatboutonPlay = digitalRead(boutonPlay);
 Serial.println(boutonPlay);
  
     if (etatboutonPlay == 0){             // si on appuie sur le bouton play 
    delay(5000);                           // après un délait de 5000 millisecondes
    digitalWrite(pinLedlampe, HIGH);       //  la lampe s'allume
    score = 1200  ;                        // la jauge se remet à 1200
    nouvelle_partie = true;                // une nouvelle partie peut commencer
   
  }

  
}


// value = digitalRead(pinBouton);
//Serial.println(value);
