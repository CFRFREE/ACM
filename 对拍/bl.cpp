#include <bits/stdc++.h>
#define ll long long

using namespace std;

inline void solve() {
	ll n, k, a, b;
	cin >> n >> k >> a >> b;
	if (a == b) {
		cout << "YES\n";
		return;
	}
	if (abs(a - b) > k) cout << "YES\n";
	else if (n <= k) cout << "NO\n";
	else if ((abs(a - 1) > k || abs(a - n) > k) && (abs(b - 1) > k || abs(b - n) > k)) cout << "YES\n";
	else cout << "NO\n";
}

int main() {
	int test;
	cin >> test;
	while (test--) solve();
	return 0;
}