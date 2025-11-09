/**
 * * @file serialInterface.h
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

#pragma once
#include <Arduino.h>
#include "CommandParser.h"

class SerialInterface {
   public:
    using CallbackFn = void (*)(const String&);

    SerialInterface(HardwareSerial& serial, uint32_t baud = 115200);

    void begin();
    void setCallback(CallbackFn cb) { callback = cb; }
    void handleCommand(const char& cmd);
    void handleCommand(const String& cmd);
    void printPrompt();
    void sendMessage(const char& msg);
    void sendMessage(const String& msg);

   private:
    HardwareSerial& serialPort;
    CommandParser parser;
    CallbackFn callback;
    uint32_t baud;
};
