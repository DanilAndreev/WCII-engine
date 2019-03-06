#pragma once
#include "DynArr.h"
#include "Threadable.h"



class ThreadDescriptor : protected DynArr {
private:
	static ThreadId freeId;
public:
	ThreadDescriptor();
	~ThreadDescriptor();
	bool add(Threadable* thread);
	bool stopThread(ThreadId targetDescriptor);
	Threadable* getThread(ThreadId targetDescriptor);
private:
	static ThreadId getFreeId();
	inline Threadable* get(ThreadId index);
};

