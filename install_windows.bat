@echo off

REM Clear previous installation
IF EXIST "C:\Program Files\bismuto\bismuto.exe" (
    del "C:\Program Files\bismuto\bismuto.exe"
)
IF EXIST "C:\Program Files\bismuto" (
    rmdir /S /Q "C:\Program Files\bismuto"
)

REM Create a build directory in %TEMP%
set BUILD_DIR=%TEMP%\bismuto_build
IF EXIST "%BUILD_DIR%" (
    rmdir /S /Q "%BUILD_DIR%"
)

REM Configure
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_TOOLCHAIN_FILE=cmake\windows.cmake --no-warn-unused-cli -S . -B "%BUILD_DIR%" -G Ninja

REM Build
cmake --build "%BUILD_DIR%" --config Release --target all --

REM Install
cmake --install "%BUILD_DIR%" --config Release --prefix "C:\Program Files\bismuto"

REM Cleanup
rmdir /S /Q "%BUILD_DIR%"
