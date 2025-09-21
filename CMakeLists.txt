# Set the minimum version of CMake required to build this project.
cmake_minimum_required(VERSION 3.10)

# Define the project name.
project(primitive-3d)

# Set the C++ standard to C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SDL2 library.
# This command searches for the necessary SDL2 libraries and headers.
# It sets the SDL2_LIBRARIES variable and makes the SDL2::SDL2 target available.
find_package(SDL2 REQUIRED)


file(GLOB_RECURSE SOURCES "src/main.cpp" "src/Stage/Stage.cpp" "src/Primitive/Primitive.cpp")
file(GLOB_RECURSE HEADERS "src/*.h", "src/Stage/Stage.hpp" "src/Primitive/Primitive.hpp")

# Add an executable target named 'primitive-3d'.
# The source file for the executable is ./src/main.cpp.
add_executable(primitive-3d ${SOURCES})

# Link the SDL2 library to the executable.
# This ensures that the SDL2 functions can be used by the program.
target_link_libraries(primitive-3d PRIVATE SDL2::SDL2)

# Set the output directory for the executable.
# This places the executable in the main project directory.
set_target_properties(primitive-3d PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

