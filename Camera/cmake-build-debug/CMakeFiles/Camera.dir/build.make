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
CMAKE_SOURCE_DIR = "/Users/hezhenbang/Documents/OpenGL Projects/Camera"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/hezhenbang/Documents/OpenGL Projects/Camera/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Camera.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Camera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Camera.dir/flags.make

CMakeFiles/Camera.dir/main.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/hezhenbang/Documents/OpenGL Projects/Camera/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Camera.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/main.cpp.o -c "/Users/hezhenbang/Documents/OpenGL Projects/Camera/main.cpp"

CMakeFiles/Camera.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/hezhenbang/Documents/OpenGL Projects/Camera/main.cpp" > CMakeFiles/Camera.dir/main.cpp.i

CMakeFiles/Camera.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/hezhenbang/Documents/OpenGL Projects/Camera/main.cpp" -o CMakeFiles/Camera.dir/main.cpp.s

CMakeFiles/Camera.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Camera.dir/main.cpp.o.requires

CMakeFiles/Camera.dir/main.cpp.o.provides: CMakeFiles/Camera.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Camera.dir/build.make CMakeFiles/Camera.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Camera.dir/main.cpp.o.provides

CMakeFiles/Camera.dir/main.cpp.o.provides.build: CMakeFiles/Camera.dir/main.cpp.o


# Object files for target Camera
Camera_OBJECTS = \
"CMakeFiles/Camera.dir/main.cpp.o"

# External object files for target Camera
Camera_EXTERNAL_OBJECTS =

Camera: CMakeFiles/Camera.dir/main.cpp.o
Camera: CMakeFiles/Camera.dir/build.make
Camera: /usr/local/lib/libglfw.3.2.dylib
Camera: CMakeFiles/Camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/hezhenbang/Documents/OpenGL Projects/Camera/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Camera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Camera.dir/build: Camera

.PHONY : CMakeFiles/Camera.dir/build

CMakeFiles/Camera.dir/requires: CMakeFiles/Camera.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Camera.dir/requires

CMakeFiles/Camera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Camera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Camera.dir/clean

CMakeFiles/Camera.dir/depend:
	cd "/Users/hezhenbang/Documents/OpenGL Projects/Camera/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/hezhenbang/Documents/OpenGL Projects/Camera" "/Users/hezhenbang/Documents/OpenGL Projects/Camera" "/Users/hezhenbang/Documents/OpenGL Projects/Camera/cmake-build-debug" "/Users/hezhenbang/Documents/OpenGL Projects/Camera/cmake-build-debug" "/Users/hezhenbang/Documents/OpenGL Projects/Camera/cmake-build-debug/CMakeFiles/Camera.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Camera.dir/depend

