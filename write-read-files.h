#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <valarray>
#include <vector>

using namespace std;

bool read_bites_from_file(valarray<valarray<unsigned long long>>& vectors, size_t& n, size_t& k, string& filename);
static void convert_s_to_ull_slice(valarray<valarray<unsigned long long>>& vectors, const vector<string>& lines, size_t begin, size_t length, size_t n);
static valarray<unsigned long long> convert_s_to_ull(const string& line, size_t n);
bool write_spectrum_to_file(const vector<size_t>& spectrum, string& filename);
