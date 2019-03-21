#pragma once
#include "Command_c.h"
#include "ID.h"
#include <iostream>

using namespace std;



class Obj{
	private:
		const char *className;
		static ID freeID;
	protected:
		bool selected;
		ID id;
	public:
		Obj();
		Obj(const char* className);
		virtual ~Obj();
		ID getId();
		const char* getClassName(); // return the class name
		virtual void operateEvent(Command_c* command);
	protected:
		void setClassName(const char* className); // write down the class name
	private:
		ID getFreeId();
};

