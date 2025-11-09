/**
 * * @file RTC1307Controller.cpp
 *
 * @brief Controlador do módulo RTC DS1307
 *
 * @details
 * Implementa a interface ISensor, fornecendo data e hora formatadas
 * e integração direta com o SystemMediator e DeviceManager.
 * Compatível com SensorData e comandos GET/SET DATE.
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

#include "Drivers/RTC1307Controller.h"

RTC1307Controller::RTC1307Controller() {}

void RTC1307Controller::begin() {
    if (!rtc.begin()) {
        Serial.println(F("[RTC1307] Erro: módulo não detectado."));
        return;
    }

    if (!rtc.isrunning()) {
        Serial.println(F("[RTC1307] RTC parado, ajustando data padrão."));
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    } else {
        Serial.println(F("[RTC1307] Inicializado e em execução."));
    }
}

bool RTC1307Controller::isAvailable() const {
    return rtc.isrunning();
}

void RTC1307Controller::printStatus() const {
    if (!rtc.isrunning()) {
        Serial.println(F("[RTC1307] Não está em execução."));
        return;
    }

    DateTime now = rtc.now();
    Serial.print(F("[RTC1307] "));
    Serial.print(now.year());
    Serial.print('/');
    Serial.print(now.month());
    Serial.print('/');
    Serial.print(now.day());
    Serial.print(' ');
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
    Serial.print(':');
    Serial.println(now.second());
}

void RTC1307Controller::response() {
    if (!rtc.isrunning()) {
        Serial.println(F("⚠️ RTC não disponível."));
        return;
    }

    DateTime now = rtc.now();
    Serial.print(F("📅 "));
    Serial.print(now.year());
    Serial.print('/');
    Serial.print(now.month());
    Serial.print('/');
    Serial.print(now.day());
    Serial.print(F(" ⏰ "));
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
    Serial.print(':');
    Serial.println(now.second());
}

void RTC1307Controller::getData(SensorData& out) {
    if (!rtc.isrunning()) {
        out.textCount = 0;
        return;
    }

    DateTime now = rtc.now();
    out.text[0] = String(now.year()) + "/" + String(now.month()) + "/" + String(now.day());
    out.text[1] = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
    out.textCount = 2;
}

void RTC1307Controller::getFormattedDate(char* dateBuf, char* timeBuf) {
    DateTime now = rtc.now();
    sprintf(dateBuf, "%04d/%02d/%02d", now.year(), now.month(), now.day());
    sprintf(timeBuf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
}

void RTC1307Controller::setDateTime(const String& datetime) {
    // Formato esperado: "yyyy-mm-dd hh:mm:ss"
    if (datetime.length() < 19) {
        Serial.println(F("❌ Formato inválido para SET DATE"));
        return;
    }

    int year = datetime.substring(0, 4).toInt();
    int month = datetime.substring(5, 7).toInt();
    int day = datetime.substring(8, 10).toInt();
    int hour = datetime.substring(11, 13).toInt();
    int min = datetime.substring(14, 16).toInt();
    int sec = datetime.substring(17, 19).toInt();

    rtc.adjust(DateTime(year, month, day, hour, min, sec));
    Serial.println(F("✅ Data/hora atualizadas com sucesso."));
}

void RTC1307Controller::appendToLogLine(String& line) {
    SensorData data;
    getData(data);

    if (data.textCount >= 2) {
        line += data.text[0] + ';' + data.text[1] + ';';
    } else {
        line += F("----/--/--;--:--:--;");  // placeholders
    }
}

String RTC1307Controller::logLine() {
    SensorData data;
    getData(data);

    if (data.textCount >= 2) {
        return data.text[0] + ';' + data.text[1] + ';';
    } else {
        return F("----/--/--;--:--:--;");  // placeholders
    }
}