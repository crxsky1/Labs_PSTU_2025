#pragma once
#include "Header.h"

template <typename T>
void Show(multiset<T> lst);

template<class T>
void Insert(multiset<T>& lst);

template<class T>
void DelElem(multiset<T>& lst,int o);

void number_1();

template<class T>
void plusMinMax(multiset<T>& lst);


void number_1()
{
	multiset<double> lst;
	int size;
	cout << "count: "; cin >> size;
	for (int i = 0; i < size; i++)
		lst.insert((double((rand() % 10000 - 5000)) / 100));
	cout << "deque:" << endl;
	Show(lst);
	cout << "podstavka:" << endl;
	Insert(lst);
	cout << "deque:" << endl;
	Show(lst);
	cout << "ydalenie" << endl;
	DelElem(lst,size + 1);
	cout << "deque:" << endl;
	Show(lst);
	cout << "subtract" << endl;
	plusMinMax(lst);
	cout << "deque:" << endl;
	Show(lst);
	return;
}

template<class T>
void plusMinMax(multiset<T>& lst)
{
	T loc_min = 0, loc_max = 0;
	for (auto& i : lst)
	{
		if (i < loc_min)
		{
			loc_min = i;
		}
		else if (i > loc_max)
		{
			loc_max = i;
		}
	}
	cout << "min element: " << loc_min << endl;
	cout << "max element: " << loc_max << endl;
	loc_min = loc_max - loc_min;
	for (auto& i : lst)
	{
		i = i + loc_min;
	}
}

template<typename T>
void Show(multiset<T> lst)
{
	int j = 0;
	for (auto& i : lst)
		cout << j++ << ")\t" << i << endl;
}

template<class T>
void Insert (multiset<T>& lst)
{
	T key;
	int start;
	cout << "chislo: "; cin >> key;
	cout << "pos: "; cin >> start;
	lst.insert(lst.begin() + start, key);
}


template<class T>
void DelElem(multiset<T>& lst,int o)
{
	T key;
	int start=0, end=o;
	auto it_start = lst.begin(), it_end = lst.begin();
	cout << "key: "; cin >> key;
	std::advance(it_start, start);
	std::advance(it_end, end);
	do
	{
		if (*it_start == key) it_start = lst.erase(it_start);
		else ++it_start;
	} while (it_start != it_end);
}