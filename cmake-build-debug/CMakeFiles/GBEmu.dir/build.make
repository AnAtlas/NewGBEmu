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
CMAKE_COMMAND = "/home/derdro/Program Files/clion-2017.2.3/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/home/derdro/Program Files/clion-2017.2.3/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/derdro/CLionProjects/GBEmu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/derdro/CLionProjects/GBEmu/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GBEmu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GBEmu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GBEmu.dir/flags.make

CMakeFiles/GBEmu.dir/Source/main.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/main.cpp.o: ../Source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GBEmu.dir/Source/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/main.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/main.cpp

CMakeFiles/GBEmu.dir/Source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/main.cpp > CMakeFiles/GBEmu.dir/Source/main.cpp.i

CMakeFiles/GBEmu.dir/Source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/main.cpp -o CMakeFiles/GBEmu.dir/Source/main.cpp.s

CMakeFiles/GBEmu.dir/Source/main.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/main.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/main.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/main.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/main.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/main.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/main.cpp.o


CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o: ../Source/Cartridges/CartRomOnly.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartRomOnly.cpp

CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartRomOnly.cpp > CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.i

CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartRomOnly.cpp -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.s

CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o


CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o: ../Source/Cartridges/Cartridge.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Cartridges/Cartridge.cpp

CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Cartridges/Cartridge.cpp > CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.i

CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Cartridges/Cartridge.cpp -o CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.s

CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o


CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o: ../Source/Cartridges/CartMBC1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC1.cpp

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC1.cpp > CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.i

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC1.cpp -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.s

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o


CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o: ../Source/Cartridges/CartMBC3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC3.cpp

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC3.cpp > CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.i

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC3.cpp -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.s

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o


# Object files for target GBEmu
GBEmu_OBJECTS = \
"CMakeFiles/GBEmu.dir/Source/main.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o"

# External object files for target GBEmu
GBEmu_EXTERNAL_OBJECTS =

GBEmu: CMakeFiles/GBEmu.dir/Source/main.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/build.make
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-network.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-window.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-system.so
GBEmu: CMakeFiles/GBEmu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable GBEmu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GBEmu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GBEmu.dir/build: GBEmu

.PHONY : CMakeFiles/GBEmu.dir/build

CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/main.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.requires

.PHONY : CMakeFiles/GBEmu.dir/requires

CMakeFiles/GBEmu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GBEmu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GBEmu.dir/clean

CMakeFiles/GBEmu.dir/depend:
	cd /home/derdro/CLionProjects/GBEmu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/derdro/CLionProjects/GBEmu /home/derdro/CLionProjects/GBEmu /home/derdro/CLionProjects/GBEmu/cmake-build-debug /home/derdro/CLionProjects/GBEmu/cmake-build-debug /home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles/GBEmu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GBEmu.dir/depend
