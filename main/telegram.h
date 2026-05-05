#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <Arduino.h>
#include <UniversalTelegramBot.h> // Membutuhkan library UniversalTelegramBot
#include <WiFiClientSecure.h>
#include "setting.h"
#include "ai.h"
#include "memori.h"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, secured_client);

unsigned long bot_lasttime = 0;
const unsigned long BOT_MTBS = 3000; // Polling pesan tiap 3 detik

void initTelegram() {
    secured_client.setInsecure(); // Wajib dipanggil untuk ESP8266 agar bisa HTTPS
    bot.sendMessage(TELEGRAM_CHAT_ID, "🤖 *Sistem Smart IoT Dapur Aktif!*\n\nSistem memantau secara real-time. Ketik /status untuk mengecek secara manual, atau tanyakan apa saja dengan bahasa Anda.", "Markdown");
}

void handleNewMessages(int numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
        String chat_id = bot.messages[i].chat_id;
        String text = bot.messages[i].text;

        // Keamanan: Hanya merespons pemilik sah (Chat ID yang terdaftar)
        if (chat_id != TELEGRAM_CHAT_ID) {
            bot.sendMessage(chat_id, "Maaf, akses ditolak. Anda bukan pemilik sistem ini.", "");
            continue;
        }

        if (text == "/start" || text == "/help") {
            String welcome = "Halo! Saya Asisten AI Dapur Anda.\n\n";
            welcome += "Anda bisa memberikan perintah atau pertanyaan seperti:\n";
            welcome += "- 'Apakah kompor saya mati?'\n";
            welcome += "- 'Tolong perhatikan dapur ya.'\n";
            welcome += "\nPerintah sistem:\n";
            welcome += "/status - Cek status manual statis\n";
            welcome += "/clear - Hapus memori percakapan AI";
            bot.sendMessage(chat_id, welcome, "");
        } 
        else if (text == "/status") {
            String stat = "*Status Aktual Dapur:*\n\n";
            stat += "🔥 Kompor: *" + String(isFlameDetected ? "MENYALA" : "MATI") + "*\n";
            stat += "👤 Kehadiran: *" + String(isPersonPresent ? "ADA ORANG" : "KOSONG") + "*\n";
            if(isDanger) stat += "\n🚨 *STATUS BAHAYA AKTIF!*";
            bot.sendMessage(chat_id, stat, "Markdown");
        }
        else if (text == "/clear") {
            clearMemory();
            bot.sendMessage(chat_id, "✅ Memori konteks percakapan AI telah dikosongkan.", "");
        }
        else {
            // Meneruskan pesan bebas (Natural Language) ke AI DeepSeek
            bot.sendMessage(chat_id, "⏳ *Memproses pemikiran...*", "Markdown");
            String aiResponse = askDeepSeek(text);
            bot.sendMessage(chat_id, aiResponse, "");
        }
    }
}

void pollTelegram() {
    // Polling non-blocking (tidak menggunakan delay())
    if (millis() - bot_lasttime > BOT_MTBS) {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        while (numNewMessages) {
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        bot_lasttime = millis();
    }
}

void sendDangerAlert() {
    if(!dangerAlertSent) {
        String alertMsg = "🚨 *PERINGATAN BAHAYA KRITIS!* 🚨\n\nKompor Anda terdeteksi MENYALA, namun tidak ada orang di area dapur selama lebih dari 3 menit!\n\nHarap segera kembali ke dapur dan matikan kompor untuk mencegah kebakaran!";
        bot.sendMessage(TELEGRAM_CHAT_ID, alertMsg, "Markdown");
        dangerAlertSent = true; // Set flag agar tidak spam
    }
}

#endif
