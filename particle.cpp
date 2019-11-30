// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#include "particle.h"
#include "cost_function.h"

namespace pso {

    // set initial fitness_ to be some large positive number
    Particle::Particle()
    {
        best_fitness_ = 10000.0;
    }

    // compare the fitness value
    void Particle::update_particle_state(
        const Eigen::VectorXd& position,
        const Eigen::VectorXd& velocity,
        const double& fitness) {
        set_position(position);
        set_velocity(velocity);
        set_best_fitness(position, fitness);
    }

    void Particle::set_position(const Eigen::VectorXd& position) {
        position_ = position;
    }

    const Eigen::VectorXd& Particle::get_position() {
        return position_;        
    }

    void Particle::set_velocity(const Eigen::VectorXd& velocity) {
        velocity_ = velocity;
    }

    const Eigen::VectorXd& Particle::get_veloctiy() {
        return velocity_;
    }

    void Particle::set_pbest(const Eigen::VectorXd& pbest) {
        pbest_ = pbest;        
    }

    const Eigen::VectorXd& Particle::get_pbest() {
        return pbest_;
    }

    void Particle::set_best_fitness(const Eigen::VectorXd& position, const double& fitness) {
        if(fitness < best_fitness_) {
            best_fitness_ = fitness;
            pbest_ = position;
        }
    }

    const double& Particle::get_best_fitness() {
        return best_fitness_;
    }
}