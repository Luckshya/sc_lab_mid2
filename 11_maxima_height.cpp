#include <bits/stdc++.h>

using namespace std;

struct Member {
	int x;
	double u;
};

/* INPUT
5
15 0.5
20 0.85
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
	
	Member heihgtMaxMember = *max_element(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		return m1.u < m2.u;
	});
	
	cout << "Maxima Height = " << heihgtMaxMember.x;
	
	return 0;
}
