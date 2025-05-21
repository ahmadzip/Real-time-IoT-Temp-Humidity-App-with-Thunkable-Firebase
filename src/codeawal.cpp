#include <WiFi.h>
#include <DHT.h>
#include <FirebaseESP32.h>

// WiFi Credentials
const char* ssid = "wokwi-GUEST";
const char* password = "";

// Firebase Settings
#define FIREBASE_HOST "iot-praktik-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "SPTb1FUF3t44TS2TomRqOJ596ZQvzpLgqvoAyqZw"

// DHT Settings
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LED Pin
#define LED 2

// Firebase Object
FirebaseData fbdo;

// WiFi Connection
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

// Firebase Initialization
void firebaseInit() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  wifiConnection();
  dht.begin();
  firebaseInit();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %, Temperature: ");
  Serial.print(t);
  Serial.println(" *C");

  // Send to Firebase
  if (Firebase.setFloat(fbdo, "/DHT22/SUHU", t)) {
    Serial.println("Temperature sent to Firebase");
  } else {
    Serial.print("Firebase setFloat failed: ");
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.setFloat(fbdo, "/DHT22/HUMIDITY", h)) {
    Serial.println("Humidity sent to Firebase");
  } else {
    Serial.print("Firebase setFloat failed: ");
    Serial.println(fbdo.errorReason());
  }

  delay(5000); // Delay for 5 seconds
}
