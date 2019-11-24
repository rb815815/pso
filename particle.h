#ifndef __PARTICLE_H_
#define __PARTICLE_H_

#include <iostream>
#include <functional>
#include <eigen3/Eigen/Dense>

typedef Eigen::VectorXd Var;

class particle{
public:
    particle();

    /*
    @brief init parameters with random number
    */
    void init_with_ramdom_param();

    /*
    @brief update the postion
    */
    void update_particle_state();

    /*
    @brief evaluate the cost function
    */
    void evaluate();

private:
    int dimension_;     // the dimension of specific problem
    Var position_;      // current position
    Var velocity_;      // current velocity
    Var pos_max_;       // pos high threshold
    Var pos_min_;       // pos low  threshold
    Var v_max_;         // vel high threshold
    Var v_min_;         // vel low  threshold
    Var gbest_;         // local optimization pos
    double fitness_;    // best fitness value
    double c1;          // social factor c1
    double c2;          // factor c2

    // forward declaration
    class cost_function;
    cost_function* loss_func;
};

#endif