#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include <string_view>



using gene_t = uint16_t;
using genome_t = std::vector<gene_t>;
using genome_frac = std::pair<genome_t::const_iterator, genome_t::const_iterator>;



enum class adapt {
    breed,
    nobreed,
    dead
};



class Phenotype
{
private:
    adapt _adapt = adapt::breed;
    genome_t _gnm;


public:
    Phenotype(std::string_view genome);
    Phenotype(genome_frac genome1, genome_frac genome2);
    genome_frac frac_front() const;
    genome_frac frac_back() const;
    const genome_t& genome() const noexcept;
    adapt adapt() const noexcept;
    void adapt(::adapt a) noexcept;
    void operator=(::adapt a) noexcept;
};
