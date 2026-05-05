#include <ESP8266WiFi.h>

// Menyertakan seluruh modul yang telah dipisah
#include "setting.h"
#include "memori.h"
#include "logikamonitoring.h"
#include "ai.h"
#include "telegram.h"

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("======================================");
    Serial.println("Memulai Sistem Smart IoT Dapur AI");
    Serial.println("======================================");

    // 1. Inisialisasi Sensor (PinMode)
    initSensors();
    Serial.println("[OK] Sensor diinisialisasi.");

    // 2. Koneksi Wi-Fi
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("[INFO] Menghubungkan ke WiFi");
    
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 40) { // Timeout 20 detik
        delay(500);
        Serial.print(".");
        retries++;
    }
    
    if(WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[OK] WiFi Terhubung!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n[FAIL] Gagal menghubungkan ke WiFi. Restarting...");
        ESP.restart();
    }

    // 3. Inisialisasi Bot Telegram (Kirim pesan pembuka)
    initTelegram();
    Serial.println("[OK] Bot Telegram siap polling.");
}

void loop() {
    // ---------------------------------------------------------
    // ALUR KERJA UTAMA (Main Loop)
    // Berjalan terus-menerus tanpa fungsi delay() yang memblokir
    // ---------------------------------------------------------

    // 1. Membaca data sensor secara Real-Time
    readSensors();

    // 2. Mengevaluasi Status Keselamatan
    if (checkDanger()) {
        // Jika status bahaya tercapai, kirim peringatan
        sendDangerAlert();
    }

    // 3. Memeriksa pesan masuk dari pengguna via Telegram
    pollTelegram();

    // Delay super kecil (10ms) semata-mata untuk mencegah Watchdog Timer (WDT) reset pada ESP8266
    delay(10);
}
