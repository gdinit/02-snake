@ECHO OFF
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: w8.rebuild_and_run.bat
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:::::::::::::::::::: CONFIGURATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
SETLOCAL


:::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CALL "w0_uncrustify_source_files.bat"					&& ^
CALL "w0b_cppcheck.bat"							&& ^
CALL "w2.execute_cmake_--build.bat"					&& ^
CALL "w3.cleanup_build_dir.bat"						&& "wrun.bat"
:: NOTE1: we use an && to launch the program at the bottom to ensure a failed build WILL NOT trigger an execution
:: NOTE2: in the "wrun.bat" bit, do not call this with CALL or output will be auto-cleared on program exit which makes it difficult to debug
:: EOF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
