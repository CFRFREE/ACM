#include<bits/stdc++.h>
#define LL long long
#define N 1000005
using namespace std;

int Next[N], ans, len1, len2;
string st1, st2;
vector<int>pos;

inline int read()
{
    int X = 0, w = 0; char ch = 0;
    while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

void KMP()
{
    Next[0] = -1;
    int k = -1;
    for (int q = 1; q < len2; q++)
    {
        while (k != -1 && st2[k + 1] != st2[q])
            k = Next[k];
        if (st2[k + 1] == st2[q])
            k++;
        Next[q] = k;
    }
    k = -1;
    for (int i = 0; i < len1; i++)
    {
        while (k != -1 && st2[k + 1] != st1[i])
            k = Next[k];
        if (st2[k + 1] == st1[i]) k++;
        if (k == len2 - 1)
        {
            i = i - len2 + 1;
            k = -1;
            cout << i + 1 << endl;
        }
    }
}

int main()
{
    cin >> st1;
    cin >> st2;
    len1 = st1.length();
    len2 = st2.length();
    KMP();
    for (int i = 0; i < len2; i++)
        cout << Next[i] + 1 << " ";
    return 0;
}

