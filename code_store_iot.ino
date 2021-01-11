#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Servo.h>

int photoSensor;
int windSpeed;

Servo myServo;
int isOpen=0;

const char *ssid = "AliceWifi";
const char *pass = "MonMdp";

String apiKey = "6beifefhfb657773934y3bfr7492"
String city = "Paris";
String country = "FR";

void setup() {
  myServo.attach(2); //2 = D4
  pinMode(6, INPUT); //12 = A0

  Serial.begin(9600);

  Wifi.begin(ssid, password);
  Sreial.print("Connecting to ");
  Serial.println(ssid);

  while(WiFi.status() != WL_CONNECTED {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected")
}

void loop() {
  if (WiFi.status()==WL_CONNECTED) {
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&APPID" + apiKey;

    jsonBuffer = httpGETRequest (serverPath.c.str());
    JSONVar myObject = JSON.parse(jsonBuffer);

    if(JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing input failed!");
      return;
    }

    windSpeed = myObject["wind"]["speed"]);
    photoSensor = analogRead(A0);
    photoSensor = map(photoSensor, 0, 1023, 0, 255);
    if(isOpen==0) //si le store est rentre
    {
      if(photoSensor > 50 && windSpeed <=40) //si il y a du soleil et pas trop de vent
      {
        myServo.write(180); //on ouvre
        isOpen=1;
      }
    } 
    else { //si le store est ouvert
      if(windSpeed > 40) // si il ya trop de vent
      {
        myServo.write(0);
        isOpen=0;
      }
    }
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

String httGETRequest(const char* serverName) {
  HTTPClient http;
  http.begin(servername);
  int httpresponseCode = http.GET();
  String myObject = "{}";

  if httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    myObject = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return myObject;
}
