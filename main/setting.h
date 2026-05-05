#ifndef SETTING_H
#define SETTING_H

#include <Arduino.h>

// Konfigurasi WiFi
const char* WIFI_SSID = "NAMA_WIFI_ANDA";
const char* WIFI_PASS = "PASSWORD_WIFI_ANDA";

// Konfigurasi Telegram
const char* TELEGRAM_BOT_TOKEN = "TOKEN_BOT_TELEGRAM_ANDA";
const char* TELEGRAM_CHAT_ID = "CHAT_ID_ANDA";

// Konfigurasi DeepSeek API
const char* DEEPSEEK_API_KEY = "DEEPSEEK_API_KEY_ANDA";

// Konfigurasi Pin Sensor Wemos D1 Mini
#define PIN_FLAME D1      // GPIO 5
#define PIN_TRIG D2       // GPIO 4
#define PIN_ECHO D3       // GPIO 0

// Parameter Bahaya
const unsigned long DANGER_TIME_THRESHOLD = 180000; // 3 Menit dalam milidetik
const float SAFE_DISTANCE_CM = 200.0; // Maksimal 2 meter untuk dianggap "ada orang"

#endif
