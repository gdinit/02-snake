#!/usr/local/bin/dash

########################################################################################################################
# m1d___wipe_build_dir_then_run_cmake_build_unix_makefiles_with_sfgui.sh
########################################################################################################################


# MAIN #################################################################################################################
rm -rf ../build
mkdir ../build

cd ../build && cmake -G "Unix Makefiles"					\
-D "SFGUI_ROOT:PATH=/Library/Frameworks/sfgui/v.0.3.1/compiledHere/lib"		\
-D "SFGUI_INCLUDE_DIR:PATH=/Library/Frameworks/sfgui/v.0.3.1/source/include"	\
../source
# EOF ##################################################################################################################
