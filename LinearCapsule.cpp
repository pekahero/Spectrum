#include "LinearCapsule.h"

using namespace std;

void generateAllMultipliers(size_t& k, vector<vector<bool>> & multipliers)
{
	size_t k_2 = pow(2, k);
	multipliers.resize(k_2);
	

	for (size_t i = k; i > 0; i--)
	{
		for (size_t j = 0; j < k_2; j++)
		{
			if ((j / size_t(pow(2, i-1))) % 2 == 0)
				multipliers[j].push_back(1);
			else
				multipliers[j].push_back(0);

		}		
	}
}

vector<size_t> countSpectrum(vector<vector<bool>>& multipliers, vector<vector<unsigned long long>>& basis, size_t& n)
{
	vector<size_t> spectrum;
	spectrum.resize(n + 1);
	vector<unsigned long long> tmp_vectors_sum;
	size_t count = 0; // counter for bits = 1 in current vector;
	vector<thread> threads;

	for (size_t i = 0; i < multipliers.size(); i++)		
		threads.push_back(thread(&vectorWeight, ref(spectrum), ref(multipliers[i]), ref(basis)));

	for (size_t i = 0; i < multipliers.size(); i++)
		threads.at(i).join();		

	return spectrum;
}

void vectorWeight(vector<size_t>& spectrum, vector<bool>& multipliers, vector<vector<unsigned long long>>& basis)
{
	vector<unsigned long long> tmp_vectors_sum;
	size_t count = 0; // counter for bits = 1 in current vector;
	
	tmp_vectors_sum.clear();
	count = 0;
	for (size_t j = 0; j < basis.size(); j++)
	{
		tmp_vectors_sum.resize(basis[j].size());
		for (size_t u = 0; u < basis[j].size(); u++)
			tmp_vectors_sum[u] ^= (multipliers[j] * basis[j][u]);								

	}
	for (size_t k = 0; k < tmp_vectors_sum.size(); k++)
		count += countOnes(tmp_vectors_sum[k]);
	spectrum[count]++;
}

size_t countOnes(unsigned long long ull)
{
	size_t count = 0;
	for (; ull; count++)
		ull &= (ull - 1);
	return count;
}
