#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000000;

int N;
vector<int> p(MAX + 1, -1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	int Q; cin >> Q;
	while (Q--) {
		int q, a, b;
		cin >> q >> a >> b;

		if (q == 0) merge(a, b);
		if (q == 1) {
			if (find(a) == find(b)) cout << "YES\n";
			else cout << "NO\n";
		}
	}

	return 0;
}
