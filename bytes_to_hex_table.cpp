#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>
#include <typeinfo>
#include <bitset>
#include <cctype>

using namespace std;

string dec_to_hex(int decimal) {
	stringstream ss;
	ss << hex << decimal;
	string res(ss.str());
	return res;
}

int main(int argc, const char *argv[]) {
	int kMaxArraySize = 0;
	char c;
	int count = 0;

	ifstream input_file(argv[1], ifstream::binary);
	
	if (input_file.fail()) {
			cerr << "Could not open input file " << argv[1] << endl;
			return 2;
	}

	input_file.seekg(0, ifstream::end);
	kMaxArraySize = input_file.tellg();

	char char_array[kMaxArraySize];

	input_file.seekg(0, ifstream::beg);
	
	while (input_file.get(c)) {
		char_array[count] = static_cast<unsigned char>(c);
		count++;
	}

	ofstream output(argv[2]);

	output << "| Printable           | Hexadecimal | Binary                              | Decimal         |" << endl;
	output << "|---------------------+-------------+-------------------------------------+-----------------|" << endl;

	for (int i = 0; i < kMaxArraySize; i+=4) {
		// Printable
		output << '|';
		for (int j = i; j < i + 4; j++) {
			if (char_array[j] == '\n') {
				output << setw(5) << "\\n";
			} else if (char_array[j] == '\0') {
				output << setw(5) << ' ';
			} else if (char_array[j] == '\t') {
				output << setw(5) << "\\t";
			} else if (char_array[j] == ' ') {
				output << setw(5) << " ' '";
			} else if (j < kMaxArraySize) {
				output << setw(5) << char_array[j];
			}
		}

		// Hexadecimal
		output << " |";
		for (int j = i; j < i + 4; j++) {
			if (j < kMaxArraySize) {
				if (char_array[j] == '\n') {
					output << setw(3) << '0' + dec_to_hex(static_cast<int>(char_array[j]));
				} else if (static_cast<int>(char_array[j]) < 16) {
					output << setw(3) << '0' + dec_to_hex(static_cast<int>(char_array[j]));
				} else {
					output << setw(3) << dec_to_hex(static_cast<int>(char_array[j]));
				}
			} else if (char_array[j] == '\0') {
					output << setw(3) << ' ';
			}
		}

		// Binary
		output << " |";
		for (int j = i; j < i + 4; j++) {
			if (j < kMaxArraySize) {
				output << setw(9) << bitset<8>(static_cast<int>(char_array[j]));
			} else if (char_array[j] == '\0') {
				output << setw(9) << ' ';
			}
		}

		// Decimal
		output << " |";
		for (int j = i; j < i + 4; j++) {
			if (j < kMaxArraySize) {
				output << setw(4) << static_cast<int>(char_array[j]);
			} else if (char_array[j] == '\0') {
				output << setw(4) << ' '; 
			}
		}

		output << " |" << endl;
	}

	// cout << dec_to_hex(0) << endl;

	return 0;
}