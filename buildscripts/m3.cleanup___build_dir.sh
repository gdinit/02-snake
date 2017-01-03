#!/usr/local/bin/dash

########################################################################################################################
# m4___cleanup___build_dir.sh
#
#
# This script will cleanup the build directory by deleting matching files
# .gitignore, .DS_Store files for now, and in the future, possibly more
########################################################################################################################


# CONFIGURATION ################################################################################################
start_root_dir=${PWD%/*}/build

# MAIN #################################################################################################################
echo "\n******************* cleanup_build_dir script executing *******************"
echo "The value of start_root_dir is: $start_root_dir"

# print out one extra space
echo "\n"

# list all matching files - just for informational purposes
echo " ~~~ any matching files should be listed  below this line ~~~\n"
/usr/bin/find $start_root_dir -name ".gitignore" -type f
/usr/bin/find $start_root_dir -name ".DS_Store" -type f

# delete all matching files
/usr/bin/find $start_root_dir -name ".gitignore" -type f -delete
/usr/bin/find $start_root_dir -name ".DS_Store" -type f -delete

echo "******************* cleanup_build_dir script exiting *******************\n\n"
# EOF ##################################################################################################################
