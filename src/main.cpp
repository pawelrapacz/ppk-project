/**
 * \file main.cpp
 * \author Paweł Rapacz
 * \date 12-2024
 */

#include <windows.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Darwin.h"
#include "clipper.hpp"


int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    CLI::clipper cli;
    DarwinArgs options;
    init_args(options, cli);

    if (!cli.parse(argc, argv)) // parse arguments
        return handle_parsing_errors(argc, cli);


    auto fitness = [](const Genome& gnm) -> double {
        uint32_t sum { };
        for (auto& i : gnm)
            sum += i;

        double r =  (std::sin(sum) + std::sin(gnm.size())) / 4 + 0.5;
        // std::cout << r << std::endl;
        return r;
    };

    Population sample;
    read_population(options.infile, sample);
    simulate_evolution(options.r, options.w, options.k, options.p, fitness, sample);
    write_population(options.outfile, sample);
    
    if (options.writeout)
        write_population(&std::cout, sample);
    
    std::cin.get();
    return 0;
}