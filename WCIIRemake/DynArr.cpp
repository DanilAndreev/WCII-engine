#include "pch.h"
#include "DynArr.h"


DynArr::DynArr() {
	len = 0;
	array = new Obj*[len];
}


DynArr::~DynArr() {
	delete[] array;
}

void DynArr::freeItems() {
	for (int i = 0; i < len; i++)
		delete array[i];
}

int DynArr::count() {
	return len;
}

Obj* DynArr::get(int index) {
	return array[index];
}

int DynArr::search(Obj *target) {
	for (int i = 0; i < this->count(); i++) {
		if (this->get(i) == target) {
			return i;
		}
	}
	return -1;
}

void DynArr::add(Obj* source) {
	Obj **newarray = new Obj*[len + 1];
	memcpy(newarray, array, len * sizeof(Obj*));
	len++;
	newarray[len - 1] = source;
	delete[] array;
	array = newarray;
}


int DynArr::del(Obj* target) {
	int id = this->search(target);
	if (id == -1) {
		return 0;
	}
	delById(id);
	return 1;
}

void DynArr::delById(int index) {
	if (index >= len) {
		return;
	}
	Obj **newarray = new Obj*[--len];
	if (index > 0) {
		memcpy(newarray, array, index*sizeof(Obj*));
	}
	memcpy(newarray + index, array, (len - (index)) * sizeof(Obj*)); // maybe change to index + 1
	delete[] array;
	array = newarray;
}

