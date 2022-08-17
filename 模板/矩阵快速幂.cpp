#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 105
using namespace std;
struct mat
{
	int M[N][N];
} ori, ans;
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
mat mul(mat a, mat b, int n)
{
	mat tep;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			tem.M[i][j] = 0;
			for (int k = 1; k <= n; k++)
				tep.M[i][j] = (tep.M[i][j] + (a.M[i][k] * b.M[k][j]) % P) % P;
		}
	return tep;
}
void qpow_mat(int n, int k)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			ans.M[i][j] = (i == j);
	while (k)
	{
		if (k & 1)
			ans = mul(ans, ori, n);
		ori = mul(ori, ori, n);
		k >>= 1;
	}
}
signed main()
{
	int n = read(), k = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			ori.M[i][j] = read();
	qpow_mat(n, k);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%lld ", ans.M[i][j]);
		printf("\n");
	}
	return 0;
}