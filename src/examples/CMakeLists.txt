# Project
add_library(examples)

# Sources
target_sources(examples
    PUBLIC
        examples.hpp
    PRIVATE
        examples.cpp
)

# Include self
target_include_directories(examples
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(examples
    PRIVATE
        glpk
        constants
        util
        book_c1_s3_sc1
        book_c3_s1_sc5
        livestock_diet
        read_csv
)

# Directories
add_subdirectory(book_c1_s3_sc1)
add_subdirectory(book_c3_s1_sc5)
add_subdirectory(livestock_diet)
add_subdirectory(read_csv)
