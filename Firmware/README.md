# 🌱 FMD Moisture Datalogger Firmware
Sistema embarcado de registro de umidade do solo desenvolvido por Fabrício Michel Denes.

---

## ⚙️ Ambiente de Desenvolvimento

### 🔧 Requisitos principais
| Componente | Descrição |
|-------------|------------|
| **Compilador AVR-GCC** | Toolchain oficial da Microchip. Caminho padrão: `E:\AVR\avr8-gnu-toolchain-win32_x86_64` |
| **CMake** | ≥ 3.28 com suporte ao generator *Ninja* |
| **Ninja Build** | Sistema de build rápido e compatível com CMake |
| **Arduino Core (AVR)** | Instalado via Arduino IDE (> 2.0). Caminho padrão: `%USERPROFILE%\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6` |
| **AVRDUDE** | Para upload do firmware (`avrdude.exe` no toolchain ou Arduino IDE) |

---

## 🧩 Estrutura de Pastas
```
Firmware/
├── CMakeLists.txt
├── cmake/
│ └── avr-toolchain.cmake
├── src/
│ ├── app.cpp
│ ├── system.cpp
│ └── …
├── include/
│ ├── HardwarePins.h
│ ├── DHT22.h
│ ├── RtcTimer.h
│ └── …
├── build.bat ← script interativo para build + upload
└── build/ ← artefatos gerados (.elf /.hex /.bin)
``` 

---

## 🚀 Compilação e Upload

### 🧰 Opção 1 – Via VS Code + CMake Tools
1. Abrir a pasta `Firmware/` no VS Code.  
2. Selecionar o generator **Ninja**.  
3. Executar **CMake Configure** → **CMake Build**.  
4. O arquivo `.elf` será gerado em `build/`.  
5. Rodar `ninja upload` para gravar no Arduino.

### 🖥️ Opção 2 – Via Terminal
```bash
cd Firmware/build
cmake .. -G "Ninja"
ninja
ninja upload

💡 Opção 3 – Via Script build.bat (interativo)
> build.bat
==========================================
Portas seriais disponíveis:
Port Name
---- ----
COM1  Porta de comunicação (COM1)
COM4  USB-SERIAL CH340 (COM4)
==========================================

Digite a porta (ex: COM4):


O script compila automaticamente e chama ninja upload, enviando o firmware para o Arduino Mega 2560.