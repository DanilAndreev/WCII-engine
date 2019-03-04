#pragma once
#include "Obj.h"
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <string>

using namespace std;

typedef unsigned long long ThreadId;

class Threadable{
private: 
	Obj* parent;
	HANDLE hThread;
	ThreadId threadId;
public:
	Threadable();
	virtual ~Threadable();
	HANDLE startThread();
private:
	virtual void threadFunction();
	static unsigned int __stdcall receiveMessageThread(void* p_this);
};






