cmake_minimum_required(VERSION 3.18)
project(Shoko)

set(CMAKE_CXX_STANDARD 17)

macro(shoko_include_platform_context PLATFORM CONTEXT)
    file(GLOB_RECURSE TEMP CONFIGURE_DEPENDS "Source/Shoko/Platform/${CONTEXT}/${CONTEXT}Declaration.h")
    list(APPEND FOUND_PLATFORM_FILES ${TEMP})
    
    file(GLOB_RECURSE TEMP CONFIGURE_DEPENDS "Source/Shoko/Platform/${CONTEXT}/${PLATFORM}/*")
    list(APPEND FOUND_PLATFORM_FILES ${TEMP})
    
    string(TOUPPER ${CONTEXT} CONTEXT_UPPER)
    target_compile_definitions(Shoko PRIVATE "SHOKO_PLATFORM_${CONTEXT_UPPER}_INCLUDE=\"Platform/${CONTEXT}/${PLATFORM}/${PLATFORM}Platform${CONTEXT}.h\"")
endmacro()

macro(shoko_init_platform PLATFORM)
    set(FOUND_PLATFORM_FILES "")
    
    shoko_include_platform_context("${PLATFORM}" "Input")
    shoko_include_platform_context("${PLATFORM}" "Renderer")
    shoko_include_platform_context("${PLATFORM}" "Window")
    
    target_compile_definitions(Shoko PRIVATE "SHOKO_PLATFORM_USE_${PLATFORM}")
    
    if(FOUND_PLATFORM_FILES)
        target_sources(Shoko PRIVATE ${FOUND_PLATFORM_FILES})
        message(STATUS "Platform [${PLATFORM}]: Added")
    else()
        message(WARNING "Platform [${PLATFORM}]: No files found!")
    endif()
    
        if("${PLATFORM}" STREQUAL "RayLib")
        find_package(raylib REQUIRED)
        target_link_libraries(Shoko PRIVATE raylib)
    elseif("${PLATFORM}" STREQUAL "SDL2")
        find_package(SDL2 REQUIRED CONFIG)
        target_link_libraries(Shoko PRIVATE SDL2::SDL2)
        target_compile_definitions(Shoko PRIVATE SDL_MAIN_HANDLED)
    elseif("${PLATFORM}" STREQUAL "OpenGL")
        find_package(glad CONFIG REQUIRED) 
        find_package(glfw3 REQUIRED)
        find_package(OpenGL REQUIRED)
        target_link_libraries(Shoko PRIVATE glad::glad glfw OpenGL::GL)
    endif()
endmacro()

# Source
file(GLOB_RECURSE BASE_FILES CONFIGURE_DEPENDS "Source/*")
list(FILTER BASE_FILES EXCLUDE REGEX "Source/Shoko/Platform/")
add_executable(Shoko ${BASE_FILES})

shoko_init_platform("OpenGL")

target_include_directories(Shoko PRIVATE Source/Shoko)

if(MSVC)
    add_compile_options(/utf-8)
endif()

# Call:
# mkdir Build
# cd Build
# cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake"
# cmake .. -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
