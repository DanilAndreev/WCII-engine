#pragma once
#include "pch.h"
#include "Queue.h"

struct AStarNode : private Obj {
	AStarNode* cameFrom;
	cordScr nodePosition;
	AStarNode(AStarNode* cameFromInp, cordScr unitInp) : cameFrom(cameFromInp), nodePosition(unitInp) {}
//	AStarNode(int x, int y, Unit* unitInp) : AStarNode(cordScr(x,y),unitInp) {}
};



class AStar : public Field{
	private:
	public:
		AStar();
		DynArr* Dejkstra(Unit* unit);
		DynArr * findPath(DynArr * passes,  cordScr targetCords);
		~AStar();
};

