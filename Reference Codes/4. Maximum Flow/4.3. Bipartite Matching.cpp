#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 1e3;

int N, M, A[MAX + 5], B[MAX + 5];
vector<int> adj[MAX + 5];
bool visited[MAX + 5];

void input();
int bMatch();
bool dfs(int a);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	int ans = bMatch();
	cout << ans << '\n';

	return 0;
}

void input() {
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		int cnt; cin >> cnt;
		while (cnt--) {
			int x; cin >> x;

			adj[i].push_back(x);
		}
	}
}

int bMatch() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));

	int ret = 0;
	for (int i = 1; i <= N; i++) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) ret++;
	}

	return ret;
}

bool dfs(int a) {
	visited[a] = true;
	for (int b : adj[a]) {
		if (B[b] == -1 || (!visited[B[b]] && dfs(B[b]))) {
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}
