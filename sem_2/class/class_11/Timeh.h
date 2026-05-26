#pragma once
#include <iostream>
using namespace std;

class Tim
{
public:
	Tim();
	Tim(int first, double second);
	Tim(int val);
	Tim(const Tim& copy);
	~Tim() {}
	int GetFirst() { return this->first; }
	double GetSecond() { return this->second; }
	void SetFirst(int first) { this->first = first; }
	void SetSecond(double second) { this->second = second; }
	Tim& operator =(const Tim& other);
	Tim operator +(const Tim& other) const;
	Tim& operator ++();
	Tim operator ++(int);
	Tim operator -(const Tim& other);
	bool operator <(const Tim& other) const;
	bool operator >(const Tim& other);
	bool operator ==(const Tim& other);
	friend const Tim operator +(const Tim& left, const int& right);
	friend const Tim operator +(const int& left, const Tim& right);
	friend const Tim operator +(const Tim& left, const double& right);
	friend const Tim operator +(const double& left, const Tim& right);
	Tim operator /(const Tim& other);
	Tim operator /(const int other);
	friend ostream& operator <<(ostream& os, const Tim& str);
	friend istream& operator >> (istream& is, Tim& str);
	Tim randomGener();
private:
	int first;
	double second;
};

ostream& operator <<(ostream& os, const Tim& val)
{
	os << val.first << " : " << val.second;
	return os;
}

istream& operator>>(istream& is, Tim& val)
{
	is >> val.first >> val.second;
	return is;
}

Tim::Tim()
{
	first = 0;
	second = 0;
}

Tim::Tim(const Tim& copy)
{
	this->first = copy.first;
	this->second = copy.second;
}

Tim::Tim(int first, double second)
{
	this->first = first;
	this->second = second;
}

Tim::Tim(int val)
{
	this->first = val;
	this->second = val;
}

Tim Tim::randomGener()
{
	return Tim(rand() % 50 - 25, (double((rand() % 10000)) / 1000));
}

Tim& Tim::operator=(const Tim& other)
{
	this->first = other.first;
	this->second = other.second;
	return *this;
}

Tim Tim::operator+(const Tim& other) const
{
	Tim temp(this->first + other.first, this->second + other.second);
	return temp;
}
Tim& Tim::operator++()
{
	++this->first;
	++this->second;
	return *this;
}

Tim Tim::operator++(int)
{
	Tim temp(*this);
	++this->first;
	++this->second;
	return temp;
}

Tim Tim::operator-(const Tim& other)
{
	return Tim(this->first - other.first, this->second - other.second);
}

const Tim operator+(const Tim& left, const int& right)
{
	return Tim(left.first + right, left.second);
}

const Tim operator+(const int& left, const Tim& right)
{
	return right + left;
}

const Tim operator+(const Tim& left, const double& right)
{
	return Tim(left.first, left.second + right);
}

const Tim operator+(const double& left, const Tim& right)
{
	return right + left;
}

Tim Tim::operator/(const Tim& other)
{
	return Tim(this->first / other.first, this->second / other.second);
}

Tim Tim::operator/(const int other)
{
	return Tim(this->first / other, this->second / other);
}

bool Tim::operator<(const Tim& other) const
{
	double thiss = this->first + this->second, otherr = other.first + other.second;
	if (thiss < otherr) return true;
	else return false;
}

bool Tim::operator>(const Tim& other)
{
	return !(*this < other);
}

bool Tim::operator==(const Tim& other)
{
	if (this->first == other.first && this->second == other.second)
		return true;
	else
		return false;
}