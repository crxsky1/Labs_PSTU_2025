#pragma once
#include <iostream>
using namespace std;

class Time				//òóò âñå ïîíÿòíî, åñëè íåò, òî íåîáõîäèìî îòêðûòü êîä 7, 10, 11 ëàáîðàòîðíîé ðàáîòû. Îí ïî÷òè âåçäå åñòü.
{
public:
	Time();
	Time(int first, double second);
	Time(int val);
	Time(const Time& copy);
	~Time() {}
	int GetFirst() { return this->first; }
	double GetSecond() { return this->second; }
	void SetFirst(int first) { this->first = first; }
	void SetSecond(double second) { this->second = second; }
	Time& operator =(const Time& other);
	Time operator +(const Time& other) const;
	Time& operator ++();
	Time operator ++(int);
	Time operator -(const Time& other);
	bool operator <(const Time& other) const;
	bool operator ==(const Time& other) const;
	bool operator !=(const Time& other) const;
	bool operator >(const Time& other) const;
	friend const Time operator +(const Time& left, const int& right);
	friend const Time operator +(const int& left, const Time& right);
	friend const Time operator +(const Time& left, const double& right);
	friend const Time operator +(const double& left, const Time& right);
	Time operator /(const Time& other);
	Time operator /(const int other);
	friend ostream& operator <<(ostream& os, const Time& str);
	friend istream& operator >> (istream& is, Time& str);
	Time randomGener();
private:
	int first;
	double second;
};