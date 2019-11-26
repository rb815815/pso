// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#include "cost_function.h"

namespace pso {

    Cost_function::Cost_function() : dimension_(0){}

    Cost_function::~Cost_function() {}

    double Cost_function::compute_loss_value(Problem& problem, 
                                            Particle& particle) {
        // compute response vector
        Eigen::VectorXd vec_cal = problem.get_response_matrix() *
            particle.get_position();
        // compute residual vector
        Eigen::VectorXd vec_residual = problem.get_observed_data() - vec_cal;
        // compute residual vec's norm
        double vec_residual_norm =  vec_residual.norm();
        // regularization = mean(partilce.position) * l2norm(particle.position)
        double regularization = particle.get_position().mean() * particle.get_position().norm(); 
        // compute observed data norm
        double obs_data_norm = problem.get_observed_data().norm();
        // compute loss value
        double loss_value = (vec_residual_norm + regularization) / obs_data_norm;

        return loss_value;
    }
}