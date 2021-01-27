#include "linear-capsule.h"

using namespace std;

// Main spectrum counting function.
void count_spectrum(vector<size_t>& spectrum, const vector<valarray<bitset<32>>>& base_vectors, size_t n, size_t k) {
	// Spectrum size is equal to maximum possible amount of "1" in vector. It is n, it is possible to have zero "1", so n+1.
	// Index of element of spectrum equals to amount of "1" in vector. Value of index shows number of vectors with such amount of "1".
	spectrum.resize(n + 1);
	size_t count = 0; // counter for bits = 1 in current vector;
	vector<thread> threads;
	// Number of rows for truth table is equal to 2^(number of columns). And number of columns is k.
	const int32_t k_2 = pow(2, k);
	// Hardware concurrency.
	const size_t concurrency = thread::hardware_concurrency();

	// In block below calculates, how much threads and operations per thread are used.
	const bool thread_flag = concurrency > k_2 ? true : false;
	const uint8_t threads_amount = thread_flag ? k_2 : concurrency;
	const uint32_t one_thread_operatirons = thread_flag ? 1 : k_2 / concurrency;
	const uint32_t one_thread_operatirons_left = thread_flag ? 0 : k_2 % concurrency;
	uint32_t one_thread_operatirons_tmp;
	uint32_t begin = 0;
	mutex spectrum_multithread_protection;

	// Divides operations by threads.
	for (size_t i = 0; i < threads_amount; i++) {
		// If number of operations can't be divided equally, some threads get one more operation.
		if (i < one_thread_operatirons_left)
			one_thread_operatirons_tmp = one_thread_operatirons + 1;
		else
			one_thread_operatirons_tmp = one_thread_operatirons;
		threads.push_back(thread(&add_vector_weight_for_slice, ref(spectrum), base_vectors, begin, one_thread_operatirons_tmp, k, ref(spectrum_multithread_protection)));
		begin += one_thread_operatirons_tmp;
	}
	// Runs threads.
	for (size_t i = 0; i < threads_amount; i++)
		threads.at(i).join();
}



// Applys function add_vector_weight to each element starting from "begin" to number of "length" elements after it.
static void add_vector_weight_for_slice(vector<size_t>& spectrum, const vector<valarray<bitset<32>>> base_vectors, int32_t begin, int32_t length, size_t k, mutex& spectrum_multithread_protection) {
	for (size_t i = 0; i < length; i++)
		add_vector_weight(spectrum, base_vectors, begin + i, k, spectrum_multithread_protection);
}

// Adds 1 to spectrum value that equals to amount of "1" in current composition of multipliers for base_vectors.
static void add_vector_weight(vector<size_t>& spectrum, const vector<valarray<bitset<32>>> base_vectors, int32_t j, size_t k, mutex& spectrum_multithread_protection) {
	// Temporal vector to represent current sum of current composition of multipliers for base_vectors.
	valarray<bitset<32>> tmp_vectors_sum;
	// Counter for bits = 1 in current vector
	size_t count_ones = 0; 
	tmp_vectors_sum.resize(base_vectors[0].size());
	// Calculates tmp_vectors_sum by multiplying each of base_vectors with its current multiplier and summarize them.
	// Using valarray helps to apply binary operations to whole vector, no need to cycle through each element.
	for (size_t i = 0; i < k; i++)
		// If multiplier is 0, operation can be skipped. 
		if (calculate_multiplier(k, i, j) == 1)
			tmp_vectors_sum ^= base_vectors[i];

	// Counts "1" in bit representation of tmp_vectors_sum.
	for (size_t u = 0; u < tmp_vectors_sum.size(); u++)
		count_ones += tmp_vectors_sum[u].count();

	// Increases spectrum's element that equals to "count" by 1.
	// Protected as critical section.
	spectrum_multithread_protection.lock();
	spectrum[count_ones]++;
	spectrum_multithread_protection.unlock();
}

// Calculates multiplier based on (i) and (j) indexes of table similar to truth table, where (k) is maximum columns number.
// It is decided to represent multipliers as truth table.
// It is decided to calculate multipliers based on indexes, so no need to store huge tables of them. Calculation is easy due to truth table's symmetry, regularity.
static bool calculate_multiplier(size_t k, size_t i, int32_t j) {
	if ((j >> (k - 1 - i)) % 2 == 1)
		return(1);
	else
		return(0);
}