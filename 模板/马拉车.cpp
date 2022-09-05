#include <bits/stdc++.h>
#include <stdio.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 2000005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int p[N];
string st, str;
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
void init()
{
	str += "&";
	str += '#';
	for (auto ch : st)
		str += ch, str += '#';
	str += '^';
}
void manachar()
{
	int R = 0, mid = 0;
	int len = str.size();
	for (int i = 1; i < len; i++)
	{
		if (i < R)
			p[i] = min(p[2 * mid - i], R - i);
		else
			p[i] = 1;
		while (str[i - p[i]] == str[i + p[i]])
			p[i]++;
		if (p[i] + i > R)
		{
			R = p[i] + i;
			mid = i;
		}
	}
}
void work()
{
	cin >> st;
	init();
	manachar();
	int ans = 0;
	int len = str.size();
	for (int i = 0; i < len; i++)
		ans = max(ans, p[i] - 1); //回文串长度为p[i] - 1, p[i]是新串的半径
	cout << ans << endl;
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	IOS;
	work();
	return 0;
}