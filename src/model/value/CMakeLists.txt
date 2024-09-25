# Library
add_library(value)

target_sources(value
    INTRFACE
        value.hpp
)

# Include self
target_include_directories(value
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(value
    PRIVATE
)
