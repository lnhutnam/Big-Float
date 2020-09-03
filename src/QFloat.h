#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// constant
#define _QFLOAT_8_LENGTH 8
#define _QFLOAT_8_BIT_EXPONENT 4
#define _QFLOAT_8_BIT_FRACTION 3

#define _QFLOAT_16_LENGTH 16
#define _QFLOAT_16_BIT_EXPONENT 5
#define _QFLOAT_16_BIT_FRACTION 10

#define _QFLOAT_32_LENGTH 32
#define _QFLOAT_32_BIT_EXPONENT 11
#define _QFLOAT_32_BIT_FRACTION 52

#define _QFLOAT_80_LENGTH 80
#define _QFLOAT_80_BIT_EXPONENT 15
#define _QFLOAT_80_BIT_FRACTION 64

#define _QFLOAT_128_LENGTH 128
#define _QFLOAT_128_BIT_EXPONENT 15
#define _QFLOAT_128_BIT_FRACTION 112

#define of "Overflow"
#define uf "Underflow"
#define NaN "None a number"
#define inf "infinity"
#define denor "denormalized"


// Structure
struct _qfloat8_ {
private:
	// sign: 1 bit - exponent: 4 bit - fraction: 3 bit
	unsigned char data = 0;
public:
	// Overloading arithemic operator
	_qfloat8_& operator+(const _qfloat8_&);
	_qfloat8_& operator-(const _qfloat8_&);
	_qfloat8_& operator*(const _qfloat8_&);
	_qfloat8_& operator/(const _qfloat8_&);
};

struct _qfloat16_ {
private:
	// sign: 1 bit - exponent: 5 bit - fraction: 10 bit
	unsigned char data[2] = { 0 };
public:
	// Overloading arithemic operator
	_qfloat16_& operator+(const _qfloat16_&);
	_qfloat16_& operator-(const _qfloat16_&);
	_qfloat16_& operator*(const _qfloat16_&);
	_qfloat16_& operator/(const _qfloat16_&);
};

struct _qfloat32_ {
private:
	// sign: 1 bit - exponent: 8 bit - fraction: 23 bit
	unsigned char data[4] = { 0 };
public:
	// Overloading arithemic operator
	_qfloat32_& operator+(const _qfloat32_&);
	_qfloat32_& operator-(const _qfloat32_&);
	_qfloat32_& operator*(const _qfloat32_&);
	_qfloat32_& operator/(const _qfloat32_&);
};

struct _qfloat64_ {
private:
	// sign: 1 bit - exponent: 11 bit - fraction: 52 bit
	unsigned char data[8] = { 0 };
public:
	// Overloading arithemic operator
	_qfloat64_& operator+(const _qfloat64_&);
	_qfloat64_& operator-(const _qfloat64_&);
	_qfloat64_& operator*(const _qfloat64_&);
	_qfloat64_& operator/(const _qfloat64_&);
};


struct _qfloat80_ {
private:
	// sign: 1 bit - exponent: 15 bit - fraction: 64 bit
	unsigned char data[10] = { 0 };
public:
	// Overloading arithemic operator
	_qfloat80_& operator+(const _qfloat80_&);
	_qfloat80_& operator-(const _qfloat80_&);
	_qfloat80_& operator*(const _qfloat80_&);
	_qfloat80_& operator/(const _qfloat80_&);
};

struct _qfloat128_ {
private:
	// sign: 1 bit - exponent: 15 bit - fraction: 112 bit
	int data[4] = { 0 };
private:
	std::string realMultiplyTwo(std::string real);
	std::string realDivisionTwo(std::string real, bool isDivReal);
	void turn_on_bit_at(int k);
	void turn_off_bit_at(int k);
	int get_bit_at(int k);
public:
	bool isSubNormal();
	bool isNaN();
	bool isInf(bool& negative);
	bool isZero();
	bool isDenormalized();
	void setNaN();
	void setInf(bool negative);
	void setZero();
	// get sign, get exponent, get fraction;
	int getSign();
	int getExponent();
	int getFraction();

	void scanQfloat(std::string str);
	std::string printQfloat();
	_qfloat128_ binToDec(std::string bit);
	std::string decToBin();

	// Overloading arithemic operator
	_qfloat128_& operator+(_qfloat128_&);
	_qfloat128_& operator-(_qfloat128_&);
	_qfloat128_& operator*(_qfloat128_&);
	_qfloat128_& operator/(_qfloat128_&);
};

template<typename T>
T max(T a, T b) {
	return (a > b) ? a : b;
}

template<typename T>
T min(T a, T b) {
	return (a > b) ? b : a;
}

std::string sum_bin(std::string firstStrBin, std::string secondStrBin) {
	std::string b1 = firstStrBin, b2 = secondStrBin;
	while ((int)b1.length() < (int)b2.length()) b1 = "0" + b1;
	while ((int)b1.length() > (int)b2.length()) b2 = "0" + b2;
	int d = 0, i, j;
	for (i = (int)b1.length() - 1, j = (int)b2.length() - 1; i >= 0; --i, --j) {
		char c = b1[i] - '0' + d;
		if (j >= 0) c += b2[j] - '0';
		b1[i] = c % 2 + '0';
		d = c / 2;
		if (i == 0 && d) b1 = "1" + b1;
	}
	if ((int)b1.length() > 128) b1 = b1.substr(1, 128);
	return b1;
}

std::string subtract_bin(std::string firstStrBin, std::string secondStrBin) {
	std::string b1 = firstStrBin, b2 = secondStrBin;
	while ((int)b1.length() < (int)b2.length()) b1 = "0" + b1;
	while ((int)b1.length() > (int)b2.length()) b2 = "0" + b2;
	int d = 0, i;
	for (i = (int)b1.length() - 1; i >= 0; --i) {
		char c = b1[i] - b2[i] - d;
		if (c < 0) c += 2, d = 1;
		else d = 0;
		b1[i] = c + '0';
	}
	if (d) while (b1.length() < 128) b1 = "1" + b1;
	return b1;
}

void make_positive_bin(std::string& bin) {
	int i;
	bin = subtract_bin(bin, "1");
	for (i = 0; i < (int)bin.length(); ++i) {
		if (bin[i] == '0') bin[i] = '1';
		else bin[i] = '0';
	}
	i = 0;
	while (i < bin.length() && bin[i] == '0') i++;
	if (i >= bin.length()) {
		bin = "0";
		return;
	}
	bin = bin.substr(i, bin.length() - i);
}

std::string _round(std::string s, int numberRound) {
	// Step 01: find index of dot in string input
	int dot = -1;
	std::string temp = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') {
			dot = i;
			break;
		}
	}

	// if the dot doesn't exist or numberRound > length - (dot + 2)
	if (dot == -1 || s.length() - 1 - dot < (numberRound + 1)) {
		return s;
	}

	std::string result = s.substr(0, (numberRound + 1 + dot));
	int k = s[(numberRound + 1 + dot)] - '0';
	bool flag = false;
	while (k > 4) {
		if (result[result.length() - 1] == '.') {
			result.erase(result.length() - 1, 1);
			flag = true;
			break;
		}

		if (result[result.length() - 1] == '9') {
			result.erase(result.length() - 1, 1);
		}
		else {
			result[result.length() - 1] = result[result.length() - 1] + 1;
			break;
		}
	}

	if (flag) {
		if (result[0] == '-') {
			// remove sign
			result.erase(0, 1);
			int z;
			for (z = (int)result.length() - 1; z >= -1; z--)
			{
				if (z == -1 || result[z] < '9')
				{
					break;
				}
			}
			// plus 1
			for (int j = z + 1; j < result.length(); j++)
			{
				result[j] = '0';
			}
			if (z == -1)
			{
				result = "1" + result;
			}
			else
			{
				result[z] += 1;
			}
			// place back sign
			result = '-' + result;
		}
		else {
			// plus one
			int z;
			for (z = (int)result.length() - 1; z >= -1; z--)
			{
				if (z == -1 || result[z] < '9')
				{
					break;
				}
			}
			for (int j = z + 1; j < result.length(); j++)
			{
				result[j] = '0';
			}
			if (z == -1)
			{
				result = "1" + result;
			}
			else
			{
				result[z] += 1;
			}
		}
	}
	return result;
}

// Qfloat file IO processing
/*
Parse function
@param string line is the string need to parse
@param string seperator is the separator string
@return an array of subline has parsed by seperator
*/
std::vector<std::string> parse_string_by(std::string line, std::string seperator)
{
	std::vector<std::string> tokens;
	int startPosition = 0;
	size_t foundPosition = line.find(seperator, startPosition);

	while (foundPosition != std::string::npos) {
		int count = foundPosition - startPosition;
		std::string token = line.substr(startPosition, count);

		tokens.push_back(token);

		startPosition = foundPosition + seperator.length();

		foundPosition = line.find(seperator, startPosition);
	}
	int count = line.length() - startPosition;
	std::string token = line.substr(startPosition, count);
	tokens.push_back(token);
	return tokens;
}


struct qfloatDataInput {
	int baseSource = 0;
	int baseDestination = 0;
	std::string data = "";
};

/*
readData function
@param string source is the string source in file input
@functional: convert the string source to qfloatDataInput
*/
qfloatDataInput readData(std::string source) {
	qfloatDataInput result;
	result.baseSource = 0;
	result.baseDestination = 0;
	result.data = "";
	std::vector<std::string> parseData = parse_string_by(source, " ");
	result.baseSource = std::atoi(parseData[0].c_str());
	result.baseDestination = std::atoi(parseData[1].c_str());
	result.data = parseData[2];
	return result;
}

/*
processing function
@param string inputFilePath is the path of file input
@param string outputFilePath is the path of file output
*/
void processing(std::string inputFilePath, std::string outputFilePath) {
	std::ifstream inputStreamFile;
	std::ofstream outputStreamFile;
	inputStreamFile.open(inputFilePath);
	if (inputStreamFile.fail()) {
		std::cout << "The path file doesn't exist." << std::endl;
		return;
	}
	outputStreamFile.open(outputFilePath);
	if (outputStreamFile.fail()) {
		std::cout << "The path file doesn't exist." << std::endl;
		return;
	}
	while (!inputStreamFile.eof()) {
		std::string temp = "";
		std::getline(inputStreamFile, temp);
		qfloatDataInput _data = readData(temp);
		_qfloat128_ qfloat;
		if (_data.baseSource == 2) {
			_data.data = qfloat.decToBin();
		}
		if (_data.baseSource == 10) {
			qfloat.scanQfloat(_data.data);
		}
		if (_data.baseDestination == 2) {
			outputStreamFile << qfloat.decToBin() << std::endl;
		}
		if (_data.baseDestination == 10) {
			outputStreamFile << qfloat.printQfloat() << std::endl;
		}
	}
	inputStreamFile.close();
	outputStreamFile.close();
}
