cmake_minimum_required(VERSION 3.20)
project(Shoko)

set(CMAKE_CXX_STANDARD 17)

# Packages
find_package(SDL2 REQUIRED CONFIG)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(raylib REQUIRED)

# Source
file(GLOB_RECURSE ALL_FILES "Source/*")
add_executable(Shoko ${ALL_FILES})

target_link_libraries(Shoko PRIVATE
    SDL2::SDL2
    glfw
    OpenGL::GL
	glad::glad
	raylib
)

target_compile_definitions(Shoko PRIVATE SDL_MAIN_HANDLED)

target_include_directories(Shoko PRIVATE Source/Shoko)

if(MSVC)
    add_compile_options(/utf-8)
endif()

# Call:
# mkdir Build
# cd Build
# cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake"
# cmake .. -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
