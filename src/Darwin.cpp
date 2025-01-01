/**
 * \file Darwin.cpp
 * \brief Implementation for Darwin utilities
 * \author Paweł Rapacz
 * \date 01-2025
 */


#include "Darwin.h"
#include <filesystem>
#include <istream>
#include <fstream>
#include <string>
#include <iostream>

void init_args(DarwinArgs& args, CLI::clipper& cli) {
    namespace pred = CLI::pred;

    cli.name("Darwin").author("Paweł Rapacz");

    cli.add_option<std::string>("--input", "-i")
        .set("file", args.infile)
        .doc("Input file")
        .req();

    cli.add_option<std::string>("--output", "-o")
        .set("file", args.outfile)
        .doc("Output file")
        .req();

    cli.add_option<double>("-w")
        .set("float", args.w)
        .doc("Extinction threshold")
        .require("in range [0; 1]", pred::ibetween<0., 1.>)
        .req();

    cli.add_option<double>("-r")
        .set("float", args.r)
        .doc("Breeding threshold")
        .require("in range [0; 1]", pred::ibetween<0., 1.>)
        .req();

    cli.add_option<unsigned>("-p")
        .set("int", args.k)
        .doc("Number of generations")
        .req();

    cli.add_option<unsigned>("-k")
        .set("int", args.p)
        .doc("Number of pairs of individuals drawn for breeding")
        .req();

    cli.add_flag("--stdout", "-c")
        .set(args.writeout)
        .doc("Writes result to standard output");
}


int handle_parsing_errors(int argc, const CLI::clipper& cli) {
    if (1 == argc) {
        std::cout << cli.make_help();
        return 0;
    }


    for (auto& i : cli.wrong)
        std::cout << i << "\n";

    return 1;
}


void simulate_evolution(double br_thr, double ex_thr, uint32_t pairs, uint32_t generations, FitnessFunction f, Population& population) {
    population.perform_selection(f, br_thr, ex_thr);
    population.determine_breeding_phenotypes();

    if (population.get_breeding().size() < 2)
        return;

    Population new_generation;
    new_generation.data().reserve(pairs);

    for (uint32_t i = 0; i < generations; i++) {
        population.perform_breeding(pairs, new_generation);
        new_generation.perform_selection(f, br_thr, ex_thr);
        population.append(new_generation);
        new_generation.data().clear();
    }
}


void read_population(std::istream *stream, Population &p) {
    if (!*stream) throw 10;

    std::string genome;
    while (std::getline(*stream, genome))
        if (not genome.empty() /* && regex */)
            p.data().emplace_back(genome);
}


void read_population(const std::filesystem::path& path, Population& p) {
    std::ifstream file(path);
    read_population(&file, p);
    file.close();
}


void write_population(std::ostream *stream, const Population& p) {
    if (!*stream) throw 10;

    for (auto& i : p.get_population()) {
        for (Gene g : i.genome())
            *stream << g << ' ';
        *stream << '\n';
    }
}


void write_population(const std::filesystem::path& path, const Population& p) {
    std::ofstream file(path);
    write_population(&file, p);
    file.close();
}