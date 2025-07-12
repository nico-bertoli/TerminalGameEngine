cmake_minimum_required(VERSION 3.22)
project(ENGINE_DEMO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Level sources
file(GLOB PLATF0RMER_SRC "Levels/Platformer/*.cpp")
file(GLOB PONG_SRC "Levels/Pong/*.cpp")
file(GLOB SPACE_INVADERS_SRC "Levels/SpaceInvaders/*.cpp")

# Main sources
file(GLOB ENGINE_DEMO_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME}
    ${ENGINE_DEMO_SRC}
    ${PLATF0RMER_SRC}
    ${PONG_SRC}
    ${SPACE_INVADERS_SRC}
)

#------------------- link levels
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Levels/Platformer)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Levels/Pong)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Levels/SpaceInvaders)

#------------------- link engine
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Engine)
target_link_libraries(${PROJECT_NAME} ENGINE)

#------------------- copy files to build directory
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Dependencies/SFML")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${SFML_DIR}/bin/sfml-system-d-2.dll>
        $<$<CONFIG:Debug>:${SFML_DIR}/bin/sfml-audio-d-2.dll>
        $<$<NOT:$<CONFIG:Debug>>:${SFML_DIR}/bin/sfml-system-2.dll>
        $<$<NOT:$<CONFIG:Debug>>:${SFML_DIR}/bin/sfml-audio-2.dll>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# resources folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources"
)

# remove all files from persistence folder
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Persistence
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Persistence
    COMMENT "Deleting all files inside Resources/Persistence before build"
)