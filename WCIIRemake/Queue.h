#pragma once
#include "DynArr.h"

class Queue : private DynArr {
	private:
		DynArr* array;
	public:
		Queue();
		virtual ~Queue();
		void put(Obj * input); // добавить елемент в очередь (push)
		Obj * get(); // вытянуть елемент с очереди (pop)
		int len(); // вернуть длину очереди(колическво елементов)
		bool isEmpty(); // возвращает истину если очередь пустая, ложь если есть хотя-бы один елемент
};

