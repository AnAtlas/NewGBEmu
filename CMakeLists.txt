cmake_minimum_required(VERSION 3.9)
project(GBEmu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(GCC_COVERAGE_LINK_FLAGS "-lX11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(SOURCE_FILES Source/main.cpp Source/Cartridges/CartRomOnly.cpp Source/Cartridges/Cartridge.cpp Source/Cartridges/CartMBC1.cpp)
set(HEADER_FILES Source/Memory.hpp Source/Utilities/Types.hpp Source/Utilities/Bios.hpp Source/MemoryManager.hpp Source/Cartridges/Cartridge.hpp Source/Cartridges/CartridgeFactory.hpp Source/Utilities/AddressRange.hpp Source/Cartridges/CartRomOnly.hpp Source/Cartridges/CartMBC1.hpp Source/Utilities/AddressRange.hpp Source/Cartridges/CartMBC3.hpp Source/Cartridges/CartMBC3.cpp Source/Cartridges/RamModule.hpp Source/Cartridges/RTCModule.hpp)


add_executable(GBEmu ${SOURCE_FILES} ${HEADER_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
find_package(X11 REQUIRED)

#Add thread libraries
find_package(Threads)
target_link_libraries(GBEmu ${CMAKE_THREAD_LIBS_INIT})

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(GBEmu ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} X11)
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)