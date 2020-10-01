#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

bool readBitesFromFile(vector < vector< unsigned long long> > &vector, size_t& n, size_t& k, string& filename);
bool writeSpectrumToFile(vector<size_t>& spectrum, string& filename);
