set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

project(snake)
set(PROJECT_SOURCE_DIR	"${CMAKE_SOURCE_DIR}/source" CACHE PATH "source files")
get_filename_component(MYPROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
list(APPEND CMAKE_MODULE_PATH	"${PROJECT_SOURCE_DIR}/cmake/modules")
add_subdirectory(source)

#EOF
