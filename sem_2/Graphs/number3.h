#pragma once
#include"header.h"

static int shet = 0;		//ãåíåðàòîð êëþ÷åé

void print(map<int, Time>& mp)		//ôóíêöèÿ âûâîäà ñëîâàðÿ
{
	cout << endl << "Ïîëó÷åííûé map:" << endl;
	for (auto& i : mp)
		cout << i.first << ". " << i.second << endl;
}

void plus_mid(map<int, Time>& mp)	//ôóíêöèÿ äîáàâëÿåò ñðåäíåå àðèôìèòè÷åñêîå
{
	Time midl(0, 0);				//ÍÎ!!!
	for (auto& i : mp)				//òàê êàê ñ êîíòåéíåðîì map íå ðàáîòàåò áèáëèëòåêà algorithm, òî÷íåå áîëüøèíñòâî ìåòîäîâ
		midl = midl + i.second;		//òóò ìû âñå äåëàåì ðó÷êàìè ÷åðåç îáû÷íûå öèêëû
	mp.emplace(++shet, midl / mp.size());	//âïðèíöèïå òàê â íîìåðå 3 âåçäå
}

void searchAndDel(map<int, Time>& mp)		//óäàëåíèå ïî êëþ÷ó
{											//íè÷åãî èíòåðåñíîãî, ïðîñòî âûçîâ ìåòîäà
	int y;
	cout << "Ââåäèòå êëþ÷ äëÿ óäàëåíèÿ (int): "; cin >> y;
	mp.erase(y);
}

void plusMinMax(map<int, Time>& mp)			//äîáàâëåíèå ê êàæäîìó ýëåìåíòó ìèíèìàëüíîãî è ìàêñèìàëüíîãî çíà÷åíèÿ
{
	Time min = min_element(mp.begin(), mp.end())->second;		//íàõîäèì ìèíèìàëüíûé è ìàêñèìàëüíûé ýëåìåíò
	Time max = max_element(mp.begin(), mp.end())->second;		//èñïîëüçóþ ôóíêöèþ áèáëèîòåêè algorithm
	cout << "min: " << min << endl << "max: " << max << endl;	//à äàëüøå ïðîñòî öèêëîì ïðîõîäèì è äîáàâëÿåì
	for (auto& i : mp)
		i.second = i.second -max + min;			//ñèíòàêñèñ òàêîé, ïîòîìó ÷òî += ó pair íå ïåðåãðóæåí
}

void myfind(map<int, Time>& mp)			//ìîé ïîèñê. Ïðîñòî ïîèñê ïî êëþ÷ó ÷åðåç ìåòîä êîíòåéíåðà map 
{
	int a;
	cout << "Ââåäèòå êëþ÷ äëÿ ïîèñêà: "; cin >> a;
	auto it = mp.find(a);
	if (it != mp.end())
		cout << "Êëþ÷: " << a << "   Çíà÷åíèå:" << it->second << endl;
	else cout << "Ýëåìåíòà ñ òàêèì êëþ÷îì íåò â ñëîâàðå." << endl;
}

void printsortup(map<int, Time>& mp)		//ßêîáû ñîðòèðîâêà, íî íå òàê.
{											//map - áèíàðíîå äåðåâî è ôàéëû òàì îòñîðòèðîâàíû, ïîýòîìó ìû ïðîñòî êëþ÷àìè äåëàåì pair è âûâîäèì íàø êîíòåéíåð
	int a = 0;
	map<Time, int> temp;
	for (auto i = mp.begin(); i != mp.end(); ++i)
		temp.emplace(i->second, i->first);
	for (auto& i : temp)
		cout << ++a << ".\t" << i.first << "  \tÊëþ÷: " << i.second << endl;
}

void printsortdown(map<int, Time>& mp)		//çäåñü òîæå ñàìîå ÷òî è ñâåðõó, òîëüêî âûâîäèì êîíòåéíåð íàîáîðîò
{
	int a = 0;
	map<Time, int> temp;
	for (auto i = mp.begin(); i != mp.end(); ++i)
		temp.emplace(i->second, i->first);
	for (auto i = temp.crbegin(); i != temp.crend(); i++)
		cout << ++a << ".\t" << i->first << "  \tÊëþ÷: " << i->second << endl;



}

void number3()		//ôóíêöèÿ, êîòîðàÿ óïðàâëÿåò âñåì
{					//âûçûâàåò ôóíêöèè âûøå è ïèøåò ñîîáùåíèÿ.
	Time p;			//÷òîáû íå ñïàìèòü â main
	map<int, Time> mp;
	int n;
	cout << "Ââåäèòå êàêîå êîëè÷åñòâî çàïèñåé ñãåíåðèðîâàòü: "; cin >> n;
	for (int i = 0; i < n; i++)
		mp.emplace(++shet, p.randomGener());
	cout << "Òèï âûâîäà:\nÊëþ÷. Çíà÷åíèå" << endl;
	print(mp);
	cout << endl << "Íàéäåì ñðåäíåå àðèôìèòè÷åñêîå çíà÷åíèå è äîáàâèì åãî â êîíòåéíåð." << endl;
	plus_mid(mp);
	print(mp);
	cout << endl << "Çàäàäèì äèàïàçîí è óäàëèì äàííûå èç êîíòåéíåðà â äàííîì äèàïàçîíå." << endl;
	searchAndDel(mp);
	print(mp);
	cout << endl << "Ê êàæäîìó ýëåìåíòó êîíòåéíåðà äîáàâèì max è min ýëåìåíò êîíòåéíåðà." << endl;
	plusMinMax(mp);
	print(mp);
	cout << endl << "Íàéäåì â äàííîì êîíòåéíåðå åëåìåíò ïî åãî êëþ÷ó." << endl;
	myfind(mp);
	cout << endl << "Îòñîðòèðóåì êîíòåéíåð ïî âîçðàñòàíèþ çíà÷åíèé." << endl;
	printsortup(mp);
	cout << endl << "Îòñîðòèðóåì êîíòåéíåð ïî óáûâàíèþ çíà÷åíèé." << endl;
	printsortdown(mp);
}