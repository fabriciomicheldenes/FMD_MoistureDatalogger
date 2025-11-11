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
#include "HardwarePins.h"

// volatile bool ledState = false;
// volatile unsigned long lastToggle = 0;

// Variáveis estáticas para ISR
volatile bool ledBlinkEnabled = false;
volatile bool ledState = false;
volatile unsigned long blinkStopTime = 0;

bool SDCardRWController::begin() {
    pinMode(HardwarePins::NoCard, OUTPUT);
    pinMode(HardwarePins::CardFail, OUTPUT);
    pinMode(HardwarePins::CardOK, OUTPUT);
    setupLedBlinkTimer();
    pinMode(HardwarePins::MissingSdCard, INPUT_PULLUP);

    updateLedStatus(false, false, false);

    if (!isCardInserted()) {
        Serial.println(F("⚠️ Nenhum cartão detectado."));
        updateLedStatus(true, false, false);  // vermelho aceso
        initialized = false;
        lastErrorMsg = F("No card");
        return false;
    }

    if (!SD.begin(cs)) {
        Serial.println(F("❌ Falha ao inicializar SDCard."));
        updateLedStatus(false, true, false);  // amarelo aceso
        initialized = false;
        lastErrorMsg = F("Init fail");
        return false;
    }

    Serial.println(F("🟢 SDCard inicializado com sucesso."));
    updateLedStatus(false, false, true);
    initialized = true;
    lastErrorMsg = F("OK");
    return true;
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

bool SDCardRWController::isCardInserted() const {
    return digitalRead(HardwarePins::MissingSdCard) == LOW;  // LOW = presente
}

void SDCardRWController::updateLedStatus(bool noCard, bool fail, bool ok) {
    digitalWrite(HardwarePins::NoCard, noCard);
    digitalWrite(HardwarePins::CardFail, fail);
    digitalWrite(HardwarePins::CardOK, ok);
}

void SDCardRWController::setupLedBlinkTimer() {
    // Configura Timer2 modo normal, prescaler 1024
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;

    // (16MHz / 1024) / 256 = ~61 Hz overflow
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
    TIMSK2 |= (1 << TOIE2);  // habilita interrupção de overflow
}

// TODO: migrar Timer2 ISR para Core/Interrupts.cpp quando houver múltiplos serviços com
// interrupções.
ISR(TIMER2_OVF_vect) {
    static uint8_t counter = 0;
    counter++;

    if (counter >= 3) {  // ~12 Hz / 2 = 6 Hz de piscar
        counter = 0;

        // Desativa automaticamente quando chega ao tempo limite
        if (blinkStopTime && millis() > blinkStopTime) {
            ledBlinkEnabled = false;
            blinkStopTime = 0;
            analogWrite(HardwarePins::CardOK, 255);  // acende fixo
        }

        if (ledBlinkEnabled) {
            ledState = !ledState;
            analogWrite(HardwarePins::CardOK, ledState ? 128 : 0);
        }
    }
}

void SDCardRWController::blinkStart() {
    ledBlinkEnabled = true;
    blinkStopTime = 0;  // sem agendamento de parada
}

void SDCardRWController::blinkEnd() {
    // agenda o fim do piscar para daqui 300 ms, sem bloquear
    blinkStopTime = millis() + 300;
}

void SDCardRWController::updateSDCard() {
    Serial.print(F("SDCHK initialized="));
    Serial.print(initialized);
    Serial.print(F(" pin="));
    Serial.println(digitalRead(HardwarePins::MissingSdCard));

    static unsigned long lastToggle = 0;
    static bool blinkState = false;

    // 1️⃣ Verifica se o cartão está presente
    bool cardInserted = (digitalRead(HardwarePins::MissingSdCard) == LOW);

    if (!cardInserted) {
        // Cartão removido
        initialized = false;
        updateLedStatus(true, false, false);  // Vermelho (NoCard)
        return;
    }

    // 2️⃣ Se o cartão foi inserido mas ainda não inicializado, tenta inicializar
    if (!initialized) {
        if (begin()) {
            updateLedStatus(false, false, true);  // Verde fixo (OK)
        } else {
            updateLedStatus(false, true, false);  // Amarelo (falha)
        }
        return;
    }
}