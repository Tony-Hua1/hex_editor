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

int main(int argc, const char *argv[]) {
	string line;
	
	ifstream input("hi_hex.txt");
	
	getline(input, line);
	if (line != "| Printable           | Hexadecimal | Binary                              | Decimal         |") {
		throw runtime_error("First row does not match!");
	}
	
	getline(input, line);
	if (line != "|---------------------+-------------+-------------------------------------+-----------------|") {
		throw runtime_error("Second row does not match!");
	}

	while (getline(input, line)) {
		int j = 0, k = 0, m = 0, n = 0;

		cout << line << endl;

		for (int i = 0; i < 4; ++i) {

			string s3 = line.substr(3 + j, 4);
			char buf3[4];
			buf3[0] = s3[0];
			buf3[1] = s3[1];
			buf3[2] = s3[2];
			buf3[3] = s3[3];
			if (buf3[0] == 'x') {
				cout << hex_to_int(buf3[1]) * 16 + hex_to_int(buf3[2]) << endl;
			} else if (buf3[0] == ' ' && buf3[1] == '\\') {
				switch (buf3[2]) {
				case '0':
					cout << 0 << endl;
				case 't':
					cout << 9 << endl;
				case 'n':
					cout << 10 << endl;
				}
			} else if (buf3[0] == ' ' && buf3[1] == ' ') {
				cout << int(buf3[2]) << endl;
			} else if (buf3[0] == '\'' && buf3[1] == ' ' && buf3[2] == '\'') {
				cout << 32 << endl;
			}
			// cout << line.substr(3 + j, 4) << endl; // printable

			string s = line.substr(24 + k, 2);
			char buf[2];
			buf[0] = s[0];
			buf[1] = s[1];
			int num = hex_to_int(buf[0]) * 16 + hex_to_int(buf[1]);
			cout << num << endl;
			// cout << line.substr(24 + k, 2) << endl; // hexadecimal
			
			string s2 = line.substr(38 + m, 8);
			char buf2[8];
			buf2[0] = s2[0];
			buf2[1] = s2[1];
			buf2[2] = s2[2];
			buf2[3] = s2[3];
			buf2[4] = s2[4];
			buf2[5] = s2[5];
			buf2[6] = s2[6];
			buf2[7] = s2[7];
			int num2 = binary_to_int(buf2[0]) * 128 + binary_to_int(buf2[1]) * 64 + binary_to_int(buf2[2]) * 32 + binary_to_int(buf2[3]) * 16 + binary_to_int(buf2[4]) * 8 + binary_to_int(buf2[5]) * 4 + binary_to_int(buf2[6]) * 2 + binary_to_int(buf2[7]);
			cout << num2 << endl;
			// cout << line.substr(38 + m, 8) << endl; // binary

			cout << stoi(line.substr(76 + n, 3)) << endl; // decimal

			j += 5;
			k += 3;
			m += 9;
			n += 4;
		}

		cout << endl;
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