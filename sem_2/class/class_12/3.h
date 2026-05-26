#pragma once
#include "Header.h"

template <typename T>
class Myvector
{
private:
	multiset<T> lst;
	T SearchMidVal();
	int _size;

public:
	Myvector() { _size = 0; }
	Myvector(int n);
	~Myvector() {};
	void Print();
	void PushMidVal();
	void DelElem();
	int size() { return this->_size; }
	void plusMinMax();
};

template<class T>
Myvector<T>::Myvector(int n)
{
	T a;
	cout << "Ââîäèòå äàííûå: " << endl;
	for (size_t i = 0; i < n; i++)
	{
		cout << i << ". ";
		cin >> a;
		this->lst.insert(a);
	}
	_size = n;
}

template<class T>
void Myvector<T>::Print()
{
	int j = 0;
	for (const auto& i : lst)
		cout << j++ << ")\t" << i << endl;
}

template<class T>
T Myvector<T>::SearchMidVal()
{
	T mid = 0;
	for (auto& i : lst)
		mid = mid + i;
	return mid / lst.size();
}

template<typename T>
void Myvector<T>::PushMidVal()
{
	lst.insert(SearchMidVal());
	this->_size = lst.size();
}

template<typename T>
void Myvector<T>::DelElem()
{
	T key;
	int start, end;
	auto it_start = lst.begin(), it_end = lst.begin();
	cout << "key: "; cin >> key;
	cout << "pos: "; cin >> start >> end;
	if (start > end) std::swap(start, end);
	std::advance(it_start, start);
	std::advance(it_end, end);
	do
	{
		if (*it_start == key) it_start = lst.erase(it_start);
		else ++it_start;
	} while (it_start != it_end);
	this->_size = lst.size();
}

template<typename T>
void Myvector<T>::plusMinMax()
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
	cout << "max elem: " << loc_max << endl;
	for (auto& i : lst)
	{
		i = i - loc_max + loc_min;
	}
}


void number_3()
{
	int n;
	cout << "count: "; cin >> n;
	Myvector<Tim> lst(n);
	cout << "deque:" << endl;
	lst.Print();
	cout << "Äîáàâèì ñðåäíåå àðèôìèòè÷åñêîå çíà÷åíèå ñïèñêà â êîíåö ôàéëà:" << endl;
	lst.PushMidVal();
	cout << "Ïîëó÷åííûé ñïèñîê:" << endl;
	lst.Print();
	cout << "Óäàëèì ýëåìåíò ïî çíà÷åíèþ â çàäàííîì äèàïàçîíå." << endl;
	lst.DelElem();
	cout << "Ïîëó÷åííûé ñïèñîê:" << endl;
	lst.Print();
	cout << "Äîáàâèì ñóììó min è max ýëåìåíòîâ ê êàæäîìó ýëåìåíòó." << endl;
	lst.plusMinMax();
	cout << "Ïîëó÷åííûé ñïèñîê:" << endl;
	lst.Print();
}