# Library
add_library(constraint INTERFACE)

# Linking libraries
target_link_libraries(constraint
    INTERFACE
        variable
)
