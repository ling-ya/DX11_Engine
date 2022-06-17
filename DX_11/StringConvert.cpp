#include "StringConvert.h"

string StringConvert::WStringToString(wstring str)
{
    int size = (int)str.size();
    string s;
    s.resize(size);
    WideCharToMultiByte(CP_ACP, 0, (LPCWCH)str.c_str(), size, (LPSTR)s.c_str(), size, 0, 0);
    return s;
}

wstring StringConvert::StringToWString(string str)
{
    int size = (int)str.size();
    wstring ws;
    ws.resize(size);
    MultiByteToWideChar(CP_ACP, 0, (LPCCH)str.c_str(), size, (LPWSTR)ws.c_str(), size);
    return ws;
}
