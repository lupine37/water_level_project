#include <ESP8266WiFi.h>


const int port = 8888;
const IPAddress server(192, 168, 1, 145);
WiFiClient client;
const char *ssid = "MW40VD_19E7_EXT";
const char *password = "Cazp2x6U7t3A9jXg";

void writeString(String stringData){
  client.write(" ");
  for (int i = 0; i < stringData.length(); i++) {
    client.write(stringData[i]);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if(client.connect(server, port)){
    Serial.println("Client connected");
  }
  else {
    Serial.println("No connection");
    delay(500);
    return;
  }
  while(client.connected()){
    while(Serial.available() > 0) {
      client.write(Serial.read());
    }
    while(client.available() > 0) {
      char c = client.read();
      Serial.print(c);
    }
    delay(10);
  }

}
