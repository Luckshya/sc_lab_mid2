#include <bits/stdc++.h>

using namespace std;

struct Member {
	double x;
	double area;
};

/* INPUT
3
2.5 1.2
5 1.5
6.5 2
*/

int main() {
	cout << "Enter number of values: ";
	int n; cin >> n;
	
	vector<Member> values;
	
	while(n--) {
		cout << "Enter Xi Ai = ";
		double x; cin >> x;
		double area; cin >> area;
		
		values.push_back({x, area});
	}
	
	// coa calculation
	
	double numerator = 0;
	double denominator = 0;
	
	for(auto entry: values) {
		double x = entry.x;
		double area = entry.area;
		
		numerator += x*area;
		denominator += area;
	}
	
	double CoA = numerator/denominator;
	
	cout << "CoA = " << CoA;
	
	return 0;
}
