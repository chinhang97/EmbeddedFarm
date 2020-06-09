#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  //initialize lcd address
#define DHTTYPE DHT11   // DHT 11

const int AirQPin = A0;       //sensors pins
const int DHTPin = 2;
const int WaterPin = A2;
const int LightPin = A3;

int show;
DHT dht(DHTPin, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  int error;
  pinMode(WaterPin, INPUT);       //initialize all sensor pins
  pinMode(LightPin, INPUT);
  pinMode(AirQPin, INPUT);

  
  Serial.begin(74880);               //define baud rate
  Serial.println("LCD...");
  Wire.begin();
  Wire.beginTransmission(0x27);      //start i2c communication
  error = Wire.endTransmission();
  if (error == 0) {
    Serial.println(": LCD found.");
 
  } else {
    Serial.println(": LCD not found.");
  } // if
 
  lcd.begin(16, 2);                 // initialize the lcd
  show = 0;
}

void loop() {
  
    float h = dht.readHumidity();       // Read humidity
     
    float t = dht.readTemperature();    // Read temperature
    
    //float f = dht.readTemperature(true);

    float water =analogRead(WaterPin);    //Read water level
    float light =analogRead(LightPin);    //Read light intensity level
    float air =analogRead(AirQPin);       //Read air quality level


    lcd.setBacklight(255);              //display sensor data on LCD
    lcd.home(); lcd.clear();
    lcd.print("Humidity: ");
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("*C");
    delay(1000);

    lcd.home(); lcd.clear();
    lcd.print("Moisture: ");
    lcd.print(water);
    lcd.setCursor(0,1);
    lcd.print("Air: ");
    lcd.print(air);

    delay(1000);
    
    lcd.home(); lcd.clear();
    lcd.print("Light : ");
    lcd.print(light);
    lcd.print("lx");

    delay(1000);
    

    Serial.print(h);          //send sensor data to nodeMCU
    Serial.print(",");

    Serial.print(t);
    Serial.print(",");

    Serial.print(water);
    Serial.print(",");

    Serial.print(air);
    Serial.print(",");
    
    Serial.println(light);
    delay(1000);


}
