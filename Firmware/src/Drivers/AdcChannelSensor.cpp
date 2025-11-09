/**
 * * @file AdcChannelSensor.cpp
 *
 * @brief Implementa um canal ADC individual como um sensor independente.
 *
 * @details
 * Cada instância representa um canal analógico (A0–A15, MCP etc.),
 * compatível com a interface ISensor e o formato unificado de log.
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

#include "Drivers/AdcChannelSensor.h"

// AdcChannelSensor::AdcChannelSensor() : channel(0), sensorName(F("UNINITIALIZED")) {}

AdcChannelSensor::AdcChannelSensor(uint8_t channel, const char* name)
    : channel(channel), sensorName(name) {}

void AdcChannelSensor::begin() {
    Serial.print(F("🔌 Inicializando ADC Canal: "));
    Serial.print(channel);
    Serial.print(F(" - "));
    Serial.println(sensorName);
    analogReference(DEFAULT);
}

bool AdcChannelSensor::isAvailable() const {
    return true;
}

const char* AdcChannelSensor::getDeviceName() const {
    return sensorName;
}

void AdcChannelSensor::printStatus() const {
    Serial.print(F("["));
    Serial.print(sensorName);
    Serial.println(F("] pronto."));
}

void AdcChannelSensor::response() {
    float value = analogRead(channel);
    Serial.print(sensorName);
    Serial.print(F(" = "));
    Serial.println(value);
}

void AdcChannelSensor::getData(SensorData& out) {
    out.numericCount = 1;
    out.textCount = 0;
    out.numeric[0] = analogRead(channel);
}

void AdcChannelSensor::appendToLogLine(String& line) {
    SensorData data;
    getData(data);
    if (data.numeric[0] < 200 || data.numeric[0] > 700)
        line += String("fail;");
    else
        line += String(data.numeric[0], 2) + ';';
}

String AdcChannelSensor::logLine() {
    SensorData data;
    getData(data);
    if (data.numeric[0] < 200 || data.numeric[0] > 700)
        return String("fail;");
    else
        return String(data.numeric[0], 2) + ';';
}
