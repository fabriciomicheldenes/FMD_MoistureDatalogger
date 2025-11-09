cmake_minimum_required(VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (WIN32)
    set(CMAKE_COLOR_MAKEFILE ON)
endif()
add_compile_options(-fdiagnostics-color=always)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(SoilLogger_Firmware LANGUAGES C CXX)
set(FIRMWARE_NAME ${PROJECT_NAME})

# ===============================================================
# 🔧 Configura toolchain AVR
# ===============================================================
if (NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/avr-toolchain.cmake" CACHE FILEPATH "" FORCE)
endif()

# ===============================================================
# 📁 Estrutura de diretórios
# ===============================================================
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")

# ===============================================================
# 📦 Arduino Core
# ===============================================================
file(TO_CMAKE_PATH "$ENV{USERPROFILE}" USER_PROFILE_PATH)
message("User Profile Path: ${USER_PROFILE_PATH}")

# REMOVIDO: add_definitions(-include Arduino.h)
# REMOVIDO: add_compile_definitions(ARDUINO_MAIN)

# Caminhos principais do Arduino Core e variantes
set(ARDUINO_CORE_PATH "${USER_PROFILE_PATH}/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino")
set(ARDUINO_VARIANT_PATH "${USER_PROFILE_PATH}/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/variants/mega")
set(ARDUINO_LIBRARIES_PATH "${USER_PROFILE_PATH}/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/libraries")

# Bibliotecas das bibliotecas nativas Arduino
set(ARDUINO_LIB_SPI_PATH "${ARDUINO_LIBRARIES_PATH}/SPI/src")
set(ARDUINO_LIB_WIRE_PATH "${ARDUINO_LIBRARIES_PATH}/Wire/src")
set(ARDUINO_LIB_SD_PATH "${ARDUINO_LIBRARIES_PATH}/SD/src")
set(ARDUINO_LIB_SoftSerial_PATH "${ARDUINO_LIBRARIES_PATH}/SoftwareSerial/src")

# Bibliotecas externas (submódulos)
set(RTCLIB_PATH "${CMAKE_SOURCE_DIR}/lib/RTClib/src")
set(Adafruit_BusIO_PATH "${CMAKE_SOURCE_DIR}/lib/Adafruit_BusIO")
set(DHTSensor_PATH "${CMAKE_SOURCE_DIR}/lib/DHTSensor")
set(SDCard_PATH "${CMAKE_SOURCE_DIR}/lib/SDCard/src")
set(Adafruit_Sensor_PATH "${CMAKE_SOURCE_DIR}/lib/Adafruit_Sensor")

# Diretórios de include unificados
include_directories(
    "${INC_DIR}"
    "${INC_DIR}/Core"
    "${INC_DIR}/Drivers"
    "${ARDUINO_CORE_PATH}"
    "${ARDUINO_VARIANT_PATH}"
    "${ARDUINO_LIBRARIES_PATH}"
    "${ARDUINO_LIB_SoftSerial_PATH}"
    "${ARDUINO_LIB_SPI_PATH}"
    "${ARDUINO_LIB_WIRE_PATH}"
    "${ARDUINO_LIB_WIRE_PATH}/utility"
    "${ARDUINO_LIB_SD_PATH}"
    "${RTCLIB_PATH}"
    "${Adafruit_BusIO_PATH}"
    "${DHTSensor_PATH}"
    "${SDCard_PATH}"
    "${SDCard_PATH}/utility"
    "${Adafruit_Sensor_PATH}"
)

# Fontes do core Arduino
file(GLOB_RECURSE ARDUINO_CORE_SRC
    "${ARDUINO_CORE_PATH}/*.c"
    "${ARDUINO_CORE_PATH}/*.cpp"
    "${ARDUINO_CORE_PATH}/*.S"

    "${ARDUINO_VARIANT_PATH}/*.c"
    "${ARDUINO_VARIANT_PATH}/*.cpp"
    "${ARDUINO_VARIANT_PATH}/*.S"
)

# Fontes das libs nativas Arduino
file(GLOB ARDUINO_LIB_SPI_SRC
    "${ARDUINO_LIB_SPI_PATH}/*.cpp"
)
file(GLOB ARDUINO_LIB_WIRE_SRC
    "${ARDUINO_LIB_WIRE_PATH}/*.cpp"
    "${ARDUINO_LIB_WIRE_PATH}/utility/*.c"
)
file(GLOB ARDUINO_LIB_SoftSerial_SRC
    "${ARDUINO_LIB_SoftSerial_PATH}/*.cpp"
)

# Fontes das libs externas (submódulos)
file(GLOB RTCLIB_SRC
    "${RTCLIB_PATH}/*.cpp"
)
file(GLOB Adafruit_BusIO_SRC
    "${Adafruit_BusIO_PATH}/*.cpp"
)
file(GLOB DHTSensor_SRC
    "${DHTSensor_PATH}/*.cpp"
)
file(GLOB SDCard_SRC
    "${SDCard_PATH}/*.cpp"
    "${SDCard_PATH}/utility/*.cpp"
)
file(GLOB Adafruit_Sensor_SRC
    "${Adafruit_Sensor_PATH}/*.cpp"
)

# Remove o main.cpp duplicado do core
list(FILTER ARDUINO_CORE_SRC EXCLUDE REGEX ".*/main\\.cpp$")

# Remove arquivos .h da lista de sources (estavam sendo incluídos pelo GLOB_RECURSE)
list(FILTER ARDUINO_CORE_SRC EXCLUDE REGEX ".*\\.h$")

# Debug: mostra quantos arquivos do core foram encontrados
list(LENGTH ARDUINO_CORE_SRC CORE_COUNT)
message(STATUS "📦 Arduino Core: ${CORE_COUNT} arquivos encontrados")

# ===============================================================
# 🧩 Fontes do projeto
# ===============================================================
file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/Core/*.cpp"
    "${SRC_DIR}/Drivers/*.cpp"
)

add_executable(${FIRMWARE_NAME}.elf
    #Sources do projeto
    ${SRC_FILES}

    #Sources do Arduino Core
    ${ARDUINO_CORE_SRC}

    #Sources das libs nativas Arduino
    ${ARDUINO_LIB_SPI_SRC}
    ${ARDUINO_LIB_WIRE_SRC}
    ${ARDUINO_LIB_SoftSerial_SRC}

    #Sources das libs externas
    ${RTCLIB_SRC}
    ${Adafruit_BusIO_SRC}
    ${DHTSensor_SRC}
    ${SDCard_SRC}
    ${Adafruit_Sensor_SRC}
)

# Define macros do Arduino
target_compile_definitions(${FIRMWARE_NAME}.elf PRIVATE
    ARDUINO=10819           # Versão do Arduino IDE (simulada)
    ARDUINO_AVR_MEGA2560   # Board específico
    ARDUINO_ARCH_AVR       # Arquitetura
)

target_compile_options(${FIRMWARE_NAME}.elf PRIVATE
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os
    -Wall -Wextra
    -ffunction-sections
    -fdata-sections
    -fno-exceptions        # Desabilita exceções C++ (economia de memória)
    -fno-threadsafe-statics # Desabilita thread-safe para static (economia de memória)
)

target_link_options(${FIRMWARE_NAME}.elf PRIVATE
    -mmcu=${MCU}
    -Wl,--gc-sections
    -lm                    # Biblioteca matemática
)

# ===============================================================
# 💾 Geração de HEX/BIN
# ===============================================================
add_custom_command(TARGET ${FIRMWARE_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${FIRMWARE_NAME}.elf ${FIRMWARE_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary -R .eeprom ${FIRMWARE_NAME}.elf ${FIRMWARE_NAME}.bin
    COMMENT "💾 Gerando arquivos .HEX e .BIN"
)
add_custom_command(TARGET ${FIRMWARE_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} -A ${FIRMWARE_NAME}.elf
    COMMAND ${CMAKE_SIZE} ${FIRMWARE_NAME}.elf || ${CMAKE_SIZE} ${FIRMWARE_NAME}.elf
    COMMENT "📏 Exibindo uso de memória (flash e SRAM)"
)

# ===============================================================
# 🧭 Localização do AVRDUDE
# ===============================================================
# 1. Tenta achar automaticamente no PATH
find_program(AVRDUDE avrdude)

# 2. Caso não encontrado, tenta nos locais padrão do Arduino IDE
if (NOT AVRDUDE)
    # Caminho do Arduino IDE 1.x
    if (EXISTS "C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avrdude.exe")
        set(AVRDUDE "C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avrdude.exe")
    endif()

    # Caminho do Arduino IDE 2.x
    if (EXISTS "$ENV{USERPROFILE}/AppData/Local/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude.exe")
        set(AVRDUDE "$ENV{USERPROFILE}/AppData/Local/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude.exe")
    endif()
endif()

# ===============================================================
# 🚀 Alvo de upload
# ===============================================================
# Porta serial do Arduino
set(ARDUINO_PORT "COM4" CACHE STRING "Porta serial para upload AVR")

if (AVRDUDE)
    add_custom_target(upload
        COMMAND "${AVRDUDE}" -v -p m2560 -c wiring -P ${ARDUINO_PORT} -b 115200 -D
                -U flash:w:${FIRMWARE_NAME}.hex:i
        DEPENDS ${FIRMWARE_NAME}.elf
        COMMENT "🚀 Gravando firmware no Arduino Mega 2560 via ${ARDUINO_PORT}"
    )
else()
    message(WARNING "⚠️  AVRDUDE não encontrado – o alvo 'upload' será desabilitado.")
endif()