# Project
target_sources(example
    PUBLIC
        example_constants.hpp
)

# Include self
target_include_directories(example
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
