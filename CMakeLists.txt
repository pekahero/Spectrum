# CMakeList.txt : CMake project for CMakeSpectrum

cmake_minimum_required (VERSION 3.8)

project(Linear-subspace-spectrum)
set(CMAKE_CXX_STANDARD 11)
add_executable (linear-subspace-spectrum "linear-subspace-spectrum.cpp" 
		"linear-capsule.cpp" "files-comparison.cpp" "write-read-files.cpp" 
		"linear-capsule.h" "write-read-files.h" "files-comparison.h")

make_directory(spectrums_out)
enable_testing()

include(ProcessorCount)
ProcessorCount(N_processor)
if(NOT N_processor EQUAL 0)
	set(CTEST_BUILD_FLAGS -j${N_processor})
	set(CMAKE_BUILD_PARALLEL_LEVEL ${N_processor})
endif()

add_test(test_1[20_32] linear-subspace-spectrum "-i" "in/tst_20_32.txt" "-o" "spectrums_out/tst_20_32.txt" "-t" "out/tst_20_32.txt")
add_test(test_2[20_8192] linear-subspace-spectrum "-i" "in/tst_20_8192.txt" "-o" "spectrums_out/tst_20_8192.txt" "-t" "out/tst_20_8192.txt")
add_test(test_3[24_8] linear-subspace-spectrum "-i" "in/tst_24_8.txt" "-o" "spectrums_out/tst_24_8.txt" "-t" "out/tst_24_8.txt")
add_test(test_4[24_32] linear-subspace-spectrum "-i" "in/tst_24_32.txt" "-o" "spectrums_out/tst_24_32.txt" "-t" "out/tst_24_32.txt")
add_test(test_5[25_8] linear-subspace-spectrum "-i" "in/tst_25_8.txt" "-o" "spectrums_out/tst_25_8.txt" "-t" "out/tst_25_8.txt")
add_test(test_6[30_8] linear-subspace-spectrum "-i" "in/tst_30_8.txt" "-o" "spectrums_out/tst_25_8.txt" "-t" "out/tst_30_8.txt")
add_test(test_7[31_32] linear-subspace-spectrum "-i" "in/tst_31_32.txt" "-o" "spectrums_out/tst_31_32.txt" "-t" "out/tst_31_32.txt")
add_test(test_8[32_32] linear-subspace-spectrum "-i" "in/tst_32_32.txt" "-o" "spectrums_out/tst_32_32.txt" "-t" "out/tst_32_32.txt")
add_test(test_9[32_64] linear-subspace-spectrum "-i" "in/tst_32_64.txt" "-o" "spectrums_out/tst_32_64.txt" "-t" "out/tst_32_64.txt")
add_test(test_10[32_256] linear-subspace-spectrum "-i" "in/tst_32_256.txt" "-o" "spectrums_out/tst_32_256.txt" "-t" "out/tst_32_256.txt")
add_test(test_11[33_64] linear-subspace-spectrum "-i" "in/tst_33_64.txt" "-o" "spectrums_out/tst_33_64.txt" "-t" "out/tst_33_64.txt")

set_tests_properties(test_1[20_32] test_2[20_8192] test_2[20_8192] test_3[24_8] test_4[24_32] test_5[25_8] test_6[30_8]
			test_7[31_32] test_8[32_32] test_9[32_64] test_10[32_256] test_11[33_64]
			PROPERTIES PASS_REGULAR_EXPRESSION "Files match")