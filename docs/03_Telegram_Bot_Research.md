# Task 3: Riset Integrasi Universal Telegram Bot Library

## 1. Pilihan Library
Untuk ESP8266, **UniversalTelegramBot** oleh Brian Lough adalah pustaka paling stabil dan banyak digunakan untuk berkomunikasi dengan API Telegram (`api.telegram.org`).

## 2. Mekanisme Komunikasi
- **Polling vs Webhook:** Telegram menyediakan webhook (server kita dipanggil), namun ESP8266 berada di balik NAT/Router rumah dan port forwarding sulit dijamin. Maka, kita wajib menggunakan metode **Long-Polling** (ESP8266 terus menanyakan Telegram, "Apakah ada pesan baru?").
- **HTTPS & SSL:** Seperti DeepSeek, Telegram juga menggunakan HTTPS. *UniversalTelegramBot* dapat menangani SSL dengan menggunakan `WiFiClientSecure` dan menset klien ke `.setInsecure()`.

## 3. Kebutuhan Memori dan Kinerja
- **Non-blocking Polling:** Secara default, memanggil API Telegram secara berulang akan mem-blokir pembacaan sensor ultrasonik/api. 
- **Solusi:** Proses cek pesan baru (polling) hanya dilakukan setiap 2-3 detik sekali menggunakan logika `millis()`, bukan `delay()`. Hal ini memungkinkan fungsi deteksi bahaya kompor tetap berjalan secepat kilat (*real-time*).

## Kesimpulan Task 3
Integrasi akan menggunakan *UniversalTelegramBot* via Long-Polling *non-blocking*. Pengecekan pesan dilakukan dengan timer `millis()` berinterval tertentu agar sistem utamanya tidak terhambat.
