/**
 * \file Darwin.h
 * \brief Darwin utilities (evolution etc.)
 * \author Paweł Rapacz
 * \date 01-2025
 */


#pragma once

#include "Phenotype.h"
#include "Population.h"
#include "clipper.hpp"


/// \brief Container for program options
struct DarwinArgs {
    std::string infile;
    std::string outfile;
    unsigned k;
    unsigned p;
    double w;
    double r;
    bool writeout;
};


/**
 * \brief Initiates command line options
 * \param args Reference to option values
 * \param cli Command line utility
 */
void init_args(DarwinArgs& args, CLI::clipper& cli);


/**
 * \brief Handles parsing errors
 * \param argc argument count
 * \param cli Command line utility reference
 * \return Value that program should return (1 - error, 0 - success)
 */
int handle_parsing_errors(int argc, const CLI::clipper& cli);


/**
 * \brief Simulates breeding and selection of its population using the \ref FitnessFunction
 * \param br_thr Breeding threshold [0; 1]
 * \param ex_thr Extinctiom threshold [0; 1]
 * \param pairs Number of pairs that will breed
 * \param generations Number od generations (number of breeding operations that will be simulated)
 * \param f Function that checks phenotype fitness/adaptation (return values should be in range [0; 1])
 * \param smpl Population to perform simulation on
 * \see FitnessFunction Population
 */
void simulate_evolution(double br_thr, double ex_thr, uint32_t pairs, uint32_t generations, FitnessFunction f, Population& smpl);


/**
 * \brief Reads the file contents and adds new elements to the given \ref Population
 * \headerfile ""
 * \param[in] stream Input stream reference containing Population information
 * \param[out] p population reference to read the file contents to
 * \see Population
 */
void read_population(std::istream *stream, Population& p);


/**
 * \brief Reads the file contents and adds new elements to the given \ref Population
 * \headerfile ""
 * \param[in] path Path to file to read from
 * \param[out] p population reference to read the file contents to
 * \see Population
 */
void read_population(const std::filesystem::path& file, Population& p);


/**
 * \brief Writes the \ref Population to the given file
 * \headerfile ""
 * \param[in] stream Output stream pointer to write to
 * \param[out] p population reference to read from
 * \see Population
 */
void write_population(std::ostream *stream, const Population& p);


/**
 * \brief Writes the \ref Population to the given file
 * \headerfile ""
 * \param[in] path Path to the file to write to
 * \param[out] p population reference to read from
 * \see Population
 */
void write_population(const std::filesystem::path& path, const Population& p);