#include "pch.h"
#include "AStar.h"



AStar::AStar() {
}

DynArr* AStar::Dejkstra(Unit* unit) {
	Queue* bunch = new Queue();
	DynArr* passes = new DynArr();


	bunch->put(unit);
	AStarNode* temp1 = new AStarNode(NULL, unit->getCord());
	passes->add((Obj*)temp1);


	while (bunch->isEmpty() == true) {
		Unit* temp = (Unit*)bunch->get();
		for (int i = 0; i < members->count(); i++) {
			if ( abs((((Screenable*)(members->get(i)))->getCord()).x - ((Screenable*)temp)->getCord().x ) == 1) {
				bunch->put((Unit*)(members->get(i)));
				AStarNode* temp1 = new AStarNode(temp->getCord(), ((Unit*)(members->get(i))) );
				passes->add((Obj*)temp1);
			}
		}
	}
	delete bunch;
	return passes;
}

DynArr* AStar::findPath(DynArr* passes, cordScr targetCords) {
	AStarNode* temp;
	int i = passes->count();
	do {
		i--;
		temp = (AStarNode*)(passes->get(i));
		temp = temp->cameFrom;
		


	} while
}


AStar::~AStar() {
	printf("HELLO");

}


