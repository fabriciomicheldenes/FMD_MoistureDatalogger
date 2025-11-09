/**
 * * @file SystemMediator.h
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

class DHTController;
class RTC1307Controller;
class SerialInterface;

class SystemMediator {
   public:
    SystemMediator(SerialInterface* serialIf) : serialInterface(serialIf) {}

    static void handleCommandStatic(const CommandResult& result);
    static void setInstance(SystemMediator* inst) { instancePtr = inst; }
    void handleCommand(const CommandResult& result);
    void generateSaveLine();
    void sendMessage(const String& msg);

   private:
    static SystemMediator* instancePtr;
    SerialInterface* serialInterface;
};
