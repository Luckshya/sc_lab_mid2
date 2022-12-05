#include <bits/stdc++.h>

using namespace std;

using piv = pair<int, vector<int>>;
using vi = vector<int>;
using vvi = vector<vector<int>>;

// f(x) = -x^2 + 5
// 0 <= x <= 31

vvi initPopulation() {
	int n = 4;
	int bits = 5;

	vvi population;
		
	for(int i = 0; i < n; ++i) {
		vi curr;
		
		for(int j = 0; j < bits; ++j) {
			curr.push_back(rand()%2);
		}
		
		population.push_back(curr);
	}
	
	return population;
}

vector<piv> caclulateFitness(vvi population) {
	int n = population.size();
	int bits = population[0].size();
	
	vector<piv> fitness;
	
	for(auto chromosome: population) {
		int value = 0;
		
		for(int i = 0; i < bits; ++i) {
			value += chromosome[i]*pow(2, bits-i-1);
		}
		
		fitness.push_back({-(value*value) + 5, chromosome});
	}
	
	sort(fitness.begin(), fitness.end(), greater<piv>());
	
	return fitness;
}

vvi selection(vector<piv> populationFitness) {
	return {populationFitness[0].second, populationFitness[1].second};
}

vvi crossover(vvi selected) {
	vvi offsprings = selected;
	
	for(int i = 0; i < selected.size(); i+=2) {
		int bits = selected[i].size();
		
		// cross point
		int k = rand() % (bits-1);	
		
		vi parent1 = selected[i];
		vi parent2 = selected[i+1];
		
		vi offspring1, offspring2;
		
		for(int j = 0; j < k + 1; ++j) {
			offspring1.push_back(parent1[j]);
			offspring2.push_back(parent2[j]);
		}
		
		for(int j = k+1; j < bits; ++j) {
			offspring1.push_back(parent2[j]);
			offspring2.push_back(parent1[j]);
		}
		
		offsprings.push_back(offspring1);
		offsprings.push_back(offspring2);
	}
	
	return offsprings;
}

vvi mutation(vvi population) {
	int n = population.size()/2;
	int bits = population[0].size();
	
	int r = rand();
	
	if(r % 7 == 0) {
		int i = n + rand() % n;
		int bit = rand() % bits;
		
		// flip bit
		population[i][bit] = 1 - population[i][bit];
	}
	
	return population;
}

int main() {
	srand(time(0));
	
	int iterations = 25;
	
	int overallBest = INT_MIN;
	
	while(iterations--) {
		vvi population = initPopulation();
		vector<piv> fitnessPopulation = caclulateFitness(population);
		
		int currBest = fitnessPopulation[0].first;
		
		cout << "Current best score = " << currBest << "\n";
		
		overallBest = max(overallBest, currBest);
		
		vvi selected = selection(fitnessPopulation);
		vvi newPopulation = crossover(selected);
		vvi mutated = mutation(newPopulation);
	}
	
	cout << "\nOverall best score = " << overallBest << "\n";
	
	return 0;
}
