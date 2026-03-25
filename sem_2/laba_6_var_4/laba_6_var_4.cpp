#include<iostream>
#include<string>
using namespace std;

void main()
{
    setlocale(LC_ALL, "ru");
    char a[150];
    char b[25] = "";
    char c[150] = "";
    int wordIndex = 0;
    bool found = false;

    cout << "Введите строку: ";
    cin.getline(a, 150);

    int n = strlen(a);

    a[n] = ' ';
    a[n + 1] = '\0';
    n = strlen(a);

    cout << "\nСлова содержащие ровно одну цифру:" << endl;

    for (int i = 0; i <= n; i++)
    {
        if (a[i] == ' ' || a[i] == '\0')
        {
            if (wordIndex > 0)
            {

                b[wordIndex] = '\0';

                int digitCount = 0;
                for (int j = 0; j < wordIndex; j++)
                {
                    if (b[j] >= '0' && b[j] <= '9')
                    {
                        digitCount++;
                    }
                }

                if (digitCount == 1)
                {
                    cout << b << endl;
                    found = true;
                }

                wordIndex = 0;
            }
        }
        else
        {
            if (wordIndex < 24)
            {
                b[wordIndex] = a[i];
                wordIndex++;
            }
        }
    }

    if (!found)
    {
        cout << "Нет слов, содержащих одну ровно одну цифру." << endl;
    }
}