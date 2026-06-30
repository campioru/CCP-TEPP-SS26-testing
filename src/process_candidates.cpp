//! \file process_candidates.cpp

#include <fstream>
#include <cmath>
#include <iostream>
#include <vector>
#include "invariant_mass.hpp"
// #include "process_candidates.hpp"

// 2. file I/O mixed with computation

// 3. mega-function

// 4. magic numbers

// 5. while loop: data format not validated!

double momentum_magnitude(double px, double py, double pz)
{
    return std::sqrt(px*px + py*py + pz*pz);
}

struct FourVector
{
    double E;
    double px;
    double py;
    double pz;
};

struct Results
{
    int n_physical;
    int n_candidates;
    double sum_mass;
};

std::vector<FourVector> read_file(const std::string& filename);

bool cut(double mass, double lower, double upper)
{
    if (mass > lower && mass < upper) return true;
}

Results process_candidates(double& g_energy_scale, const std::string& filename) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    int    n_candidates = 0;
    int    n_physical   = 0;
    double sum_mass     = 0.0;

    auto data = read_file(filename);

    double energy, px, py, pz;
    while (file >> energy >> px >> py >> pz) {
        ++n_candidates;

        energy *= g_energy_scale;

        double momentum = momentum_magnitude(px, py, pz);

        try {
            double mass = invariant_mass(energy, momentum);
            ++n_physical;
            sum_mass += mass;

            bool passes = cut(mass, lower_cut, upper_cut);

            if (mass > 70.0 && mass < 110.0) {
                std::cout << "Z candidate found with mass "
                          << mass << " GeV" << std::endl;
            }
        } catch (const std::domain_error&) {
            std::cout << "Unphysical candidate, skipping." << std::endl;
        }
    }

    if (n_physical > 0) {
        std::cout << "Mean mass: " << sum_mass / n_physical
                  << " GeV" << std::endl;
    }
    std::cout << "Processed " << n_candidates << " candidates, "
              << n_physical   << " physical." << std::endl;


    return Results{n_physical, n_candidates, sum_mass};
}
