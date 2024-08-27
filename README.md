# Physics Engine & Newton's Cradle Simulation

## Overview

This project is a simulation of Newton's Cradle using WebAssembly and Emscripten. The simulation is rendered using Three.js and includes physics calculations for realistic motion.

## Project Structure

- **src/**: Contains the source code for the physics simulation and rendering.
  - `physics_wrapper.cpp`: Main entry point for the physics simulation.
  - `Ball.cpp`: Implementation of the ball physics.
  - `RigidBody.cpp`: Implementation of the rigid body physics.
  - `Ball.h`, `RigidBody.h`, `Vec3D.h`: Header files for the respective implementations.
- **build/**: Contains the build artifacts and configuration files.
  - `physicsSim.js`: Generated JavaScript file from the Emscripten build.
  - `CMakeFiles/`, `CMakeCache.txt`, `build.ninja`, etc.: CMake and Ninja build system files.
- **test.html**: HTML file to run the simulation in a web browser.

## Build Instructions

1. **Set up Emscripten environment**:

   ```sh
   call path\to\emsdk_env.bat
   ```

2. **Configure the project using CMake**:

   ```sh
   cmake -G Ninja -B build -S . -DCMAKE_TOOLCHAIN_FILE=%EMSDK%\upstream\emscripten\cmake\Modules\Platform\Emscripten.cmake -DCMAKE_CROSSCOMPILING_EMULATOR=%EMSDK%\node\18.20.3_64bit\bin\node.exe
   ```

3. **Build the project using Ninja**:
   ```sh
   emmake ninja -C build
   ```

## Running the Simulation

1. Open `test.html` in a web browser to view the simulation.

## Dependencies

- **Emscripten**: For compiling C++ code to WebAssembly.
- **Three.js**: For rendering the simulation.
- **CMake**: For managing the build process.
- **Ninja**: For building the project.

## License

This project is licensed under the MIT License.

## Acknowledgements

- Emscripten for enabling C++ to WebAssembly compilation.
- Three.js for providing a powerful 3D rendering library.
