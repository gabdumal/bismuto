# Library
add_library(model)

# Sources
target_sources(model
    PUBLIC
        model.hpp
    PRIVATE
        model.cpp
        reading.cpp
)

# Include self
target_include_directories(model
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(model
    PRIVATE
        variable
        constraint
        objective
)

# Directories
add_subdirectory(variable)
add_subdirectory(constraint)
add_subdirectory(objective)
