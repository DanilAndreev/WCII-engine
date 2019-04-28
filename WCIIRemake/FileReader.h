#pragma once
#include "Obj.h"
#include <fstream>
#include <iostream>
#include <string>

class FileReader : public Obj {
private:
	string data;
	ifstream filein;
public:
	FileReader(string filename);
	~FileReader();
	string getData();
	bool read(string filename);
	bool isOpened();
};
