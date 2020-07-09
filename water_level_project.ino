#include <SoftwareSerial.h>

SoftwareSerial esp8266(2, 3);

#define RELAY 10
const int trigPin = 8;
const int echoPin = 9;

long duration;
int volume;
unsigned long initialTime = 0;
unsigned long finalTime = 1000;

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
  Serial.begin(9600);
  esp8266.begin(115200);
  digitalWrite(RELAY, HIGH);
  initialTime = millis();

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
  if(duration != 0){
    volume = 1696.46 -(0.034 * float(duration / 2) * (22 / 7) * sq(6));
  }
  Serial.print("mililitres: ");
  Serial.println(volume);
  delay(1000);
  if (volume <=350) {
    Serial.println("WATER IS EMPTY");
    digitalWrite(RELAY, LOW);
  }
  else if (volume >= 1300) {
    Serial.println("WATER IS FULL");
    digitalWrite(RELAY, HIGH);
  }
  if (((millis() - initialTime) > finalTime)) {
    String vol = String(volume);
    writeString(vol);
    initialTime = millis();
  }
}
