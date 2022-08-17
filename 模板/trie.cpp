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