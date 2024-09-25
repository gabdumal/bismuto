# Library
add_library(objective)

target_sources(objective
    PRIVATE
        objective.cpp
)

# Include self
target_include_directories(objective
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(objective
    PRIVATE
        variable
)
