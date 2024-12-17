#include "Population.h"

#include <cstdint>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

Population::Population(double r, double w, uint32_t k, uint32_t p)
    : R(r), W(w),  K(k), P(p) {}


void Population::simulate()
{
}

void read_population(std::ifstream& file, Population& p) {
    if (!file) ; // error

    std::string genome;
    while (std::getline(file, genome))
        p._ppltn.emplace_back(genome);
}


void read_population(const std::filesystem::path& path, Population& p) {
    std::ifstream __file(path);
    read_population(__file, p);
    __file.close();
}


void read_population(const std::string& path, Population& p) {
    std::ifstream __file(path);
    read_population(__file, p);
    __file.close();
}


void read_population(const char* path, Population& p) {
    std::ifstream __file(path);
    read_population(__file, p);
    __file.close();
}



void write_population(std::ofstream& file, const Population& p) {
    if (!file) // error

    for (const Phenotype& i : p._ppltn) {
        for (gene g : i._gnm)
            file << g << ' ';
        file << '\n';
    }

}


void write_population(const std::filesystem::path& path, const Population& p) {
    std::ofstream __file(path);
    write_population(__file, p);
    __file.close();
}


void write_population(const std::string& path, const Population& p) {
    std::ofstream __file(path);
    write_population(__file, p);
    __file.close();
}


void write_population(const char* path, const Population& p) {
    std::ofstream __file(path);
    write_population(__file, p);
    __file.close();
}

