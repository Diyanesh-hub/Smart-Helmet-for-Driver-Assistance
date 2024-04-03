#include <SoftwareSerial.h>

int const gas_sen = A1;
int gas_value;
int green = 11;

int photoresistor= A3;		
int led2 =4;

int but = 0;

const int sensorpin = A2;
int wet = 700;
int sensor;

// Define SoftwareSerial object
SoftwareSerial espSerial(5, 6); // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600); // Initialize SoftwareSerial with the baud rate of ESP8266
  pinMode(led2, OUTPUT);	//setting pinmode as output
  pinMode(photoresistor, INPUT);
  pinMode(green, OUTPUT);
  pinMode(2, INPUT);
  pinMode(12, OUTPUT);
}

void loop() {

  sensor = analogRead(sensorpin);
  Serial.println(sensor);

  but = digitalRead(2); 
  
  if(but == HIGH)
  {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }

  if ( digitalRead(photoresistor) ==0)	//reading light intensity
  {
    digitalWrite(led2, 1);
  	delay(500);
    digitalWrite(led2, 0);
  	delay(500);
    
  }
   else
      digitalWrite(led2, 0);
    
  gas_value = analogRead(gas_sen);
  gas_value = map(gas_value, 80, 300, 0, 100);

  // Print gas_value to Arduino's serial monitor
  Serial.print("Gas value.: ");
  Serial.println(gas_value);
  digitalWrite(green,gas_value>=140 ? HIGH : LOW);

  // Send gas_value to ESP8266
  espSerial.print(gas_value); // Send the integer value directly
  
  delay(2500); // delay to avoid flooding the ESP8266 with data
}
