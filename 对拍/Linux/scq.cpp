#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand((unsigned int)time(NULL));
	int n=rand()%10+1;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++)
	printf("%d\n", rand()%10+1);
	return 0;
}