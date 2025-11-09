/**
 * * @file MCP3008Controller.cpp
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

#include "MCP3008Controller.h"

MCP3008Controller::MCP3008Controller(uint8_t csPin) : _csPin(csPin) {}

void MCP3008Controller::begin() {
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);
    SPI.begin();
}

uint16_t MCP3008Controller::readChannel(uint8_t channel) {
    if (channel > 7)
        return 0;

    digitalWrite(_csPin, LOW);
    // Envia: Start bit (1), modo single/diff (1), canal (3 bits)
    uint8_t command = 0b11000000 | (channel << 3);

    SPI.transfer(command);
    uint8_t high = SPI.transfer(0x00);
    uint8_t low = SPI.transfer(0x00);
    digitalWrite(_csPin, HIGH);

    // Combina os 10 bits (os 2 menos significativos de 'high' + 'low')
    return ((high & 0x0F) << 8) | low;
}
