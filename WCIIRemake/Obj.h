#pragma once
#include "Command_c.h"


class Obj {
	private:
		const char *className;
	protected:
		bool selected;
	public:
		Obj();
		Obj(const char* className);
		virtual ~Obj();
		const char* getClassName(); // возвращает имя класса
		virtual void operateEvent(Command_c command);
	protected:
		void setClassName(const char* className); // записать имя класса(для наследования)
};

