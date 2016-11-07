#include "tsp-ga.hh"
#include <algorithm>
// I don't know what the compile time problem wass because it compiled fine
// on my computer, even without <algorithm>.
// I'm using g++ -Wall -std=c++14 Point.cc tsp-ga.cc tsp-main.cc -o tspga

using namespace std;

// Constructor for given number of points
TSPGenome::TSPGenome(int numPoints) {
	pointOrder.reserve(numPoints);

	for (int i = 0; i < numPoints; i++){
		pointOrder.push_back(i);		// initialize order to [0, 1...numPoints-1]
	}

	random_shuffle(pointOrder.begin(), pointOrder.end());	// randomize the order

	circuitLength = 1e9;		// initialize circuitLength to dummy value
}

// Constructor for given ordering of points
TSPGenome::TSPGenome(vector<int> order) {
	pointOrder = order;
	circuitLength = 1e9;
}

// Destructor
TSPGenome::~TSPGenome() {

}

// Get current order
vector<int> TSPGenome::getOrder() const {
	return pointOrder;
}

// Prints contents of pointOrder
void TSPGenome::print() const {
	for (int n = 0; n < pointOrder.size(); n++) {
		cout << pointOrder[n] << " ";
	}
			
	cout << endl;
}

// Compute circuit length for given points visited in pointOrder
void TSPGenome::computeCircuitLength(const vector<Point> &points){
	int a;
	int b;
	double length = 0;

	for (int i = 0; i < pointOrder.size(); i++) {
		a = pointOrder[i];

		if ((i + 1) == pointOrder.size()) {
			b = pointOrder[0];
		}

		else {
			b = pointOrder[i+1];
		}

		length += points[a].distanceTo(points[b]);
	}

	circuitLength = length;
}

// Get current circuit length
double TSPGenome::getCircuitLength() const {
	return circuitLength;
}

// Swaps two randomly-selected values in the order vector
void TSPGenome::mutate() {
	vector<int> order = getOrder();
	int numPoints = order.size();
	int randA = rand() % numPoints;
	int randB = randA;

	while (randB == randA) { 		// Make sure the swap indices are different
		randB = rand() % numPoints;
	}
	
	int temp = order[randA];
	order[randA] = order[randB];
	order[randB] = temp;

	pointOrder = order;
}

// Make a new genome from parent genomes g1 and g2
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2) {
	int numPoints = g1.getOrder().size();
	int i = rand() % numPoints;
	vector<int> offspring;
	offspring.reserve(numPoints);

	for (int j = 0; j < i; j++) {
		offspring.push_back(g1.getOrder()[j]);
	}

	// Fill in the rest of the offspring genome from g2
	for (int k = 0; k < numPoints; k++){ 
		// Only insert values that aren't already used
		if (find(offspring.begin(), offspring.end(), g2.getOrder()[k])
				== offspring.end()) {
			offspring.push_back(g2.getOrder()[k]);
		}
	}
	TSPGenome offspring_Genome = TSPGenome(offspring);
	return offspring_Genome;

}

// Return whether g1 is shorter than g2
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2) {
	return (g1.getCircuitLength() < g2.getCircuitLength());
}

// Find a short path between points, using a given population size,
// number of generations, number to keep, and mutations per generation
TSPGenome findAShortPath(const vector<Point> &points, 
							int populationSize, int numGenerations,
							int keepPopulation, int numMutations) {
	int generation = 0;

	// Generate the initial population
	vector<TSPGenome> population;
	population.reserve(populationSize);
	for (int i = 0; i < populationSize; i++) {
		population.push_back(TSPGenome(points.size()));
	}

	// Repeat for the given number of generations
	while (generation < numGenerations){

		// Update circuitLength for each genome
		for (int i = 0; i < populationSize; i++) {
			population[i].computeCircuitLength(points);
		}
		
		// Sort the genomes in this generation
		sort(population.begin(), population.end(), isShorterPath);

		// Every 10th generation, print the shortest path found
		if (generation % 10 == 0) {
			cout << "Generation " << generation << ": shortest path is "
				<< population[0].getCircuitLength() << endl;
		}
	
		// Replace the least-fit genomes
		for (int j = keepPopulation; j < populationSize; j++) {
			int g1 = rand() % keepPopulation;
			int g2 = g1;

			while (g1 == g2) { 		// Make sure the indices are different
				g2 = rand() % keepPopulation;
			}	
			// Generate new genomes from the fittest ones
			population[j] = crosslink(population[g1], population[g2]);
		}

		// Mutate the population
		for (int k =0; k < numMutations; k++){
			int mIndex = 1 + rand() % (populationSize - 1); // pick a random index other than 0

			population[mIndex].mutate(); // mutate the chosen genome

		}

		generation++;
	}
	// Once all generations have completed, return the best solution found
	return population[0];
	
}
