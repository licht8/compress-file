@echo off
setlocal

:: Check for CMake presence
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo CMake not found. Please install CMake.
    exit /b 1
)

:: Check for GCC compiler presence
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo GCC compiler not found. Please install GCC.
    exit /b 1
)

:: Prompt user to choose build mode
echo Choose build mode:
echo 1. Debug
echo 2. Release
set /p BUILD_MODE="Enter build mode number (1 or 2): "

:: Validate user input and set corresponding build mode
if "%BUILD_MODE%"=="1" (
    set CMAKE_BUILD_TYPE=Debug
) else if "%BUILD_MODE%"=="2" (
    set CMAKE_BUILD_TYPE=Release
) else (
    echo Invalid build mode number. Please choose 1 or 2.
    exit /b 1
)

:: Check if build directory exists, create if it doesn't
if not exist build (
    mkdir build
)

:: Change directory to build
cd build

:: Run CMake commands for building
cmake -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% -G "MinGW Makefiles" ..
if %errorlevel% neq 0 (
    echo Error running cmake -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% -G "MinGW Makefiles".
    exit /b 1
)

cmake --build .
if %errorlevel% neq 0 (
    echo Error running cmake --build .
    exit /b 1
)

echo Build completed successfully.

pause
endlocal
exit /b 0
