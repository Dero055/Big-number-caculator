#pragma once
#include "Utils.h"
#include "QInt.h"
#include "QFloat.h"
#include <fstream>
#include <vector>
#include<iostream>

class Program
{
public:
	///*  QInt  */
	/* Chuyen doi co so */
	static string ChuyenDoiQInt(string h1, string h2, string str);
	/* Not */
	static string NotQInt(string h, string s);
	/* Tinh toan */
	static string TinhToanQInt(string h, string s1, string toantu, string s2);
	/* Xu ly file */
	static void ProgrammingQInt(string filein = "input1.txt", string fileout = "output1.txt");

	///*  QFloat  */
	/* Chuyen doi */
	static string ChuyenDoiQFloat(string h1, string h2, string s);
	/* Xu ly file */
	static void ProgrammingQFloat(string filein = "input2.txt", string fileout = "output2.txt");

	///* Chương trình console */
	static void ProgramConsole();

	static void Ouput2(bool *bit, bool bin = true)
	{
		int index = 0;
		if (bin)
		{
			for (int i = 0; i < QINT_BITS; i++)
			{
				if (bit[i] != 0)
				{
					index = i;
					break;
				}
			}
		}
		for (int i = index; i < QINT_BITS; i++)
		{
			cout << bit[i];
		}
		cout << endl;

	}

	static void Output16(char *hex)
	{
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
			cout << hex[i];
		}
		cout << endl;
	}
};

