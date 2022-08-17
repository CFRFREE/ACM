#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 505
using namespace std;
int son[N], f[N];
string h[N];
vector<string>h2;
vector<int>a[N];
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
void find_root(int x, int fa, int n)
{
	son[x] = 1, f[x] = 0;
	for (auto y : a[x])
	{
		if (y == fa)continue;
		find_root(y, x, n);
		son[x] += son[y];
		f[x] = max(f[x], son[y]);
	}
	f[x] = max(f[x], n - son[x]);//f[x]最小的一个或两个点就是重心
}
void dfs(int x, int fa)
{
	h[x] = "(";
	for (auto y : a[x])
		if (y != fa)dfs(y, x);
	h2.clear();
	for (auto y : a[x])
		if (y != fa)h2.emplace_back(h[y]);
	sort(h2.begin(), h2.end());
	for (auto st : h2)
		h[x] += st;
	h[x] += ")";
}
string get_hash()
{
	int n = read();
	for (int i = 1; i <= n; i++)
		a[i].clear();
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		if (!x)continue;
		a[x].emplace_back(i);
		a[i].emplace_back(x);
	}
	find_root(1, 0, n);
	int mini = *min_element(f + 1, f + n + 1);
	string tep;
	for (int i = 1; i <= n; i++)
	{
		h[i] = "";
		if (mini == f[i])
		{
			dfs(i, 0);
			tep = max(tep, h[i]);//字符串不能max_element()
		}
	}
	return tep;
}
signed main()
{
	int n = read();
	vector<string>hash(n + 1);
	for (int i = 1; i <= n; i++)
	{
		hash[i] = get_hash();
		for (int j = 1; j <= i; j++)
			if (hash[j] == hash[i])
			{
				printf("%d\n", j);
				break;
			}
	}
	return 0;
}