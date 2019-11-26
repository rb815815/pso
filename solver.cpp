// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#include "solver.h"
#include "particle.h"
#include "problem.h"

namespace pso {

    Solver::Solver(const Options& options) 
        : options_(options) 
    {}

    Solver::~Solver() {
        delete ptr_problem_;
        delete ptr_particles_;
        delete ptr_cost_function;
        ptr_problem_ = nullptr;
        ptr_particles_ = nullptr;
        ptr_cost_function = nullptr;
    }

    void Solver::start() {

    }
}