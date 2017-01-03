@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w3.cleanup_build_dir.bat
::
:: This script cleanup the build directory by deleting matching files.
:: .gitignore, .DS_Store files for now, and in the future, possibly more
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL
SET PROJECT_BUILD_DIR="../build"
SET START_ROOT_DIR=%PROJECT_BUILD_DIR%
SET EXT01="*.gitignore"
SET EXT02="*.DS_Store"



:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CD /D %START_ROOT_DIR%
DEL /S /Q %EXT01%
DEL /S /Q %EXT02%
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
