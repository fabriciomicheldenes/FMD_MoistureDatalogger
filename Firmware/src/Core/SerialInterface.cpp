/**
 * * @file SerialInterface.cpp
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

#include "SerialInterface.h"
#include "SystemMediator.h"

SerialInterface::SerialInterface(HardwareSerial& serial, uint32_t baud)
    : serialPort(serial), callback(nullptr), baud(baud) {}

void SerialInterface::begin() {
    serialPort.begin(baud);
    Serial.println(baud);
    sendMessage(F("🟢 SerialInterface iniciado."));
    printPrompt();
}

void SerialInterface::handleCommand(const char& cmd) {
    handleCommand(String(cmd));
}

void SerialInterface::handleCommand(const String& cmd) {
    CommandResult result = parser.processCommand(cmd);
    
    // Envia para o SystemMediator tratar a ação real
    SystemMediator::handleCommandStatic(result);
}

void SerialInterface::sendMessage(const char& msg) {
    serialPort.println(msg);
}

void SerialInterface::sendMessage(const String& msg) {
    serialPort.println(msg);
}

void SerialInterface::printPrompt() {
    serialPort.print(F("\n> "));
}