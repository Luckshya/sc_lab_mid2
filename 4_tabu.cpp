#include <bits/stdc++.h>
#define N 3

using namespace std;

struct PuzzleState {
	vector<vector<int>> data;
	int heuristic;
	
	int x;
	int y;
	
	PuzzleState() {
		heuristic = INT_MAX;	
	}
	
	PuzzleState(vector<vector<int>>& data, vector<vector<int>>& goalState, int x, int y) {
		this->data = data;
		this->x = x;
		this->y = y;
		
		heuristic = calcHeurisitic(goalState);
	}
	
	int calcHeurisitic(vector<vector<int>>& goalState) {
		int mismatch = 0;
		
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if(data[i][j] != goalState[i][j] && data[i][j] != 0) mismatch++;
			}
		}
		
		return mismatch;
	}
	
	string stringify() {
		string build = "";
		
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				build += data[i][j];
			}
		}
		
		return build;
	}
	
	void print() {
		cout << "\n";
		
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				cout << data[i][j] << " ";
			}
			cout << "\n";
		}
		
		cout << "\n";
	}
};

struct MyCmp {
	bool operator()(const PuzzleState& p1, const PuzzleState& p2) {
		return p1.heuristic < p2.heuristic;
	}
};

int main() {
	srand(time(0));

	vector<vector<int>> initialState = {
		{1, 2, 3},
		{8, 0, 4},
		{7, 6, 5}
	};
	
	vector<vector<int>> goalState = {
		{1, 2, 3},
		{5, 8, 6},
		{0, 7, 4}
	};
//	vector<vector<int>> initialState = {
//		{1, 2, 3},
//		{7, 8, 4},
//		{6, 0, 5}
//	};
//	
//	vector<vector<int>> goalState = {
//		{1, 2, 3},
//		{8, 0, 4},
//		{7, 6, 5}
//	};
	
	PuzzleState pzState(initialState, goalState, 2, 1);
	
	int rowOff[] = {-1, 1, 0, 0};
	int colOff[] = {0, 0, -1, 1};
	
	int depth = 0;
	
	unordered_set<string> tabuList;
	tabuList.insert(pzState.stringify());	
	
	bool found = false;
	
	PuzzleState bestSoFar = pzState;
	
	while(depth < 10) {
		PuzzleState prevState = pzState;
		cout << "Moving to depth: " << depth << "\n";
		
		if(pzState.data == goalState) {
			cout << "\nSolution found!\n";
			pzState.print();
			found = true;
			break;
		}
		
		vector<int> movesLeft = {0, 1, 2, 3};		
		vector<int> randMoves;
		
		while(!movesLeft.empty()) {
			int randIdx = rand() % movesLeft.size();
			randMoves.push_back(movesLeft[randIdx]);
			movesLeft.erase(movesLeft.begin() + randIdx);
		}
		
		PuzzleState currBest;
		
		for(auto i: randMoves) {
			vector<vector<int>> currData = pzState.data;
			int x = pzState.x + rowOff[i];
			int y = pzState.y + colOff[i];
			
			if(x < 0 || y < 0 || x >= N || y >= N) continue;
						
			swap(currData[pzState.x][pzState.y], currData[x][y]);
		
			PuzzleState currState(currData, goalState, x, y);
			string currStateString = currState.stringify();
			
			if(currState.heuristic < currBest.heuristic) {
				// tabu move
				if(tabuList.find(currStateString) != tabuList.end()) {
					// aspiration criteria
					// if(currState.heuristic < bestSoFar.heuristic) {
					if((rand() % 2)) {
						cout << "Tabu move accepted through aspiration criteria\n";
					}
					// ignore move
					else continue;
				}
				
				currBest = currState;
			}
		}
		
		string currBestString = currBest.stringify();
		tabuList.insert(currBestString);
		pzState = currBest;
		
		if(currBest.heuristic < bestSoFar.heuristic) {
			bestSoFar = currBest;
		}
		
		depth++;
		
		// Short-term memory tabu list
		if(tabuList.size() > 4) tabuList.erase(tabuList.begin());
	}
	
	cout << "Best state: ";
	bestSoFar.print();
	
	return 0;
}
