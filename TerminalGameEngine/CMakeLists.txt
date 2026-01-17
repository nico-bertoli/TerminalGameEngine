cmake_minimum_required(VERSION 3.22)
project(TerminalGameEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Force C++20 support
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler extensions

file(GLOB_RECURSE ENGINE_SRC  # Put source files in variable ENGINE_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/Engine/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Engine/*.h"
)

add_library(${PROJECT_NAME} ${ENGINE_SRC})  # Create static library using ENGINE_SRC var

# Add Engine to include path, allows including header files
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Engine"
)

#---------------------------------------- NbaseKit
include(FetchContent)
set(NbaseKitVersion 1.0.0)

FetchContent_Declare(  # Download library
    NbaseKit
    URL https://raw.githubusercontent.com/nico-bertoli/NbaseKit/master/packages/NbaseKit-${NbaseKitVersion}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(NbaseKit)  # Configure library and make it available

# ---------------------------------------- SFML
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SFML")  # Use bundled SFML
message(STATUS "SFML_DIR = ${SFML_DIR}")

target_include_directories(${PROJECT_NAME} PUBLIC "${SFML_DIR}/include")  # Tells compiler where to find haders
target_link_directories(${PROJECT_NAME} PUBLIC "${SFML_DIR}/lib")  # Tells linker where to find library files (.so/a/dll/lib)

target_link_libraries(${PROJECT_NAME}  # Tells linker which libraries to link
    PRIVATE
        NbaseKit
        sfml-system
        sfml-audio
)

#----------------------- CPack Configuration 
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_GENERATOR "TGZ")  # Binary package format
set(CPACK_SOURCE_GENERATOR "TGZ")  # Source package format
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An engine for making 2D terminal games")
set(CPACK_PACKAGE_VENDOR "Nicolò Bertoli")
set(CPACK_PACKAGE_CONTACT "nicobertoli.1999@gmail.com")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/nico-bertoli/TerminalGameEngine")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")  # Output filename
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/packages") # Output directory

#----------------------- CPack Installation Rules
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Engine" DESTINATION .)  # Install Engine/ directory
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" DESTINATION .)  # Install CMakeLists.txt
include(CPack)  # Initialize CPack (must be after install commands)

# ---------------------------------------- Include X11 lib on linux
if(UNIX AND NOT APPLE)  # Linux-specific: X11 library required for terminal management
    find_package(X11 REQUIRED)  # Locate X11 development libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE X11::X11)  # Link X11
endif()
