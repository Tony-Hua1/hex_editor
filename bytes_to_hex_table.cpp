#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>
#include <typeinfo>
#include <bitset>
#include <cctype>

using namespace std;

// string dec_to_hex(int decimal) {
// 	stringstream ss;
// 	ss << hex << decimal;
// 	string res(ss.str());
// 	return res;
// }

// int main(int argc, const char *argv[]) {
// 	int kMaxArraySize = 0;
// 	char c;
// 	int count = 0;

// 	ifstream input_file(argv[1], ifstream::binary);
	
// 	if (input_file.fail()) {
// 			cerr << "Could not open input file " << argv[1] << endl;
// 			return 2;
// 	}

// 	input_file.seekg(0, ifstream::end);
// 	kMaxArraySize = input_file.tellg();

// 	char char_array[kMaxArraySize];

// 	input_file.seekg(0, ifstream::beg);
	
// 	while (input_file.get(c)) {
// 		char_array[count] = static_cast<unsigned char>(c);
// 		count++;
// 	}

// 	ofstream output(argv[2]);

// 	output << "| Printable           | Hexadecimal | Binary                              | Decimal         |" << endl;
// 	output << "|---------------------+-------------+-------------------------------------+-----------------|" << endl;

// 	for (int i = 0; i < kMaxArraySize; i+=4) {
// 		// Printable
// 		output << '|';
// 		for (int j = i; j < i + 4; j++) {
// 			if (char_array[j] == '\n') {
// 				output << setw(5) << "\\n";
// 			} else if (char_array[j] == '\0') {
// 				output << setw(5) << ' ';
// 			} else if (char_array[j] == '\t') {
// 				output << setw(5) << "\\t";
// 			} else if (char_array[j] == ' ') {
// 				output << setw(5) << " ' '";
// 			} else if (j < kMaxArraySize) {
// 				output << setw(5) << char_array[j];
// 			}
// 		}

// 		// Hexadecimal
// 		output << " |";
// 		for (int j = i; j < i + 4; j++) {
// 			if (j < kMaxArraySize) {
// 				if (char_array[j] == '\n') {
// 					output << setw(3) << '0' + dec_to_hex(static_cast<int>(char_array[j]));
// 				} else if (static_cast<int>(char_array[j]) < 16) {
// 					output << setw(3) << '0' + dec_to_hex(static_cast<int>(char_array[j]));
// 				} else {
// 					output << setw(3) << dec_to_hex(static_cast<int>(char_array[j]));
// 				}
// 			} else if (char_array[j] == '\0') {
// 					output << setw(3) << ' ';
// 			}
// 		}

// 		// Binary
// 		output << " |";
// 		for (int j = i; j < i + 4; j++) {
// 			if (j < kMaxArraySize) {
// 				output << setw(9) << bitset<8>(static_cast<int>(char_array[j]));
// 			} else if (char_array[j] == '\0') {
// 				output << setw(9) << ' ';
// 			}
// 		}

// 		// Decimal
// 		output << " |";
// 		for (int j = i; j < i + 4; j++) {
// 			if (j < kMaxArraySize) {
// 				output << setw(4) << static_cast<int>(char_array[j]);
// 			} else if (char_array[j] == '\0') {
// 				output << setw(4) << ' '; 
// 			}
// 		}

// 		output << " |" << endl;
// 	}

// 	// cout << dec_to_hex(0) << endl;

// 	return 0;
// }


#include <algorithm>
#include <stdexcept>

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

// int main(int argc, const char *argv[]) {
// 	char c;

// 	ifstream input_bytes(argv[1], ifstream::binary);
	
// 	while (input_bytes.get(c)) {
// 		if (static_cast<unsigned int>(c) == 0) {
// 			cout << static_cast<unsigned int>(c) << '\t';
// 			cout << "00" << '\t';
// 			cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';
// 			cout << "\\0" << endl;
// 		} else if (static_cast<unsigned int>(c) > 0 && static_cast<unsigned int>(c) < 16) {
// 			cout << static_cast<unsigned int>(c) << '\t';
// 			cout << '0' + to_string(static_cast<unsigned int>(c), 16) << '\t';
// 			cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';

// 			if (static_cast<unsigned int>(c) == 9) {
// 				cout << "\\t" << endl;
// 			} else if (static_cast<unsigned int>(c) == 10) {
// 				cout << "\\n" << endl;
// 			} else {
// 				cout << "\\x0" + to_string(static_cast<unsigned int>(c), 16) << endl;
// 			}
// 		} else if (static_cast<unsigned int>(c) >= 16 && static_cast<unsigned int>(c) < 32) {
// 			cout << static_cast<unsigned int>(c) << '\t';
// 			cout << to_string(static_cast<unsigned int>(c), 16) << '\t';
// 			cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';
// 			cout << "\\x" + to_string(static_cast<unsigned int>(c), 16) << endl;
// 		} else if (static_cast<unsigned int>(c) >= 32 && static_cast<unsigned int>(c) < 128) {
// 			cout << static_cast<unsigned int>(c) << '\t';
// 			cout << to_string(static_cast<unsigned int>(c), 16) << '\t';
// 			cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';

// 			if (static_cast<unsigned int>(c) == 32) {
// 				cout << " ' '" << endl;
// 			} else {
// 				cout << static_cast<char>(c) << endl;
// 			}
// 		} else {
// 			cout << static_cast<unsigned int>(c) % 256 << '\t';
// 			cout << to_string(static_cast<unsigned int>(c) % 256, 16) << '\t';
// 			cout << to_string(static_cast<unsigned int>(c) % 256, 2) << '\t';
// 			cout << "\\x" + to_string(static_cast<unsigned int>(c) % 256, 16) << endl;
// 		}
// 	}

// 	return 0;
// }

int main(int argc, const char *argv[]) {
	int kMaxArraySize = 0;
	char c;
	int count = 0;
	unsigned decimal = 0;

	ifstream input_bytes(argv[1], ifstream::binary);
	
	if (input_bytes.fail()) {
			cerr << "Could not open input file " << argv[1] << endl;
			return 2;
	}

	input_bytes.seekg(0, ifstream::end);
	kMaxArraySize = input_bytes.tellg();

	// int byte_array[kMaxArraySize];

	unsigned int dec_array[kMaxArraySize];
	string hex_array[kMaxArraySize];
	string bin_array[kMaxArraySize];
	string printable_array[kMaxArraySize];

	input_bytes.seekg(0, ifstream::beg);
	
	// while (input_file.get(c)) {
	// 	byte_array[count] = static_cast<unsigned int>(c);
	// 	count++;
	// }

	while (input_bytes.get(c)) {
		decimal = static_cast<unsigned int>(c);

		if (decimal == 0) {
			dec_array[count] = decimal;
			hex_array[count] = "00";

			ostringstream ss;
			ss << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2);
			string s(ss.str());
			bin_array[count] = s;

			printable_array[count] = "\\0";

			// cout << static_cast<unsigned int>(c) << '\t';
			// cout << "00" << '\t';
			// cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';
			// cout << "\\0" << endl;
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

			// cout << static_cast<unsigned int>(c) << '\t';
			// cout << '0' + to_string(static_cast<unsigned int>(c), 16) << '\t';
			// cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';

			// if (static_cast<unsigned int>(c) == 9) {
			// 	cout << "\\t" << endl;
			// } else if (static_cast<unsigned int>(c) == 10) {
			// 	cout << "\\n" << endl;
			// } else {
			// 	cout << "\\x0" + to_string(static_cast<unsigned int>(c), 16) << endl;
			// }
		} else if (decimal >= 16 && decimal < 32) {
			dec_array[count] = decimal;
			hex_array[count] = to_string(static_cast<unsigned int>(c), 16);

			ostringstream ss;
			ss << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2);
			string s(ss.str());
			bin_array[count] = s;

			printable_array[count] = "\\x" + to_string(static_cast<unsigned int>(c), 16);
			
			// cout << static_cast<unsigned int>(c) << '\t';
			// cout << to_string(static_cast<unsigned int>(c), 16) << '\t';
			// cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';
			// cout << "\\x" + to_string(static_cast<unsigned int>(c), 16) << endl;
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
			
			// cout << static_cast<unsigned int>(c) << '\t';
			// cout << to_string(static_cast<unsigned int>(c), 16) << '\t';
			// cout << setw(8) << setfill('0') << to_string(static_cast<unsigned int>(c), 2) << '\t';

			// if (static_cast<unsigned int>(c) == 32) {
			// 	cout << " ' '" << endl;
			// } else {
			// 	cout << static_cast<char>(c) << endl;
			// }
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

			// cout << static_cast<unsigned int>(c) % 256 << '\t';
			// cout << to_string(static_cast<unsigned int>(c) % 256, 16) << '\t';
			// cout << to_string(static_cast<unsigned int>(c) % 256, 2) << '\t';
			// cout << "\\x" + to_string(static_cast<unsigned int>(c) % 256, 16) << endl;
		}

		count ++;
	}

	ofstream output(argv[2]);

	// for (int i = 0; i < kMaxArraySize; ++i) {
	// 	cout << byte_array[i] << endl;
	// }

	// cout << "| Printable           | Hexadecimal | Binary                              | Decimal         |" << endl;
	// cout << "|---------------------+-------------+-------------------------------------+-----------------|" << endl;

	// for (int i = 0; i < kMaxArraySize; ++i) {
	// 	cout << hex_array[i] << endl;
	// }

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