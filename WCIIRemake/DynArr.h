#pragma once
#include "pch.h"
#include "Obj.h"

//Динамический массив

class DynArr : public Obj {
	private:
		Obj **array;
		int len;
	public:
		DynArr();
		virtual ~DynArr();
		void freeItems(); // удалить все елементы внутри массива (осторожно, указатели останутся!!!)
		int count(); // возвращает длину массива
		Obj *get(int index); // возвращает указатель на index-овый елемент
		int search(Obj * target); // возвращает индекс елемента в массиве(передаем указатель на искомый елемент)
		void add(Obj* source); // добавить даный елемент в массив
		void delById(int index); // удалить елемент по указанному индексу из массива (не из памяти, только с массива!!!)
		int del(Obj* target); // удалить указанный елемент из массива (передаем указатель на целевой елемент) (не из памяти, только с массива!!!)
};

