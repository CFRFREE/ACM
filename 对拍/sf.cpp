#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define int long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
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
	while (isdigit(ch))
		X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
void work()
{
	vector<int> v(3);
	int n = read();
	for (auto &x : v)
		x = read();
	int sum = 0ll;
	map<int, int> M;
	M[0ll] = 1ll;
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		sum += x;
		int tep = v.front();
		if (M.find(sum - tep) != M.end())
		{
			M.clear();
			M[0] = 1ll;
			sum = 0ll;
			v.erase(v.begin());
		}
		M[sum] = 1ll;
		if (!v.size())
		{
			puts("Yes");
			return;
		}
	}
	puts("No");
}
signed main()
{
	work();
	return 0;
}