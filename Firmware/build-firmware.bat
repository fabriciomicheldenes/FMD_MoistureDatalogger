@echo off
setlocal ENABLEDELAYEDEXPANSION

:: ===============================================================
:: AVR Firmware Build & Upload Script (by FMD)
:: ===============================================================

set BUILD_DIR=build
set TOOLCHAIN_FILE=cmake\avr-toolchain.cmake
set FIRMWARE=SoilLogger_Firmware

:: ---- DETECTA PORTAS DISPONÃVEIS ----
echo.
echo ==========================================
echo Portas seriais disponiveis:
echo ==========================================
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$ports = Get-CimInstance Win32_PnPEntity | Where-Object { $_.Name -match '\(COM[0-9]+\)' } | ForEach-Object { if ($_.Name -match '\((COM[0-9]+)\)') { [PSCustomObject]@{ Port=$Matches[1]; Name=$_.Name } } }; if(-not $ports -or $ports.Count -eq 0) { $ports = [System.IO.Ports.SerialPort]::GetPortNames() | ForEach-Object { [PSCustomObject]@{ Port=$_; Name='(sem nome detectado)' } } }; $ports | Sort-Object Port | Format-Table -AutoSize"
echo ==========================================
echo.

set /p COM_PORT="Digite a porta (ex: COM4): "
if "%COM_PORT%"=="" (
    echo Porta nao informada. Abortando.
    pause
    exit /b
)

echo Porta selecionada: %COM_PORT%
echo.

:: ---- GARANTE QUE O BUILD FOI CONFIGURADO ----
if not exist "%BUILD_DIR%" (
    echo Gerando ambiente CMake...
    cmake -S . -B %BUILD_DIR% -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN_FILE% -DARDUINO_PORT=%COM_PORT%
    if errorlevel 1 (
        echo Erro ao configurar o CMake.
        pause
        exit /b
    )
) else (
    echo Atualizando configuracao existente...
    cmake -S . -B %BUILD_DIR% -DARDUINO_PORT=%COM_PORT%
)

:: ---- COMPILA O PROJETO ----
echo Compilando firmware...
ninja -C %BUILD_DIR%
if errorlevel 1 (
    echo Erro na compilacao.
    pause
    exit /b
)

:: ---- UPLOAD USANDO O ALVO CMAKE ----
echo Gravando firmware no Arduino via Ninja...
ninja -C %BUILD_DIR% upload
if errorlevel 1 (
    echo Falha no upload.
    pause
    exit /b
)

echo Upload concluIdo com sucesso na %COM_PORT%!
pause
exit /b