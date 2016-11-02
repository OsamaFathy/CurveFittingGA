#ifndef CURVEFITTER_H_
#define CURVEFITTER_H_
#include <bits/stdc++.h>
#include "GA.h"
using namespace std;

class CurveFitter: public GA<double> {
private:
	pair<double, double> bounds;
	vector<pair<double, double>> points;

	double MutateGene(double gene, int generation_number);
	double CalculateFitness(Chromosome chromosome);
	void Crossover();
	void Initialize();

public:
	CurveFitter(int iterations_count, int population_size,
			vector<pair<double, double>> points, pair<double, double> bounds,
			double pc, double pm, int degree);

	virtual ~CurveFitter() {
	}
};
#endif /* CURVEFITTER_H_ */
