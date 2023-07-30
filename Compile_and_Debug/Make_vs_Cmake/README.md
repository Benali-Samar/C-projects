# Can i make it ?
The repo contains code example and demo for using the make/cmake build system

#Make vs Cmake
Make is a simple and widely-used build automation tool that relies on platform-specific Makefiles, while CMake is a more feature-rich and platform-independent build system that generates build files for different platforms and build tools. CMake offers more flexibility and ease of use for managing complex projects and is often preferred for cross-platform development.

# Make

To build the project run:
```
make
```
To clean up the artifacts run the following command:
```
make clean
```

# Cmake
Run the below command to generate the build configuration using cmake:
```
cmake -S ./ -B ./build_cmake from the root directory
```
To build the project run make from build_cmake directory:
```
cd build_cmake
make
```
To clean up the artifacts run the following command from the build_cmake directory:
```
make clean
```
