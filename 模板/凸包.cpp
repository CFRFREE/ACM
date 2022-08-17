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