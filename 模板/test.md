### 2sat.cpp
```cpp
#include <bits/stdc++.h>
#define INF 2147483647
#define LL long long
#define N 2000005
using namespace std;
int n, m, cnt, dfn[N], low[N], in[N], tot;
int to[N], id[N], next[N], from[N];
stack<int> S;
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
inline void add(int x, int y)
{
    to[+cnt] = y;
    next[cnt] = from[x];
    from[x] = cnt;
}
void tarjan(int x)
{
    dfn[x] = low[x] = ++cnt;
    S.push(x);
    in[x] = 1;
    for (int i = from[x]; i; i = next[i])
    {
        int y = to[i];
        if (!dfn[y])
        {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (in[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (low[x] == dfn[x])
    {
        tot++;
        while (S.top() != x)
        {
            int X = S.top();
            id[X] = tot;
            in[X] = 0;
            S.pop();
        }
        id[S.top()] = tot;
        in[S.top()] = 0;
        S.pop();
    }
}
int main()
{
    n = read(), m = read();
    while (m--)
    {
        int a = read();
        int x = read();
        int b = read();
        int y = read();
        if (x == 0 && y == 0)
        {
            add(a + n, b);
            add(b + n, a);
        }
        if (x == 0 && y == 1)
        {
            add(a + n, b + n);
            add(b, a);
        }
        if (x == 1 && y == 0)
        {
            add(a, b);
            add(b + n, a + n);
        }
        if (x == 1 && y == 1)
        {
            add(a, b + n);
            add(b, a + n);
        }
    }
    cnt = 0;
    for (int i = 1; i <= n << 1; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (id[i] == id[i + n])
        {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    printf("POSSIBLE\n");
    for (int i = 1; i <= n; i++)
        if (id[i] > id[i + n])
            printf("1 ");
        else
            printf("0 ");
    return 0;
}

```

### dinic.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 500005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N], cur[N];
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
inline void addage(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
inline void add(int x, int y, int z)
{
	addage(x, y, z);
	addage(y, x, 0);
}
int bfs()
{
	queue<int> q;
	memset(d, 0, sizeof(d));
	d[S] = 1;
	cur[S] = from[S];
	q.push(S);
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				d[y] = d[x] + 1;
				cur[y] = from[y];
				q.push(y);
				if (y == T)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == T)
		return flow;
	int k, rest = flow;
	for (int i = from[x]; i && rest; i = Next[i])
	{
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(rest, val[i]));
			if (!k)
				d[y] = 0;
			val[i] -= k;
			val[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		int tep;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read();
	S = read(), T = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z);
	}
	int maxflow = dinic();
	printf("%d\n", maxflow);
	return;
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### kmp.cpp
```cpp
#include<bits/stdc++.h>
#define LL long long
#define N 1000005
using namespace std;

int Next[N], ans, len1, len2;
string st1, st2;
vector<int>pos;

inline int read()
{
    int X = 0, w = 0; char ch = 0;
    while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

void KMP()
{
    Next[0] = -1;
    int k = -1;
    for (int q = 1; q < len2; q++)
    {
        while (k != -1 && st2[k + 1] != st2[q])
            k = Next[k];
        if (st2[k + 1] == st2[q])
            k++;
        Next[q] = k;
    }
    k = -1;
    for (int i = 0; i < len1; i++)
    {
        while (k != -1 && st2[k + 1] != st1[i])
            k = Next[k];
        if (st2[k + 1] == st1[i]) k++;
        if (k == len2 - 1)
        {
            i = i - len2 + 1;
            k = -1;
            cout << i + 1 << endl;
        }
    }
}

int main()
{
    cin >> st1;
    cin >> st2;
    len1 = st1.length();
    len2 = st2.length();
    KMP();
    for (int i = 0; i < len2; i++)
        cout << Next[i] + 1 << " ";
    return 0;
}


```

### kruskal重构树解决最小瓶颈路.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int fa[N], f[N][20], val[N], lg[N], dep[N], vis[N];
int n, m, cnt;
vector<int>a[N];
pair<int, pii>e[N];
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
	if (x != fa[x])
		fa[x] = find(fa[x]);
	return fa[x];
}
void add(int x, int y)
{
	a[x].push_back(y);
	a[y].push_back(x);
}
void init()
{
	for (int i = 1; i < N; i++)
	{
		lg[i] = lg[i - 1];
		if (i == (1 << lg[i - 1]))lg[i]++;
	}
}
void dfs(int x, int father)
{
	vis[x] = 1;
	dep[x] = dep[father] + 1;
	f[x][0] = father;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		f[x][i] = f[f[x][i - 1]][i - 1];
	for (auto y : a[x])
		if (y != father)
			dfs(y, x);
}
int LCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	while (dep[x] != dep[y])
		x = f[x][lg[dep[x] - dep[y]] - 1];
	if (x == y)return x;
	for (int i = lg[dep[x]]; i >= 0; i--)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}
void kruskal()
{
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		auto [x, y] = e[i].second;
		int z = e[i].first;
		x = find(x), y = find(y);
		if (x == y)continue;
		val[++cnt] = z;
		fa[cnt] = fa[x] = fa[y] = cnt;
		add(x, cnt);
		add(y, cnt);
	}
	for (int i = 1; i <= cnt; i++)
		if (!vis[i])
			dfs(find(i), 0);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	init();
	n = read(), m = read();
	int q = read();
	cnt = n;
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		e[i] = { z, {x, y} };
	}
	kruskal();
	while (q--)
	{
		int x = read(), y = read();
		if (find(x) != find(y))
			puts("-1");
		else
			printf("%d\n", val[LCA(x, y)]);
	}
	return 0;
}
```

### lucas定理.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 200005
using namespace std;
int jc[N], p;
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
int qpow(int x, int k)
{
	int tep = 1ll;
	while (k)
	{
		if (k & 1ll)
			tep = tep * x % p;
		x = x * x % p;
		k >>= 1ll;
	}
	return tep;
}
int C(int x, int y)
{
	if (x < y)
		return 0;
	return (jc[x] * qpow(jc[x - y], p - 2) % p * qpow(jc[y], p - 2));
}
int lucas(int x, int y)
{
	if (!y)
		return 1;
	return C(x % p, y % p) * lucas(x / p, y / p) % p;
}
void init()
{
	memset(jc, 0, sizeof(jc));
	jc[0] = 1;
	for (int i = 1; i <= p; i++)
		jc[i] = (jc[i - 1] * i) % p;
}
signed main()
{
	int T = read();
	while (T--)
	{
		int n = read(), m = read();
		p = read();
		init();
		printf("%lld\n", lucas(n + m, n));
	}
	return 0;
}
```

### spfa多路增广求最小费用最大流.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int to[N], Next[N], from[N], val[N], fy[N];
int cnt = 1, ans_cost, ans_flow;
int vis[N], dis[N];
int S, T;
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
inline void addage(int x, int y, int z, int c)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
	fy[cnt] = c;
}
inline void add(int x, int y, int z, int c)
{
	addage(x, y, z, c);
	addage(y, x, 0, -c);
}
int spfa()
{
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	vis[T] = 1;
	dis[T] = 0;
	deque<int> q;
	q.push_back(T);
	while (q.size())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		for (int i = from[x]; i; i = Next[i])
		{
			if (val[i ^ 1] <= 0)
				continue;
			int y = to[i];
			if (dis[y] > dis[x] - fy[i])
			{
				dis[y] = dis[x] - fy[i];
				if (vis[y] == 0)
				{
					vis[y] = 1;
					if (q.size() && dis[y] < dis[q.front()])
						q.push_front(y);
					else
						q.push_back(y);
				}
			}
		}
	}
	return dis[S] != dis[N - 1];
}
int dfs(int x, int flow)
{
	if (x == T)
	{
		vis[T] = 1;
		return flow;
	}
	int used = 0;
	vis[x] = 1;
	for (int i = from[x]; i; i = Next[i])
	{
		int y = to[i];
		if (vis[y] == 0 && val[i] > 0 && dis[x] - fy[i] == dis[y])
		{
			int tep = dfs(y, min(val[i], flow - used));
			if (tep > 0)
			{
				ans_cost += tep * fy[i];
				val[i] -= tep;
				val[i ^ 1] += tep;
				used += tep;
			}
			if (used == flow)
				break;
		}
	}
	return used;
}
void costflow()
{
	ans_cost = 0;
	ans_flow = 0;
	while (spfa())
	{
		vis[T] = 1;
		while (vis[T])
		{
			memset(vis, 0, sizeof(vis));
			ans_flow += dfs(S, INF);
		}
	}
}
void work()
{
	int n = read(), m = read();
	S = read(), T = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read(), c = read();
		add(x, y, z, c);
	}
	costflow();
	printf("%d %d\n", ans_flow, ans_cost);
	// for (int i = 2; i <= cnt; i += 2)
	// {
	// 	val[i] += val[i ^ 1];
	// 	val[i ^ 1] = 0;
	// 	fy[i] = -fy[i];
	// 	fy[i ^ 1] = -fy[i ^ 1];
	// }
	// costflow();
	// printf("%d\n", -ans_cost);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### spfa暴力最小费用最大流.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int S, T, cnt = 1, to[N], Next[N], from[N], fy[N], val[N], cost[N], flow[N];
int pre[N], last[N], vis[N];
LL ans_flow, ans_cost;
queue<int> q;
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
inline void addage(int x, int y, int z, int Cost)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
	fy[cnt] = Cost;
}
void add(int x, int y, int z, int Cost)
{
	addage(x, y, z, Cost);
	addage(y, x, 0, -Cost);
}
int spfa()
{
	memset(vis, 0, sizeof(vis));
	memset(cost, 0x7f, sizeof(cost));
	memset(flow, 0x7f, sizeof(flow));
	pre[T] = -1;
	q.push(S);
	vis[S] = 1;
	cost[S] = 0;
	while (q.size())
	{
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && cost[x] + fy[i] < cost[y])
			{
				cost[y] = cost[x] + fy[i];
				pre[y] = x;
				last[y] = i;
				flow[y] = min(flow[x], val[i]);
				if (!vis[y])
				{
					vis[y] = 1;
					q.push(y);
				}
			}
		}
	}
	return pre[T] != -1;
}
void work()
{
	int n = read(), m = read();
	S = read(), T = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read(), Cost = read();
		add(x, y, z, Cost);
	}
	while (spfa())
	{
		int x = T;
		ans_flow += flow[T];
		ans_cost += flow[T] * cost[T];
		while (x != S)
		{
			val[last[x]] -= flow[T];
			val[last[x] ^ 1] += flow[T];
			x = pre[x];
		}
	}
	printf("%lld %lld\n", ans_flow, ans_cost);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### st表.cpp
```cpp
#include<bits/stdc++.h>
#define LL long long
#define N 100005
using namespace std;
int n, m, st[N][25], lg[N];
inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))X = X * 10 + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
void init()
{
    for (int i = 1; i < N; i++)
    {
        lg[i] = lg[i - 1];
        if (1 << lg[i] == i)lg[i]++;
    }
}
void ST()
{
    for (int i = 1; i <= n; i++)
        st[i][0] = read();
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
int get_max(int L, int R)
{
    int k = lg[R - L + 1] - 1;
    return max(st[L][k], st[R - (1 << k) + 1][k]);
}
int main()
{
    init();
    n = read(), m = read();
    ST();
    while (m--)
    {
        int L = read(), R = read();
        printf("%d\n", get_max(L, R));
    }
    return 0;
}
```

### tarjanLCA.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 500005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;

int n, m, s, vis[N], ans[N], fa[N];
vector<int>v[N];
vector<pii>ask[N];

inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))X = X * 10 + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

int find(int x)
{
    if (fa[x] != x)
        fa[x] = find(fa[x]);
    return fa[x];
}

void tarjan(int x)
{
    vis[x] = 1;
    int X = find(x);
    for (auto y : v[x])
    {
        if (vis[y])continue;
        tarjan(y);
        int Y = find(y);
        if (X != Y)fa[Y] = X;
    }
    for (auto [y, id] : ask[x])
        if (vis[y])
            ans[id] = find(y);
}

int main()
{
    n = read(), m = read(), s = read();
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i < n; i++)
    {
        int x = read(), y = read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for (int i = 1; i <= m; i++)
    {
        int x = read(), y = read();
        ask[x].push_back({y, i});
        ask[y].push_back({x, i});
    }
    tarjan(s);
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}


```

### tarjan缩点.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int sum[N], scc[N], in[N];
int low[N], dfn[N], w[N], dp[N];
int n, m, cnt, M, ans;
vector<int>a[N], v[N];
stack<int>s;
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
void tarjan(int x)
{
	in[x] = 1;
	s.push(x);
	dfn[x] = low[x] = ++cnt;
	for (auto y : a[x])
	{
		if (!dfn[y])
		{
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if (in[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x])
	{
		M++;
		while (1)
		{
			int X = s.top();
			s.pop();
			scc[X] = M;
			in[X] = 0;
			sum[M] += w[X];
			if (x == X)break;
		}
	}
}
void search(int x)
{
	if (dp[x])return;
	dp[x] = sum[x];
	int maxson = 0;
	for (auto y : v[x])
	{
		if (!dp[y])
			search(y);
		maxson = max(maxson, dp[y]);
	}
	dp[x] += maxson;
}
signed main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		w[i] = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		a[x].push_back(y);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i);
	for (int i = 1; i <= n; i++)
		for (auto y : a[i])
			if (scc[i] != scc[y])
				v[scc[i]].push_back(scc[y]);
	for (int i = 1; i <= M; i++)
		search(i);
	for (int i = 1; i <= M; i++)
		ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}
```

### trie.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 1000005
using namespace std;
int tot;
struct Node {
	int son[27], ed, vis;
} trie[N];
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
void insert(string str)
{
	int pos = 1;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		int x = str[i] - 'a';
		if (!trie[pos].son[x])
			trie[pos].son[x] = ++tot;
		pos = trie[pos].son[x];
	}
	trie[pos].ed = 1;
}
void work(string str)
{
	int pos = 1;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		int x = str[i] - 'a';
		if (!trie[pos].son[x])
		{
			printf("WRONG\n");
			return;
		}
		pos = trie[pos].son[x];
	}
	if (!trie[pos].ed)
	{
		printf("WRONG\n");
		return;
	}
	else if (trie[pos].vis)
	{
		printf("REPEAT\n");
		return;
	}
	else
	{
		printf("OK\n");
		trie[pos].vis = 1;
	}
}
int main()
{
	int n = read();
	for (int i = 1; i <= n; i++)
	{
		string st;
		cin >> st;
		insert(st);
	}
	int m = read();
	while (m--)
	{
		string st;
		cin >> st;
		work(st);
	}
	return 0;
}
```

### 主席树.cpp
```cpp
//静态区间第k小
#include<bits/stdc++.h>
#define LL long long
#define maxn 200005

using namespace std;

int n, m, q, cnt;
int L[maxn << 5], R[maxn << 5], sum[maxn << 5], T[maxn], a[maxn], b[maxn];

inline int build(int l, int r)
{
    int rt = ++cnt;
    sum[rt] = 0;
    if (l < r)
    {
        int mid = (l + r) >> 1;
        L[rt] = build(l, mid);
        R[rt] = build(mid + 1, r);
    }
    return rt;
}

inline int change(int pre, int l, int r, int x)
{
    int rt = ++cnt;
    L[rt] = L[pre], R[rt] = R[pre], sum[rt] = sum[pre] + 1;
    if (l < r)
    {
        int mid = (l + r) >> 1;
        if (x <= mid)L[rt] = change(L[pre], l, mid, x);
        else R[rt] = change(R[pre], mid + 1, r, x);
    }
    return rt;
}

inline int search(int u, int v, int l, int r, int k)
{
    if (l >= r)return l;
    int x = sum[L[v]] - sum[L[u]];
    int mid = (l + r) >> 1;
    if (x >= k)return search(L[u], L[v], l, mid, k);
    else return search(R[u], R[v], mid + 1, r, k - x);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    T[0] = build(1, m);

    for (int i = 1; i <= n; i++)
    {
        int t = lower_bound(b + 1, b + m + 1, a[i]) - b;
        T[i] = change(T[i - 1], 1, m, t);
    }

    while (q--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int t = search(T[x - 1], T[y], 1, m, z);
        printf("%d\n", b[t]);
    }

    return 0;
}


```

### 乘法逆元2.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 5000005
using namespace std;
int n, k, p, a[N], suf[N], pre[N];
int fz;
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
int work(int x)
{
	if (x == 1)return 1;
	return ((int)(p - p / x) * work(p % x) % p);
}
signed main()
{
	n = read(), p = read(), k = read();
	int K = k;
	for (int i = 1; i <= n; i++)
		a[i] = read();
	pre[0] = suf[n + 1] = 1;
	for (int i = 1; i <= n; i++)
		pre[i] = (int)pre[i - 1] * a[i] % p;
	for (int i = n; i >= 1; i--)
		suf[i] = (int)(suf[i + 1] * a[i]) % p;
	for (int i = 1; i <= n; i++)
	{
		fz = (fz + (int)K * pre[i - 1] % p * suf[i + 1]) % p;
		//ans=(ans+(LL)j*pre[i-1]%md*suf[i+1])%md;
		K = (int)(K * k) % p;
	}
	//printf("%d\n", fz);
	printf("%lld\n", (fz * (int)work(pre[n]) % p));
	return 0;
}
```

### 乘法逆元2_2.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 5000005
using namespace std;
int n, p, k, s[N], t[N], a[N], ans, K;
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
int work(int x)
{
	if (x == 1)return 1;
	return (int)(p - p / x) * (work(p % x)) % p;
}
signed main()
{
	n = read(), p = read(), k = read();
	K = k;
	s[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		s[i] = (int)s[i - 1] * a[i] % p;
	}
	t[n] = work(s[n]);
	for (int i = n - 1; i >= 1; i--)
		t[i] = (int)t[i + 1] * a[i + 1] % p;
	for (int i = 1; i <= n; i++)
	{
		ans = (ans + ((((int)t[i] * s[i - 1]) % p) * K) % p) % p;
		K = (int)(K * k) % p;
	}
	// for(int i=n;i;--i)
	//      ans=((ll)t[i]*s[i-1]%p+ans)*k%p;
	printf("%lld\n", ans);
	return 0;
}
```

### 二分.cpp
```cpp
#include <bits/stdc++.h>
#define INF 2147483647
#define LL long long
#define N 100005
using namespace std;
int a[N];
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
	/*
	while(l<=r)
	{
		LL mid=(l+r)>>1;
		if(ok(mid))
		{
			ans=min(ans,mid);
			r=mid-1;
		}
		else l=mid+1;
	}
	*/
	int n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	int pos3 = lower_bound(a + 1, a + n + 1, k, greater<int>()) - a - 1;
	printf("%d\n", pos3);
	return 0;
}
```

### 二分01规划SLF优化负环.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 1005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int n, m, vis[N], cnt[N], f[N];
double d[N];
vector<pair<int, double> >a[N];
vector<pair<pii, int> >e;
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
int ok(double now)
{
	stack<int>q;
	for (int i = 1; i <= n; i++)
	{
		vis[i] = cnt[i] = 0;
		d[i] = INF;
		q.push(i);
	}
	while (q.size())
	{
		int x = q.top();
		q.pop();
		vis[x] = 0;
		if (cnt[x] >= n)
			return 1;
		for (auto [y, z] : a[x])
		{
			double val = now * z - f[y];
			if (d[x] + val < d[y])
			{
				d[y] = d[x] + val;
				cnt[y]++;
				if (!vis[y])
					q.push(y);
				vis[y] = 1;
			}
		}
	}
	return 0;
}
signed main()
{
	n = read(), m = read();
	e.resize(m);
	for (int i = 1; i <= n; i++)
		f[i] = read();
	for (int i = 0; i < m; i++)
	{
		int x = read(), y = read(), z = read();
		a[x].emplace_back(y, z);
	}
	double L = 0.0, R = 1000.0, eps = 1e-4;
	double ans = 0;
	for (int i = 1; i <= 30; i++)
	{
		double mid = (L + R) / 2.0;
		if (ok(mid))
		{
			ans = max(ans, mid);
			L = mid;
		}
		else
			R = mid;
	}
	printf("%.2f\n", ans);
	return 0;
}
```

### 倍增LCA.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
int n, m, s, lg[N], dep[N], f[N][22], col[N];
vector<int>a[N];

inline int read()
{
	int X = 0, w = 0; char ch = 0;
	while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

void dfs(int x, int fa)
{
	dep[x] = dep[fa] + 1;
	f[x][0] = fa;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		f[x][i] = f[f[x][i - 1]][i - 1];
	for (auto y : a[x])
		if (y != fa)
			dfs(y, x);
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	while (dep[x] != dep[y])
		x = f[x][lg[dep[x] - dep[y]] - 1];
	if (x == y)return x;
	for (int i = lg[dep[x]]; i >= 0; i--)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}
int getdis(int x, int y)
{
	return dep[x] + dep[y] - 2 * dep[LCA(x, y)];
}
void work()
{
	int n = read(), m = read(), root = read();
	for (int i = 1; i <= n - 1; i++)
	{
		int x = read(), y = read();
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(root, 0);
	while (m--)
	{
		int x = read(), y = read();
		printf("%d\n", LCA(x, y));
	}
}
void init()
{
	for (int i = 1; i < N; i++)
	{
		lg[i] = lg[i - 1];
		if (i == (1 << lg[i - 1]))lg[i]++;
	}
}
int main()
{
	int T = read();
	while (T--)
		work();
	return 0;
}


```

### 全排列.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;
inline int read()
{
	int X = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch)) { w |= ch == '-'; ch = getchar(); }
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	int n = read();
	vector<int>id(n);
	for (int i = 1; i <= n; i++)
		id[i - 1] = i;
	do
	{
		for (auto x : id)
			printf("%d ", x);
		puts("");
	} while (next_permutation(all(id)));
	return 0;
}
```

### 凸包.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int n, s[N], cnt;
double ans;
struct Node {
	double x, y;
} p[N];
inline int cmp(Node a, Node b)
{
	if (a.x != b.x)return a.x < b.x;
	return a.y < b.y;
}
Node getvec(Node a, Node b)
{
	return Node{(b.x - a.x), (b.y - a.y)};
}
double chaji(Node a, Node b)
{
	return (a.x * b.y - b.x * a.y);
}
double dis(Node a, Node b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	sort(p + 1, p + n + 1, cmp);
	s[++cnt] = 1, s[++cnt] = 2;
	for (int i = 3; i <= n; i++)
	{
		Node u = getvec(p[s[cnt - 1]], p[s[cnt]]);
		Node v = getvec(p[s[cnt]], p[i]);
		while (chaji(u, v) < 0.0)
		{
			if (cnt == 1)break;
			cnt--;
			u = getvec(p[s[cnt - 1]], p[s[cnt]]);
			v = getvec(p[s[cnt]], p[i]);
		}
		s[++cnt] = i;
	}
	int tep = cnt;
	s[++cnt] = n, s[++cnt] = n - 1;
	for (int i = n - 2; i >= 1; i--)
	{
		Node u = getvec(p[s[cnt - 1]], p[s[cnt]]);
		Node v = getvec(p[s[cnt]], p[i]);
		while (chaji(u, v) < 0.0)
		{
			if (cnt == tep + 1)break;
			cnt--;
			u = getvec(p[s[cnt - 1]], p[s[cnt]]);
			v = getvec(p[s[cnt]], p[i]);
		}
		s[++cnt] = i;
	}
	for (int i = 1; i <= cnt - 1; i++)
		ans += dis(p[s[i]], p[s[i + 1]]);
	printf("%.2lf\n", ans);
	return 0;
}
```

### 分块.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 100005
using namespace std;
int a[N], id[N], L[N], R[N], sum[N], lazy[N];
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
signed main()
{
    int n = read(), m = read();
    int len = sqrt(n);
    int tot = (n + len - 1) / len;
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += a[i];
    }
    for (int i = 1; i <= tot; i++)
    {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
    }
    while (m--)
    {
        int p = read();
        if (p == 1)
        {
            int x = read(), y = read(), z = read();
            if (id[x] == id[y])
                for (int i = x; i <= y; i++)
                    a[i] += z, sum[id[i]] += z;
            else
            {
                for (int i = x; i <= R[id[x]]; i++)
                    a[i] += z, sum[id[i]] += z;
                for (int i = L[id[y]]; i <= y; i++)
                    a[i] += z, sum[id[i]] += z;
                for (int i = id[x] + 1; i <= id[y] - 1; i++)
                    lazy[i] += z;
            }
        }
        else
        {
            int x = read(), y = read();
            int s = 0;
            if (id[x] == id[y])
                for (int i = x; i <= y; i++)
                    s += a[i] + lazy[id[i]];
            else
            {
                for (int i = x; i <= R[id[x]]; i++)
                    s += a[i] + lazy[id[i]];
                for (int i = L[id[y]]; i <= y; i++)
                    s += a[i] + lazy[id[i]];
                for (int i = id[x] + 1; i <= id[y] - 1; i++)
                    s += sum[i] + lazy[i] * len;
            }
            printf("%lld\n", s);
        }
    }
    return 0;
}
```

### 割点.cpp
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int dfn[N], low[N], cnt, gd[N];
vector<int> a[N];
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
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++cnt;
	int son = 0;
	for (auto y : a[x])
	{
		if (!dfn[y])
		{
			tarjan(y, fa);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x] && x != fa)
				gd[x] = 1;
			if (x == fa)
				son++;
		}
		low[x] = min(low[x], dfn[y]);
	}
	if (son >= 2 && x == fa)
		gd[x] = 1;
}
void work()
{
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i, i);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (gd[i])
			ans++;
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		if (gd[i])
			printf("%d ", i);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 匈牙利算法.cpp
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int n, m, e, match[maxn], vis[maxn], x, y, ans;
vector<int>v[maxn];
int find(int x)
{
    for (int i = 0; i < v[x].size(); i++)
    {
        int y = v[x][i];
        if (!vis[y])
        {
            vis[y] = 1;
            if (!match[y] || find(match[y])) {
                match[y] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1; i <= e; i++)
    {
        scanf("%d%d", &x, &y);
        if (x <= n && y <= m)
            v[x].push_back(y);
    }
    for (int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof(vis));
        if (find(i))ans++;
    }
    cout << ans;
}

```

### 单调栈.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 5005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int a[N][N], c[N][N];
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
void work()
{
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			a[i][j] = read();
			c[i][j] = 0;
		}
	for (int j = 1; j <= m; j++)
		for (int i = 1; i <= n; i++)
		{
			if (a[i][j] >= a[i - 1][j])
				c[i][j] = c[i - 1][j] + 1;
			else
				c[i][j] = 1;
		}
	int ans = 0;
	stack<int>s;
	for (int i = 1; i <= n; i++)
	{
		vector<int>val(m + 2), L(m + 2), R(m + 2);
		for (int j = 1; j <= m; j++)
			val[j] = c[i][j];
		val[0] = val[m + 1] = 0;
		while (s.size())s.pop();
		for (int j = 0; j <= m + 1; j++)
		{
			while (s.size() && val[s.top()] >= val[j])
				s.pop();
			if (s.size())
				L[j] = s.top();
			s.push(j);
		}
		while (s.size())s.pop();
		for (int j = m + 1; j >= 0; j--)
		{
			while (s.size() && val[s.top()] >= val[j])
				s.pop();
			if (s.size())
				R[j] = s.top();
			s.push(j);
		}
		for (int j = 1; j <= m; j++)
			ans = max(ans, val[j] * (R[j] - L[j] - 1));
	}
	printf("%d\n", ans);
}
signed main()
{
	int T = 1; cin >> T;
	while ( T-- )
		work();
	return 0;
}
```

### 取模.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define int long long
#define endl '\n'
#define N 555
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;

template<int T>
struct ModInt {
	const static int MD = T;
	int x;
	ModInt(int x = 0) : x(x % MD) {}
	int get() { return x; }
	ModInt operator + (const ModInt& that) const { int x0 = x + that.x; return ModInt(x0 < MD ? x0 : x0 - MD); }
	ModInt operator - (const ModInt& that) const { int x0 = x - that.x; return ModInt(x0 < MD ? x0 + MD : x0); }
	ModInt operator * (const ModInt& that) const { return ModInt((long long)x * that.x % MD); }
	ModInt operator / (const ModInt& that) const { return *this * that.inverse(); }
	void operator += (const ModInt& that) { x += that.x; if (x >= MD) x -= MD; }
	void operator -= (const ModInt& that) { x -= that.x; if (x < 0) x += MD; }
	void operator *= (const ModInt& that) { x = (long long)x * that.x % MD; }
	void operator /= (const ModInt& that) { *this = *this / that; }
	ModInt inverse() const {
		int a = x, b = MD, u = 1, v = 0;
		while (b) {
			int t = a / b;
			a -= t * b; std::swap(a, b);
			u -= t * v; std::swap(u, v);
		}
		if (u < 0) u += MD;
		return u;
	}
};
typedef ModInt<P> mint;
mint m;
```

### 可持久化KMP.cpp
```cpp
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
```

### 启发式合并.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int sz[N], fa[N];
set<int>rb[N], cb[N];
queue<pii>q;
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
	if (fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}
void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y)return;
	if (cb[x].size() > cb[y].size())
	{
		swap(x, y);
		swap(rb[x], rb[y]);
	}
	fa[x] = y;
	sz[y] += sz[x];
	for (auto tep : cb[x])
	{
		int v = find(tep);
		if (v == y)continue;
		rb[v].erase(x);
		rb[v].insert(y);
		cb[y].insert(v);
		if (rb[v].size() == 1)
			q.push({v, *rb[v].begin()});
	}
	cb[y].erase(x);
}
void work(int num)
{
	int n = read();
	for (int i = 1; i <= n; i++)
	{
		rb[i].clear(), cb[i].clear();
		fa[i] = i;
		sz[i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		int m = read();
		while (m--)
		{
			int x = read();
			rb[i].insert(x);
			cb[x].insert(i);
		}
	}
	for (int i = 1; i <= n; i++)
		if (rb[i].size() == 1)
			q.push({i, *rb[i].begin()});
	while (q.size())
	{
		auto tep = q.front();
		q.pop();
		merge(tep.first, tep.second);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, sz[find(i)]);
	printf("Case #%d: %d\n", num, ans);
}
signed main()
{
	int T = read();
	for (int i = 1; i <= T; i++)
		work(i);
	return 0;
}
```

### 堆优化dij.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int vis[N], d[N];
vector<pii> a[N];
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
signed main()
{
	int n = read(), m = read(), s = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		a[x].emplace_back(y, z);
	}
	memset(d, 0x3f, sizeof(d));
	d[s] = 0;
	priority_queue<pii> q;
	q.push({0, s});
	while (!q.empty())
	{
		auto [val, x] = q.top();
		val = -val;
		q.pop();
		if (vis[x] || val > d[x])
			continue;
		vis[x] = 1;
		for (auto [y, z] : a[x])
			if (val + z < d[y])
			{
				d[y] = val + z;
				q.push({-d[y], y});
			}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", d[i]);
	return 0;
}

```

### 堆优化prim.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define endl '\n'
#define N 5005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int d[N];
vector<pair<int, int> >a[N];
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

signed main()
{
	int n = read(), m = read();
	vector<int>vis(n + 1);
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		a[x].emplace_back(y, z);
		a[y].emplace_back(x, z);
	}
	memset(d, 0x7f, sizeof(d));
	d[1] = 0;
	int cnt = 0;
	int ans = 0;
	priority_queue<pair<int, int> >q;
	q.push({0, 1});
	while (q.size() && cnt < n)
	{
		auto [val, x] = q.top();
		q.pop();
		if (vis[x])continue;
		vis[x] = 1;
		cnt++;
		ans += -val;
		for (auto [y, z] : a[x])
			if (d[y] > z)
			{
				d[y] = z;
				if (!vis[y])
					q.push({ -d[y], y});
			}
	}
	if (cnt == n)
		printf("%lld\n", ans);
	else
		puts("orz");
	return 0;
}
```

### 并查集.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 200005
using namespace std;
namespace UF
{
int fa[N], rank[N];
inline void init(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		fa[i] = i;
		rank[i] = 1;
	}
}
int find(int x)
{
	return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
inline void merge(int i, int j)
{
	int x = find(i), y = find(j);
	if (rank[x] <= rank[y])
		fa[x] = y;
	else
		fa[y] = x;
	if (rank[x] == rank[y] && x != y)
		rank[y]++;
}
inline bool same(int i, int j)
{
	return find(i) == find(j);
}
} // namespace UF
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
int main()
{
	int n = read(), m = read();
	UF::init(n);
	while (m--)
	{
		int opt = read(), x = read(), y = read();
		if (opt == 1)
			UF::merge(x, y);
		else
		{
			if (UF::same(x, y))
				printf("Y\n");
			else
				printf("N\n");
		}
	}
	return 0;
}
```

### 手写hash.cpp
```cpp
static struct HashTable {
	int head[HASHMOD];
	int key[HASHSIZE + 10], val[HASHSIZE + 10], nxt[HASHSIZE + 10], cnt;
	void clear() {
		cnt = 0;
		memset(head, 0, sizeof(head));
	}
	bool count(const int k) {
		for (int i = head[k % HASHMOD]; i; i = nxt[i])
			if (key[i] == k) return true;
		return false;
	}
	int operator[](const int k) {
		for (int i = head[k % HASHMOD]; i; i = nxt[i]) {
			if (key[i] == k) return val[i];
		}
		return 0;
	}
	void add(int k, int v) {
		int p = k % HASHMOD;
		nxt[++cnt] = head[p];
		key[cnt] = k; val[cnt] = v;
		head[p] = cnt;
	}
} tb;
```

### 无汇源上下界可行流.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 500005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N];
vector<int> ans[N];
struct Node
{
	int from, to, min, max;
} e[N];

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
inline void addage(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
inline void add(int x, int y, int mini, int maxn)
{
	addage(x, y, maxn - mini);
	addage(y, x, 0);
}
int bfs()
{
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(S);
	d[S] = 1;
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				q.push(y);
				d[y] = d[x] + 1;
				if (y == T)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == T)
		return flow;
	int k, rest = flow;
	for (int i = from[x]; i && rest; i = Next[i])
	{
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(rest, val[i]));
			if (!k)
				d[y] = 0;
			val[i] -= k;
			val[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		int tep = 0;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read();
	vector<int> delta(n + 1);
	S = 0, T = n + 1;
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read(), d = read();
		add(a, b, c, d);
		e[i] = {a, b, c, d};
		delta[a] -= c;
		delta[b] += c;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
		if (delta[i] > 0)
		{
			sum += delta[i];
			add(S, i, 0, delta[i]);
		}
		else if (delta[i] < 0)
			add(i, T, 0, -delta[i]);
	int maxflow = dinic();
	if (maxflow != sum)
	{
		puts("NO");
		return;
	}
	puts("YES");
	for (int i = 1; i <= m; i++)
		printf("%d\n", e[i].min + val[i << 1 | 1]);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 普通平衡树.cpp
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define LL long long
#define MAXN 100005

using namespace std;
int n, cnt, root;
struct Node {
	int v, rnd, son[2], size;
} tree[MAXN];

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

void PushUp(int k)
{
	tree[k].size = tree[tree[k].son[0]].size + tree[tree[k].son[1]].size + 1;
}

int build(int v)
{
	++cnt;
	tree[cnt].size = 1;
	tree[cnt].v = v;
	tree[cnt].rnd = rand();
	return cnt;
}

int merge(int x, int y)
{
	if (!x || !y)return x + y;
	if (tree[x].rnd < tree[y].rnd)
	{
		tree[x].son[1] = merge(tree[x].son[1], y);
		PushUp(x);
		return x;
	}
	else
	{
		tree[y].son[0] = merge(x, tree[y].son[0]);
		PushUp(y);
		return y;
	}
}

void split(int now, int k, int &x, int &y)
{
	if (!now)x = y = 0;
	else
	{
		if (tree[now].v <= k)
		{
			x = now;
			split(tree[now].son[1], k, tree[now].son[1], y);
		}
		else
		{
			y = now;
			split(tree[now].son[0], k, x, tree[now].son[0]);
		}
		PushUp(now);
	}
}

int kth(int now, int k)
{
	while (1)
	{
		if (k <= tree[tree[now].son[0]].size)
			now = tree[now].son[0];
		else
		{
			if (k == tree[tree[now].son[0]].size + 1)
				return now;
			else
			{
				k -= tree[tree[now].son[0]].size + 1;
				now = tree[now].son[1];
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	n = read();
	int x, y, z;
	while (n--)
	{
		int opt = read(), a = read();
		if (opt == 1)
		{
			split(root, a, x, y);
			root = merge(merge(x, build(a)), y);
		}//插入x
		if (opt == 2)
		{
			split(root, a, x, z);
			split(x, a - 1, x, y);
			y = merge(tree[y].son[0], tree[y].son[1]);
			root = merge(merge(x, y), z);
		}//删除x
		if (opt == 3)
		{
			split(root, a - 1, x, y);
			printf("%d\n", tree[x].size + 1);
			root = merge(x, y);
		}//查询x的排名
		if (opt == 4)
			printf("%d\n", tree[kth(root, a)].v);//查询排名为x的数
		if (opt == 5)
		{
			split(root, a - 1, x, y);
			printf("%d\n", tree[kth(x, tree[x].size)].v);
			root = merge(x, y);
		}//求x前驱
		if (opt == 6)
		{
			split(root, a, x, y);
			printf("%d\n", tree[kth(y, 1)].v);
			root = merge(x, y);
		}//求x后缀
	}
	return 0;
}
```

### 最大权闭合子图.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 500005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N], cur[N];
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
inline void addage(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
inline void add(int x, int y, int z)
{
	addage(x, y, z);
	addage(y, x, 0);
}
int bfs()
{
	queue<int> q;
	memset(d, 0, sizeof(d));
	d[S] = 1;
	cur[S] = from[S];
	q.push(S);
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				d[y] = d[x] + 1;
				cur[y] = from[y];
				q.push(y);
				if (y == T)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == T)
		return flow;
	int k, rest = flow;
	for (int i = from[x]; i && rest; i = Next[i])
	{
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(rest, val[i]));
			if (!k)
				d[y] = 0;
			val[i] -= k;
			val[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		int tep;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read();
	S = 0, T = n + m + 1;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		add(i + m, T, x); // 负权点到T
	}
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read();
		add(S, i, c);		// S到正权点
		add(i, m + a, INF); // i需要的依赖
		add(i, m + b, INF); // i需要的依赖
		ans += c;			// 计算所有正权点的和
	}
	printf("%lld\n", ans - dinic()); //所有正权点的和-最小割
	return;
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 最小点权覆盖.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 500005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N], cur[N];
int vis[N];
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
inline void addage(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
inline void add(int x, int y, int z)
{
	addage(x, y, z);
	addage(y, x, 0);
}
int bfs()
{
	queue<int> q;
	memset(d, 0, sizeof(d));
	d[S] = 1;
	cur[S] = from[S];
	q.push(S);
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				d[y] = d[x] + 1;
				cur[y] = from[y];
				q.push(y);
				if (y == T)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == T)
		return flow;
	int k, rest = flow;
	for (int i = from[x]; i && rest; i = Next[i])
	{
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(rest, val[i]));
			if (!k)
				d[y] = 0;
			val[i] -= k;
			val[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		int tep;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void dfs(int x)
{
	vis[x] = 1;
	for (int i = from[x]; i; i = Next[i])
	{
		if (!val[i]) //在残量网络上dfs
			continue;
		int y = to[i];
		if (!vis[y])
			dfs(y);
	}
}
void work()
{
	int n = read(), m = read();
	S = 0, T = 2 * n + 1;
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		add(S, i, x); // S到每个左点，边权为点权
	}
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		add(i + n, T, x); //右点到T
	}

	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		add(y, x + n, INF); //左点到右点
	}
	printf("%d\n", dinic());
	dfs(S);
	int res = 0;
	for (int i = 2; i <= cnt; i += 2)
	{
		int y = to[i], x = to[i ^ 1];
		if (vis[x] && !vis[y]) //删点的数量
			res++;
	}
	printf("%d\n", res);
	for (int i = 2; i <= cnt; i += 2)
	{
		int y = to[i], x = to[i ^ 1];
		if (vis[x] && !vis[y])
		{
			if (x == S)
				printf("%d +\n", y);
			if (y == T)
				printf("%d -\n", x - n);
		}
	}
	return;
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 有汇源上下界最大流.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 500005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N];
vector<int> ans[N];
struct Node
{
	int from, to, min, max;
} e[N];

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
inline void addage(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
inline void add(int x, int y, int mini, int maxn)
{
	addage(x, y, maxn - mini);
	addage(y, x, 0);
}
int bfs()
{
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(S);
	d[S] = 1;
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				q.push(y);
				d[y] = d[x] + 1;
				if (y == T)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == T)
		return flow;
	int k, rest = flow;
	for (int i = from[x]; i && rest; i = Next[i])
	{
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(rest, val[i]));
			if (!k)
				d[y] = 0;
			val[i] -= k;
			val[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		int tep = 0;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read(), s = read(), t = read();
	vector<int> delta(n + 1);
	S = 0, T = n + 1;
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read(), d = read();
		add(a, b, c, d);
		e[i] = {a, b, c, d};
		delta[a] -= c;
		delta[b] += c;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
		if (delta[i] > 0)
		{
			sum += delta[i];
			add(S, i, 0, delta[i]);
		}
		else if (delta[i] < 0)
			add(i, T, 0, -delta[i]);
	add(t, s, 0, INF);
	int maxflow = dinic();
	if (maxflow != sum)
	{
		puts("No Solution");
		return;
	}
	int res = val[cnt];
	S = s, T = t;
	val[cnt] = val[cnt - 1] = 0;
	printf("%lld\n", res + dinic());
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 有汇源上下界最小流.cpp
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 400005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N], cur[N];
struct Node
{
	int from, to, min, max;
} e[N];

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
inline void addage(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
inline void add(int x, int y, int mini, int maxn)
{
	addage(x, y, maxn - mini);
	addage(y, x, 0);
}
int bfs()
{
	queue<int> q;
	memset(d, 0, sizeof(d));
	d[S] = 1;
	cur[S] = from[S];
	q.push(S);
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				d[y] = d[x] + 1;
				cur[y] = from[y];
				q.push(y);
				if (y == T)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == T)
		return flow;
	int k, rest = flow;
	for (int i = cur[x]; i && rest; i = Next[i])
	{
		cur[x] = i;
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(val[i], rest));
			if (!k)
				d[y] = 0;
			rest -= k;
			val[i] -= k;
			val[i ^ 1] += k;
		}
	}
	return flow - rest;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		int tep = 0;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read(), s = read(), t = read();
	vector<int> delta(n + 1);
	S = 0, T = n + 1;
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read(), d = read();
		add(a, b, c, d);
		e[i] = {a, b, c, d};
		delta[a] -= c;
		delta[b] += c;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
		if (delta[i] > 0)
		{
			sum += delta[i];
			add(S, i, 0, delta[i]);
		}
		else if (delta[i] < 0)
			add(i, T, 0, -delta[i]);
	add(t, s, 0, INF);
	int maxflow = dinic();
	if (maxflow < sum)
	{
		puts("No Solution");
		return;
	}
	int res = val[cnt];
	S = t, T = s;
	val[cnt] = val[cnt - 1] = 0;
	printf("%d\n", res - dinic());
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 树上启发式合并.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define int long long
#define endl '\n'
#define N 500005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int col[N], sz[N], son[N], cnt[N][26], ans[N], dep[N];
int flag, sum, maxn, tot;
char st[N];
vector<int>a[N];
vector<pii>ask[N];
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
void dfs1(int x, int fa)
{
	sz[x] = 1;
	dep[x] = dep[fa] + 1;
	for (auto y : a[x])
	{
		if (y == fa)continue;
		dfs1(y, x);
		sz[x] += sz[y];
		if (sz[y] > sz[son[x]])
			son[x] = y;
	}
}
void cal(int x, int fa, int opt)
{
	cnt[dep[x]][st[x] - 'a'] += opt;
	for (auto y : a[x])
		if (y != fa && y != flag)
			cal(y, x, opt);
}
int check(int k)
{
	int p = 0;
	for (int i = 0; i < 26; i++)
		p += (cnt[k][i] % 2);
	return p <= 1;
}
void dfs2(int x, int fa, int opt)
{
	for (auto y : a[x])
		if (y != fa && y != son[x])
			dfs2(y, x, 0);
	if (son[x])
	{
		dfs2(son[x], x, 1);
		flag = son[x];
	}
	cal(x, fa, 1);
	flag = 0;
	for (auto [k, id] : ask[x])
		ans[id] = check(k);
	if (!opt)
		cal(x, fa, -1);
}
void work()
{
	int n = read(), m = read();
	for (int i = 2; i <= n; i++)
	{
		int x = read();
		a[x].push_back(i);
		a[i].push_back(x);
	}
	scanf("%s", st + 1);
	dfs1(1, 0);
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		ask[x].push_back({ y, i });
	}
	dfs2(1, 0, 0);
	for (int i = 1; i <= m; i++)
		if (ans[i])
			puts("Yes");
		else
			puts("No");
}
signed main()
{
	work();
	return 0;
}
```

### 树同构哈希重心.cpp
```cpp
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
```

### 树状数组.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 500005
using namespace std;
int n, m, tree[N];
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
inline int lowbit(int x)
{
	return x & -x;
}
void add(int x, int k)
{
	while (x <= n)
	{
		tree[x] += k;
		x += lowbit(x);
	}
}
int sum(int x)
{
	int s = 0;
	while (x)
	{
		s += tree[x];
		x -= lowbit(x);
	}
	return s;
}
signed main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		add(i, x);
	}
	while (m--)
	{
		int opt = read(), x = read(), y = read();
		if (opt == 1)
			add(x, y);
		else
			printf("%lld\n", sum(y) - sum(x - 1));
	}
	return 0;
}
```

### 树链剖分.cpp
```cpp
#include <bits/stdc++.h>
//#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define int long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int n, m, root, P, id[N], f[N], son[N], cnt;
int top[N], sum, a[N], b[N], dep[N], sz[N];
vector<int>v[N];
struct node {
	int l, r, w, f;
} tree[N << 2];
inline int read()
{
	int X = 0, w = 0; char ch = 0;
	while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

void PushUp(int k)
{
	tree[k].w = (tree[k << 1].w + tree[k << 1 | 1].w) % P;
}

void PushDown(int k)
{
	if (!tree[k].f)return;
	int x = tree[k].f;
	tree[k].f = 0;
	tree[k << 1].f += x;
	tree[k << 1 | 1].f += x;
	tree[k << 1].w += x * (tree[k << 1].r - tree[k << 1].l + 1);
	tree[k << 1 | 1].w += x * (tree[k << 1 | 1].r - tree[k << 1 | 1].l + 1);
	tree[k << 1].w %= P;
	tree[k << 1 | 1].w %= P;
}

void build(int k, int L, int R)
{
	tree[k].l = L;
	tree[k].r = R;
	if (L == R)
	{
		tree[k].w = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(k << 1, L, mid);
	build(k << 1 | 1, mid + 1, R);
	PushUp(k);
}

void change(int k, int L, int R, int d)
{
	if (tree[k].l >= L && tree[k].r <= R)
	{
		tree[k].f += d;
		tree[k].w += d * (tree[k].r - tree[k].l + 1);
		tree[k].w %= P;
		return;
	}
	PushDown(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= L)change(k << 1, L, R, d);
	if (R > mid)change(k << 1 | 1, L, R, d);
	PushUp(k);
}

int search(int k, int L, int R)
{
	int ans = 0;
	if (tree[k].l >= L && tree[k].r <= R)
		return tree[k].w % P;
	PushDown(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= L)ans += search(k << 1, L, R);
	if (R > mid)ans += search(k << 1 | 1, L, R);
	return ans % P;
}

void dfs1(int x, int fa)
{
	dep[x] = dep[fa] + 1;
	f[x] = fa;
	sz[x] = 1;
	for (auto y : v[x])
	{
		if (y == f[x])continue;
		dfs1(y, x);
		sz[x] += sz[y];
		if (sz[y] > sz[son[x]])
			son[x] = y;
	}
}

void dfs2(int x, int topf)
{
	top[x] = topf;
	id[x] = ++cnt;
	a[cnt] = b[x];
	if (!son[x])return;
	dfs2(son[x], topf);
	for (auto y : v[x])
		if (!id[y])
			dfs2(y, y);
}

void path_change(int x, int y, int z)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])swap(x, y);
		change(1, id[top[x]], id[x], z);
		x = f[top[x]];
	}
	if (dep[x] > dep[y])swap(x, y);
	change(1, id[x], id[y], z);
}

void path_search(int x, int y)
{
	int ans = 0;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])swap(x, y);
		ans += search(1, id[top[x]], id[x]);
		ans %= P;
		x = f[top[x]];
	}
	if (dep[x] > dep[y])swap(x, y);
	ans += search(1, id[x], id[y]);
	printf("%lld\n", ans % P);
}

void tree_change(int x, int y)
{
	change(1, id[x], id[x] + sz[x] - 1, y);
}

void tree_search(int x)
{
	printf("%lld\n", search(1, id[x], id[x] + sz[x] - 1));
}

signed main()
{
	n = read(), m = read(), root = read(), P = read();
	for (int i = 1; i <= n; i++)
		b[i] = read();
	for (int i = 1; i < n; i++)
	{
		int x = read(), y = read();
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs1(root, 0);
	dfs2(root, root);
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		int opt = read();
		if (opt == 1)
		{
			int x = read(), y = read(), z = read();
			path_change(x, y, z);
		}
		else if (opt == 2)
		{
			int x = read(), y = read();
			path_search(x, y);
		}
		else if (opt == 3)
		{
			int x = read(), y = read();
			tree_change(x, y);
		}
		else
		{
			int x = read();
			tree_search(x);
		}
	}
	return 0;
}
```

### 模拟退火.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define LL long long
#define N 1005
using namespace std;
struct Node
{
    int x, y, z;
} a[N];
int n;
double ansx, ansy, ansz, ans;
double down = 0.996;
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
double cal(double x, double y, double z)
{
    double tep = 0.0;
    for (int i = 1; i <= n; i++)
        tep = max(tep, sqrt((a[i].x - x) * (a[i].x - x) + (a[i].y - y) * (a[i].y - y) + (a[i].z - z) * (a[i].z - z)));
    return tep;
}
void SA()
{
    double t = 3000;
    while (t >= 1e-15)
    {
        double x1 = ansx + (rand() * 2 - RAND_MAX) * t;
        double y1 = ansy + (rand() * 2 - RAND_MAX) * t;
        double z1 = ansz + (rand() * 2 - RAND_MAX) * t;
        double ans1 = cal(x1, y1, z1);
        double d = ans1 - ans;
        if (d < 0)
        {
            ansx = x1;
            ansy = y1;
            ansz = z1;
            ans = ans1;
        }
        else if (exp(-d / t) * RAND_MAX > rand())
        {
            ansx = x1;
            ansy = y1;
            ansz = z1;
        }
        t *= down;
    }
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i].x = read(), a[i].y = read(), a[i].z = read();
        ansx += a[i].x;
        ansy += a[i].y;
        ansz += a[i].z;
    }
    ansx /= n;
    ansy /= n;
    ansz /= n;
    ans = cal(ansx, ansy, ansz);
    SA(), SA(), SA(), SA(), SA();

    printf("%.10lf\n", ans);
    return 0;
}
```

### 点双.cpp
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 500005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int dfn[N], low[N], cnt, gd[N];
int bcc;
vector<int> a[N], ans[N];
stack<int> S;
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
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++cnt;
	S.push(x);
	int son = 0;
	for (auto y : a[x])
	{
		if (!dfn[y])
		{
			son++;
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x])
			{
				ans[++bcc].push_back(x);
				while (ans[bcc].back() != y)
				{
					ans[bcc].push_back(S.top());
					S.pop();
				}
			}
		}
		else if (y != fa)
			low[x] = min(low[x], dfn[y]);
	}
	if (fa == 0 && son == 0)
		ans[++bcc].push_back(x);
}
void work()
{
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i, 0);
	printf("%d\n", bcc);
	for (int i = 1; i <= bcc; i++)
	{
		printf("%d ", ans[i].size());
		for (auto x : ans[i])
			printf("%d ", x);
		puts("");
	}
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 矩阵快速幂.cpp
```cpp
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
```

### 米勒罗宾.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 100005
using namespace std;
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
int qpow(int a, int n, int p)
{
    int ans = 1;
    while (n)
    {
        if (n & 1)
            ans = (__int128)ans * a % p;
        a = (__int128)a * a % p;
        n >>= 1;
    }
    return ans;
}
int is_prime(int x)
{
    if (x < 3)
        return x == 2;
    if (x % 2 == 0)
        return 0;
    int A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, d = x - 1, r = 0;
    while (d % 2 == 0)
        d /= 2, ++r;
    for (auto a : A)
    {
        int v = qpow(a, d, x);
        if (v <= 1 || v == x - 1)
            continue;
        for (int i = 0; i < r; ++i)
        {
            v = (__int128)v * v % x;
            if (v == x - 1 && i != r - 1)
            {
                v = 1;
                break;
            }
            if (v == 1)
                return 0;
        }
        if (v != 1)
            return 0;
    }
    return 1;
}
signed main()
{
    int x = read();
    printf("%lld\n", is_prime(x));
    return 0;
}
```

### 线性乘法逆元.cpp
```cpp
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
```

### 线性筛.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 1000005
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;
int vis[N];
vector<int>prime;
inline int read()
{
	int X = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch)) { w |= ch == '-'; ch = getchar(); }
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
void init(int n)
{
	vis[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!vis[i])prime.push_back(i);
		for (auto x : prime)
		{
			if (x * i > n)break;
			vis[x * i] = 1;
			if (i % x == 0)break;
		}
	}
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	init(N - 1);
	return 0;
}
```

### 线段树.cpp
```cpp
#include <bits/stdc++.h>
#include <cstdio>
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
struct Node
{
	int l, r, f;
	LL w;
} tree[N << 2];
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
void PushUp(int k)
{
	tree[k].w = tree[k << 1].w + tree[k << 1 | 1].w;
}
void PushDown(int k)
{
	if (!tree[k].f)
		return;
	int x = tree[k].f;
	tree[k].f = 0;
	tree[k << 1].f += x;
	tree[k << 1 | 1].f += x;
	tree[k << 1].w += x * (tree[k << 1].r - tree[k << 1].l + 1);
	tree[k << 1 | 1].w += x * (tree[k << 1 | 1].r - tree[k << 1 | 1].l + 1);
}
void build(int k, int L, int R)
{
	tree[k].l = L;
	tree[k].r = R;
	if (L == R)
	{
		tree[k].w = read();
		return;
	}
	int mid = (L + R) >> 1;
	build(k << 1, L, mid);
	build(k << 1 | 1, mid + 1, R);
	PushUp(k);
}
void change(int k, int L, int R, int x)
{
	if (tree[k].l >= L && tree[k].r <= R)
	{
		tree[k].f += x;
		tree[k].w += x * (tree[k].r - tree[k].l + 1);
		return;
	}
	PushDown(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= L)
		change(k << 1, L, R, x);
	if (mid < R)
		change(k << 1 | 1, L, R, x);
	PushUp(k);
}
LL query(int k, int L, int R)
{
	if (tree[k].l >= L && tree[k].r <= R)
		return tree[k].w;
	PushDown(k);
	LL sum = 0;
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= L)
		sum += query(k << 1, L, R);
	if (mid < R)
		sum += query(k << 1 | 1, L, R);
	return sum;
}
void work()
{
	int n = read(), m = read();
	build(1, 1, n);
	while (m--)
	{
		int opt = read();
		if (opt == 1)
		{
			int x = read(), y = read(), z = read();
			change(1, x, y, z);
		}
		else
		{
			int x = read(), y = read();
			printf("%lld\n", query(1, x, y));
		}
	}
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 组合数.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF ((1 << 31) - 1)
#define INFF ((1 << 63) - 1)
#define int long long
#define N 1000003
using namespace std;
int jc[N], jc_inv[N];
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
int qpow(int x, int y)
{
	int res = 1ll;
	x %= P;
	while (y)
	{
		if (y & 1ll)
			res = res * x % P;
		x = x * x % P;
		y >>= 1ll;
	}
	return res;
}
void init()
{
	jc[0] = 1;
	for (int i = 1; i < N; i++)
		jc[i] = (jc[i - 1] * i) % P;
	jc_inv[N - 1] = qpow(jc[N - 1], P - 2);
	for (int i = N - 1; i >= 1; i--)
		jc_inv[i - 1] = (jc_inv[i] * i) % P;
}
int C(int x, int y)
{
	if (x < y || y < 0)
		return 0;
	if (y == 0)
		return 1;
	return (jc[x] * jc_inv[y] % P) * jc_inv[x - y] % P;
}
signed main()
{
	int T = read();
	init();
	for (int t = 1; t <= T; t++)
	{
		int n = read(), m = read();
		printf("%lld\n", C(n, m));
	}
	return 0;
}

```

### 莫比乌斯反演.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 500005
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;
int a, b, c, d, k;
int vis[N], mu[N], sum[N];
vector<int> prime;
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
void init(int n)
{
	vis[1] = 1;
	mu[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!vis[i])
			prime.push_back(i), mu[i] = -1;
		for (auto x : prime)
		{
			if (x * i > n)
				break;
			vis[x * i] = 1;
			if (i % x == 0)
				break;
			mu[x * i] = -mu[i];
		}
	}
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + mu[i];
}
int get(int a, int b)
{
	int res = 0;
	for (int L = 1, R; L <= min(a, b); L = R + 1)
	{
		R = min(a / (a / L), b / (b / L));
		res += (sum[R] - sum[L - 1]) * ((a / k) / L) * ((b / k) / L);
	}
	return res;
}
void work()
{
	a = read(), b = read(), c = read(), d = read(), k = read();
	printf("%d\n", get(b, d) - get(a - 1, d) - get(b, c - 1) + get(a - 1, c - 1));
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	init(N - 1);
	int T = read();
	while (T--)
		work();
	return 0;
}
```

### 莫队.cpp
```cpp
#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 50005
using namespace std;
int n, m, k, cnt[N], a[N], len;
LL ans[N], ans_tep;
struct Node
{
    int l, r, id, pos;
} ask[N];
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
inline int cmp(Node x, Node y)
{
    if (x.pos != y.pos)return x.pos < y.pos;
    if (x.pos % 2)return x.r < y.r;
    else return x.r > y.r;
}
void add(int pos)
{
    ans_tep += 2 * cnt[a[pos]] + 1;
    cnt[a[pos]]++;
}
void remove(int pos)
{
    ans_tep += 1 - cnt[a[pos]] * 2;
    cnt[a[pos]]--;
}
int main()
{
    n = read(), m = read(), k = read();
    len = (int)sqrt(n);
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= m; i++)
    {
        ask[i].l = read(), ask[i].r = read();
        ask[i].id = i;
        ask[i].pos = (ask[i].l - 1) / len + 1;
    }
    sort(ask + 1, ask + m + 1, cmp);
    int L = 0, R = 0;
    for (int i = 1; i <= m; i++)
    {
        while (L < ask[i].l)remove(L++);
        while (L > ask[i].l)add(--L);
        while (R > ask[i].r)remove(R--);
        while (R < ask[i].r)add(++R);
        ans[ask[i].id] = ans_tep;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ans[i] - 1);
    return 0;
}
```

### 边双求割边.cpp
```cpp
#include <bits/stdc++.h>
#include <cstdio>
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
int dfn[N], low[N], cnt, gb[N], id[N];
int dcc;
stack<int> S;
vector<int> ans[N];
vector<pii> a[N];
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
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++cnt;
	for (auto [y, z] : a[x])
	{
		if (!dfn[y])
		{
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
			if (low[y] > dfn[x])
				gb[z] = 1;
		}
		else if (y != fa)
			low[x] = min(low[x], dfn[y]);
	}
}
void dfs(int x)
{
	id[x] = dcc;
	for (auto [y, z] : a[x])
		if (!gb[z] && !id[y])
			dfs(y);
}
void work()
{
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		a[x].push_back({y, i});
		a[y].push_back({x, i});
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i, 0);
	for (int i = 1; i <= n; i++)
		if (!id[i])
		{
			dcc++;
			dfs(i);
		}
	for (int i = 1; i <= n; i++)
		ans[id[i]].push_back(i);
	printf("%d\n", dcc);
	for (int i = 1; i <= dcc; i++)
	{
		printf("%d ", ans[i].size());
		for (auto x : ans[i])
			printf("%d ", x);
		puts("");
	}
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	work();
	return 0;
}
```

### 逆序对.cpp
```cpp
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
```

### 马拉车.cpp
```cpp
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
```

