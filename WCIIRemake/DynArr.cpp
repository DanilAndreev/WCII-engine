#include "pch.h"
#include "DynArr.h"

const int DynArrThreadTimeout = 16;

DynArr::DynArr() {
	len = 0;
	array = new Obj*[len];
	notBusy = true;
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
	if (index < this->count()) {
		return array[index];
	}
	return NULL;
}



int DynArr::search(Obj *target) {
	for (int i = 0; i < this->count(); i++) {
		if (this->get(i) == target) {
			return i;
		}
	}
	return -1;
}

bool DynArr::waitThreadQueue() {
	for (int i = 0; i < DynArrThreadTimeout; i++) {
		if (notBusy) {
			return true;
		}
		Sleep(10);
	}
	return false;
}

bool DynArr::add(Obj* source) {
	if (!waitThreadQueue()) {
		cout << "Failed to add element to DynArr" << endl;
		return false;
	}

	notBusy = false;

	Obj **newarray = new Obj*[len + 1];
	memcpy(newarray, array, len * sizeof(Obj*));
	len++;
	newarray[len - 1] = source;
	delete[] array;
	array = newarray;

	notBusy = true;
	return true;
}


int DynArr::del(Obj* target) {
	if (!waitThreadQueue()) {
		cout << "Failed to add element to DynArr" << endl;
		return 0;
	}

	notBusy = false;


	int id = this->search(target);
	if (id == -1) {
		notBusy = true;
		return 0;
	}
	delById(id);

	notBusy = true;
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
	memcpy(newarray + index, array, (len - (index)) * sizeof(Obj*));
	delete[] array;
	array = newarray;
}

