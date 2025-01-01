/**
 * \file Population.cpp
 * \brief Implementation for class \ref Population and its friend functions
 * \author Paweł Rapacz
 * \date 12-2024
 */


#include "Population.h"
#include <cstdint>
#include <random>
#include <chrono>



Population &Population::operator+=(const Population &other) {
    std::size_t prvlen = _data.size();
    _data.insert(_data.end(), other._data.begin(), other._data.end());
    auto first = _br.insert(_br.end(), other._br.begin(), other._br.end());
    std::for_each(first, _br.end(), [&prvlen](Index& idx) { idx += prvlen; });
    return *this;
}


Population &Population::operator+=(const PopulationVec &range) {
    std::size_t prevlen = _data.size();
    _data.insert(_data.end(), range.begin(), range.end());
    determine_breeding_phenotypes(prevlen);
    return *this;
}


Population& Population::append(const Population& other)
{ return *this += other; }


Population& Population::append(const PopulationVec& range)
{ return *this += range; }


Population Population::operator+(const Population &other) const {
    Population newp = *this;
    newp += other;
    return newp;
}


Population Population::operator+(const PopulationVec &range) const {
    Population newp = *this;
    newp += range;
    return newp;
}


void Population::perform_selection(FitnessFunction f, const double &br_thr, const double &ex_thr)
{
    double ftns;
    for (auto& indv : _data) {
        ftns = f(indv.genome());

        if (ftns > br_thr)
            indv.adapt(Adapt::breed);
        else if (ftns >= ex_thr)
            indv.adapt(Adapt::nobreed);
        else
            indv.adapt(Adapt::dead);
    }

    std::erase_if(_data, [](const Phenotype& p) -> bool { return Adapt::dead == p.adapt(); });
}


void Population::perform_breeding(std::size_t pairs, Population& other) const {
    static std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::size_t> range(0, _br.size() - 1);

    for (auto i = 0; i < pairs; i++) {
        Index first = _br[range(rand)];
        Index second = _br[range(rand)];

        if (first == second) {
            i--;
            continue;
        }

        other._data.emplace_back(_data[first].frac_front(), _data[second].frac_back());
    }
}


Population Population::perform_breeding(std::size_t pairs) const {
    static std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::size_t> range(0, _br.size() - 1);

    Population newp;

    for (auto i = 0; i < pairs; i++) {
        Index first = _br[range(rand)];
        Index second = _br[range(rand)];

        if (first == second) {
            i--;
            continue;
        }

        newp._data.emplace_back(_data[first].frac_front(), _data[second].frac_back());
    }

    return newp;
}


void Population::determine_breeding_phenotypes(Index first_ph) {
    for (auto i = first_ph; i < _data.size(); i++)
        if (Adapt::breed == _data[i].adapt())
            _br.push_back(i);
}