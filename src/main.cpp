/**
 * \file main.cpp
 * \author Paweł Rapacz
 * \date 12-2024
 */


#include "clipper.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Population.h"


int main(int argc, char** argv) {
    CLI::clipper cli;
    cli.name("Darwin");
    cli.author("Paweł Rapacz");

    std::string infile, outfile;
    int k, p;
    float w, r;
    cli.add_option<std::string>("--input", "-i").set("file", infile).doc("Input file").req();
    cli.add_option<std::string>("--output", "-o").set("file", outfile).doc("Output file").req();
    cli.add_option<float>("-w").set("float", w).doc("Extinction threshold").req();
    cli.add_option<float>("-r").set("float", r).doc("Breeding threshold").req();
    cli.add_option<int>("-p").set("int", k).doc("Number of generations").req();
    cli.add_option<int>("-k").set("int", p).doc("Number of pairs of individuals drawn for breeding").req();

    if (1 == argc) {
        std::cout << cli.make_help();
        return 0;
    }

    if (not cli.parse(argc, argv))
        return 1;

    if (not cli.wrong.empty()) {
        for (auto& i : cli.wrong) {
            std::cout << i << '\n';
            std::cout.flush();
        }
        return 1;
    }



    auto fitness = [](const genome_t& gnm) -> double {
        uint32_t sum { };
        for (auto& i : gnm)
            sum += i;

        double r =  (std::sin(sum) + std::sin(gnm.size())) / 4 + 0.5;
        // std::cout << r << std::endl;
        return r;
    };

    Population sample;
    read_population(infile, sample);
    sample.simulate(r, w, k, p, fitness);
    write_population(outfile, sample);

    // std::cin.get();
    return 0;
}