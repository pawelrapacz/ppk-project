/**
 * \file Population.h
 * \brief Declaration for class \ref Population and its friend functions
 * \author Paweł Rapacz
 * \date 12-2024
 */


#pragma once

#include "Phenotype.h"
#include <cstdint>
#include <vector>
#include <filesystem>
#include <fstream>


/**
 * \brief Represents a population and allows simulating its evolution
 * \headerfile ""
 * 
 * This class is a interface for \ref Phenotype population, and allowes \ref Population::simulate "simulating" its evolution.
 * 
 * \see Phenotype adapt
 */
class Population
{
    using index_t = std::size_t; ///< Type for container indexes
    using populationvec_t = std::vector<Phenotype>; ///< Type for storing the population of \ref Phenotype "Phenotypes"


public:
    /**
     * \brief Type for fitness function
     * 
     * Fitness function type is used to represent a function that evaluates \ref Phenotype "Phenotype's"
     * adaptation.
     * 
     * Value returned by a fitness function is then used to set (according to breeding and extinction thresholds)
     * the \ref Phenotype::_adapt "adaptation" of a \ref Phenotype.
     * Furthermore \ref Phenotype::_adapt "adaptation" property is needed to properly \ref Population::simulate "simulate"
     * \ref Population "population's" evolution.
     * 
     * \b Requirements:
     * \li The parameter is a \ref genome_t "const genome_t&"
     * \li returns adaptation value in range [0; 1]
     * 
     * \see Phenotype adapt
     */
    using fitness_func = double (*)(const genome_t&);


private:
    populationvec_t _ppltn; ///< Container that stores the population itself (\ref Phenotype "Phenotypes")
    std::vector<index_t> _breeding; ///< Container that stores \ref index_t "indexes" of (\ref Phenotype "Phenotypes") that can \ref adapt "breed"

public:
    const populationvec_t& population = _ppltn; ///< Reference to Population::_ppltn


public:
    Population() = default;
    ~Population() = default;


    /**
     * \brief Simulates breeding and selection of its population using the \ref fitness_func
     * \param br_thr Breeding threshold [0; 1]
     * \param ex_thr Extinctiom threshold [0; 1]
     * \param pairs Number of pairs that will breed
     * \param generations Number od generations (number of breeding operations that will be simulated)
     * \param f Function that checks phenotype fitness/adaptation (return values should be in range [0; 1])
     * \see fitness_func population
     */
    void simulate(double br_thr, double ex_thr, uint32_t pairs, uint32_t generations, fitness_func f);

private:

    /**
     * \brief
     * \param f Function that checks phenotype fitness/adaptation (return values should be in range [0; 1])
     * \param br_thr Breeding threshold [0; 1]
     * \param ex_thr Extinctiom threshold [0; 1]
     * \see simulation()
     */
    void selection(fitness_func f, const double& br_thr, const double& ex_thr);


    /**
     * \brief Performs breeding on an object's population
     * \param n Number of pairs that will breed
     * \param[out] newgen Population reference where the descendants will be saved to (new generation)
     * \see simulation()
     */
    void breed(uint32_t n, Population& newgen) const;


    /**
     * \brief Determines population members that can breed
     * \param first_ph index of an element to start the checking from
     * \see adapt index_t
     */
    void determine_breeding_phenotypes(index_t first_ph = 0);


    friend void read_population(std::ifstream& file, Population& p);
    friend void read_population(const std::filesystem::path& path, Population& p);
    friend void write_population(std::ofstream& file, const Population& p);
    friend void write_population(const std::filesystem::path& path, const Population& p);
};



/**
 * \brief Reads the file contents and adds new elements to the given \ref Population
 * \headerfile ""
 * \param[in] file Input filestream reference containing Population information
 * \param[out] p population reference to read the file contents to
 * \see Population
 */
void read_population(std::ifstream& file, Population& p);


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
 * \param[in] file Output filestream reference containing file to write to
 * \param[out] p population reference to read from
 * \see Population
 */
void write_population(std::ofstream& file, const Population& p);


/**
 * \brief Writes the \ref Population to the given file
 * \headerfile ""
 * \param[in] path Path to the file to write to
 * \param[out] p population reference to read from
 * \see Population
 */
void write_population(const std::filesystem::path& path, const Population& p);