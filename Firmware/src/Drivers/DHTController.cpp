/**
 * * @file DHTController.cpp
 *
 * @brief Implementação do Controlador do sensor DHT22 (umidade e temperatura)
 *
 * @details
 * Implementa a interface ISensor, fornecendo leituras unificadas
 * de temperatura e umidade. Compatível com o sistema de coleta
 * polimórfico via SensorData.
 *
 * @author
 *   Fabrício Michel Denes (FMD)
 * @date
 *   2025
 *
 * @copyright
 *   © 2025 Fabrício Michel Denes. Todos os direitos reservados.
 *
 * @license
 *   Este código é distribuído sob a licença MIT.
 *   Consulte o arquivo LICENSE ou visite:
 *   https://opensource.org/licenses/MIT
 *
 * @version
 * * v0.2.x  - Em desenvolvimento
 */

#include "Drivers/DHTController.h"

static long lastSaveTime = 0;
static unsigned long SAVE_INTERVAL = 2000;

DHTController::DHTController(uint8_t pin, uint8_t type)
    : dhtPin(pin), dhtType(type), dht(pin, type) {}

void DHTController::begin() {
    dht.begin();
    delay(100);
    Serial.println(F("[DHT22] Inicializado."));
}

bool DHTController::isAvailable() const {
    unsigned long currentMillis = millis();

    if (currentMillis - lastSaveTime >= SAVE_INTERVAL) {
        float t = dht.readTemperature();
        float h = dht.readHumidity();
        if (isnan(t) || isnan(h))
            return false;
        lastTemp = t;
        lastHum = h;
    }
    return true;
}

void DHTController::printStatus() const {
    if (isAvailable()) {
        Serial.print(F("[DHT22] Temp: "));
        Serial.print(lastTemp, 1);
        Serial.print(F(" °C | Umid: "));
        Serial.print(lastHum, 1);
        Serial.println(F(" %"));
    } else {
        Serial.println(F("[DHT22] Erro de leitura."));
    }
}

void DHTController::response() {
    if (!isAvailable()) {
        Serial.println(F("⚠️ Falha na leitura do DHT22"));
        return;
    }
    Serial.print(F("💧 Umid: "));
    Serial.print(lastHum, 1);
    Serial.print(F("%  🌡 Temp: "));
    Serial.print(lastTemp, 1);
    Serial.println(F("°C"));
}

void DHTController::getData(SensorData& out) {
    if (!isAvailable()) {
        out.numericCount = 0;
        return;
    }
    out.numeric[0] = lastHum;
    out.numeric[1] = lastTemp;
    out.numericCount = 2;
}

void DHTController::appendToLogLine(String& line) {
    SensorData data;
    getData(data);

    if (data.numericCount >= 2) {
        line += String(data.numeric[0], 2) + ';' + String(data.numeric[1], 2) + ';';
    } else {
        line += F("--;--;");  // placeholders
    }
}

String DHTController::logLine() {
    SensorData data;
    getData(data);

    if (data.numericCount >= 2) {
        return String(data.numeric[0], 2) + ';' + String(data.numeric[1], 2) + ';';
    } else {
        return ("--;--;");  // placeholders
    }
}