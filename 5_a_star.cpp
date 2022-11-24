#include <bits/stdc++.h>
using namespace std;

struct Point {
	int x;
	int y;
	
	Point() {
		x = -1;
		y = -1;
	}
	
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct Node {
	Point coords;
	Node* parent;
	double gVal;
	double hVal;
	double fVal;
	
	Node(Point& coords, Node* parent, double gVal, double hVal) {
		this->coords = coords;
		this->parent = parent;
		this->gVal = gVal;
		this->hVal = hVal;
		
		fVal = gVal + hVal;
	}
};

struct NodeCmp {
    bool operator() (Node* a, Node* b) const {
        return a->fVal < b->fVal;
    }
};

// distance between 2 cells
double hValue(Point src, Point dest) {
	return sqrt(pow(dest.x - src.x, 2) + pow(dest.y - src.y, 2));
}

void printPath(Node* node) {
	if(node == NULL) return;
	
	printPath(node->parent);
	cout << "(" << (node->coords).x << ", " << (node->coords).y << ") => f = " << (node->fVal) << "\tg = " << (node->gVal) << "\th = " << (node->hVal) << "\n";
}

bool aStar(vector<vector<int>>& grid, Point& src, Point& dest) {
	int ROWS = grid.size();
	int COLS = grid[0].size();
	
	int rowOff[] = {-1, -1, 1, 1, -1, 1, 0, 0};
	int colOff[] = {-1, 1, -1, 1, 0, 0, -1, 1};
	
	set<Node*, NodeCmp> s;
	s.insert(new Node(src, NULL, 0.0, hValue(src, dest)));
	vector<vector<bool>> visited(ROWS, vector<bool>(COLS, 0));
	
	bool found = false;
	
	while(!s.empty()) {
		Node* node = *s.begin(); 
		s.erase(s.begin());
			
		if((node->coords).x == dest.x && (node->coords).y == dest.y) {
			cout << "Path found with gValue = " << node->gVal << ", hVal = " << node->hVal << ", fVal = " << node->fVal << "\n";
			printPath(node);
			return true;
		}
	
		for(int i = 0; i < 8; ++i) {
			Point point(rowOff[i] + (node->coords).x, colOff[i] + (node->coords).y);
			
			// valid point
			if(point.x < 0 || point.y < 0 || point.x >= ROWS || point.y >= COLS || grid[point.x][point.y] == 0) continue;
			
			// visited
			if(visited[point.x][point.y]) continue;
			
			double edgeCost = 1;
			if(i < 4) edgeCost = 1.414;
			
			Node *newNode = new Node(point, node, node->gVal + edgeCost, hValue(point, dest));
			s.insert(newNode);
			visited[point.x][point.y] = 1;
		}	
	}

	return false;
}

int main() {
	vector<vector<int>> grid = {
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
	};
	
	// top left
	Point src(0, 0);
	
	// bottom right
	Point dest(grid.size()-1, grid[0].size()-1);
	
	aStar(grid, src, dest);
	
	return 0;
}
