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