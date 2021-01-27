#include "write-read-files.h"

using namespace std;

// Function reads bites from file and write them to "vectors" as numbers. Return "false" if reading is failed, "truth" otherwise.
// Vectors are decided to store as valarray of bitset<32>.
bool read_bites_from_file(vector<valarray<bitset<32>>> &vectors, size_t& n, size_t& k, string& filename) {
	// Check if file is opened.
	ifstream ifs(filename.c_str());
	if (!ifs.is_open()){
		cerr << "Can not open this file!" << endl;
		return false;
	}

	vector<string> lines;
	string line;

	// First, reads lines of file to "lines". Count them to "k".
	while (getline(ifs, line)) {
		if (k == 0) 
			// Vectors length.
			n = line.length();
		// Check if all lines have same length.
		if (line.length() != n) {
			cerr << "Not all lines have same length!" << endl;
			system("PAUSE");
			return false;
		}
		lines.push_back(line);
		k++;
	}

	// Size of line divided by 32, rounded up.
	size_t n_32 = n / 32 + ( n % 32 ? 1 : 0);
	// Size of vectors is number of vectors, which equal to number of lines in file.
	vectors.resize(k);

	for (size_t i = 0; i < k; i++) {
		vectors[i].resize(n_32);
		for (size_t j = 0; j < n_32; j++)
			vectors[i][j] = bitset<32>(lines[i].substr(32 * j, 32));
	}
	 
	ifs.close();
	return true;
}

// Function writes spectrum to file in form of "index"\t"index's value". Return "false" if writing is failed, "truth" otherwise.
bool write_spectrum_to_file(const vector<size_t>& spectrum, string& filename)
{
	// Checks if file is opened.
	ofstream ofs(filename.c_str(), ios::ate);
	if (!ofs.is_open()){
		cerr << "Can not open this file!" << endl;
		return false;
	}
	// Writes to file.
	for (size_t i = 0; i < spectrum.size(); i++)
		ofs << i << "\t" << spectrum[i] << endl;

	ofs.close();
	return true;
}