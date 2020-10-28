#include "write-read-files.h"

using namespace std;

// Function reads bites from file and write them to "vectors" as numbers. Return "false" if reading is failed, "truth" otherwise.
// Bits are decided to store as numbers, because unsigned long long stores 64 bits and as symbols they take full byte at least.
bool read_bites_from_file(valarray<valarray<unsigned long long>> &vectors, size_t& n, size_t& k, string& filename) {
	// Check if file is opened.
	ifstream ifs(filename.c_str());
	if (!ifs.is_open()){
		cerr << "Can not open this file!" << endl;
		system("PAUSE");
		return false;
	}

	vector<thread> threads;
	vector<string> lines;
	string line;
	size_t lines_counter = 0;

	// First, reads lines of file to "lines". Count them to "line_counter".
	while (getline(ifs, line)) {
		if (lines_counter == 0) 
			// Vectors length.
			n = line.length();
		// Check if all lines have same length.
		if (line.length() != n) {
			cerr << "Not all lines have same length!" << endl;
			system("PAUSE");
			return false;
		}
		lines.push_back(line);
		lines_counter++;
	}
	valarray<unsigned long long> tmp_vector(line.size()/64 + 1);
	// Size of vectors is number of vectors, which equal to number of lines in file.
	vectors.resize(lines_counter);

	// Hardware concurrency.
	size_t concurrency = thread::hardware_concurrency();

	// In block below calculates, how much threads and operations per thread are used.
	bool thread_flag = concurrency > lines_counter ? true : false;
	unsigned int threads_amount = thread_flag ? lines_counter : concurrency;
	size_t one_thread_operatirons = thread_flag ? 1 : lines_counter / concurrency;
	size_t one_thread_operatirons_left = thread_flag ? 0 : lines_counter % concurrency;
	size_t one_thread_operatirons_tmp;
	size_t begin = 0;
	// Divides operatins by threads.
	for (size_t i = 0; i < threads_amount; i++) {
		// If number of operations can't be divided equally, some threads get one more operation.
		if (i < one_thread_operatirons_left)
			one_thread_operatirons_tmp = one_thread_operatirons + 1;
		else
			one_thread_operatirons_tmp = one_thread_operatirons;
		threads.push_back(thread(&convert_s_to_ull_slice, ref(vectors), ref(lines), begin, one_thread_operatirons_tmp, n));
		begin += one_thread_operatirons_tmp;
	}

	// Runs threads.
	for (unsigned long long i = 0; i < threads_amount; i++)
		threads.at(i).join();

	// Amount of vectors.
	k = vectors.size();
	 
	ifs.close();
	return true;
}

// Runs function convert_s_to_ull for each element in "lines".
static void convert_s_to_ull_slice(valarray<valarray<unsigned long long>>& vectors, const vector<string>& lines, size_t begin, size_t length, size_t n) {
	for (size_t i = 0; i < length; i++)
		vectors[begin + i] = convert_s_to_ull(lines[begin + i], n);
}

// Transforms string line to unsigned long long numbers.
static valarray<unsigned long long> convert_s_to_ull(const string& line, size_t n) {
	unsigned long long ull = 0;
	unsigned long long ull1 = 0;
	unsigned long long ull2 = 0;
	size_t tmp_counter = 0;
	valarray<unsigned long long> tmp_vector(line.size() / 64 + 1);
	tmp_counter = 0;

	// Takes each element of line and convert it from bynary to decimal numerical system based on its index.
	for (size_t j = 0; j < n; j++) {
		if (j >= n - (n % 64)) {
			if (j % 64 < 32)
				ull1 += stoull(line.substr(j, 1)) << (n % 64 - 1 - j % 64); //* pow(2, n % 64 - 1 - j % 64);
			else
				ull2 += stoull(line.substr(j, 1)) << (n % 64 - 1 - j % 64); //* pow(2, n % 64 - 1 - j % 64);
			ull = ull1 + ull2;
		}
		else {
			if (j % 64 < 32)
				ull1 += stoull(line.substr(j, 1)) << (63 - j % 64); //* pow(2, 63 - j % 64);
			else
				ull2 += stoull(line.substr(j, 1)) << (63 - j % 64); //* pow(2, 63 - j % 64);
			ull = ull1 + ull2;

			if ((j + 1) % 64 == 0) {
				tmp_vector[tmp_counter++] = ull;
				ull = 0;
				ull1 = 0;
				ull2 = 0;
			}
		}
	}

	if (n % 64 != 0)
		tmp_vector[tmp_counter++] = ull;

	return tmp_vector;
}

// Function writes spectrum to file in form of "index"\t"index's value". Return "false" if writing is failed, "truth" otherwise.
bool write_spectrum_to_file(const vector<size_t>& spectrum, string& filename)
{
	// Checks if file is opened.
	ofstream ofs(filename.c_str(), ios::ate);
	if (!ofs.is_open()){
		cerr << "Can not open this file!" << endl;
		system("PAUSE");
		return false;
	}
	// Writes to file.
	for (size_t i = 0; i < spectrum.size(); i++)
		ofs << i << "\t" << spectrum[i] << endl;

	ofs.close();
	return true;
}