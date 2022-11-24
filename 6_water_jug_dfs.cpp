#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

#define MAX_DEPTH 5

#define findV(a, b) find(a.begin(), a.end(), b)

string stringify(pii a) {
	string s = "";
	return s + to_string(a.first) + "," + to_string(a.second);
}

bool isValid(pii a) {
	return a.first >= 0 && a.second >= 0 && a.first <= 4 && a.second <= 3;
}

// depth limited dfs
bool dfs(pii u, int depth, unordered_set<string>& visited) {
	if(depth >= MAX_DEPTH) return false;
	 
	cout << "(" << u.first << ", " << u.second << ")\n";
	
	if(u.first == 2 || u.second == 2) {
		cout << "Solution found: (" << u.first << ", " << u.second << ")\n"; 
		return true;
	}
	
	bool found = false;
	
	visited.insert(stringify(u));

	// CASE 1 fill 4L jug
	if(u.first < 4) {
		pii next = {4, u.second};
		if(!found && visited.find(stringify(next)) == visited.end()) {
			found = dfs(next, depth + 1, visited);
		}
	}
	
	// CASE 2 fill 3L jug
	if(u.second < 3) {
		pii next = {u.first, 3};
		if(!found && visited.find(stringify(next)) == visited.end()) {
			found = dfs(next, depth + 1, visited);
		}
	}
	
	// CASE 3: transfer from 4L -> 3L jug
	if(u.first > 0) {
		// available space in 3L jug
		int available = 3 - u.second;
		
		pii next = {u.first - available, u.second + u.first - available};
		if(!found && visited.find(stringify(next)) == visited.end() && isValid(next)) {
			found = dfs(next, depth + 1, visited);
		}
	}
	
	// CASE 4: transfer from 3L -> 4L jug
	if(u.second > 0) {
		// available space in 4L jug
		int available = 4 - u.first;
		
		pii next = {u.first + u.second - available, u.second - available};
		if(!found && visited.find(stringify(next)) == visited.end() && isValid(next)) {
			found = dfs(next, depth + 1, visited);
		}
	}
	
	// CASE 6: empty 4L jug
	{
		pii next = {0, u.second};
		
		if(!found && visited.find(stringify(next)) == visited.end()) {
			found = dfs(next, depth + 1, visited);		
		}
	}
	
	// CASE 7: empty 3L jug
	{
		pii next = {u.first, 0};
		
		if(!found && visited.find(stringify(next)) == visited.end()) {
			found = dfs(next, depth + 1, visited);
		}	
	}
	
	return found;
}

int main() {
	// 4L, 3L jug
	pii initialstate = {0, 0};

	unordered_set<string> visited;
	visited.insert(stringify(initialstate));
	
	dfs(initialstate, 0, visited);
	
	return 0;
}
