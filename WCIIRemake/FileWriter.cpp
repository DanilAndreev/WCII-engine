#include "pch.h"
#include "FileWriter.h"


FileWriter::FileWriter(string filename, ios_base::openmode mode) {
	this->filename = filename;
	this->fileHandle = ofstream(this->filename, mode);
}

FileWriter::~FileWriter() {
	fileHandle.close();
}


ofstream& FileWriter::operator << (string text) {
	fileHandle << text;
	return fileHandle;
}

bool FileWriter::setMode(ios_base::openmode mode) {
	fileHandle.close();
	fileHandle.open(this->filename, mode);
	return false;
}
