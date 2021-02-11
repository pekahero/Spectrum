#include "files-comparison.h"
#include "linear-capsule.h"
#include "write-read-files.h"

#include <chrono>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) {
	const regex filename_mask_txt = regex(R"(.*\.txt)");
	// Check if command line arguments of input/output files are correct.
	if (argc > 4) {
		if (!(string(argv[1]) == "-i") || !(regex_match(argv[2], filename_mask_txt)) || !(string(argv[3]) == "-o") || !(regex_match(argv[4], filename_mask_txt))) {
			cerr << "Wrong command line arguments of input/output files!" << endl;
			return EXIT_FAILURE;
		}
	}
	else {
		cerr << "Wrong command line arguments of input/output files!" << endl;
		return EXIT_FAILURE;
	}

	bool is_testing = false;
	string comparison_filename = "";
	// Check if command line arguments of comparison file are correct.
	if (argc > 5)
		if ((string(argv[5]) == "-t") && (argc > 6))
			if (regex_match(argv[6], filename_mask_txt)) {
				comparison_filename = argv[6];
				is_testing = true;
			}
			else {
				cerr << "Wrong command line arguments of comparison file!" << endl;
				return EXIT_FAILURE;
			}
		else
			cout << "If you wanted to test if an output of program is correct, try '-t <filename>' instead.";

	// File's name to read vectors from.
	string input_filename = argv[2];
	// File's name to write spectrum to.
	string output_filename = argv[4];

	//string first_file = argv[1];
	//string second_file = argv[2];

	// Vectors' length and number of vectors.
	uint64_t n = 0, k = 0;
	// Starting, base vectors to work with.
	vector<valarray<bitset<32>>> base_vectors;
	// Spectrum, which will be calculated as a result.
	vector<uint64_t> spectrum;

	// Checks if data is correctly read from file.
	if (!LinearSubspaceSpectrum::read_bites_from_file(base_vectors, n, k, input_filename))
		return EXIT_FAILURE;
	cout << "Data is successfully read from '" << input_filename << "'." << endl;

	cout << "Spectrum calculation has started." << endl;
	chrono::high_resolution_clock::time_point calculating_start = chrono::high_resolution_clock::now();
	// Runs main function to calculate spectrum.
	LinearSubspaceSpectrum::count_spectrum(spectrum, base_vectors, n, k);
	chrono::high_resolution_clock::time_point calculating_stop = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> calculating_time = calculating_stop - calculating_start;
	cout << "Spectrum is calculeted for " << calculating_time.count() << " milliseconds." << endl;

	// Checks if data is correctly written to file.
	if (!LinearSubspaceSpectrum::write_spectrum_to_file(spectrum, output_filename))
		return EXIT_FAILURE;
	cout << "Data is successfully written to '" << output_filename << "'." << endl;

	// Testing output file correctness, if it is needed.
	if (is_testing) {
		cout << endl << "Testing result:" << endl;
		if (!LinearSubspaceSpectrum::compare_two_files(output_filename, comparison_filename))
			return EXIT_FAILURE;
		cout << "Test finished." << endl;
	}

	return EXIT_SUCCESS;
}
