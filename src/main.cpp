#include "clipper.hpp"
#include <string>
#include <iostream>
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
        
        return sum / (gnm.size() * 100);
    };

    Population sample(r, w, k, p);
    read_population(infile, sample);
    sample.simulate();
    write_population(outfile, sample);

    return 0;
}