#include <SoftwareSerial.h>

SoftwareSerial esp8266(5, 6);

#define RELAY 9
const int trigPin = 3;
const int echoPin = 4;
const int redLedPin = 10;
const int greenLedPin = 11;


long duration;
float diameter;
float height;
float totalVol;
float volume;
unsigned long initialTime = 0, finalTime = 1000;
int ledCount;
bool ledState = LOW;

float readnumber(void){
  float num = 0;
  while (num == 0){
    while (!Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void writeString(String stringData) {
  esp8266.write(" ");
        for (int i = 0; i < stringData.length(); i++) {
                esp8266.write(stringData[i]);
        }
}

void setup() {
  pinMode(RELAY, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  Serial.begin(9600);
  esp8266.begin(115200);
  digitalWrite(RELAY, HIGH);
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  initialTime = millis();
  Serial.println("What is the diameter of the tank");
  diameter = readnumber();
  Serial.println("What is the height of the tank");
  height = readnumber();
  totalVol = (PI * sq(diameter / 2) * height);
  Serial.print("The total volume of the tank is: "); Serial.println(totalVol); Serial.print("mililitres");

}

void loop() {
  // Clear the trigPIn
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

//  Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

//  Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

//  Calculating the ml
  volume = totalVol -(0.034 * float(duration / 2) * PI * sq(diameter / 2));
    delay(100);
    if (((millis() - initialTime) > finalTime)) {
      Serial.print("mililitres: ");
      Serial.println(volume);
      String vol = String(volume);
      writeString(vol);
      initialTime = millis();
    }
    if (volume <=(totalVol / 4)) {
    // Serial.println("WATER IS EMPTY");
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(RELAY, LOW);
    }
    
    else if (volume >= (totalVol * 3 / 4)) {
      // Serial.println("WATER IS FULL");
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
      digitalWrite(RELAY, HIGH);
    }
    else {
      if(volume >= (totalVol / 2)) {
       digitalWrite(redLedPin, LOW);
       digitalWrite(greenLedPin, HIGH);
      }
      else{
        int Count;
        digitalWrite(greenLedPin, LOW);
        Count = (map(volume, (totalVol / 4), (totalVol / 2), 0, 9));
        ledCount++;
        if(ledCount >= Count) {
        ledState = !ledState;
        digitalWrite(redLedPin, ledState); 
        ledCount = 0;
        }  
      }
    }
    
}
