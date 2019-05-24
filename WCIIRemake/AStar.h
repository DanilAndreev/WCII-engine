#pragma once
#include "pch.h"
#include "Queue.h"
#include "Field.h"
#include "Unit.h"
#include "MScreen.h"

using namespace std;

struct AStarNode : private Obj {
	AStarNode* cameFrom;
	//cordScr nodePosition;
	//AStarNode(AStarNode* cameFromInp, cordScr unitInp) : cameFrom(cameFromInp), nodePosition(unitInp) {}
//	AStarNode(int x, int y, Unit* unitInp) : AStarNode(cordScr(x,y),unitInp) {}
};

struct cell {
	// Row and Column index of its parent 
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

class AStar : public FastPath {
private:
	cell** cellDetails;
	bool** closedList;
	typedef pair<int, int> Pair;
	typedef pair<double, pair<int, int>> pPair;
	bool isValid(int row, int col); // Returns true if row number and column number is in range 
	bool isUnBlocked(int row, int col); // check whether the given cell is blocked or not 
	bool isDestination(int row, int col, cordScr dest); // check whether destination cell has been reached or not
	double calculateHValue(int row, int col, cordScr dest); // Return using the distance formula of Pifagor :)
	cordScr tracePath(cordScr dest); // // trace the path from the start to destination
	cordScr nextCord;
	cordScr start;
	cordScr dest;
protected:
	char** path;
	int** grid;
	int direction;
public:
	//AStar(int h, int w);
	~AStar();
	AStar(Field* world, Unit* unit, int h, int w, cordScr start, cordScr dest);
	//AStar(Field * world, Unit * unit, int h, int w);
	void getMap(DynArr* field, int type, Unit* unt); // for transformation in bool map
	int rows;
	int columns;
	void getMap(Field* field, int type, Unit* unt);
	void Dijkstra(cordScr start, cordScr dest); // path search of Dijkstra(not developed)
	int getPath();// returns 1 - up, 2 - down, 3 - right, 4 - left, 5 - north east, 6 - north west, 7 - south east, 8 - south west
	void aStarSearch(); // main function for astar search, from start to destination
	cordScr getNextCord() {
		return this->nextCord;
	}
};