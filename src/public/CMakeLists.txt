# Path to the model file relative to the source directory
set(SRC__PUBLIC__CANONICAL_ODS "${CMAKE_SOURCE_DIR}/src/public/canonical.ods")

# Custom target to copy the model file
add_custom_target(copy__src__public__canonical_ods ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC__PUBLIC__CANONICAL_ODS} $<TARGET_FILE_DIR:bismuto>/public/canonical.ods
    DEPENDS ${SRC__PUBLIC__CANONICAL_ODS}
)

# Rewrite the model file every time the target is built
add_dependencies(bismuto copy__src__public__canonical_ods)
