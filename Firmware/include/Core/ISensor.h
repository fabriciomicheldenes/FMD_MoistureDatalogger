/**
 * * @file ISensor.h
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

struct SensorData {
    float numeric[4];
    String text[2];
    uint8_t numericCount = 0;
    uint8_t textCount = 0;
};

class ISensor {
   public:
    virtual void begin() = 0;
    virtual bool isAvailable() const = 0;
    virtual const char* getDeviceName() const = 0;
    virtual void printStatus() const = 0;
    virtual void response() = 0;
    virtual void getData(SensorData& out) = 0;
    virtual void appendToLogLine(String& line) = 0;
    virtual String logLine() = 0;
};