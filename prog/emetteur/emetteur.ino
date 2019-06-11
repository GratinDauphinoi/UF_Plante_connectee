#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

#define PIN_CS 10
#define PIN_CE 9

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

RF24 radio(PIN_CE,PIN_CS);

int PinGrove = A0; //Broche du capteur Grove
int humidite = 0; //Valeur de l'humidité
const uint64_t pipeA = 0xF0F0F0F0C6LL; // adresse canal luminosité



void configureSensor(void) {
  tsl.enableAutoRange(true); // Gain automatique

  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);// Vitesse et résolution moyenne
}

void setup() {
  Serial.begin(9600);
  tsl.begin();

  if(!tsl.begin()) {
    Serial.print("Aucun capteur detecte ");
    while(1);
  }

  configureSensor();
  
  Serial.println(F("Debut transmission  "));
  radio.begin();

  radio.openWritingPipe(pipeA);
}

void loop() {
  
  Serial.println(F("Envoi  :"));
  sensors_event_t event;
  tsl.getEvent(&event);
  
  unsigned long humidite = analogRead(PinGrove);//valeur de l'humidité


  unsigned long luminosite = event.light; //valeur de la luminosité
  
  // début envoi
//Humidité
  if(!radio.write(&humidite, sizeof(unsigned long) )){
    Serial.println(F("Aucune donnée Hygrometrique !"));    
  }
  else { 
    radio.write(&humidite, sizeof(unsigned long) );
      Serial.print("Humidite : ");
      Serial.println(humidite);
  }

//Luminosité
  if(!radio.write(&luminosite, sizeof(unsigned long) )){
    Serial.println(F("Aucune lumiere !"));
  }
  else {
    radio.write(&luminosite, sizeof(unsigned long) );
      Serial.print("Luminosite : ");
      Serial.print(luminosite);
      Serial.println("  lux");
  }
}

