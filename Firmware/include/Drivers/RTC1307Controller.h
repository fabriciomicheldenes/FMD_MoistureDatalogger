/**
 * * @file RTC1307Controller.h
 *
 * @brief Controlador do módulo RTC DS1307
 *
 * @details
 * Implementa a interface ISensor, fornecendo data e hora formatadas
 * e integração direta com o SystemMediator e DeviceManager.
 * Compatível com SensorData e comandos GET/SET DATE.
 *
 * @author
 *   Fabrício Michel Denes (FMD) fmicheld@gmail.com
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
#include <RTClib.h>
#include <Wire.h>

#include "Core/ISensor.h"

/**
 * @class RTC1307Controller
 * @brief Controlador para o módulo DS1307/DS3231 via barramento I²C.
 *
 * Implementa interface de alto nível para manipulação de data e hora,
 * incluindo ajuste, leitura e formatação, com inicialização automática
 * e mensagens padronizadas no Serial.
 */
class RTC1307Controller : public ISensor {
   public:
    RTC1307Controller();

    void begin() override;
    bool isAvailable() const override;
    const char* getDeviceName() const override { return "RTC1307"; }
    void printStatus() const override;
    void response() override;
    void getData(SensorData& out) override;
    void appendToLogLine(String& line) override;
    String logLine() override;

    // Métodos adicionais úteis ao SystemMediator
    void getFormattedDate(char* dateBuf, char* timeBuf);
    void setDateTime(const String& datetime);

   private:
    mutable RTC_DS1307 rtc;
};