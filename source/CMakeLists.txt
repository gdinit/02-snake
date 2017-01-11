cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set (CMAKE_CXX_STANDARD 11)

project(snake)

# SETTING PATHS		########################################################
#
# Definitions		################
# source: https://cmake.org/Wiki/CMake_Useful_Variables
# CMAKE_SOURCE_DIR	this is the directory, from which cmake was started, i.e. the top level source directory 
# CMAKE_BINARY_DIR	if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise this is the top level directory of your build tree 
# PROJECT_SOURCE_DIR	contains the full path to the root of your project source directory, i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command
#
# Our Configuration	################
#set(PROJECT_SOURCE_DIR	${CMAKE_SOURCE_DIR}/source		CACHE PATH "source files")
set(PROJECT_SOURCE_DIR	${CMAKE_SOURCE_DIR}			CACHE PATH "source files")
#set(PROJECT_BINARY_DIR	${CMAKE_SOURCE_DIR}/build		CACHE PATH "out of source, temporary build dir")
#
list(APPEND CMAKE_MODULE_PATH	"${CMAKE_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_INCLUDE_PATH	"${CMAKE_SOURCE_DIR}/include")
# add includes to this using list/appent ->	CMAKE_INCLUDE_PATH 
#
# get the MYPROJECT_ROOT_DIR
get_filename_component(MYPROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
########################################

find_package(SFML 2.4 COMPONENTS graphics audio window system network)

file	(GLOB SOURCES 
	"${PROJECT_SOURCE_DIR}/include/*.h" 
	"${PROJECT_SOURCE_DIR}/include/*.inl" 
	"${PROJECT_SOURCE_DIR}/*.cc"
	)

# Compiler options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()
if (NOT CONFIGURED_ONCE)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -fpermissive -std=c++11"
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wpedantic -std=c++11"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SFML_INCLUDE_DIR})
IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    INCLUDE_DIRECTORIES("/Library/Frameworks/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBRARIES OFF)

#add_executable(${PROJECT_NAME} ${SOURCES})
SET(CMAKE_RC_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
add_executable(
  ${PROJECT_NAME}
  ${GUI_TYPE}
  ${SOURCES}
  ${MYPROJECT_ROOT_DIR}/extras/exe_icon_for_windows/resource.rc
)

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})



if	(${CMAKE_SYSTEM_NAME}		MATCHES "Darwin")
	#set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
	set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")
        set	(EXECUTABLE_OUTPUT_PATH
		${PROJECT_BINARY_DIR}/release.mac
		CACHE PATH
		"Description to be updated..."
		)
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
	set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
	set	(EXECUTABLE_OUTPUT_PATH
		${PROJECT_BINARY_DIR}/release.win
		CACHE PATH
		"Description to be updated...")
	#----------------------------------------
	# for Windows builds, copy dependency binaries to build dir (only OpenAL so far as we embed SFML into the EXE).
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${MYPROJECT_ROOT_DIR}/dependencies	$<TARGET_FILE_DIR:${PROJECT_NAME}>/)
	#----------------------------------------
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Linux")
	set	(EXECUTABLE_OUTPUT_PATH
		${PROJECT_BINARY_DIR}/release.lin
		CACHE PATH
		"Description to be updated..."
		)
else()
        set	(EXECUTABLE_OUTPUT_PATH
		${PROJECT_BINARY_DIR}/release.unknown_platform
		CACHE PATH
		"Description to be updated..."
		)
endif()
mark_as_advanced	(EXECUTABLE_OUTPUT_PATH)



set	(LIBRARY_OUTPUT_PATH
	${PROJECT_BINARY_DIR}/bin
	CACHE PATH
	"Single directory for all libraries."
	)
mark_as_advanced	(LIBRARY_OUTPUT_PATH)



################################################################################
# PRE-BUILD SCRIPTS
################################################################################
#----------------------------------------
#add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#so far, nothing to do in pre-build stage...
#----------------------------------------
################################################################################



################################################################################
# POST-BUILD SCRIPTS
################################################################################
#----------------------------------------
# copy product ASSETS to build dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${MYPROJECT_ROOT_DIR}/assets				$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
#----------------------------------------


#----------------------------------------
# SELF-REMINDER:
#
# DLL DEPENDENCIES are handled above, in this section -->  IF ${CMAKE_SYSTEM_NAME} MATCHES WIN
#----------------------------------------



#----------------------------------------
# copy product DOCUMENTATION to build dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${MYPROJECT_ROOT_DIR}/documentation			$<TARGET_FILE_DIR:${PROJECT_NAME}>/documentation)
#----------------------------------------
################################################################################

#EOF
