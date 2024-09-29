# Executables
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
add_executable(bismuto
    main.cpp
)

# Include directories
target_include_directories(bismuto
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(bismuto
    PRIVATE
        argparse::argparse
        glpk
        pretty_console
        constants
        util
        examples
)

# Directories
add_subdirectory(constants)
add_subdirectory(util)
add_subdirectory(examples)
add_subdirectory(model)
