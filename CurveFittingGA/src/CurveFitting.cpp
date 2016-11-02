/*
 * CurveFitting.cpp
 *
 *  Created on: Nov 2, 2016
 *      Author: Osama
 */

#include "CurveFitting.h"

CurveFitting::CurveFitting(int iterations_count, int population_size,
		vector<pair<double, double>> points, pair<int, int> bounds, double pc,
		double pm, int sz) :
		GA<double>(iterations_count, population_size, sz, pc, pm), points(
				points), bounds(bounds) {
}

double CurveFitting::mutate_gene(double gene, int t) {
	double delta_low = gene - bounds.first;
	double delta_high = bounds.second - gene;
	int r = rand() % 2;
	double y = (r == 0 ? delta_low : delta_high);

	double nr = rand() / (double) RAND_MAX;
	double b = 0.5 + (rand() / (double) RAND_MAX) * 4.5; // dependency factor [0.5, 5]

	double amount_of_mutation = y
			* (1 - pow(nr, pow( 1 -  (double)t/ iterations_count, b)));
	return gene + (r == 0 ? -1 : 1) * amount_of_mutation;
}

double CurveFitting::fitness(Chromosome chromosome) {
	double square_error_sum = 0;
	for (auto point : points) {
		double y = 0;
		for (int i = 0; i < chromosome_size; i++) {
			y += chromosome[i] * pow(point.first, chromosome_size - i - 1);
		}
		square_error_sum += (y - point.second) * (y - point.second);
	}
	return square_error_sum/points.size();
}

void CurveFitting::initialize() {
	for (int i = 0; i < population.size(); i++) {
		population[i] = Chromosome(chromosome_size);
		for (int j = 0; j < chromosome_size; j++)
			population[i][j] = bounds.first + (bounds.second - bounds.first) * rand() / (double) RAND_MAX;
		fitness_value[i] = fitness(population[i]);
	}
}

void CurveFitting::crossover() {
	// Single point crossover
	int r = rand() % (chromosome_size);
	int p1 = parents.first;
	int p2 = parents.second;
	for (int i = 0; i < r; i++) {
		swap(population[p1][i], population[p2][i]);
	}
	fitness_value[p1] = fitness(population[p1]);
	fitness_value[p2] = fitness(population[p2]);
}

