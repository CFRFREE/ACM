#include "iostream"
#define P 1000000007
#define N 500005
using namespace std;
long long tmp[N], sum1[N], sum2[N];
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
void work()
{
	int n; cin >> n;
	cout << (tmp[n] * ((n * sum1[n]) % P - sum2[n] + P) % P) % P << endl;
}
signed main()
{
	init();
	int T; cin >> T;
	while (T--)
		work();
	return 0;
}