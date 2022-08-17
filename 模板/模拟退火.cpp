#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define LL long long
#define N 1005
using namespace std;
struct Node
{
    int x, y, z;
} a[N];
int n;
double ansx, ansy, ansz, ans;
double down = 0.996;
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
double cal(double x, double y, double z)
{
    double tep = 0.0;
    for (int i = 1; i <= n; i++)
        tep = max(tep, sqrt((a[i].x - x) * (a[i].x - x) + (a[i].y - y) * (a[i].y - y) + (a[i].z - z) * (a[i].z - z)));
    return tep;
}
void SA()
{
    double t = 3000;
    while (t >= 1e-15)
    {
        double x1 = ansx + (rand() * 2 - RAND_MAX) * t;
        double y1 = ansy + (rand() * 2 - RAND_MAX) * t;
        double z1 = ansz + (rand() * 2 - RAND_MAX) * t;
        double ans1 = cal(x1, y1, z1);
        double d = ans1 - ans;
        if (d < 0)
        {
            ansx = x1;
            ansy = y1;
            ansz = z1;
            ans = ans1;
        }
        else if (exp(-d / t) * RAND_MAX > rand())
        {
            ansx = x1;
            ansy = y1;
            ansz = z1;
        }
        t *= down;
    }
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i].x = read(), a[i].y = read(), a[i].z = read();
        ansx += a[i].x;
        ansy += a[i].y;
        ansz += a[i].z;
    }
    ansx /= n;
    ansy /= n;
    ansz /= n;
    ans = cal(ansx, ansy, ansz);
    SA(), SA(), SA(), SA(), SA();

    printf("%.10lf\n", ans);
    return 0;
}