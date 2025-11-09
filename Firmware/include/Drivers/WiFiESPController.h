/**
 * * @file WiFiESPController.h
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
#include "HardwarePins.h"

#define WIFI_HAS_ISCONNECTED

class WiFiESPController {
   public:
    explicit WiFiESPController(const HardwarePins::ESP01Pins& pins,
                               HardwareSerial& serialPort = Serial1);

    void begin(long baud = 115200);
    bool connect(const char* ssid, const char* password);
    bool sendData(const String& data);
    bool isConnected() const { return connected; }

   private:
    HardwareSerial* espSerial;
    HardwarePins::ESP01Pins pins;
    bool connected = false;

    void reset();
    bool sendCommand(const char* cmd, const char* ack, uint32_t timeout = 2000);
};
