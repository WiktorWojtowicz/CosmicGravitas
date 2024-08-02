@echo off

set ROOT_DIR=%cd%
set BUILD_DIR="%ROOT_DIR%\build"
set RELEASE_DIR="%BUILD_DIR%\release"

mkdir %BUILD_DIR% > nul 2>&1
mkdir %RELEASE_DIR% > nul 2>&1

cd %RELEASE_DIR%

echo Running CMake
cmake -S %ROOT_DIR% -DCMAKE_BUILD_TYPE="Release" -B %RELEASE_DIR% %*
if %ERRORLEVEL% NEQ 0 (
    echo CMake failed with exit code %ERRORLEVEL%.
    exit
)

echo Building...
cmake --build %RELEASE_DIR% --parallel 
if %ERRORLEVEL% NEQ 0 (
    echo Build failed with exit code %ERRORLEVEL%.
    exit
)

echo Running CPack
cpack
if %ERRORLEVEL% NEQ 0 (
    echo CPack failed with exit code %ERRORLEVEL%.
    exit
)

echo Done! your executable is in %RELEASE_DIR%
