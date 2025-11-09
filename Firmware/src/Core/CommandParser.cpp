/**
 * * @file CommandParser.cpp

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

#include "CommandParser.h"
#include "Auxiliary/StringManipulation.h"

CommandResult CommandParser::processCommand(const String& cmd) {
    String upper = cmd;
    upper.toUpperCase();
    CommandResult res;

    if (upper.equals("HELP")) {
        res.type = CMD_HELP;
        res.message = F("Comandos: HELP, START, STOP, STATUS, LIST, READ <DEV>, GET DATE, SET DATE <YYYY-MM-DD HH:MM:SS>");
        return res;
    }

    if (upper.equals("START")) {
        res.type = CMD_START;
        res.message = F("Iniciando streaming...");
        return res;
    }

    if (upper.equals("STOP")) {
        res.type = CMD_STOP;
        res.message = F("Parando streaming...");
        return res;
    }

    if (upper.equals("STATUS")) {
        res.type = CMD_STATUS;
        res.message = F("Status do sistema:");
        return res;
    }

    if (upper.equals("LIST DEVICES") || upper.equals("LIST")) {
        res.type = CMD_LIST_DEVICES;
        res.message = F("Listando dispositivos registrados...");
        return res;
    }

    // 🔹 Leitura genérica de sensor: "READ DHT22"
    if (upper.startsWith("READ ")) {
        res.type = CMD_READ_SENSOR;
        res.deviceTarget = cmd.substring(5);
        res.deviceTarget.trim();
        res.message = "Lendo sensor " + res.deviceTarget;
        return res;
    }

    // 🔹 GET DATE
    if (upper.startsWith("GET DATE")) {
        res.type = CMD_GET_DATE;
        res.deviceTarget = "RTC1307";
        res.message = F("Obtendo data e hora do RTC...");
        return res;
    }

    // 🔹 SET DATE yyyy-mm-dd hh:mm:ss
    if (upper.startsWith("SET DATE")) {
        res.type = CMD_SET_DATE;
        res.deviceTarget = "RTC1307";
        res.args = cmd.substring(8);
        res.args.trim();
        res.message = "Definindo data/hora: " + res.args;
        return res;
    }

    // 🔹 Caso não reconhecido
    res.type = CMD_INVALID;
    res.message = F("Comando inválido. Digite HELP.");
    return res;
}