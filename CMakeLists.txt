cmake_minimum_required(VERSION 3.20)
project(Shoko)

set(CMAKE_CXX_STANDARD 17)

# Packages
find_package(SDL2 REQUIRED CONFIG)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)

# Source
add_executable(Shoko
	Source/Shoko/Core/Aliases.h
	Source/Shoko/Core/Macros.h
	Source/Shoko/Core/Meta.h
	Source/Shoko/Core/New.h
	
	Source/Shoko/Renderer/Renderer.h
	
	Source/Shoko/Renderer/Backends/OpenGL/ShokoOpenGLRenderer.h
	Source/Shoko/Renderer/Backends/OpenGL/ShokoOpenGLRenderer.cpp
	Source/Shoko/Renderer/Backends/OpenGL/Shaders/Rect.frag
	Source/Shoko/Renderer/Backends/OpenGL/Shaders/Rect.vert
	
	Source/Shoko/Renderer/Backends/SDL2/ShokoSDL2Renderer.h
	Source/Shoko/Renderer/Backends/SDL2/ShokoSDL2Renderer.cpp
	
	Source/Shoko/Types/Color.h
	Source/Shoko/Types/Geometry.h
	Source/Shoko/Types/StaticArray.h
	Source/Shoko/Types/Vector2D.h
	
	Source/Shoko/Widgets/Border.h
	Source/Shoko/Widgets/BoxWidget.h
	Source/Shoko/Widgets/Button.h
    Source/Shoko/Widgets/OpenGLContext.h
    Source/Shoko/Widgets/Widget.h
    Source/Shoko/Widgets/WidgetBase.h
    Source/Shoko/Widgets/WidgetContainer.h
    Source/Shoko/Widgets/WidgetWrapper.h
	
	Source/Shoko/Shoko.h
	Source/Shoko/Widgets.h
	
	Source/main.cpp
)
target_link_libraries(Shoko PRIVATE
    SDL2::SDL2
    glfw
    OpenGL::GL
	glad::glad
)

target_compile_definitions(Shoko PRIVATE SDL_MAIN_HANDLED)


if(MSVC)
    add_compile_options(/utf-8)
endif()

# Call:
# mkdir Build
# cd Build
# cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake"
# cmake .. -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
