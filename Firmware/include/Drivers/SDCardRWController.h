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

#include "Core/ISystemService.h"

#include <Arduino.h>
#include <SD.h>

class SDCardRWController : public ISystemService {
   public:
    explicit SDCardRWController(uint8_t csPin)
        : cs(csPin), initialized(false), lastErrorMsg("Not initialized") {}

    bool begin() override;
    bool isReady() const override { return initialized; }
    const char* getName() const override { return "SDCard"; }
    void printStatus() const override;

    /** Adiciona uma linha CSV ao arquivo atual */
    bool appendCSV(const String& dataLine, bool verbose = false);

    /** Retorna o texto da última falha */
    String lastError() const { return lastErrorMsg; }

    bool isCardInserted() const;
    void updateLedStatus(bool noCard, bool fail, bool ok);
    void setupLedBlinkTimer();
    void blinkStart();
    void blinkEnd();
    void updateSDCard();

   private:
    uint8_t cs;
    bool initialized = false;
    String filename = "log.csv";
    String lastErrorMsg;
};
