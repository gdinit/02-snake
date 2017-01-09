@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w1e.wipe_build_dir_then_run_cmake_build_visual_studio.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL
SET PATH=%PATH%;C:/dev/compilers/mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0/bin
SET PATH=%PATH%;C:/dev/prg/tools/CMake/bin
SET PATH=%PATH%;C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1
SET PATH=%PATH%;C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib
SET CMAKE_BINARY="C:/dev/prg/tools/CMake/bin/cmake.exe"
SET PROJECT_BUILD_DIR="../build"

:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
ECHO DELETING BUILD DIRECTORY...
IF EXIST %PROJECT_BUILD_DIR%			RD /Q /S %PROJECT_BUILD_DIR%
ECHO RECREATING BUILD DIRECTORY...
MKDIR %PROJECT_BUILD_DIR%
CD %PROJECT_BUILD_DIR%
%CMAKE_BINARY% ^
-D "SFML_ROOT:PATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1" ^
-D "SFML_STATIC_LIBRARIES:BOOL=ON" ^
-D "SFML_INCLUDE_DIR:PATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/include" ^
-D "LINK_DIRECTORIES:PATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib" ^
-D "SFML_AUDIO_LIBRARY_DYNAMIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-audio-d-2.dll" ^
-D "SFML_AUDIO_LIBRARY_DYNAMIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-audio-2.dll" ^
-D "SFML_AUDIO_LIBRARY_STATIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-audio-d-2.dll" ^
-D "SFML_AUDIO_LIBRARY_STATIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-audio-2.dll" ^
-D "SFML_GRAPHICS_LIBRARY_DYNAMIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-graphics-d-2.dll" ^
-D "SFML_GRAPHICS_LIBRARY_DYNAMIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-graphics-2.dll" ^
-D "SFML_GRAPHICS_LIBRARY_STATIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-graphics-d-2.dll" ^
-D "SFML_GRAPHICS_LIBRARY_STATIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-graphics-2.dll" ^
-D "SFML_NETWORK_LIBRARY_DYNAMIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-network-d-2.dll" ^
-D "SFML_NETWORK_LIBRARY_DYNAMIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-network-2.dll" ^
-D "SFML_NETWORK_LIBRARY_STATIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-network-d-2.dll" ^
-D "SFML_NETWORK_LIBRARY_STATIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-network-2.dll" ^
-D "SFML_SYSTEM_LIBRARY_DYNAMIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-system-d-2.dll" ^
-D "SFML_SYSTEM_LIBRARY_DYNAMIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-system-2.dll" ^
-D "SFML_SYSTEM_LIBRARY_STATIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-system-d-2.dll" ^
-D "SFML_SYSTEM_LIBRARY_STATIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-system-2.dll" ^
-D "SFML_WINDOW_LIBRARY_DYNAMIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-window-d-2.dll" ^
-D "SFML_WINDOW_LIBRARY_DYNAMIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-window-2.dll" ^
-D "SFML_WINDOW_LIBRARY_STATIC_DEBUG:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-window-d-2.dll" ^
-D "SFML_WINDOW_LIBRARY_STATIC_RELEASE:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/bin/sfml-window-2.dll" ^
-D "FLAC_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libFLAC.a" ^
-D "FREETYPE_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libfreetype.a" ^
-D "JPEG_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libjpeg.a" ^
-D "OGG_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libogg.a" ^
-D "OPENAL_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libopenal32.a" ^
-D "VORBISENC_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libvorbisenc.a" ^
-D "VORBISFILE_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libvorbisfile.a" ^
-D "VORBIS_LIBRARY:FILEPATH=C:/dev/libs/SFML/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib/libvorbis.a" ^
-G "Visual Studio 14 2015" ^
../source
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
