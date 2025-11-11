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

#pragma once
#include <Arduino.h>

/**
 * @brief Interface base para serviços de sistema (SDCard, WiFi, etc.)
 * 
 * Define métodos mínimos para inicialização e diagnóstico de periféricos
 * que não são sensores, mas que fornecem funcionalidades de suporte.
 */
class ISystemService {
public:
    virtual ~ISystemService() = default;

    /** Inicializa o serviço (ex: inicia SPI, WiFi.begin(), etc.) */
    virtual void begin() = 0;

    /** Retorna true se o serviço está operacional */
    virtual bool isReady() const = 0;

    /** Retorna o nome identificador do serviço */
    virtual const char* getName() const = 0;

    /** Exibe status básico via serial */
    virtual void printStatus() const = 0;
};
