/**
 * * @file DeviceManager.cpp
 * @brief Implementação do gerenciador de dispositivos centralizado usando padrão Registry
 *
 * Responsável por:
 * - Instanciar todos os dispositivos
 * - Inicializá-los de forma uniforme
 * - Fornecer acesso centralizado
 * - Exibir status geral do sistema
 *
 * @details
 * Parte integrante do projeto MOMEA / Moisture Datalogger.
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

/**
 * @file DeviceManager.cpp
 * @brief Implementação do gerenciador de dispositivos
 *
 * @author Fabrício Michel Denes (FMD)
 * @date 2025
 * @version v0.2.x - Em desenvolvimento
 */

#include "Core/DeviceManager.h"

void DeviceManager::begin() {
    Serial.println(F("🚀 INICIALIZANDO DISPOSITIVOS"));

    registerDevices();

    Serial.println(deviceCount);
    for (size_t i = 0; i < deviceCount; i++) {
        if (devices[i]) {
            devices[i]->begin();
        }
    }

    Serial.println();
    Serial.println(F("✅ INICIALIZAÇÃO CONCLUÍDA"));
}

void DeviceManager::registerDevices() {
    deviceCount = 0;

    // Registra os sensores
    devices[deviceCount++] = &rtc;

    // Registra os canais ADC internos do ATmega2560
    for (uint8_t i = 0; i < 16; i++) {
        devices[deviceCount++] = &adcChannels[i];
    }

    devices[deviceCount++] = &dht;

    // devices[deviceCount++] = &sd; placeholder
    // devices[deviceCount++] = &wifi; placeholder

    Serial.print(F("📋 Dispositivos registrados: "));
    Serial.println(deviceCount);
}

ISensor* DeviceManager::getDevice(const String& name) {
    for (size_t i = 0; i < deviceCount; i++) {
        if (devices[i] && String(devices[i]->getDeviceName()).equalsIgnoreCase(name)) {
            return devices[i];
        }
    }
    return nullptr;
}

ISensor* DeviceManager::getDeviceAt(uint8_t index) {
    if (index < deviceCount)
        return devices[index];
    return nullptr;
}

uint8_t DeviceManager::getDeviceCount() {
    return deviceCount;
}

void DeviceManager::printAllStatus() {
    Serial.println(F("📊 STATUS DOS DISPOSITIVOS"));

    for (size_t i = 0; i < deviceCount; i++) {
        if (devices[i]) {
            devices[i]->printStatus();
        }
    }
    Serial.println();
}

void DeviceManager::listDevices() {
    Serial.println(F("📋 DISPOSITIVOS DISPONÍVEIS"));

    for (size_t i = 0; i < deviceCount; i++) {
        if (devices[i]) {
            Serial.print(F("  • "));
            Serial.print(devices[i]->getDeviceName());
            Serial.print(F(" - "));
            Serial.println(devices[i]->isAvailable() ? F("✅ Disponível") : F("❌ Indisponível"));
        }
    }
    Serial.println();
}
