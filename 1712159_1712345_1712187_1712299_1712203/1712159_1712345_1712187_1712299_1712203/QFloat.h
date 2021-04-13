#pragma once
#include "Utils.h"
#include "QInt.h"


class QFloat
{
	int a[4];
public:
	/* Constructors */
	QFloat();
	QFloat(string);

	/* Nhập xuất */
	friend istream& operator >> (istream&, QFloat&);
	friend ostream& operator<<(ostream&, QFloat);

	/* Chuyển đổi hệ số */
	static bool* DecToBin(QFloat);
	static QFloat BinToDec(bool*);

	/* ToString */
	string ToString();
};

