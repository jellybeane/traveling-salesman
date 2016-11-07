#include "Point.hh"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

double circuitLength(const vector<Point> &points, const vector<int> &order) {

	// Find the total roundtrip length between points, following a given order 

	int a;
	int b;
	double length = 0;

	for (unsigned int i = 0; i < order.size(); i++) {
		a = order[i];

		if ((i + 1) == order.size()) {
			b = order[0];
		}

		else {
			b = order[i+1];
		}

		length += points[a].distanceTo(points[b]);
	}
	return length;
}

vector<int> findShortestPath(const vector<Point> &points){

	// Find the shortest path between points

	vector<int> order;
	vector<int> bestOrder;
	double distance;
	double shortestDistance;
	
	int numpoints = (int) points.size(); // We don't have like 2^32 points
	order.reserve(numpoints);

	for (int i = 0; i < numpoints; i++) {
		order.push_back(i);		// Start with order [0, 1, ... , N-1]
	}
	
	bestOrder = order;
	shortestDistance = circuitLength(points, order);

	do { 	// Update shortestDistance and bestOrder

		distance = circuitLength(points, order); // Find the circuit length for the given order

		if (shortestDistance > distance) {		
			shortestDistance = distance;
			bestOrder = order;
		}

	} while (next_permutation(order.begin(), order.end())); // Get all permutations

	return bestOrder;
}

int main() {

	// Declare variables
	int numpoints;
	vector<Point> points;
	vector<int> bestOrder;
	double x;
	double y;
	double z;
	double length;
	int i = 0;

	// Get input from user
	cout << "How many points?: " << endl;
	cin >> numpoints;
	points.reserve(numpoints);
	bestOrder.reserve(numpoints);

	while (i < numpoints) {
		cout << "Point " << i << ": " << endl;
		cin  >> x >> y >> z;
		cout << endl;
		points.push_back(Point(x, y, z));

		i++;
	}

	// Find the shortest path and its length
	bestOrder = findShortestPath(points);
	length = circuitLength(points, bestOrder);

	cout << "Best order:  [";
	
	for (int i = 0; i < numpoints-1; i++) {
		cout << bestOrder[i] << " ";
	}

	cout << bestOrder[numpoints-1];
	cout << "]" << endl;

	cout << "Shortest distance:  " << length << endl;


}