#include <iostream>
using namespace std;
int main()
{
	const int n = 4;
	int tmp;

int arr[n] = { 41, 42, 66, 77 };

for (int i = 0; i < n; i++)
{
	cout << arr[i] << " ";
}
cout << endl;

for (int i = 0; i < n / 2; i++)
{
	tmp = arr[i];
	arr[i] = arr[n - 1 - i];
	arr[n - 1 - i] = tmp;
}


for (int i = 0; i < n; i++)
{
	cout << arr[i] << " ";
}
cout << endl;

return 0;
}