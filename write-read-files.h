#pragma once
#include <bitset>
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <valarray>
#include <vector>

namespace LinearSubspaceSpectrum {

	using namespace std;

	bool read_bites_from_file(vector<valarray<bitset<32>>>& vectors, uint64_t& n, uint64_t& k, string& filename);
	bool write_spectrum_to_file(const vector<uint64_t>& spectrum, string& filename);
}
