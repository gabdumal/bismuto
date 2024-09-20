# Project
add_library(examples)

# Sources
target_sources(examples
    PUBLIC
        examples.hpp
    PRIVATE
        examples.cpp
        book_c1_s3_sc1.cpp
)

# Include self
target_include_directories(examples
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(examples
    PRIVATE
)
