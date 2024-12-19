#pragma once

#include "Phenotype.h"
#include <cstdint>
#include <vector>
#include <filesystem>
#include <fstream>



class Population
{
using index_t = std::size_t;
using fitness_func = double (*)(const genome_t&);
using populationvec_t = std::vector<Phenotype>;

private:
    populationvec_t _ppltn;
    std::vector<index_t> _breeding;

public:
    const std::vector<Phenotype>& population = _ppltn;


public:
    Population() = default;
    ~Population() = default;

    void simulate(double br_thr, double ex_thr, uint32_t pairs, uint32_t generations, fitness_func f);

private:
    void selection(fitness_func f, const double& br_thr, const double& ex_thr);
    void breed(uint32_t n, Population& newgen) const;
    void determine_breeding_phenotypes(index_t first_ph = 0);


    friend void read_population(std::ifstream& file, Population& p);
    friend void read_population(const std::filesystem::path& file, Population& p);

    friend void write_population(std::ofstream& file, const Population& p);
    friend void write_population(const std::filesystem::path& file, const Population& p);
};
