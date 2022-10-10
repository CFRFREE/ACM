#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 1000005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int rk[N << 1], sa[N << 1], cnt[N << 1], height[N << 1], x[N << 1], y[N << 1];
int n, m;
string st;
inline int read()
{
	int X = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch))
	{
		w |= ch == '-';
		ch = getchar();
	}
	while (isdigit(ch))
		X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
void SA()
{
	cin >> st;
	n = st.size();
	st = " " + st;
	m = 'z';
	for (int i = 1; i <= n; i++)
	{
		x[i] = st[i];
		cnt[x[i]]++;
	}
	for (int i = 2; i <= m; i++)
		cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; i--)
		sa[cnt[x[i]]--] = i;
	for (int k = 1; k <= n; k <<= 1)
	{
		int num = 0;
		for (int i = n - k + 1; i <= n; i++)
			y[++num] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k)
				y[++num] = sa[i] - k;
		for (int i = 1; i <= m; i++)
			cnt[i] = 0;
		for (int i = 1; i <= n; i++)
			cnt[x[i]]++;
		for (int i = 2; i <= m; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--)
		{
			sa[cnt[x[y[i]]]--] = y[i];
			y[i] = 0;
		}
		swap(x, y);
		num = 1;
		x[sa[1]] = 1;
		for (int i = 2; i <= n; i++)
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
				x[sa[i]] = num;
			else
				x[sa[i]] = ++num;
		if (num == n)
			break;
		m = num;
	}
	for (int i = 1; i <= n; i++)
		cout << sa[i] << " ";
	cout << endl;
}
void LCP()
{
	int k = 0; // 用k代表h[i]
	for (int i = 1; i <= n; i++)
		rk[sa[i]] = i;			 // 初始化rk[i]
	for (int i = 1; i <= n; i++) // 这里其实是枚举rk[i]
	{
		if (rk[i] == 1)
			continue; // height[1]=0
		if (k)
			k--;			   // h[i]>=h[i-1]-1,更新k然后一位位枚举
		int j = sa[rk[i] - 1]; // 前一位字符串
		while (i + k <= n && j + k <= n && st[i + k] == st[j + k])
			k++;		   // 一位位枚举
		height[rk[i]] = k; // h[i]=height[rk[i]]
	}
	for (int i = 1; i <= n; i++)
		cout << height[i] << " ";
	cout << endl;
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	SA(); // 后缀数组
	// LCP(); // 两个后缀的最长公共前缀，LCP(i, j) == min{height[pos]}, i < pos <= j;
	return 0;
}