/**************************************************************************
 *                          STATTRACK Airsoft V1                          *
 *------------------------------------------------------------------------*
 * Auteur  : Bulbicrave                                                   *
 * Date    : 19/03/2025                                                   *
 * Matériel: Arduino Nano                                                 *
 */const int Version = 0.1;                                              /*
 *------------------------------------------------------------------------*
 * Description :                                                          *
 * Ce programme permet de suivre les statistiques d'une partie d'airsoft  *
 * en affichant diverses informations                                     *
 *                                                                        *
 *------------------------------------------------------------------------*
 * Licence : CopyrAithe                                                   *
 * Vous êtes libre d'utiliser, modifier et partager ce code à des fins    *
 * personnelles et éducatives. Toute utilisation commerciale nécessite    *
 * une autorisation explicite de l'auteur.                                *
 **************************************************************************/

// Bibliothèque / Library
#include <Arduino.h>
#include <TM1637TinyDisplay6.h>
#include <AT24C256.h>

// Module connection pins (Digital Pins) TM1637
#define CLK 4
#define DIO 5

const int BAug = 2;  // Boutton pour incrémenter
int kill; 

//Init Eeprom and 6digit
TM1637TinyDisplay6 display(CLK, DIO);
AT24C256 eeprom(0x50);

char eepromdata[30];

unsigned long lastPressTime = 0;  // Temps du dernier appui
bool waitingSecondPress = false;  // Indique si on attend un second appui
const unsigned long doublePressDelay = 500; // Temps max entre 2 appuis (500ms)

volatile bool flag = false; // Drapeau d'interruption


bool inMenu = false; // Indique si on est dans le menu
int menuPage = 0; // Page actuelle du menu
const int maxPages = 3; // Nombre de pages du menu
  

void setup() {

  display.begin();
  Serial.begin(9600);

  pinMode(BAug, INPUT_PULLUP); // connection sans resistance, GND to 2
  attachInterrupt(digitalPinToInterrupt(BAug), onEvent, CHANGE); // Bouton en mode interrupt

  Serial.println("Start Init");
  eeprom.read(0, eepromdata, sizeof(eepromdata));

  if(eepromdata != NULL)
  {
    kill = eepromdata;
  }
  else kill = 0;

  display.showNumber(kill);

}


void loop() {
  
if (flag) {
    flag = false;
    
    unsigned long currentTime = millis();

    if (waitingSecondPress && (currentTime - lastPressTime <= doublePressDelay)) {
      // ➡️ Double appui détecté
      if (inMenu) {
        // Quitter le menu
        Serial.println("Sortie du menu !");
        inMenu = false;
        display.showNumber(kill); // Revenir à l'affichage normal
      } else {
        // Entrer dans le menu
        Serial.println("Entrée dans le menu !");
        inMenu = true;
        menuPage = 0; // Réinitialiser à la première page
        showMenuPage();
      }
      waitingSecondPress = false;
    } 
    else {
      // ➡️ Premier appui, on attend un second
      waitingSecondPress = true;
      lastPressTime = currentTime;
    }
  }

  // Si on attend un second appui mais qu'il ne vient pas à temps
  if (waitingSecondPress && (millis() - lastPressTime > doublePressDelay)) {
    waitingSecondPress = false;

    if (inMenu) {
      // ➡️ Navigation dans le menu
      menuPage = (menuPage + 1) % maxPages;
      showMenuPage();
    } else {

      kill++;
      display.showNumber(kill);
      eeprom.write(0, (uint8_t*)&kill, sizeof(kill));

    }
  }
}

// Fonction pour afficher les pages du menu
void showMenuPage() {
  switch (menuPage) {
    case 0:
      display.showString("PAGE1");
      break;
    case 1:
      display.showString("RESET");
      delay(500);
      break;
    case 2:
      display.showString("VERS");
      delay(500);
      display.showString(Version);
      delay(500);
      break;
  }
}

void onEvent() {
  flag = true; // Déclenche une mise à jour dans loop()
}