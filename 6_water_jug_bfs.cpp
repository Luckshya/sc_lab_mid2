#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
using piii = pair<int, pii>;

#define MAX_DEPTH 5

#define findV(a, b) find(a.begin(), a.end(), b)

string stringify(pii a) {
	string s = "";
	return s + to_string(a.first) + "," + to_string(a.second);
}

bool isValid(pii a) {
	return a.first >= 0 && a.second >= 0 && a.first <= 4 && a.second <= 3;
}

bool bfs(pii src, int depth) {
	queue<piii> q;
	unordered_set<string> visited;
	
	q.push({0, src});
	visited.insert(stringify(src));
	
	bool found = false;
	
	while(!q.empty()) {
		auto front = q.front(); q.pop();
		int depth = front.first;
		
		if(depth >= MAX_DEPTH) return false;
		pii u = front.second;
		
		cout << "(" << u.first << ", " << u.second << ")\n";
		
		if(u.first == 2 || u.second == 2) {
			cout << "Solution found: (" << u.first << ", " << u.second << ")\n"; 
			return true;
		}
		
		// CASE 1 fill 4L jug
		if(u.first < 4) {
			pii next = {4, u.second};
			if(visited.find(stringify(next)) == visited.end()) {
				q.push({depth + 1, next});
				visited.insert(stringify(next));
			}
		}
		
		// CASE 2 fill 3L jug
		if(u.second < 3) {
			pii next = {u.first, 3};
			if(visited.find(stringify(next)) == visited.end()) {
				q.push({depth + 1, next});
				visited.insert(stringify(next));
			}
		}
		
		// CASE 3: transfer from 4L -> 3L jug
		if(u.first > 0) {
			// available space in 3L jug
			int available = 3 - u.second;
			
			pii next = {u.first - available, u.second + u.first - available};
			if(visited.find(stringify(next)) == visited.end() && isValid(next)) {
				q.push({depth + 1, next});
				visited.insert(stringify(next));
			}
		}
		
		// CASE 4: transfer from 3L -> 4L jug
		if(u.second > 0) {
			// available space in 4L jug
			int available = 4 - u.first;
			
			pii next = {u.first + u.second - available, u.second - available};
			if(visited.find(stringify(next)) == visited.end() && isValid(next)) {
				q.push({depth + 1, next});
				visited.insert(stringify(next));
			}
		}
		
		// CASE 6: empty 4L jug
		{
			pii next = {0, u.second};
			
			if(visited.find(stringify(next)) == visited.end()) {
				q.push({depth + 1, next});	
				visited.insert(stringify(next));
			}
		}
		
		// CASE 7: empty 3L jug
		{
			pii next = {u.first, 0};
			
			if(visited.find(stringify(next)) == visited.end()) {
				q.push({depth + 1, next});
				visited.insert(stringify(next));
			}	
		}
	}
	
	return found;	
}

int main() {
	// 4L, 3L jug
	pii initialstate = {0, 0};

	bfs(initialstate, 0);
	
	return 0;
}
