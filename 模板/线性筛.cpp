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