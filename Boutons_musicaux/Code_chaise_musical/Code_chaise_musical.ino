#include <Adafruit_NeoPixel.h> // downoald it !
#include <Arduino.h>
#include <time.h>
#include <stdlib.h>

/*
 * Gestion du temps et des valeurs
 */
#define TIME_BETWEEN_GAMES 2500
#define TIME_BETWEEN_ROUNDS 3000
#define TIME_SHOW_LOOSER 3000
#define TIME_SHOW_WINNER 4000
#define FLASH_COUNT 5
#define FLASH_INTERVAL 300


/*
 * MUSIQUE
 */
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698

//Pin du piezo Buzzer
int pinMusique = 5;

//durée en milliseconde pour chaque note (dans l'ordre) TOTAL 14000
int princesseDesNeigesRytm[] = {
		250, 250, 1500, 250, 250, 750,
		250, 250, 750, 250, 750,
		250, 750,
		250, 250, 1500, 250, 250, 250, 250, 750,
		250, 250, 750, 750, 500, 500, 750, 0
};
int totalTimeSound = 14000;

//Note à jouer (dans l'ordre)
int princesseDesNeigesNote[] = {
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_G4, NOTE_G4, NOTE_D5,
		NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4,
		NOTE_B4, NOTE_C5,
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_G4, NOTE_G4, NOTE_E5, NOTE_E5, NOTE_D5,
		NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_C5, 0
};

/*
 * LEDS
 */
#define BROCHE_LED   2
#define NUM_PIXELS    24

#define DELAY_LED 80

// Couleur des leds Rose
#define COLOR_RED 255
#define COLOR_GREEN 0
#define COLOR_BLUE 184
#define COLOR_OFF 0
// Créer l'objet :
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, BROCHE_LED,
                                             NEO_GRB + NEO_KHZ800); // NOLINT(hicpp-signed-bitwise)


/*
 * BUTTONS
 */

int numberButtons = 4;
int pinBouton = 8;
int pinBouton2 = 9;
int pinBouton3 = 10;
int pinBouton4 = 11; // 0 off & 1 up

#define BUTTON_DOWN 0


void setup() {
	srand(time(NULL));   // Initialization, random .
	pinMode(13, OUTPUT);
	pixels.begin(); // init pixels
	pixels.setBrightness(55); // pixels led luminosity to 55

	Serial.begin(9600); // serial output
}

/**
 * turn led and sound off
 */
void clearLedAndSound() {
	for (int i = 0; i < NUM_PIXELS; i++)
		pixels.setPixelColor(i, pixels.Color(COLOR_OFF, COLOR_OFF, COLOR_OFF)); // hide the led
	pixels.show();
	noTone(pinMusique);
}

/**
 * Presser le bouton master pour commencer le jeu.
 */
void phase1() {
	Serial.println("debut phase 1");
	// turn on led to wait
	for (int i = 0; i < NUM_PIXELS; i += 2)
		pixels.setPixelColor(i, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE)); // hide the led
	pixels.show();
	while (digitalRead(pinBouton) == BUTTON_DOWN); //tant que le bouton est down...
	//button 1 est le chef, il dit quand la partie commence (bouton commande)

	clearLedAndSound();
}

/**
 * temps passé entre le point from et toi
 * @param from
 * @param to
 * @return temps passé
 */
int getElapsedTime(int from, int to) {
	return to - from;
}

void announce() {

	for (int i = 0; i < NUM_PIXELS; i++) { //prépare le décompte
		pixels.setPixelColor(i, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE));
	}

	pixels.show();

	for (int i = NUM_PIXELS; i >= 0; i--) { // fait le décompte
		pixels.setPixelColor(i, pixels.Color(COLOR_OFF, COLOR_OFF, COLOR_OFF));
		delay(TIME_BETWEEN_ROUNDS / NUM_PIXELS);
		pixels.show();
	}
}

void phase2() {
	Serial.println("debut phase 2");
	announce();
	//calcul de la durée du round
	int time = (rand() % 10 + 5) * 1000; //entre 5 et 10s

	//lecture son et led
	int timestamp = millis();
	int timestampLastNote = millis();
	int note = 0;
	int led = -1;

	while (getElapsedTime(timestamp, millis()) < time) {
		int currentTimeLed = (getElapsedTime(timestamp, millis())) % (DELAY_LED * NUM_PIXELS);

		int nextNoteTimer = princesseDesNeigesNote[note];

		// test led
		int ledNumberCheck = currentTimeLed / DELAY_LED;

		//est-ce que l'on doit allumer la led suivante et éteindre l'actuelle ?
		if (ledNumberCheck != led) { // on est pas sur la même session d'allumage
			// on
			pixels.setPixelColor(led, pixels.Color(COLOR_OFF, COLOR_OFF, COLOR_OFF));
			led++;
			led = led % NUM_PIXELS; //ne pas dépasser la base
			pixels.setPixelColor(led, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE));
			pixels.show();
		}

		//test note
		//est-ce que l'on doit passer à la note suivante
		if (nextNoteTimer < getElapsedTime(timestampLastNote, millis())) {
			noTone(pinMusique);
			timestampLastNote = millis(); // reset the value to start the next one
			note++;
			if (princesseDesNeigesNote[note] == 0) note = 0; // reset ne pas sortir de l'array OBE
			tone(pinMusique, princesseDesNeigesNote[note], princesseDesNeigesRytm[note]);
		}
	}
	noTone(pinMusique);
//	pixels.setPixelColor((led- 1) % NUM_PIXELS, pixels.Color(COLOR_OFF, COLOR_OFF, COLOR_OFF));
	pixels.setPixelColor(led, pixels.Color(COLOR_OFF, COLOR_OFF, COLOR_OFF));

}

void phase3() {
	Serial.println("debut phase 3");
	clearLedAndSound();
}

int phase4(int playersCounter, int buzzers[]) {
	int buzzerBuzzed = 0;
	bool buzzedArray[playersCounter];

	// init array
	for (int i = 0; i < playersCounter; i++) {
		buzzedArray[i] = false; // n'a pas été buzzé
	}

	while (buzzerBuzzed < playersCounter - 1) { // phase de pression du buzzer
		for (int i = 0; i < playersCounter; i++) {
			if (digitalRead(buzzers[i]) == 1 &&
			    buzzerBuzzed < playersCounter - 1
			    && buzzedArray[i] != true) {
				// Le buzzer du joueur i a été pressé et on a pas atteint la limite et il ne l'a jamais.
				Serial.print("RECEPTION BUZZER: ");
				Serial.println(buzzers[i]);
				buzzedArray[i] = true; // Set dans les buzzers buzzé celui du joueur actuel
				buzzerBuzzed++; // incrémentation du compteur
			}
		}
	}

	// Qui est le perdant, analyse
	for (int i = 0; i < playersCounter; i++) {
		if (buzzedArray[i] == false) return i;
	}
}

void displayLooser(int buzzers[], int index) {
	Serial.print("Looser Pin: ");
	Serial.println(buzzers[index]);

	// turn on led for the looser corresponding
	int looser = buzzers[index] - pinBouton + 1;
	for (int i = 0; i < looser; i++)
		pixels.setPixelColor(i, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE));
	pixels.show();
	delay(TIME_SHOW_LOOSER);
	for (int i = 0; i < looser; i++)
		pixels.setPixelColor(i, pixels.Color(COLOR_OFF, COLOR_OFF, COLOR_OFF)); // hide the led
	pixels.show();
}

/**
 * annonce le buzzer gagnant
 * @param buzzers array
 */
void announceWinner(int buzzers[]) {
	Serial.print("Winner Pin: ");
	Serial.println(buzzers[0]);

	for (int i = 0;
	     i < FLASH_COUNT; i++) { // flash les leds pour annoncer que la partie est finie et désigner le vainqueur
		for (int j = 0; j < NUM_PIXELS; j++) {
			pixels.setPixelColor(j, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE));
		}
		pixels.show();
		delay(FLASH_INTERVAL);
		clearLedAndSound();
		delay(FLASH_INTERVAL);
	}

	int winner = buzzers[0] - pinBouton + 1; // buzzer gagnant - 8 + 1
	for (int i = 0; i < winner; i++) // annonce les leds gagnates
		pixels.setPixelColor(i, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE));
	pixels.show();
	delay(TIME_SHOW_WINNER);
	for (int i = 0; i < winner; i++)
		pixels.setPixelColor(i, pixels.Color(COLOR_OFF, COLOR_OFF, COLOR_OFF)); // hide the led
	pixels.show();

	delay(TIME_BETWEEN_GAMES);

}

void loop() {
	// 1. start a game on press
	phase1();
	Serial.println("fin de la phase 1");
	int buzzers[] = {pinBouton, pinBouton2, pinBouton3, pinBouton4};
	int playersCounter = numberButtons;
	while (playersCounter > 1) {
		// 2. LED + music ON - READ FUNCTION
		phase2();
		// 3. shutdown sound & leds
		phase3();
		// 4. last buzzer loose + LED on - remove a buzzer from the array (list)
		int looserIndex = phase4(playersCounter, buzzers);

		// 5. disable the looser cf 4
		// buzzers = phase5();
		displayLooser(buzzers, looserIndex);
		playersCounter--; // reduction du nombre de joueurs
		for (int i = 0; i < playersCounter; i++) { //recopie des valeurs qui doivent être décalée
			/* if (i < looserIndex) { // NOLINT(bugprone-branch-clone)
				buzzers[i] = buzzers[i]
			} else */ //Debug infos
			if (i >= looserIndex) {
				buzzers[i] = buzzers[i + 1]; //décaler a gauche les éléments
			}
		}
	}
	announceWinner(buzzers);
}

#pragma clang diagnostic pop