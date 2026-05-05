#ifndef AI_H
#define AI_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> // Pastikan library ArduinoJson v6/v7 terinstall
#include "setting.h"
#include "memori.h"

String askDeepSeek(String userQuestion) {
    WiFiClientSecure client;
    client.setInsecure(); // Mengabaikan sertifikat SSL untuk menghemat RAM ESP8266

    HTTPClient http;
    String url = "https://api.deepseek.com/chat/completions";
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + DEEPSEEK_API_KEY);

    // Dynamic buffer untuk menyusun JSON Payload
    DynamicJsonDocument doc(2048);
    doc["model"] = "deepseek-chat";
    
    JsonArray messages = doc.createNestedArray("messages");
    
    // 1. System Prompt (Menyuntikkan Konteks Aktual Dapur ke AI)
    JsonObject systemMsg = messages.createNestedObject();
    systemMsg["role"] = "system";
    String systemContext = "Anda adalah AI pemantau dapur rumah pintar. Jawab dengan ramah dan singkat. Status aktual saat ini: Kompor ";
    systemContext += (isFlameDetected ? "MENYALA" : "MATI");
    systemContext += ", Manusia di dapur: ";
    systemContext += (isPersonPresent ? "ADA" : "TIDAK ADA");
    systemContext += ". ";
    if(isDanger) {
        systemContext += "PERINGATAN: KONDISI SAAT INI BAHAYA KARENA KOMPOR MENYALA DITINGGAL PENGGUNA! BERIKAN PERINGATAN KERAS.";
    }
    systemMsg["content"] = systemContext;

    // 2. Memori Singkat (Menyisipkan Riwayat Percakapan)
    for(int i = 0; i < memoryCount; i++){
        JsonObject memMsg = messages.createNestedObject();
        memMsg["role"] = chatRoles[i];
        memMsg["content"] = chatContents[i];
    }

    // 3. Pertanyaan Pengguna Terbaru
    JsonObject userMsg = messages.createNestedObject();
    userMsg["role"] = "user";
    userMsg["content"] = userQuestion;

    // Serialisasi JSON menjadi string
    String requestBody;
    serializeJson(doc, requestBody);

    // Kirim POST Request
    int httpCode = http.POST(requestBody);
    String responseText = "Maaf, sistem gagal menghubungi server AI DeepSeek.";

    if (httpCode > 0) {
        String payload = http.getString();
        
        // Parsing jawaban AI
        DynamicJsonDocument respDoc(1024);
        DeserializationError error = deserializeJson(respDoc, payload);
        if (!error) {
            responseText = respDoc["choices"][0]["message"]["content"].as<String>();
            
            // Simpan percakapan ke memori singkat
            addMemory("user", userQuestion);
            addMemory("assistant", responseText);
        } else {
            responseText = "Gagal memproses jawaban AI (JSON Error).";
        }
    } else {
        Serial.printf("[HTTP] POST failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    return responseText;
}

#endif
