#include <iostream>
using namespace std;
int main()
{
	const int n = 7;
	int key;

int arr[n] = { 5, 2, 4, 6, 0, 1, 3 };

for (int i = 0; i < n; i++)
{
	cout << arr[i] << " ";
}
cout << endl;

for (int i = 1; i < n - 1; i++)
{
	key = arr[i];
	int j = i - 1;
	while (j >= 0 && arr[j] > key)
	{
		arr[j + 1] = arr[j];
		j--;
	}
	arr[j + 1] = key;
}

for (int i = 0; i < n; i++)
{
	cout << arr[i] << " ";
}
cout << endl;
return 0;
}