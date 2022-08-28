#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 5000005
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;
int Next[N], pre[N];
char s[N];
int last;
void add(char ch)
{
	int j = last;
	while (j && s[Next[j] + 1] != ch)
		j = pre[j];
	s[++last] = ch, j = Next[j] + 1;
	if (last == 1)
		Next[1] = pre[1] = 0;
	else if (s[j] == ch)
	{
		Next[last] = j;
		if (s[Next[j] + 1] == s[j + 1])
			pre[last] = pre[j];
		else
			pre[last] = j;
	}
	else
		Next[last] = pre[last] = 0;
}
void del(int len)
{
	last -= len;
}
void work()
{
	last = 0;
	string st;
	cin >> st;
	for (auto ch : st)
		add(ch);
	int n;
	cin >> n;
	while (n--)
	{
		string str;
		cin >> str;
		int len = str.size();
		for (auto ch : str)
		{
			add(ch);
			cout << Next[last] << " ";
		}
		cout << endl;
		del(len);
	}
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	IOS;
	work();
}