// PWM PIN 2,4,12-19,21-23,25-27, 32,,33

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <ESP32Servo.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Kost F59"
#define WIFI_PASSWORD "F59595959"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino
#define API_KEY "AIzaSyBo-XNbeCo-Wi5nSEur740YSbFGQQxU3NU"
#define DATABASE_URL "https://armfix-b84a8-default-rtdb.firebaseio.com/"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL ""
#define USER_PASSWORD ""

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist;
Servo grip;

unsigned long sendDataPrevMillis = 0;
bool is_signup = false;
int gripFrom = 0, baseFrom = 0, shoulderFrom = 0, wristFrom = 0, elbowFrom = 0;
int mode = 1;
int tasks = 0;
int state = 0;
unsigned long prev = 0;

const int basePin = 23;
const int shoulderPin = 18;
const int elbowPin = 19;
const int wristPin = 22;
const int gripPin = 21;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  networkConnection();
  configFirebase();
  setupServo();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  firebaseCRUD();
  // try_led();
}

void try_led() {
  if (millis() - prev > 1500) {
    if (state) state = 0;
    else state = 1;
    digitalWrite(LED_BUILTIN, state);
    prev = millis();
  }
}