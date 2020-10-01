#pragma once
#include <vector>
#include <iostream>
#include <thread>

using namespace std;

void generateAllMultipliers(size_t& k, vector<vector<bool>>& multipliers);
vector<size_t> countSpectrum(vector<vector<bool>>& multipliers, vector<vector<unsigned long long>>& basis, size_t& n);
static void vectorWeight(vector<size_t>& spectrum, vector<bool>& multipliers, vector<vector<unsigned long long>>& basis);
static size_t countOnes(unsigned long long ull);


