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
include processorInfo/CMakeFiles/processorInfo.dir/depend.make
# Include the progress variables for this target.
include processorInfo/CMakeFiles/processorInfo.dir/progress.make

# Include the compile flags for this target's objects.
include processorInfo/CMakeFiles/processorInfo.dir/flags.make

processorInfo/CMakeFiles/processorInfo.dir/processorInfo.cpp.o: processorInfo/CMakeFiles/processorInfo.dir/flags.make
processorInfo/CMakeFiles/processorInfo.dir/processorInfo.cpp.o: ../processorInfo/processorInfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shea/CLionProjects/cpp_record/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object processorInfo/CMakeFiles/processorInfo.dir/processorInfo.cpp.o"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/processorInfo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/processorInfo.dir/processorInfo.cpp.o -c /home/shea/CLionProjects/cpp_record/processorInfo/processorInfo.cpp

processorInfo/CMakeFiles/processorInfo.dir/processorInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/processorInfo.dir/processorInfo.cpp.i"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/processorInfo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shea/CLionProjects/cpp_record/processorInfo/processorInfo.cpp > CMakeFiles/processorInfo.dir/processorInfo.cpp.i

processorInfo/CMakeFiles/processorInfo.dir/processorInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/processorInfo.dir/processorInfo.cpp.s"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/processorInfo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shea/CLionProjects/cpp_record/processorInfo/processorInfo.cpp -o CMakeFiles/processorInfo.dir/processorInfo.cpp.s

# Object files for target processorInfo
processorInfo_OBJECTS = \
"CMakeFiles/processorInfo.dir/processorInfo.cpp.o"

# External object files for target processorInfo
processorInfo_EXTERNAL_OBJECTS =

processorInfo/processorInfo: processorInfo/CMakeFiles/processorInfo.dir/processorInfo.cpp.o
processorInfo/processorInfo: processorInfo/CMakeFiles/processorInfo.dir/build.make
processorInfo/processorInfo: processorInfo/CMakeFiles/processorInfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shea/CLionProjects/cpp_record/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable processorInfo"
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/processorInfo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/processorInfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
processorInfo/CMakeFiles/processorInfo.dir/build: processorInfo/processorInfo
.PHONY : processorInfo/CMakeFiles/processorInfo.dir/build

processorInfo/CMakeFiles/processorInfo.dir/clean:
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug/processorInfo && $(CMAKE_COMMAND) -P CMakeFiles/processorInfo.dir/cmake_clean.cmake
.PHONY : processorInfo/CMakeFiles/processorInfo.dir/clean

processorInfo/CMakeFiles/processorInfo.dir/depend:
	cd /home/shea/CLionProjects/cpp_record/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shea/CLionProjects/cpp_record /home/shea/CLionProjects/cpp_record/processorInfo /home/shea/CLionProjects/cpp_record/cmake-build-debug /home/shea/CLionProjects/cpp_record/cmake-build-debug/processorInfo /home/shea/CLionProjects/cpp_record/cmake-build-debug/processorInfo/CMakeFiles/processorInfo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : processorInfo/CMakeFiles/processorInfo.dir/depend
