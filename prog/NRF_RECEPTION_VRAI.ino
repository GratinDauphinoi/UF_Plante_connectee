#include <SPI.h> // librairie pour controler le bus SPI
#include <RF24.h> // librairie pour controler le module RF24
#define PIN_CS 10 // attribution de la broche 10 pour PIN_CS
#define PIN_CE 9 // attribution de la broche 9 pour PIN_CE
RF24 radio (PIN_CE, PIN_CS);

int pinIrqNrf24 = 2; //IRQ sur la broche 2 lance l'interruption 0


// inclusion des données et mise a 55 pour savoir si il y a une erreur
unsigned long int luminosite = 55; 
unsigned long int humidite = 55;
unsigned long int pluvio = 55;
// mise en place de l'adresse utilisée
const uint64_t addrCanal = 0xF0F0F0F0C6; 
//définition de la variable newValeur en false
boolean newValeur = false; // 
//mise en place des sorties 
const int out1 = 5;
const int out2 = 6;
const int out3 = 7;
const int out4 = 8;

void setup() {
pinMode(out1, OUTPUT);
pinMode(out2, OUTPUT);
pinMode(out3, OUTPUT);
pinMode(out4, OUTPUT);
Serial.begin(9600);
}

// début du système radio
radio.begin();

radio.setPALevel(RF24_PA_LOW); //RF24_PA_HIGH consomme trop de courant

radio.openReadingPipe(1, addrCanal); //définition de l'adresse canal 1 en lecture

//Si la broche IRQ est en état bas nous utilisons le void irqRecep
attachInterrupt(digitalPinToInterrupt(pinIrqNrf24), IRQ, LOW); 

radio.startListening(); //En lecture
  
}

void setRelay(int relay, int value)
{
  if(relay > 0 && relay < 5) digitalWrite ((relay+4),value);
}
void loop() {
   if(newValeur == true){
    // affichage des données
    Serial.print(F("Humidite : "));
    Serial.println(humidite);
    Serial.print(F("Luminosite : "));
    Serial.println(luminosite);
    Serial.print(F("Pluviometrie : "));
    Serial.println(pluvio);
    Serial.println( );
    newValeur = false;
    }
    Serial.print("Relay 1: Enabled ... ");
    delay(1000);                           // wait for a second
    setRelay(1, 1);                       // Vanne ouverte
    println("La vanne est ouverte");
    delay(1000);                         // wait for a second 
    setRelay(1, 0);                     // Vanne fermée
    println("La vanne est fermée");
    println(" ");
  }

void IRQ(){

  unsigned long int R;
  while(radio.available()){
    radio.read(&R, sizeof(unsigned long int));
    unsigned long int var = R / 100000;

    // début du switch et mise en place des 3 cases
    switch (var) {
      case 1:
        humidite = R - 100000;
        
        
      break;
        
      case 2:
        luminosite = R - 200000;
      
      break;
     
      
      case 3:
        pluvio = R- 300000;
      break;
      
      default: 
      break;
  
    }
    //Vérification de la réception
    Serial.print(F("Reception : "));
    Serial.println(R);
  }
  // Passage de newValeur en true
  newValeur = true;
}
