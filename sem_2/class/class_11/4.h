#pragma once


void Show(priority_queue<Tim> q);

Tim insert(priority_queue<Tim>& q);

void DelElem(priority_queue<Tim>& q);

void plusMinMax(priority_queue<Tim>& q);

void number_4()
{
	Tim temp;
	priority_queue<Tim> pq;
	int size;
	cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â î÷åðåäè: "; cin >> size;
	for (int i = 0; i < size; i++)
		pq.push(temp.randomGener());
	cout << "Ïîëó÷åííàÿ î÷åðåäü:" << endl;
	Show(pq);
	cout << "Äîáàâèì ñðåäíåå àðèôìèòè÷åñêîå çíà÷åíèå î÷åðåäè:" << endl;
	insert(pq);
	cout << "Ïîëó÷åííûé î÷åðåäü:" << endl;
	Show(pq);
	cout << "Óäàëèì ýëåìåíò ïî çíà÷åíèþ." << endl;
	DelElem(pq);
	cout << "Ïîëó÷åííûé î÷åðåäü:" << endl;
	Show(pq);
	cout << "Äîáàâèì ñóììó min è max ýëåìåíòîâ ê êàæäîìó ýëåìåíòó." << endl;
	plusMinMax(pq);
	cout << "Ïîëó÷åííûé î÷åðåäü:" << endl;
	Show(pq);
	return;
}



void Show(priority_queue<Tim> q)
{
	int j = 0;
	//priority_queue<Pair> temp(q);
	while (!q.empty())
	{
		cout << j++ << ". " << q.top() << endl;
		q.pop();
	}
}


Tim insert (priority_queue<Tim>& q)
{
	priority_queue<Tim> temp(q);
	Tim mid = 0;
	while (!temp.empty())
	{
		mid = mid + temp.top();
		temp.pop();
	}
	return mid / q.size();
}


void DelElem(priority_queue<Tim>& q)
{
	Tim key, k;
	priority_queue<Tim> temp;
	cout << "Ââåäèòå êëþ÷ äëÿ ïîèñêà: "; cin >> key;
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

void plusMinMax(priority_queue<Tim>& q)
{
	Tim k;
	Tim loc_min = q.top(), loc_max = 0;
	priority_queue<Tim> temp(q);
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