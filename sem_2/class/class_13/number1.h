#pragma once
#include"header.h"

//åäèíñòâåííîå íîðìàëüíîå çàäàíèå âî âñåé ëàáå
void Insert(deque<Time>& lst)
{
	Time key;
	int start;
	cout << "chislo: "; cin >> key;
	cout << "pos: "; cin >> start;
	lst.insert(lst.begin() + start, key);
}

void searchAndDel(deque<Time>& lst)			//èùåì è óäàëÿåì
{
	Time y;
	cout << "Ââåäèòå äàííûå äëÿ óäàëåíèÿ: "; cin >> y;
	int min, max;
	cout << "Ââåäèòå äèàïàçîí äëÿ ïîèñêà:\n" << "min: "; cin >> min;
	cout << "max: "; cin >> max;					//ìîæíî çàäàòü äèàïàçîí, ðàáîòàåò ñ èíäåêñàìè
	auto left = lst.begin(); auto right = lst.begin();
	advance(left, min);			//ñìåùàåì èòåðàòîðû, ÷òîáû óñòàíîâèò äèàïàçîí 
	advance(right, max);
	lst.erase(remove_if(left, right, [&y](Time& x)	//óäàëåì åñëè ââåäåííîå ÷èñëî ñîâïàäàåò ñ òåì, íà êîòîðîå ìû óêàçûâàåì
		{return x == y; }));		//àíîíèìíàÿ ôóíêöèÿ
}

void plusMinMax(deque<Time>& lst)		//äîáàâëåíèå ê êàæäîìó ýëåìåíòó ìèí è ìàêñ çíà÷åíèÿ
{
	Time min = *min_element(lst.begin(), lst.end());		//íàõîäèì ìèí è ìàêñ 
	Time max = *max_element(lst.begin(), lst.end());
	cout << "min: " << min << endl << "max: " << max << endl;
	for_each(lst.begin(), lst.end(),		//ïðîõîäèì ïî âñåìó ñïèñêó
		[&min, &max](Time& this_el) {this_el = this_el - max + min; });		//ëÿìáäà-âûðàæåíèå - êîòîðîå äîáàâëÿåò ê êàæäîìó ýëåìåíòó ìèí è ìàêñ
}

void number1()			//ôóíêöèÿ äëÿ óïðàâëåíèÿ, çäåñò íè÷åãî îñîáåííîãî, òîëüêî â êîíöå êîììû
{
	Time p;
	deque<Time> lst;
	int n;
	cout << "count: "; cin >> n;
	for (int i = 0; i < n; i++)
		lst.push_back(p.randomGener());
	cout << endl << "Ïîëó÷åííûé list:" << endl; n = 0;
	for (auto& i : lst)
		cout << ++n << ". " << i << endl;
	cout << endl << "Íàéäåì ñðåäíåå àðèôìèòè÷åñêîå çíà÷åíèå è äîáàâèì åãî â êîíòåéíåð." << endl;
	Insert(lst);
	cout << endl << "Ïîëó÷åííûé list:" << endl; n = 0;
	for (auto& i : lst)
		cout << ++n << ". " << i << endl;
	cout << endl << "Çàäàäèì äèàïàçîí è óäàëèì äàííûå èç êîíòåéíåðà â äàííîì äèàïàçîíå." << endl;
	searchAndDel(lst);
	cout << endl << "Ïîëó÷åííûé list:" << endl; n = 0;
	for (auto& i : lst)
		cout << ++n << ". " << i << endl;
	cout << endl << "Ê êàæäîìó ýëåìåíòó êîíòåéíåðà äîáàâèì max è min ýëåìåíò êîíòåéíåðà." << endl;
	plusMinMax(lst);
	cout << endl << "Ïîëó÷åííûé list:" << endl; n = 0;
	for (auto& i : lst)
		cout << ++n << ". " << i << endl;
	cout << endl << "Íàéäåì â äàííîì êîíòåéíåðå åëåìåíò è åãî èíäåêñ." << endl;
	cout << "Ââåäèòå ýëåìåíò äëÿ ïîèñêà: "; cin >> p;
	auto it = find(lst.begin(), lst.end(), p);
	if (it != lst.end())
		cout << "Íîìåð ýëåìåíòà: " << distance(lst.begin(), it) + 1 << "\tÝëåìåíò: " << p;
	else
		cout << "Ýëåìåíò íå íàéäåí." << endl;
	cout << endl << "Îòñîðòèðóåì êîíòåéíåð ïî âîçðàñòàíèþ." << endl;
	for (auto& i : lst)
		cout << ++n << ". " << i << endl;
	cout << endl << "Îòñîðòèðóåì êîíòåéíåð ïî óáûâàíèþ." << endl;
	for (auto& i : lst)
		cout << ++n << ". " << i << endl;
}