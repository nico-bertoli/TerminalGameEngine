#--------------------------------------------- base setup
cmake_minimum_required(VERSION 3.22)
project(terme VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#--------------------------------------------- create library
file(GLOB_RECURSE SRC 
    "${CMAKE_CURRENT_SOURCE_DIR}/terme/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/terme/*.h"
)

add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

#--------------------------------------------- conan linking
find_package(nbkit REQUIRED)
find_package(SFML REQUIRED COMPONENTS system audio)

target_link_libraries(${PROJECT_NAME} PRIVATE nbkit::nbkit sfml::sfml)

# include X11 lib on linux
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11::X11)
endif()

#--------------------------------------------- install rules
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY terme/
    DESTINATION include/terme
    FILES_MATCHING PATTERN "*.h"
)