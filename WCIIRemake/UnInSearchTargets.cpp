#include "pch.h"
#include "UnInSearchTargets.h"


UnInSearchTargets::UnInSearchTargets(string type) {
	this->setType(type);
}


UnInSearchTargets::~UnInSearchTargets() {
}

bool UnInSearchTargets::addTarget(SearchTarget input) {
	targets.push_back(input);
	return true;
}

bool UnInSearchTargets::setType(string newtype) {
	this->type = newtype;
	return true;
}

int UnInSearchTargets::search(string word) {
	for (int i = 0; i < targets.size(); i++) {
		if (targets[i].target_word == word) {
			return i;
		}
	}
	return -1;
}
