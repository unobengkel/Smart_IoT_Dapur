# Task 2: Riset Spesifikasi API DeepSeek

## 1. Endpoint & Otentikasi
- **URL Endpoint:** `https://api.deepseek.com/chat/completions`
- **Method:** POST
- **Header yang dibutuhkan:**
  - `Content-Type: application/json`
  - `Authorization: Bearer <DEEPSEEK_API_KEY>`

## 2. Struktur Payload JSON (Request)
Wemos ESP8266 perlu mengirim data dalam format JSON. Karena keterbatasan RAM, JSON string harus se-efisien mungkin.
```json
{
  "model": "deepseek-chat",
  "messages": [
    {"role": "system", "content": "Anda adalah asisten AI pemantau dapur. Jawab singkat padat."},
    {"role": "user", "content": "Apakah dapur aman?"}
  ],
  "temperature": 0.5,
  "max_tokens": 100
}
```

## 3. Limitasi & Eksekusi pada ESP8266
- **Sertifikat SSL (HTTPS):** DeepSeek menggunakan HTTPS. Pada ESP8266 (`ESP8266HTTPClient`), kita bisa mengabaikan sertifikat (`setInsecure()`) agar tidak memakan memori untuk menyimpan root CA, meski kurang aman secara teori, ini praktik umum di sistem *embedded* skala hobi.
- **Library JSON:** Gunakan library **ArduinoJson** v6 atau v7.
- **Memori Pendek (Short Memory):** Array dari JSON messages harus dibuat melingkar (*circular buffer*) atau hanya menampung 3 request-response terakhir agar memori ESP8266 (yang hanya ~40KB free RAM) tidak kehabisan (*Out of Memory*).

## Kesimpulan Task 2
Metode yang digunakan adalah HTTP POST cURL melalui WiFiClientSecure. Format pesan JSON akan digabung (*concatenate*) dan dimanipulasi dengan array statis/dinamis kecil.
