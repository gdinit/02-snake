#!/bin/bash

########################################################################################################################
# j9l.linux-all-in-one.wipe_build_dir_then_run_cmake_build_unix_makefiles_with_clang.sh
########################################################################################################################


# MAIN #################################################################################################################
export CCC_CC=clang
export CCC_CXX=clang++
/bin/echo                       ""                                      && \
/bin/echo                       "removing build dir..."                 && \
/bin/rm -rf                     "../build"                              && \
/bin/echo                       ""                                      && \
/bin/echo                       "recreating build dir..."               && \
/bin/mkdir                      "../build"                              && \
/bin/echo                       ""                                      && \
cd                              "../build"                              && \
/usr/bin/scan-build			\
	-o .				\
	/usr/bin/cmake3 		\
	-DCMAKE_CXX_COMPILER=clang++ 	\
	-DCMAKE_C_COMPILER=clang 	\
	-G "Unix Makefiles" ".." &&	\
#/usr/bin/make
/usr/local/bin/cmake --build .
# EOF ##################################################################################################################
