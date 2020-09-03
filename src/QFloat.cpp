#include "QFloat.h"

// Private method
// Private method - binary128
std::string _qfloat128_::realMultiplyTwo(std::string real) {
	// Initialization
	int rememberVar = 0;
	int sum = 0;
	std::string result = "";
	// Multi
	for (int i = (int)real.length() - 1; i >= 0; i--) {
		if (real[i] == '.') {
			result = "." + result;
			continue;
		}
		sum = rememberVar + (real[i] - '0') * 2;
		result = char('0' + sum % 10) + result;
		rememberVar = sum / 10;
	}
	if (rememberVar > 0) {
		result = char(rememberVar + '0') + result;
	}
	int count = 0;
	for (int i = 0; i < (int)real.length(); i++) {
		if (real[i] == '0' || real[i] == '.') {
			count = count + 1;
		}
		else {
			break;
		}
	}
	if (count == (int)real.length()) {
		result = "0";
	}
	if (result[0] == '.') {
		result = '0' + result;
	}
	return result;
}

std::string _qfloat128_::realDivisionTwo(std::string real, bool isDivReal) {
	// Initialization
	int rememberVar = 0;
	int sum = 0;
	bool check = false;
	std::string result = "";
	// Division
	for (int i = 0; i < (int)real.length(); i++) {
		if (real[i] == '.') {
			result = result + ".";
			check = true;
			continue;
		}
		sum = rememberVar * 10 + real[i] - '0';
		result += '0' + sum / 2;
		rememberVar = sum % 2;
	}

	if (isDivReal && rememberVar > 0) {
		if (check) {
			result = result + "5";
		}
		else {
			result = result + ".5";
		}
	}

	while (result.length() > 1 && result[0] == '0') {
		result.erase(0, 1);
	}

	int count = 0;
	for (int i = 0; i < (int)real.length(); i++) {
		if (real[i] == '0' || real[i] == '.') {
			count = count + 1;
		}
		else {
			break;
		}
	}
	if (count == (int)real.length()) {
		result = "0";
	}
	if (result[0] == '.') {
		result = '0' + result;
	}
	return result;
}

void _qfloat128_::turn_on_bit_at(int k) {
	k = _QFLOAT_128_LENGTH - k - 1;
	int i = k / 32, j = 32 - k % 32 - 1;
	this->data[i] = (this->data[i] & ~(1U << j)) | (1 << j);
}

void _qfloat128_::turn_off_bit_at(int k) {
	k = _QFLOAT_128_LENGTH - k - 1;
	int i = k / 32, j = 32 - k % 32 - 1;
	this->data[i] = (this->data[i] & ~(1U << j)) | (0 << j);
}

int _qfloat128_::get_bit_at(int k) {
	k = _QFLOAT_128_LENGTH - k - 1;
	int i = k / 32, j = 32 - k % 32 - 1;
	return ((this->data[i] >> j) & 1U);
}

// Public method
// Public method - binary128
bool _qfloat128_::isSubNormal() {
	for (int i = _QFLOAT_128_BIT_EXPONENT; i < _QFLOAT_128_BIT_EXPONENT + _QFLOAT_128_BIT_FRACTION; i++) {
		if ()
	}
}

int _qfloat128_::getSign() { return get_bit_at(_QFLOAT_128_LENGTH - 1); }

bool _qfloat128_::isNaN() {
	unsigned int Sign = (this->data[0] >> 31) & 1;
	int Exponent = (this->data[0] >> 16) & ((1 << 15) - 1);
	if (Exponent == ((1 << 15) - 1)) {
		if (this->data[0] > (Exponent << 16) || this->data[1] != 0 || this->data[2] != 0 || this->data[3] != 0)
			return true;
	}
	return false;
}

bool _qfloat128_::isInf(bool& negative) {
	unsigned int sign = (this->data[0] >> 31) & 1;
	int exponent = (this->data[0] >> 16) & ((1 << 15) - 1);
	if (sign == 1) {
		negative = true; // Negative infinity
	}
	else if (sign == 0) {
		negative = false; // Positive infinity
	}
	if (exponent == ((1 << 15) - 1)) {
		if (this->data[0] == (exponent << 16) && this->data[1] == 0 && this->data[2] == 0 && this->data[3] == 0)
			return true;
	}
	return false;
}

bool _qfloat128_::isZero() {
	if (this->data[1] == 0 && this->data[2] == 0 && this->data[3] == 0 && (this->data[0] == 0 || this->data[0] == 1 << 31))
		return true;
	return false;
}

bool _qfloat128_::isDenormalized() {
	unsigned int sign = (this->data[0] >> 31) & 1;
	int exponent = (this->data[0] >> 16) & ((1 << 15) - 1);
	if (exponent == 0) {
		if (this->data[0] > 0 || this->data[1] != 0 || this->data[2] != 0 || this->data[3] != 0)
			return true;
	}
	return false;
}

void _qfloat128_::setNaN() {
	int temp = 1;
	int k = 0;
	this->data[k / 32] = (~(temp << (31 - k % 32))) & this->data[k / 32];
	// Set bit bias = overerflow = (1 << 14) - 1
	for (int i = 1; i <= 15; i++) {
		this->data[(i) / 32] = (temp << (31 - ((i) % 32))) | this->data[(i) / 32];
	}
	// Set fraction != 0
	this->data[(16) / 32] = (temp << (31 - ((16) % 32))) | this->data[(16) / 32];
}

void _qfloat128_::setInf(bool negative) {
	if (negative == true) {
		// Set bit sign = 0
		this->data[0 / 32] = (~(1 << (31 - 0 % 32))) & this->data[0 / 32];
	}
	else {
		// Set bit sign = 1
		this->data[(0) / 32] = (1 << (31 - (0 % 32))) | this->data[0 / 32];
	}
	// Set bit bias = overerflow = (1 << 14) - 1
	for (int i = 1; i <= 15; i++) {
		this->data[(i) / 32] = (1 << (31 - ((i) % 32))) | this->data[(i) / 32];
	}
}

void _qfloat128_::setZero() {
	this->data[0] = this->data[1] = this->data[2] = this->data[3];
}

void _qfloat128_::scanQfloat(std::string str) {
	// Initialization for sure qfloat equal to zero
	this->data[0] = this->data[1] = this->data[2] = this->data[3] = 0;
	// Sign - Exponent - Fraction
	char sign = 0;
	int exponent = 0;
	std::string integerPart = "";
	std::string decimalPart = "";
	std::string fraction = "";
	std::string fraction_01 = "";
	std::string fraction_02 = "";
	int bias = (1 << (_QFLOAT_128_BIT_EXPONENT - 1)) - 1;

	// Check sign
	bool checkIndexOfDot = false;
	if (str[0] == '+' || str[0] == '-') {
		sign = str[0];
		str.erase(0, 1);
	}
	else {
		sign = '+';
	}

	// Divide into two part - integerPart and decimalPart
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.') {
			checkIndexOfDot = true;
			integerPart = str.substr(0, i);
			decimalPart = str.substr((i + 1), ((int)str.length() - i - 1));
			break;
		}
	}

	// Case the input string decimal is the integer
	if (checkIndexOfDot == false) {
		integerPart = str;
		decimalPart = "0";
	}

	if (integerPart == "") {
		integerPart = "0";
	}

	if (decimalPart == "") {
		decimalPart = "0";
	}

	while (integerPart.length() > 1 && integerPart[0] == '0')
	{
		integerPart.erase(0, 1);
	}
	while (decimalPart.length() > 1 && decimalPart[decimalPart.length() - 1] == '0')
	{
		decimalPart.erase(decimalPart.length() - 1, 1);
	}

	if (integerPart == "0" && decimalPart == "0") {
		this->data[0] = this->data[1] = this->data[2] = this->data[3] = 0;
		return;
	}

	// Convert integerPart -> binary
	if (integerPart == "0")
	{
		fraction = "0";
	}
	else
	{
		while (integerPart != "0") {
			fraction_01 = char('0' + (integerPart[integerPart.length() - 1]) % 2) + fraction_01;
			integerPart = realDivisionTwo(integerPart, false);
		}
	}

	// Convert decimalPart -> binary
	decimalPart = "0." + decimalPart;
	int i = 0, j = 0;
	while (i < (bias + 1) && decimalPart != "0") {
		decimalPart = realMultiplyTwo(decimalPart);
		fraction_02 = fraction_02 + (char)('0' + (decimalPart[0] == '1'));
		if (decimalPart[0] == '1')
		{
			if (j < 128) {
				j++;
			}
		}
		decimalPart[0] = '0';
		i++;
	}

	if (fraction_01[0] == '1') {
		exponent = (int)fraction_01.length() - 1 + bias;
		fraction = fraction_01 + fraction_02;
		fraction.erase(0, 1);
	}
	else {
		fraction = fraction_02;
		for (int i = 0; i < fraction_02.length(); i++)
			if (fraction_02[i] == '1') {
				exponent = i;
				break;
			}
		if (exponent + 1 < bias) {
			fraction.erase(0, exponent + 1);
			exponent = -exponent - 1 + bias;
		}
		else {
			fraction.erase(0, bias - 1);
			exponent = 0;
		}
	}

	// Set bit in to Qfloat

	// Step 01: Set bit sign to qfloat
	if (sign == '-') {
		int temp = 1;
		this->data[(0) / 32] = (temp << (31 - ((0) % 32))) | this->data[(0) / 32];
	}

	// Step 02: Set bit exponent to qfloat
	for (int i = 1; i <= 15; i++) {
		if (((exponent >> (15 - i)) & 1) == 1) {
			int temp = 1;
			this->data[(i) / 32] = (temp << (31 - ((i) % 32))) | this->data[(i) / 32];
		}
	}

	// Step03: Set bit fraction to qfloat
	if (fraction.length() > 112) {
		if (fraction[112] == '1') {
			fraction = fraction.substr(0, 111);
			fraction = sum_bin(fraction, "1");
		}
	}
	for (int i = 0; i < (int)fraction.length(); i++) {
		if (fraction[i] == '1') {
			int temp = 1;
			this->data[(i + 16) / 32] = (temp << (31 - ((i + 16) % 32))) | this->data[(i + 16) / 32];
		}
		if (i == 111) {
			break;
		}
	}
}

std::string _qfloat128_::printQfloat() {
	bool negative;
	if (isZero()) {
		return "0";
	}
	else if (isNaN()) {
		return "NaN";
	}
	else if (isInf(negative)) {
		/*if (negative == true) {
			return "negative " + (string)inf;
		}
		else {
			return "positive " + (string)inf;
		}*/
		return (std::string)inf;
	}
	else if (isDenormalized()) {
		return denor;
	}
	// Initialization
	unsigned int sign = 0;
	int exponent = 0;
	int bias = (1 << (_QFLOAT_128_BIT_EXPONENT - 1)) - 1;
	std::string fraction = "";
	std::string fraction_01 = "";
	std::string fraction_02 = "";
	std::string result = "0";

	// Sign
	sign = (this->data[0] >> 31) & 1;
	// Exponent
	exponent = (this->data[0] >> 16) & ((1 << 15) - 1);

	if (exponent != 0) {
		exponent = exponent - bias;
		fraction_01 = "1";
	}
	else {
		fraction_01 = "1";
		exponent = 1 - bias;
	}
	// Fraction
	for (int i = 16; i < 32; i++)
		fraction_02 += char('0' + ((this->data[0] >> (31 - i)) & 1));
	for (int i = 1; i < 4; i++)
		for (int j = 0; j < 32; j++)
			fraction_02 += char('0' + ((this->data[i] >> (31 - j)) & 1));

	if (fraction_01 == "1") {
		fraction = fraction_01 + fraction_02;
		exponent = exponent + 1;
	}
	else {
		fraction = fraction_02;
	}

	for (int i = (int)fraction.length() - 1; i >= 0; i--) {
		if (fraction[i] == '1') {
			fraction.erase(i + 1, fraction.length() - i - 1);
			exponent = exponent - (i + 1);
			break;
		}
	}

	for (int i = 0; i < fraction.length(); i++) {
		int carried = 0;
		// mult by 2
		result = realMultiplyTwo(result);
		// add 1
		if (fraction[i] == '1') {
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
	if (exponent < 0)
	{
		for (int i = 0; i < abs(exponent); i++)
		{
			result = realDivisionTwo(result, true);
		}
	}

	if (exponent > 0)
	{
		for (int i = 0; i < exponent; i++)
		{
			result = realMultiplyTwo(result);
		}
	}

	if (result[0] == '.')
		result = '0' + result;

	if (sign == 1)
		result = '-' + result;
	// Rrounded
	// Step 1: find index of the dot
	int dot = -1;
	for (int i = 0; i < result.length(); i++) {
		if (result[i] == '.') {
			dot = i;
			break;
		}
	}
	// Step 02: find some where has start the duplicate
	int index = 0;
	for (int i = 0; i < result.length(); i++) {
		int count = 0;
		for (int j = i + 1; j < result.length(); j++) {
			if (result[j] == result[i]) {
				count++;
			}
			else {
				break;
			}
		}
		if (count > 20) {
			index = i;
			break;
		}
		if (count == 1) {
			count = 0;
		}
	}
	// Step 3: round 
	return _round(result, index - dot - 1);
}

_qfloat128_ _qfloat128_::binToDec(std::string bit) {
	// Default setup for sure that qfloat equal to zero
	this->data[0] = 0;
	this->data[1] = 0;
	this->data[2] = 0;
	this->data[3] = 0;
	// Set bit from string bit to Qfloat
	for (int i = 0; i < min((int)bit.length(), 128); i++) {
		if (bit[i] == '1') {
			int temp = 1;
			this->data[i / 32] = (temp << (31 - (i % 32))) | this->data[i / 32];
		}
	}

	return *this;
}

std::string _qfloat128_::decToBin() {
	// Init string result bin = ""
	std::string bin = "";
	// Get bit and add to string
	for (int i = 0; i < 4; i++) {
		for (int j = sizeof(int) * 8 - 1; j >= 0; j--) {
			bin = bin + char('0' + ((this->data[i] >> j) & 1));
		}
	}
	return bin;
}

_qfloat128_& _qfloat128_::operator+(_qfloat128_& qfloat) {
	_qfloat128_ result;
	result.setZero();
	if (this->isZero() && !qfloat.isZero()) { return qfloat; }
	if (!this->isZero() && qfloat.isZero()) { return *this;  }
	if (this->isZero() && qfloat.isZero()) { return result;  }


	return result;
}

_qfloat128_& _qfloat128_::operator-(_qfloat128_& qfloat) {
	_qfloat128_ result;
	result.setZero();

	return result;
}

_qfloat128_& _qfloat128_::operator*(_qfloat128_& qfloat) {
	_qfloat128_ result;
	result.setZero();

	return result;
}

_qfloat128_& _qfloat128_::operator/(_qfloat128_& qfloat) {
	_qfloat128_ result;
	result.setZero();

	return result;
}