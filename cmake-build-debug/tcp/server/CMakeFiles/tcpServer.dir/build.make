# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/930/bin/cmake

# The command to remove a file.
RM = /snap/cmake/930/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shea/CLionProjects/cpp_record

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shea/CLionProjects/cpp_record/cmake-build-debug

# Include any dependencies generated for this target.
include tcp/server/CMakeFiles/tcpServer.dir/depend.make
# Include the progress variables for this target.
include tcp/server/CMakeFiles/tcpServer.dir/progress.make

# Include the compile flags for this target's objects.
include tcp/server/CMakeFiles/tcpServer.dir/flags.make

tcp/server/CMakeFiles/tcpServer.dir/server.cpp.o: tcp/server/CMakeFiles/tcpServer.dir/flags.make
tcp/server/CMakeFiles/tcpServer.dir/server.cpp.o: ../tcp/server/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shea/CLionProjects/cpp_record/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tcp/server/CMakeFiles/tcpServer.dir/server.cpp.o"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/tcp/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcpServer.dir/server.cpp.o -c /home/shea/CLionProjects/cpp_record/tcp/server/server.cpp

tcp/server/CMakeFiles/tcpServer.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpServer.dir/server.cpp.i"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/tcp/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shea/CLionProjects/cpp_record/tcp/server/server.cpp > CMakeFiles/tcpServer.dir/server.cpp.i

tcp/server/CMakeFiles/tcpServer.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpServer.dir/server.cpp.s"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/tcp/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shea/CLionProjects/cpp_record/tcp/server/server.cpp -o CMakeFiles/tcpServer.dir/server.cpp.s

# Object files for target tcpServer
tcpServer_OBJECTS = \
"CMakeFiles/tcpServer.dir/server.cpp.o"

# External object files for target tcpServer
tcpServer_EXTERNAL_OBJECTS =

tcp/server/tcpServer: tcp/server/CMakeFiles/tcpServer.dir/server.cpp.o
tcp/server/tcpServer: tcp/server/CMakeFiles/tcpServer.dir/build.make
tcp/server/tcpServer: tcp/server/CMakeFiles/tcpServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shea/CLionProjects/cpp_record/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tcpServer"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/tcp/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcpServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tcp/server/CMakeFiles/tcpServer.dir/build: tcp/server/tcpServer
.PHONY : tcp/server/CMakeFiles/tcpServer.dir/build

tcp/server/CMakeFiles/tcpServer.dir/clean:
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/tcp/server && $(CMAKE_COMMAND) -P CMakeFiles/tcpServer.dir/cmake_clean.cmake
.PHONY : tcp/server/CMakeFiles/tcpServer.dir/clean

tcp/server/CMakeFiles/tcpServer.dir/depend:
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shea/CLionProjects/cpp_record /home/shea/CLionProjects/cpp_record/tcp/server /home/shea/CLionProjects/cpp_record/cmake-build-debug /home/shea/CLionProjects/cpp_record/cmake-build-debug/tcp/server /home/shea/CLionProjects/cpp_record/cmake-build-debug/tcp/server/CMakeFiles/tcpServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tcp/server/CMakeFiles/tcpServer.dir/depend

