@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w1c.wipe_build_dir_then_run_cmake_build_sublime.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL
SET PATH=%PATH%;C:/dev/compilers/mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0/bin
SET PATH=%PATH%;C:/dev/prg/tools/CMake/bin
SET CMAKE_BINARY="C:/dev/prg/tools/CMake/bin/cmake.exe"
SET PROJECT_BUILD_DIR="../build"



:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
IF EXIST %PROJECT_BUILD_DIR%			RD /Q /S %PROJECT_BUILD_DIR%
MKDIR %PROJECT_BUILD_DIR%
CD %PROJECT_BUILD_DIR%
%CMAKE_BINARY% ^
-D "CMAKE_MAKE_PROGRAM:PATH=C:/dev/compilers/mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0/bin/mingw32-make.exe" ^
-D "CMAKE_C_COMPILER:PATH=C:/dev/compilers/mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0/bin/i686-w64-mingw32-gcc.exe" ^
-D "CMAKE_CXX_COMPILER:PATH=C:/dev/compilers/mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0/bin/i686-w64-mingw32-g++.exe" ^
-D "SFML_ROOT:PATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1" ^
-D "SFML_STATIC_LIBRARIES:BOOL=TRUE" ^
-G "Sublime Text 2 - MinGW Makefiles" ^
../source
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
