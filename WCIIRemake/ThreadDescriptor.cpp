#include "pch.h"
#include "ThreadDescriptor.h"

ThreadDescriptor* gameThreads;
ThreadId ThreadDescriptor::freeId = 0;
extern Console* defaultConsole;

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
/*
	int index = getIndexByDescriptror(targetDescriptor);
	if (index != -1) {
		HANDLE handle = getT(index)->getHandle();
		getT(index)->stopThread();
		defaultConsole->warning("Waiting for thread finish");
		WaitForSingleObject(handle, INFINITE);
		return true;
	}
	return false;
*/
	return stopThread(targetDescriptor, "");
}

bool ThreadDescriptor::stopThread(ThreadId targetDescriptor, string message) {
	int index = getIndexByDescriptror(targetDescriptor);
	if (index != -1) {
		HANDLE handle = getT(index)->getHandle();
		getT(index)->stopThread();
		if (message.length() != 0) {
			//			defaultConsole->warning("Waiting for thread finish");
			cout << "Waiting for thread " << message << " finish" << endl;
		}
		WaitForSingleObject(handle, INFINITE);
		return true;
	}
	return false;
}

bool ThreadDescriptor::stopThreadNoWait(ThreadId targetDescriptor) {
	int index = getIndexByDescriptror(targetDescriptor);
	if (index != -1) {
		getT(index)->stopThread();
		return true;
	}
	return false;
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
	freeId++;
	return freeId;
}

Threadable * ThreadDescriptor::getT(ThreadId index) {
	return (Threadable*)(get(index));
}
