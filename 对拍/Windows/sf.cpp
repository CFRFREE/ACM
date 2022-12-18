#include "bits/stdc++.h"
#include <iterator>
#define P 1000000007
#define N 500005
#define int long long
using namespace std;
int tmp[N], sum1[N], sum2[N];
void init()
{
	tmp[2] = 1;
	for (int i = 3; i < N; i++)
		tmp[i] = (tmp[i - 1] * i) % P;
	for (int i = 1; i < N; i++)
	{
		sum1[i] = (sum1[i - 1] + i) % P;
		sum2[i] = (sum2[i - 1] + (i * i) % P) % P;
	}
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
void work()
{
	int n; cin >> n;
	int tep = (sum2[n] - sum1[n] + P) % P;
	cout << (tmp[n] * tep) % P << endl;
}
signed main()
{
	init();
	int T; cin >> T;
	while (T--)
		work();
	return 0;
}