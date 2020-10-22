#pragma once
#include <vector>
#include "UnInSearchTargets.h"
#include "Exitcode.h"

class UnitInterpretor {
protected:
	vector <SearchTarget> temp_targets;
	UnInSearchTargets targets;
public:
	UnitInterpretor();
	~UnitInterpretor();
	void init(UnInSearchTargets newtargets);
	UnInSearchTargets getTargets();
	Exitcode interpret(ParserOut input);
	Exitcode interpret(string filename);
};

