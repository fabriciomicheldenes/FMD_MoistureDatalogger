/**
 * * @file SDCardRWController.cpp
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

#include "drivers/SDCardRWController.h"

SDCardRWController::SDCardRWController(uint8_t csPin) : chipSelect(csPin) {}

bool SDCardRWController::begin() {
    if (!SD.begin(chipSelect)) {
        Serial.println(F("❌ Falha ao inicializar SD!"));
        return initialized;
    }
    logFile = SD.open(filename, FILE_WRITE);
    if (!logFile) {
        Serial.println(F("❌ Falha ao abrir arquivo de log!"));
        return false;
    }
    logFile.println(F("timestamp;adc0;adc1;...;temp;hum"));
    logFile.flush();
    Serial.println(F("✅ SDCard inicializado."));
    return true;
}

bool SDCardRWController::appendCSV(const String& dataLine) {
    if (!logFile)
        return false;
    logFile.println(dataLine);
    logFile.flush();
    return true;
}

void SDCardRWController::close() {
    if (logFile)
        logFile.close();
}

bool SDCardRWController::isReady() const {
    return initialized;
}