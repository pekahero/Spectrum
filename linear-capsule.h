#pragma once
#include <bitset>
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <valarray>
#include <vector>

namespace LinearSubspaceSpectrum {

	using namespace std;

	void count_spectrum(vector<uint64_t>& spectrum, const vector<valarray<bitset<32>>>& base_vectors, uint64_t n, uint64_t k);
	static void add_vector_weight(vector<uint64_t>& spectrum, const vector<valarray<bitset<32>>> base_vectors, uint64_t begin, uint64_t length, uint64_t k, mutex& spectrum_multithread_protection);
}