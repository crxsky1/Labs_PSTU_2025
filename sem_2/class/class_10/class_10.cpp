#include "Timess.h"
#include "file_work.h"
#include <iostream>
using namespace std; 
int main() 
{
	Times p,p1,p2,qwe;
	int k, c;
	char file_name[30]; 
	do
	{ //���� 
		cout << "\n1. Make file";//�������� ����� 
		cout << "\n2. Print file";//������ �����
		cout << "\n3. Delete record from file";
		cout << "\n4. Add record to file";
		cout << "\n5. -1:30";
		cout << "\n0. Exit\n";
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "file name?";
			cin >> file_name;//������ ��� �����
			k = makes_file(file_name);//����� ������� ��� ������ � ���� 
			if (k < 0)cout << "Can't make file";//����� ��������� �� ������
			break;
		case 2:
			cout << "file name?";
			cin >> file_name;//������ ��� ����� 
			k = prints_file(file_name);//����� ������� ��� ������ �����
			if (k == 0)cout << "Empty file\n";//���� ���� ������ 
			if (k < 0)cout << "Can't read file\n";//���� ���� ������ ������� 
			break;
		
		case 3:
			cout << "file name?";
			cin >> file_name;
			int nom;
			cout << "?";
			cin >> qwe;
			k = del_file(file_name, qwe);
			if (k < 0)cout << "Can't read file";
			break;
		case 4: 
			cout << "file name?";
			cin >> file_name;
			cout << "nom?"; 
			cin >> nom; 
			cout << "New person:"; 
			cin >> p1;
			k = add_file(file_name, nom, p1);
			if (k < 0) 
				cout << "Can't read file";
			if (k == 0)
				k = add_end(file_name, p1); 
			break;
		case 5: 
			cout << "file name?";
			cin >> file_name;
			k=change_file(file_name);
			if(k<0) 
				cout<<"\nCan't read file"; 
			break;
		}
	}
		while(c!=0);
	return 0;
}