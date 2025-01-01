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

    cli.name("Darwin").author("Paweł Rapacz");

    std::string infile, outfile;
    unsigned k, p;
    double w, r;


    cli.add_option<std::string>("--input", "-i").set("file", infile).doc("Input file").req();
    cli.add_option<std::string>("--output", "-o").set("file", outfile).doc("Output file").req();

    namespace pred = CLI::pred;
    cli.add_option<double>("-w")
        .set("float", w)
        .doc("Extinction threshold")
        .require("in range [0; 1]", pred::ibetween<0., 1.>)
        .req();

    cli.add_option<double>("-r")
        .set("float", r)
        .doc("Breeding threshold")
        .require("in range [0; 1]", pred::ibetween<0., 1.>)
        .req();

    cli.add_option<unsigned>("-p").set("int", k).doc("Number of generations").req();
    cli.add_option<unsigned>("-k").set("int", p).doc("Number of pairs of individuals drawn for breeding").req();

    if (1 == argc) {
        std::cout << cli.make_help();
        return 0;
    }

    if (not cli.parse(argc, argv) or not cli.wrong.empty()) {
        for (auto& i : cli.wrong)
            std::cout << i << '\n';
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