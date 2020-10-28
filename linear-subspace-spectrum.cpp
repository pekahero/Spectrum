#include "linear-capsule.h"
#include "write-read-files.h"

using namespace std;

int main() {
	// Vectors' length and number of vectors.
	size_t n, k;
	// Starting, base vectors to work with.
	valarray<valarray<unsigned long long>> base_vectors;
	// Spectrum, which will be calculated as a result.
	vector<size_t> spectrum;
	
	// File to read from.
	string filename_1;
	cout << "Enter file's name to read vectors from: ";
	cin >> filename_1;
	cout << endl;

	// Checks if data is correctly read from file.
	if (!read_bites_from_file(base_vectors, n, k, filename_1))
		return 0;

	// Runs main function to calculate spectrum.
	count_spectrum(spectrum, base_vectors, n, k);

	// File to write to.
	string filename_2;
	cout << "Enter file's name to write spectrum to: ";
	cin >> filename_2;
	cout << endl;

	// Checks if data is correctly written to file.
	if (!write_spectrum_to_file(spectrum, filename_2))
		return 0;
}
