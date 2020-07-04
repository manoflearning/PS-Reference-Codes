const int MAX = 40000, MAXD = 15;

vector<int> adj[MAX + 5];
int N, depth[MAX + 5], par[MAX + 5][MAXD + 5];

void dfs(int now, int prv);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	dfs(1, 0);

	//점화식
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= N; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
	}

	int Q; cin >> Q;
	while (Q--) {
		//두 정점 u와 v가 주어질 때, lca 구하기
		int u, v;
		cin >> u >> v;

		if (depth[u] > depth[v]) swap(u, v);

		//두 노드의 깊이를 같게
		int diff = depth[v] - depth[u];
		for (int i = MAXD; i >= 0; i--) {
			if (diff & (1 << i)) {
				v = par[v][i];
				diff -= (1 << i);
			}
		}

		if (u != v) {
			for (int i = MAXD; i >= 0; i--) {
				if (par[u][i] != par[v][i]) {
					su = par[u][i];
					sv = par[v][i];
				}
			}
			u = par[u][0];
		}

		int lca = u;
		cout << lca << '\n';
	}

	return 0;
}

void dfs(int now, int prv) {
	for (int next : adj[now]) {
		if (next == prv) continue;
		depth[next] = depth[now] + 1;
		par[next][0] = next;
		dfs(next, now);
	}
}
