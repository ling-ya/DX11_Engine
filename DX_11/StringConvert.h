#pragma once
#include<Windows.h>
#include<string>
using namespace std;

class StringConvert
{
public:
	static string WStringToString(wstring str);
	static wstring StringToWString(string str);
};

