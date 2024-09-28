# Library
add_library(book_c3_s1_sc5)

target_sources(book_c3_s1_sc5
    PRIVATE
        book_c3_s1_sc5.cpp
)

# Include self
target_include_directories(book_c3_s1_sc5
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(book_c3_s1_sc5
    PRIVATE
        glpk
        util
)
