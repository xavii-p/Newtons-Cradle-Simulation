@echo off

REM Set up Emscripten environment
call C:\DevTools\emsdk-main\emsdk_env.bat

REM Use the full path to CMake if it's not in your PATH
set CMAKE_PATH="C:\Program Files\CMake\bin\cmake.exe"

REM Explicitly use Ninja
set CMAKE_GENERATOR=Ninja

REM Update the path to the Emscripten toolchain file
set EMSCRIPTEN_TOOLCHAIN=%EMSDK%\upstream\emscripten\cmake\Modules\Platform\Emscripten.cmake

REM Check if Ninja is available in the system PATH
where ninja >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Ninja not found in system PATH. Please ensure Ninja is installed and added to your PATH.
    exit /b 1
)

%CMAKE_PATH% -G %CMAKE_GENERATOR% -B build -S . -DCMAKE_TOOLCHAIN_FILE=%EMSCRIPTEN_TOOLCHAIN% -DCMAKE_CROSSCOMPILING_EMULATOR=%EMSDK%\node\18.20.3_64bit\bin\node.exe

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed
    exit /b %ERRORLEVEL%
)

emmake ninja -C build

if %ERRORLEVEL% neq 0 (
    echo Build failed
    exit /b %ERRORLEVEL%
)

echo Build completed successfully