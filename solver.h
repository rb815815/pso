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
    class Cost_function;

    class Solver
    {
    public:        
        /*
        @brief constructor with give parameters
        */
        Solver(
            int max_iter,              // max iteration number
            int cur_iter,              // current iteration count
            int dimension,             // the variable dimension of specific problem
            int num_partilces,         // the number of particles
            double c1,                 // congnition factor
            double c2,                 // social factor
            double epsilon,            // stop criteria
            double w_max,              // w high threshold
            double w_min);             // w low threshold

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
        @brief set position_max
        */
        void set_pos_max(const Eigen::VectorXd&);

        /*
        @brief get position_max
        */
        const Eigen::VectorXd& get_pos_max();
        
        /*
        @brief set position_max
        */
        void set_pos_min(const Eigen::VectorXd&);

        /*
        @brief get position_min
        */
        const Eigen::VectorXd& get_pos_min();

        /*
        @brief set velocity_max
        */
        void set_vel_max(const Eigen::VectorXd&);

        /*
        @brief get velocity_max
        */
        const Eigen::VectorXd& get_vel_max();

        /*
        @brief set velocity_min
        */
        void set_vel_min(const Eigen::VectorXd&);

        /*
        @brief get velocity_min
        */
        const Eigen::VectorXd& get_vel_min();

        /*
        @brief init solver with given problem and cost function
        */
        void build_problem(Problem* problem, Cost_function* cost_functoion);

        /*
        @brief starting iteration
        */
        void start();

    private:
        /*
        @brief allocate memory and assign init value for particles
        */
        void init_particles();

        /*
        @brief assign state to particles and truncate the value is neccessray
        */
        void assign_state_to_particle(
            Particle* particle,
            const Eigen::VectorXd& position,
            const Eigen::VectorXd& velocity,
            const double& fitness
        );

        /*
        @brief truncate given posotion value to threshold region
        */
        void truncate_position_value(Eigen::VectorXd&);

        /*
        @brief truncate given velocity value to threshold region
        */
        void truncate_velocity_value(Eigen::VectorXd&);

        /*
        @brief truncate given state value to some threshold region
        */
        void truncate_vec_value(
            Eigen::VectorXd&, 
            const Eigen::VectorXd&,
            const Eigen::VectorXd&);

        /*
        @brief evaluate the loss value
        */
        double evaluate(Particle* particle);

        Eigen::VectorXd zbest_;     // the global optimal positon in history
        double global_fitness_;     // the global optimal cost value in history
        double r1_,r2_;             // uniformly destributed random number
        double z_;                  // weight parameter
        double w_;                  // inertial weight

        bool is_problem_success_;   // flag, true: problem build sucessfully, false: failed
        int max_iter_;              // max iteration number
        int cur_iter_;              // current iteration count
        int dimension_;             // the variable dimension of specific problem
        int num_partilces_;         // the number of particles
        double c1_;                 // congnition factor
        double c2_;                 // social factor
        double epsilon_;            // stop criteria
        double w_max_;              // w high threshold
        double w_min_;              // w low threshold
        Eigen::VectorXd pos_max_;   // position high threshold
        Eigen::VectorXd pos_min_;   // position low  threshold
        Eigen::VectorXd vel_max_;   // velocity high threshold
        Eigen::VectorXd vel_min_;   // velocity low  threshold

        Particle *ptr_particles_;           // pointer to particle objects
        Problem *ptr_problem_;              // pointer to Problem object
        Cost_function *ptr_cost_function_;  // pointer to Cost_function object
    };
}

#endif