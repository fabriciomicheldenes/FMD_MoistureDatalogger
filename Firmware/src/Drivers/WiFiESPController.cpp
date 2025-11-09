/**
 * * @file WiFiESPController.cpp
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

#include "WiFiESPController.h"

WiFiESPController::WiFiESPController(const HardwarePins::ESP01Pins& pinsConfig,
                                     HardwareSerial& serialPort)
    : espSerial(&serialPort), pins(pinsConfig) {}

void WiFiESPController::begin(long baud) {
    // Configura pinos de controle
    pinMode(pins.rst, OUTPUT);
    pinMode(pins.en, OUTPUT);
    digitalWrite(pins.en, HIGH);
    digitalWrite(pins.rst, HIGH);

    espSerial->begin(baud);
    delay(200);

    // Faz um reset rápido do módulo
    reset();
    sendCommand("AT\r\n", "OK");
}

void WiFiESPController::reset() {
    digitalWrite(pins.rst, LOW);
    delay(100);
    digitalWrite(pins.rst, HIGH);
    delay(1000);
}

bool WiFiESPController::connect(const char* ssid, const char* password) {
    String cmd = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"\r\n";
    connected = sendCommand(cmd.c_str(), "WIFI GOT IP", 10000);
    return connected;
}

bool WiFiESPController::sendData(const String& data) {
    if (!connected)
        return false;

    String cmd = "AT+CIPSEND=" + String(data.length()) + "\r\n";
    if (!sendCommand(cmd.c_str(), ">"))
        return false;

    espSerial->print(data);
    return sendCommand("", "SEND OK", 5000);
}

bool WiFiESPController::sendCommand(const char* cmd, const char* ack, uint32_t timeout) {
    if (cmd && *cmd)
        espSerial->print(cmd);
    uint32_t start = millis();
    String response;
    while (millis() - start < timeout) {
        while (espSerial->available()) {
            response += (char)espSerial->read();
            if (response.indexOf(ack) != -1)
                return true;
        }
    }
    return false;
}
