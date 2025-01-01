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



using Gene = uint16_t; ///< Type for a gene
using Genome = std::vector<Gene>; ///< Type for a genome (chromosome) of multiple \ref Gene "genes"
using GenomeFrac = std::pair<Genome::const_iterator, Genome::const_iterator>; ///< Type that contains a fraction of a \ref Genome



/**
 * \brief Holds information about \ref Phenotype "Phenotype's" adaptation
 * 
 * Adaptation should be determined by the result of a \ref Population::FitnessFunction "fitness function",
 * according to breeding and extinction thresholds. 
 * 
 * \see Phenotype Population Population::FitnessFunction
 */
enum class Adapt {
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
 * \li **Genome:** The genome is stored as a \ref Genome type and can be divided into fragments (\ref frac_front(), \ref frac_back()).
 *
 * \see Population adapt Genome GenomeFrac
 */
class Phenotype
{
private:
    Adapt _adapt; ///< Phenotype's adaptation
    Genome _gnm; ///< Phenotype's genome (chromosome)


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
     * \see GenomeFrac frac_front() frac_back()
     */
    Phenotype(GenomeFrac genome1, GenomeFrac genome2);


    /**
     * \brief 
     * \return fraction of genome (chromosome) starting at the begining and ending in a random place
     * \see GenomeFrac
     */
    GenomeFrac frac_front() const;


    /**
     * \brief 
     * \return fraction of genome (chromosome) starting in a random place and ending at the back
     * \see GenomeFrac
     */
    GenomeFrac frac_back() const;


    /**
     * \brief Acesses objects's genome
     * \return const reference to object's genome
     * \see Genome
     */
    const Genome& genome() const noexcept;


    /**
     * \brief Gets object's adaptation value
     * \return object's adaptation
     * \see adapt
     */
    Adapt adapt() const noexcept;


    /**
     * \brief Sets object's adaptation value
     * \see adapt
     */
    void adapt(Adapt a) noexcept;
};
