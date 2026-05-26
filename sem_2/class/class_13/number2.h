#pragma once
void Show(priority_queue<Time> q);

void Insert(priority_queue<Time>& q);

void DelElem(priority_queue<Time>& q);

void plusMinMax(priority_queue<Time>& q);




void number2()			
{					
	setlocale(0, "rus");
	Time temp;			
	priority_queue<Time> pq;	
	int size;
	cout << "������� ���������� ��������� � �������: "; cin >> size;
	for (int i = 0; i < size; i++)
		pq.push(temp.randomGener());
	cout << "���������� �������:" << endl;
	Show(pq);
	cout << "������� �������� �������:" << endl;
	Insert(pq);
	cout << "���������� �������:" << endl;
	Show(pq);
	cout << "������ ������� �� ��������." << endl;
	DelElem(pq);
	cout << "���������� �������:" << endl;
	Show(pq);
	cout << "������� ����� min � max ��������� � ������� ��������." << endl;
	plusMinMax(pq);
	cout << "���������� �������:" << endl;
	Show(pq);
	return;
}



void Show(priority_queue<Time> q)
{
	int j = 0;
	while (!q.empty())
	{
		cout << j++ << ". " << q.top() << endl;
		q.pop();
	}
}


void Insert(priority_queue<Time>& q)
{
	priority_queue<Time> temp(q);
	Time mid = 0;
	while (!temp.empty())
	{
		mid = mid + temp.top();
		temp.pop();
	}
}

void DelElem(priority_queue<Time>& q)
{
	Time key, k;
	priority_queue<Time> temp;
	cout << "������� ���� ��� ������: "; cin >> key;
	while (!q.empty())
	{
		k = q.top();
		if (key == k)
			q.pop();
		else

		{
			temp.push(k);
			q.pop();
		}
	}
	q.swap(temp);
}

void plusMinMax(priority_queue<Time>& q)
{
	Time k;
	Time loc_min = q.top(), loc_max = 0;
	priority_queue<Time> temp(q);
	while (!temp.empty())
	{
		k = temp.top();
		if (loc_max < k)
		{
			loc_max = k;
			temp.pop();
		}
		else if (loc_min > k)
		{
			loc_min = k;
			temp.pop();
		}
		else temp.pop();
	}
	cout << "min element: " << loc_min << endl;
	cout << "max element: " << loc_max << endl;
	temp.swap(q);
	while (!temp.empty())
	{
		k = temp.top();
		q.push(k + loc_min - loc_max);
		temp.pop();
	}
}