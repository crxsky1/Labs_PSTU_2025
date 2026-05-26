#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Times
{
private: 
		int min, sec;
public:
	Times() { min = 0; sec = 0; };
	Times(int m, int s) { min = m; sec = s; } 
	Times(const Times& t) { min = t.min; sec = t.sec; }
	~Times() {}; 
	int get_min() { return min; } 
	int get_sec() { return sec; } 
	void set_min(int m) { min = m; } 
	void set_sec(int s) { sec = s; } 
	//������������� �������� 
	Times&operator=(const Times&); 
	Times operator+ (const Times&);
	Times operator- (const Times&);
	friend istream& operator>>(istream& in, Times& t); 
	friend ostream& operator<<(ostream& out, const Times& t);
	friend fstream& operator>>(fstream& fin, Times& p);
	friend fstream& operator <<(fstream& fout, const Times& p);
};