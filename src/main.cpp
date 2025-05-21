#include <WiFi.h>
#include <DHTesp.h> 
#include <FirebaseESP32.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

#define FIREBASE_HOST "YOUR FIREBASE HOST"
#define FIREBASE_AUTH "YOUR FIREBASE AUTH TOKEN"

#define DHTPIN 13
DHTesp dht; 

#define LED 2

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void wifiConnection() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Connected!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void firebaseInit() {
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  wifiConnection();
  dht.setup(DHTPIN, DHTesp::DHT22); 
  firebaseInit();
}

void loop() {
  TempAndHumidity data = dht.getTempAndHumidity(); 

  if (isnan(data.humidity) || isnan(data.temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(data.humidity);
  Serial.print(" %, Temperature: ");
  Serial.print(data.temperature);
  Serial.println(" *C");

  String temperatureWithUnit = String(data.temperature, 1) + " *C"; 
  String humidityWithUnit = String(data.humidity, 1) + " %";    

  if (Firebase.setString(fbdo, "/DHT22/SUHU", temperatureWithUnit)) {
    Serial.println("Temperature sent to Firebase");
  } else {
    Serial.print("Firebase setString failed: ");
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.setString(fbdo, "/DHT22/HUMIDITY", humidityWithUnit)) {
    Serial.println("Humidity sent to Firebase");
  } else {
    Serial.print("Firebase setString failed: ");
    Serial.println(fbdo.errorReason());
  }

  delay(5000);
}