#pragma once
#include "Obj.h"
#include "Resource.h"

typedef int PID;

class Player : public Obj {
public:
	int team;
	vector <int> friendTeams;
	vector <Resource> resources;
	PID PlayerID;
public:
	Player(int team, vector<int> friendTeams, vector<Resource> resources, PID PlayerID);
	Player(int team, vector<int> friendTeams, PID PlayerID) : Player(team, friendTeams, vector<Resource>(), PlayerID) {}
	virtual ~Player();
};

