cmake_minimum_required(VERSION 3.9)
project(GBEmu)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_LINK_FLAGS "-lX11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(SOURCE_FILES Source/Main.cpp Source/Cartridges/CartRomOnly.cpp Source/Cartridges/Cartridge.cpp Source/Cartridges/CartMBC1.cpp  Source/Cartridges/CartMBC3.cpp Source/Cartridges/CartMBC5.cpp Source/Gameboy.cpp Source/Components/Memory.cpp Source/Components/Cpu.cpp Source/Components/CpuOpcodeTable.cpp Source/Components/Gpu.cpp Source/Components/Timer.cpp Source/Components/Input.cpp Source/Components/Apu.cpp Source/Utilities/Audio/SoundChannel.cpp Source/Utilities/Audio/SquareChannel.cpp Source/Utilities/Audio/SquareSweepChannel.cpp Source/Utilities/Audio/WaveChannel.cpp Source/Utilities/Audio/NoiseChannel.cpp)
set(HEADER_FILES Source/Components/Memory.hpp Source/Utilities/Types.hpp Source/Utilities/Bios.hpp Source/Cartridges/Cartridge.hpp Source/Cartridges/CartridgeFactory.hpp Source/Utilities/AddressRange.hpp Source/Cartridges/CartRomOnly.hpp Source/Cartridges/CartMBC1.hpp Source/Cartridges/CartMBC5.hpp Source/Utilities/AddressRange.hpp Source/Cartridges/CartMBC3.hpp Source/Cartridges/RamModule.hpp Source/Cartridges/RTCModule.hpp Source/Components/Cpu.hpp Source/Components/Gpu.hpp Source/Components/Timer.hpp Source/Gameboy.hpp Source/Components/GpuMemoryInterface.hpp Source/Components/CpuMemoryInterface.hpp Source/Components/TimerMemoryInterface.hpp Source/DebuggingTools/Debugger.hpp Source/DebuggingTools/Instructions.hpp Source/Components/Input.hpp Source/Components/InputMemoryInterface.hpp Source/Utilities/Settings.hpp Source/Utilities/InputInterface.hpp Source/DebuggingTools/TilesetViewer.hpp Source/Components/Apu.hpp Source/Utilities/Audio/SoundChannel.hpp Source/Components/AudioMemoryInterface.hpp Source/Utilities/Bits.hpp Source/Utilities/Audio/SquareSweepChannel.hpp Source/Components/MemoryAudioInterface.hpp Source/Utilities/Audio/SquareChannel.hpp Source/Utilities/Audio/WaveChannel.hpp Source/Utilities/Audio/NoiseChannel.hpp)


add_executable(GBEmu ${SOURCE_FILES} ${HEADER_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED network audio graphics window system)
find_package(X11 REQUIRED)

#Add thread libraries
find_package(Threads)
target_link_libraries(GBEmu ${CMAKE_THREAD_LIBS_INIT})

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(GBEmu ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(GBEmu X11)
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)