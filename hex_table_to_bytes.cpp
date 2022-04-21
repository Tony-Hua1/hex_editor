#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int to_int(char c, int base);
int to_int(string str, int base);
char to_char(int num);
string to_string(int num, int base);

int hex_to_int(char c);
int binary_to_int(char c);

int char_to_dec(string str);
int hex_to_dec(string str);
int bin_to_dec(string str);
bool is_byte_empty(string str);

// void find_formatted_byte(string line) {
// 	int j = 0, k = 0, m = 0, n = 0;
// 	int column_dec[4];

// 	// cout << line << endl;

// 	for (int i = 0; i < 4; ++i) {
// 		if (is_byte_empty(line.substr(3 + j, 4))) {
// 			j += 5;
// 			k += 3;
// 			m += 9;
// 			n += 4;
			
// 			continue;
// 		} else {
// 			column_dec[0] = char_to_dec(line.substr(3 + j, 4));
// 			column_dec[1] = hex_to_dec(line.substr(24 + k, 2));
// 			column_dec[2] = bin_to_dec(line.substr(38 + m, 8));
// 			column_dec[3] = stoi(line.substr(76 + n, 3));

// 			if (column_dec[0] != column_dec[1] && column_dec[0] != column_dec[2] && column_dec[0] != column_dec[3]) {
// 				cout << static_cast<char>(column_dec[0]); 
// 			} else if (column_dec[1] != column_dec[0] && column_dec[1] != column_dec[2] && column_dec[1] != column_dec[3]) {
// 				cout << static_cast<char>(column_dec[1]); 
// 			} else if (column_dec[2] != column_dec[0] && column_dec[2] != column_dec[1] && column_dec[2] != column_dec[3]) {
// 				cout << static_cast<char>(column_dec[2]); 
// 			} else if (column_dec[3] != column_dec[0] && column_dec[3] != column_dec[1] && column_dec[3] != column_dec[2]) {
// 				cout << static_cast<char>(column_dec[3]); 
// 			} else {
// 				cout << static_cast<char>(column_dec[0]); 
// 			}
// 		}

// 		j += 5;
// 		k += 3;
// 		m += 9;
// 		n += 4;
// 	}
// }

int main(int argc, const char *argv[]) {
	string line;
	
	// ifstream input("hi_hex.txt");

	ifstream input(argv[1]);
	ofstream output(argv[2]);
	
	getline(input, line);
	if (line != "| Printable           | Hexadecimal | Binary                              | Decimal         |") {
		throw runtime_error("First row does not match!");
	}
	
	getline(input, line);
	if (line != "|---------------------+-------------+-------------------------------------+-----------------|") {
		throw runtime_error("Second row does not match!");
	}

	while (getline(input, line)) {
		// find_formatted_byte(line);

		int j = 0, k = 0, m = 0, n = 0;
		int column_dec[4];

		// cout << line << endl;

		for (int i = 0; i < 4; ++i) {
			if (is_byte_empty(line.substr(3 + j, 4))) {
				j += 5;
				k += 3;
				m += 9;
				n += 4;
				
				continue;
			} else {
				column_dec[0] = char_to_dec(line.substr(3 + j, 4));
				column_dec[1] = hex_to_dec(line.substr(24 + k, 2));
				column_dec[2] = bin_to_dec(line.substr(38 + m, 8));
				column_dec[3] = stoi(line.substr(76 + n, 3));

				if (column_dec[0] != column_dec[1] && column_dec[0] != column_dec[2] && column_dec[0] != column_dec[3]) {
					output << static_cast<char>(column_dec[0]); 
				} else if (column_dec[1] != column_dec[0] && column_dec[1] != column_dec[2] && column_dec[1] != column_dec[3]) {
					output << static_cast<char>(column_dec[1]); 
				} else if (column_dec[2] != column_dec[0] && column_dec[2] != column_dec[1] && column_dec[2] != column_dec[3]) {
					output << static_cast<char>(column_dec[2]); 
				} else if (column_dec[3] != column_dec[0] && column_dec[3] != column_dec[1] && column_dec[3] != column_dec[2]) {
					output << static_cast<char>(column_dec[3]); 
				} else {
					output << static_cast<char>(column_dec[0]); 
				}
			}

			j += 5;
			k += 3;
			m += 9;
			n += 4;
		}
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

int hex_to_int(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  }
  throw runtime_error("Char is not a hex char!");
}

int binary_to_int(char c) {
  if (c >= '0' && c <= '1') {
    return c - '0';
  }
  throw runtime_error("Char is not a binary char!");
}

int char_to_dec(string str) {
	char buf[4];

	for (int i = 0; i < str.length(); ++i) {
		buf[i] = str[i];
	}

	if (buf[0] == 'x') {
		return hex_to_int(buf[1]) * 16 + hex_to_int(buf[2]);
	} else if (buf[0] == ' ' && buf[1] == '\\') {
		switch (buf[2]) {
		case '0':
			return 0;
		case 't':
			return 9;
		case 'n':
			return 10;
		}
	} else if (buf[0] == ' ' && buf[1] == ' ') {
		return int(buf[2]);
	} else if (buf[0] == '\'' && buf[1] == ' ' && buf[2] == '\'') {
		return 32;
	}
	throw runtime_error("Could not convert chararacter to a decimal!");
}

int hex_to_dec(string str) {
	char buf[2];

	buf[0] = str[0];
	buf[1] = str[1];
	
	return hex_to_int(buf[0]) * 16 + hex_to_int(buf[1]);
}

int bin_to_dec(string str) {
	char buf[8];

	for (int i = 0; i < str.length(); ++i) {
		buf[i] = str[i];
	}

	return binary_to_int(buf[0]) * 128 + binary_to_int(buf[1]) * 64 + binary_to_int(buf[2]) * 32 + binary_to_int(buf[3]) * 16 + binary_to_int(buf[4]) * 8 + binary_to_int(buf[5]) * 4 + binary_to_int(buf[6]) * 2 + binary_to_int(buf[7]);
}

bool is_byte_empty(string str) {
	char buf[4];

	for (int i = 0; i < str.length(); ++i) {
		buf[i] = str[i];
	}

	if (buf[0] == ' ' && buf[1] == ' ' && buf[2] == ' ') {
		return true;
	} else {
		return false;
	}
}