# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/space/Projects/FeliksEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/space/Projects/FeliksEngine/build

# Include any dependencies generated for this target.
include src/CMakeFiles/feliksengine.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/feliksengine.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/feliksengine.dir/flags.make

src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o: src/CMakeFiles/feliksengine.dir/flags.make
src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o: ../src/feliksengine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/space/Projects/FeliksEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o"
	cd /home/space/Projects/FeliksEngine/build/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/feliksengine.dir/feliksengine.cpp.o -c /home/space/Projects/FeliksEngine/src/feliksengine.cpp

src/CMakeFiles/feliksengine.dir/feliksengine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/feliksengine.dir/feliksengine.cpp.i"
	cd /home/space/Projects/FeliksEngine/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/space/Projects/FeliksEngine/src/feliksengine.cpp > CMakeFiles/feliksengine.dir/feliksengine.cpp.i

src/CMakeFiles/feliksengine.dir/feliksengine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/feliksengine.dir/feliksengine.cpp.s"
	cd /home/space/Projects/FeliksEngine/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/space/Projects/FeliksEngine/src/feliksengine.cpp -o CMakeFiles/feliksengine.dir/feliksengine.cpp.s

src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.requires:

.PHONY : src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.requires

src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.provides: src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/feliksengine.dir/build.make src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.provides.build
.PHONY : src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.provides

src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.provides.build: src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o


# Object files for target feliksengine
feliksengine_OBJECTS = \
"CMakeFiles/feliksengine.dir/feliksengine.cpp.o"

# External object files for target feliksengine
feliksengine_EXTERNAL_OBJECTS =

bin/feliksengine: src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o
bin/feliksengine: src/CMakeFiles/feliksengine.dir/build.make
bin/feliksengine: src/CMakeFiles/feliksengine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/space/Projects/FeliksEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/feliksengine"
	cd /home/space/Projects/FeliksEngine/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/feliksengine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/feliksengine.dir/build: bin/feliksengine

.PHONY : src/CMakeFiles/feliksengine.dir/build

src/CMakeFiles/feliksengine.dir/requires: src/CMakeFiles/feliksengine.dir/feliksengine.cpp.o.requires

.PHONY : src/CMakeFiles/feliksengine.dir/requires

src/CMakeFiles/feliksengine.dir/clean:
	cd /home/space/Projects/FeliksEngine/build/src && $(CMAKE_COMMAND) -P CMakeFiles/feliksengine.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/feliksengine.dir/clean

src/CMakeFiles/feliksengine.dir/depend:
	cd /home/space/Projects/FeliksEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/space/Projects/FeliksEngine /home/space/Projects/FeliksEngine/src /home/space/Projects/FeliksEngine/build /home/space/Projects/FeliksEngine/build/src /home/space/Projects/FeliksEngine/build/src/CMakeFiles/feliksengine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/feliksengine.dir/depend

