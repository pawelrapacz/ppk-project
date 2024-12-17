#pragma once

#include "Phenotype.h"
#include <string>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <fstream>



class Population
{
private:
    std::vector<Phenotype> _ppltn;

public:
    const std::vector<Phenotype>& population = _ppltn;
    const double R;
    const double W;
    const uint32_t K;
    const uint32_t P;

public:
    Population(double r, double w, uint32_t k, uint32_t p);
    ~Population() = default;

    void simulate();

private:
    void breed();


    friend void read_population(std::ifstream& file, Population& p);
    friend void read_population(const std::filesystem::path& file, Population& p);
    friend void read_population(const std::string& file, Population& p);
    friend void read_population(const char* file, Population& p);

    friend void write_population(std::ofstream& file, const Population& p);
    friend void write_population(const std::filesystem::path& file, const Population& p);
    friend void write_population(const std::string& file, const Population& p);
    friend void write_population(const char* file, const Population& p);
};
