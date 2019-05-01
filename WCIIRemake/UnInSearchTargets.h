#pragma once
#include "SearchTarget.h"

class UnInSearchTargets {
public:
	vector <SearchTarget> targets;
	string type;
public:
	UnInSearchTargets(string type);
	UnInSearchTargets() : UnInSearchTargets("unit") {}
	~UnInSearchTargets();
	bool addTarget(SearchTarget input);
	bool setType(string newtype);
	int search(string word); // returns the index of searcthTarget with this word or -1 when not found
};

