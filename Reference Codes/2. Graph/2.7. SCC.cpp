#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 1e5;

int N, label[MAXV + 5], labelCnt;
int SCCnum[MAXV + 5], SCCcnt;
vector<int> adj[MAXV + 5];
bool finished[MAXV + 5];
stack<int> S;
vector<vector<int>> SCC;

void getSCC() {
	memset(label, -1, sizeof(label));

	for (int v = 0; v < N; v++)
		if (label[v] == -1) dfs(v);
}

int dfs(int v) {
	label[v] = labelCnt++;
	S.push(v);

	int ret = label[v];
	for (int next : adj[v]) {
		//방문하지 않은 정점
		if (label[next] == -1) ret = min(ret, dfs(next));
		//방문은 했으나 아직 SCC로 분류되지 않은 정점
		else if (!finished[next]) ret = min(ret, label[next]);
	}

	if (ret == label[v]) {
		vector<int> vSCC;
		while (true) {
			int t = S.top();
			S.pop();

			vSCC.push_back(t);
			SCCnum[t] = SCCcnt;
			finished[t] = true;

			if (t == v) break;
		}

		SCC.push_back(vSCC);
		SCCcnt++;
	}

	return ret;
}
