#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 1e3;
const int INF = 1e9 + 7;

struct edge {
	int v, c, f;
	edge* dual; //역방향 간선을 가리키는 포인터
	edge() : edge(-1, 0) {}
	edge(int v1, int c1) : v(v1), c(c1), f(0), dual(nullptr) {}
	int residual() {
		return c - f;
	}
	void addFlow(int f1) {
		f += f1;
		dual->f -= f1;
	}
};

int N;
vector<edge*> adj[MAXV + 5];
int prv[MAXV + 5];
edge* path[MAXV + 5];
int st, en;

void input();
int max_flow();
void BFS(int st, int en);
int flow(int st, int en);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	st = 1, en = N;
	int total = max_flow();

	cout << total << endl;

	return 0;
}

void input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		int n1, n2, cap;
		cin >> n1 >> n2 >> cap;

		edge* e1 = new edge(n2, cap), * e2 = new edge(n1, 0);
		e1->dual = e2, e2->dual = e1;
		adj[n1].push_back(e1);
		adj[n2].push_back(e2);
	}
}

int max_flow() {
	int ret = 0;
	while (true) {
		BFS(st, en);

		if (prv[en] == -1) break;

		ret += flow(st, en);
	}
	return ret;
}

void BFS(int st, int en) {
	memset(prv, -1, sizeof(prv));

	queue<int> q;
	q.push(st);
	prv[st] = 0;

	while (!q.empty() && prv[en] == -1) {
		int now = q.front();
		q.pop();

		for (auto* e : adj[now]) {
			int next = e->v;
			if (prv[next] == -1 && e->residual() > 0) {
				q.push(next);
				prv[next] = now;
				path[next] = e;
			}
		}
	}
}

int flow(int st, int en) {
	int n = en, block = INF;
	for (int i = en; i != st; i = prv[i]) {
		block = min(block, path[i]->residual());
	}
	for (int i = en; i != st; i = prv[i]) {
		path[i]->addFlow(block);
	}
	return block;
}
