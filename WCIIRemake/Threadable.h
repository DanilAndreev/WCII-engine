#pragma once
#include "Obj.h"
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <string>

using namespace std;


class Threadable : public Obj{
private: 
	//Obj* unit;
	HANDLE receiveMessageHandle;
public:
	Threadable();
	virtual ~Threadable();
	HANDLE startThread();
private:
	void threadFunction();
	static unsigned int __stdcall receiveMessageThread(void* p_this);
};






