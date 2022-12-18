#include <algorithm>
#include <bits/stdc++.h>
#define P 19260817
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;
int a[N];
inline int read()
{
	int X = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch)) { w |= ch == '-'; ch = getchar(); }
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
void work()
{
	int n = read();
	for (int i = 1; i <= n; i++)
		a[i] = i;
	int ans = 0;
	do
	{
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				if (a[i] > a[j])
					ans = (ans + a[i] - a[j]) % P;
	} while (next_permutation(a + 1, a + n + 1));
	cout << ans << endl;
}
signed main()
{
	int T = read();
	while (T--)
		work();
	return 0;
}