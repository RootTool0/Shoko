cmake_minimum_required(VERSION 3.20)
project(Shoko)

set(CMAKE_CXX_STANDARD 17)

# Packages
find_package(SDL2 REQUIRED CONFIG)

# Source
add_executable(Shoko 
	Source/main.cpp
	
	Source/Shoko/Shoko.h
    Source/Shoko/Widget.h
    Source/Shoko/WidgetWrapper.h
    Source/Shoko/WidgetContainer.h
	Source/Shoko/BoxWidget.h
	Source/Shoko/Button.h
    
	Source/Shoko/Core/Aliases.h
	Source/Shoko/Core/Macros.h
	Source/Shoko/Core/Meta.h
	
	Source/Shoko/Types/Color.h
	Source/Shoko/Types/StaticArray.h
	
)

target_link_libraries(Shoko PRIVATE SDL2::SDL2)
target_compile_definitions(Shoko PRIVATE SDL_MAIN_HANDLED)


if(MSVC)
    add_compile_options(/utf-8)
endif()

# Call:
# mkdir Build
# cd Build
# cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake"
# cmake .. -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
