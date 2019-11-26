// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#ifndef __PSO_SOLVER_H_
#define __PSO_SOLVER_H_

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

namespace pso {

    // forward declaration
    class Problem;
    class Particle;
    class Cost_funtion;

    class Solver
    {
    public:
        struct Options
        {
            int max_iter_;      // max iteration number
            int dimension_;     // the variable dimension of specific problem
            int num_partilces;  // the number of particles
            double c1;          // congnition factor
            double c2;          // social factor
            double epsilon;     // convergence threshold
            Eigen::VectorXd pos_max_;   // position high threshold
            Eigen::VectorXd pos_min_;   // position low  threshold
            Eigen::VectorXd v_max_;     // velocity high threshold
            Eigen::VectorXd v_min_;     // velocity low  threshold
        };
        
        /*
        @brief construct with give parameters
        */
        explicit Solver(const Options&);

        /*
        @brief forbid copy constructor
        */
        Solver(const Solver&) = delete;

        /*
        @brief forbid assignment operator
        */
        void Solver(const Solver&) = delete;

        /*
        @brief destructor
        */
        virtual ~Solver();

        /*
        @brief 
        */

        /*
        @brief starting iteration
        */
        void start();

    private:
        Eigen::VectorXd zbest_;             // the global optimal positon in history
        double global_fitness_;             // the global optimal cost value in history
        double r1,r2;                       // uniformly destributed random number
        double z;                           // weight parameter
        double w;                           // inertial weight
        Options options_;                   // options of solver
        Particle *ptr_particles_;           // pointer to particle objects
        Problem *ptr_problem_;              // pointer to Problem object
        Cost_funtion *ptr_cost_function;    // pointer to Cost_function object
    };
}

#endif