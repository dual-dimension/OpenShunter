@echo off
"C:\Program Files\CMake\bin\cmake.exe" --build build --config Release
if %ERRORLEVEL% neq 0 (
    echo.
    echo BUILD FAILED - make sure openttd.exe is not running
    pause
) else (
    echo.
    echo Build succeeded.
)
