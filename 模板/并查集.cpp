#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 200005
using namespace std;
int fa[N];
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
int find(int x)
{
	if (fa[x] != x)fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	while (m--)
	{
		int opt = read(), x = read(), y = read();
		if (opt == 1)
			fa[find(x)] = fa[find(y)];
		else
		{
			if (find(x) == find(y))
				printf("Y\n");
			else
				printf("N\n");
		}
	}
	return 0;
}