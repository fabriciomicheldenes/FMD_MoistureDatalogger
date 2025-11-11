/**
 * * @file DeviceManager.h
 * @brief Implementação do gerenciador de dispositivos centralizado usando padrão Registry
 *
 * Responsável por:
 * - Instanciar todos os dispositivos
 * - Inicializá-los de forma uniforme
 * - Fornecer acesso centralizado
 * - Exibir status geral do sistema
 *
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

#pragma once
#include "Core/DeviceManager.h"
#include "Core/ISensor.h"
#include "Core/ISystemService.h"
#include "Drivers/AdcChannelSensor.h"
#include "Drivers/DHTController.h"
#include "Drivers/MCP3008ChannelSensor.h"
#include "Drivers/RTC1307Controller.h"
#include "Drivers/SDCardRWController.h"
#include "HardwarePins.h"

#define MAX_DEVICES 32
#define MAX_SERVICES 4
constexpr int DHT_TYPE = 22;

class DeviceManager {
   public:
    static void registerDevices();
    static void registerServices();
    static void begin();
    static void printAllStatus();
    static ISensor* getDevice(const String& name);
    static ISystemService* getService(const char* name);
    static ISensor* getDeviceAt(uint8_t index);
    static uint8_t getDeviceCount();
    static uint8_t getServiceCount();
    static void listDevices();
    static SDCardRWController* getSDController() { return &sdController; }
    static bool updateDevices() {
        Serial.println(F("[DeviceManager] Atualizando dispositivos..."));
        // if (!sdController.isReady())
            sdController.updateSDCard();
        // futuramente: wifi.update(), rtc.update(), etc.
        return true;
    }

   private:
    inline static SDCardRWController sdController{HardwarePins::CS_SDCARD};
    inline static RTC1307Controller rtc{};
    inline static DHTController dht{HardwarePins::DHT_PIN, DHT_TYPE};

    inline static Mcp3008ChannelSensor mcpChannels[8] = {
        Mcp3008ChannelSensor(HardwarePins::CS_MCP3008, 0, "MCP_CH0"),
        Mcp3008ChannelSensor(HardwarePins::CS_MCP3008, 1, "MCP_CH1")};

    // inline static Mcp3008ChannelSensor mcp_ch0{HardwarePins::CS_MCP3008, 0, "MCP_CH0"};

    inline static AdcChannelSensor adcChannels[16] = {
        AdcChannelSensor(HardwarePins::ADC0_PIN, "ADC_CH1"),
        AdcChannelSensor(HardwarePins::ADC1_PIN, "ADC_CH2"),
        AdcChannelSensor(HardwarePins::ADC2_PIN, "ADC_CH3"),
        AdcChannelSensor(HardwarePins::ADC3_PIN, "ADC_CH4"),
        AdcChannelSensor(HardwarePins::ADC4_PIN, "ADC_CH5"),
        AdcChannelSensor(HardwarePins::ADC5_PIN, "ADC_CH6"),
        AdcChannelSensor(HardwarePins::ADC6_PIN, "ADC_CH7"),
        AdcChannelSensor(HardwarePins::ADC7_PIN, "ADC_CH8"),
        AdcChannelSensor(HardwarePins::ADC8_PIN, "ADC_CH9"),
        AdcChannelSensor(HardwarePins::ADC9_PIN, "ADC_CH10"),
        AdcChannelSensor(HardwarePins::ADC10_PIN, "ADC_CH11"),
        AdcChannelSensor(HardwarePins::ADC11_PIN, "ADC_CH12"),
        AdcChannelSensor(HardwarePins::ADC12_PIN, "ADC_CH13"),
        AdcChannelSensor(HardwarePins::ADC13_PIN, "ADC_CH14"),
        AdcChannelSensor(HardwarePins::ADC14_PIN, "ADC_CH15"),
        AdcChannelSensor(HardwarePins::ADC15_PIN, "ADC_CH16")};

    inline static ISensor* devices[MAX_DEVICES] = {nullptr};
    inline static ISystemService* services[MAX_SERVICES] = {nullptr};
    inline static uint8_t deviceCount = 0;
    inline static uint8_t serviceCount = 0;
};
