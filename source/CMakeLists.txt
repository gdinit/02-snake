set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

project(snake)
#set_target_properties(breakout PROPERTIES LINKER_LANGUAGE CXX)
SET(PROJECT_STATIC_RUNTIME TRUE CACHE BOOL "Use statically linked standard/runtime libraries?")

list(APPEND CMAKE_MODULE_PATH	"${PROJECT_SOURCE_DIR}/cmake/modules")
find_package(SFML 2.4 COMPONENTS graphics audio window system network)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h"  "${PROJECT_SOURCE_DIR}/*.cc")

if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

####################
# Compiler options
####################
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wno-unknown-pragmas -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc /Wno-unknown-pragmas")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	if(PROJECT_STATIC_RUNTIME)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static -Wall -Wno-unknown-pragmas")
	else()
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
	endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SFML_INCLUDE_DIR})

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	INCLUDE_DIRECTORIES("/Library/Frameworks/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

####################
# LIB SUFFIXES
####################
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
	SET(CMAKE_FIND_LIBRARY_PREFIXES "")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Linux")
	SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
endif()
mark_as_advanced	(CMAKE_FIND_LIBRARY_PREFIXES)

SET(CMAKE_RC_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
add_executable(
	${PROJECT_NAME}
	${GUI_TYPE}
	${SOURCES}
	${CMAKE_SOURCE_DIR}/extras/exe_icon_for_windows/resource.rc)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# this is in trunk as of 2016Dec - let's just keep it here till it makes to the release
# set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/release.win/Debug")

set(CMAKE_SUPPRESS_REGENERATION true)

####################
# LINKER FLAGS
####################
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Darwin")
        set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
        set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")
	if(CMAKE_COMPILER_IS_GNUCXX)
		set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
	endif()
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Linux")
        set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")
endif()
mark_as_advanced	(CMAKE_EXE_LINKER_FLAGS)


####################
# EXECUTABLE_OUTPUT_PATH
####################
set(PROJECT_BINARY_DIR "${CMAKE_SOURCE_DIR}/build" CACHE PATH "out of source, temporary build dir")
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Darwin")
        set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.mac CACHE PATH "Mac output directory")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
	set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.win CACHE PATH "Windows output directory")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Linux")
	set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.lin CACHE PATH "Linux output directory")
else()
        set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.unknown_platform CACHE PATH "UnknownPlatform output directory")
endif()
mark_as_advanced	(EXECUTABLE_OUTPUT_PATH)

####################
# LIBRARIES
####################
set	(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "NOT IN USE" )
mark_as_advanced	(LIBRARY_OUTPUT_PATH)


####################
# CUSTOM COMMANDS
####################
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/extras/dependencies $<TARGET_FILE_DIR:${PROJECT_NAME}>/)
	# copy ASSETS for Visual Studio so that debug run can find assets
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/build/source/assets)
endif()

################################################################################
# PRE/POST BUILD SCRIPTS
################################################################################
#----------------------------------------
#add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#so far, nothing to do in pre-build stage...
#----------------------------------------

#----------------------------------------
# copy ASSETS
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
# copy DOCUMENTATION
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/extras/documentation $<TARGET_FILE_DIR:${PROJECT_NAME}>/documentation)
#----------------------------------------

# NOTES - Microsoft Visual Studio compiler flags
# /W4 -> For a new project, it may be best to use /W4 in all compilations; this will ensure the fewest possible hard-to-find code defects.
# /WX -> Treats all compiler warnings as errors. For a new project, it may be best to use /WX in all compilations; resolving all warnings ensures the fewest possible hard-to-find code defects.
# /EHsc -> Exception handling model'optimization, space and time for x86 code, space for x64 code'	

# for Windows builds, copy dependency binaries to build dir (only OpenAL so far as we embed SFML into the EXE)

#EOF








#set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")#good for GCC
#set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")#good for MSVC

#if(UNIX)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wno-unused-variable -Wno-unused-but-set-variable -Wno-switch -Werror")
#endif()

#		if (NOT CONFIGURED_ONCE)
#			if	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
#				# nothing
#			else	()
#				set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -std=c++11" CACHE STRING "Flags used by the compiler during DEBUG builds." FORCE)
#				set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -std=c++11" CACHE STRING "Flags used by the compiler during RELEASE builds." FORCE)
#			endif()	
#			#	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wpedantic -std=c++11" CACHE STRING "Flags used by the compiler during all build types." FORCE)
#			#	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -std=c++11" CACHE STRING "Flags used by the compiler during DEBUG builds." FORCE)
#			#	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -std=c++11" CACHE STRING "Flags used by the compiler during RELEASE builds." FORCE)
#		endif()
