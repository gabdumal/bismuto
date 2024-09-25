# Library
add_library(constraint)

target_sources(constraint
    PRIVATE
        constraint.cpp
)

# Include self
target_include_directories(constraint
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(constraint
    PRIVATE
        variable
)
