#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 200005
using namespace std;
int n, m;
struct Node
{
	int l, r, f, w;
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
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
void PushUp(int k)
{
	tree[k].w = tree[k << 1].w + tree[k << 1 | 1].w;
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
	if (mid >= L)change(k << 1, L, R, x);
	if (mid < R)change(k << 1 | 1, L, R, x);
	PushUp(k);
}
int query(int k, int L, int R)
{
	if (tree[k].l >= L && tree[k].r <= R)
		return tree[k].w;
	PushDown(k);
	int sum = 0;
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= L)sum += query(k << 1, L, R);
	if (mid < R)sum += query(k << 1 | 1, L, R);
	return sum;
}
int main()
{
	n = read(), m = read();
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
	return 0;
}