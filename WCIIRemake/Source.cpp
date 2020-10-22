#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <Windows.h>

using namespace std;

typedef vector<string> stringvec;

stringvec read_directory(const string directoryPath)
{
	stringvec v;
	string pattern(directoryPath);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	return v;
}
