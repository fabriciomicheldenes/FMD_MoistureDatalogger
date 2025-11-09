/**
 * * @file app.cpp
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

#include <Arduino.h>
#include "Core/DeviceManager.h"
#include "Core/SerialInterface.h"
#include "Core/SystemMediator.h"

HardwareSerial& serial = Serial;
SerialInterface serialInterface(serial, 115200UL);
SystemMediator systemMediator(&serialInterface);

unsigned long lastSaveTime = 0;
const unsigned long SAVE_INTERVAL = 5000;

int main(void) {
    init();
#if defined(USBCON)
    USBDevice.attach();
#endif

    setup();

    for (;;) {
        loop();
#if defined(USBCON)
        if (serialEventRun)
            serialEventRun();
#endif
    }

    return 0;
}

void setup() {
    serialInterface.begin();
    DeviceManager::begin();
    systemMediator.setInstance(&systemMediator);
}

void loop() {
    if (serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        serialInterface.handleCommand(cmd);
    }

    unsigned long currentMillis = millis();
    // Se já se passaram 5 segundos desde o último log
    if (currentMillis - lastSaveTime >= SAVE_INTERVAL) {
        lastSaveTime = currentMillis;
        systemMediator.generateSaveLine();
    }
}