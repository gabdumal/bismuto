# Version
cmake_minimum_required(VERSION 3.12...3.28)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

# Project
project(bismuto
        LANGUAGES CXX
)

# Environment
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,readability-identifier-naming")

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

# Configure a header file to pass the version information to the source code
configure_file(
  "${CMAKE_SOURCE_DIR}/version.h.in"
  "${CMAKE_BINARY_DIR}/version.h"
  @ONLY
)

# Include the build directory in the include paths
include_directories("${CMAKE_BINARY_DIR}")

# Directories
add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(resources)

# Install the executable
install(TARGETS bismuto DESTINATION bin)
