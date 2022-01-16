#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <ESP8266HTTPClient.h>
String apiKey_tilt = "2UPXPOR1RNP8RCZO";
const char apikey_2_tilt[] = "M2X2I7LIXNTXWX8S";
const char *ssid =  "Sonu_iphone";# WiFi NAME
const char *pass =  "sonu311?";# WiFi PASSWORD
const char* server = "api.thingspeak.com";
WiFiClient client;
boolean checkPoint_tilt = true;
//boolean checkPoint1 = true;
long myChannelNumber_tilt = 1552406;

int d = 0;

int Analogpin = D0;

String apiKey_uss = "BGAH5ID2OL5HW7RR";
const char apikey_2_uss[] = "SGQI7299LE3H26W0";

boolean checkPoint_uss = true;
// boolean checkPoint1 = true;
long myChannelNumber_uss = 1552360;

const int trigPin = 12;
const int echoPin = 14;
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;
int c = 0;

String apiKey_gas = "HIHHG1VBJU6YM60B";
const char apikey_2_gas[] = "JI0JB1NU40INN0R5";

boolean checkPoint_gas = true;
//boolean checkPoint1 = true;
long myChannelNumber_gas = 1552440;

int e = 0;

int Analogu_pin = A0;
#include<Servo.h>
Servo myservo;
int pos;
int SENSOR_OUTPUT_PIN = 5;

void setup() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.begin(9600); // Starts the serial communication
  pinMode(Analogpin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(Analogu_pin, INPUT);
  pinMode(SENSOR_OUTPUT_PIN, INPUT);
  myservo.attach(0);
}
void loop() {
  uss();
  tilt();
  gas();
  pir();
}
void serup() {

  myservo.write(180);

}

void serdown() {


  for (pos = 180; pos >= 0; pos -= 5) {

    myservo.write(pos);

    delay(5);

  }

}

void pir() {
  int sensorvalue = digitalRead(SENSOR_OUTPUT_PIN);
  if (sensorvalue == HIGH) {
    Serial.println("Motion detected!");
    sensorvalue = LOW;
    serdown();
    delay(50000);
  }
  else {
    Serial.println("Motion absent!");
    serup();
  }

}



void gas() {
  int status = analogRead(Analogu_pin);
  Serial.println(status);
  int t = status;
  if (t > 500)
  {
    if (checkPoint_gas)
    {
      HTTPClient http;



      Serial.println("[HTTP] begin...\n");
      String qur = String(t);
      http.begin(client, "  https://api.thingspeak.com/apps/thinghttp/send_request?api_key=JI0JB1NU40INN0R5 " + qur);
      Serial.println("[HTTP] GET...\n");

      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.println(httpCode);
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);

        }
      }
    }
  }



  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey_gas;
    postStr += "&field1=";
    postStr += String(t);

    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey_gas + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("GAS VALUE CHK ");
    Serial.print(t);

    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
void uss() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY / 2;
  // Convert to inches
  //distanceInch = distanceCm * CM_TO_INCH;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance (cm): ");
  //Serial.println(distanceCm);
  int t = 100 - distanceCm;
  if (t > 75)
  {
    if (checkPoint_uss)
    {
      HTTPClient http;



      Serial.println("[HTTP] begin...\n");
      String qur = String(t) + "% completed";
      http.begin(client, " https://api.thingspeak.com/apps/thinghttp/send_request?api_key=SGQI7299LE3H26W0" + qur);
      Serial.println("[HTTP] GET...\n");

      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.println(httpCode);
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);

        }
      }
    }
  }
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey_uss;
    postStr += "&field1=";
    postStr += String(t);


    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey_uss + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("DISTANCE: ");
    Serial.print(t);

    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
void tilt() {
  int status = digitalRead(Analogpin);
  int t = status;
  if (t == 0)
  {
    if (checkPoint_tilt)
    {
      HTTPClient http;
      Serial.println("[HTTP] begin...\n");
      String qur = String(t) + "% completed";
      http.begin(client, " https://api.thingspeak.com/apps/thinghttp/send_request?api_key=M2X2I7LIXNTXWX8S" + qur);
      Serial.println("[HTTP] GET...\n");

      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.println(httpCode);
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);

        }
      }
    }
  }






  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey_tilt;
    postStr += "&field1=";
    postStr += String(t);

    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey_tilt + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("TILT_CHECK ");
    Serial.print(t);

    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
