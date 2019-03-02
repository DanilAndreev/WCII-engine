#include "pch.h"
#include "Threadable.h"



Threadable::Threadable() {

}


Threadable::~Threadable() {
	_endthread();
}

HANDLE Threadable::startThread() {
	receiveMessageHandle = (HANDLE)_beginthreadex(0, 0, &Threadable::receiveMessageThread, this, 0, 0);
	return receiveMessageHandle;
}

void Threadable::threadFunction() {
	cout << "Unreloaded basic thread function" << endl;
}

unsigned int __stdcall Threadable::receiveMessageThread(void * p_this) {
	Threadable* p_Threadable = static_cast<Threadable*>(p_this);
	p_Threadable->threadFunction();
	return 0;
}
