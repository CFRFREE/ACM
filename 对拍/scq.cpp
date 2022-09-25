#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	int n = rand() % 10 + 1;
	int T = rand() % 10 + 1;
	printf("%d %d\n", n, T);
	for (int i = 1; i <= 4; i++)
		printf("%d ", rand() % 10 + 1);
	puts("");
	for (int i = 1; i <= n; i++)
		printf("%d ", rand() % 10 + 1);
	puts("");
	return 0;
}
