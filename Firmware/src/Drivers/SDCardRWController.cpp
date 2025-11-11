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

#include "Drivers/SDCardRWController.h"

void SDCardRWController::begin() {
    if (!SD.begin(cs)) {
        initialized = false;
        lastErrorMsg = F("Init failed");
        Serial.println(F("❌ Falha ao inicializar o SDCard."));
    } else {
        initialized = true;
        lastErrorMsg = F("OK");
        Serial.println(F("🟢 SDCard inicializado com sucesso."));
    }
}

void SDCardRWController::printStatus() const {
    Serial.print(F("[SDCard] Status: "));
    Serial.println(initialized ? F("OK") : F("FALHA"));
}

bool SDCardRWController::appendCSV(const String& dataLine, bool verbose) {
    if (!initialized) {
        if (verbose)
            Serial.println(F("⚠️ SDCard não inicializado."));
        lastErrorMsg = F("not_ready");
        return false;
    }

    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        lastErrorMsg = F("open_fail");
        if (verbose)
            Serial.println(F("❌ Falha ao abrir arquivo para escrita."));
        return false;
    }

    bool success = file.println(dataLine);
    file.close();

    if (success) {
        lastErrorMsg = F("OK");
        return true;
    } else {
        lastErrorMsg = F("write_fail");
        if (verbose)
            Serial.println(F("❌ Falha ao escrever no SDCard."));
        return false;
    }
}
