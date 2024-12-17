#include "Phenotype.h"
#include <cmath>
#include <random>
#include <chrono>


Phenotype::Phenotype(std::string_view gnm) {
}



Phenotype::Phenotype(genome_frac gnm1, genome_frac gnm2) {
    std::ptrdiff_t gnm1_len = gnm1.first - gnm1.second;
    std::ptrdiff_t gnm2_len = gnm2.first - gnm2.second;
    _gnm.reserve(std::abs(gnm1_len) + std::abs(gnm2_len));
    _gnm.assign(gnm1.first, gnm1.second);
    _gnm.insert(_gnm.end(), gnm2.first, gnm2.second);
}



genome_frac Phenotype::frac_begin() const {
    static std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> range(1, _gnm.size() - 1);
    return {_gnm.cbegin(), _gnm.cbegin() + range(rand)};
}



genome_frac Phenotype::frac_back() const {
    static std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> range(0, _gnm.size() - 2);
    return {_gnm.cbegin() + range(rand), _gnm.cend()};
}
