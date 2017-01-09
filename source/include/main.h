/* main.h */

#ifndef MAIN_H
#define MAIN_H

#include <include/application.h>
#include <include/globals.h>
// needed for exception handling in main
#include <stdexcept>
// needed for exception handling in main
#include <iostream>

#if defined __APPLE__
// Fix for `cwd issue`. Temporary, till we get the bundle build system in CMake: BEGIN
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <unistd.h>
#include <sys/param.h>
#include <mach-o/dyld.h>
// Fix for `cwd issue`. Temporary, till we get the bundle build system in CMake: END
#endif	// __APPLE__

#if defined __APPLE__
// Fix for `cwd issue`. Temporary, till we get the bundle build system in CMake: BEGIN
char real_path [ MAXPATHLEN ];

const char * getExePath()
{
	char		exe_path [ MAXPATHLEN ];

	uint32_t	size = sizeof( exe_path );

	if ( _NSGetExecutablePath( exe_path, &size ) != 0 ) {
		std::cout << "Error Occured with _NSGetExecutablePath " << std::endl;
	} else {
		// now attempt to get a real path (no symlinks)
		realpath( real_path, exe_path );

		return real_path;
	}

	return nullptr;
}

// Fix for `cwd issue`. Temporary, till we get the bundle build system in CMake: END
#endif	// __APPLE__

#endif	// MAIN_H

/* EOF */

