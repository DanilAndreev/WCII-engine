#include "pch.h"
#include "Player.h"


Player::Player(int team, vector<int> friendTeams, vector<Resource> resources) {
	this->team = team;
	this->friendTeams = friendTeams;
	this->resources = resources;
}


Player::~Player() {
}
