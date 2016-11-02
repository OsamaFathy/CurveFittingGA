#include "CurveFitter.h"

CurveFitter::CurveFitter(int iterations_count, int population_size,
		vector<pair<double, double> > points, pair<double, double> bounds,
		double pc, double pm, int degree) :
		GA<double>(iterations_count, population_size, degree + 1, pc, pm), bounds(
				bounds), points(points) {
}

double CurveFitter::MutateGene(double gene, int generation_number) {
	double delta_low = gene - bounds.first;
	double delta_high = bounds.second - gene;
	int r = rand() % 2;
	double y = (r == 0 ? delta_low : delta_high);

	double nr = rand() / (double) RAND_MAX;
	double b = 0.5 + (rand() / (double) RAND_MAX) * 4.5; // dependency factor [0.5, 5]

	double amount_of_mutation =
			y
					* (1
							- pow(nr,
									pow(1 - (double) generation_number / iterations_count, b)));
	return gene + (r == 0 ? -1 : 1) * amount_of_mutation;
}

double CurveFitter::CalculateFitness(Chromosome chromosome) {
	double square_error_sum = 0;
	for (auto point : points) {
		double y = 0;
		for (int i = 0; i < chromosome_size; ++i) {
			y += chromosome[i] * pow(point.first, i);
		}
		square_error_sum += (y - point.second) * (y - point.second);
	}
	return points.size() / (square_error_sum + 1e-10);
}

void CurveFitter::Initialize() {
	for (int i = 0; i < population.size(); ++i) {
		population[i] = Chromosome(chromosome_size);
		for (int j = 0; j < chromosome_size; ++j)
			population[i][j] = bounds.first
					+ (bounds.second - bounds.first) * rand() / (double) RAND_MAX;
		fitness[i] = CalculateFitness(population[i]);
	}
}

void CurveFitter::Crossover() {
// Single point crossover
	int r = rand() % (chromosome_size);
	int p1 = parents.first;
	int p2 = parents.second;
	for (int i = 0; i < r; i++) {
		swap(population[p1][i], population[p2][i]);
	}
	fitness[p1] = CalculateFitness(population[p1]);
	fitness[p2] = CalculateFitness(population[p2]);
}

