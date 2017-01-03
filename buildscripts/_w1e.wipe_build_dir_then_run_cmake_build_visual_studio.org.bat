@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w1e.wipe_build_dir_then_run_cmake_build_visual_studio.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL
SET PATH=%PATH%;C:/dev/compilers/mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0/bin
SET PATH=%PATH%;C:/dev/prg/tools/CMake/bin
SET PATH=%PATH%;C:/dev/libs/SFML/SFML-2.4.0-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.0
SET PATH=%PATH%;C:/dev/libs/SFML/SFML-2.4.0-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.0/lib
SET CMAKE_BINARY="C:/dev/prg/tools/CMake/bin/cmake.exe"
SET PROJECT_BUILD_DIR="../build"

:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
IF EXIST %PROJECT_BUILD_DIR%			RD /Q /S %PROJECT_BUILD_DIR%
MKDIR %PROJECT_BUILD_DIR%
CD %PROJECT_BUILD_DIR%
%CMAKE_BINARY% ^
-D "SFML_ROOT:PATH=C:/dev/libs/SFML/SFML-2.4.0-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.0" ^
-D "SFML_STATIC_LIBRARIES:BOOL=TRUE" ^
-D "LINK_DIRECTORIES:PATH=C:/dev/libs/SFML/SFML-2.4.0-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.0" ^
-D "INCLUDE_DIRECTORIES:PATH=C:/dev/libs/SFML/SFML-2.4.0-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.0" ^
-G "Visual Studio 14 2015" ^
../source
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
