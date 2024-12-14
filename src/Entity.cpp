#include "Entity.h"
#include <cmath>


Entity::Entity(std::string_view gnm) {
}



Entity::Entity(genome_frac gnm1, genome_frac gnm2) {
    genome_t:ptrdiff_t gnm1_len = gnm1.first - gnm1.second;
    genome_t:ptrdiff_t gnm2_len = gnm2.first - gnm2.second;
    _gnm.reserve(std::abs(gnm1_len) + std::abs(gnm2_len));
    _gnm.assign(gnm1.first, gnm1.second);
    _gnm.insert(_gnm.end(), gnm2.first, gnm2.second);
}



genome_frac Entity::frac_begin() const {
    std::uniform_int_distribution<> range(1, _gnm.size() - 1);
    return {_gnm.cbegin(), _gnm.cbegin() + range(rand)};
}



genome_frac Entity::frac_back() const {
    std::uniform_int_distribution<> range(0, _gnm.size() - 2);
    return {_gnm.cbegin() + range(rand), _gnm.cend()};
}
