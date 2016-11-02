#ifndef GA_H_
#define GA_H_
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

template<class GeneType>
class GA {
public:
	typedef vector<GeneType> Chromosome;

	GA(int iterations_count, int population_size, int chromosome_size, double pc,
			double pm);
	pair<Chromosome, double> Run();

protected:
	int chromosome_size;
	int iterations_count;
	double pc, pm;
	vector<Chromosome> population;
	vector<double> fitness;
	pair<int, int> parents;

	void Select();
	void MutateChromosome(int child_index, int generation_number);
	virtual void Initialize() = 0;
	virtual double CalculateFitness(Chromosome chromosome) = 0;
	virtual void Crossover() = 0;
	virtual GeneType MutateGene(GeneType gene, int generation_number) = 0;
};

template<class GeneType>
GA<GeneType>::GA(int iterations_count, int population_size, int chromosome_size,
		double pc, double pm) {
	population.resize(population_size);
	fitness.resize(population_size);
	this->iterations_count = iterations_count;
	this->chromosome_size = chromosome_size;
	this->pc = pc;
	this->pm = pm;
}

template<class GeneType>
void GA<GeneType>::MutateChromosome(int child_index, int generation_number) {
	int gene_index = rand() % chromosome_size;
	population[child_index][gene_index] = MutateGene(
			population[child_index][gene_index], generation_number);
	fitness[child_index] = CalculateFitness(population[child_index]);
}

template<class GeneType>
void GA<GeneType>::Select() {
	int pop_sz = population.size();
	double cummulative[pop_sz];
	for (int i = 0; i < pop_sz; i++) {
		cummulative[i] = bool(i) * cummulative[i - 1] + fitness[i];
	}

	double rand1 = (double) rand() / RAND_MAX * cummulative[pop_sz - 1];
	int gene1 = upper_bound(cummulative, cummulative + pop_sz, rand1)
			- cummulative;
	double rand2 = (double) rand() / RAND_MAX * cummulative[pop_sz - 1];
	int gene2 = upper_bound(cummulative, cummulative + pop_sz, rand2)
			- cummulative;
	parents = {gene1, gene2};
}

template<class GeneType>
pair<vector<GeneType>, double> GA<GeneType>::Run() {
	Initialize();

	double max_fitness = 0;
	Chromosome best;

	for (int i = 0; i < population.size(); ++i) {
		if (fitness[i] > max_fitness) {
			max_fitness = fitness[i];
			best = population[i];
		}
	}

	for (int i = 0; i < iterations_count; ++i) {

		double r1 = rand() / (double) RAND_MAX;
		double r2 = rand() / (double) RAND_MAX;
		double r3 = rand() / (double) RAND_MAX;

		Select();

		if (r1 < pc) {
			Crossover();
		}
		if (r2 < pm) {
			MutateChromosome(parents.first, i);
		}
		if (r3 < pm) {
			MutateChromosome(parents.second, i);
		}
	}

	return {best, max_fitness};
}

#endif /* GA_H_ */
