#pragma once
#include "pch.h"
#include "Obj.h"
#include <Windows.h>

//������������ ������


class DynArr : public Obj {
	protected:
		Obj **array;
		int len;
		bool notBusy;
	public:
		DynArr();
		virtual ~DynArr();
		void freeItems(); // ������� ��� �������� ������ ������� (���������, ��������� ���������!!!)
		int count(); // ���������� ����� �������
		Obj *get(int index); // ���������� ��������� �� index-���� �������
		int search(Obj * target); // ���������� ������ �������� � �������(�������� ��������� �� ������� �������) , ���� �� ����� �� -1;
		virtual bool add(Obj* source); // �������� ����� ������� � ������
		virtual void delById(int index); // ������� ������� �� ���������� ������� �� ������� (�� �� ������, ������ � �������!!!)
		virtual int del(Obj* target); // ������� ��������� ������� �� ������� (�������� ��������� �� ������� �������) (�� �� ������, ������ � �������!!!)
		void clear();
	private:
		bool waitThreadQueue();
};

