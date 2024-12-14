#pragma once

#include <vector>
#include <utility>
#include <string_view>
#include <random>
#include <chrono>


using genome_t = std::vector<int>;
using genome_frac = std::pair<genome_t::const_iterator, genome_t::const_iterator>;

enum class adpt {
    breed,
    nobreed,
    dead
};



class Entity
{
private:
    adpt _adpt;
    genome_t _gnm;

    inline static std::default_random_engine rand;

public:
    Entity(std::string_view gnm);
    Entity(genome_frac gnm1, genome_frac gnm2);
    void check_adaptation(/* args */);
    genome_frac frac_begin() const;
    genome_frac frac_back() const;

public:
    const adpt& adpt = _adpt;
};
