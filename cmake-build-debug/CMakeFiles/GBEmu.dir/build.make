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

CMakeFiles/GBEmu.dir/Source/Main.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Main.cpp.o: ../Source/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GBEmu.dir/Source/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Main.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Main.cpp

CMakeFiles/GBEmu.dir/Source/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Main.cpp > CMakeFiles/GBEmu.dir/Source/Main.cpp.i

CMakeFiles/GBEmu.dir/Source/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Main.cpp -o CMakeFiles/GBEmu.dir/Source/Main.cpp.s

CMakeFiles/GBEmu.dir/Source/Main.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Main.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Main.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Main.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Main.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Main.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Main.cpp.o


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


CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o: ../Source/Cartridges/CartMBC5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC5.cpp

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC5.cpp > CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.i

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Cartridges/CartMBC5.cpp -o CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.s

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o


CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o: ../Source/Gameboy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Gameboy.cpp

CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Gameboy.cpp > CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.i

CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Gameboy.cpp -o CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.s

CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o


CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o: ../Source/Components/Memory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Components/Memory.cpp

CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Components/Memory.cpp > CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.i

CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Components/Memory.cpp -o CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.s

CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o


CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o: ../Source/Components/Cpu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Components/Cpu.cpp

CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Components/Cpu.cpp > CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.i

CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Components/Cpu.cpp -o CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.s

CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o


CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o: ../Source/Components/CpuOpcodeTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Components/CpuOpcodeTable.cpp

CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Components/CpuOpcodeTable.cpp > CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.i

CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Components/CpuOpcodeTable.cpp -o CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.s

CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o


CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o: ../Source/Components/Gpu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Components/Gpu.cpp

CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Components/Gpu.cpp > CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.i

CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Components/Gpu.cpp -o CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.s

CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o


CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o: ../Source/Components/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Components/Timer.cpp

CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Components/Timer.cpp > CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.i

CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Components/Timer.cpp -o CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.s

CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o


CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o: CMakeFiles/GBEmu.dir/flags.make
CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o: ../Source/Components/Input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o -c /home/derdro/CLionProjects/GBEmu/Source/Components/Input.cpp

CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/derdro/CLionProjects/GBEmu/Source/Components/Input.cpp > CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.i

CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/derdro/CLionProjects/GBEmu/Source/Components/Input.cpp -o CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.s

CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.requires:

.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.requires

CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.provides: CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.requires
	$(MAKE) -f CMakeFiles/GBEmu.dir/build.make CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.provides.build
.PHONY : CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.provides

CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.provides.build: CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o


# Object files for target GBEmu
GBEmu_OBJECTS = \
"CMakeFiles/GBEmu.dir/Source/Main.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o" \
"CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o"

# External object files for target GBEmu
GBEmu_EXTERNAL_OBJECTS =

GBEmu: CMakeFiles/GBEmu.dir/Source/Main.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o
GBEmu: CMakeFiles/GBEmu.dir/build.make
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-network.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-window.so
GBEmu: /usr/lib/x86_64-linux-gnu/libsfml-system.so
GBEmu: CMakeFiles/GBEmu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable GBEmu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GBEmu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GBEmu.dir/build: GBEmu

.PHONY : CMakeFiles/GBEmu.dir/build

CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Main.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/CartRomOnly.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/Cartridge.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC1.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC3.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Cartridges/CartMBC5.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Gameboy.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Components/Memory.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Components/Cpu.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Components/CpuOpcodeTable.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Components/Gpu.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Components/Timer.cpp.o.requires
CMakeFiles/GBEmu.dir/requires: CMakeFiles/GBEmu.dir/Source/Components/Input.cpp.o.requires

.PHONY : CMakeFiles/GBEmu.dir/requires

CMakeFiles/GBEmu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GBEmu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GBEmu.dir/clean

CMakeFiles/GBEmu.dir/depend:
	cd /home/derdro/CLionProjects/GBEmu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/derdro/CLionProjects/GBEmu /home/derdro/CLionProjects/GBEmu /home/derdro/CLionProjects/GBEmu/cmake-build-debug /home/derdro/CLionProjects/GBEmu/cmake-build-debug /home/derdro/CLionProjects/GBEmu/cmake-build-debug/CMakeFiles/GBEmu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GBEmu.dir/depend

