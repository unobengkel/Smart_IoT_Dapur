#ifndef MEMORI_H
#define MEMORI_H

#include <Arduino.h>

// Variabel Global Status Sensor
bool isFlameDetected = false;
float distanceCm = 0.0;
bool isPersonPresent = false;
unsigned long dangerTimerStart = 0;
bool isDanger = false;
bool dangerAlertSent = false;

// Memori Singkat AI (Circular Buffer)
const int MAX_MEMORY = 4; // Menyimpan 2 pasang percakapan terakhir (User - Assistant)
String chatRoles[MAX_MEMORY];
String chatContents[MAX_MEMORY];
int memoryCount = 0;

void addMemory(String role, String content) {
    // Geser memori ke kiri jika penuh (menghapus memori paling lama)
    if (memoryCount >= MAX_MEMORY) {
        for (int i = 1; i < MAX_MEMORY; i++) {
            chatRoles[i-1] = chatRoles[i];
            chatContents[i-1] = chatContents[i];
        }
        chatRoles[MAX_MEMORY-1] = role;
        chatContents[MAX_MEMORY-1] = content;
    } else {
        chatRoles[memoryCount] = role;
        chatContents[memoryCount] = content;
        memoryCount++;
    }
}

void clearMemory() {
    memoryCount = 0;
}

#endif
