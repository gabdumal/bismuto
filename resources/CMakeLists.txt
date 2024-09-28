# Specify the directory containing the resources
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# Install the resources to the appropriate directory
install(DIRECTORY ${RESOURCE_DIR}/ DESTINATION share/bismuto)

add_subdirectory(examples)

## Copy the resource files to the build directory

# Get all files in the resources directory and its subdirectories
file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_SOURCE_DIR}/resources/*")

# Filter to include only .csv, .glpk, and .ods files
list(FILTER RESOURCE_FILES INCLUDE REGEX "\\.(csv|glpk|ods)$")

# Loop through each file and copy it to the build directory
foreach(RESOURCE_FILE ${RESOURCE_FILES})
    # Get the relative path of the resource file
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/resources" ${RESOURCE_FILE})
    # Copy the resource file to the build directory
    configure_file(${RESOURCE_FILE} ${CMAKE_BINARY_DIR}/share/bismuto/${REL_PATH} COPYONLY)
endforeach()
