# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/beck/CLionProjects/untitled3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/beck/CLionProjects/untitled3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

CMakeFiles/demo.dir/main.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/beck/CLionProjects/untitled3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/main.cpp.o -c /Users/beck/CLionProjects/untitled3/main.cpp

CMakeFiles/demo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/beck/CLionProjects/untitled3/main.cpp > CMakeFiles/demo.dir/main.cpp.i

CMakeFiles/demo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/beck/CLionProjects/untitled3/main.cpp -o CMakeFiles/demo.dir/main.cpp.s

CMakeFiles/demo.dir/byylf_cf.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/byylf_cf.cpp.o: ../byylf_cf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/beck/CLionProjects/untitled3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/demo.dir/byylf_cf.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/byylf_cf.cpp.o -c /Users/beck/CLionProjects/untitled3/byylf_cf.cpp

CMakeFiles/demo.dir/byylf_cf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/byylf_cf.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/beck/CLionProjects/untitled3/byylf_cf.cpp > CMakeFiles/demo.dir/byylf_cf.cpp.i

CMakeFiles/demo.dir/byylf_cf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/byylf_cf.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/beck/CLionProjects/untitled3/byylf_cf.cpp -o CMakeFiles/demo.dir/byylf_cf.cpp.s

# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/main.cpp.o" \
"CMakeFiles/demo.dir/byylf_cf.cpp.o"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

libdemo.a: CMakeFiles/demo.dir/main.cpp.o
libdemo.a: CMakeFiles/demo.dir/byylf_cf.cpp.o
libdemo.a: CMakeFiles/demo.dir/build.make
libdemo.a: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/beck/CLionProjects/untitled3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libdemo.a"
	$(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: libdemo.a

.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend:
	cd /Users/beck/CLionProjects/untitled3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/beck/CLionProjects/untitled3 /Users/beck/CLionProjects/untitled3 /Users/beck/CLionProjects/untitled3/cmake-build-debug /Users/beck/CLionProjects/untitled3/cmake-build-debug /Users/beck/CLionProjects/untitled3/cmake-build-debug/CMakeFiles/demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo.dir/depend

