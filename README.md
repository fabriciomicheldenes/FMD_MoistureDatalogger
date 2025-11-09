# 🌱 Datalogger de Umidade do Solo *FMD_Soil Moisture*

## 📘 Visão Geral

 O **FMD_Soil Moisture** é um sistema autônomo para **monitoramento contínuo de umidade e temperatura do solo**, com armazenamento local e conectividade Wi-Fi e Serial-USB.

Projetado para aplicações agrícolas e experimentais, o sistema registra dados ambientais em longo prazo com alta confiabilidade e baixo custo.

O projeto é baseado em um **Arduino Mega 2560**, que coleta leituras de múltiplos sensores capacitivos de umidade do solo **HW-101 HW**, além de um sensor **DHT22** para temperatura e umidade do ar.

Os dados são registrados em **cartão microSD** e podem ser sincronizados via **módulo ESP-01 (ESP8266)** para monitoramento remoto.

## 🧩 Hardware - Arquitetura Geral

### 🔹 Componentes Principais

| Módulo / Componente                                         | Função                            | Interface         | Observações                                                        |
| ----------------------------------------------------------- | --------------------------------- | ----------------- | ------------------------------------------------------------------ |
| **Arduino Mega 2560**                                       | Unidade de controle principal     | –                 | 16 canais analógicos nativos + expansão SPI                        |
| **Sensores de Umidade Capacitivos (HW-101 HW V1.2 / V2.0)** | Medição de umidade do solo        | Analógica (0–5 V) | 16 sensores diretos + 2 via MCP3008                                |
| **MCP3008**                                                 | Conversor A/D externo de 8 canais | SPI               | Expande entradas                                                   |
| **DHT22**                                                   | Temperatura e umidade do ar       | 1 fio (digital)   | Sensor ambiente                                                    |
| **ESP-01 (ESP8266)**                                        | Comunicação Wi-Fi                 | UART              | Upload de dados ou configuração remota                             |
| **RTC DS1307 + Bateria 3 V**                                | Relógio e calendário              | I²C               | Mantém data/hora durante desligamento                              |
| **MicroSD Card (SPI)**                                      | Armazenamento local               | SPI               | Indicadores de status via LEDs                                     |
| **LEDs de Status (3×)**                                     | Indicação do estado do SDCard     | GPIO              | - Sem cartão<br>- Falha no cartão<br>- Cartão OK (pisca ao gravar) |

## ⚙️ Recursos Adicionais (não implementados (no firmware) na versão atual)

| Recurso                | Componente              | Interface | Estado    |
| ---------------------- | ----------------------- | --------- | --------- |
| Memória EEPROM externa | 24C32WP                 | I²C       | Reservado |
| Display LCD 1602       | HD44780 (modo 4 bits)   | GPIO      | Reservado |
| Display 5110           | Nokia 5110              | SPI       | Reservado |
| Teclado                | Teclado matricial 4×4   | GPIO      | Reservado |
| Expansão ADC           | MCP3008 (canais livres) | SPI       | Reservado |

## 🔌 Conectores de Expansão

| Conector                | Interface               | Descrição                                          |
| ----------------------- | ----------------------- | -------------------------------------------------- |
| **Expansão A**          | I²C, 1× I/O, 2× PWM     | Compatível com sensores e atuadores externos       |
| **Expansão B**          | SPI, CS, 1× I/O, 1× PWM | Para módulos SPI adicionais                        |
| **Expansão C**          | SPI, CS, 1× I/O, 1× PWM | Similar à Expansão B                               |
| **Expansão D (Serial)** | TX/RX, 1× I/O, 2× PWM   | Conexão de módulos seriais ou periféricos externos |
| **Planejado**           | RS-232 e RS-485         | UART + controle de hardware                        |

## 🧾 Histórico de Versões do Hardware

| Versão   | Plataforma            | Descrição                                               | Status    |
| -------- | --------------------- | ------------------------------------------------------- | --------- |
| **V0.1** | Proteus (ISIS + ARES) | Primeira versão funcional do circuito e layout          | ✅ Testada |
| **V0.2** | KiCad 8               | Novo layout, roteamento otimizado e serigrafia revisada | 🔄 Atual  |

A **versão V0.1**, desenvolvida no *Proteus (ISIS + ARES)*, foi a primeira versão funcional do hardware, mas apresentava algumas limitações de projeto, como trilhas longas e cruzadas, componentes em ambos os lados e uso reduzido de plano de terra, exigindo pequenas correções com jumpers.

A **versão V0.2**, redesenhada no *KiCad 8*, manteve o mesmo circuito eletrônico, mas trouxe um layout mais maduro e eficiente: todos os componentes estão em um único lado, as trilhas são curtas e bem distribuídas, e há ampla costura de planos de terra em ambas as faces, resultando em **melhor imunidade a ruídos** e maior confiabilidade do sistema.

## 💾 Firmware

O firmware foi desenvolvido em **Arduino C++**, com foco em modularidade e confiabilidade para operação contínua.  
Ele realiza:

- Leitura sequencial dos sensores de umidade e do DHT22  
- Registro no **RTC DS1307** para carimbo de data/hora  
- Armazenamento no **microSD (FAT32)**  
- Indicação visual do status via LEDs  
- Envio de dados via **Wi-Fi (ESP-01)**  

### 🔹 Bibliotecas utilizadas

- `DHT.h` – leitura de temperatura/umidade  
- `Wire.h` – comunicação I²C (RTC e EEPROM)  
- `SPI.h` – comunicação SPI (SD e MCP3008)  
- `SD.h` – gerenciamento do cartão microSD  
- `SoftwareSerial.h` – interface serial com ESP-01  

> 🔗 Detalhes do código e pinagem em [`Firmware/README.md`](Firmware/README.md)

---

## 💻 Software de Visualização

O software de visualização foi desenvolvido em **Python/Qt**, permitindo:

- Leitura direta dos arquivos `.CSV` ou `.TXT` do microSD  
- Exibição de gráficos de tendência (umidade x tempo)  
- Exportação dos dados para análise estatística  
- Modo de operação **offline (SD)** e **online (Wi-Fi)**  

> 🔗 Documentação completa em [`Software/README.md`](Software/README.md)

---