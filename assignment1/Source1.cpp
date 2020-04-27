#include <iostream>

using namespace std;
bool isDragonKnight(int n)
{
	for (int i = n; i > n/3 ; i--)
	{
		for (int j = n-i; j >0; j--)
		{
			int z = n - i - j;
			if (z == 0) continue;
			if (i * i - j * j - z * z == 0)
			{
				cout << i << " " << j << " " << z << endl;
				return true;
			}
		}
	}
	return false;
}
int nearestFibo(int hp)
{
	int a1 = 1, a2 = 1;
	int a = 0;
	while (a <= hp)
	{
		a = a1 + a2;
		a1 = a2;
		a2 = a;
	}
	return a;
}
void resizeArr(int* arrEvent, int& nEvent, int i)
{
	nEvent = (i + 1) * 2 - 1;
	int j = i + 1, k = i - 1;
	for (j; j < nEvent; j++)
		arrEvent[j] = arrEvent[k--];
}
int main()
{
	int n, i, dem = 0;
	cin >> n;
	int min = 10;
	do
	{
		i = n % 10;
		if (i == min)
			dem++;
		if (i < min)
		{
			min = i;
			dem = 1;
		}
	} while (n /= 10);
	cout << min << " " << dem;
}