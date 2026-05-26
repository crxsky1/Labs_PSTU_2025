#include "Timess.h" 
#include <iostream>
#include <fstream> 
#include <string> 
using namespace std;

int del_file(const char* f_name, Times qwe) {
	fstream temp("temp", ios::out);//������� ��� ������ 
	fstream stream(f_name, ios::in);//������� ��� ������ 
	if (!stream)return -1;//������ �������� ����� 
	int i = 0,c,d; Times p;
	c = qwe.get_min();
	d = qwe.get_sec();
	while (stream >> p)//���� ��� ����� ����� ��������� ������ ������� 
	{ 
//���� �������� ������� ����� �����,�� ����� �� 
		if (stream.eof())break; 
		i++; 
		int a, b;
		a = p.get_min();
		b = p.get_sec();
		//���� ����� ������� �� ����� k, �� ��������
		if ((a == c) && (b == d))
			i;
		else temp << p;
	} //������� ����� 
	stream.close();
	temp.close();
	remove(f_name);//������� ������ ���� 
	rename("temp", f_name);// ������������� temp
	return (i);//���������� �����������
	}
int makes_file(const char* f_name) 
{ 
	fstream stream(f_name,ios::out|ios::trunc);//������� ��� ������ 
	if(!stream)return -1;//������ �������� ����� 
	int n; 
	Times p; 
	cout<<"N?";
	cin>>n; 
	for(int i=0;i<n;i++ )
	{
		cin>>p;//���� ��������� ������� �� ������������ ������
		 stream<<p<<"\n";//������ ������� � ��������
	} 
	stream.close();//������� �����
	return n;//������� ���������� ���������� ��������
}
int prints_file(const char* f_name)
{
	fstream stream(f_name, ios::in);//������� ��� ������ 
	if (!stream)return -1;//������ �������� ����� 
	Times p;
	int i = 0;
	while (stream >> p)
	{
		cout << p << "\n";
		i++;
	}
	stream.close();
	return i;
}
int add_file(const char* f_name, int k, Times pp)
{
	fstream temp("temp", ios::out);//������� ��� ������
	fstream stream(f_name,ios::in);//������� ��� ������
	if(!stream)return -1;//������ �������� ����� 
	Times p; int i=0, l=0; 
	while(stream>>p)
	{
		if (stream.eof())break; i++; if (i == k) {
			temp << pp;//�������� � temp ����� ������
			l++;
		} temp<<p;
	} 
	stream.close();
	temp.close();
	remove(f_name);
	rename("temp",f_name); 
	return l;//���������� �����������
}
int add_end(const char* f_name, Times pp) {
	fstream stream(f_name, ios::app);//������� ��� ���������� 
	if(!stream)return -1;//������ �������� ����� 
	stream<<pp; //�������� ����� ������ 
	return 1; 
}
int change_file(const char* f_name) {
	fstream temp("temp", ios::out);//������� ��� ������
	fstream stream(f_name, ios::in);//������� ��� ������ 
	if (!stream)return -1;//������ �������� ����� 
	Times p; int i = 0; Times qwe;
	qwe.set_min(1);
	qwe.set_sec(30);
	while (stream >> p)//���� ��� ����� ����� ��������� ������ ������� 
	{
		if (stream.eof())break;
		i++;
		p=p - qwe;
		temp << p;
	}
		stream.close();
		temp.close();
		remove(f_name);
		rename("temp", f_name);
		return i;//���������� ��������� 
}