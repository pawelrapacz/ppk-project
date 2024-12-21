/**
 * \file Phenotype.cpp
 * \brief Implementation for class \ref Phenotype
 * \author Paweł Rapacz
 * \date 12-2024
 */


#include "Phenotype.h"
#include <cmath>
#include <random>
#include <chrono>
#include <sstream>


Phenotype::Phenotype(std::string_view genome) {
    std::istringstream gnm_in(genome.data());
    gene_t g;
    while (gnm_in >> g)
        _gnm.push_back(g);
}


Phenotype::Phenotype(genome_frac genome1, genome_frac genome2) {
    std::ptrdiff_t genome1_len = genome1.second - genome1.first;
    std::ptrdiff_t genome2_len = genome2.second - genome2.first;
    _gnm.reserve(genome1_len + genome2_len);
    _gnm.assign(genome1.first, genome1.second);
    _gnm.insert(_gnm.end(), genome2.first, genome2.second);
}


genome_frac Phenotype::frac_front() const {
    static std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> range(1, _gnm.size() - 1);
    return {_gnm.cbegin(), _gnm.cbegin() + range(rand)};
}


genome_frac Phenotype::frac_back() const {
    static std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> range(0, _gnm.size() - 2);
    return {_gnm.cbegin() + range(rand), _gnm.cend()};
}


const genome_t &Phenotype::genome() const noexcept
{ return _gnm; }


adapt Phenotype::adapt() const noexcept
{ return _adapt; }


void Phenotype::adapt(::adapt a) noexcept
{ _adapt = a; }


void Phenotype::operator=(::adapt a) noexcept
{ adapt(a); }
