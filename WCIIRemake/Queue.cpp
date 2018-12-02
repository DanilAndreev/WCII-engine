#include "pch.h"
#include "Queue.h"


Queue::Queue() {
	array = new DynArr();
}


Queue::~Queue() {
	delete [] array;
}

void Queue::put(Obj* input) {
	array->add(input);
}

Obj* Queue::get() {
	Obj* temp;
	if (array->count() > 0) {
		temp = array->get(0);
		array->delById(0);
		return temp;
	}
	return NULL;
}

int Queue::len() {
	return array->count();
}

bool Queue::isEmpty() {
	if (array->count()) {
		return false;
	}
	return true;
}