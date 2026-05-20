@echo off
"C:\Program Files\CMake\bin\cmake.exe" -B build -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows
if %ERRORLEVEL% neq 0 (
    echo.
    echo CONFIGURE FAILED
    pause
) else (
    echo.
    echo Configure succeeded. Run build.bat to compile.
)
