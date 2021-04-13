#include "QInt.h"


/* Constructors */
QInt::QInt()
{
	a[0] = a[1] = a[2] = a[3] = 0;
}

QInt::QInt(string value)
{
	a[0] = a[1] = a[2] = a[3] = 0;
	if (Utils::CheckStringForIntType(value))
	{
		bool isAm = false;
		if (value[0] == '-')
		{
			isAm = true;
			value = value.erase(0, 1);
		}

		/* Phát sinh mảng bool lưu giá trị các bit */
		bool *bit = new bool[QINT_BITS];
		for (int i = 0; i < QINT_BITS; i++)
		{
			bit[i] = 0;
		}
		int k = QINT_BITS - 1;
		string temp = value;
		while (temp != "")
		{
			int n = temp.length();
			int item = temp[n - 1] + 48;
			bit[k--] = item % 2;
			temp = Utils::StringChia2(temp);
		}

		if (isAm)
		{
			bit = Utils::SoBu2(bit);
		}

		/* Bật các bit tương ứng ở QInt */
		for (int i = 0; i < QINT_BITS; i++)
		{
			if (bit[i] == 1)
			{
				int j = 31 - i % 32;
				a[i / 32] = a[i / 32] | (1 << j);
			}
		}
	}

}

//-----------------------------------------------------
/*  Hàm ToString  */
string QInt::ToString()
{
	/* phát sinh biến kiểm tra âm - dương */
	bool check_am = false;

	/* Phát sinh mảng lưu các bit */
	bool *bit = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++)
	{
		bit[i] = (a[i / 32] >> (32 - (i % 32) - 1)) & 1;
	}

	if (bit[0] == 1)
	{
		check_am = true;
		bit = Utils::SoBu2(bit);
	}


	string result = "0";
	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit[i] == 1)
		{
			result = Utils::CongStringTheoInt(result, Utils::MuCua2(QINT_BITS - i - 1));
		}
	}
	if (check_am)
	{
		result = "-" + result;
	}
	return result;
}

//--------------------------------------------------------
/* Toán tử nhập xuất */
istream& operator >> (istream& inDev, QInt &x)
{
	x.a[0] = x.a[1] = x.a[2] = x.a[3] = 0;
	/* chúng ta sẽ nhập dữ liệu vào 1 chuỗi lưu tạm */
	string value;
	while (1)
	{
		getline(cin, value);
		if (Utils::CheckStringForIntType(value))
			break;
		else
			cout << "Type input is error, input again!" << endl;
	}

	/* phát sinh biến kiểm tra âm dương */
	bool isAm = false;
	if (value[0] == '-')
	{
		isAm = true;
		value = value.erase(0, 1);
	}

	/* Phát sinh mảng bool lưu giá trị các bit */
	bool *bit = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++)
	{
		bit[i] = 0;
	}
	int k = QINT_BITS - 1;
	string temp = value;
	while (temp != "")
	{
		int n = temp.length();
		int item = temp[n - 1] + 48;
		bit[k--] = item % 2;
		temp = Utils::StringChia2(temp);
	}

	if (isAm)
	{
		bit = Utils::SoBu2(bit);
	}

	/* Bật các bit tương ứng ở QInt */
	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit[i] == 1)
		{
			int j = 31 - i % 32;
			x.a[i / 32] = x.a[i / 32] | (1 << j);
		}
	}
	delete[] bit;
	return inDev;
}

ostream& operator<<(ostream &outDev, QInt x)
{
	/* phát sinh biến kiểm tra âm - dương */
	bool check_am = false;

	/* Phát sinh mảng lưu các bit */
	bool *bit = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++)
	{
		bit[i] = (x.a[i / 32] >> (32 - (i % 32) - 1)) & 1;
	}

	if (bit[0] == 1)
	{
		check_am = true;
		bit = Utils::SoBu2(bit);
	}


	string result = "0";
	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit[i] == 1)
		{
			result = Utils::CongStringTheoInt(result, Utils::MuCua2(QINT_BITS - i - 1));
		}
	}
	if (check_am)
	{
		result = "-" + result;
	}
	outDev << result;
	delete[] bit;
	return outDev;
}

//---------------------------------------------------------------------------
/*  Chuyển đổi hệ số */

bool* QInt::DecToBin(QInt x)
{
	bool *bit = new bool[QINT_BITS];

	for (int i = 0; i < QINT_BITS; i++)
	{
		bit[i] = (x.a[i / 32] >> (32 - (i % 32) - 1)) & 1;
	}
	return bit;
}

QInt QInt::BinToDec(bool *bit)
{
	/* Để đảm bảo độ chu toàn của thuật toán. thì ở đây dãy bit nhận vào chắc chắn phải có 128 pt */
	QInt x;
	x.a[0] = x.a[1] = x.a[2] = x.a[3] = 0;
	/* Bật các bit tương ứng ở QInt */
	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit[i] == 1)
		{
			int j = 31 - i % 32;
			x.a[i / 32] = x.a[i / 32] | (1 << j);
		}
	}
	return x;
}

char* QInt::BinToHex(bool *bit)
{
	/* phát sinh mảng char lưu hexa */
	int n = QINT_BITS / 4;
	char *hex = new char[n];
	for (int i = 0; i<n; i++)
	{
		int item = 0;
		int x = 3;
		for (int k = i * 4; k < i * 4 + 4; k++)
		{
			item += bit[k] * (int)pow(2, x--);
		}
		/* là số 0-9 */
		if (item >= 0 && item <= 9)
			hex[i] = char(item + 48);
		else /* từ A-F */
			hex[i] = char(item + 55);
	}
	return hex;
}

char* QInt::DecToHex(QInt x)
{
	bool *bit = QInt::DecToBin(x);
	char *hex = QInt::BinToHex(bit);
	return hex;

}

bool* QInt::HexToBin(char *hex)
{
	bool *bit = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++) bit[i] = 0;

	int h = QINT_BITS - 1;
	for (int i = QINT_BITS / 4 - 1; i >= 0; i--)
	{
		int temp;
		if (hex[i] >= '0' && hex[i] <= '9')
			temp = hex[i] - 48;
		else temp = hex[i] - 55; // case A-F

		int k = h;
		while (temp != 0)
		{
			bit[k] = temp % 2;
			temp /= 2;
			k--;
		}
		/* mỗi lần lấy 4 bit */
		h -= 4;
	}

	return bit;
}

QInt QInt::HexToDec(char *hex)
{
	QInt result;
	bool *bit = QInt::HexToBin(hex);
	result = QInt::BinToDec(bit);
	return result;
}

//--------------------------------------------------------------------------------
/* Toán tử so sánh & gán */

bool QInt::operator==(QInt other)
{
	bool *bit_a = QInt::DecToBin(*this);
	bool *bit_b = QInt::DecToBin(other);

	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit_a[i] != bit_b[i])
			return false;
	}
	return true;
}

bool QInt::operator!=(QInt other)
{
	return !(*this == other);
}

bool QInt::operator>(QInt other)
{
	bool *bit_a = QInt::DecToBin(*this);
	bool *bit_b = QInt::DecToBin(other);

	/* Đầu tiên xét a,b có bằng nhau không */
	if (*this == other)
		return false;

	/* Sau đó là ta xét dấu */
	// a âm, b dương
	if (bit_a[0] == 1 && bit_b[0] == 0)
	{
		return false;
	}
	// a dương, b âm
	else if (bit_a[0] == 0 && bit_b[0] == 1)
	{
		return true;
	}
	// cả 2 cùng dương
	else if (bit_a[0] == 0 && bit_b[0] == 0)
	{
		for (int i = 1; i < QINT_BITS; i++)
		{
			if (bit_a[i] < bit_b[i])
				return false;
			else if (bit_a[i] > bit_b[i])
				return true;
		}
	}
	// cả 2 cùng âm
	else
	{
		/* chuyển về số dương */
		bool *a = Utils::SoBu2(bit_a);
		bool *b = Utils::SoBu2(bit_b);
		bool a_lonhon = false;
		for (int i = 1; i < QINT_BITS; i++)
		{
			if (a[i] < b[i])
			{
				a_lonhon = false;
				break;
			}
			else if (a[i] > b[i])
			{
				a_lonhon = true;
				break;
			}
		}
		if (a_lonhon)
		{
			return false;
		}
	}
	return true;
}

bool QInt::operator<(QInt other)
{
	return !(*this > other || *this == other);
}

bool QInt::operator>=(QInt other)
{
	return (*this > other || *this == other);
}

bool QInt::operator<=(QInt other)
{
	return (*this < other || *this == other);
}

QInt& QInt::operator=(QInt other)
{
	a[0] = a[1] = a[2] = a[3] = 0;
	for (int i = 0; i < 4; i++)
	{
		this->a[i] = other.a[i];
	}
	return *this;
}

//-------------------------------------------------------------
/* Các toán tử AND OR XOR NOT */
QInt QInt::operator&(QInt x)
{
	QInt result;
	bool *bit_a = QInt::DecToBin(*this);
	bool *bit_b = QInt::DecToBin(x);
	bool *item = new bool[QINT_BITS];

	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit_a[i] == 1 && bit_b[i] == 1)
		{
			item[i] = 1;
		}
		else
		{
			item[i] = 0;
		}
	}
	result = QInt::BinToDec(item);
	delete[] bit_a;
	delete[] bit_b;
	delete[] item;
	return result;
}

QInt QInt::operator|(QInt x)
{
	QInt result;
	bool *bit_a = QInt::DecToBin(*this);
	bool *bit_b = QInt::DecToBin(x);
	bool *item = new bool[QINT_BITS];

	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit_a[i] == 1 || bit_b[i] == 1)
		{
			item[i] = 1;
		}
		else
		{
			item[i] = 0;
		}
	}
	result = QInt::BinToDec(item);
	delete[] bit_a;
	delete[] bit_b;
	delete[] item;
	return result;
}

QInt QInt::operator^(QInt x)
{
	QInt result;
	bool *bit_a = QInt::DecToBin(*this);
	bool *bit_b = QInt::DecToBin(x);
	bool *item = new bool[QINT_BITS];

	for (int i = 0; i < QINT_BITS; i++)
	{
		if (bit_a[i] == bit_b[i])

		{
			item[i] = 0;
		}
		else
		{
			item[i] = 1;
		}
	}
	result = QInt::BinToDec(item);
	delete[] bit_a;
	delete[] bit_b;
	delete[] item;
	return result;
}

QInt QInt::operator~()
{
	QInt result;
	bool *bit = QInt::DecToBin(*this);
	bool *item = new bool[QINT_BITS];

	for (int i = 0; i < QINT_BITS; i++)
	{
		item[i] = !bit[i];
	}
	result = QInt::BinToDec(item);
	delete[] bit;
	delete[] item;
	return result;
}

//-------------------------------------------------------------------
/* Các toán tử xoay trái phải,dịch trái phải */
QInt QInt::operator<<(unsigned int k)
{
	QInt result;
	bool *bit = QInt::DecToBin(*this);
	for (int i = 0; i < QINT_BITS - (int)k; i++)
	{
		bit[i] = bit[i + k];
	}
	for (int i = QINT_BITS - k; i < QINT_BITS; i++)
	{
		bit[i] = 0;
	}
	result = QInt::BinToDec(bit);
	delete[] bit;
	return result;
}

QInt QInt::operator >> (unsigned int k)
{
	QInt result;
	bool *bit = QInt::DecToBin(*this);
	for (int i = QINT_BITS - 1; i >= (int)k; i--)
	{
		bit[i] = bit[i - k];
	}
	for (int i = 0; i < (int)k; i++)
	{
		bit[i] = 0;
	}
	result = QInt::BinToDec(bit);
	delete[] bit;
	return result;
}

QInt QInt::RotateLeft(unsigned int k)
{
	k = k % QINT_BITS;
	QInt result;
	QInt a = *this << k;
	QInt b = *this >> (QINT_BITS - k);
	result = a | b;
	return result;
}

QInt QInt::RotateRight(unsigned int k)
{
	k = k % QINT_BITS;
	QInt result;
	QInt a = *this >> k;
	QInt b = *this << (QINT_BITS - k);
	result = a | b;
	return result;
}

//---------------------------------------------------------------------
/* Các toán tử +,-,*,/ */
QInt QInt::operator+(QInt x)
{
	QInt result;
	bool *a = QInt::DecToBin(*this);
	bool *b = QInt::DecToBin(x);
	bool *bit = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++)
	{
		bit[i] = 0;
	}
	int mod = 0;

	for (int i = QINT_BITS - 1; i >= 0; i--)
	{
		bit[i] = (a[i] + b[i] + mod) % 2;
		mod = (a[i] + b[i] + mod) / 2;
	}
	result = QInt::BinToDec(bit);
	delete[] a;
	delete[] b;
	delete[] bit;
	return result;
}

QInt QInt::operator-(QInt x)
{
	QInt result;
	bool *a = QInt::DecToBin(*this);
	bool *b = Utils::SoBu2(QInt::DecToBin(x));
	bool *bit = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++)
	{
		bit[i] = 0;
	}
	int mod = 0;

	for (int i = QINT_BITS - 1; i >= 0; i--)
	{
		bit[i] = (a[i] + b[i] + mod) % 2;
		mod = (a[i] + b[i] + mod) / 2;
	}
	result = QInt::BinToDec(bit);
	delete[] a;
	delete[] b;
	delete[] bit;
	return result;
}

QInt QInt::operator*(QInt x)
{
	QInt result;
	/* khởi tạo các mạng cần thiết */
	bool *A = new bool[QINT_BITS];
	bool *Q = QInt::DecToBin(x);
	bool Q1 = 0;
	bool *M = QInt::DecToBin(*this);
	for (int i = 0; i < QINT_BITS; i++) A[i] = 0;
	int k = QINT_BITS;

	while (k > 0)
	{
		/* Xét 2 bit cuối Q Q1 */
		if (Q[QINT_BITS - 1] == 1 && Q1 == 0)
		{
			QInt temp = QInt::BinToDec(A) - QInt::BinToDec(M);
			A = QInt::DecToBin(temp);
		}
		else if (Q[QINT_BITS - 1] == 0 && Q1 == 1)
		{
			QInt temp = QInt::BinToDec(A) + QInt::BinToDec(M);
			A = QInt::DecToBin(temp);
		}
		/* Shift right [A,Q,Q1] */
		bool a = A[QINT_BITS - 1];
		bool b = Q[QINT_BITS - 1];
		for (int i = QINT_BITS - 1; i > 0; i--)
		{
			A[i] = A[i - 1];
		} A[0] = 0;
		for (int i = QINT_BITS - 1; i > 0; i--)
		{
			Q[i] = Q[i - 1];
		} Q[0] = a;
		Q1 = b;
		--k;
	}

	result = QInt::BinToDec(Q);
	delete[] A;
	delete[] Q;
	delete[] M;
	return result;
}

QInt QInt::operator/(QInt x)
{
	/* Q/M */
	if (x == QInt("0"))
	{
		return QInt("0");
	}

	bool *Q = QInt::DecToBin(*this);
	bool *M = QInt::DecToBin(x);
	bool *A = new bool[QINT_BITS];
	int k = QINT_BITS;
	bool Q_am = false, M_am = false;

	/* Xử lý âm dương */
	if (Q[0] == 1) // Q âm
	{
		Q = Utils::SoBu2(Q);
		Q_am = true;
	}
	if (M[0] == 1)// M âm
	{
		M = Utils::SoBu2(M);
		M_am = true;
	}

	/* xét trường hợp Q âm dương */
	if (Q[0] == 0) // Q dương
	{
		for (int i = 0; i < QINT_BITS; i++)
			A[i] = 0;
	}
	else // Q âm
	{
		for (int i = 0; i < QINT_BITS; i++)
			A[i] = 1;
	}

	/* thuật toán chia */
	while (k > 0)
	{
		/* shift left [A,Q] */
		bool bit_temp = Q[0];
		for (int i = 0; i < QINT_BITS - 1; i++)
		{
			A[i] = A[i + 1];
			Q[i] = Q[i + 1];
		}
		A[QINT_BITS - 1] = bit_temp;
		Q[QINT_BITS - 1] = 0;

		QInt temp = QInt::BinToDec(A);
		QInt item = QInt::BinToDec(A) - QInt::BinToDec(M);
		A = QInt::DecToBin(item);
		if (A[0] == 1) // A âm
		{
			Q[QINT_BITS - 1] = 0;
			A = QInt::DecToBin(temp);
		}
		else
		{
			Q[QINT_BITS - 1] = 1;
		}
		--k;
	}

	if ((Q_am && !M_am) || (!Q_am && M_am))
	{
		Q = Utils::SoBu2(Q);
	}

	QInt result = QInt::BinToDec(Q);
	delete[] Q;
	delete[] A;
	delete[] M;
	return result;
}