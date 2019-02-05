#include "pch.h"

using namespace std;


void AStar::getMap(char * field, char type) {
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (field[i*count+j] == '.' || field[i*count+j] == type) {
				grid[i][j] = 1;
			}
			else grid[i][j] = 0;
		}
		count++;
	}
}
void AStar::getPathMap() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << path[i][j];
		}
		cout << endl;
	}
}

AStar::AStar(int h, int w) {
	rows = h;
	columns = w;
	path = new char*[rows];
	cellDetails = new cell*[rows];
	grid = new int*[rows];
	closedList = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		path[i] = new char[columns];
		cellDetails[i] = new cell[columns];
		grid[i] = new int[columns];
		closedList[i] = new bool[columns];
		for (int j = 0; j < columns; j++) {
			closedList[i][j] = false;
		}
	}
}

AStar::~AStar() {
	delete[] path;
	delete[] grid;
	delete[] cellDetails;
	delete[] closedList;
}
bool AStar::isValid(int row, int col) {
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < rows) &&
		(col >= 0) && (col < columns);
}

// check whether the given cell is 
// blocked or not 
bool AStar::isUnBlocked(int **grid, int row, int col){
	// Returns true if the cell is not blocked else false 
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

// check whether destination cell has 
// been reached or not 
bool AStar::isDestination(int row, int col, cordScr dest){
	//printf("%d %d %d %d", row, col, dest.x, dest.y);
	if (row == dest.x && col == dest.y)
		return (true);
	else
		return (false);
}

// 
double AStar::calculateHValue(int row, int col, cordScr scr){
	// Return using the distance formula of Pifagor :)
	return ((double)sqrt((row - scr.x)*(row - scr.x)
		+ (col - scr.y)*(col - scr.y)));
}

// trace the path from the source 
// to destination 
void AStar::tracePath(cell **cellDetails, cordScr finish, int **grid){
	printf("\nThe Path is \n");
	int row = finish.x;
	int col = finish.y;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
		&& cellDetails[row][col].parent_j == col))
	{
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty()){
		pair<int, int> p = Path.top();
		Path.pop();
		for (int x = 0; x < rows; x++) {
			for (int y = 0; y < columns; y++) {
				if (grid[x][y] == 0) {
					path[x][y] = char(0xdb);
				}
				else {
					if (y == p.second && x == p.first) {
						path[x][y] = 'x';
					}
					else if (path[x][y] == 'x') continue;
					else path[x][y] = '.';
				}
			}
		}
		printf("%d %d\n", p.first, p.second);
	}

	return;
}

// find the shortest path between 
// a given source cell to a destination cell
void AStar::aStarSearch(int **grid, cordScr start, cordScr dest)
{
	// If the source is out of range 
	if (isValid(start.x, start.y) == false)
	{
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range 
	if (isValid(dest.x, dest.y) == false)
	{
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked 
	if (isUnBlocked(grid, start.x, start.y) == false ||
		isUnBlocked(grid, dest.x, dest.y) == false)
	{
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell 
	if (isDestination(start.x, start.y, dest) == true)
	{
		printf("We are already at the destination\n");
		return;
	}

	int i, j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node 
	i = start.x, j = start.y;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	set<pPair> openList;
	openList.insert(make_pair(0.0, make_pair(i, j)));
	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		// Remove this vertex from the open list 
		openList.erase(openList.begin());

		// Add this vertex to the closed list 
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		 // To store the 'g', 'h' and 'f' of the 8 successors 
		double gNew, hNew, fNew;

		if (isValid(i - 1, j) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i - 1, j, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}
			else if (closedList[i - 1][j] == false &&
				isUnBlocked(grid, i - 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;
				if (cellDetails[i - 1][j].f == FLT_MAX ||
					cellDetails[i - 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i - 1, j)));
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}
		if (isValid(i + 1, j) == true)
		{
			if (isDestination(i + 1, j, dest) == true)
			{
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}
			else if (closedList[i + 1][j] == false &&
				isUnBlocked(grid, i + 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;
				if (cellDetails[i + 1][j].f == FLT_MAX ||
					cellDetails[i + 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i + 1, j)));
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		if (isValid(i, j + 1) == true)
		{
			if (isDestination(i, j + 1, dest) == true)
			{
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}
			else if (closedList[i][j + 1] == false &&
				isUnBlocked(grid, i, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;
				if (cellDetails[i][j + 1].f == FLT_MAX ||
					cellDetails[i][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j + 1)));
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}
		if (isValid(i, j - 1) == true)
		{
			if (isDestination(i, j - 1, dest) == true)
			{
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}

			else if (closedList[i][j - 1] == false &&
				isUnBlocked(grid, i, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;
				if (cellDetails[i][j - 1].f == FLT_MAX ||
					cellDetails[i][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j - 1)));
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}
		if (isValid(i - 1, j + 1) == true)
		{
			if (isDestination(i - 1, j + 1, dest) == true)
			{
				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}
			else if (closedList[i - 1][j + 1] == false &&
				isUnBlocked(grid, i - 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i - 1, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
					cellDetails[i - 1][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i - 1, j + 1)));
					cellDetails[i - 1][j + 1].f = fNew;
					cellDetails[i - 1][j + 1].g = gNew;
					cellDetails[i - 1][j + 1].h = hNew;
					cellDetails[i - 1][j + 1].parent_i = i;
					cellDetails[i - 1][j + 1].parent_j = j;
				}
			}
		}
		if (isValid(i - 1, j - 1) == true)
		{
			if (isDestination(i - 1, j - 1, dest) == true)
			{
				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}

			else if (closedList[i - 1][j - 1] == false &&
				isUnBlocked(grid, i - 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i - 1, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
					cellDetails[i - 1][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
					cellDetails[i - 1][j - 1].f = fNew;
					cellDetails[i - 1][j - 1].g = gNew;
					cellDetails[i - 1][j - 1].h = hNew;
					cellDetails[i - 1][j - 1].parent_i = i;
					cellDetails[i - 1][j - 1].parent_j = j;
				}
			}
		}
		if (isValid(i + 1, j + 1) == true)
		{ 
			if (isDestination(i + 1, j + 1, dest) == true)
			{
				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j + 1] == false &&
				isUnBlocked(grid, i + 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i + 1, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
					cellDetails[i + 1][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i + 1, j + 1)));
					cellDetails[i + 1][j + 1].f = fNew;
					cellDetails[i + 1][j + 1].g = gNew;
					cellDetails[i + 1][j + 1].h = hNew;
					cellDetails[i + 1][j + 1].parent_i = i;
					cellDetails[i + 1][j + 1].parent_j = j;
				}
			}
		}
		if (isValid(i + 1, j - 1) == true)
		{
			if (isDestination(i + 1, j - 1, dest) == true)
			{
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}
			else if (closedList[i + 1][j - 1] == false &&
				isUnBlocked(grid, i + 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i + 1, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
					cellDetails[i + 1][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i + 1, j - 1)));
					cellDetails[i + 1][j - 1].f = fNew;
					cellDetails[i + 1][j - 1].g = gNew;
					cellDetails[i + 1][j - 1].h = hNew;
					cellDetails[i + 1][j - 1].parent_i = i;
					cellDetails[i + 1][j - 1].parent_j = j;
				}
			}
		}
	}
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}