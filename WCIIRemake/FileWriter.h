#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

class FileWriter {
protected:
	ofstream fileHandle;
	string filename;
public:
	FileWriter(string filename, ios_base::openmode mode = ios_base::out);
	virtual ~FileWriter();
	bool setMode(ios_base::openmode mode = ios_base::out);
	ofstream& operator << (string text);
};