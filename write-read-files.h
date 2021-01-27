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

using namespace std;

bool read_bites_from_file(vector<valarray<bitset<32>>> & vectors, size_t& n, size_t& k, string& filename);
bool write_spectrum_to_file(const vector<size_t>& spectrum, string& filename);
