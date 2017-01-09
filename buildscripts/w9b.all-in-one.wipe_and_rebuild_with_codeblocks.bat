@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w9b.all-in-one.wipe_and_rebuild_with_codeblocks.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL


:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CALL "w0_uncrustify_source_files.bat"					&& ^
CALL "w0b_cppcheck.bat"							&& ^
CALL "w1b.wipe_build_dir_then_run_cmake_build_codeblocks.bat"		&& ^
CALL "w2.execute_cmake_--build.bat"					&& ^
CALL "w3.cleanup_build_dir.bat"						&& ^
CALL "w4b.open_project_in_codeblocks.bat"				&& ^
DIR "..\build\"								&& ^
"wrun.bat"
:: NOTE1: we use an && to launch the program at the bottom to ensure a failed build WILL NOT trigger an execution
:: NOTE2: in the "wrun.bat" bit, do not call this with CALL or output will be auto-cleared on program exit which makes it difficult to debug
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
