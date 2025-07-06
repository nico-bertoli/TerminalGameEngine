cmake_minimum_required(VERSION 3.22)
project(ENGINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB ENGINE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(${PROJECT_NAME} ${ENGINE_SRC})

# ---------------------------------------- SFML

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SFML")
message(STATUS "SFML_DIR = ${SFML_DIR}")

# include headers
target_include_directories(${PROJECT_NAME} PRIVATE "${SFML_DIR}/include")

# Link lib files
# link_directories("${SFML_DIR}/lib") # not working
target_link_directories(${PROJECT_NAME} PRIVATE "${SFML_DIR}/lib") #working

# add -d if debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_CONFIGURATION_TYPES MATCHES "Debug")
    set(SFML_LIB_SUFFIX "-d")
else()
    set(SFML_LIB_SUFFIX "")
endif()
target_link_libraries(${PROJECT_NAME}
    sfml-system${SFML_LIB_SUFFIX}
    sfml-audio${SFML_LIB_SUFFIX}
)

# copy the SFML DLLs next to your executable for runtime
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_DIR}/bin/sfml-system-2.dll"
        "${SFML_DIR}/bin/sfml-audio-2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
