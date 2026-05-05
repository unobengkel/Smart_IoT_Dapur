# PAPER: Rancang Bangun Sistem "Smart IoT Pemantau Dapur" Berbasis Wemos ESP8266 dengan Integrasi Artificial Intelligence DeepSeek dan Telegram Bot

**Abstrak**
Kelalaian saat memasak sering kali menjadi penyebab utama terjadinya kebakaran di area dapur rumah tangga. Makalah riset ini mengusulkan sebuah prototipe *Smart IoT Pemantau Dapur* yang mampu mendeteksi potensi bahaya secara seketika (*real-time*). Menggunakan mikrokontroler Wemos ESP8266, sistem ini memadukan sensor nyala api (Flame Sensor) dan sensor jarak spasial (Ultrasonik HC-SR04). Integrasi dengan *Universal Telegram Bot* memungkinkan notifikasi peringatan dini. Lebih jauh, penggunaan pemrosesan bahasa alami (*Natural Language Processing*) melalui *DeepSeek API* memberikan sistem sebuah memori singkat untuk berinteraksi dengan pengguna secara cerdas dan kontekstual.

## 1. Pendahuluan
Meningkatnya mobilitas manusia sering kali berdampak pada penurunan kewaspadaan terhadap hal-hal domestik, seperti meninggalkan kompor dalam keadaan menyala tanpa pengawasan. Solusi tradisional berupa detektor asap sering kali terlambat memberikan peringatan karena membutuhkan akumulasi asap yang cukup padat. Oleh karena itu, diperlukan sistem *Internet of Things* (IoT) prediktif yang dapat memantau korelasi antara status kompor dan kehadiran fisik pengguna di sekitarnya. 

## 2. Arsitektur Perangkat Keras (Hardware)
Sistem dikendalikan oleh **Wemos ESP8266**, sebuah SoC Wi-Fi berbiaya rendah yang kuat. 
- **Sensor Flame** diposisikan mengarah ke area tungku kompor. Output digital dari sensor ini akan bernilai LOW saat radiasi inframerah dari lidah api terdeteksi. Sensor ini beroperasi pada 3.3V dan terhubung ke GPIO 5 (D1).
- **Sensor Ultrasonik (HC-SR04)** ditempatkan pada ketinggian tertentu mengarah ke zona berdiri pengguna di depan kompor. Gelombang suara 40kHz dipancarkan dari pin TRIG (GPIO 4 / D2), dan pantulannya dibaca oleh pin ECHO (GPIO 0 / D3). Rentang aman (ada orang) didefinisikan sebagai jarak pantulan kurang dari 200 sentimeter.

## 3. Desain Perangkat Lunak & Logika Sistem
Algoritma utama berfokus pada mitigasi *false-positive*. Sistem mendefinisikan "Kondisi Bahaya" bukan sekadar ketika kompor menyala, melainkan ketika **kompor menyala secara bersamaan dengan ketidakhadiran pengguna melebihi ambang batas waktu 3 menit (180.000 milidetik).**

Jika sistem masuk ke status bahaya, prosedur *Interrupt* darurat akan memicu fungsi HTTP Client untuk mengirimkan alert secara instan ke API Telegram Bot (`api.telegram.org`). 

## 4. Integrasi Kecerdasan Buatan (DeepSeek AI)
Pendekatan unik dari penelitian ini adalah penanaman "Otak AI" menggunakan DeepSeek. Sistem menyimpan status sensor (*state*) sebagai variabel lingkungan. Ketika pengguna berinteraksi dengan bot di Telegram (contoh: *"Apakah dapur saya aman?"*), ESP8266 akan menyusun sebuah payload JSON yang memuat:
1. *System Prompt* (Konteks tersembunyi: "Kompor mati, tidak ada orang").
2. *User Prompt* (Pertanyaan pengguna).
3. *Chat History* (Log 2 percakapan sebelumnya untuk mempertahankan ingatan jangka pendek).

Payload ini dikirim menggunakan protokol POST HTTPS cURL ke `api.deepseek.com`. Response dari AI kemudian diproses (*parsing*) menggunakan library *ArduinoJson* sebelum dikirimkan kembali sebagai teks balasan Telegram. Hal ini memungkinkan notifikasi yang jauh lebih kaya dan *human-readable* dibandingkan notifikasi status statis.

## 5. Kesimpulan
Integrasi mikrokontroler *edge-computing* (ESP8266) dengan *Cloud AI* (DeepSeek) menghasilkan sistem keamanan yang tidak hanya reaktif tetapi juga interaktif. Optimalisasi manajemen memori (penggunaan *circular buffer* untuk riwayat chat) terbukti krusial untuk mencegah *heap overflow* pada RAM ESP8266 yang sangat terbatas.
