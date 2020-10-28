#include "linear-capsule.h"

using namespace std;

// Main spectrum counting function.
void count_spectrum(vector<size_t>& spectrum, const valarray<valarray<unsigned long long>>& base_vectors, size_t n, size_t k) {
	// Spectrum size is equal to maximum possible amount of "1" in vector. It is n, it is possible to have zero "1", so n+1.
	// Index of element of spectrum equals to amount of "1" in vector. Value of index shows number of vectors with such amount of "1".
	spectrum.resize(n + 1);
	size_t count = 0; // counter for bits = 1 in current vector;
	vector<thread> threads;
	// Number of rows for truth table is equal to 2^(number of columns). And number of columns is k.
	unsigned long long k_2 = pow(2, k);
	// Hardware concurrency.
	size_t concurrency = thread::hardware_concurrency();

	// In block below calculates, how much threads and operations per thread are used.
	bool thread_flag = concurrency > k_2 ? true : false;
	unsigned int threads_amount = thread_flag ? k_2 : concurrency;
	unsigned long long one_thread_operatirons = thread_flag ? 1 : k_2 / concurrency;
	unsigned long long one_thread_operatirons_left = thread_flag ? 0 : k_2 % concurrency;
	unsigned long long one_thread_operatirons_tmp;
	unsigned long long begin = 0;

	// Divides operatins by threads.
	for (size_t i = 0; i < threads_amount; i++) {
		// If number of operations can't be divided equally, some threads get one more operation.
		if (i < one_thread_operatirons_left)
			one_thread_operatirons_tmp = one_thread_operatirons + 1;
		else
			one_thread_operatirons_tmp = one_thread_operatirons;
		threads.push_back(thread(&add_vector_weight_for_slice, ref(spectrum), ref(base_vectors), begin, one_thread_operatirons_tmp, k));
		begin += one_thread_operatirons_tmp;
	}

	// Runs threads.
	for (size_t i = 0; i < threads_amount; i++)
		threads.at(i).join();
}

// Applys function add_vector_weight to each element starting from "begin" to number of "length" elements after it.
static void add_vector_weight_for_slice(vector<size_t>& spectrum, const valarray<valarray<unsigned long long>>& base_vectors, unsigned long long begin, unsigned long long length, size_t k) {
	for (size_t i = 0; i < length; i++)
		add_vector_weight(spectrum, base_vectors, begin + i, k);
}

// Adds 1 to spectrum value that equals to amount of "1" in current composition of multipliers for base_vectors.
static void add_vector_weight(vector<size_t>& spectrum, const valarray<valarray<unsigned long long>>& base_vectors, unsigned long long j, size_t k) {
	// Temporal vector to represent current sum of current composition of multipliers for base_vectors.
	valarray<unsigned long long> tmp_vectors_sum;
	// Counter for bits = 1 in current vector
	size_t count = 0; 
	mutex spectrum_multithread_protection;
	tmp_vectors_sum.resize(base_vectors[0].size());

	// Caiculates tmp_vectors_sum by multiplying each of base_vectors with its current multiplier and summarize them.
	// Using valarray helps to apply binary operations to whole vector, no need to cycle through each element.
	for (size_t i = 0; i < k; i++)
		tmp_vectors_sum ^= (calculate_multiplier(k, i, j) * base_vectors[i]);

	// Counts "1" in bit representation of tmp_vectors_sum.
	for (size_t u = 0; u < tmp_vectors_sum.size(); u++)
		count += count_ones(tmp_vectors_sum[u]);

	// Increases spectrum's element that equals to "count" by 1.
	// Protected as critical section.
	spectrum_multithread_protection.lock();
	spectrum[count] += 1;
	spectrum_multithread_protection.unlock();
}


// Calculates multiplier based on (i) and (j) indexes of table similar to truth table, where k is maximum columns number.
// It is decided to represent multipliers as truth table.
// It is decided to calculate multipliers based on indexes, so no need to store huge tables of them. Calculation is easy due to truth table's symmetry, regularity.
static bool calculate_multiplier(size_t k, size_t i, unsigned long long j) {
	//if ((j / size_t(pow(2, k-1-i))) % 2 == 1)
	size_t tmp = (j >> (k - 1 - i)) % 2;
	if ((j >> (k - 1 - i)) % 2 == 1)
		return(0);
	else
		return(1);
}

// Counts "1" in bit representation of ull.
static size_t count_ones(unsigned long long ull) {
	size_t count = 0;
	for (; ull; count++)
		ull &= (ull - 1);
	return count;
}