/**
 * * @file CommandParser.h
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

// Enumeração dos tipos de comandos reconhecidos
enum CommandType {
    CMD_INVALID,
    CMD_HELP,
    CMD_START,
    CMD_STOP,
    CMD_STATUS,
    CMD_LIST_DEVICES,
    CMD_READ_SENSOR,
    CMD_SET_DATE,
    CMD_GET_DATE
};

// Estrutura de resultado do parser de comandos
struct CommandResult {
    CommandType type;     // Tipo de comando
    String message;       // Mensagem descritiva (resposta humana)
    String deviceTarget;  // Nome do dispositivo-alvo, ex: "DHT22", "RTC1307", "SOIL"
    String args;          // Argumentos adicionais (ex: "2025-11-07 22:12:07")
};

// Classe de parsing de comandos seriais
class CommandParser {
public:
    CommandResult processCommand(const String& cmd);
};
