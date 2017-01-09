@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: wrun.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:: MAIN :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL
DEL /Q "..\..\02-snake\*.*"

IF EXIST "..\..\02-snake\assets\"			RD /Q /S "..\..\02-snake\assets\"
XCOPY /S /E /C /I "..\assets" "..\..\02-snake\assets"

IF EXIST "..\..\02-snake\documentation\"			RD /Q /S "..\..\02-snake\documentation\"
XCOPY /S /E /C /I "..\documentation" "..\..\02-snake\documentation"

IF EXIST "..\..\02-snake\exe_icon_for_windows\"			RD /Q /S "..\..\02-snake\exe_icon_for_windows\"
XCOPY /S /E /C /I "..\exe_icon_for_windows" "..\..\02-snake\exe_icon_for_windows"

IF EXIST "..\..\02-snake\source\"			RD /Q /S "..\..\02-snake\source\"
XCOPY /S /E /C /I "..\source" "..\..\02-snake\source"

IF EXIST "..\..\02-snake\.gitignore"			DEL /Q "..\..\02-snake\.gitignore"
XCOPY /C /I "..\.gitignore" "..\..\02-snake\"

IF EXIST "..\..\02-snake\readme.txt"			DEL /Q "..\..\02-snake\readme.txt"
XCOPY /C /I "..\readme.txt" "..\..\02-snake\"

:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
