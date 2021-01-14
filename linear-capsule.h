#pragma once
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <valarray>
#include <vector>

using namespace std;

void count_spectrum(vector<size_t>& spectrum, const valarray<valarray<unsigned long long>>& base_vectors, size_t n, size_t k);
static void add_vector_weight_for_slice(vector<size_t>& spectrum, const valarray<valarray<unsigned long long>>& base_vectors, mutex& spectrum_multithread_protection, unsigned long long begin, unsigned long long length, size_t k);
static void add_vector_weight(vector<size_t>& spectrum, const valarray<valarray<unsigned long long>>& base_vectors, mutex& spectrum_multithread_protection, unsigned long long j, size_t k);
static bool calculate_multiplier(size_t k, size_t i, unsigned long long j);
static size_t count_ones(unsigned long long ull);


