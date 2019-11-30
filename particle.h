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
    Particle();

    /**
    * @brief update the parameters of a Particle
    * @param[in] position   user provided position vector
    * @param[in] velocity   user provided velocity vector
    * @param[in] fitness    user provided fitness value
    */
    void update_particle_state(const Eigen::VectorXd& position,
                            const Eigen::VectorXd& velocity,
                            const double& fitness);

    /**
    * @brief set current position
    * @param[in] position position value in Eigen::VectorXd type
    */
    void set_position(const Eigen::VectorXd& position);

    /**
    * @brief get current position
    *
    * @return a const reference to position_
    */
    const Eigen::VectorXd& get_position();

    /**
    * @brief set current velocity
    * @param[in] velocity   velocity value in Eigen::VectorXd type
    */
    void set_velocity(const Eigen::VectorXd& velocity);

    /**
    * @brief get current veloctiy
    * 
    * @return a const reference to velocity_
    */
    const Eigen::VectorXd& get_veloctiy();

    /**
    * @brief set current pbest_
    * 
    * @return pbest     pbest value in Eigen::VectorXd type
    */
    void set_pbest(const Eigen::VectorXd& pbest);

    /**
    * @brief get current pbest
    *
    * @return a const reference to pbset
    */
    const Eigen::VectorXd& get_pbest();

    /**
    * @brief set current fitness
    * @param[in] position   position value in Eigen::VectorXd type
    * @param[in] fitness    fitness value
    */
    void set_best_fitness(const Eigen::VectorXd& position, const double& fitness);

    /**
    * @brief get current fitness
    * 
    * @return a const reference to best_fitness_
    */
    const double& get_best_fitness();

private:
    Eigen::VectorXd position_;  // current position
    Eigen::VectorXd velocity_;  // current velocity
    Eigen::VectorXd pbest_;     // local optimization position
    double best_fitness_;       // best fitness value
};

}

#endif