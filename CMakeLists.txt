# CMakeList.txt : CMake project for CMakeSpectrum, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
project(Linear_subspace_spectrum)
add_executable (Linear_subspace_spectrum "Linear_subspace_spectrum.cpp" "LinearCapsule.cpp" "WriteReadFiles.cpp" "LinearCapsule.h" "WriteReadFiles.h")

# TODO: Add tests and install targets if needed.
