#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "changethis";
const char* pwd = "changethis";
int led = 2;
int currentStatus = LOW;
long currentMillis = 0;
long millibegin = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("connecting...");
  }
  Serial.println("Connected to network");
  // put your setup code here, to run once:
  millibegin = millis();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED)
  {
    return ;
  }

  currentMillis = millis();

  if(currentMillis - millibegin < 6000) //delay(6000) simulator
  {
    return ;
  }
  else
  {
    millibegin = currentMillis; //new begin time to cmpare the next 6 seconds
  }
  

  HTTPClient http;
  WiFiClient client;
  String payload;
  http.begin(client, "changethis");
  int httpCode = http.GET();
  if(httpCode >0)
  {
    payload = http.getString();
  }
  http.end();
  Serial.println(payload);

  if(payload == "false" && currentStatus != HIGH)
  {
    digitalWrite(led, HIGH);
    currentStatus = HIGH;
    Serial.println("switched off");
  }
  if(payload == "true" && currentStatus != LOW)
  {
    digitalWrite(led, LOW);
    currentStatus = LOW;
    Serial.println("Switched on");
  }

}
