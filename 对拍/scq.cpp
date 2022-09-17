#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	puts("1");
	int n = rand() % 10 + 1;
	int k = rand() % 10 + 1;
	int a = rand() % n + 1;
	int b = rand() % n + 1;
	printf("%d %d %d %d\n", n, k, a, b);
	return 0;
}
