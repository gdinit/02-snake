@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w0b_cppcheck.bat
::
::
:: This script does the following: 
:: 1) scan all source code files under "source" directory and output to the console
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



:::::::::: CONFIGURATION - begin
SET CPPCHECK_EXE_FILE="C:\dev\prg\tools\Cppcheck\cppcheck.exe"
SET SOURCE_CODE_MAIN_DIR="../source"

:: name of the directory that holds headers and inline files
SET INCLUDEDIR="../source"
:::::::::: CONFIGURATION - end










:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING

:::::::::::::::::::: MAIN - begin
:: update user
ECHO.
ECHO.
ECHO w0b_cppcheck.bat LAUNCHING... **************************************
:: initialize
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
::ECHO "*** FIRST LINE *** uncrustify - main dir phase"
:: go to source code directory
CD /D "%SOURCE_CODE_MAIN_DIR%"
ECHO CURRENT DIR is:
CD
ECHO.

:: launch cppcheck, process each source/header file (using cppcheck's default known-file-extensions)
%CPPCHECK_EXE_FILE% ^
--quiet ^
--relative-paths ^
--enable=warning,style,performance,portability,information,unusedFunction ^
-I "%INCLUDEDIR%" ^
--language=c++ ^
--std=c++11 ^
"%SOURCE_CODE_MAIN_DIR%"
ECHO w0b_cppcheck.bat ENDING... **************************************
ECHO.
ECHO.
:::::::::::::::::::: MAIN - end

::	DISABLED BIT:
::	--error-exitcode=1 ^

:: EOF
