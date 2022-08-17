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