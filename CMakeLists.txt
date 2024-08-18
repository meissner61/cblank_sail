
cmake_minimum_required(VERSION 3.10)
project(Cblank_sail C)


#Add an option for building with 64 or 32 bit on Windows
if(MSVC)
    #Include Directories
    set(SDL2_INCLUDE_DIRS "C:/libs/SDL2-2.26.4")
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8") #checks x64
    set(CMAKE_GENERATOR_PLATFORM x64)
    # Specify the path to the SDL2 manually 
    set(SDL2_LIB ${SDL2_INCLUDE_DIRS}/lib/x64/SDL2.lib)
    set(SDL2MAIN_LIB ${SDL2_INCLUDE_DIRS}/lib/x64/SDL2main.lib)
    set(SDL2_DLL ${SDL2_INCLUDE_DIRS}/lib/x64/SDL2.dll)

    elseif("${CMAKE_SIZEOF_VOID_P}" EQUAL "4") #checks x86
    set(CMAKE_GENERATOR_PLATFORM Win32)
    set(SDL2_LIB "C:/libs/SDL2-2.26.4/lib/x86/SDL2.lib")
    set(SDL2MAIN_LIB "C:/libs/SDL2-2.26.4/lib/x86/SDL2main.lib")
    set(SDL2_DLL "C:/libs/SDL2-2.26.4/lib/x86/SDL2.dll")
    endif()
endif()
# Check if the compiler is MSVC
if(MSVC)
    # Set compiler flags
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Cblank_sail)
    #set_target_properties(Cblank_sail PROPERTIES LINKER_LANGUAGE C)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -I/usr/include/SDL2")
endif()



#WARNING: This will not find subdirectories inside of src/
# Use GLOB_RECURSE for that
file(GLOB SOURCES 
        "src/*.c"
        "src/*.h"
)

add_executable(Cblank_sail ${SOURCES})


# Link SDL2,SDL2_image, spdlog, e.t.c
include_directories(${SDL2_INCLUDE_DIRS}/include)
target_link_libraries(Cblank_sail ${SDL2_LIB} ${SDL2MAIN_LIB})
target_compile_features(Cblank_sail PUBLIC) #Works for MSVC


if(MSVC)
    # Copy SDL2.dll to the output directory
    add_custom_command(TARGET Cblank_sail POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                        ${SDL2_DLL}
                        # ${SDL2_IMG_DLL}
                        # ${SDL2_IMG_zlib}
                        # ${SDL2_IMG_libpng}
                        $<TARGET_FILE_DIR:Cblank_sail>)
endif()