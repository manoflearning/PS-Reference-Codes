#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 1e5;

int N;
vector<int> arr;
bool isCycle;

void topological_sort() {
	queue<int> q;

	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0) q.push(i);

	for (int i = 0; i < N; i++) {
		if (q.empty()) {
			isCycle = true;
			break;
		}

		int v = q.front();
		q.pop();

		arr.push_back(v);
        
		for (int next : adj[v]) {
			indegree[next]--;
			if (indegree[next] == 0) q.push(next);
		}
	}

	if (isCycle) cout << 0;
	else {
		for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << '\n';
	}
}
