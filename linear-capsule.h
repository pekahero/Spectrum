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

	void count_spectrum(vector<size_t>& spectrum, const vector<valarray<bitset<32>>>& base_vectors, size_t n, size_t k);
	static void add_vector_weight(vector<size_t>& spectrum, const vector<valarray<bitset<32>>> base_vectors, size_t begin, size_t length, size_t k, mutex& spectrum_multithread_protection);
}