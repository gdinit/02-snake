#!/usr/local/bin/dash

########################################################################################################################
# m1b___wipe_build_dir_then_run_cmake_build_codeblocks.sh
########################################################################################################################


# MAIN #################################################################################################################
rm -rf ../build
mkdir ../build
cd ../build && cmake -G "CodeBlocks - Unix Makefiles"  ../source
# EOF ##################################################################################################################
