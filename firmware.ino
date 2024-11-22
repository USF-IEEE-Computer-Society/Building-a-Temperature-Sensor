// Created by Liam Osman for IEEE-CS TechX Florida 11/22/24

// Include a sensor library for DHT11
// This one was created by Scott Piette
// Remember to "Include in Project"
#include <PietteTech_DHT.h>

// Constant Declarations
#define DHT_TYPE            DHT11             
#define DHT_PIN             A1
#define DHT_SAMPLE_INTERVAL 2000

// Instantiate a DHT sensor object of our type
PietteTech_DHT DHT(DHT_PIN, DHT_TYPE, dht_wrapper);
// DHT wrapper function necessary for object
void dht_wrapper() { DHT.isrCallback(); }

// Declare variables on board memory
double temperature = 0;
double humidity = 0;

// Setup runs only once when board is started 
void setup() {
    
    // Connects variables to Particle cloud data
    Particle.variable("humidity", humidity);
    Particle.variable("temperature", temperature);

    // Starts our sensor object behavior
    DHT.begin();
}

// Runs forever while device is on
void loop() {

    // DHT sensor can only acquire new value
    // once every interval, so this prevents
    // updating every loop cycle of device
    if (!DHT.acquiring()) {

        // update variables with methods
        humidity = DHT.getHumidity();
        temperature = DHT.readTemperature();
  }
}
