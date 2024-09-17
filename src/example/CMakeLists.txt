# Project
add_library(example)

# Sources
target_sources(example
    PUBLIC
        example.hpp
    PRIVATE
        example.cpp
)

# Include self
target_include_directories(example
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(example
    PRIVATE
        pretty_console
        uuid
        util
)

# Directories
add_subdirectory(example_constants)
