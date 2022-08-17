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