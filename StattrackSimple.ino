/**************************************************************************
 *                          STATTRACK Airsoft V1                          *
 *------------------------------------------------------------------------*
 * Auteur  : Bulbicrave                                                   *
 * Date    : 19/03/2025                                                   *
 * Matériel: Arduino Nano, button, Digit 7 * 6 Element                    *
 */const int Version = 1;                                                /*
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

#include <Arduino.h>
#include <TM1637TinyDisplay6.h>
#include <AT24C256.h>

// Pins pour le module TM1637
#define CLK 5
#define DIO 4
#define BOUTON 3  // Bouton sur la broche 3

int kill = 0;
uint8_t Init = 0; // Stocké sur 1 octet
volatile bool flag = false; // Drapeau pour détecter un appui

// Initialisation du display et EEPROM
TM1637TinyDisplay6 display(CLK, DIO);
AT24C256 eeprom(0x50);

void setup() {
  pinMode(BOUTON, INPUT_PULLUP); // Bouton avec pull-up interne
  attachInterrupt(digitalPinToInterrupt(BOUTON), onBoutonPress, FALLING); // Déclenche sur appui

  Serial.begin(9600);
  Serial.println("Démarrage...");

  // Lecture des valeurs en EEPROM
  eeprom.read(0, &Init, sizeof(Init));
  eeprom.read(1, (uint8_t*)&kill, sizeof(kill));

  Serial.print("Valeur Init: ");
  Serial.println(Init);
  Serial.print("Kill init: ");
  Serial.println(kill);

  // Vérification de l'initialisation
  if (Init != 1) {  
    Serial.println("Première initialisation...");
    kill = 0;
    Init = 1;
    eeprom.write(0, &Init, sizeof(Init));
    delay(10);  // Attente pour éviter des corruptions mémoire
    eeprom.write(1, (uint8_t*)&kill, sizeof(kill));
    delay(10);
  }

  display.begin();
  display.showNumber(kill);
}

void loop() {
  if (flag) {
    flag = false;

    kill++;
    Serial.print("Kill: ");
    Serial.println(kill);

    display.showNumber(kill);

    // Sauvegarde dans l'EEPROM
    eeprom.write(1, (uint8_t*)&kill, sizeof(kill));
    delay(10);
  }
}

// Fonction appelée lors d'un appui sur le bouton
void onBoutonPress() {
  static unsigned long lastPress = 0;
  unsigned long now = millis();

  if (now - lastPress > 50) { // Anti-rebond logiciel
    flag = true;
  }
  lastPress = now;
}
