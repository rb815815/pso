// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#ifndef __COST_FUNCTION_H_
#define __COST_FUNCTION_H_

#include "problem.h"
#include "particle.h"
#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

namespace pso {

// Cost function which evaluate the loss value of neutron spectrum unfolding problem
//
//   Cost = ( ||Obs - R*phi|| + ||phi||*mean(phi) )/||Obs||
// 
// Example:
//      Cost cost;
//      double loss_value = cost.compute_loss_value(prolem, particle);
//

class Cost_function
{
public:
    Cost_function();

    virtual ~Cost_function();

    /**
    * @brief evaluate loss value
    * @param[in] problem      An Problem instance
    * @param[in] particle     An Particle instance
    *
    * @return loss value of given particle and problem
    */
    double compute_loss_value(Problem& problem, Particle& particle);

private:
    int dimension_;     // the variable dimension of specific problem
};

}

#endif