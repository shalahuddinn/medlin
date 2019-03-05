//// INPUT DARI USER ////
#define FIREBASE_HOST "medlin-5fe2d.firebaseio.com/"
#define FIREBASE_AUTH "tWVG4NrwtA3r43hNlgivjc0av0wnujB0B2b9gk70"
#define WIFI_SSID "Gabung? Bayar 50k Dulu!"
#define WIFI_PASSWORD "amperegauss"

// Library WiFi
#include <ESP8266WiFi.h>
// Library Firebase
#include <FirebaseArduino.h>

// Deklarasi Variabel
float suhu;
int bpm;
float jarak;
int mulaiWaktuKerja;
int waktuKerja = 0;
int waktuIstirahat;
int lamaKerja;

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  suhu = random(20, 30); // Pembacaan sensor suhu
  bpm = random(90, 170); // Pembacaan sensor pulse sensor
  jarak = random(0, 30); // // Pembacaan sensor lidar

  Serial.print("Suhu : ");
  Serial.println(suhu);
  Serial.print("BPM : ");
  Serial.println(bpm);
  Serial.print("Jarak : ");
  Serial.println(jarak);

  String strSuhu = "";
  if (suhu > 30) {
    strSuhu = "suhupanas";
  } else if (suhu < 20) {
    strSuhu = "suhudingin";
  } else {
    strSuhu = "suhunormal";
  }
  Firebase.setString("SUHU", strSuhu);
  if (Firebase.failed()) {
    Serial.print("send suhu failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("suhu : ");
  Serial.println(strSuhu);

  String strBPM = "";
  if (bpm > 170) {
    strBPM = "bpmcepat";
  } else if (suhu < 90) {
    strBPM = "bpmlambat";
  } else {
    strBPM = "bpmnormal";
  }
  Firebase.setString("BPM", strBPM);
  if (Firebase.failed()) {
    Serial.print("send BPM failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("BPM : ");
  Serial.println(strBPM);

  String strJarak = "";
  if (jarak > 40) {
    strJarak = "jarakjauh";
  } else if (suhu < 90) {
    strJarak = "jarakdekat";
  } else {
    strJarak = "jaraknormal";
  }
  Firebase.setString("JARAK", strJarak);
  if (Firebase.failed()) {
    Serial.print("send Jarak failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("Jarak : ");
  Serial.println(strJarak);

  if (millis() > 2 * 3600 * 10000) {
    waktuIstirahat = millis();
    do {
      jarak = random(0, 30); // // Pembacaan sensor lidar
      if (jarak > 40) {
        String strKondisi = "Istirahat";
        Firebase.setString("Kondisi", strKondisi);
        if (Firebase.failed()) {
          Serial.print("send Kondisi failed:");
          Serial.println(Firebase.error());
          return;
        }
        Serial.print("Kondisi : ");
        Serial.println(strKondisi);
      } else {
        String strKondisi = "Kerja";
        Firebase.setString("Kondisi", strKondisi);
        if (Firebase.failed()) {
          Serial.print("send Kondisi failed:");
          Serial.println(Firebase.error());
          return;
        }
        Serial.print("Kondisi : ");
        Serial.println(strKondisi);
      }
    } while (millis() - waktuIstirahat < 30 * 60 * 10000 );
  }

  String strKondisi = "Kerja";
  Firebase.setString("Kondisi", strKondisi);
  if (Firebase.failed()) {
    Serial.print("send Kondisi failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("Kondisi : ");
  Serial.println(strKondisi);

  lamaKerja = millis()/(36000 * 10000);
  Firebase.setFloat("lamaKerja", lamaKerja);
  if (Firebase.failed()) {
    Serial.print("send lama kerja failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("Lama Kerja : ");
  Serial.println(lamaKerja);


delay(10000);
}
