# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/hezhenbang/Documents/OpenGL Projects/Light"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/hezhenbang/Documents/OpenGL Projects/Light/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Light.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Light.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Light.dir/flags.make

CMakeFiles/Light.dir/main.cpp.o: CMakeFiles/Light.dir/flags.make
CMakeFiles/Light.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/hezhenbang/Documents/OpenGL Projects/Light/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Light.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Light.dir/main.cpp.o -c "/Users/hezhenbang/Documents/OpenGL Projects/Light/main.cpp"

CMakeFiles/Light.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Light.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/hezhenbang/Documents/OpenGL Projects/Light/main.cpp" > CMakeFiles/Light.dir/main.cpp.i

CMakeFiles/Light.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Light.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/hezhenbang/Documents/OpenGL Projects/Light/main.cpp" -o CMakeFiles/Light.dir/main.cpp.s

CMakeFiles/Light.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Light.dir/main.cpp.o.requires

CMakeFiles/Light.dir/main.cpp.o.provides: CMakeFiles/Light.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Light.dir/build.make CMakeFiles/Light.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Light.dir/main.cpp.o.provides

CMakeFiles/Light.dir/main.cpp.o.provides.build: CMakeFiles/Light.dir/main.cpp.o


# Object files for target Light
Light_OBJECTS = \
"CMakeFiles/Light.dir/main.cpp.o"

# External object files for target Light
Light_EXTERNAL_OBJECTS =

Light: CMakeFiles/Light.dir/main.cpp.o
Light: CMakeFiles/Light.dir/build.make
Light: /usr/local/lib/libglfw.3.2.dylib
Light: CMakeFiles/Light.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/hezhenbang/Documents/OpenGL Projects/Light/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Light"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Light.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Light.dir/build: Light

.PHONY : CMakeFiles/Light.dir/build

CMakeFiles/Light.dir/requires: CMakeFiles/Light.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Light.dir/requires

CMakeFiles/Light.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Light.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Light.dir/clean

CMakeFiles/Light.dir/depend:
	cd "/Users/hezhenbang/Documents/OpenGL Projects/Light/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/hezhenbang/Documents/OpenGL Projects/Light" "/Users/hezhenbang/Documents/OpenGL Projects/Light" "/Users/hezhenbang/Documents/OpenGL Projects/Light/cmake-build-debug" "/Users/hezhenbang/Documents/OpenGL Projects/Light/cmake-build-debug" "/Users/hezhenbang/Documents/OpenGL Projects/Light/cmake-build-debug/CMakeFiles/Light.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Light.dir/depend

