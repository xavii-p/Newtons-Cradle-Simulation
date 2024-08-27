cmake_minimum_required(VERSION 3.10)
project(NewtonsCradle)

set(CMAKE_CXX_STANDARD 14)

# Add Emscripten-specific options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s MODULARIZE=1 -s EXPORT_ES6=1 -s USE_ES6_IMPORT_META=1 -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] -s ALLOW_MEMORY_GROWTH=1")

# Include directory for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add source files
add_executable(physics_module
    src/physics_wrapper.cpp
    src/Ball.cpp
    src/RigidBody.cpp
)

# Add header files
target_sources(physics_module PRIVATE
    src/Ball.h
    src/RigidBody.h
    src/Vec3D.h
)

# Set the output name
set_target_properties(physics_module PROPERTIES OUTPUT_NAME "physicsSim")

# Link against the embind library
set_target_properties(physics_module PROPERTIES LINK_FLAGS "--bind")