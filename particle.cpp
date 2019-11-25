#include "particle.h"
#include "cost_function.h"

namespace pso {

    // set initial fitness_ to be some large positive number
    particle::particle()
    {
        fitness_ = 10000.0;
    }

    // compare the fitness value
    void particle::update_particle_state(
        const Eigen::VectorXd& position,
        const Eigen::VectorXd& velocity,
        const double& fitness) {
        set_position(position);
        set_velocity(velocity);
        set_fitness(position, fitness);
    }

    void particle::set_position(const Eigen::VectorXd& position) {
        position_ = position;
    }

    const Eigen::VectorXd& particle::get_position() {
        return position_;        
    }

    void particle::set_velocity(const Eigen::VectorXd& velocity) {
        velocity_ = velocity;
    }

    const Eigen::VectorXd& particle::get_veloctiy() {
        return velocity_;
    }

    void particle::set_pbest(const Eigen::VectorXd& pbest) {
        pbest_ = pbest;        
    }

    const Eigen::VectorXd& particle::get_pbest() {
        return pbest_;
    }

    void particle::set_fitness(const Eigen::VectorXd& position, const double& fitness) {
        if(fitness < fitness_) {
            fitness_ = fitness;
            pbest_ = position;
        }
    }

    const double& particle::get_fitness() {
        return fitness_;
    }
}