# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/leo/DIT168/ProductionCode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leo/DIT168

# Include any dependencies generated for this target.
include CMakeFiles/Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project.dir/flags.make

CMakeFiles/Project.dir/Main.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Main.cpp.o: ProductionCode/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leo/DIT168/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project.dir/Main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Main.cpp.o -c /home/leo/DIT168/ProductionCode/Main.cpp

CMakeFiles/Project.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leo/DIT168/ProductionCode/Main.cpp > CMakeFiles/Project.dir/Main.cpp.i

CMakeFiles/Project.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leo/DIT168/ProductionCode/Main.cpp -o CMakeFiles/Project.dir/Main.cpp.s

CMakeFiles/Project.dir/Main.cpp.o.requires:

.PHONY : CMakeFiles/Project.dir/Main.cpp.o.requires

CMakeFiles/Project.dir/Main.cpp.o.provides: CMakeFiles/Project.dir/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/Main.cpp.o.provides.build
.PHONY : CMakeFiles/Project.dir/Main.cpp.o.provides

CMakeFiles/Project.dir/Main.cpp.o.provides.build: CMakeFiles/Project.dir/Main.cpp.o


# Object files for target Project
Project_OBJECTS = \
"CMakeFiles/Project.dir/Main.cpp.o"

# External object files for target Project
Project_EXTERNAL_OBJECTS =

Project: CMakeFiles/Project.dir/Main.cpp.o
Project: CMakeFiles/Project.dir/build.make
Project: CMakeFiles/Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leo/DIT168/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project.dir/build: Project

.PHONY : CMakeFiles/Project.dir/build

CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/Main.cpp.o.requires

.PHONY : CMakeFiles/Project.dir/requires

CMakeFiles/Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project.dir/clean

CMakeFiles/Project.dir/depend:
	cd /home/leo/DIT168 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leo/DIT168/ProductionCode /home/leo/DIT168/ProductionCode /home/leo/DIT168 /home/leo/DIT168 /home/leo/DIT168/CMakeFiles/Project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project.dir/depend

