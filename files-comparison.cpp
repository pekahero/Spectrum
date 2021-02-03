#include "files-comparison.h"

namespace LinearSubspaceSpectrum{

	using namespace std;

	bool compare_two_files(string& first_file, string& second_file) {
		// Check if first file is opened.
		ifstream ifs_1(first_file);
		if (!ifs_1.is_open()) {
			cerr << "\tCan not open first file!" << endl;
			return false;
		}
		// Check if file is opened.
		ifstream ifs_2(second_file);
		if (!ifs_2.is_open()) {
			cerr << "\tCan not open second file!" << endl;
			return false;
		}

		string first_line, second_line;
		// Read lines from both files and compare them.
		while (!ifs_1.eof() && !ifs_2.eof()) {
			getline(ifs_1, first_line);
			getline(ifs_2, second_line);
			if (strcmp(first_line.c_str(), second_line.c_str()) != 0) {
				cout << "\tFiles mismatch." << endl;
				return true;
			}
		}
		cout << "\tFiles match." << endl;

		ifs_1.close();
		ifs_2.close();
		return true;
	}
}