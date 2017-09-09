// Peoria HamFest Arduino demo by KG9DW 09/2017
// This demo uses a OneWire temperature probe (DS18B20) and 3 LEDs to demonstrate basic concepts.
// When temperature rises above set thresholds, the LEDs will light.
// Code shows the basic If This Then That (IFTT) functionality.
// This code relies on the modified OneWire library from Josh.com.
// See: https://wp.josh.com/2014/06/23/no-external-pull-up-needed-for-ds18b20-temp-sensor/

#include <OneWire.h>
#include <DallasTemperature.h>

// OneWire data wire is plugged into port 7 on the Arduino
#define ONE_WIRE_BUS 7
#define TEMPERATURE_PRECISION 9

// Define the LED pins and thresholds
#define RED_LED_PIN 8
#define RED_LED_TEMP 90.0

#define YEL_LED_PIN 9
#define YEL_LED_TEMP 80.0

#define GRE_LED_PIN 10
#define GRE_LED_TEMP 70.0


// Setup oneWire instance to communicate with any OneWire devices 
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Setup - runs once
void setup(void)
{

  // initialize LEDs as output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YEL_LED_PIN, OUTPUT);
  pinMode(GRE_LED_PIN, OUTPUT);
  
  // start serial port
  Serial.begin(9600);
  Serial.println("Peoria Hamfest Arduino Demo de KG9DW"); 

  // Test the lights
  digitalWrite(LED_BUILTIN, HIGH);
  delay(750);
  digitalWrite(GRE_LED_PIN, HIGH);
  delay(750);
  digitalWrite(YEL_LED_PIN, HIGH);
  delay(750);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(750);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YEL_LED_PIN, LOW);
  digitalWrite(GRE_LED_PIN, LOW);
  delay(750);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(YEL_LED_PIN, HIGH);
  digitalWrite(GRE_LED_PIN, HIGH);
  delay(1000);  

  // turn off the lights
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YEL_LED_PIN, LOW);
  digitalWrite(GRE_LED_PIN, LOW);
  
  // initialize the sensor
  sensors.begin();

}

// Main loop - runs over and over
void loop(void)
{ 
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on so we know we're running
  
  // Address of temp sensor found
  DeviceAddress tempDeviceAddress; 

  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Search the wire for address
  if(sensors.getAddress(tempDeviceAddress, 0))
  {
      float tempC = sensors.getTempC(tempDeviceAddress);
      float tempF = DallasTemperature::toFahrenheit(tempC); // Converts tempC to Fahrenheit

      Serial.println(tempF);
      if (tempF > RED_LED_TEMP) {
        Serial.println("Above red temp");
        digitalWrite(RED_LED_PIN, HIGH);
      } else {
        digitalWrite(RED_LED_PIN, LOW);
      }

      if (tempF > YEL_LED_TEMP) {
        Serial.println("Above yellow temp");
        digitalWrite(YEL_LED_PIN, HIGH);
      } else {
        digitalWrite(YEL_LED_PIN, LOW);
      }

      if (tempF > GRE_LED_TEMP) {
        Serial.println("Above green temp");
        digitalWrite(GRE_LED_PIN, HIGH);
      } else {
        digitalWrite(GRE_LED_PIN, LOW);
      }

  } 
	
	digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
  delay(1500);
}

