@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w4b.open_project_in_codeblocks.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::: CONFIGURATION - begin
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
::
IF EXIST "c:\Program Files\CodeBlocks\CodeBlocks.exe" (
	SET CODEBLOCKS_EXE_FILE="c:\Program Files\CodeBlocks\CodeBlocks.exe"
	GOTO MAIN
	)
IF EXIST "C:\dev\prg\ide\02hd\CodeBlocks\codeblocks.exe" (
	SET CODEBLOCKS_EXE_FILE="C:\dev\prg\ide\02hd\CodeBlocks\codeblocks.exe"
	GOTO MAIN
	)
IF EXIST "C:\dev\prg\ide\lw\CodeBlocks\codeblocks.exe" (
	SET CODEBLOCKS_EXE_FILE="C:\dev\prg\ide\lw\CodeBlocks\codeblocks.exe"
	GOTO MAIN
	)
:: TODO - add standard/default codeblocks paths here program files\ etc.

:: cannot find CodeBlocks executable file - terminate
GOTO ERR_CANNOT_FIND_CODEBLOCKS_EXECUTABLE_FILE
:::::::::: CONFIGURATION - end



:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING

:::::::::::::::::::: MAIN - begin
:MAIN
:: update user
ECHO.
ECHO w4b.open_project_in_codeblocks.bat RUNNING...
ECHO.
ECHO.
:::::::::: clean up
IF EXIST __tmp__codeblocks_project_file_list		DEL /Q /F __tmp__codeblocks_project_file_list
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash
:::::::::: compile cbp project file list under build and write it to a tmp file
CD /D "..\build"
DIR /B "*.cbp" > __tmp__codeblocks_project_file_list
:::::::::: prepare full path prefix & apply to all files
:: capture current directory IN a variable
SET "CURPATH=%cd%"
:: save the current directory to a tmp file
>__tmp__curpath_without_trailing_backslash ECHO %CURPATH%
:: append a single backslash to the current path IN the tmp file, save as new tmp file
FOR /F "tokens=*" %%a			IN (__tmp__curpath_without_trailing_backslash)		DO (ECHO %%a\) > __tmp__curpath_with_trailing_backslash
:: our current-directory prefix is now ready. read it into a new variable
SET /P curdirprefix=<__tmp__curpath_with_trailing_backslash
:: modify the compiled list of all cbp project files, and for each file, add the cur-dir-prefix
FOR /F "tokens=*" %%a			IN (__tmp__codeblocks_project_file_list)			DO (ECHO %curdirprefix%%%a) >> __tmp__source_files_list_fullpath
:: read the full path from the temp file
FOR /F "usebackq delims=" %%L		IN ("__tmp__source_files_list_fullpath")		DO SET "FILEFULLPATH=%%L"
SET "FILEFULLPATH=%FILEFULLPATH:/=\%"
:: launch CodeBlocks, with each sublime-project file as parameter
START "" %CODEBLOCKS_EXE_FILE% %FILEFULLPATH%


:::::::::: clean up
IF EXIST __tmp__codeblocks_project_file_list		DEL /Q /F __tmp__codeblocks_project_file_list
IF EXIST __tmp__source_files_list_fullpath		DEL /Q /F __tmp__source_files_list_fullpath
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash
ECHO *** LAST LINE *** w4b.open_project_in_codeblocks
ECHO.
ECHO.
ECHO w0_uncrustify_source_files.bat ENDING...
ECHO.
GOTO:EOF
:::::::::::::::::::: MAIN - end


:: couldn't find the codeblocks exe :(
:ERR_CANNOT_FIND_CODEBLOCKS_EXECUTABLE_FILE
ECHO.
ECHO *********************************************************************************************************
ECHO ERROR: Cannot find CodeBlocks executable file.
ECHO Please add the full path to codeblocks.exe in the configuration section of this batch script.
ECHO *********************************************************************************************************
ECHO.
:: EOF
