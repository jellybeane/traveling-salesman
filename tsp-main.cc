#include "tsp-ga.hh"
#include <ctime>

using namespace std;

int main(int argc, char **argv) {

	// Command line arguments
	int population = (int) atoi(argv[1]);
	int generations = (int) atoi(argv[2]);
	float keep = (float) atof(argv[3]);
	float mutate = (float) atof(argv[4]); // mutate < 1 seems to work better

	// Info to get from user input
	int numpoints;
	vector<Point> points;
	double x;
	double y;
	double z;

	// Seed the RNG
	srand(time(NULL));

	// Get input about points to visit from user
	cout << "How many points?: ";
	cin >> numpoints;

	points.reserve(numpoints);

	for (int i = 0; i < numpoints; i++) {
		cout << "Point " << i << ": ";
		cin  >> x >> y >> z;
		points.push_back(Point(x, y, z));
	}
	cout << endl;

	// Find a short path between the points and its length
	TSPGenome bestOrder(numpoints);
	bestOrder = findAShortPath(points, population, generations, 
						ceil(keep * population), ceil(mutate * population));
	double length = bestOrder.getCircuitLength();

	// Print out the path and its length
	cout << "Best order:  [";
	for (int i = 0; i < numpoints-1; i++) {
		cout << bestOrder.getOrder()[i] << " ";
	}
	cout << bestOrder.getOrder()[numpoints-1];
	cout << "]" << endl;

	cout << "Shortest distance:  " << length << endl;

	return 0;
}


