#pragma once
#include "pch.h"
#include "Obj.h"

class DynArr : public Obj {
	private:
		Obj **array;
		int len;
	public:
		DynArr();
		virtual ~DynArr();
		void freeItems();
		int count();
		Obj *get(int index);
		int search(Obj * target);
		void add(Obj* source);
		void delById(int index);
		int del(Obj* target);
};

