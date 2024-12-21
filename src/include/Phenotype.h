/**
 * \file Phenotype.h
 * \brief Declaration for class \ref Phenotype and other utilities
 * \author Paweł Rapacz
 * \date 12-2024
 */


#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include <string_view>



using gene_t = uint16_t; ///< Type for a gene
using genome_t = std::vector<gene_t>; ///< Type for a genome (chromosome) of multiple \ref gene_t "genes"
using genome_frac = std::pair<genome_t::const_iterator, genome_t::const_iterator>; ///< Type that contains a fraction of a \ref genome_t



/**
 * \brief Holds information about \ref Phenotype "Phenotype's" adaptation
 * 
 * Adaptation should be determined by the result of a \ref Population::fitness_func "fitness function",
 * according to breeding and extinction thresholds. 
 * 
 * \see Phenotype Population Population::fitness_func
 */
enum class adapt {
    breed,      ///< Phenotype remains in the population, and will breed
    nobreed,    ///< Phenotype remains in the population, but will not breed
    dead        ///< Phenotype will be remved from the population
};




/**
 * \brief Represents a phenotype (individual) and its associated genetic information.
 * \headerfile ""
 *
 * This class stores data related to the phenotype's adaptation status and its genome.
 * It also provides functionality to manipulate the adaptation status and split the genome into fragments.
 *
 * \li **Adaptation:** Each phenotype has an adaptation status represented by the \ref adapt enum.
 * \li **Genome:** The genome is stored as a \ref genome_t type and can be divided into fragments (\ref frac_front(), \ref frac_back()).
 *
 * \see Population adapt genome_t genome_frac
 */
class Phenotype
{
private:
    adapt _adapt; ///< Phenotype's adaptation
    genome_t _gnm; ///< Phenotype's genome (chromosome)


public:

    /**
     * \brief constructor
     * \param genome a string containning chromosome (2 34 455 34 3 85)
     */
    Phenotype(std::string_view genome);


    /**
     * \brief constructor
     * \param genome1 faction of a chromosome (pair of pointers)
     * \param genome2 faction of a chromosome (pair of pointers)
     * \see genome_frac frac_front() frac_back()
     */
    Phenotype(genome_frac genome1, genome_frac genome2);


    /**
     * \brief 
     * \return fraction of genome (chromosome) starting at the begining and ending in a random place
     * \see genome_frac
     */
    genome_frac frac_front() const;


    /**
     * \brief 
     * \return fraction of genome (chromosome) starting in a random place and ending at the back
     * \see genome_frac
     */
    genome_frac frac_back() const;


    /**
     * \brief Acesses objects's genome
     * \return const reference to object's genome
     * \see genome_t
     */
    const genome_t& genome() const noexcept;


    /**
     * \brief Gets object's adaptation value
     * \return object's adaptation
     * \see adapt
     */
    adapt adapt() const noexcept;


    /**
     * \brief Sets object's adaptation value
     * \see adapt
     */
    void adapt(::adapt a) noexcept;


    /**
     * \brief Sets object's adaptation value
     * \see adapt
     */
    void operator=(::adapt a) noexcept;
};
