#pragma once
#include "DynArr.h"
class Queue : private DynArr {
	private:
		DynArr* array;
	public:
		Queue();
		virtual ~Queue();
		void put(Obj * input);
		Obj * get();
		int len();
		bool isEmpty();
};

