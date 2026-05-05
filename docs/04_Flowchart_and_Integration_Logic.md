# Task 4 & 5: Perancangan Flowchart Logika & Alur Integrasi AI

## A. Flowchart Logika Pemantauan (Task 4)
Logika ini berjalan pada `loop()` utama setiap puluhan milidetik.
1. **Baca Sensor:**
   - Cek Sensor Flame -> Apakah mendeteksi api? (Ya/Tidak)
   - Cek Ultrasonik -> Berapa jaraknya? (< 200cm = Ada Orang, > 200cm = Kosong)
2. **Evaluasi Status:**
   - **Kondisi Aman:** Api Mati, ada/tidak ada orang.
   - **Kondisi Wajar:** Api Nyala, ada orang di dapur.
   - **Kondisi Potensi Bahaya:** Api Nyala, tidak ada orang.
3. **Timer Bahaya:**
   - Jika "Potensi Bahaya" terjadi, jalankan timer `millis()`.
   - Jika kondisi ini berlangsung selama > 3 Menit terus menerus: **Trigger Alarm Bahaya!** Kirim notifikasi darurat via Telegram.
   - Jika orang kembali ke dapur sebelum 3 menit, batalkan timer (Reset ke Aman/Wajar).

## B. Alur Integrasi AI DeepSeek (Task 5)
DeepSeek berfungsi sebagai asisten interaktif, dipanggil hanya jika pengguna mengirim pesan melalui Telegram atau saat sistem mengirimkan peringatan darurat yang membutuhkan penjelasan kontekstual.

**Skenario: Pengguna bertanya via Telegram**
1. User kirim pesan Telegram: *"Halo bot, apakah kompor saya mati?"*
2. Wemos menangkap pesan via Polling (Interval 3 detik).
3. Wemos menggabungkan data sensor aktual dengan pesan user:
   *Prompt ke AI:* `[SYSTEM]: Sensor menunjukkan kompor: MATI. Tidak ada orang. [USER]: Halo bot, apakah kompor saya mati?`
4. ESP8266 HTTP POST ke endpoint `api.deepseek.com`.
5. ESP8266 menunggu balasan (Proses blocking sebentar, bisa ditoleransi karena user mengharapkan balasan).
6. Balasan AI di-parsing via ArduinoJson: *"Ya, kondisi aman, kompor Anda saat ini dalam keadaan mati."*
7. Wemos mengirim balasan tersebut ke Telegram user.

**Memori Singkat AI:**
Agar percakapan terasa natural, 2 percakapan terakhir (User & Asisten) disimpan dalam variabel array string dan selalu disertakan dalam `messages` JSON payload, memberikan AI konteks dari pertanyaan sebelumnya.
