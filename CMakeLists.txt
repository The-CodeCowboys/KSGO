cmake_minimum_required (VERSION 3.5)
project (KeyboardShooter)

# All packages used
find_package(raylib REQUIRED)

# Set static linking
# set(CMAKE_EXE_LINKER_FLAGS "-static")

# Where all the C files go
set(PROJECT_SOURCE_FILES
    src/main.cpp
    src/scenes.cpp
    src/button.cpp
    src/components.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Fixes includes path
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Libraries
target_link_libraries(${PROJECT_NAME}
    raylib
)

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
