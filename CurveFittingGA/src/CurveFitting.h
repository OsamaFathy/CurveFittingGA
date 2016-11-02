/*
 * CurveFitting.h
 *
 *  Created on: Nov 2, 2016
 *      Author: Osama
 */

#ifndef CURVEFITTING_H_
#define CURVEFITTING_H_
#include <bits/stdc++.h>
#include "GA.h"
using namespace std;

class CurveFitting : public GA<double>{
private:
	pair<int, int> bounds;
	vector<pair<double, double>> points;
	double mutate_gene(double, int);
	double fitness(Chromosome);
	void crossover();
	void initialize();

public:
	CurveFitting(int iterations_count, int population_size, vector<pair<double, double>> points, pair<int, int> bounds, double pc, double pm, int sz);
};
#endif /* CURVEFITTING_H_ */
