#include "pch.h"
#include "FileReader.h"

using namespace std;

extern Console* defaultConsole;

FileReader::FileReader(string filename) {
	this->data.clear();
	read(filename);
}

FileReader::~FileReader() {
	if (isOpened()) {
		filein.close();
	}
}

bool FileReader::isOpened() {
	if (filein) {
		return true;
	}
	return false;
}

string FileReader::getData() {
	return this->data;
}

bool FileReader::read(string filename) {
	if (isOpened()) {
		filein.close();
	}
	filein = ifstream(filename);
	if (!filein) {
		defaultConsole->error("Cannot open file");
		return false;
	}
	this->data.clear();
	string temp;
	while (!filein.eof()) {
		getline(filein, temp);
		this->data += temp + "\n";
	}
	return true;
}

