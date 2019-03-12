#include "pch.h"
#include "Threadable.h"
#include "ThreadDescriptor.h"

extern ThreadDescriptor* gameThreads;
extern Console* defaultConsole;

Threadable::Threadable() {
	this->isRunning = true;
	gameThreads->addThread(this);
}


Threadable::~Threadable() {
	gameThreads->delById(gameThreads->getIndexByDescriptror(this->getDescriptor()));
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
	_endthreadex(0);
	CloseHandle(threadHandle);
}

void Threadable::threadFunction() {
	defaultConsole->error("Unreloaded basic thread function");
}



unsigned int __stdcall Threadable::receiveMessageThread(void * p_this) {
	Threadable* p_Threadable = static_cast<Threadable*>(p_this);
	p_Threadable->threadController();
	delete p_Threadable;

	return 0;
}
