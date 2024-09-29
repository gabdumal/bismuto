set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER "C:\\msys64\\clang64\\bin\\clang.exe")
set(CMAKE_CXX_COMPILER "C:\\msys64\\clang64\\bin\\clang++.exe")

# Adjust the default behavior of the FIND_XXX() commands:
## Search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
## Search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Find the argparse package
set(argparse_DIR "C:\\Program Files (x86)\\argparse\\lib\\cmake\\argparse")
find_package(argparse REQUIRED)
