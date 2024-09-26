# Library
add_library(objective INTERFACE)

# Linking libraries
target_link_libraries(objective
    INTERFACE
        variable
)
