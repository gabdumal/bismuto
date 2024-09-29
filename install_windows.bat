@echo off

REM Check for administrator privileges
net session >nul 2>&1
if %errorLevel% NEQ 0 (
    echo This script requires administrator privileges. Please run as administrator.
    exit /b 1
)

REM Create a build directory in %TEMP%
set TEMP_DIR=%TEMP%\bismuto_build
IF EXIST "%TEMP_DIR%" (
    rmdir /S /Q "%TEMP_DIR%"
)
mkdir "%TEMP_DIR%"

REM Set installation directory
set INSTALL_DIR=C:\Program Files (x86)\bismuto

REM Clear previous installation
IF EXIST "%INSTALL_DIR%\bismuto.exe" (
    del "%INSTALL_DIR%\bismuto.exe"
)
IF EXIST "%INSTALL_DIR%" (
    rmdir /S /Q "%INSTALL_DIR%"
)

REM Install dependencies

REM Check if argparse is installed
set argaparse_hpp_found=0
IF EXIST "%PROGRAMFILES%"\argparse\include\argparse\argparse.hpp (
    set argaparse_hpp_found=1
    echo Found argparse.hpp in Program Files
)
IF EXIST "%PROGRAMFILES(X86)%"\argparse\include\argparse\argparse.hpp (
    set argaparse_hpp_found=1
    echo Found argparse.hpp in Program Files x86
)
IF %argaparse_hpp_found% EQU 0 (
    echo Have not found argparse.hpp in Program Files or Program Files x86
    echo Installing argparse...
    
    REM Clone the argparse repository
    git clone https://github.com/p-ranav/argparse "%TEMP_DIR%"\argparse
    
    REM Build the argparse library
    mkdir "%TEMP_DIR%"\argparse\build
    cmake -DARGPARSE_BUILD_SAMPLES=on -DARGPARSE_BUILD_TESTS=on -S "%TEMP_DIR%"\argparse -B "%TEMP_DIR%"\argparse\build -G "Ninja"
    
    cmake --build "%TEMP_DIR%"\argparse\build --config Release
    
    REM Install the argparse library
    cmake --install "%TEMP_DIR%"\argparse\build --config Release
)

REM Configure
mkdir "%TEMP_DIR%"\build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE --no-warn-unused-cli -S . -B "%TEMP_DIR%"\build -G Ninja

REM Build
cmake --build "%TEMP_DIR%"\build --config Release --target all --

REM Install
cmake --install "%TEMP_DIR%"\build --config Release

REM Set PATH
setx PATH "%PATH%;%INSTALL_DIR%\bin"

REM Cleanup
rmdir /S /Q "%TEMP_DIR%"
