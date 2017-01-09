@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: launch_cppcheck_gui.bat
::
::
:: This script does the following: 
:: 1) scan all source code files under "source" directory and output to the console
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



:::::::::: CONFIGURATION - begin
SET CPPCHECKGUI_EXE_FILE="C:\dev\prg\tools\Cppcheck\cppcheckgui.exe"
SET CPPCHECK_PROJECT_FILE="C:\g\snakeprivate\buildscripts\static_analysis\cppcheck\project.cppcheck"
:::::::::: CONFIGURATION - end










:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING

:::::::::::::::::::: MAIN - begin
:: update user
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
:: launch cppcheck, process each source/header file (using cppcheck's default known-file-extensions)
START "" %CPPCHECKGUI_EXE_FILE% %CPPCHECK_PROJECT_FILE%
:::::::::::::::::::: MAIN - end

:: EOF
