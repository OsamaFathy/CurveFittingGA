#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "CurveFitter.h"
using namespace std;

int iterations_count = 30000;
int population_size = 30000;
double pc = 0.3;
double pm = 0.5;

int main() {
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	srand(time(NULL));

	int test_cases;
	cin >> test_cases;
	while (test_cases--) {
		int number_of_points, degree;
		cin >> number_of_points >> degree;
		vector<pair<double, double>> points(number_of_points);
		for (int i = 0; i < number_of_points; i++) {
			cin >> points[i].first >> points[i].second;
		}
		CurveFitter curve_fitter(iterations_count, population_size, points, { -10,
				10 }, pc, pm, degree);
		pair<CurveFitter::Chromosome, double> result = curve_fitter.Run();
		for (double x : result.first)
			cout << x << " , ";
		cout << "Mean Square Error: " << 1.0 / result.second << endl;
	}
	return 0;
}
