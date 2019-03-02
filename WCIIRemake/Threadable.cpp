#include "pch.h"
#include "Threadable.h"



Threadable::Threadable() {
}


Threadable::~Threadable() {
	CloseHandle(hThread);
}

HANDLE Threadable::startThread() {
	hThread = (HANDLE)_beginthreadex(0, 0, &Threadable::receiveMessageThread, this, 0, 0);
	return hThread;
}

void Threadable::threadFunction() {
	cout << "Unreloaded basic thread function" << endl;
}

unsigned int __stdcall Threadable::receiveMessageThread(void * p_this) {
	Threadable* p_Threadable = static_cast<Threadable*>(p_this);
	p_Threadable->threadFunction();
	_endthread();
	return 0;
}
