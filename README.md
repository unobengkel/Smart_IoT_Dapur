# Smart IoT Pemantau Dapur Berbasis AI 🍳🔥🤖

Sistem keamanan dapur cerdas berbasis mikrokontroler **Wemos ESP8266** yang mengintegrasikan Sensor Api (Flame Sensor), Sensor Ultrasonik, **Telegram Bot**, dan Kecerdasan Buatan dari **DeepSeek API**.

Sistem ini didesain untuk mendeteksi bahaya kebakaran karena kelalaian pengguna. Jika kompor dibiarkan menyala dan tidak ada orang di dapur selama lebih dari 3 menit, sistem akan mengirimkan peringatan darurat ke Telegram.

## Fitur Utama
1. **Pemantauan Real-Time:** Membaca status api dan kehadiran orang secara instan (*non-blocking*).
2. **Alert Bahaya Kritis:** Algoritma cerdas yang hanya mengirim peringatan saat benar-benar ada bahaya (Kompor nyala + Tidak ada orang + Melewati ambang batas waktu).
3. **Integrasi NLP DeepSeek:** Bot Telegram tidak kaku! Anda bisa menggunakan bahasa sehari-hari untuk bertanya tentang dapur Anda.
4. **Short-Term Memory AI:** AI mampu mengingat konteks 2 percakapan terakhir untuk interaksi yang lebih natural.

## Kebutuhan Perangkat Keras
- 1x Board Wemos D1 Mini (ESP8266)
- 1x Sensor Flame (Digital Output)
- 1x Sensor Jarak Ultrasonik HC-SR04
- Kabel Jumper secukupnya
- Power Supply / Charger HP 5V (Minimal 1A)

### Skema Pengkabelan (Wiring)
| Komponen | Pin Modul | Pin Wemos (ESP8266) |
| --- | --- | --- |
| Sensor Flame | VCC | 3V3 |
| Sensor Flame | GND | G (GND) |
| Sensor Flame | DO | D1 (GPIO 5) |
| Ultrasonik HC-SR04 | VCC | 5V |
| Ultrasonik HC-SR04 | GND | G (GND) |
| Ultrasonik HC-SR04 | TRIG | D2 (GPIO 4) |
| Ultrasonik HC-SR04 | ECHO | D3 (GPIO 0) |

## Cara Instalasi & Persiapan
1. **Buka Arduino IDE**, pastikan board *ESP8266* sudah terinstal di Board Manager.
2. **Instal Library berikut via Library Manager:**
   - `ArduinoJson` (Versi 6.x atau 7.x) oleh Benoit Blanchon
   - `UniversalTelegramBot` oleh Brian Lough
3. **Konfigurasi Akun:**
   - Buka file `main/setting.h`
   - Masukkan `WIFI_SSID` dan `WIFI_PASS`
   - Dapatkan `TELEGRAM_BOT_TOKEN` dari *BotFather* di Telegram.
   - Dapatkan `TELEGRAM_CHAT_ID` Anda (Bisa menggunakan bot *IDBot* di Telegram).
   - Daftar dan dapatkan `DEEPSEEK_API_KEY` dari [DeepSeek API Platform](https://platform.deepseek.com/).
4. **Upload ke Wemos ESP8266:** Buka `src/main.ino` dan tekan tombol *Upload*.

## Panduan Penggunaan Bot Telegram
- `/start` atau `/help`: Memulai percakapan dan melihat perintah dasar.
- `/status`: Mengambil data mentah (raw data) sensor saat ini secara cepat.
- `/clear`: Menghapus memori singkat bot jika konteks obrolan dirasa sudah melenceng.
- **Bebas!** Ketik saja *"Halo, gimana keadaan kompor?"* atau *"Tolong ingatkan aku kalau ada yang aneh"*, AI akan merespons sesuai data sensor terbaru.

---
*Proyek Riset IoT - MIT License*
