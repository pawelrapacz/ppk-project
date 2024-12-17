#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <utility>
#include <string_view>


using gene = uint16_t;
using genome_t = std::vector<gene>;
using genome_frac = std::pair<genome_t::const_iterator, genome_t::const_iterator>;

enum class adapt {
    breed,
    nobreed,
    dead
};

class Population;

class Phenotype
{
private:
    adapt _adapt;
    genome_t _gnm;

    // inline static std::default_random_engine rand;

public:
    Phenotype(std::string_view gnm);
    Phenotype(genome_frac gnm1, genome_frac gnm2);
    genome_frac frac_begin() const;
    genome_frac frac_back() const;

public:
    const adapt& adpt = _adapt;


    friend class Population;
    friend void write_population(std::ofstream& file, const Population& p);
};
