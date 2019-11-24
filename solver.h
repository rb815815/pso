#ifndef __SOLVER_H_
#define __SOLVER_H_

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>

class solver
{
public:
    solver();

    /*
    @brief starting iteration
    */
    void start();

private:
    int max_iter_;          // max iteration number
    int dimension_;         // the variable dimension of specific problem
    Eigen::VectorXd zbest;  // the global optimal positon in history
    double global_fitness;  // the global optimal cost value in history
};

#endif