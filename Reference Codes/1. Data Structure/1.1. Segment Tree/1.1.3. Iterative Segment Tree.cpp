#include <iostream>
#define ll long long
using namespace std;

const int MAXN = 1e5;  // limit for array size

int N;  // array size
ll t[2 * MAXN];

void modify(int p, int value);
ll query(int L, int R);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i = 0; i < N; i++) cin >> t[N + i];
	for (int i = N - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];

	modify(0, 1);
	cout << query(3, 11);

	return 0;
}

void modify(int p, int value) {  // set value at position p
	for (t[p += N] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

ll query(int L, int R) {  // sum on interval [L, R)
	ll ret = 0;
	for (L += N, R += N; L < R; L >>= 1, R >>= 1) {
		if (L & 1) ret += t[L++];
		if (R & 1) ret += t[--R];
	}
	return ret;
}
