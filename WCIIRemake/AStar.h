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
		int calcDist(point& p);
		bool isValid(point& p);
		bool existPoint(point& p, int cost);
		bool fillOpen(node& n);
		bool search(point& s, point& e, map& mp);
		int path(std::list<point>& path);
		~AStar();

		map m; point end, start;
		point neighbours[8];
		std::list<node> open;
		std::list<node> closed;
};

class map : public AStar {
public:
	map() {
		char t[8][8] = {
			{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0, 1, 0},
			{0, 0, 1, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}
		};
		w = h = 8;
		for (int r = 0; r < h; r++)
			for (int s = 0; s < w; s++)
				m[s][r] = t[r][s];
	}
	int operator() (int x, int y) { return m[x][y]; }
	char m[8][8];
	int w, h;
};

class node : public AStar {
public:
	bool operator == (const node& o) { return pos == o.pos; }
	bool operator == (const point& o) { return pos == o; }
	bool operator < (const node& o) { return dist + cost < o.dist + o.cost; }
	point pos, parent;
	int dist, cost;
};

class point : public AStar {
public:
	point(int a = 0, int b = 0) { x = a; y = b; }
	bool operator ==(const point& o) { return o.x == x && o.y == y; }
	point operator +(const point& o) { return point(o.x + x, o.y + y); }
	int x, y;
};