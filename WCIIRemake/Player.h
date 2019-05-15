#pragma once
#include "Obj.h"
#include "Resource.h"

class Player : public Obj {
public:
	int team;
	vector <int> friendTeams;
	vector <Resource> resources;
public:
	Player(int team, vector<int> friendTeams, vector<Resource> resources);
	Player(int team, vector<int> friendTeams) : Player(team, friendTeams, vector<Resource>()) {}
	virtual ~Player();
};

