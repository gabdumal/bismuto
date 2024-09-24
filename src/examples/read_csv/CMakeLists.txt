# Project
add_library(read_csv)

target_sources(read_csv
    PRIVATE
        read_csv.cpp
)

# Include self
target_include_directories(read_csv
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(read_csv
    PRIVATE
        constants
        util
)

# Path to the model file relative to the source directory
set(SRC__EXAMPLES__read_csv__MODEL_ODS "${CMAKE_SOURCE_DIR}/src/examples/read_csv/model.ods")

# Custom target to copy the model file
add_custom_target(copy__src_examples_read_csv_ods ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC__EXAMPLES__read_csv__MODEL_ODS} $<TARGET_FILE_DIR:read_csv>/model.ods
    DEPENDS ${SRC__EXAMPLES__read_csv__MODEL_ODS}
)

# Rewrite the model file every time the target is built
add_dependencies(read_csv copy__src_examples_read_csv_ods)
