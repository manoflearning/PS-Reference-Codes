#include <iostream>
#include <stack>
using namespace std;

const int MAX = 1e5;

int N;
stack<int> sort;
bool visited[MAX + 5], isCycle;

void topological_sort() {
	for (int i = 1; i <= N; i++) {
		if (!visited[i]) dfs(i);
	}

	if (isCycle) cout << 0;
	else {
		while (!sort.empty()) {
			cout << sort.top() << '\n';
			sort.pop();
		}
	}
}

void dfs(int v) {
	visited[v] = true;
	for (int next : adj[v]) {
		if (!visited[next]) dfs(next);
		//visited[next]가 참인 정점 next에 대해 finish[next]가 거짓이라면, 이는 사이클이 존재함을 뜻한다. 
		//그래프에 사이클이 존재할 경우 위상 정렬 문제는 정의되지 않는다.
		else if (!finish[next]) isCycle = true;
	}
	finish[v] = true;
	sort.push(v);
}
