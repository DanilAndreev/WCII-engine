#include "pch.h"
#include "ThreadDescriptor.h"

ThreadDescriptor* gameThreads;
ThreadId ThreadDescriptor::freeId = 0;

ThreadDescriptor::ThreadDescriptor() {
	if (gameThreads == NULL) {
		gameThreads = this;
	}
}

ThreadDescriptor::~ThreadDescriptor() {
}

ThreadId ThreadDescriptor::addThread(Threadable* thread) {
	if (this->search(thread) != -1) {
		return 0;
	}
	ThreadId descriptor = getFreeId();
	thread->setDescriptor(descriptor);
	DynArr::add((Obj*)thread);
	return descriptor;
}

int ThreadDescriptor::getIndexByDescriptror(ThreadId targetDescriptor) {
	for (int i = 0; i < this->len; i++) {
		if (this->getT(i)->getDescriptor() == targetDescriptor) {
			return i;
		}
	}
	return -1;

}

bool ThreadDescriptor::stopThread(ThreadId targetDescriptor) {
	int index = getIndexByDescriptror(targetDescriptor);
	if (index != -1) {
		getT(index)->stopThread();
		return true;
	}
	return false;
/*
	Threadable* thread = this->get(i);
	DynArr::delById(i); //REPAIR ----------------------------------------------------------------------
	delete thread;
*/
}

Threadable * ThreadDescriptor::getThread(ThreadId targetDescriptor) {
	for (int i = 0; i < this->len; i++) {
		if (this->getT(i)->getDescriptor() == targetDescriptor) {
			return this->getT(i);
		}
	}
	return NULL;
}

ThreadId ThreadDescriptor::getFreeId() {
	cout << "Incrementing free id" << endl;
	freeId++;
	return freeId;
}

Threadable * ThreadDescriptor::getT(ThreadId index) {
	return (Threadable*)(get(index));
}
