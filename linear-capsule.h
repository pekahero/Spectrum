#pragma once
#include <bitset>
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <valarray>
#include <vector>

using namespace std;

void count_spectrum(vector<size_t>& spectrum, const vector<valarray<bitset<32>>>& base_vectors, size_t n, size_t k);
static void add_vector_weight_for_slice(vector<size_t>& spectrum, const vector<valarray<bitset<32>>> base_vectors, int32_t begin, int32_t length, size_t k, mutex& spectrum_multithread_protection);
static void add_vector_weight(vector<size_t>& spectrum, const vector<valarray<bitset<32>>> base_vectors, int32_t j, size_t k, mutex& spectrum_multithread_protection);
static bool calculate_multiplier(size_t k, size_t i, int32_t j);

