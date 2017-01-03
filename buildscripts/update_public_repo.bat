@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: wrun.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:: MAIN :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL
DEL /Q "..\..\01-pong\*.*"

IF EXIST "..\..\01-pong\assets\"			RD /Q /S "..\..\01-pong\assets\"
XCOPY /S /E /C /I "..\assets" "..\..\01-pong\assets"

IF EXIST "..\..\01-pong\documentation\"			RD /Q /S "..\..\01-pong\documentation\"
XCOPY /S /E /C /I "..\documentation" "..\..\01-pong\documentation"

IF EXIST "..\..\01-pong\exe_icon_for_windows\"			RD /Q /S "..\..\01-pong\exe_icon_for_windows\"
XCOPY /S /E /C /I "..\exe_icon_for_windows" "..\..\01-pong\exe_icon_for_windows"

IF EXIST "..\..\01-pong\source\"			RD /Q /S "..\..\01-pong\source\"
XCOPY /S /E /C /I "..\source" "..\..\01-pong\source"

IF EXIST "..\..\01-pong\.gitignore"			DEL /Q "..\..\01-pong\.gitignore"
XCOPY /C /I "..\.gitignore" "..\..\01-pong\"

IF EXIST "..\..\01-pong\readme.txt"			DEL /Q "..\..\01-pong\readme.txt"
XCOPY /C /I "..\readme.txt" "..\..\01-pong\"

:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
