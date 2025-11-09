/**
 * * @file SDCardRWController.h
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
#include <SD.h>

class SDCardRWController {
   public:
    explicit SDCardRWController(uint8_t csPin = 4);
    bool begin();
    bool appendCSV(const String& dataLine);
    void close();
    bool isReady() const;

   private:
    uint8_t chipSelect;
    File logFile;
    const char* filename = "/datalog.csv";
    bool initialized = false;
};
