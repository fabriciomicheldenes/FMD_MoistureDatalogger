# 🌱  TerraMoistLogger

## TODO: terminar de editar este README

Sistema de Monitoramento de Umidade do Solo – GUI para até 4 TerraMoistSense

O TerraMoistLogger é uma interface gráfica desenvolvida em Qt para monitorar até 4 dispositivos TerraMoistSense, cada um equipado com:

16 sensores analógicos nativos (ATmega2560)

2 sensores externos via MCP3008 (SPI)

**🔢 Total de sensores por dispositivo: 18**

**🔢 Total suportado pela GUI: 4 × 18 = 72 sensores**

O sistema foi criado para ser portátil, leve e compatível com hardware antigo — rodando atualmente em Qt 5.5 - 32 bits, porém planejado para migrar para Qt 6.x, mantendo compatibilidade com versões antigas para uso em netbooks e PCs modestos.

## 📌 Funcionalidades Principais
**-✔️ Autodetecção de dispositivos via USB/Serial**

A GUI detecta automaticamente conexão e desconexão de dispositivos

Atualização de portas monitorada a cada 1 segundo
(implementado em MainWindow::scanSerialPorts() – 

mainwindow

)

**-✔️ Gerenciamento automático das interfaces (ConsoleManager)**

Cada dispositivo é gerenciado por um ConsoleManager, criado dinamicamente:

Instância de QSerialPort

Conexão automática

Leitura de dados em tempo real

Configuração automática do intervalo de registro

(Classes referentes: consolemanager.h, console.h – )

**-✔️ Leitura e exibição de dados de até 72 sensores simultaneamente**

O TerraMoistSense envia dados no formato:

```
YYYY/MM/DD;HH:MM:SS;valorCH1;...;valorCH18;umidade;temperatura;ID_dispositivos;SalvoOUNãonoCartão
````

## A GUI:

organiza em 4 consoles independentes

salva logs (quando ativado)

permite visualizar, limpar e configurar os dispositivos

**-✔️ Configuração de intervalo de registro**

Controlada via combo box (registerFrequency no MainWindow – 

mainwindow

):

5 segundos

10 segundos

1 minuto

5 minutos

15 minutos

30 minutos

60 minutos

120 minutos

**-✔️ Totalmente compatível com hardware antigo**

Qt 5.5 – 32bit usado por compatibilidade com Acer One / Netbooks antigos

Código preparado para migração gradual para Qt 6 (Windows/Linux)

🏗️ Arquitetura Geral da Aplicação
Estrutura principal do projeto
TerraMoistLogger/
│   CMakeLists.txt
│   main.cpp
│   mainwindow.h / .cpp / .ui
│   consolemanager.h / .cpp
│   console.h / .cpp / .ui
│   settingsdialog.h / .cpp / .ui
│   QSerialPortInfoOperatores.h / .cpp
│   images/
│       *.png
│   app.ico
│   TerraMoistLogger.pro
│   TerraMoistLogger.qrc

Diagrama de classes simplificado
MainWindow
 ├── QList<QSerialPortInfo>
 ├── QList<QSerialPort*>
 ├── QList<ConsoleManager*>
 ├── registerFrequency (QComboBox)
 └── scanSerialPorts()  ----> detecta conexão/desconexão

ConsoleManager
 ├── QSerialPort*
 ├── Console*
 ├── Intervalo de registro
 └── Envio/Recepção de dados

Console
 ├── Widget de exibição de dados
 ├── Botões de comando
 └── Sinais Qt para comunicação

🔌 Comunicação Serial
🔍 Autodetecção

O método scanSerialPorts() compara portas atuais com as previamente listadas e, se houver alteração, reconstrói toda a interface automaticamente:

mainwindow

🔧 Configuração automática

O método autoConnect() gera dinamicamente até 4 ConsoleManager, um para cada TerraMoistSense conectado:

mainwindow

📡 Compatibilidade com TerraMoistSense (Firmware)

A GUI foi projetada para trabalhar com as funcionalidades atuais do firmware:

RTC DS1307

DHT22

ADC nativo (ATmega2560 – 16 canais)

ADC MCP3008 (SPI – 2 canais)

SDCard como armazenamento interno

Indicação por LED de presença/erro/atividade

Envio de logs padronizados

Planejamento para futuras versões

Integração com ESP-01 (upload sem fio)

Upload MQTT ou HTTP

Status remoto do dispositivo

Configuração de datalogger via GUI

📦 Build
Requisitos atuais

Qt 5.5 (32 bits)

CMake 3.16+

MinGW 4.9 ou MSVC 2015 (dependendo da build)

Make (Windows)
mkdir build
cd build
cmake ..
cmake --build . --config Release

Executável gerado
build/TerraMoistLogger.exe

🗺️ Roadmap
✔️ Versão atual

GUI funcional com suporte automático para 4 dispositivos

Logging e leitura em tempo real

Compatível com equipamentos antigos

Suporte completo ao protocolo atual do TerraMoistSense

🚧 Versões futuras

Migração para Qt 6

Novo design responsivo

Dashboards com gráficos

Conexão com ESP-01

Banco de dados local SQLite

Exportação para CSV/XLSX

Modo “Live Dashboard” para agrônomos e laboratórios

📚 Licença

O TerraMoistLogger segue a mesma licença do QtSerialPort utilizado internamente, conforme apresentado nos cabeçalhos originais do Qt — como no arquivo mainwindow.cpp:
