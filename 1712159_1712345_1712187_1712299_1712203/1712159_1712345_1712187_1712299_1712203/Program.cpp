#include "Program.h"

//
/// QInt
/* Chuyển đổi cơ số */
string Program::ChuyenDoiQInt(string h1, string h2, string str)
{
	string result = "";
	/* Chuyển từ hệ 2 */
	if (h1 == "2")
	{
		/* phat sinh mang bit */
		bool *bit = new bool[QINT_BITS];
		for (int i = 0; i < QINT_BITS; i++) bit[i] = 0;
		int n = str.length() - 1;
		for (int i = QINT_BITS - 1; i >= 0; i--)
		{
			bit[i] = str[n] - 48;
			--n;
			if (n < 0) break;
		}
		/* sang hệ 10 */
		if (h2 == "10")
		{
			QInt temp = QInt::BinToDec(bit);
			result = temp.ToString();
		}
		/* sang hệ 16 */
		else if (h2 == "16")
		{
			char *c = QInt::BinToHex(bit);
			int index = 0;
			for (int i = 0; i < QINT_BITS / 4; i++)
			{
				if (c[i] != '0')
				{
					index = i;
					break;
				}
			}
			for (int i = index; i < QINT_BITS/4; i++)
			{
				result = result + c[i];
			}
			delete[] c;
		}
		delete[] bit;
	}
	/* Chuyển từ hệ 10 */
	else if (h1 == "10")
	{
		QInt x(str);
		/* sang hệ 2 */
		if (h2 == "2")
		{
			bool *bit = QInt::DecToBin(x);
			int index = 0;
			for (int i = 0; i < QINT_BITS; i++)
			{
				if (bit[i] != 0)
				{
					index = i;
					break;
				}
			}
			for (int i = index; i < QINT_BITS; i++)
			{
				result = result + (char)(bit[i] + 48);
			}
			delete[] bit;
		}
		/*  sang hệ 16 */
		else if (h2 == "16")
		{
			char *c = QInt::DecToHex(x);
			int index = 0;
			for (int i = 0; i < QINT_BITS / 4; i++)
			{
				if (c[i] != '0')
				{
					index = i;
					break;
				}
			}
			for (int i = index; i < QINT_BITS / 4; i++)
			{
				result = result + c[i];

			}
			delete[] c;
		}
	}
	/* Chuyển từ hệ 16 */
	else if (h1 == "16")
	{
		char *hex = new char[QINT_BITS/4];
		for (int i = 0; i < QINT_BITS / 4; i++) hex[i] = '0';
		int n = (int)str.length();
		int temp = n - 1;
		for (int i = QINT_BITS / 4 - 1; i >= 0; i--)
		{
			hex[i] = str[temp--];
			if (temp < 0) break;
		}
		/*  Chuyển sang 2  */
		if (h2 == "2")
		{
			bool *bit = QInt::HexToBin(hex);
			int index = 0;
			for (int i = 0; i < QINT_BITS; i++)
			{
				if (bit[i] != 0)
				{
					index = i;
					break;
				}
			}
			for (int i = index; i < QINT_BITS; i++) 
			{
				result = result + char(bit[i] + 48);
			}
			delete[] bit;
		}
		else if (h2 == "10")
		{
			QInt x = QInt::HexToDec(hex);
			result = x.ToString();
		}
		delete[] hex;
	}
	if (result == "") result = "0";
	return result;
}
/* Not QInt */
string Program::NotQInt(string h, string s)
{
	string result = "";
	/* case 16 */
	if (h == "16")
	{
		/* phat sinh mang char */
		char *hex = new char[QINT_BITS / 4];
		for (int i = 0; i < QINT_BITS / 4; i++) hex[i] = '0';
		int n = (int)s.length();
		int temp = n - 1;
		for (int i = QINT_BITS / 4 - 1; i >= 0; i--)
		{
			hex[i] = s[temp--];
			if (temp < 0) break;
		}
		/* change 2 */
		QInt item = QInt::HexToDec(hex);
		QInt item1 = ~item;
		char *x = QInt::DecToHex(item1);
		int index = 0;
		for (int i = 0; i < QINT_BITS / 4; i++)
		{
			if (x[i] != '0')
			{
				index = i;
				break;
			}
		}
		for (int i = index; i < QINT_BITS / 4; i++)
		{
			result = result + x[i];
		}
		delete[] hex;
		delete[] x;
	}
	/*  10  */
	else if (h == "10")
	{
		QInt item = QInt(s);
		QInt x = ~item;
		result = x.ToString();
	}
	/*  2  */
	else if (h == "2")
	{
		/* phat sinh mang bit */
		bool *bit = new bool[QINT_BITS];
		for (int i = 0; i, i < QINT_BITS; i++) bit[i] = 0;
		int t = (int)s.length() - 1;
		for (int i = QINT_BITS - 1; i >= 0; i--)
		{
			bit[i] = s[t--] - 48;
			if (t < 0)
			{
				break;
			}
		}
		/* change 10 */
		QInt x = QInt::BinToDec(bit);
		QInt item = ~x;
		bool *y = QInt::DecToBin(item);
		int index = 0;
		for (int i = 0; i < QINT_BITS; i++)
		{
			if (y[i] != 0)
			{
				index = i;
				break;
			}
		}
		for (int i = index; i < QINT_BITS; i++)
		{
			result = result + char(y[i] + 48);
		}
		delete[] bit;
		delete[] y;
	}
	return result;
}
/*  Tính toán  */
string Program::TinhToanQInt(string h, string s1, string toantu, string s2)
{
	string result = "";
	/* phát sinh các mảng lưu ở dạng nhị phân */
	bool *b1 = new bool[QINT_BITS],
		*b2 = new bool[QINT_BITS],
		*b = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++)
	{
		b1[i] = 0;
		b2[i] = 0;
		b[i] = 0;
	}
	
	// Chuyển tất cả sang nhị phân
	int type = 2;
	/* Nếu ở dạng nhị phân */
	if (h == "2")
	{
		type = 2;
		/* Chuyển chuỗi sang mảng nhị phân */
		int n1 = (int)s1.length() - 1;
		for (int i = QINT_BITS - 1; i >= 0; i--)
		{
			b1[i] = s1[n1--] - 48;
			if (n1 < 0) break;
		}
		int n2 = (int)s2.length() - 1;
		for (int i = QINT_BITS - 1; i >= 0; i--)
		{
			b2[i] = s2[n2--] - 48;
			if (n2 < 0) break;
		}
	}
	/* Nếu ở hs 10 */
	else if (h == "10")
	{
		type = 10;
		/*  Chuyển sang các mảng nhị phân */
		b1 = QInt::DecToBin(QInt(s1));
		b2 = QInt::DecToBin(QInt(s2));
	}
	/*  Nếu ở hs 16 */
	else if (h == "16")
	{
		type = 16;
		/* phát sinh các mảng h1,h2 lưu hexa */
		char *h1 = new char[QINT_BITS / 4];
		for (int i = 0; i < QINT_BITS / 4; i++) h1[i] = '0';
		int n1 = (int)s1.length() - 1;
		for (int i = QINT_BITS/4 - 1; i >= 0; i--)
		{
			h1[i] = s1[n1--];
			if (n1 < 0) break;
		}

		char *h2 = new char[QINT_BITS / 4];
		for (int i = 0; i < QINT_BITS / 4; i++) h2[i] = '0';
		int n2 = (int)s2.length() - 1;
		for (int i = QINT_BITS/4 - 1; i >= 0; i--)
		{
			h2[i] = s2[n2--];
			if (n2 < 0) break;
		}
		/* Chuyển sang nhị phân */
		b1 = QInt::HexToBin(h1);
		b2 = QInt::HexToBin(h2);
		delete[] h1;
		delete[] h2;
	}

	QInt t;
	QInt t1 = QInt::BinToDec(b1);
	QInt t2 = QInt::BinToDec(b2);

	// Tính toán
	/* Cộng */
	if (toantu == "+")
	{
		t = t1 + t2;
	}
	/* Trừ */
	else if (toantu == "-")
	{
		t = t1 - t2;
	}
	/* Nhân */
	else if (toantu == "*")
	{
		t = t1 * t2;
	}
	/* Chia */
	else if (toantu == "/")
	{
		t = t1 / t2;
	}
	/* AND */
	else if (toantu == "&") {
		t = t1 & t2;
	}
	/* XOR */
	else if (toantu == "^")
	{
		t = t1 ^ t2;
	}
	/* OR */
	else if (toantu == "|")
	{
		t = t1 | t2;
	}
	/* Dich trai */
	else if (toantu == "<<")
	{
		int item = stoi(s2);
		t = t1 << item;
	}
	/* Dich phai */
	else if (toantu == ">>")
	{
		int item = stoi(s2);
		t = t1 >> item;
	}
	/* Xoay trai */
	else if (toantu == "rol")
	{
		int item = stoi(s2);

		t = t1.RotateLeft(item);
	}
	/* Xoay phai */
	else if (toantu == "ror")
	{
		int item = stoi(s2);
		t = t1.RotateRight(item);
	}
	/* == */
	else if (toantu == "==")
	{
		if (t1 == t2)
			result = "true";
		else
			result = "false";
		return result;
	}
	/* != */
	else if (toantu == "!=")
	{
		if (t1 != t2)
			result = "true";
		else
			result = "false";
		return result;
	}
	/* > */
	else if (toantu == ">")
	{
		if (t1 > t2)
			result = "true";
		else
			result = "false";
		return result;
	}
	/* < */
	else if (toantu == "<")
	{
		if (t1 < t2)
			result = "true";
		else
			result = "false";
		return result;
	}
	/* >= */
	else if (toantu == ">=")
	{
		if (t1 >= t2)
			result = "true";
		else
			result = "false";
		return result;
	}
	/* <= */
	else if (toantu == "<=")
	{
		if (t1 <= t2)
			result = "true";
		else
			result = "false";
		return result;
	}



	/*  Lưu kết quả đúng hệ số  */
	/*  Hệ 2 */
	if (type == 2)
	{
		bool *temp = QInt::DecToBin(t);
		int index = 0;
		for (int i = 0; i < QINT_BITS; i++)
		{
			if (temp[i] != 0)
			{
				index = i;
				break;
			}
		}
		for (int i = index; i < QINT_BITS; i++)
		{
			result = result + char(temp[i] + 48);
		}
		delete[] temp;
	}
	/* Hệ 10 */
	else if (type == 10)
	{
		result = t.ToString();
	}
	/* Hệ 16 */
	else if (type == 16)
	{
		char *hex = QInt::DecToHex(t);
		int index = 0;
		for (int i = 0; i < QINT_BITS / 4; i++)
		{
			if (hex[i] != '0')
			{
				index = i;
				break;
			}
		}
		for (int i = index; i < QINT_BITS / 4; i++)
		{
			result = result + hex[i];
		}
		delete[] hex;
	}

	delete[] b;
	delete[] b1;
	delete[] b2;
	if (result == "") result = "0";
	return result;
}
/* Chương trình xử lý file */
void Program::ProgrammingQInt(string filein, string fileout)
{
	vector<string> result; result.resize(0);
	/* input file */
	ifstream i(filein, ios::in);
	while (!i.eof())
	{
		string item;
		string temp; getline(i, temp);
		/* tìm số khoảng trắng trong string */
		int count_space = Utils::CountSpace(temp);

		/* 2 khoảng trắng là chuyển đổi cơ số */
		if (count_space == 2)
		{
			string h1, h2, s;
			int index1 = temp.find_first_of(' ');
			int index2 = temp.find_last_of(' ');
			h1 = temp.substr(0, index1);
			h2 = temp.substr(index1 + 1, index2 - index1 - 1);
			s = temp.substr(index2 + 1);
			/* case not. 2 spaces */
			if (h2 == "~")
			{
				string he = h1;
				string str = s;
				item = Program::NotQInt(he, str);
			}
			else
			{
				item = Program::ChuyenDoiQInt(h1, h2, s);
			}
		}
		/*  Tức là tính toán */
		else if (count_space == 3)
		{
			string h, s1, tt, s2;
			int index1 = temp.find_first_of(' ');
			int index2 = temp.find_first_of(' ', index1 + 1);
			int index3 = temp.find_first_of(' ', index2 + 1);
			h = temp.substr(0, index1);
			s1 = temp.substr(index1 + 1, index2 - index1 - 1);
			tt = temp.substr(index2 + 1, index3 - index2 - 1);
			s2 = temp.substr(index3 + 1);

			item = Program::TinhToanQInt(h, s1, tt, s2);
		}
		result.push_back(item);
	}
	i.close();
	/*  output file */
	ofstream o(fileout, ios::out);
	for (int i = 0; i < (int)result.size(); i++)
	{
		o << result[i] << endl;
	}
	o.close();
}


//
/// QFloat
/* Chuyen doi co so */
string Program::ChuyenDoiQFloat(string h1, string h2, string s)
{
	string result = "";
	/*  10 to 2  */
	if (h1 == "10" && h2 == "2")
	{
		QFloat item = QFloat(s);
		bool *bit = QFloat::DecToBin(item);
		for (int i = 0; i < QFLOAT_BIT; i++)
		{
			result = result + char(bit[i] + 48);
		}
		delete[] bit;
	}
	/* 2 to 10 */
	else if (h1 == "2" && h2 == "10")
	{
		/* phat sinh mang bit luu tam */
		bool *bit = new bool[QFLOAT_BIT];
		for (int i = 0; i < QFLOAT_BIT; i++) bit[i] = 0;
		int t = (int)s.length() - 1;
		for (int i = QFLOAT_BIT - 1; i >= 0; i--)
		{
			bit[i] = s[t--] - 48;
			if (t < 0) break;
		}
		QFloat item = QFloat::BinToDec(bit);
		result = item.ToString();
		delete[] bit;
	}
	return result;
}

/* Xu ly file QFloat */
void Program::ProgrammingQFloat(string filein, string fileout)
{
	vector<string> result; result.resize(0);
	/* input file */
	ifstream i(filein, ios::in);
	while (!i.eof())
	{
		string line;
		getline(i, line);
		string h1, h2, s;
		int index1 = line.find_first_of(' ');
		int index2 = line.find_last_of(' ');
		h1 = line.substr(0, index1);
		h2 = line.substr(index1 + 1, index2 - index1 - 1);
		s = line.substr(index2 + 1);
		string item = Program::ChuyenDoiQFloat(h1, h2, s);
		result.push_back(item);
	}
	i.close();

	/*  output file  */
	ofstream o(fileout, ios::out);
	for (int i = 0; i < (int)result.size(); i++)
	{
		o << result[i] << endl;
	}
	o.close();
}

//
void Program::ProgramConsole()
{
	int type;
	CHOOSE_TYPE:
	
	while(true)
	{
		system("cls");
		cout << "=================================\n";
		cout << "          CALCULATOR             \n";
		cout << "     1. QInt                     \n";
		cout << "     2. QFloat                   \n";
		cout << "     3. Exit                     \n";
		cout << "   => Your choice : "; cin >> type; 
		if (type == 1 || type == 2)
		{
			break;
		}
		else if (type == 3)
		{
			return;
		}
		else
		{
			cout << "Type is error, try again!\n";

		}
	} 

	if (type == 1)
	{
	QINT:
		system("cls");
		QInt a, b;
		int choice_int;
		do
		{
			system("cls");
			cout << "=================================\n";
			cout << "             QINT               \n";
			cout << "     1.Add                      \n";
			cout << "     2.Sub                      \n";
			cout << "     3.Mult                     \n";
			cout << "     4.Div                      \n";
			cout << "     5.AND                      \n";
			cout << "     6.OR                       \n";
			cout << "     7.XOR                      \n";
			cout << "     8.NOT                      \n";
			cout << "     9.<<                       \n";
			cout << "     10.>>                      \n";
			cout << "     11.rol                     \n";
			cout << "     12.ror                     \n";
			cout << "     13.Compare                 \n";
			cout << "     14.Convert 2               \n";
			cout << "     15.Convert 16              \n";
			cout << "     16.Return                  \n";
			cout << "   => Your choice : "; cin >> choice_int;
			if (choice_int < 1 || choice_int>16)
			{
				cout << "Type is error,try again!\n";
				_getch();
			}
			else break;
		} while (true);

		system("cls");
		if (choice_int >= 1 && choice_int <= 7)
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			cout << "Input QInt b : "; cin >> b;
		}

		switch (choice_int)
		{
		case 1:
		{
			QInt c = a + b;
			cout << a << " + " << b << " = " << c << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 2:
		{
			QInt c = a - b;
			cout << a << " - " << b << " = " << c << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 3:
		{
			QInt c = a * b;
			cout << a << " * " << b << " = " << c << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 4:
		{
			QInt c = a / b;
			cout << a << " / " << b << " = " << c << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 5:
		{
			QInt c = a & b;
			cout << a << " & " << b << " = " << c << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 6:
		{
			QInt c = a | b;
			cout << a << " | " << b << " = " << c << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 7:
		{
			QInt c = a ^ b;
			cout << a << " ^ " << b << " = " << c << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 8:
		{
			cin.ignore();
			cout << "Input QInt : "; cin >> a;
			b = ~a;
			cout << "NOT : " << b << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 9:
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			unsigned int k;
			cout << "Input k : "; cin >> k;
			b = a << k;
			cout << " a << " << k << " = " << b << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 10:
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			unsigned int k;
			cout << "Input k : "; cin >> k;
			b = a >> k;
			cout << " a >> " << k << " = " << b << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 11:
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			unsigned int k;
			cout << "Input k : "; cin >> k;
			b = a.RotateLeft(k);
			cout << " a rol " << k << " = " << b << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 12:
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			unsigned int k;
			cout << "Input k : "; cin >> k;
			b = a.RotateRight(k);
			cout << " a ror " << k << " = " << b << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 13:
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			cout << "Input QInt b : "; cin >> b;
			if (a > b)
			{
				cout << a << " > " << b << endl;
			}
			else if (a < b)
			{
				cout << a << " < " << b << endl;
			}
			else
				cout << a << " == " << b << endl;
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 14:
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			bool *bit = QInt::DecToBin(a);
			cout << "Binary : "; Program::Ouput2(bit);
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 15:
		{
			cin.ignore();
			cout << "Input QInt a : "; cin >> a;
			char *hex = QInt::DecToHex(a);
			cout << "Binary : "; Program::Output16(hex);
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QINT;
		}
		case 16:
		{
			goto CHOOSE_TYPE;
			return;
		}

		}
	}

	if (type == 2)
	{
	QFLOAT:
		int choice_float;
		QFloat a;
		do
		{
			system("cls");
			cout << "=================================\n";
			cout << "             QFLOAT              \n";
			cout << "     1.Convert 2                 \n";
			cout << "     2.Return                    \n";
			cout << "   => Your choice : "; cin >> choice_float;
			if (choice_float == 1 || choice_float == 2)
				break;
			else
			{
				cout << "Type is error, try again!";
				_getch();
			}
		} while (true);

		if (choice_float == 1)
		{
			cin.ignore();
			cout << "Input QFloat : "; cin >> a;
			bool *bit = QFloat::DecToBin(a);
			cout << "Binary (Floating Point) : \n";
			Program::Ouput2(bit, false);
			cout << "ENTER TO CONTINUE.....";
			_getch();
			goto QFLOAT;
		}
		else
		{
			goto CHOOSE_TYPE;
			return;
		}
	}
}