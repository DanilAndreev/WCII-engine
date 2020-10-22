#include "pch.h"
#include "UnitInterpretor.h"

extern const char* PARSER_DQDATA;
extern const char* PARSER_QDATA;
extern const char* PARSER_DOTCOM;
extern const char* PARSER_COMA;
extern const char* PARSER_DDOTS;
extern const char* PARSER_NUMBER;
extern const char* PARSER_WORD;
extern const char* PARSER_SBORD_LIST;
extern const char* PARSER_SBORD;
extern const char* PARSER_FBORD;
extern const char* PARSER_DQUOTE;
extern const char* PARSER_QUOTE;


UnitInterpretor::UnitInterpretor() {
}


UnitInterpretor::~UnitInterpretor() {
}

void UnitInterpretor::init(UnInSearchTargets newtargets) {
	this->targets = newtargets;
}

UnInSearchTargets UnitInterpretor::getTargets() {
	return this->targets;
}

Exitcode UnitInterpretor::interpret(ParserOut input) {
	if (input.args.size() < 8) {
		return GM_ERROR_ARGUMENTS_COUNT;
	}
	//interpreting parsed file data
	if (input.args[0].first != this->targets.type) {
		return GM_ERROR_NOT_VALID_TYPE;
	}
	if (input.args[1].second == PARSER_WORD) {
		int t_id;
		if ((t_id = targets.search("name")) != -1) {
			this->targets.targets[t_id].addData(input.args[1].first);
			// --------------------------------------------------------------------ADD EVENT AND CHECK THE NAME, if exist - name.append(to_string(i)); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
	}
	if (input.args[2].second != PARSER_FBORD || input.args[input.args.size() - 1].second != "fbord") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}
	if (input.args[2].first != "{" || input.args[input.args.size() - 1].first != "}") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}

	int lineArgs = 1; // count of arguments in one line, to jump over lines in each step
	for (unsigned int i = 3; i < input.args.size() - 1; i += lineArgs) {
		lineArgs = 1;
		// Checking input correctness
		if (input.args[i].second != PARSER_WORD) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (i + 1 >= input.args.size()) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (input.args[i + 1].second != PARSER_DDOTS) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}

		if (targets.search(input.args[i].first) != -1 && targets.targets[targets.search(input.args[i].first)].target_type == PARSER_SBORD_LIST) {  // condition for looking for multiple values
			if (input.args[i + 2].second != PARSER_SBORD) {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			if (input.args[i + 2].first != "[") {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			int startbrackets_index = i + 2;
			if (startbrackets_index + 2 >= input.args.size()) {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			if (input.args[startbrackets_index + 1].first == "]" && input.args[startbrackets_index + 1].second == PARSER_SBORD && input.args[startbrackets_index + 2].second == PARSER_DOTCOM) { // checking if it is an empty data sequence
				lineArgs = 5;
			}
			else {
				int endbrackets_index = startbrackets_index + 1;
				if (endbrackets_index >= input.args.size()) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				while (input.args[endbrackets_index].second != PARSER_SBORD && input.args[endbrackets_index].first != "]" && endbrackets_index < input.args.size()) { // looking for ] symbol id
					endbrackets_index++;
				}
				if (endbrackets_index == input.args.size() - 1) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				if (endbrackets_index + 1 >= input.args.size()) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				if (input.args[endbrackets_index + 1].second != PARSER_DOTCOM) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				lineArgs = endbrackets_index - i + 2; // setting line width to number of line arguments to skip whole line on the next step
				if ((endbrackets_index - startbrackets_index) % 2 != 0) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				vector <string> vstring_temp;
				for (int ind = startbrackets_index + 1; ind < endbrackets_index; ind += 2) {
					if (input.args[ind].second != PARSER_DQDATA) {
						return GM_ERROR_NOT_VALID_STRUCTURE;
					}
					if (input.args[ind + 1].second != PARSER_COMA && ind + 1 != endbrackets_index) {
						return GM_ERROR_NOT_VALID_STRUCTURE;
					}
					vstring_temp.push_back(input.args[ind].first);
					//adding data
					if (targets.search(input.args[i].first) != -1) {
						targets.targets[targets.search(input.args[i].first)].addData(vstring_temp);
					}
				}
			}
		}
		else {
			if (i + 3 > input.args.size() - 1) {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			lineArgs = 4;
			if (input.args[i + 1].second != PARSER_DDOTS) {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			if (input.args[i + 3].second != PARSER_DOTCOM) {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			// Temporary buffer variables
			string temp_str;
			int temp_integer = 0;
			char temp_character = ' ';

			// Choosing buffer to save info
			if (input.args[i + 2].second == PARSER_QDATA && strlen(input.args[i + 2].first.data()) == 1) {
				temp_character = input.args[i + 2].first[0];
			}
			if (input.args[i + 2].second == PARSER_DQDATA || input.args[i + 2].second == "word") {
				temp_str = input.args[i + 2].first;
			}
			if (input.args[i + 2].second == PARSER_NUMBER) {
				temp_integer = stoi(input.args[i + 2].first);
			}

			// addingData
			if (targets.search(input.args[i].first) != -1 && (targets.targets[targets.search(input.args[i].first)].target_type == PARSER_DQDATA || targets.targets[targets.search(input.args[i].first)].target_type == PARSER_WORD)) {
				targets.targets[targets.search(input.args[i].first)].addData(temp_str);
			}
			if (targets.search(input.args[i].first) != -1 && targets.targets[targets.search(input.args[i].first)].target_type == PARSER_QDATA) {
				targets.targets[targets.search(input.args[i].first)].addData(temp_character);
			}
			if (targets.search(input.args[i].first) != -1 && targets.targets[targets.search(input.args[i].first)].target_type == PARSER_NUMBER) {
				targets.targets[targets.search(input.args[i].first)].addData(temp_integer);
			}
		}
	}
	return GM_NO_ERROR;
}

Exitcode UnitInterpretor::interpret(string filename) {
	ParserOut parsedFile;
	FileParser* parser = new FileParser();

	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	parsedFile = parser->parseFile(filename);
	delete parser;

	return interpret(parsedFile);
}
