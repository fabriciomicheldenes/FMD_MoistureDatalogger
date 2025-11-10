/**
 * * @file MCP3008Controller.cpp
 * TODO: @brief <TODO: Descrição breve do propósito do arquivo>
 *
 * @details
 * Parte integrante do projeto Moisture Datalogger.
 * Contém a implementação das rotinas de controle e comunicação do sistema,
 * incluindo o parser de comandos, interface serial e mediador de módulos.
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

#include "Drivers/Mcp3008ChannelSensor.h"

Mcp3008ChannelSensor::Mcp3008ChannelSensor(uint8_t csPin, uint8_t channel, const char* name)
    : _channel(channel), _sensorName(name), _csPin(csPin) {}

#include "Mcp3008ChannelSensor.h"

void Mcp3008ChannelSensor::begin() {
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);
    SPI.begin();
    mcp.begin(_csPin);
    Serial.print(F("[MCP3008 Channel :"));
    Serial.print(_sensorName);
    Serial.println(F("] Inicializado e em execução."));
}

bool Mcp3008ChannelSensor::isAvailable() const {
    return true;  // TODO verfificar algum modo de testar o MCP
}

const char* Mcp3008ChannelSensor::getDeviceName() const {
    return _sensorName;
}

void Mcp3008ChannelSensor::printStatus() const {
    Serial.print('[');
    Serial.print(_sensorName);
    Serial.println(F("] MCP3008 pronto."));
}

void Mcp3008ChannelSensor::response() {
    if (!isAvailable()) {
        Serial.println(F("⚠️ MCP3008 driver não inicializado."));
        return;
    }
    float value = mcp.readADC(_channel);
    Serial.print(_sensorName);
    Serial.print(F(" = "));
    Serial.println(value, 2);
}

void Mcp3008ChannelSensor::getData(SensorData& out) {
    out.numericCount = 1;
    out.textCount = 0;
    out.numeric[0] = isAvailable() ? mcp.readADC(_channel) : NAN;
}

void Mcp3008ChannelSensor::appendToLogLine(String& line) {
    SensorData data;
    getData(data);
    line += String(data.numeric[0], 2) + ';';
}

String Mcp3008ChannelSensor::logLine() {
    SensorData data;
    getData(data);
    return String(data.numeric[0], 2) + ';';
}
