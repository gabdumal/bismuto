# Project
add_library(pretty_console)

# Sources
target_sources(pretty_console
    PUBLIC
        pretty_console.hpp
    PRIVATE
        pretty_console.cpp
)

# Include self
target_include_directories(pretty_console
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
