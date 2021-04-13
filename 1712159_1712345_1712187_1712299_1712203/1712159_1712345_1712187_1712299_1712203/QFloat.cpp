#include "QFloat.h"


//------------------------------------------------------
/* Constructors */
QFloat::QFloat()
{
	a[0] = a[1] = a[2] = a[3] = 0;
}

QFloat::QFloat(string value)
{
	a[0] = a[1] = a[2] = a[3] = 0;
	/* kiểm tra tính hợp lệ dữ liệu vào */
	if (!Utils::CheckStringForFloatType(value))
	{
		return;
	}

	/* tách phần nguyên và phần thập phân */
	string N = "0", TP = "0";
	int separator = -1;
	separator = (int)value.find_first_of('.');
	if (separator != -1)
	{
		N = value.substr(0, separator);
		TP = value.substr(separator + 1);
	}
	else
	{
		N = value;
	}

	/* tách dấu */
	bool isAm = false;
	if (N[0] == '-')
	{
		N = N.erase(0, 1);
		isAm = true;
	}

	/* tách bỏ các số 0 dư thừa */
	int count = 0;
	for (int i = 0; i < (int)N.length(); i++)
	{
		if (N[i] == '0')
			count++;
		else break;
	}
	N = N.erase(0, count);
	count = 0;
	for (int i = (int)TP.length() - 1; i >= 0; i--)
	{
		if (TP[i] == '0')
			count++;
		else break;
	}
	TP = TP.erase((int)TP.length() - count);

	// Nếu là số 0 ta sẽ dừng
	if (N == "" && TP == "")
	{
		a[0] = a[1] = a[2] = a[3] = 0;
	}

	/* phát sinh mảng phụ lưu các giá trị bit */
	bool *phan_nguyen = new bool[QFLOAT_BIT];
	bool *phan_tp = new bool[QFLOAT_BIT];
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		phan_nguyen[i] = 0;
		phan_tp[i] = 0;
	}

	/* đồi phần nguyên sang nhị phân*/
	int k = QFLOAT_BIT - 1;
	string temp = N;
	while (temp != "" && k >= 0)
	{
		int n = temp.length();
		int item = temp[n - 1] + 48;
		phan_nguyen[k--] = item % 2;
		temp = Utils::StringChia2(temp);
	}

	/* đổi phần thập phân sang nhị phân */

	string temp1 = TP;
	temp1 = "1" + TP;
	int n = (int)temp1.length();
	for (int i = n; i < 129; i++)
		temp1 += "0";
	int h = 0;
	string check = "1";
	for (int i = 0; i < 128; i++) check += "0";
	while (temp1 != check && h != (QFLOAT_BIT - 1))
	{
		temp1 = Utils::StringNhan2(temp1);
		if (temp1[0] == '3')
		{
			phan_tp[h] = 1;
			temp1[0] = '1';
		}
		else
		{
			phan_tp[h] = 0;
			temp1[0] = '1';
		}
		h++;
	}

	/* Chuyển sang floating point */

	/* Tìm vị trí số 1 */
	int index = -1;
	bool dichtrai = false;
	if (QInt::BinToDec(phan_nguyen) != QInt("0"))
	{
		dichtrai = true;
		for (index; index < QFLOAT_BIT; index++)
		{
			if (phan_nguyen[index] == 1)
				break;
		}
	}
	else
	{
		for (index; index < QFLOAT_BIT; index++)
		{
			if (phan_tp[index] == 1)
				break;
		}
	}


	/*  tìm các bit cần thiết */
	bool *muE = new bool[15];
	bool sign;
	bool * signifi = new bool[112];
	int E; // số mũ
	if (dichtrai)
	{
		E = QFLOAT_BIT - index - 1;
	}
	else
	{
		E = -(index + 1);
	}
	E = E + (int)pow(2, 14) - 1;

	//---------------------------------------
	if (isAm)
		sign = 1;
	else
		sign = 0;
	//-----------------------------------------
	for (int i = 0; i < 15; i++)
	{
		muE[i] = 0;
	}
	int ie = 14;
	int e = E;
	while (e != 0)
	{
		muE[ie--] = e % 2;
		e = e / 2;
	}

	//-------------------------------------------
	for (int i = 0; i < 112; i++)
		signifi[i] = 0;
	if (dichtrai)
	{
		int is = 0;
		for (int i = index + 1; i < QFLOAT_BIT; i++)
		{
			signifi[is++] = phan_nguyen[i];
			if (is == 112) break;
		}
		for (int i = 0; i < QFLOAT_BIT; i++)
		{
			signifi[is++] = phan_tp[i];
			if (is == 112)
			{
				if (phan_tp[i + 1] == 1)
					signifi[is - 1] = 1;
				break;
			}
		}
	}
	else
	{
		int is = 0;
		for (int i = index + 1; i < QFLOAT_BIT; i++)
		{
			signifi[is++] = phan_tp[i];
			if (is == 112) break;
		}
	}


	/* lưu vào Qfloat */
	bool *b = new bool[128];
	int bb = 1;
	b[0] = sign;
	for (int i = 0; i < 15; i++)
		b[bb++] = muE[i];
	for (int i = 0; i < 112; i++)
		b[bb++] = signifi[i];

	/* sao chép bit vào Qfloat */
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		if (b[i] == 1)
		{
			int j = 31 - i % 32;
			a[i / 32] = a[i / 32] | (1 << j);
		}
	}
	delete[] phan_nguyen;
	delete[] phan_tp;
	delete[] muE;
	delete[] signifi;
	delete[] b;
}

//-----------------------------------------------------
/* Toán tử nhập xuất */
ostream& operator<<(ostream &outDev, QFloat x)
{
	// th đặc biệt
	if (x.a[0] == 0 && x.a[1] == 0 && x.a[2] == 0 && x.a[3] == 0)
	{
		outDev << "0.0";
		return outDev;
	}
	/* Phát sinh mảng lưu các bit */
	bool *bit = new bool[QFLOAT_BIT];
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		bit[i] = (x.a[i / 32] >> (32 - (i % 32) - 1)) & 1;
	}


	/* tách ra Sing,E,Signifi */
	bool sign = bit[0];
	bool *E = new bool[15];
	bool *signifi = new bool[112];
	int k = 1;
	for (int i = 0; i < 15; i++)
		E[i] = bit[k++];
	for (int i = 0; i < 112; i++)
		signifi[i] = bit[k++];

	// tính e
	int e = 0;
	for (int i = 0; i < 15; i++)
	{
		e += E[i] * (int)pow(2, 15 - i - 1);
	}
	e = e - ((int)pow(2, 14) - 1);

	/* bit lưu phần nguyên, phần âm*/
	bool *phan_nguyen = new bool[QFLOAT_BIT];
	bool *phan_am = new bool[QFLOAT_BIT];
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		phan_nguyen[i] = 0;
		phan_am[i] = 0;
	}

	/* phát sinh mảng phụ */
	// qui ước dấu . nằm sau index
	int index = QFLOAT_BIT - 1;
	bool *temp = new bool[QFLOAT_BIT * 2];
	for (int i = 0; i < QFLOAT_BIT * 2; i++)
		temp[i] = 0;
	temp[QFLOAT_BIT - 1] = 1;
	for (int i = 0; i < 112; i++)
		temp[QFLOAT_BIT + i] = signifi[i];
	index = index + e;

	int kk = index;
	for (int i = QFLOAT_BIT - 1; i >= 0; i--)
	{
		phan_nguyen[i] = temp[kk--];
		if (kk < 0) break;
	}

	int h = index + 1;
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		phan_am[i] = temp[h++];
		if (h == 2 * QFLOAT_BIT) break;
	}

	string N = "0";
	string TP = "0";

	// phần nguyên
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		if (phan_nguyen[i] == 1)
		{
			N = Utils::CongStringTheoInt(N, Utils::MuCua2(QFLOAT_BIT - i - 1));
		}
	}

	// phần thập phân
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		if (phan_am[i] == 1)
		{
			//cout << "das" << endl;
			string a; a.resize(129); a[0] = '1';
			for (int j = 1; j < 129; j++) a[j] = '0';
			for (int j = 1; j <= i + 1; j++)
			{
				a = Utils::StringChia2(a);
			}
			TP = Utils::CongStringTheoInt(TP, a);
		}
	}
	int count = 0;
	int n = (int)TP.length();
	for (int i = n - 1; i >= 0; i--)
	{
		if (TP[i] == '0') count++;
		else break;
	}
	TP = TP.erase(n - count);
	if ((int)TP.length() > 10)
		TP = TP.substr(0, 10);

	if (TP == "") TP = "0";
	string result = N + "." + TP;
	if (sign == 1)
		result = "-" + result;

	outDev << result << endl;

	delete[] phan_nguyen;
	delete[] phan_am;
	delete[] E;
	delete[] signifi;
	delete[] temp;

	return outDev;
}

istream& operator >> (istream &inDev, QFloat &x)
{
	string value;

	/* kiểm tra tính hợp lệ dữ liệu vào */
	while (1)
	{
		getline(inDev, value);
		if (!Utils::CheckStringForFloatType(value))
			cout << "Type of data input is error, try again!" << endl;
		else break;
	}

	x.a[0] = x.a[1] = x.a[2] = x.a[3] = 0;


	/* tách phần nguyên và phần thập phân */
	string N = "0", TP = "0";
	int separator = -1;
	separator = (int)value.find_first_of('.');
	if (separator != -1)
	{
		N = value.substr(0, separator);
		TP = value.substr(separator + 1);
	}
	else
	{
		N = value;
	}

	/* tách dấu */
	bool isAm = false;
	if (N[0] == '-')
	{
		N = N.erase(0, 1);
		isAm = true;
	}

	/* tách bỏ các số 0 dư thừa */
	int count = 0;
	for (int i = 0; i < (int)N.length(); i++)
	{
		if (N[i] == '0')
			count++;
		else break;
	}
	N = N.erase(0, count);
	count = 0;
	for (int i = (int)TP.length() - 1; i >= 0; i--)
	{
		if (TP[i] == '0')
			count++;
		else break;
	}
	TP = TP.erase((int)TP.length() - count);

	// Nếu là số 0 ta sẽ dừng
	if (N == "" && TP == "")
	{
		x.a[0] = x.a[1] = x.a[2] = x.a[3] = 0;
	}

	/* phát sinh mảng phụ lưu các giá trị bit */
	bool *phan_nguyen = new bool[QFLOAT_BIT];
	bool *phan_tp = new bool[QFLOAT_BIT];
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		phan_nguyen[i] = 0;
		phan_tp[i] = 0;
	}

	/* đồi phần nguyên sang nhị phân*/
	int k = QFLOAT_BIT - 1;
	string temp = N;
	while (temp != "" && k >= 0)
	{
		int n = temp.length();
		int item = temp[n - 1] + 48;
		phan_nguyen[k--] = item % 2;
		temp = Utils::StringChia2(temp);
	}

	/* đổi phần thập phân sang nhị phân */

	string temp1 = TP;
	temp1 = "1" + TP;
	int n = (int)temp1.length();
	for (int i = n; i < 129; i++)
		temp1 += "0";
	int h = 0;
	string check = "1";
	for (int i = 0; i < 128; i++) check += "0";
	while (temp1 != check && h != (QFLOAT_BIT - 1))
	{
		temp1 = Utils::StringNhan2(temp1);
		if (temp1[0] == '3')
		{
			phan_tp[h] = 1;
			temp1[0] = '1';
		}
		else
		{
			phan_tp[h] = 0;
			temp1[0] = '1';
		}
		h++;
	}

	/* Chuyển sang floating point */

	/* Tìm vị trí số 1 */
	int index = -1;
	bool dichtrai = false;
	if (QInt::BinToDec(phan_nguyen) != QInt("0"))
	{
		dichtrai = true;
		for (index; index < QFLOAT_BIT; index++)
		{
			if (phan_nguyen[index] == 1)
				break;
		}
	}
	else
	{
		for (index; index < QFLOAT_BIT; index++)
		{
			if (phan_tp[index] == 1)
				break;
		}
	}


	/*  tìm các bit cần thiết */
	bool *muE = new bool[15];
	bool sign;
	bool * signifi = new bool[112];
	int E; // số mũ
	if (dichtrai)
	{
		E = QFLOAT_BIT - index - 1;
	}
	else
	{
		E = -(index + 1);
	}
	E = E + (int)pow(2, 14) - 1;

	//---------------------------------------
	if (isAm)
		sign = 1;
	else
		sign = 0;
	//-----------------------------------------
	for (int i = 0; i < 15; i++)
	{
		muE[i] = 0;
	}
	int ie = 14;
	int e = E;
	while (e != 0)
	{
		muE[ie--] = e % 2;
		e = e / 2;
	}

	//-------------------------------------------
	for (int i = 0; i < 112; i++)
		signifi[i] = 0;
	if (dichtrai)
	{
		int is = 0;
		for (int i = index + 1; i < QFLOAT_BIT; i++)
		{
			signifi[is++] = phan_nguyen[i];
			if (is == 112) break;
		}
		for (int i = 0; i < QFLOAT_BIT; i++)
		{
			signifi[is++] = phan_tp[i];
			if (is == 112)
			{
				if (phan_tp[i + 1] == 1)
					signifi[is - 1] = 1;
				break;
			}
		}
	}
	else
	{
		int is = 0;
		for (int i = index + 1; i < QFLOAT_BIT; i++)
		{
			signifi[is++] = phan_tp[i];
			if (is == 112) break;
		}
	}


	/* lưu vào Qfloat */
	bool *b = new bool[128];
	int bb = 1;
	b[0] = sign;
	for (int i = 0; i < 15; i++)
		b[bb++] = muE[i];
	for (int i = 0; i < 112; i++)
		b[bb++] = signifi[i];

	/* sao chép bit vào Qfloat */
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		if (b[i] == 1)
		{
			int j = 31 - i % 32;
			x.a[i / 32] = x.a[i / 32] | (1 << j);
		}
	}

	delete[] phan_nguyen;
	delete[] phan_tp;
	delete[] muE;
	delete[] signifi;
	delete[] b;

	return inDev;
}

//-------------------------------------------------------
/* Chuyển đổi cơ số */
bool* QFloat::DecToBin(QFloat x)
{
	/* Phát sinh mảng lưu các bit */
	bool *bit = new bool[QFLOAT_BIT];
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		bit[i] = (x.a[i / 32] >> (32 - (i % 32) - 1)) & 1;
	}


	return bit;
}

QFloat QFloat::BinToDec(bool *bit)
{
	QFloat x;

	/* sao chép bit vào Qfloat */
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		if (bit[i] == 1)
		{
			int j = 31 - i % 32;
			x.a[i / 32] = x.a[i / 32] | (1 << j);
		}
	}

	return x;
}


/*  To String  */
string QFloat::ToString()
{
	string result = "";

	// th đặc biệt
	if (a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0)
	{
		result = "0.0";
		return result;
	}
	/* Phát sinh mảng lưu các bit */
	bool *bit = new bool[QFLOAT_BIT];
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		bit[i] = (a[i / 32] >> (32 - (i % 32) - 1)) & 1;
	}


	/* tách ra Sing,E,Signifi */
	bool sign = bit[0];
	bool *E = new bool[15];
	bool *signifi = new bool[112];
	int k = 1;
	for (int i = 0; i < 15; i++)
		E[i] = bit[k++];
	for (int i = 0; i < 112; i++)
		signifi[i] = bit[k++];

	// tính e
	int e = 0;
	for (int i = 0; i < 15; i++)
	{
		e += E[i] * (int)pow(2, 15 - i - 1);
	}
	e = e - ((int)pow(2, 14) - 1);

	/* bit lưu phần nguyên, phần âm*/
	bool *phan_nguyen = new bool[QFLOAT_BIT];
	bool *phan_am = new bool[QFLOAT_BIT];
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		phan_nguyen[i] = 0;
		phan_am[i] = 0;
	}

	/* phát sinh mảng phụ */
	// qui ước dấu . nằm sau index
	int index = QFLOAT_BIT - 1;
	bool *temp = new bool[QFLOAT_BIT * 2];
	for (int i = 0; i < QFLOAT_BIT * 2; i++)
		temp[i] = 0;
	temp[QFLOAT_BIT - 1] = 1;
	for (int i = 0; i < 112; i++)
		temp[QFLOAT_BIT + i] = signifi[i];
	index = index + e;

	int kk = index;
	for (int i = QFLOAT_BIT - 1; i >= 0; i--)
	{
		phan_nguyen[i] = temp[kk--];
		if (kk < 0) break;
	}

	int h = index + 1;
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		phan_am[i] = temp[h++];
		if (h == 2 * QFLOAT_BIT) break;
	}

	string N = "0";
	string TP = "0";

	// phần nguyên
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		if (phan_nguyen[i] == 1)
		{
			N = Utils::CongStringTheoInt(N, Utils::MuCua2(QFLOAT_BIT - i - 1));
		}
	}

	// phần thập phân
	for (int i = 0; i < QFLOAT_BIT; i++)
	{
		if (phan_am[i] == 1)
		{
			string a; a.resize(129); a[0] = '1';
			for (int j = 1; j < 129; j++) a[j] = '0';
			for (int j = 1; j <= i + 1; j++)
			{
				a = Utils::StringChia2(a);
			}
			TP = Utils::CongStringTheoInt(TP, a);
		}
	}
	int count = 0;
	int n = (int)TP.length();
	for (int i = n - 1; i >= 0; i--)
	{
		if (TP[i] == '0') count++;
		else break;
	}
	TP = TP.erase(n - count);
	if ((int)TP.length() > 10)
		TP = TP.substr(0, 10);

	if (TP == "") TP = "0";
	result = N + "." + TP;
	if (sign == 1)
		result = "-" + result;

	return result;
}
