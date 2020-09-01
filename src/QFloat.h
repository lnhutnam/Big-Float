#pragma once
#include <string>

// constant
#define _QFLOAT_8_BIT_EXPONENT 4
#define _QFLOAT_8_BIT_FRACTION 3

#define _QFLOAT_16_BIT_EXPONENT 5
#define _QFLOAT_16_BIT_FRACTION 10

#define _QFLOAT_32_BIT_EXPONENT 11
#define _QFLOAT_32_BIT_FRACTION 52

#define _QFLOAT_80_BIT_EXPONENT 15
#define _QFLOAT_80_BIT_FRACTION 64

#define _QFLOAT_128_BIT_EXPONENT 15
#define _QFLOAT_128_BIT_FRACTION 112

#define of "Overflow"
#define uf "Underflow"
#define NaN "None a number"
#define inf "infinity"
#define denor "denormalized"


// Structure
struct _qfloat8_ {
	// sign: 1 bit - exponent: 4 bit - fraction: 3 bit
};

struct _qfloat16_ {
	// sign: 1 bit - exponent: 5 bit - fraction: 10 bit
};

struct _qfloat32_ {
	// sign: 1 bit - exponent: 8 bit - fraction: 23 bit
};

struct _qfloat64_ {
	// sign: 1 bit - exponent: 11 bit - fraction: 52 bit
};


struct _qfloat80_ {
	// sign: 1 bit - exponent: 15 bit - fraction: 64 bit
};

struct _qfloat128_ {
private:
	// sign: 1 bit - exponent: 15 bit - fraction: 112 bit
	int data[4] = { 0 };
private:
	std::string realMultiplyTwo(std::string real);
	std::string realDivisionTwo(std::string real, bool isDivReal);
	bool isNaN();
	bool isInf(bool& negative);
	bool isZero();
	bool isDenormalized();
	void setNaN();
	void setInf(bool negative);
	void setZero();
public:
	void scanQfloat(std::string str);
	std::string printQfloat();
	_qfloat128_ binToDec(std::string bit);
	std::string decToBin();

	// Overloading arithemic operator
	_qfloat128_& operator+(const _qfloat128_&);
	_qfloat128_& operator-(const _qfloat128_&);
	_qfloat128_& operator*(const _qfloat128_&);
	_qfloat128_& operator/(const _qfloat128_&);
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