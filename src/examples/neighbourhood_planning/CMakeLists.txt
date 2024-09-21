# Project
add_library(neighbourhood_planning)

target_sources(neighbourhood_planning
    PRIVATE
        neighbourhood_planning.cpp
)

# Include self
target_include_directories(neighbourhood_planning
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(neighbourhood_planning
    PRIVATE
        glpk
        util
)

# Path to the model file relative to the source directory
set(SRC__EXAMPLES__NEIGHBOURHOOD_PLANNING__MODEL_ODS "${CMAKE_SOURCE_DIR}/src/examples/neighbourhood_planning/model.ods")

# Custom target to copy the model file
add_custom_target(copy__src_examples_neighbourhood_planning_ods ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC__EXAMPLES__NEIGHBOURHOOD_PLANNING__MODEL_ODS} $<TARGET_FILE_DIR:neighbourhood_planning>/model.ods
    DEPENDS ${SRC__EXAMPLES__NEIGHBOURHOOD_PLANNING__MODEL_ODS}
)

# Rewrite the model file every time the target is built
add_dependencies(neighbourhood_planning copy__src_examples_neighbourhood_planning_ods)
