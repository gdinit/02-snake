@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w2.execute_cmake_--build.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL
SET PATH=%PATH%;C:/dev/compilers/mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0/bin
SET PATH=%PATH%;C:/dev/prg/tools/CMake/bin
SET CMAKE_BINARY="C:/dev/prg/tools/CMake/bin/cmake.exe"
SET PROJECT_BUILD_DIR="../build"
SET START_ROOT_DIR=%PROJECT_BUILD_DIR%



:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
IF EXIST %PROJECT_BUILD_DIR%		CD /D %PROJECT_BUILD_DIR%
%CMAKE_BINARY% --build .
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
