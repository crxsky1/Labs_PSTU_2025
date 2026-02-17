#include <iostream>
using namespace std;
int main()
{
	const int n = 7;
	int tmp, min_index;

	int arr[n] = { 5, 2, 4, 6, 0, 1, 3 };

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < n - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		tmp = arr[min_index];
		arr[min_index] = arr[i];
		arr[i] = tmp;
	}

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}