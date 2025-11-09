/**
 * * @file AdcChannelSensor.h
 *
 * @brief Implementa um canal ADC individual como um sensor independente.
 *
 * @details
 * Cada instância representa um canal analógico (A0–A15, MCP etc.),
 * compatível com a interface ISensor e o formato unificado de log.
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
#include "Core/ISensor.h"

class AdcChannelSensor : public ISensor {
   public:
    // AdcChannelSensor();
    explicit AdcChannelSensor(uint8_t channel, const char* name);

    void begin() override;
    bool isAvailable() const override;
    const char* getDeviceName() const override;
    void printStatus() const override;
    void response() override;
    void getData(SensorData& out) override;
    void appendToLogLine(String& line) override;
    String logLine() override;

   private:
    uint8_t channel;
    const char* sensorName;
};