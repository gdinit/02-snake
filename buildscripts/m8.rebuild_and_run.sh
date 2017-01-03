#!/usr/local/bin/dash

########################################
# m.rebuild_and_run.sh
########################################


# MAIN #################################
# do NOT put the wildcard in double quotes or it will break
./m2.execute_cmake_--build.sh && ./mrun.sh &
# EOF ##################################
