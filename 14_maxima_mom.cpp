#include <bits/stdc++.h>

using namespace std;

struct Member {
	int x;
	double u;
};

/* INPUT
5
15 0.5
25 0.85
18 0.85
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
	
	sort(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		if(m1.u == m2.u) return m1.x < m2.x;
		return m1.u > m2.u;
	});
	
	Member maxEntry = *max_element(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		return m1.u < m2.u;
	});
	
	double sum = 0;
	int ni = 0;
	
	for(auto entry: values) {
		if(entry.u == maxEntry.u) {
			sum += entry.x;
			ni++;
		}
	}
	
	cout << "Maxima MoM = " << sum/ni;
	
	return 0;
}
