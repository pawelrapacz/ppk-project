/**
 * \file Population.h
 * \brief Declaration for class \ref Population
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
 * \li The parameter is a \ref Genome "const Genome&"
 * \li returns adaptation value in range [0; 1]
 * 
 * \see Phenotype adapt
 */
using FitnessFunction = double (*)(const Genome&);


using Index = std::size_t; ///< Type for container indexes



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
    using PopulationVec = std::vector<Phenotype>; ///< Type for storing the population of \ref Phenotype "Phenotypes"

private:
    PopulationVec _data; ///< Container that stores the population itself (\ref Phenotype "Phenotypes")
    std::vector<Index> _br; ///< Container that stores \ref Index "indexes" of (\ref Phenotype "Phenotypes") that can \ref adapt "breed"


public:
    Population() = default;
    ~Population() = default;


    /// \brief Gets the underlying \c PopulationVec container
    /// \return \c PopulationVec reference
    const PopulationVec& get_population() const noexcept
    { return _data; }


    /// \copydoc get_population()
    PopulationVec& data() noexcept
    { return _data; }


    /// \brief Gets the underlying \c std::vector<Index> container, that contains indexes of \c Phenotypes that can breed
    /// \return \c std::vector<Index> reference
    const std::vector<Index>& get_breeding() const noexcept
    { return _br; }


    /// \copydoc get_breeding()
    std::vector<Index>& get_breeding() noexcept
    { return _br; }


    Population& operator+=(const Population& other);

    Population& operator+=(const PopulationVec& range);

    Population& append(const Population& other);

    Population& append(const PopulationVec& range);

    Population operator+(const Population& other) const;

    Population operator+(const PopulationVec& range) const;


    /**
     * \brief
     * \param f Function that checks phenotype fitness/adaptation (return values should be in range [0; 1])
     * \param br_thr Breeding threshold [0; 1]
     * \param ex_thr Extinctiom threshold [0; 1]
     * \see simulate_evolution()
     */
    void perform_selection(FitnessFunction f, const double& br_thr, const double& ex_thr);


    /**
     * \brief Performs breeding on an object's population
     * \param n Number of pairs that will breed
     * \param[out] other Population reference where the descendants will be saved to (new generation)
     * \see simulate_evolution()
     */
    void perform_breeding(std::size_t pairs, Population& other) const;

    /// \copydoc perform_breeding()
    /// \return New Population
    Population perform_breeding(std::size_t pairs) const;

    /**
     * \brief Determines population members that can breed
     * \param first_ph index of an element to start the checking from
     * \see adapt Index
     */
    void determine_breeding_phenotypes(Index first_ph = 0);


    friend void read_population(std::istream*, Population&);
};