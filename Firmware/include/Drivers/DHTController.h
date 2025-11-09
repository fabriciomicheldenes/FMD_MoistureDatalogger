/**
 * * @file DHTController.h
 *
 * @brief Controlador do sensor DHT22 (umidade e temperatura)
 *
 * @details
 * Implementa a interface ISensor, fornecendo leituras unificadas
 * de temperatura e umidade. Compatível com o sistema de coleta
 * polimórfico via SensorData.
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
#include <DHT.h>
#include "Core/ISensor.h"

class DHTController : public ISensor {
   public:
    DHTController(uint8_t pin, uint8_t type = DHT22);

    void begin() override;
    bool isAvailable() const override;
    const char* getDeviceName() const override { return ("DHT22"); }
    void printStatus() const override;
    void response() override;
    void getData(SensorData& out) override;
    void appendToLogLine(String& line) override;
    String logLine() override;

   private:
    mutable DHT dht;  // mutable permite leitura em métodos const
    uint8_t dhtPin;
    uint8_t dhtType;
    mutable float lastTemp = NAN;
    mutable float lastHum = NAN;
};