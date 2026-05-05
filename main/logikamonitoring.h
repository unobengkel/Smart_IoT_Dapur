#ifndef LOGIKAMONITORING_H
#define LOGIKAMONITORING_H

#include <Arduino.h>
#include "setting.h"
#include "memori.h"

void initSensors() {
    pinMode(PIN_FLAME, INPUT);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void readSensors() {
    // 1. Baca Flame Sensor (Active Low)
    int flameVal = digitalRead(PIN_FLAME);
    isFlameDetected = (flameVal == LOW);

    // 2. Baca Ultrasonik
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    
    // Timeout 30000 microsecond (~5 meter maks) untuk mencegah blocking
    long duration = pulseIn(PIN_ECHO, HIGH, 30000); 
    
    if(duration == 0) {
        distanceCm = 999.0; // Tidak ada pantulan (Kosong)
    } else {
        distanceCm = duration * 0.034 / 2;
    }

    // Evaluasi Kehadiran
    isPersonPresent = (distanceCm > 0 && distanceCm <= SAFE_DISTANCE_CM);
}

bool checkDanger() {
    if (isFlameDetected && !isPersonPresent) {
        // Kompor nyala, orang tidak ada -> Potensi Bahaya
        if (dangerTimerStart == 0) {
            dangerTimerStart = millis(); // Mulai hitung
        } else {
            if (millis() - dangerTimerStart >= DANGER_TIME_THRESHOLD) {
                isDanger = true;
                return true; // Bahaya tercapai!
            }
        }
    } else {
        // Kondisi Aman atau Wajar
        // Reset timer dan flag bahaya
        dangerTimerStart = 0;
        isDanger = false;
        dangerAlertSent = false;
    }
    return false;
}

#endif
