#include <bits/stdc++.h>

using namespace std;

struct Graph {
	int V;
	vector<vector<int>> adj;
	
	Graph(int V) {
		this->V = V;
		adj.resize(V);
	}
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
};

void dfs(Graph& g, int searchNode, int depthLimit = 0) {
	vector<bool> visited(g.V, false);
	stack<pair<int, int>> s;
		
	// node, depth
	s.push({0, 1});
	
	while(!s.empty()) {
		auto e = s.top(); s.pop();
		int u = e.first;
		int depth = e.second;

		if(u == searchNode) {
			cout << "\nNode " << searchNode << " found at depth: " << depth << " and iteration: " << depthLimit << "\n";
			return;	
		}
		
		if(visited[u]) continue;
		visited[u] = true;
		
		cout << u << " ";
		
		if(depthLimit > 0 && depth >= depthLimit) continue;
		
		for(int v: g.adj[u]) {
			if(visited[v]) continue;
			
			s.push({v, depth+1});
		}
	}
	
	cout << "\n";
}

void idds(Graph &g, int searchNode, int depth) {
	for(int i = 1; i <= depth; ++i) {
		dfs(g, searchNode, i);
	}
	
	cout << "\n";
}

int main() {
	Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 4);
    g.addEdge(1, 3);
    g.addEdge(1, 5);
    g.addEdge(2, 6);
    g.addEdge(4, 5);
    
    cout << "Iterative Deepening DFS\n";
    idds(g, 5, 6);
    cout << "\n";
    
	return 0;
}
