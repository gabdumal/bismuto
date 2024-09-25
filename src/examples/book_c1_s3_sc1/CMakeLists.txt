# Library
add_library(book_c1_s3_sc1)

target_sources(book_c1_s3_sc1
    PRIVATE
        book_c1_s3_sc1.cpp
)

# Include self
target_include_directories(book_c1_s3_sc1
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(book_c1_s3_sc1
    PRIVATE
        glpk
)
