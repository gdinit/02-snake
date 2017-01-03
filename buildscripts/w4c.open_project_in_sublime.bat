@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w4c.open_project_in_sublime.bat
::
:: Note: If there are more than one *.sublime-project files IN the ..\build directory, only the last one will be opened.
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::




:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
::
SET SUBLIME_EXECUTABLE_FILE="C:\Program Files\Sublime Text 3\sublime_text.exe"
:::::::::: clean up
IF EXIST __tmp__sublime_project_file_list		DEL /Q /F __tmp__sublime_project_file_list
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash



:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::: compile sublime-project file list under build and write it to a tmp file
CD /D "..\build"
DIR /B "*.sublime-project" > __tmp__sublime_project_file_list
:::::::::: prepare full path prefix & apply to all files
:: capture current directory IN a variable
SET "CURPATH=%cd%"
:: save the current directory to a tmp file
>__tmp__curpath_without_trailing_backslash ECHO %CURPATH%
:: append a single backslash to the current path IN the tmp file, save as new tmp file
FOR /F "tokens=*" %%a			IN (__tmp__curpath_without_trailing_backslash)		DO (ECHO %%a\) > __tmp__curpath_with_trailing_backslash
:: our current-directory prefix is now ready. read it into a new variable
SET /P curdirprefix=<__tmp__curpath_with_trailing_backslash
:: modify the compiled list of all sublime-project files, and for each file, add the cur-dir-prefix
FOR /F "tokens=*" %%a			IN (__tmp__sublime_project_file_list)			DO (ECHO %curdirprefix%%%a) >> __tmp__source_files_list_fullpath
:: read the full path from the temp file
FOR /F "usebackq delims=" %%L		IN ("__tmp__source_files_list_fullpath")		DO SET "FILEFULLPATH=%%L"
SET "FILEFULLPATH=%FILEFULLPATH:/=\%"
:: launch Sublime Text 3, with each sublime-project file as parameter
START "" %SUBLIME_EXECUTABLE_FILE% %FILEFULLPATH%


:::::::::: clean up
IF EXIST __tmp__sublime_project_file_list		DEL /Q /F __tmp__sublime_project_file_list
IF EXIST __tmp__source_files_list_fullpath		DEL /Q /F __tmp__source_files_list_fullpath
IF EXIST __tmp__curpath_without_trailing_backslash	DEL /Q /F __tmp__curpath_without_trailing_backslash
IF EXIST __tmp__curpath_with_trailing_backslash		DEL /Q /F __tmp__curpath_with_trailing_backslash
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
