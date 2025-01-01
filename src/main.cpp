/**
 * \file main.cpp
 * \author Paweł Rapacz
 * \date 12-2024
 */

#include <windows.h>
#include <cmath>
#include <iostream>
#include "Darwin.h"
#include "clipper.hpp"



/**
 * @brief Entry point for the Darwin simulation program.
 *
 * Parses command-line arguments, reads the input population, performs 
 * evolutionary simulation, and writes the results to an output file (and optionally to stdout).
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status: 0 on success, non-zero on error.
 */

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
    
    if (!read_population(options.infile, sample)) {
        std::clog << "Cannot access file: No such file [" << options.infile << "]\n";
        return 1;
    }

    simulate_evolution(options.r, options.w, options.k, options.p, fitness, sample);
    write_population(options.outfile, sample);

    if (options.writeout)
        write_population(&std::cout, sample);
    
    return 0;
}
