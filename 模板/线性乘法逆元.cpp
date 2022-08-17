#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 3000005
using namespace std;
int inv[N];
inline int read()
{
	int X = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch))
	{
		w |= ch == '-';
		ch = getchar();
	}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
int main()
{
	int n = read(), p = read();
	inv[1] = 1;
	printf("1\n");
	for (int i = 2; i <= n; i++)
	{
		inv[i] = (LL)(p - p / i) * inv[p % i] % p;
		printf("%d\n", inv[i]);
	}
	return 0;
}