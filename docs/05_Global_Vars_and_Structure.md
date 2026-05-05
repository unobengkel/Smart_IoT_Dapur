# Task 6 & 7: Pendefinisian Variabel Global & Struktur Folder

## A. Variabel Global Utama (Task 6)
Pada header `setting.h` dan `memori.h`, sistem membutuhkan data berikut:
- `bool isFlameDetected`: Menyimpan status kompor.
- `float distanceCm`: Menyimpan jarak objek di dapur.
- `bool isPersonPresent`: Status keberadaan orang.
- `unsigned long dangerTimer`: Pencatat waktu sejak potensi bahaya dimulai.
- `bool dangerAlertSent`: Flag mencegah pengiriman spam telegram berulang kali.
- `String chatHistory[4]`: Array sirkular untuk memori percakapan singkat AI. Indeks menyimpan urutan pesan.

## B. Struktur Folder Proyek (Task 7)
Proyek Arduino akan dikelola dalam arsitektur modular yang rapi agar `main.ino` tidak terlalu penuh:
```text
Smart_IoT_Dapur/
│
├── README.md                 (Dokumentasi)
├── docs/                     (Folder dokumen riset & paper)
│   ├── 01_Hardware_Analysis.md
│   ├── ...
│
└── src/                      (Folder Source Code Utama ESP8266)
    ├── Smart_IoT_Dapur.ino   (Berisi fungsi setup() dan loop() utama)
    ├── setting.h             (Konfigurasi WiFi, API Keys, Konfigurasi Pin)
    ├── memori.h              (Manajemen array historis percakapan AI)
    ├── logikamonitoring.h    (Fungsi pembacaan sensor dan timer bahaya)
    ├── ai.h                  (Fungsi HTTP Client ke DeepSeek API)
    └── telegram.h            (Fungsi Inisialisasi dan polling pesan Telegram)
```

Struktur ini mendukung pembagian tugas (*separation of concern*). Setiap logika dienkapsulasi dengan baik.
