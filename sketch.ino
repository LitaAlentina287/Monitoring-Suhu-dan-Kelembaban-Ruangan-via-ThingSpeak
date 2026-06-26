/*
  PROYEK AKHIR SISTEM MIKROKONTROLER

  Monitoring Suhu dan Kelembaban Ruangan
  Menggunakan ESP32 + DHT22 + LCD I2C + ThingSpeak

  Field 1 = Suhu
  Field 2 = Kelembaban
  Field 3 = Status Ruangan

  Status:
  1 = Dingin
  2 = Normal
  3 = Panas
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// =======================
// WIFI
// =======================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// =======================
// THINGSPEAK
// =======================
String apiKey = "25SUZFG9VRKZKYFR";
const char* server = "http://api.thingspeak.com/update";

// =======================
// DHT22
// =======================
#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// =======================
// LCD I2C
// =======================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// =======================
// LED DAN BUZZER
// =======================
#define LED_HIJAU 18
#define LED_KUNING 19
#define LED_MERAH 23
#define BUZZER 5

// =======================
// SETUP
// =======================
void setup() {

  Serial.begin(115200);

  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);

  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_MERAH, LOW);

  // Setup buzzer ESP32
  ledcAttach(BUZZER, 1000, 8);
  ledcWriteTone(BUZZER, 0);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(03, 0);
  lcd.print("Monitoring");
  lcd.setCursor(03, 1);
  lcd.print("Suhu & Hum");

  delay(2000);

  WiFi.begin(ssid, password);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  Serial.print("Menghubungkan WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Terhubung");

  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");

  delay(2000);
}

// =======================
// LOOP
// =======================
void loop() {

  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  if (isnan(suhu) || isnan(kelembaban)) {

    Serial.println("Gagal membaca DHT22");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");

    delay(2000);
    return;
  }

  int statusRuangan;
  String statusText;

  // =======================
  // KONDISI DINGIN
  // =======================
  if (suhu < 25) {

    statusRuangan = 1;
    statusText = "DINGIN";

    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(LED_KUNING, LOW);
    digitalWrite(LED_MERAH, LOW);

    // Buzzer OFF
    ledcWriteTone(BUZZER, 0);
  }

  // =======================
  // KONDISI NORMAL
  // =======================
  else if (suhu >= 25 && suhu <= 30) {

    statusRuangan = 2;
    statusText = "NORMAL";

    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(LED_KUNING, HIGH);
    digitalWrite(LED_MERAH, LOW);

    // Buzzer OFF
    ledcWriteTone(BUZZER, 0);
  }

  // =======================
  // KONDISI PANAS
  // =======================
  else {

    statusRuangan = 3;
    statusText = "PANAS";

    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(LED_KUNING, LOW);
    digitalWrite(LED_MERAH, HIGH);

    // Buzzer ON (1000 Hz)
    ledcWriteTone(BUZZER, 1000);
  }

  // =======================
  // SERIAL MONITOR
  // =======================
  Serial.println("========================");
  Serial.print("Suhu       : ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembaban : ");
  Serial.print(kelembaban);
  Serial.println(" %");

  Serial.print("Status     : ");
  Serial.println(statusText);

  // =======================
  // LCD
  // =======================
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(suhu, 1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(10, 0);
  lcd.print("H:");
  lcd.print((int)kelembaban);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Status:");
  lcd.print(statusText);

  // =======================
  // THINGSPEAK
  // =======================
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = String(server) +
                 "?api_key=" + apiKey +
                 "&field1=" + String(suhu) +
                 "&field2=" + String(kelembaban) +
                 "&field3=" + String(statusRuangan);

    http.begin(url);

    int httpCode = http.GET();

    if (httpCode > 0) {

      Serial.print("ThingSpeak Response : ");
      Serial.println(httpCode);

    } else {

      Serial.println("Gagal kirim data");
    }

    http.end();
  }
  else {

    Serial.println("WiFi Terputus");
  }

  // ThingSpeak minimal 15 detik
  delay(20000);
}
