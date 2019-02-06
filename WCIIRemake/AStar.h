#pragma once
#include "pch.h"
#include "Queue.h"
#include "Field.h"
#include "Unit.h"
#include "MScreen.h"

using namespace std;

#define ROW 9 
#define COL 10

struct AStarNode : private Obj {
	AStarNode* cameFrom;
	//cordScr nodePosition;
	//AStarNode(AStarNode* cameFromInp, cordScr unitInp) : cameFrom(cameFromInp), nodePosition(unitInp) {}
//	AStarNode(int x, int y, Unit* unitInp) : AStarNode(cordScr(x,y),unitInp) {}
};

struct cell{
	// Row and Column index of its parent 
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	int parent_i, parent_j;	
	// f = g + h
	double f, g, h;
};

class AStar : public Obj {
	private :
		cell **cellDetails;
		bool **closedList;
		typedef pair<int, int> Pair;
		typedef pair<double, pair<int, int>> pPair;
		bool isValid(int row, int col);
		bool isUnBlocked(int **grid, int row, int col);
		bool isDestination(int row, int col, cordScr scr);
		double calculateHValue(int row, int col, cordScr scr);
		void tracePath(cell **cellDetails, cordScr scr, int **grid);
	public:
		char ** path;
		int **grid;
		int rows;
		int columns;
		void getPathMap();
		AStar(int h, int w);
		~AStar();
		void getMap(char * field, char type);
		void aStarSearch(int **grid, cordScr start, cordScr scr);
};