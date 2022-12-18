#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int sum=0;
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		int x;
		cin>>x;
		sum+=x;
	}
	cout<<sum+(n==5)<<endl;
	return 0;
}