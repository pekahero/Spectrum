
# CMakeList.txt : CMake project for CMakeSpectrum, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
project(Linear-subspace-spectrum)
add_executable (linear-subspace-spectrum "linear-subspace-spectrum.cpp" "linear-capsule.cpp" "write-read-files.cpp" "linear-capsule.h" "write-read-files.h")

# TODO: Add tests and install targets if needed.