// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#include "cost_function.h"

namespace pso {

CostFunction::CostFunction() {
    dimension_ = 0;
}

CostFunction::~CostFunction() {}

double CostFunction::compute_loss_value_of_particle(Problem* problem, 
                                        Particle* particle) {                                         
    return compute_loss_value_with_given_position(problem, particle->get_position());
}

double CostFunction::compute_loss_value_with_given_position(Problem* problem, 
                                                            const Eigen::VectorXd& position) {
    // compute response vector (Ncal = R*phi)
    Eigen::VectorXd vec_cal = problem->get_response_matrix() * position;

    // compute residual vector (Ncode - Ncal)
    Eigen::VectorXd vec_residual = problem->get_observed_data() - vec_cal;

    // compute l2 norm of residual vector
    double vec_residual_norm =  vec_residual.norm();

    // regularization = mean(partilce.position) * l2norm(particle.position)
    double regularization = position.mean() * position.norm(); 

    // compute l2 norm of observed data vector
    double obs_data_norm = problem->get_observed_data().norm();
    
    // compute loss value
    double loss_value = (vec_residual_norm + regularization) / obs_data_norm;

    return loss_value;
}

}
