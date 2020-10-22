#pragma once
#include "Command_c.h"
#include "ID.h"
#include "Eventable.h"
#include <iostream>
#include <string>
using namespace std;



class Obj : public Eventable {
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
	protected:
		void setClassName(const char* className); // write down the class name
	private:
		ID getFreeId();
};

