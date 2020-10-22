#include "pch.h"
#include "Player.h"


Player::Player(int team, vector<int> friendTeams, vector<Resource> resources, PID PlayerID) {
	this->team = team;
	this->friendTeams = friendTeams;
	this->resources = resources;
	this->PlayerID = PlayerID;
}


Player::~Player() {
}
