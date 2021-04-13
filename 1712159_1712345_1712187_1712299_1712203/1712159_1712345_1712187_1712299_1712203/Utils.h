#pragma once
#include "Definition.h"
#include <iostream>
#include <string>
#include <cmath>
#include"conio.h"
using namespace std;


class Utils
{
public:
	/* Hàm kiểm tra tính đúng đắn của chuỗi số nguyên */
	static bool CheckStringForIntType(string);
	/* Hàm kiểm tra tính đúng đắn của chuỗi số thực */
	static bool CheckStringForFloatType(string);
	/* Hàm chuỗi chia 2 theo số nguyên */
	static string StringChia2(string);
	/* Hàm chuỗi nhân 2 theo số nguyên */
	static string StringNhan2(string);
	/* Hàm cộng chuỗi theo số nguyên */
	static string CongStringTheoInt(string, string);
	/* Hàm tính số mũ của 2 */
	static string MuCua2(unsigned int);
	/* Hàm tính số bù 2 của dãy bit */
	static bool* SoBu2(bool*);
	/* Hàm tính số khoảng trắng của một chuỗi */
	static int CountSpace(string);

};

