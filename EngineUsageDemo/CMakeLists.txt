cmake_minimum_required(VERSION 3.22)
project(ENGINE_DEMO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB ENGINE_DEMO_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${PROJECT_NAME} main.cpp)

# ---------------------------------------- linking engine

include(FetchContent)

FetchContent_Declare(
    Engine
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/../Engine
)

# Make the content available
FetchContent_MakeAvailable(Engine)

# link this library you can find in the given path
target_link_libraries(${PROJECT_NAME} ENGINE)