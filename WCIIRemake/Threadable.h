#pragma once
#include "Obj.h"
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <string>

using namespace std;


class Threadable{
private: 
	//Obj* unit;
	HANDLE hThread;
public:
	Threadable();
	virtual ~Threadable();
	HANDLE startThread();
private:
	virtual void threadFunction();
	static unsigned int __stdcall receiveMessageThread(void* p_this);
};






