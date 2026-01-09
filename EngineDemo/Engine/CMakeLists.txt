cmake_minimum_required(VERSION 3.22)
project(ENGINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# gather .cpp from subfolders too
file(GLOB_RECURSE ENGINE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(${PROJECT_NAME} ${ENGINE_SRC})

# make the engine source dir and subfolders available for #include "Header.h"
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/TerminalManager"
)

#---------------------------------------- NbaseKit
include(FetchContent)
set(NbaseKitVersion 1.0.0)

FetchContent_Declare(
    NbaseKit
    URL https://raw.githubusercontent.com/nico-bertoli/NbaseKit/master/packages/NbaseKit-${NbaseKitVersion}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(NbaseKit)

# ---------------------------------------- SFML
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SFML")
message(STATUS "SFML_DIR = ${SFML_DIR}")

target_include_directories(${PROJECT_NAME} PUBLIC "${SFML_DIR}/include")
target_link_directories(${PROJECT_NAME} PUBLIC "${SFML_DIR}/lib") #working

# ----------------------------------------
target_link_libraries(${PROJECT_NAME}
    PUBLIC NbaseKit
    PRIVATE
        sfml-system$<$<CONFIG:Debug>:-d>
        sfml-audio$<$<CONFIG:Debug>:-d>
)

# ----------------------------------------
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11::X11)
endif()
