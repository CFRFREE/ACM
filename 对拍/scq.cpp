#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	int n = 8;
	printf("%d ", n);
	for (int i = 1; i <= 3; i++)
		printf("%d ", rand() % 10 + 1);
	puts("");
	for (int i = 1; i <= n; i++)
		printf("%d ", rand() % 10 + 1);
	puts("");
	return 0;
}
