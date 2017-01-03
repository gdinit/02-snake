#!/usr/local/bin/dash

########################################################################################################################
# m0_uncrustify_source_files.sh
#
# This script does the following: 
# 1) compile a list of all source code files that exist in the current dir & any include dirs listed in configuration
# 2) then execute an `uncrustify` operation on them based on the rules defined in the configuration file
########################################################################################################################



########## CONFIGURATION - begin
uncrustify_config_file="/Users/mgm/g/dev/config/uncrustify/uncrustify_config.mine.v.0.62.cfg"
uncrustify_binary=/usr/local/bin/uncrustify
# note: source code main directory will be set to ../source in the main section. manually override it there if you need to.

# file extensions that we should be parsing
ext01="*.h"
ext02="*.hpp"
ext03="*.inl"
ext04="*.cc"
ext05="*.cpp"

# name of the directory that holds headers and inline files
includedir="include"
########## CONFIGURATION - end










########## DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
########## DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING
########## DO NOT TOUCH BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING

#################### MAIN - begin
## update user
echo "\n********** uncrustify script running - phase main dir BEGIN **********"
project_language=CPP
#echo "The value of project_language is: $project_language"

### CONFIGURATION.SYSTEM
start_root_dir=${PWD%/*}/source
#echo "The value of start_root_dir is: $start_root_dir"

to_be_uncrustified_list=$start_root_dir/___uncrustify_file_list.txt
#echo "The value of to_be_uncrustified_list is: $to_be_uncrustified_list"

## Compile a list of all files that will need to be uncrustified
# add all header files (.h) to the list to process
ls -d $start_root_dir/*.h		> 	$start_root_dir/___uncrustify_file_list.txt			2>/dev/null

# add all source files (.cc) to the list to process
ls -d $start_root_dir/*.cc		>>	$start_root_dir/___uncrustify_file_list.txt			2>/dev/null

# add all inline include files (.inl) to the list to process
ls -d $start_root_dir/*.inl		>>	$start_root_dir/___uncrustify_file_list.txt			2>/dev/null

# execute the operation
$uncrustify_binary --no-backup -l $project_language -c $uncrustify_config_file -F $to_be_uncrustified_list

# cleanup
/bin/rm $to_be_uncrustified_list
echo "********** uncrustify script running - phase main dir END **********\n"





## update user
echo "\n********** uncrustify script running - phase include dir BEGIN **********"
cd $start_root_dir/$includedir
start_root_dir=${PWD}
echo "The value of start_root_dir is: $start_root_dir"

to_be_uncrustified_list=$start_root_dir/___uncrustify_file_list.txt
#echo "The value of to_be_uncrustified_list is: $to_be_uncrustified_list"

ls -d $start_root_dir/*.h		> 	$start_root_dir/___uncrustify_file_list.txt			2>/dev/null
ls -d $start_root_dir/*.cc		>>	$start_root_dir/___uncrustify_file_list.txt			2>/dev/null
ls -d $start_root_dir/*.inl		>>	$start_root_dir/___uncrustify_file_list.txt			2>/dev/null
$uncrustify_binary --no-backup -l $project_language -c $uncrustify_config_file -F $to_be_uncrustified_list
/bin/rm $to_be_uncrustified_list
echo "********** uncrustify script running - phase include dir END **********\n"
#################### MAIN - end




# EOF

