// A genetic algorithm for the Traveling Salesman Problem

#include <vector>
#include "Point.hh"
#include <cstdlib>
#include <iostream>

using namespace std;

class TSPGenome {

private:
	vector<int> pointOrder; 
	double circuitLength;

public:
	// Constructors
	TSPGenome(int numPoints);	// takes number of points to visit
	TSPGenome(vector<int> order); // takes a specified visit order

	 // Destructor
  	~TSPGenome();

	// Get current order
	vector<int> getOrder() const;

	void print() const;

	// Change ordering
	void setOrder(const vector<int> &order);

	// Compute circuit length from given point ordering
	void computeCircuitLength(const vector<Point> &points);

	// Get current circuit length
	double getCircuitLength() const;

	// Mutate the genome
	void mutate();

};

// Make a new genome from parent genomes g1 and g2
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);

// Return whether g1 is shorter than g2
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2);

// Find a short path between points, using a given population size,
// number of generations, number to keep, and mutations per generation
TSPGenome findAShortPath(const vector<Point> &points, 
							int populationSize, int numGenerations,
							int keepPopulation, int numMutations);
