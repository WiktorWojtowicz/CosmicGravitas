@echo off

set ROOT_DIR=%cd%
set BUILD_DIR="%ROOT_DIR%\build"
set RELEASE_DIR="%BUILD_DIR%\release"

mkdir %BUILD_DIR% > nul 2>&1
mkdir %RELEASE_DIR% > nul 2>&1

cd %RELEASE_DIR%

echo Installing...
cmake --install %RELEASE_DIR% 
if %ERRORLEVEL% NEQ 0 (
    echo Installing failed with exit code %ERRORLEVEL%.
    exit
)

echo Done! Your executable is in now installed
