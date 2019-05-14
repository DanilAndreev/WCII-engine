#pragma once
#include "DynArr.h"
#include "Threadable.h"



class ThreadDescriptor : public DynArr {
private:
	static ThreadId freeId;
public:
	ThreadDescriptor();
	~ThreadDescriptor();
	ThreadId addThread(Threadable* thread);
	int getIndexByDescriptror(ThreadId targetDescriptor); // returns array index of thread or -1 if not found
	HANDLE stopThread(ThreadId targetDescriptor);
//	HANDLE stopThread(ThreadId targetDescriptor, string message);
//	bool stopThreadNoWait(ThreadId targetDescriptor);
	Threadable* getThread(ThreadId targetDescriptor);
private:
	static ThreadId getFreeId();
	inline Threadable* getT(ThreadId index);
};

