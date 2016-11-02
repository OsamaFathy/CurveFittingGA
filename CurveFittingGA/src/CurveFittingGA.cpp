#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "CurveFitting.h"
using namespace std;

int iterations_count = 10000;
int population_size = 10000;
double pc = 0.3;
double pm = 0.5;

int main() {
	srand(time(NULL));
	int n, deg;
	cin >> n >> deg;
	vector<pair<double, double>> points(n);
	for(int i = 0; i<n; i++){
		cin >> points[i].first >> points[i].second;
	}
	CurveFitting curve(iterations_count, population_size, points, {-10, 10}, pc, pm, deg+1);
	pair<vector<double>, double> res = curve.run();
	cout << "Error: " << res.second << endl;
	for(double x : res.first)
		cout << x << "  " ;
	return 0;
}
