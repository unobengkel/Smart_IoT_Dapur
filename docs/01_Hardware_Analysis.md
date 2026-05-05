# Task 1: Analisis Spesifikasi Perangkat Keras dan Pinout

## 1. Wemos ESP8266 (NodeMCU Wemos D1 Mini / Sejenisnya)
- **Tegangan Operasional:** 3.3V. Namun, board Wemos biasanya memiliki pin 5V (dihubungkan dari USB) yang dapat mensuplai tegangan untuk sensor yang membutuhkan 5V.
- **Logika I/O:** 3.3V (Sangat penting: sinyal masuk dari sensor yang berlogika 5V perlu penyesuaian atau pembagi tegangan jika pin tidak 5V tolerant, meskipun beberapa pin ESP8266 diklaim 5V tolerant).
- **Wi-Fi:** Built-in 802.11 b/g/n, ideal untuk HTTP Request (ke DeepSeek) dan Long Polling (ke Telegram).
- **Keterbatasan Daya:** Mengirim data via Wi-Fi bisa memakan arus puncak hingga ~200-300mA. Pastikan *power supply* (adaptor USB) setidaknya 1A atau 2A untuk mencegah *brown-out* atau *restart* tiba-tiba.

## 2. Sensor Flame (Sensor Api)
- **Karakteristik:** Menggunakan *photodiode* (biasanya penerima inframerah dengan sensitivitas spektrum 760nm - 1100nm) untuk mendeteksi keberadaan nyala api.
- **Output:** Digital (DO) bernilai HIGH atau LOW (tergantung model, seringkali LOW / `0` saat mendeteksi api - *active low*) dan Analog (AO). Untuk efisiensi pada mikrokontroler ini, kita gunakan pin Digital.
- **Tegangan:** 3.3V - 5V. Sangat cocok ditenagai langsung dari pin 3.3V Wemos agar output logikanya aman menyesuaikan Wemos (3.3V).

## 3. Sensor Ultrasonik (HC-SR04)
- **Karakteristik:** Menghitung jarak berdasarkan waktu tempuh pantulan suara ultrasonik.
- **Pin:** VCC, TRIG, ECHO, GND.
- **Tegangan Operasional:** VCC membutuhkan 5V untuk beroperasi secara optimal dan stabil. Output ECHO menghasilkan sinyal puncak 5V.
- **Perhatian Khusus:** Karena ECHO = 5V dan level I/O Wemos = 3.3V, disarankan menggunakan *voltage divider* (pembagi tegangan dengan resistor, misal 1K ohm dan 2K ohm) dari ECHO ke pin Wemos untuk keamanan jangka panjang sirkuit mikrokontroler.

## 4. Alokasi Pinout (*Mapping Pin*)
Rencana pengkabelan (*Wiring*) pada Wemos D1 Mini:

| Komponen | Pin Modul | Pin Wemos (ESP8266) | Keterangan |
| :--- | :--- | :--- | :--- |
| **Wemos ESP8266** | 5V / Vin | VCC Power Supply | Menggunakan charger HP (5V, min 1A) |
| | G / GND | GND Power Supply | Titik Ground bersama (Common Ground) |
| **Sensor Flame** | VCC | 3V3 (Wemos) | Aman beroperasi di 3.3V |
| | GND | G (Wemos) | |
| | DO (Digital) | D1 (GPIO 5) | Membaca status api via `digitalRead` |
| **Ultrasonik** | VCC | 5V (Wemos) | Membutuhkan tegangan 5V dari rail USB |
| (HC-SR04) | GND | G (Wemos) | |
| | TRIG | D2 (GPIO 4) | Memicu sinyal ultrasonik (`digitalWrite`) |
| | ECHO | D3 (GPIO 0) | Membaca pantulan (`pulseIn`) - Pasang pembagi tegangan jika perlu |

## 5. Kesimpulan Analisis (Task 1)
Integrasi sensor-sensor di atas cukup efisien direalisasikan dengan Wemos ESP8266. Pemilihan pin **D1, D2, dan D3** dirancang secara khusus untuk menghindari pin-pin sensitif yang memiliki peran saat *booting* (seperti D8 / GPIO15 atau D4 / GPIO2). Menggunakan pin khusus booting secara tidak hati-hati dapat menyebabkan ESP8266 gagal *boot* apabila sensor aktif saat mikrokontroler baru dihidupkan. Selain itu, penggunaan modul daya independen yang memadai (minimal 1A) adalah hal yang wajib agar koneksi Wi-Fi tidak terputus (*drop*) saat kompor memicu bahaya dan sistem memproses AI ke DeepSeek.
