/**
 * \file Population.cpp
 * \brief Implementation for class \ref Population and its friend functions
 * \author Paweł Rapacz
 * \date 12-2024
 */


#include "Population.h"
#include <cstdint>
#include <string>
#include <filesystem>
#include <fstream>
#include <regex>
#include <random>
#include <chrono>



void Population::simulate(double br_thr, double ex_thr, uint32_t pairs, uint32_t generations, fitness_func f) {
    selection(f, br_thr, ex_thr);
    determine_breeding_phenotypes();

    if (_breeding.size() < 2)
        return;

    Population newgen;
    newgen._ppltn.reserve(pairs);

    for (uint32_t i = 0; i < generations; i++) {
        breed(pairs, newgen);
        newgen.selection(f, br_thr, ex_thr);
        index_t newgen_idx = _ppltn.size();
        _ppltn.insert(_ppltn.end(), newgen._ppltn.cbegin(), newgen._ppltn.cend());
        determine_breeding_phenotypes(newgen_idx);
        newgen._ppltn.clear();
    }
}


void Population::selection(fitness_func f, const double& br_thr, const double& ex_thr) {
    double ftns;
    for (auto& indv : _ppltn) {
        ftns = f(indv.genome());

        if (ftns > br_thr)
            indv = adapt::breed;
        else if (ftns >= ex_thr)
            indv = adapt::nobreed;
        else
            indv = adapt::dead;
    }

    std::erase_if(_ppltn, [](const Phenotype& p) -> bool { return adapt::dead == p.adapt(); });
}


void Population::breed(uint32_t n, Population& ng) const {
    static std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::size_t> range(0, _breeding.size() - 1);

    for (uint32_t i = 0; i < n; i++) {
        index_t first = _breeding[range(rand)];
        index_t second = _breeding[range(rand)];

        if (first == second) {
            i--;
            continue;
        }

        ng._ppltn.emplace_back(_ppltn[first].frac_front(), _ppltn[second].frac_back());
    }
}


void Population::determine_breeding_phenotypes(index_t first_ph) {
    for (auto i = first_ph; i < _ppltn.size(); i++)
        if (adapt::breed == _ppltn[i].adapt())
            _breeding.push_back(i);
}


void read_population(std::ifstream& file, Population& p) {
    if (!file) throw 10;

    std::string genome;
    while (std::getline(file, genome))
        if (not genome.empty() /* && regex */)
            p._ppltn.emplace_back(genome);
}


void read_population(const std::filesystem::path& path, Population& p) {
    std::ifstream __file(path);
    read_population(__file, p);
    __file.close();
}


void write_population(std::ofstream& file, const Population& p) {
    if (!file) throw 10;

    for (const Phenotype& i : p._ppltn) {
        for (gene_t g : i.genome())
            file << g << ' ';
        file << '\n';
    }
}


void write_population(const std::filesystem::path& path, const Population& p) {
    std::ofstream __file(path);
    write_population(__file, p);
    __file.close();
}