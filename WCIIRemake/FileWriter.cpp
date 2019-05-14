#include "pch.h"
#include "FileWriter.h"


FileWriter::FileWriter(string filename, ios_base::openmode mode) {
	this->filename = filename;
	this->fileHandle = ofstream(this->filename, mode);
//	cout << "Opened file: " << filename << endl;
}

FileWriter::~FileWriter() {
	fileHandle.close();
//	cout << "Closed file: " << filename << endl;
}


ofstream& FileWriter::operator << (string text) {
	fileHandle << text;
	return fileHandle;
}

bool FileWriter::setMode(ios_base::openmode mode) {
	fileHandle.close();
//	cout << "Closed file: " << filename << endl;
	fileHandle.open(this->filename, mode);
//	cout << "Opened file: " << filename << endl;
	return false;
}
