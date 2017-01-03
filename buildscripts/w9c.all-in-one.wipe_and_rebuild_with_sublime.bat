@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w9c.all-in-one.wipe_and_rebuild_with_sublime.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL


:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CALL "w0_uncrustify_source_files.bat"					&& ^
CALL "w1c.wipe_build_dir_then_run_cmake_build_sublime.bat"		&& ^
CALL "w2.execute_cmake_--build.bat"					&& ^
CALL "w3.cleanup_build_dir.bat"						&& ^
CALL "w4c.open_project_in_sublime.bat"					&& ^
DIR "..\build\"								&& ^
"wrun.bat"
:: NOTE1: we use an && to launch the program at the bottom to ensure a failed build WILL NOT trigger an execution
:: NOTE2: in the "wrun.bat" bit, do not call this with CALL or output will be auto-cleared on program exit which makes it difficult to debug
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
