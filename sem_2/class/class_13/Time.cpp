#include "Time.h"


ostream& operator <<(ostream& os, const Time& val)
{
	os << val.first << " : " << val.second;
	return os;
}

istream& operator>>(istream& is, Time& val)
{
	is >> val.first >> val.second;
	return is;
}

Time::Time()
{
	first = 0;
	second = 0;
}

Time::Time(const Time& copy)
{
	this->first = copy.first;
	this->second = copy.second;
}

Time::Time(int first, double second)
{
	this->first = first;
	this->second = second;
}

Time::Time(int val)
{
	this->first = val;
	this->second = val;
}

Time Time::randomGener()
{
	return Time(rand() % 50 - 25, (double((rand() % 10000)) / 1000));
}

Time& Time::operator=(const Time& other)
{
	this->first = other.first;
	this->second = other.second;
	return *this;
}

Time Time::operator+(const Time& other) const
{
	Time temp(this->first + other.first, this->second + other.second);
	return temp;
}
Time& Time::operator++()
{
	++this->first;
	++this->second;
	return *this;
}

Time Time::operator++(int)
{
	Time temp(*this);
	++this->first;
	++this->second;
	return temp;
}

Time Time::operator-(const Time& other)
{
	return Time(this->first - other.first, this->second - other.second);
}

const Time operator+(const Time& left, const int& right)
{
	return Time(left.first + right, left.second);
}

const Time operator+(const int& left, const Time& right)
{
	return right + left;
}

const Time operator+(const Time& left, const double& right)
{
	return Time(left.first, left.second + right);
}

const Time operator+(const double& left, const Time& right)
{
	return right + left;
}

Time Time::operator/(const Time& other)
{
	return Time(this->first / other.first, this->second / other.second);
}

Time Time::operator/(const int other)
{
	return Time(this->first / other, this->second / other);
}

bool Time::operator<(const Time& other) const
{
	double thiss = this->first + this->second, otherr = other.first + other.second;
	if (thiss < otherr) return true;
	else return false;
}


bool Time::operator==(const Time& other) const
{
	if (this->first == other.first && this->second == other.second)
		return true;
	else
		return false;
}

bool Time::operator!=(const Time& other) const
{
	return !(*this == other);
}

bool Time::operator>(const Time& other) const
{
	return !((*this < other) && !(*this == other));
}