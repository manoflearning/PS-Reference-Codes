#include <iostream>
#include <string>
#include <vector>
#define ll long long
using namespace std;

const int MAX = 1e6 + 5;
const ll MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;

string T, P;
ll d = 128, dexp1[MAX], dexp2[MAX];
vector<int> ans;

void rabinKarp();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	dexp1[0] = dexp2[0] = 1;
	for (int i = 1; i < MAX; i++) {
		dexp1[i] = d * dexp1[i - 1] % MOD1;
		dexp2[i] = d * dexp2[i - 1] % MOD2;
	}

	getline(cin, T);
	getline(cin, P);

	rabinKarp();

	cout << ans.size() << '\n';
	for (int i : ans) cout << i << ' ';

	return 0;
}

void rabinKarp() {
	int len = P.size();

	ll p1 = 0, p2 = 0, t1 = 0, t2 = 0;
	for (int i = 0; i < len; i++) {
		p1 = (d * p1 + P[i]) % MOD1;
		p2 = (d * p2 + P[i]) % MOD2;
		t1 = (d * t1 + T[i]) % MOD1;
		t2 = (d * t2 + T[i]) % MOD2;
	}

	if (p1 == t1 && p2 == t2) ans.push_back(0);

	for (int i = 1; i < T.size() - len + 1; i++) {
		t1 = (d * (t1 - dexp1[len - 1] * T[i - 1]) + T[i + len - 1]) % MOD1;
		t1 = (t1 + MOD1) % MOD1;
		t2 = (d * (t2 - dexp2[len - 1] * T[i - 1]) + T[i + len - 1]) % MOD2;
		t2 = (t2 + MOD2) % MOD2;
		if (p1 == t1 && p2 == t2) ans.push_back(i);
	}
}
