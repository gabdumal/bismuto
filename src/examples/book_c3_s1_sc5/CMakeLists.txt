# Project
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

# Path to the model file relative to the source directory
set(SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_GLPK "${CMAKE_SOURCE_DIR}/src/examples/book_c3_s1_sc5/model.glpk")

# Custom target to copy the model file
add_custom_target(copy__src__examples__book_c3_s1_sc5__model_glpk ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_GLPK} $<TARGET_FILE_DIR:book_c3_s1_sc5>/model.glpk
    DEPENDS ${SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_GLPK}
)

# Rewrite the model file every time the target is built
add_dependencies(book_c3_s1_sc5 copy__src__examples__book_c3_s1_sc5__model_glpk)
