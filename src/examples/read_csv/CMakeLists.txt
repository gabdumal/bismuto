# Library
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

# # Path to the model file relative to the source directory
# set(SRC__EXAMPLES__READ_CSV__DATA_CSV "${CMAKE_SOURCE_DIR}/src/examples/read_csv/data.csv")

# # Custom target to copy the model file
# add_custom_target(copy__src__examples__read_csv__data_csv ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC__EXAMPLES__READ_CSV__DATA_CSV} $<TARGET_FILE_DIR:read_csv>/data.csv
#     DEPENDS ${SRC__EXAMPLES__READ_CSV__DATA_CSV}
# )

# # Rewrite the model file every time the target is built
# add_dependencies(read_csv copy__src__examples__read_csv__data_csv)
