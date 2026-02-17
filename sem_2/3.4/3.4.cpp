#include <iostream>
using namespace std;
int main(){
	setlocale(LC_ALL, "ru");
	const int n = 6;

	int arr[n] = { 1, 2, 3, 4, 5, 6 };

	bool sorted = true;
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			sorted = false;
			break;
		}
	}
	cout << endl;

	if (sorted)
	{
		cout << "Массив отсортирован!" << endl;
	}
	else { cout << "Массив не упорядочен по возрастанию" << endl; }


	return 0;
}