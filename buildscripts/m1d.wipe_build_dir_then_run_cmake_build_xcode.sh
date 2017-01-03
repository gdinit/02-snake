#!/usr/local/bin/dash

########################################################################################################################
# m1d.wipe_build_dir_then_run_cmake_build_xcode.sh
########################################################################################################################


# MAIN #################################################################################################################
/bin/echo			""					&& \
/bin/echo			"removing build dir..."			&& \
/bin/rm -rf			"../build"				&&	\
/bin/echo			""					&& \
/bin/echo			"recreating build dir..."		&& \
/bin/mkdir			"../build"				&&	\
/bin/echo			""					&& \
cd				"../build"				&&	\
/usr/local/bin/cmake -G		"Xcode"					../source
# EOF ##################################################################################################################

