#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	int T = rand() % 9 + 1;
	cout << T << endl;
	for (int i = 1; i <= T; i++)
		cout << rand() % 9 + 1 << endl;
	return 0;
}
