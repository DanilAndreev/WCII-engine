#include "pch.h"
#include "SearchTarget.h"

using namespace std;

SearchTarget::SearchTarget(string target_word, string target_type, string default_value) {
	this->target_type = target_type;
	this->target_word = target_word;
	pair <string, string> temp;
	temp.first = default_value;
	temp.second = target_type;
	addData(temp);
}

SearchTarget::~SearchTarget() {
}

bool SearchTarget::addData(char tChar) {
	this->temp_char = tChar;
	return true;
}

bool SearchTarget::addData(int tInt) {
	this->temp_int = tInt;
	return true;
}

bool SearchTarget::addData(string tString) {
	this->temp_string = tString;
	return true;
}

bool SearchTarget::addData(vector<string> tVstring) {
	this->temp_vstring = tVstring;
	return true;
}

bool SearchTarget::addData(pair <string, string> input) {
	if (input.second == "dqdata" || input.second == "word") {
		this->temp_string = input.first;
		return true;
	}
	if (input.second == "number") {
		this->temp_int = stoi(input.first);
		return true;
	}
	if (input.second == "qdata") {
		this->temp_char = input.first[0];
		return true;
	}
	return false;
}
