#include "linear-capsule.h"

namespace LinearSubspaceSpectrum {

	using namespace std;

	// Main spectrum counting function.
	void count_spectrum(vector<uint64_t>& spectrum, const vector<valarray<bitset<32>>>& base_vectors, uint64_t n, uint64_t k) {
		// Spectrum size is equal to maximum possible amount of "1" in vector. It is n, it is possible to have zero "1", so n+1.
		// Index of element of spectrum equals to amount of "1" in vector. Value of index shows number of vectors with such amount of "1".
		spectrum.resize(n + 1);
		vector<thread> threads;
		// Number of rows for truth table is equal to 2^(number of columns). And number of columns is k.
		const uint64_t k_2 = static_cast<uint64_t>(pow(2, k));
		// Hardware concurrency.
		const uint64_t concurrency = thread::hardware_concurrency();

		// In block below calculates, how much threads and operations per thread are used.
		const bool thread_flag = concurrency > k_2 ? true : false;
		const uint64_t threads_amount = thread_flag ? k_2 : concurrency;
		const uint64_t one_thread_operatirons = thread_flag ? 1 : k_2 / concurrency;
		const uint64_t one_thread_operatirons_left = thread_flag ? 0 : k_2 % concurrency;
		uint64_t one_thread_operatirons_tmp;
		uint64_t begin = 0;
		mutex spectrum_multithread_protection;

		// Divides operations by threads.
		for (uint64_t i = 0; i < threads_amount; i++) {
			// If number of operations can't be divided equally, some threads get one more operation.
			if (i < one_thread_operatirons_left)
				one_thread_operatirons_tmp = one_thread_operatirons + 1;
			else
				one_thread_operatirons_tmp = one_thread_operatirons;
			threads.push_back(thread(&add_vector_weight, ref(spectrum), base_vectors, begin, one_thread_operatirons_tmp, k, ref(spectrum_multithread_protection)));
			begin += one_thread_operatirons_tmp;
		}
		// Runs threads.
		for (uint64_t i = 0; i < threads_amount; i++)
			threads.at(i).join();
	}

	// Add vectors' weights values to spectrum starting from "begin" vector to "begin + length" vector.
	static void add_vector_weight(vector<uint64_t>& spectrum, const vector<valarray<bitset<32>>> base_vectors, uint64_t begin, uint64_t length, uint64_t k, mutex& spectrum_multithread_protection) {
		uint64_t n_32 = base_vectors[0].size();
		valarray<bitset<32>> tmp_vectors_sum;
		tmp_vectors_sum.resize(n_32);
		uint64_t count_ones = 0;
		uint64_t multipliers = 0;
		uint64_t previous_multipliers = 0;

		// Go through all vectors at current thread and adding its values to spectrum.
		for (uint64_t i = begin; i < begin + length; i++) {
			count_ones = 0;

			if (i == begin) {
				multipliers = begin ^ (begin >> 1);
				// Add first vectors' sum.
				for (uint64_t i = 0; i < k; i++)
					// If multiplier is 0, operation can be skipped. 
					if ((uint64_t(1) << i) & multipliers)
						tmp_vectors_sum ^= base_vectors[i];
			}
			else {
				previous_multipliers = multipliers;
				multipliers = i ^ (i >> 1);
				// Add exactly one vector to vectors' sum.
				tmp_vectors_sum ^= base_vectors[log2(previous_multipliers ^ multipliers)];
			}

			// Count "1"s in current vectors' sum.
			for (uint64_t j = 0; j < n_32; j++)
				count_ones += tmp_vectors_sum[j].count();

			// Protected section - adding spectrum value.
			spectrum_multithread_protection.lock();
			spectrum[count_ones]++;
			spectrum_multithread_protection.unlock();
		}
	}
}
