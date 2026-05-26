#include "Timess.h"
#include <iostream> 
using namespace std; 
//���������� �������� ������������ 
Times& Times::operator=(const Times& t)
{
	//�������� �� ���������������� 
	if (&t == this) return *this;
	min = t.min;
	sec = t.sec;
	return *this;
};
//���������� �������� �������� �������� 
Times Times::operator+(const Times&t)
{ 
	int temp1=min*60+sec; 
	int temp2=t.min*60+t.sec;
	Times p; 
	p.min=(temp1+temp2)/60; 
	p.sec=(temp1+temp2)%60; 
	return p; 
}
//���������� �������� �������� ��������� 
Times Times::operator-(const Times& t)
{
	int temp1 = min * 60 + sec;
	int temp2 = t.min * 60 + t.sec;
	Times p;
	p.min = (temp1 - temp2) / 60;
	p.sec = (temp1 - temp2) % 60;
	if (p.sec < 0)  p.sec = 0 ;
	if (p.min < 0)  p.min = 0;
	return p;
}
//���������� ���������� �������-�������� ����� 
istream&operator>>(istream&in, Times&t)
{
	cout<<"min? ";in>>t.min;
	cout<<"sec? ";in>>t.sec; 
	return in;
}
//���������� ���������� �������-�������� ������ 
ostream&operator<<(ostream&out, const Times&t)
{
	out << "min:" << t.min << "sec:" << t.sec << "\n";
	return  out;
}
fstream& operator>>(fstream& fin, Times& p) 
{ 
	fin >> p.min;
	fin >> p.sec;
	return fin;
}
fstream& operator<<(fstream& fout, const Times& p) 
{ 
	fout << p.min << "\n" << p.sec << "\n";
	return fout; 
}