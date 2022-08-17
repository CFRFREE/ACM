#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 500005
using namespace std;
int tree[N], a[N], cnt;
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
int low(int x)
{
	return x & -x;
}
void add(int x)
{
	for (; x <= cnt; x += low(x))
		tree[x]++;
}
int sum(int x)
{
	int s = 0;
	for (; x != 0; x -= low(x))
		s += tree[x];
	return s;
}
signed main()
{
	int n = read();
	vector<int>v;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	map<int, int>M;
	for (auto x : v)
		if (M.find(x) == M.end())
			M[x] = ++cnt;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		add(M[a[i]]);
		ans += i - sum(M[a[i]]);
	}
	printf("%lld\n", ans);
	return 0;
}