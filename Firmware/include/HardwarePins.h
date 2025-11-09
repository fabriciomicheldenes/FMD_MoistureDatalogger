/**
 * * @file HardwarePins.h
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

#pragma once
#include <Arduino.h>

/**
 * @brief Define os pinos de hardware utilizados pelo sistema de aquisição.
 *
 * Mantém todos os pinos organizados em uma única estrutura, facilitando
 * ajustes de hardware e manutenção do código.
 *
 * Compatível com Arduino Mega 2560.
 */
class HardwarePins {
   public:
    // --------------------------------------------------
    // 🧩 ADCs
    // --------------------------------------------------
    static constexpr uint8_t CS_MCP3008 = 48;  // Chip Select do ADC externo (SPI)
    static constexpr uint8_t ADC0_PIN = A0;    // ADC interno canal 0
    static constexpr uint8_t ADC1_PIN = A1;    // ADC interno canal 1
    static constexpr uint8_t ADC2_PIN = A2;
    static constexpr uint8_t ADC3_PIN = A3;
    static constexpr uint8_t ADC4_PIN = A4;
    static constexpr uint8_t ADC5_PIN = A5;
    static constexpr uint8_t ADC6_PIN = A6;
    static constexpr uint8_t ADC7_PIN = A7;
    static constexpr uint8_t ADC8_PIN = A8;
    static constexpr uint8_t ADC9_PIN = A9;
    static constexpr uint8_t ADC10_PIN = A10;
    static constexpr uint8_t ADC11_PIN = A11;
    static constexpr uint8_t ADC12_PIN = A12;
    static constexpr uint8_t ADC13_PIN = A13;
    static constexpr uint8_t ADC14_PIN = A14;
    static constexpr uint8_t ADC15_PIN = A15;

    // --------------------------------------------------
    // 🌡️ Sensores de ambiente
    // --------------------------------------------------
    // Sensor de temperatura/umidade DHT22
    static constexpr uint8_t DHT_PIN = 7;

    // --------------------------------------------------
    // ⏰ RTC DS1307 (I2C)
    // --------------------------------------------------
    static constexpr uint8_t I2C_SDA = 20;  // SDA I2C
    static constexpr uint8_t I2C_SCL = 21;  // SCL I2C

    // --------------------------------------------------
    // 💾 SD Card (SPI)
    // --------------------------------------------------
    static constexpr uint8_t CS_SDCARD = 4;  // Chip Select do módulo SD

    // --------------------------------------------------
    // 📡 Módulo Wi-Fi ESP-01 (UART)
    // --------------------------------------------------
    // static constexpr uint8_t ESP01_TX    = 18;  // TX → RX do Mega
    // static constexpr uint8_t ESP01_RX    = 19;  // RX → TX do Mega
    // static constexpr uint8_t ESP01_RST   = 8;   // Reset do ESP-01
    // static constexpr uint8_t ESP01_EN    = 9;   // Enable (CH_PD)
    struct ESP01Pins {
        uint8_t tx;
        uint8_t rx;
        uint8_t rst;
        uint8_t en;
    };

    static constexpr ESP01Pins ESP01{
        18,  // TX → RX do Mega
        19,  // RX → TX do Mega
        8,   // Reset
        9    // Enable (CH_PD)
    };

    // --------------------------------------------------
    // 💡 LEDs e debug
    // --------------------------------------------------
    static constexpr uint8_t LED_STATUS = 13;  // LED onboard

    HardwarePins() = default;
};
