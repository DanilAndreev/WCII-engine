#include "pch.h"
#include "ParserOut.h"

using namespace std;

ParserOut::ParserOut() {
	ParserOut("error");
}

ParserOut::ParserOut(string arg) {
	pair <string, string> command;
	command.first = arg;
	command.second = "command";
	args.push_back(command);
}

ParserOut::~ParserOut() {
}

void ParserOut::print(string imessage) {
	cout << imessage << endl;
	for (unsigned int i = 0; i < args.size(); i++) {
		cout << "[" << i << "]" << "(" << args[i].second << ")'" << args[i].first << "'";
		if (i != args.size() - 1) {
			cout << " : ";
		}
	}
	cout << endl;
}

void ParserOut::print() {
	print("");
}



bool operator==(const ParserOut& left, string right) {
	return left.args[0].first == right;
}

