#pragma once
#include <iostream>
#include <string>
#include "Definition.h"
#include "Utils.h"
using namespace std;


class QInt
{
private:
	unsigned int a[4];
public:
	/* Constructors */
	QInt();
	QInt(string value);

	/* Hàm ToString */
	string ToString();

	/* Toán tử nhập xuất */
	friend istream& operator >> (istream &inDev, QInt &x);
	friend ostream& operator<<(ostream &outDev, QInt x);

	/* Chuyển đổi hệ số */
	static bool* DecToBin(QInt);
	static QInt BinToDec(bool*);
	static char* BinToHex(bool*);
	static char* DecToHex(QInt);
	static bool* HexToBin(char*);
	static QInt HexToDec(char*);

	/* Toán tử so sánh và gán */
	bool operator==(QInt other);
	bool operator!=(QInt other);
	bool operator>(QInt other);
	bool operator<(QInt other);
	bool operator>=(QInt other);
	bool operator<=(QInt other);
	QInt& operator=(QInt other);

	/* Toán tử dịch trái, dịch phải, xoay trái phải */
	QInt operator<<(unsigned int);
	QInt operator >> (unsigned int);
	QInt RotateLeft(unsigned int);
	QInt RotateRight(unsigned int);

	/* Các toán tử AND OR XOR NOT*/
	QInt operator&(QInt);
	QInt operator|(QInt);
	QInt operator^(QInt);
	QInt operator~();

	/* Các toán tử +,-,*,/ */
	QInt operator+(QInt);
	QInt operator-(QInt);
	QInt operator*(QInt);
	QInt operator/(QInt);
};

