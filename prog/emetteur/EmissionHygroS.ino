//Insertion des bibliothèques
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>


//Définition des broches CSN et CE du module nRF24
#define PIN_CS 10
#define PIN_CE 9

RF24 radio(PIN_CE,PIN_CS);

int PinGrove = A0; //Broche du capteur Grove

const uint64_t addrCanal = 0xF0F0F0F0C6; // adresse du canal d'émission

int pinPluvio = 3; //Broche du capteur 
int impulsion = 2;
int compt = 0;
unsigned long int pluvio;





void setup() {
  Serial.begin(9600);

attachInterrupt(digitalPinToInterrupt(pinPluvio),comptage,RISING); //IRQ 0 sur la broche 3
//Initialistion de l'émission radio  
  Serial.println(F("Debut transmission  "));
  radio.begin();
  radio.setPALevel(RF24_PA_LOW); //RF24_PA_HIGH consome trop de courant
  radio.openWritingPipe(addrCanal);
}


void loop() {
  
  Serial.println(F("Envoi  :"));
  Serial.println("     ");
   unsigned long int pluvio ;//valeur de pluviométrie
  Serial.print("impulsion=");
  Serial.println(compt/impulsion) ;

  delay(1000) ;
  pluvio= (compt/impulsion)*0.2794 ;
  Serial.print("pluviometrie(mm)=");
  Serial.println(pluvio);

  
//Stockage des valeurs dans les variables 
  unsigned long int Cte3 = 300000 ;

 

delay(500);
 

//Luminosité
    pluvio = pluvio + Cte3;
    radio.write(&pluvio, sizeof(unsigned long int) );
      Serial.print("Pluviometrie : ");Serial.print(pluvio); Serial.print("  ");
      Serial.print(pluvio - Cte3);
      Serial.println("  mm");
      Serial.println("       ");
delay(500);
}
void comptage(){

compt ++ ;
delay(1000);
  }

