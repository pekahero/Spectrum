#include "WriteReadFiles.h"

using namespace std;

bool readBitesFromFile(vector< vector< unsigned long long>> &vectors, size_t& n, size_t& k, string& filename)
{
	ifstream ifs(filename.c_str());
	if (!ifs.is_open())
	{
		cout << "Can not open this file!" << endl;
		system("PAUSE");
		return false;
	}

	string line;
	unsigned long long ull = 0;
	unsigned long long ull1 = 0;
	unsigned long long ull2 = 0;
	vector<unsigned long long> tmp_vector;

	while (getline(ifs, line))
	{
		n = line.length(); //vectors length

		ull = 0;
		ull1 = 0;
		ull2 = 0;
		tmp_vector.clear();

		for(size_t j = 0; j < n; j++)
		{
			if (j >=  n - (n % 64))
			{
				if (j % 64 < 32)
					ull1 += stoull(line.substr(j, 1)) * pow(2, n % 64 - 1 - j % 64);

				else
					ull2 += stoull(line.substr(j, 1)) * pow(2, n % 64 - 1 - j % 64);

				ull = ull1 + ull2;
			}
			else
			{
				if (j % 64 < 32)
					ull1 += stoull(line.substr(j, 1)) * pow(2, 63 - j % 64);

				else					
					ull2 += stoull(line.substr(j, 1)) * pow(2, 63 - j % 64);

				ull = ull1 + ull2;

				if ((j + 1) % 64 == 0)
				{
					tmp_vector.push_back(ull);
					ull = 0;
					ull1 = 0;
					ull2 = 0;
				}
			}
			
		}

		if(n % 64 != 0) 
			tmp_vector.push_back(ull);

		vectors.push_back(tmp_vector);

		line.clear();

	}
	
	k = vectors.size(); // amount of vectors
	 
	ifs.close();
	return true;
}

bool writeSpectrumToFile(vector<size_t>& spectrum, string& filename) 
{
	ofstream ofs(filename.c_str(), ios::ate);
	if (!ofs.is_open())
	{
		cout << "Can not open this file!" << endl;
		system("PAUSE");
		return false;
	}
	for (size_t i = 0; i < spectrum.size(); i++)
		ofs << i << " | " << spectrum[i] << endl;

	ofs.close();
	return true;
}