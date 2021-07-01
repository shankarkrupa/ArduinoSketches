#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "<changethis>";
const char* pwd = "<changethis>";
int led = 2;
int currentStatus = LOW;
unsigned long currentMillis = 0;
unsigned long millibegin = 0;

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
   // Serial.println("Running ");
    //Serial.println("Wait for " + (currentMillis - millibegin));
    return ;
  }
  else
  {
    millibegin = currentMillis; //new begin time to cmpare the next 6 seconds
  }
  //Serial.println("completed six seconds...");

  HTTPClient http;
  WiFiClient client;
  String payload;
  http.begin(client, "<url>");
  int httpCode = http.GET();
  if(httpCode >0)
  {
    payload = http.getString();
  }
  http.end();
  Serial.println(payload);

  if(payload == "false" && currentStatus != HIGH)
  {
   //Serial.println("false condition met and current status is high");
    digitalWrite(led, HIGH);
    currentStatus = HIGH;
    Serial.println("switched off");
  }
  if(payload == "true" && currentStatus != LOW)
  {
    //Serial.println("true condition and currentstatus is not low");
    digitalWrite(led, LOW);
    currentStatus = LOW;
    Serial.println("Switched on");
  }
}
