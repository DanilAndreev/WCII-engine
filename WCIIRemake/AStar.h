#pragma once
#include "pch.h"
#include "Queue.h"
#include "Field.h"
#include "Unit.h"

struct AStarNode : private Obj {
	//AStarNode* cameFrom;
	//cordScr nodePosition;
	//AStarNode(AStarNode* cameFromInp, cordScr unitInp) : cameFrom(cameFromInp), nodePosition(unitInp) {}
//	AStarNode(int x, int y, Unit* unitInp) : AStarNode(cordScr(x,y),unitInp) {}
};

class AStar : private Obj {
public:

private:

	bool aStar(const float * weights, const int h, const int w, const int start, const int goal, bool diag_ok, int * paths);

};

class Node {
public:
	int idx;     // index in the flattened grid
	float cost;  // cost of traversing this pixel

	Node(int i, float c) : idx(i), cost(c) {}
};

float linf_norm(int i0, int j0, int i1, int j1);
