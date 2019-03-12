#pragma once
#include "Obj.h"
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <string>

using namespace std;

typedef unsigned long long ThreadId;

class Threadable : public Obj{
protected: 
//	Obj* parent;
//	HANDLE hThread;
	ThreadId threadId;
	bool isRunning;
	HANDLE threadHandle;
public:
	Threadable();
	virtual ~Threadable();
	bool setDescriptor(ThreadId id);
	ThreadId getDescriptor();
	void startThread();
	void stopThread();
protected:
	void threadController();
	virtual void threadFunction();
private:
	static unsigned int __stdcall receiveMessageThread(void* p_this);
};






