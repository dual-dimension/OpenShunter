@echo off
if not exist build mkdir build
cd build
cmake .. || goto error
cmake --build . || goto error
goto end

:error
echo.
echo Build failed.
pause
exit /b 1

:end
