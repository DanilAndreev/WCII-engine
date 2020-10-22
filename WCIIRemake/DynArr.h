#pragma once
#include "pch.h"
#include "Obj.h"
#include <Windows.h>

//Динамический массив


class DynArr : public Obj {
	protected:
		Obj **array;
		int len;
		bool notBusy;
	public:
		DynArr();
		virtual ~DynArr();
		void freeItems(); // удалить все елементы внутри массива (осторожно, указатели останутся!!!)
		int count(); // возвращает длину массива
		Obj *get(int index); // возвращает указатель на index-овый елемент
		int search(Obj * target); // возвращает индекс елемента в массиве(передаем указатель на искомый елемент) , если не нащел то -1;
		virtual bool add(Obj* source); // добавить даный елемент в массив
		virtual void delById(int index); // удалить елемент по указанному индексу из массива (не из памяти, только с массива!!!)
		virtual int del(Obj* target); // удалить указанный елемент из массива (передаем указатель на целевой елемент) (не из памяти, только с массива!!!)
		void clear();
	private:
		bool waitThreadQueue();
};

