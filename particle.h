// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#ifndef __PSO_PARTICLE_H_
#define __PSO_PARTICLE_H_

#include <iostream>
#include <functional>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

namespace pso {

    class Particle{
    public:
        /*
        @brief default constructor
        */
        Particle();

        /*
        @brief update the parameters of a Particle
        */
        void update_particle_state(const Eigen::VectorXd&,
                                const Eigen::VectorXd&,
                                const double&);

        /*
        @brief set current position
        */
        void set_position(const Eigen::VectorXd&);

        /*
        @brief get current position
        */
        const Eigen::VectorXd& get_position();

        /*
        @brief set current velocity
        */
        void set_velocity(const Eigen::VectorXd&);

        /*
        @brief get current veloctiy
        */
        const Eigen::VectorXd& get_veloctiy();

        /*
        @brief set current pbest_
        */
        void set_pbest(const Eigen::VectorXd&);

        /*
        @brief get current pbest
        */
        const Eigen::VectorXd& get_pbest();

        /*
        @brief set current fitness
        */
        void set_fitness(const Eigen::VectorXd&, const double&);

        /*
        @brief get current fitness
        */
        const double& get_fitness();

    private:
        Eigen::VectorXd position_;  // current position
        Eigen::VectorXd velocity_;  // current velocity
        Eigen::VectorXd pbest_;     // local optimization pos
        double fitness_;            // best fitness value
    };
}

#endif