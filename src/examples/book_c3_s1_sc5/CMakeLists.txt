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
)

# Define the path to the model.glpk file relative to the binary directory
set(SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH "${CMAKE_BINARY_DIR}/src/examples/book_c3_s1_sc5/model.glpk")

# Add the definition to the compiler
add_definitions(-DSRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH=\"${SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH}\")

# # Copy the model.glpk file to the binary directory
# add_custom_command(
#   TARGET book_c3_s1_sc5 POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy
#           ${CMAKE_SOURCE_DIR}/src/examples/book_c3_s1_sc5/model.glpk
#           ${SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH}
# )

# Add a custom command to copy the model.glpk file to the binary directory
add_custom_command(
  OUTPUT ${SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH}
  COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_SOURCE_DIR}/src/examples/book_c3_s1_sc5/model.glpk
          ${SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH}
  DEPENDS ${CMAKE_SOURCE_DIR}/src/examples/book_c3_s1_sc5/model.glpk
)

# Add a custom target that depends on the copied file
add_custom_target(copy__src__examples__book_c3_s1_sc5__model ALL DEPENDS ${SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH})

# Ensure the executable depends on the custom target
add_dependencies(book_c3_s1_sc5 copy__src__examples__book_c3_s1_sc5__model)
