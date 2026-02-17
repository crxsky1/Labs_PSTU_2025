#include <iostream>
using namespace std;
int main()
{
	const int n = 11;
	int tmp, p, q;

	int arr[n] = { 41, 42, 66, 87, 86, 38, 77, 84, 45, 35, 22 };

	p = 2; q = 6;

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	while (p < q)
	{
		tmp = arr[p];
		arr[p] = arr[q];
		arr[q] = tmp;
		p++;
		q--;
	}

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}