#include "pch.h"

using namespace std;


void AStar::getMap(DynArr* field, int type, Unit* unt) {
	/*
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (field[i*count+j].count() == 0 || unt.getType() == type) {
				grid[i][j] = 1;
			}
			else grid[i][j] = 0;

			cout << grid[i][j] << " ";
		}
		count++;
		cout << endl << endl;
	}
	*/

	for (int i = 0; i < field->count(); i++) {
		Unit* temp = (Unit*)(field->get(i));
		if (temp->getType() == type && temp != unt) {  //------------------------------------------------------------------------------------------------------------------<<<<<<<<<<<<<<<
			int x = temp->getCords().x;
			int y = temp->getCords().y;
			if (x < rows && x >= 0 && y < columns && y >= 0) {
				grid[y][x] = 0;
			}
		}
	}



	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
	cout << endl << endl;

	Sleep(3000);
}

void AStar::Dijkstra(cordScr start, cordScr dest) {
	return;
}

int AStar::getPath() {
	//aStarSearch(start, finish)
	return this->direction;
}

void AStar::getPathMap() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << path[i][j];
		}
		cout << endl;
	}
}

AStar::AStar(Field* world, Unit* unit, int h, int w, cordScr start, cordScr dest) : FastPath(world, unit) {
	rows = h;
	columns = w;
	this->start.x = start.y;
	this->start.y = start.x;
	this->dest.x = dest.y;
	this->dest.y = dest.x;
	cellDetails = new cell * [rows];
	grid = new int* [rows];
	closedList = new bool* [rows];
	for (int i = 0; i < rows; i++) {
		cellDetails[i] = new cell[columns];
		grid[i] = new int[columns];
		closedList[i] = new bool[columns];
		for (int j = 0; j < columns; j++) {
			closedList[i][j] = false;
			grid[i][j] = 1; //-----------------------------
		}
	}
}

AStar::~AStar() {
	for (int i = 0; i < rows; i++)
	{
		delete[] grid[i];
		delete[] closedList[i];
		delete[] cellDetails[i];
	}
	delete[] grid;
	delete[] closedList;
	delete[] cellDetails;
}
bool AStar::isValid(int row, int col) {
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < rows) &&
		(col >= 0) && (col < columns);
}

// check whether the given cell is 
// blocked or not 
bool AStar::isUnBlocked(int row, int col) {
	// Returns true if the cell is not blocked else false 
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

// check whether destination cell has 
// been reached or not 
bool AStar::isDestination(int row, int col, cordScr dest) {
	//printf("%d %d %d %d", row, col, dest.x, dest.y);
	if (row == dest.x && col == dest.y)
		return (true);
	else
		return (false);
}

// 
double AStar::calculateHValue(int row, int col, cordScr dest) {
	// Return using the distance formula of Pifagor :)
	return ((double)sqrt((row - dest.x) * (row - dest.x)
		+ (col - dest.y) * (col - dest.y)));
}

// trace the path from the source 
// to destination 
cordScr AStar::tracePath(cordScr dest) {
	//printf("\nThe Path is \n");
	int row = dest.x;
	int col = dest.y;
	cordScr nextCord;
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
	pair<int, int> p = Path.top();
	while (!Path.empty()) Path.pop();
	//printf("%d %d\n", p.first, p.second);
	nextCord.x = p.second;
	nextCord.y = p.first;
	// ���� ����� �������� ����� ���� �������� � �������� �����������
	return nextCord;
}

// find the shortest path between 
// a given source cell to a destination cell
void AStar::aStarSearch()
{
	bool isUnreachable = false;
	// If the source is out of range 
	if (isValid(start.x, start.y) == false)
	{
		//printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range 
	if (isValid(dest.x, dest.y) == false)
	{
		//printf("Destination is invalid\n");
		return;
	}


	// Either the source or the destination is blocked 
	if (isUnBlocked(start.x, start.y) == false ||
		isUnBlocked(dest.x, dest.y) == false)
	{
		//printf("Source or the destination is blocked\n");
		isUnreachable = true;
	}
	// If the destination cell is the same as source cell 
	if (isDestination(start.x, start.y, dest) == true)
	{
		//printf("We are already at the destination\n");
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

		// Check all 8 succesors of current node

		if (isValid(i - 1, j) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i - 1, j, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				//printf("The destination cell is found\n");
				//direction = 1;
				nextCord = tracePath(dest);
				foundDest = true;
				return;
			}
			else if (closedList[i - 1][j] == false &&
				isUnBlocked(i - 1, j) == true)
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
			if (isDestination(i + 1, j, dest) == true && !isUnreachable)
			{
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				//printf("The destination cell is found\n");
				//direction = 2;
				nextCord = tracePath(dest);
				foundDest = true;
				return;
			}
			else if (closedList[i + 1][j] == false &&
				isUnBlocked(i + 1, j) == true)
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
			if (isDestination(i, j + 1, dest) == true && !isUnreachable)
			{
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				//printf("The destination cell is found\n");
				nextCord = tracePath(dest);
				//direction = 3;
				foundDest = true;
				return;
			}
			else if (closedList[i][j + 1] == false &&
				isUnBlocked(i, j + 1) == true)
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
		if (isValid(i, j - 1) == true && !isUnreachable)
		{
			if (isDestination(i, j - 1, dest) == true)
			{
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				//printf("The destination cell is found\n");
				nextCord = tracePath(dest);
				//direction = 4;
				foundDest = true;
				return;
			}

			else if (closedList[i][j - 1] == false &&
				isUnBlocked(i, j - 1) == true)
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
			if (isDestination(i - 1, j + 1, dest) == true && !isUnreachable)
			{
				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
				//printf("The destination cell is found\n");
				nextCord = tracePath(dest);
				//direction = 5;
				foundDest = true;
				return;
			}
			else if (closedList[i - 1][j + 1] == false &&
				isUnBlocked(i - 1, j + 1) == true)
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
			if (isDestination(i - 1, j - 1, dest) == true && !isUnreachable)
			{
				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
				//printf("The destination cell is found\n");
				nextCord = tracePath(dest);
				//direction = 6;
				foundDest = true;
				return;
			}

			else if (closedList[i - 1][j - 1] == false &&
				isUnBlocked(i - 1, j - 1) == true)
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
			if (isDestination(i + 1, j + 1, dest) == true && !isUnreachable)
			{
				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
				//printf("The destination cell is found\n");
				nextCord = tracePath(dest);
				//direction = 7;
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j + 1] == false &&
				isUnBlocked(i + 1, j + 1) == true)
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
			if (isDestination(i + 1, j - 1, dest) == true && !isUnreachable)
			{
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
				//printf("The destination cell is found\n");
				nextCord = tracePath(dest);
				//direction = 8;
				foundDest = true;
				return;
			}
			else if (closedList[i + 1][j - 1] == false &&
				isUnBlocked(i + 1, j - 1) == true)
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
	if (foundDest == false) {
		//printf("Failed to find the Destination Cell\n");
		//direction = 0;

		double minHWalue = FLT_MAX;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (cellDetails[i][j].h < minHWalue && cellDetails[i][j].h > 0) {
					minHWalue = cellDetails[i][j].h;
				}
			}
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (closedList[i][j] == true && cellDetails[i][j].h == minHWalue) {
					dest.x = i;
					dest.y = j;
					nextCord = tracePath(dest);
					return;
				}
			}
		}
		//cout << minHWalue;*/
	}
	return;
}