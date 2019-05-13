#pragma once
#include "Command_c.h"
#include "ID.h"
#include <iostream>
#include <string>

using namespace std;



class Obj{
	protected:
		const char *className;
		static ID freeID;
		string description;
	protected:
		bool selected;
		ID id;
	public:
		Obj();
		Obj(const char* className);
		virtual ~Obj();
		void setDescription(string description);
		string getDescription();
		ID getId();
		const char* getClassName(); // return the class name
		virtual void operateEvent(Command_c* command);
	protected:
		void setClassName(const char* className); // write down the class name
	private:
		ID getFreeId();
};

