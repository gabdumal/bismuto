# Executables
add_executable(optimization_model
    main.cpp
)

# Include directories
target_include_directories(optimization_model
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(optimization_model
    PRIVATE
        pretty_console
        uuid
        util
        example
)

# Directories
add_subdirectory(util)
add_subdirectory(example)
