#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>
#include <typeinfo>
#include <bitset>
#include <cctype>
#include <algorithm>
#include <stdexcept>

using namespace std;

int to_int(char c, int base);
int to_int(string str, int base);
char to_char(int num);
string to_string(int num, int base);

int main(int argc, const char *argv[]) {
	int kMaxArraySize = 0;
	char c;
	int count = 0;
	unsigned decimal = 0;

	ifstream input_file(argv[1], ifstream::binary);
	if (input_file.fail()) {
		cerr << "Could not open input file " << '"' << argv[1] << '"' << endl;
		return 2;
	}
	
	if (input_file.fail()) {
			cerr << "Could not open input file " << argv[1] << endl;
			return 2;
	}

	input_file.seekg(0, ifstream::end);
	kMaxArraySize = input_file.tellg();

	unsigned int dec_array[kMaxArraySize];
	string hex_array[kMaxArraySize];
	string bin_array[kMaxArraySize];
	string printable_array[kMaxArraySize];

	input_file.seekg(0, ifstream::beg);

	while (input_file.get(c)) {
		decimal = static_cast<unsigned int>(c);

		if (decimal == 0) {
			dec_array[count] = decimal;
			hex_array[count] = "00";

			ostringstream ss;
			ss << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2);
			string s(ss.str());
			bin_array[count] = s;

			printable_array[count] = "\\0";
		} else if (decimal > 0 && decimal < 16) {
			dec_array[count] = decimal;
			hex_array[count] = '0' + to_string(static_cast<unsigned int>(c), 16);

			ostringstream ss;
			ss << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2);
			string s(ss.str());
			bin_array[count] = s;

			if (decimal == 9) {
				printable_array[count] = "\\t";
			} else if (decimal == 10) {
				printable_array[count] = "\\n";
			} else {
				ostringstream ss2;
				ss2 << "\\x0" + to_string(static_cast<unsigned int>(c), 16);
				string s2(ss2.str());
				printable_array[count] = s2;
			}
		} else if (decimal >= 16 && decimal < 32) {
			dec_array[count] = decimal;
			hex_array[count] = to_string(static_cast<unsigned int>(c), 16);

			ostringstream ss;
			ss << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2);
			string s(ss.str());
			bin_array[count] = s;

			printable_array[count] = "\\x" + to_string(static_cast<unsigned int>(c), 16);
		} else if (decimal >= 32 && decimal < 127) {
			dec_array[count] = decimal;
			hex_array[count] = to_string(static_cast<unsigned int>(c), 16);
			
			ostringstream ss;
			ss << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2);
			string s(ss.str());
			bin_array[count] = s;

			if (decimal == 32) {
				printable_array[count] = " ' '";
			} else {
				printable_array[count] = static_cast<char>(c);
			}
		} else {
			dec_array[count] = decimal % 256;
			hex_array[count] = to_string(static_cast<unsigned int>(c) % 256, 16);

			if (decimal == 127) {
				ostringstream ss;
				ss << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2);
				string s(ss.str());
				bin_array[count] = s;
			} else {
				bin_array[count] = to_string(static_cast<unsigned int>(c) % 256, 2);
			}

			printable_array[count] = "\\x" + to_string(static_cast<unsigned int>(c) % 256, 16);
		}

		count ++;
	}

	ofstream output(argv[2]);
	if (output.fail()) {
		cerr << "Could not open outfile file " << '"' << argv[2] << '"' << endl;
		return 2;
	}

	output << "| Printable           | Hexadecimal | Binary                              | Decimal         |" << endl;
	output << "|---------------------+-------------+-------------------------------------+-----------------|" << endl;

	for (int i = 0; i < kMaxArraySize; i+=4) {
		output << '|';
		for (int j = i; j < i + 4; ++j) {
			if (j < kMaxArraySize) {
				output << setw(5) << printable_array[j];
			} else {
				output << setw(5) << ' ';
			}
		}

		output << " |";
		for (int j = i; j < i + 4; ++j) {
			if (j < kMaxArraySize) {
				output << setw(3) << hex_array[j];
			} else {
				output << setw(3) << ' ';
			}
		}

		output << " |";
		for (int j = i; j < i + 4; ++j) {
			if (j < kMaxArraySize) {
				output << setw(9) << bin_array[j];
			} else {
				output << setw(9) << ' ';
			}
		}

		output << " |";
		for (int j = i; j < i + 4; ++j) {
			if (j < kMaxArraySize) {
				output << setw(4) << dec_array[j];
			} else {
				output << setw(4) << ' ';
			}
		}
		
		output << " |" << endl;
	}

	return 0;
}

int to_int(char c, int base) {
    int num = base;
    if (c >= '0' && c <= '9') {
        num = c - '0';
    } else if (c >= 'a' && c <= 'z') {
        num = c - 'a' + 10;
    }
    if (num < base) {
        return num;
    }
    throw runtime_error("char is not a valid digit!");
}

int to_int(string str, int base=10) {
    int num = 0;
    for (int i = str.size() - 1, place = 1; i >= 0; --i, place *= base) {
        num += to_int(str[i], base) * place;
    }
    return num;
}

char to_char(int num) {
    if (num < 10) {
        return num + '0';
    } else if (num < 36) {
        return num - 10 + 'a';
    }
    throw runtime_error("num is too big to be converted to a char!");
}

string to_string(int num, int base=10) {
    string result;
    while (num != 0) {
        result.push_back(to_char(num % base));
        num /= base;
    }
    reverse(result.begin(), result.end());
    return result;
}