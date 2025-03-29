# STATTRACK-Airsoft
Module de comptage de touche pour réplique Airsoft 

# Materiel 

[Arduino Nano](https://fr.aliexpress.com/item/1005007342237827.html?spm=a2g0o.order_list.order_list_main.292.3e6e5e5bb49QwX&gatewayAdapt=glo2fra)

[Exemple of Digit](https://fr.aliexpress.com/item/1005001582129952.html?spm=a2g0o.order_list.order_list_main.312.3e6e5e5bb49QwX&gatewayAdapt=glo2fra)

[Exemple of button](https://fr.aliexpress.com/item/1005007571293510.html?spm=a2g0o.order_list.order_list_main.342.3e6e5e5bb49QwX&gatewayAdapt=glo2fra)

[Plate 5*7](https://fr.aliexpress.com/item/1005007204340724.html?spm=a2g0o.order_list.order_list_main.298.3e6e5e5bb49QwX&gatewayAdapt=glo2fra)

[EEPROM AT24C256](https://fr.aliexpress.com/item/1005005676146387.html?spm=a2g0o.order_list.order_list_main.378.5a945e5bvdvnk7&gatewayAdapt=glo2fra)

# Assembly

## Connect Arduino Nano

### Afficheur LED 6 Digits
| Arduino Nano | Afficheur LED |
|-------------|----------------|
| VCC         | VCC            |
| GND         | GND            |
| D4          | DIO            |
| D5          | CLK            |

### EEPROM
| Arduino Nano | EEPROM |
|-------------|---------|
| 5V          | VCC     |
| GND         | GND     |
| A5          | SCL     |
| A4          | SDA     |

### Bouton
| Arduino Nano | Bouton |
|--------------|--------|
| D3           | NO     |
| GND          | NO     |


## Schéma 
![Design sans titre](https://github.com/user-attachments/assets/41ad3ab9-1eee-4093-afb0-9d0807e0a535)


## STL 


# Program

StattrackSimple.ino is just simple, save the kill on the eeprom and add kill with the button. 

StattrackAvecReset.ino add an shunt on the D6 for the reset, make this before plug the arduino, and after the shunt is done, wait 5 second. 

StattrackResetSameButton.ino is same but just press the button 6 seconde for reset. 


# Arduino Prog 

Make sur you select the old ATmega328P(OLD) for the arduino on the tuto : 

<img width="355" alt="Capture d’écran 2025-03-29 à 14 30 21" src="https://github.com/user-attachments/assets/55b3b2f2-a092-421a-afdd-3cb774ebffc3" />


# Futur update 

New features with some menu 

Add battery on the tuto (in progress) 


