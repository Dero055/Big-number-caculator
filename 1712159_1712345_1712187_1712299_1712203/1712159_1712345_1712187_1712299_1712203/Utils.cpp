#include "Utils.h"

/* Kiểm tra tính hợp lệ của chuỗi kiểu int */
bool Utils::CheckStringForIntType(string value)
{
	bool check = true;
	int i = 0;
	if (value[0] == '-')
	{
		i = 1;
	}

	for (i; i < (int)value.length(); i++)
	{
		if (value[i]<'0' || value[i]>'9')
		{
			check = false;
			break;
		}
	}
	return check;
}

/* Kiểm tra tính hợp lệ của chuỗi kiểu float */
bool Utils::CheckStringForFloatType(string value)
{
	int count = 0;
	int i = 0;
	if (value[i] == '-')
	{
		i = 1;
	}
	for (i; i < (int)value.length(); i++)
	{
		if ((value[i]<'0' || value[i]>'9') && value[i] != '.')
		{
			return false;
		}
		if (value[i] == '.')
		{
			count++;
		}
	}
	if (count > 1)
	{
		return false;
	}
	return true;
}

/* Hàm tính chia 2 của kiểu int theo chuỗi */
string Utils::StringChia2(string value)
{
	string result = "";
	int n = (int)value.length();
	int index = 0;

	string mod = "0";
	while (index != n)

	{
		int temp = stoi(mod + value[index]);
		int du = temp % 2;
		int nguyen = temp / 2;
		result += char(nguyen + 48);
		mod = char(du + 48);
		index++;
	}
	if (result[0] == '0')
	{
		result.erase(0, 1);
	}
	return result;
}

/* hàm tính nhân 2 của kiểu int theo chuỗi */
string Utils::StringNhan2(string value)
{
	string result = "";
	result = Utils::CongStringTheoInt(value, value);
	return result;
}

/* Cộng 2 chuổi theo kiểu int */
string Utils::CongStringTheoInt(string a, string b)
{
	/* Phát sinh mảng lưu kết quả */
	string result;
	int n_a = (int)a.length();
	int n_b = (int)b.length();
	int n = n_a > n_b ? n_a : n_b;
	++n;
	result.resize(n);
	for (int i = 0; i < n; i++)
	{
		result[i] = '0';
	}
	for (int i = 1; i <= n - n_a; i++)
	{
		a = '0' + a;
	}
	for (int i = 1; i <= n - n_b; i++)
	{
		b = '0' + b;
	}

	int mod = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		int item = a[i] + b[i] - 96 + mod;
		result[i] = item % 10 + 48;
		mod = item / 10;
	}
	if (result[0] == '0')
	{
		result = result.erase(0, 1);
	}
	return result;
}

/* Hàm tính mũ của 2 */
string Utils::MuCua2(unsigned int x)
{
	if (x == 0)
	{
		return "1";
	}
	else if (x == 1)
	{
		return "2";
	}

	string result = "2";
	for (int i = 2; i <= (int)x; i++)
	{
		result = Utils::CongStringTheoInt(result, result);
	}
	return result;
}

/* Hàm tìm số bù 2 */
bool* Utils::SoBu2(bool *bit)
{
	bool *bu2 = new bool[QINT_BITS];
	for (int i = 0; i < QINT_BITS; i++)
	{
		bu2[i] = !bit[i];
	}
	for (int i = QINT_BITS - 1; i >= 1; i--)
	{
		if (bu2[i] == 0)
		{
			bu2[i] = 1;
			for (int j = i + 1; j < QINT_BITS; j++)
			{
				bu2[j] = 0;
			}
			break;
		}
	}
	return bu2;
}

/* Hàm tính số khoảng trắng của chuỗi */
int Utils::CountSpace(string value)
{
	int count = 0;
	for (int i = 0; i < (int)value.length(); i++)
	{
		if (value[i] == ' ')
			count++;
	}
	return count;
}

