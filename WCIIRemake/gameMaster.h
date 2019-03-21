#pragma once
#include "Obj.h"
class GameMaster : public Obj {
	vector <Unit> unitPresets;
	//add players
public:
	GameMaster();
	~GameMaster();
	void readUnits();
};

