#include "WriteReadFiles.h"
#include "LinearCapsule.h"

using namespace std;

int main()
{
	size_t n, k; // vectors' length and number of vectors
	vector<vector<bool>> multipliers;
	vector< vector< unsigned long long> > basis;
	vector<size_t> spectrum;
	
	string filename1; // file to read from
	cout << "Enter file's name to read vectors from: ";
	cin >> filename1;
	cout << endl;

	if (!readBitesFromFile(basis, n, k, filename1))
		return 0;

	generateAllMultipliers(k, multipliers);
	spectrum = countSpectrum(multipliers, basis, n);

	string filename2; // file to write to
	cout << "Enter file's name to write spectrum to: ";
	cin >> filename2;
	cout << endl;

	if (!writeSpectrumToFile(spectrum, filename2))
		return 0;
}
