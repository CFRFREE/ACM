#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define int long long
#define endl '\n'
#define N 555
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;

template<int T>
struct ModInt {
	const static int MD = T;
	int x;
	ModInt(int x = 0) : x(x % MD) {}
	int get() { return x; }
	ModInt operator + (const ModInt& that) const { int x0 = x + that.x; return ModInt(x0 < MD ? x0 : x0 - MD); }
	ModInt operator - (const ModInt& that) const { int x0 = x - that.x; return ModInt(x0 < MD ? x0 + MD : x0); }
	ModInt operator * (const ModInt& that) const { return ModInt((long long)x * that.x % MD); }
	ModInt operator / (const ModInt& that) const { return *this * that.inverse(); }
	void operator += (const ModInt& that) { x += that.x; if (x >= MD) x -= MD; }
	void operator -= (const ModInt& that) { x -= that.x; if (x < 0) x += MD; }
	void operator *= (const ModInt& that) { x = (long long)x * that.x % MD; }
	void operator /= (const ModInt& that) { *this = *this / that; }
	ModInt inverse() const {
		int a = x, b = MD, u = 1, v = 0;
		while (b) {
			int t = a / b;
			a -= t * b; std::swap(a, b);
			u -= t * v; std::swap(u, v);
		}
		if (u < 0) u += MD;
		return u;
	}
};
typedef ModInt<P> mint;
mint m;