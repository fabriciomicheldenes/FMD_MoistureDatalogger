/**
 * * @file SystemMediator.cpp
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

#include "SystemMediator.h"
#include "Core/DeviceManager.h"
#include "Core/SerialInterface.h"

SystemMediator* SystemMediator::instancePtr = nullptr;

void SystemMediator::handleCommandStatic(const CommandResult& result) {
    if (instancePtr)
        instancePtr->handleCommand(result);
}

void SystemMediator::handleCommand(const CommandResult& result) {
    switch (result.type) {
        case CMD_LIST_DEVICES:
            DeviceManager::printAllStatus();
            break;

        case CMD_READ_SENSOR: {
            ISensor* sensor = DeviceManager::getDevice(result.deviceTarget);
            if (sensor && sensor->isAvailable())
                sensor->response();
            else
                sendMessage("⚠️ Sensor não disponível.");
            break;
        }

        case CMD_GET_DATE:
        case CMD_SET_DATE: {
            ISensor* rtc = DeviceManager::getDevice("RTC1307");
            if (rtc)
                rtc->response();
            break;
        }

        case CMD_START:
            sendMessage("🚀 Streaming iniciado!");
            break;

        case CMD_STOP:
            sendMessage("🛑 Streaming parado!");
            break;

        case CMD_STATUS:
            sendMessage("📡 Sistema operando normalmente.");
            break;

        default:
            break;
    }
}

void SystemMediator::sendMessage(const String& msg) {
    if (serialInterface)
        serialInterface->sendMessage(msg);
    else
        Serial.println(msg);
}

/**
 * @brief Gera uma linha unificada de log iterando sobre todos os sensores registrados.
 */
void SystemMediator::generateSaveLine() {
    String line;
    line.reserve(128);

    line = "3;";  // TODO: ID do datalogger, fixo para teste - placeholder

    Serial.print(F("Quantidade de dispositivos: "));
    Serial.println(DeviceManager::getDeviceCount());

    for (uint8_t i = 0; i < DeviceManager::getDeviceCount(); ++i) {
        ISensor* sensor = DeviceManager::getDeviceAt(i);
        sensor->appendToLogLine(line);
    }

    bool saved = false;

    auto* service = DeviceManager::getService("SDCard");
    if (service && service->isReady()) {
        auto* sd = static_cast<SDCardRWController*>(service);
        saved = sd->appendCSV(line);
    }

    line += saved ? F(";SD=OK") : F(";SD=ERR");
    // serialInterface->sendMessage(line);

    // line += "SDCard;";  // TODO: Indicar que dado foi salvo no sdcard antes de enviar para serial


    Serial.println(line);
}
