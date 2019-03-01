#pragma once
#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;


struct Command_c {
	vector <pair<string, string>> args;

	friend bool operator==(const Command_c& left, string right) {
		return left.args[0].first == right;
	}

	Command_c(vector <pair<string, string>> inp_args) : args(inp_args) {}
	Command_c() {}

	void printCommand(string imessage) {
		cout << imessage << endl;
		for (unsigned int i = 0; i < args.size(); i++) {
			cout << "[" << i << "]" << "(" << args[i].second << ")" << args[i].first;
			if (i != args.size() - 1) {
				cout << " : ";
			}
		}
		cout << endl;
	}

	void printCommand() {
		printCommand("");
	}
};
