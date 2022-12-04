#include <bits/stdc++.h>

using namespace std;

struct Member {
	int x;
	double u;
};

/* INPUT
5
15 0.5
20 0.8
25 0.8
30 0.5
35 0.3
*/

int main() {
	cout << "Enter number of values: ";
	int n; cin >> n;
	
	vector<Member> values;
	
	while(n--) {
		cout << "Enter Xi Ui = ";
		int x; cin >> x;
		double u; cin >> u;
		
		values.push_back({x, u});
	}
	
	// cog calculation
	
	double numerator = 0;
	double denominator = 0;
	
	for(auto entry: values) {
		int x = entry.x;
		double u = entry.u;
		
		numerator += x*u;
		denominator += u;
	}
	
	double CoG = numerator/denominator;
	
	cout << "CoG = " << CoG;
	
	return 0;
}
