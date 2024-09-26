# Library
add_library(livestock_diet)

target_sources(livestock_diet
    PRIVATE
        livestock_diet.cpp
)

# Include self
target_include_directories(livestock_diet
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Linking libraries
target_link_libraries(livestock_diet
    PRIVATE
        glpk
        constants
        util
        model
)

# Path to the model file relative to the source directory
set(SRC__EXAMPLES__LIVESTOCK_DIET__MODEL_ODS "${CMAKE_SOURCE_DIR}/src/examples/livestock_diet/model.ods")

# Custom target to copy the model file
add_custom_target(copy__src__examples__livestock_diet__model_ods ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC__EXAMPLES__LIVESTOCK_DIET__MODEL_ODS} $<TARGET_FILE_DIR:livestock_diet>/model.ods
    DEPENDS ${SRC__EXAMPLES__LIVESTOCK_DIET__MODEL_ODS}
)

# Rewrite the model file every time the target is built
add_dependencies(livestock_diet copy__src__examples__livestock_diet__model_ods)
