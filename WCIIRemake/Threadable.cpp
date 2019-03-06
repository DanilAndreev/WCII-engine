#include "pch.h"
#include "Threadable.h"
#include "ThreadDescriptor.h"

extern ThreadDescriptor* gameThreads;

Threadable::Threadable() {
	this->isRunning = true;
	startThread();
}


Threadable::~Threadable() {

	this->stopThread();
	Sleep(5);
	CloseHandle(hThread);
}

bool Threadable::setDescriptor(ThreadId id) {
	this->threadId = id;
	return true;
}

ThreadId Threadable::getDescriptor() {
	return this->threadId;
}

void Threadable::startThread() {
	this->threadHandle = (HANDLE)_beginthreadex(0, 0, &Threadable::receiveMessageThread, this, 0, 0);
}

void Threadable::stopThread() {
	this->isRunning = false;
}

void Threadable::threadController() {
	threadFunction();
	gameThreads->stopThread(this->threadId);
}

void Threadable::threadFunction() {
	cout << "Unreloaded basic thread function" << endl;
}



unsigned int __stdcall Threadable::receiveMessageThread(void * p_this) {
	Threadable* p_Threadable = static_cast<Threadable*>(p_this);
	p_Threadable->threadController();
	_endthread();
	
	return 0;
}
