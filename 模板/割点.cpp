//删除后强连通分量数量增加
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100001;
int n, m, cnt, dfn[maxn], low[maxn], father[maxn];
vector<int>v[maxn];
set<int>s;
inline int read()
{
	int X = 0, w = 0; char ch = 0;
	while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
void tarjan(int x)
{
	dfn[x] = low[x] = ++cnt;
	int child = 0;
	for (int i = 0; i < v[x].size(); i++)
	{
		if (!dfn[v[x][i]])
		{
			father[v[x][i]] = x;
			child++;
			tarjan(v[x][i]);
			low[x] = min(low[x], low[v[x][i]]);

			if (father[x] && low[v[x][i]] >= dfn[x])
				s.insert(x);
		} else if (father[v[x][i]] != x)
			low[x] = min(low[x], dfn[v[x][i]]);
	}
	if (!father[x] && child >= 2)
		s.insert(x);
}
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		v[x].push_back(y);
		v[y].push_back(x);
	}

	for (int i = 1; i <= n; i++)
		if (!dfn[i])
		{
			//	cnt=0;
			tarjan(i);
		}

	cout << s.size() << endl;
	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); it++)
		cout << *it << " ";
	return 0;
}

