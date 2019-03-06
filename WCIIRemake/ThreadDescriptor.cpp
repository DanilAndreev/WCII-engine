#include "pch.h"
#include "ThreadDescriptor.h"

ThreadDescriptor* gameThreads;
ThreadId ThreadDescriptor::freeId = 0;

ThreadDescriptor::ThreadDescriptor() {
	if (gameThreads == NULL) {
		gameThreads = this;
	}
	DynArr::DynArr();
}

ThreadDescriptor::~ThreadDescriptor() {
}

bool ThreadDescriptor::add(Threadable* thread) {
	if (this->search(thread) == -1) {
		return false;
	}
	thread->setDescriptor(getFreeId());
	DynArr::add((Obj*)thread);
	return true;
}

bool ThreadDescriptor::stopThread(ThreadId targetDescriptor) {
	for (int i = 0; i < this->len; i++) {
		if ( this->get(i)->getDescriptor() == targetDescriptor ) {
			Threadable* thread = this->get(i);
			DynArr::delById(i); //REPAIR ----------------------------------------------------------------------
			delete thread;
			return true;
		}
	}
	return false;
}

Threadable * ThreadDescriptor::getThread(ThreadId targetDescriptor) {
	for (int i = 0; i < this->len; i++) {
		if (this->get(i)->getDescriptor() == targetDescriptor) {
			return this->get(i);
		}
	}
	return NULL;
}

ThreadId ThreadDescriptor::getFreeId() {
	freeId++;
	return freeId;
}

Threadable * ThreadDescriptor::get(ThreadId index) {
	return (Threadable*)(DynArr::get(index));
}
