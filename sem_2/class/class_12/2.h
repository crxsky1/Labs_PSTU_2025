#pragma once
#include "Header.h"

void number_2()
{
	multiset<Tim> lst;
	Tim temp;
	int size;
	cout << "count: "; cin >> size;
	for (int i = 0; i < size; i++)
		lst.insert(temp.randomGener());
	cout << "deque:" << endl;
	Show(lst);
	cout << "insert:" << endl;
	Insert(lst);
	cout << "deque:" << endl;
	Show(lst);
	cout << "delete" << endl;
	DelElem(lst,size+1);
	cout << "deque:" << endl;
	Show(lst);
	cout << "subtract." << endl;
	plusMinMax(lst);
	cout << "deque:" << endl;
	Show(lst);
	return;
}