# Library
add_library(variable)

target_sources(variable
    INTERFACE
        variable.hpp
)

# Include self
target_include_directories(variable
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(variable
    PRIVATE
        value
)
