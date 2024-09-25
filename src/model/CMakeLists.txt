# Library
add_library(model)

# Sources
target_sources(model
    INTERFACE
        model.hpp
)

# Include self
target_include_directories(model
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(model
    PRIVATE
        value
        variable
        constraint
        objective
)

# Directories
add_subdirectory(value)
add_subdirectory(variable)
add_subdirectory(constraint)
add_subdirectory(objective)
