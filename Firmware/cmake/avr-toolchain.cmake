# ===============================================================
# ðŸ§° AVR TOOLCHAIN FILE â€“ Auto-detect e fallback (by FMD)
# ===============================================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Caminho fixo do toolchain (ajuste conforme necessÃ¡rio)
set(AVR_DEFAULT_PATH "E:/AVR/avr8-gnu-toolchain-win32_x86_64/bin")

# Evita buscar libs/includes do host
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# -------------------------------------------------------------------
# Detecta ferramentas
# -------------------------------------------------------------------
find_program(AVR_GCC avr-gcc)
find_program(AVR_GPP avr-g++)
find_program(AVR_AR avr-ar)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_OBJDUMP avr-objdump)
find_program(AVR_SIZE avr-size)
find_program(AVRDUDE avrdude)

if (NOT AVR_GCC)
    message(WARNING "âš ï¸  AVR-GCC nÃ£o encontrado no PATH. Tentando em ${AVR_DEFAULT_PATH}...")
    find_program(AVR_GCC avr-gcc PATHS "${AVR_DEFAULT_PATH}" NO_DEFAULT_PATH)
    find_program(AVR_GPP avr-g++ PATHS "${AVR_DEFAULT_PATH}" NO_DEFAULT_PATH)
    find_program(AVR_AR avr-ar PATHS "${AVR_DEFAULT_PATH}" NO_DEFAULT_PATH)
    find_program(AVR_OBJCOPY avr-objcopy PATHS "${AVR_DEFAULT_PATH}" NO_DEFAULT_PATH)
    find_program(AVR_OBJDUMP avr-objdump PATHS "${AVR_DEFAULT_PATH}" NO_DEFAULT_PATH)
    find_program(AVR_SIZE avr-size PATHS "${AVR_DEFAULT_PATH}" NO_DEFAULT_PATH)
    find_program(AVRDUDE avrdude PATHS "${AVR_DEFAULT_PATH}" NO_DEFAULT_PATH)
endif()

if (NOT AVR_GCC)
    message(FATAL_ERROR "âŒ AVR-GCC nÃ£o encontrado! Verifique o caminho em ${AVR_DEFAULT_PATH}")
endif()

set(CMAKE_C_COMPILER   ${AVR_GCC})
set(CMAKE_CXX_COMPILER ${AVR_GPP})
set(CMAKE_AR           ${AVR_AR})
set(CMAKE_OBJCOPY      ${AVR_OBJCOPY})
set(CMAKE_OBJDUMP      ${AVR_OBJDUMP})
set(CMAKE_SIZE         ${AVR_SIZE})

# MCU e clock
set(MCU atmega2560 CACHE STRING "AVR microcontroller type")
set(F_CPU 16000000UL CACHE STRING "CPU clock frequency")

add_compile_definitions(F_CPU=${F_CPU})
add_compile_options(-mmcu=${MCU} -Os -Wall -Wextra -ffunction-sections -fdata-sections)
add_link_options(-Wl,--gc-sections)

message(STATUS "âœ… AVR-GCC detectado: ${AVR_GCC}")
message(STATUS "ðŸ”§ MCU: ${MCU} @ ${F_CPU}")