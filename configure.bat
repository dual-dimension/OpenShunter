@echo off
set "INCLUDE=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\atlmfc\include;%INCLUDE%"
"C:\Program Files\CMake\bin\cmake.exe" -B build -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DVCPKG_OVERLAY_TRIPLETS="D:/New Projects/C++/OpenShunter/vcpkg-triplets" -DVCPKG_OVERLAY_PORTS="D:/New Projects/C++/OpenShunter/vcpkg-overlays"
if %ERRORLEVEL% neq 0 (
    echo.
    echo CONFIGURE FAILED
    pause
) else (
    echo.
    echo Configure succeeded. Run build.bat to compile.
)
