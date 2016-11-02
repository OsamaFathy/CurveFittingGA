#ifndef GA_H_
#define GA_H_
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

template<class GeneType>
class GA {

protected:
	typedef vector<GeneType> Chromosome;
	int chromosome_size;
	int iterations_count;
	double pc, pm;
	vector<Chromosome> population;
	vector<double> fitness_value;
	pair<int, int> parents;
	virtual void initialize() = 0;
	virtual double fitness(Chromosome chromosome) = 0;
	void selection();
	virtual void crossover() = 0;
	void mutation(int ind, int t);
	virtual GeneType mutate_gene(GeneType gene, int t) = 0;

public:
	GA(int iterations_count, int population_size, int chromosome_size,
			double pc, double pm);
	pair< vector<GeneType>, double > run();
};

template<class GeneType>
GA<GeneType>::GA(int iterations_count, int population_size, int chromosome_size,
		double pc, double pm) {
	population.resize(population_size);
	fitness_value.resize(population_size);
	this->iterations_count = iterations_count;
	this->chromosome_size = chromosome_size;
	this->pc = pc;
	this->pm = pm;
}

template<class GeneType>
void GA<GeneType>::mutation(int ind, int t) {
	int gene_index = rand() % chromosome_size;
	population[ind][gene_index] = mutate_gene(population[ind][gene_index], t);
	fitness_value[ind] = fitness(population[ind]);
}

template<class GeneType>
void GA<GeneType>::selection() {
	int pop_sz = population.size();
	double cummulative[pop_sz];
	for (int i = 0; i < pop_sz; i++) {
		cummulative[i] = bool(i) * cummulative[i - 1] + 1000.0/(1e-7 + fitness_value[i]);
	}

	double rand1 = max(rand()-1.0, 0.0)/RAND_MAX * cummulative[pop_sz - 1];
	int gene1 = upper_bound(cummulative, cummulative + pop_sz, rand1)
			- cummulative;
	double rand2 = max(rand()-1.0, 0.0)/RAND_MAX * cummulative[pop_sz - 1];
	int gene2 = upper_bound(cummulative, cummulative + pop_sz, rand2)
			- cummulative;
	parents = {gene1, gene2};
}

template<class GeneType>
pair< vector<GeneType>, double > GA<GeneType>::run() {
	initialize();
	for (int i = 0; i < iterations_count; i++) {

		double r1 = rand() / (double) RAND_MAX;
		double r2 = rand() / (double) RAND_MAX;
		double r3 = rand() / (double) RAND_MAX;

		selection();

		if (r1 < pc)
			crossover();
		if (r2 < pm) {
			mutation(parents.first, i);
		}
		if (r3 < pm && r1 < pc) {
			mutation(parents.second, i);
		}

	}

	double mx = 2e18;
	int ind = -1;
	for (int i = 0; i < population.size(); i++){
		if(mx > fitness_value[i]){
			ind = i, mx = fitness_value[i];
		}
	}
	return {population[ind], mx};
}

#endif /* GA_H_ */
