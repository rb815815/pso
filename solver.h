#ifndef __PSO_SOLVER_H_
#define __PSO_SOLVER_H_

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include "particle.h"

namespace pso {

    class Solver
    {
    public:
        struct Options
        {
            int max_iter_;      // max iteration number
            int dimension_;     // the variable dimension of specific problem
            double c1;          // congnition factor
            double c2;          // social factor
            double w;           // inertial weight
            Eigen::VectorXd pos_max_;   // position high threshold
            Eigen::VectorXd pos_min_;   // position low  threshold
            Eigen::VectorXd v_max_;     // velocity high threshold
            Eigen::VectorXd v_min_;     // velocity low  threshold
        };
        
        /*
        @brief construct with give parameters
        */
        explicit Solver(const Optioins&);

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
        @brief starting iteration
        */
        void start();

    private:
        Eigen::VectorXd zbest_; // the global optimal positon in history
        double global_fitness_; // the global optimal cost value in history
        double r1,r2;           // uniformly destributed random number
        particle* p_particles;  // pointer to particles;
    };
}


#endif