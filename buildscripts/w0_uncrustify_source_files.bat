@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w0_uncrustify_source_files
::
::
:: This script does the following: 
:: 1) compile a list of all source code files that exist in the current dir & any include dirs listed in configuration
:: 2) then execute an `uncrustify` operation on them based on the rules defined in the configuration file
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



:::::::::: CONFIGURATION - begin
SET UNCRUSTIFY_CONFIG_FILE="C:\g\dev\config\uncrustify\uncrustify_config.mine.v.0.62.cfg"
SET UNCRUSTIFY_EXE_FILE="C:\g\dev\infra\prg\uncrustify\uncrustify.exe"
SET SOURCE_CODE_MAIN_DIR="..\source"

:: file extensions that we should be parsing
SET EXT01="*.h"
SET EXT02="*.hpp"
SET EXT03="*.inl"
SET EXT04="*.cc"
SET EXT05="*.cpp"

:: name of the directory that holds headers and inline files
SET INCLUDEDIR="include"
:::::::::: CONFIGURATION - end










:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
:::::::::: DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING

:::::::::::::::::::: MAIN - begin
:: update user
ECHO.
ECHO w0_uncrustify_source_files.bat RUNNING...
ECHO.
ECHO.
:: initialize
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
ECHO "*** FIRST LINE *** uncrustify - main dir phase"
:: go to source code directory
CD /D "%SOURCE_CODE_MAIN_DIR%"
ECHO CURRENT DIR is:
CD
ECHO.
:: clean up bit
IF EXIST __tmp__source_files_list_filename_only		DEL /Q /F __tmp__source_files_list_filename_only	
IF EXIST __tmp__source_files_list_fullpath		DEL /Q /F __tmp__source_files_list_fullpath		
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash	
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash	
:: compile source code file list and write it to a tmp file
DIR /B  %EXT01% %EXT02% %EXT03% %EXT04% %EXT05% > __tmp__source_files_list_filename_only			
:: prepare full path prefix & apply to all files
:: capture current directory IN a variable
SET "CURPATH=%CD%"
:: save the current directory to a tmp file
>__tmp__curpath_without_trailing_backslash ECHO %CURPATH%
:: append a single backslash to the current path IN the tmp file, save as new tmp file
FOR /F "tokens=*" %%a			IN (__tmp__curpath_without_trailing_backslash)			DO (ECHO %%a\)			> __tmp__curpath_with_trailing_backslash	
:: our current-directory prefix is now ready. read it into a new variable
SET /P curdirprefix=<__tmp__curpath_with_trailing_backslash
:: modify the compiled list of all source code files, and for each file, add the cur-dir-prefix
FOR /F "tokens=*" %%a			IN (__tmp__source_files_list_filename_only)			DO (ECHO %curdirprefix%%%a)	>> __tmp__source_files_list_fullpath		

:::::::::: uncrustify all matching source code files
:: launch uncrustify, process each file
%UNCRUSTIFY_EXE_FILE% --no-backup -l CPP -c %UNCRUSTIFY_CONFIG_FILE% -F __tmp__source_files_list_fullpath
:: clean up
IF EXIST __tmp__source_files_list_filename_only		DEL /Q /F __tmp__source_files_list_filename_only
IF EXIST __tmp__source_files_list_fullpath		DEL /Q /F __tmp__source_files_list_fullpath
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash
:: completing the `process the main dir` phase
ECHO "*** LAST LINE *** uncrustify - main dir phase"
ECHO.
ECHO.
:: end of phase






:: process the "include/" directory next (only if it exists)

:: attempt to enter the include dir
CD %INCLUDEDIR%
::IF %ERRORLEVEL% NEQ 0 EXIT /b %ERRORLEVEL%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

:: if execution hit this line, we are in include dir. carry on
ECHO *** FIRST LINE *** uncrustify - include dir phase
ECHO CURRENT DIR is:
CD
ECHO.
IF EXIST __tmp__source_files_list_filename_only		DEL /Q /F __tmp__source_files_list_filename_only	
IF EXIST __tmp__source_files_list_fullpath		DEL /Q /F __tmp__source_files_list_fullpath		
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash	
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash	
:: compile source code file list and write it to a tmp file
DIR /B %EXT01%	> __tmp__source_files_list_filename_only
:: prepare full path prefix & apply to all files
:: capture current directory IN a variable
SET CURPATH=%CD%
:: save the current directory to a tmp file
>__tmp__curpath_without_trailing_backslash ECHO %CURPATH%
:: append a single backslash to the current path IN the tmp file, save as new tmp file
FOR /F "tokens=*" %%a			IN (__tmp__curpath_without_trailing_backslash)			DO (ECHO %%a\)			> __tmp__curpath_with_trailing_backslash
:: our current-directory prefix is now ready. read it into a new variable
SET /P curdirprefix=<__tmp__curpath_with_trailing_backslash
:: modify the compiled list of all source code files, and for each file, add the cur-dir-prefix
FOR /F "tokens=*" %%a			IN (__tmp__source_files_list_filename_only)			DO (ECHO %curdirprefix%%%a)	>> __tmp__source_files_list_fullpath

:::::::::: uncrustify all matching source code files
:: launch uncrustify, process each file
%UNCRUSTIFY_EXE_FILE% --no-backup -l CPP -c %UNCRUSTIFY_CONFIG_FILE% -F __tmp__source_files_list_fullpath
:: clean up
IF EXIST __tmp__source_files_list_filename_only		DEL /Q /F __tmp__source_files_list_filename_only
IF EXIST __tmp__source_files_list_fullpath		DEL /Q /F __tmp__source_files_list_fullpath
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash
:: process the "include/" directory next (only if it exists)
ECHO "*** LAST LINE *** uncrustify - include dir phase"
ECHO.
ECHO.
ECHO w0_uncrustify_source_files.bat ENDING...
ECHO.
:::::::::::::::::::: MAIN - end

:: EOF
