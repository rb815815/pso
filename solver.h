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

// Solver that manage the optimization process
//
// At first user should init a solver with proper parameters,
// then load an existing problem and given cost_function, when
// the problem is built successfully, call start().
//
// Example:
//      Solver *solver = new Solver(max_iter = 1000,
//                                  num_particles = 100,
//                                  c1 = 0.4,
//                                  c2 = 0.4,
//                                  epsilon = 1e-6,
//                                  w_max = 0,
//                                  w_min = 1);
//      solver->build_problem(problem, cost_function);
//      solver->start();
//
class Solver
{
public:
    /**
    * @brief init parameters with user provided values
    * @param[in] max_iter       max iteration number
    * @param[in] dimension      the variable dimension of specific problem
    * @param[in] num_particles  the number of particles
    * @param[in] c1             congnition factor
    * @param[in] c2             social factor
    * @param[in] epsilon        stop criteria
    * @param[in] w_max          high threshold of w
    * @param[in] w_min          low threshold of w
    */
    Solver(
        int max_iter,
        int dimension,
        int num_partilces,
        double c1,
        double c2,
        double epsilon,
        double w_max, 
        double w_min);

    /**
    * @brief forbid copy constructor
    */
    Solver(const Solver&) = delete;

    /**
    * @brief forbid assignment operator
    */
    void Solver(const Solver&) = delete;

    virtual ~Solver();

    /**
    * @brief set position_max_ with user provided value
    * @param[in]  pos_max   predefined high threshold of position
    */
    void set_pos_max(const Eigen::VectorXd& pos_max);

    /**
    * @brief get position_max_
    * 
    * @return  a const reference to position_max_
    */
    const Eigen::VectorXd& get_pos_max();
        
    /**
    * @brief set pos_min_ with user provided value
    * 
    * @param[in]  pos_min   predefined low threshold of position
    */
    void set_pos_min(const Eigen::VectorXd& pos_min);

    /**
    * @brief get pos_min_
    * 
    * @return a const reference to position_min_
    */
    const Eigen::VectorXd& get_pos_min();

    /**
    * @brief set velocity_max_ with user defined value
    * @param[in] vel_max   high threshold of velocity
    */
    void set_vel_max(const Eigen::VectorXd& vel_max);

    /**
    * @brief get velocity_max_
    * 
    * @return a const reference to velocity_max_
    */
    const Eigen::VectorXd& get_vel_max();

    /**
    * @brief set velocity_min_ with user defined value
    * @param[in] vel_min   low threshold of velocity
    */
    void set_vel_min(const Eigen::VectorXd&);

    /**
    * @brief get velocity_min_
    * 
    * @return a const reference to velocity_min_
    */
    const Eigen::VectorXd& get_vel_min();

    /**
    * @brief init ptr_problem_ and ptr_cost_function_ 
    * @param[in] problem        pointer to an existing Problem instance
    * @param[in] cost_functoion pointer to an existing Cost_function instance
    */
    void build_problem(Problem* problem, Cost_function* cost_functoion);

    /**
    * @brief starting iteration
    */
    void start();

private:
    /**
    * @brief allocate memory and assign init value for particles
    */
    void init_particles();

    /**
    * @brief assign state to particles and truncate the value is neccessray
    * @param[in] particle   pointer to an existing particle instance
    * @param[in] position   position value in Eigen::VectorXd form
    * @param[in] velocity   velocity value in Eigen::VectorXd form
    * @param[in] fitness    fitness value
    */
    void assign_state_to_particle(
        Particle* particle,
        const Eigen::VectorXd& position,
        const Eigen::VectorXd& velocity,
        const double& fitness
    );

    /**
    * @brief truncate given posotion value to predefined threshold region
    * @param[in/out] position   position value in Eigen::VectorXd form
    */
    void truncate_position_value(Eigen::VectorXd& position);

    /**
    * @brief truncate given velocity value to threshold region
    * @param[in/out] velocity   velocity value in Eigen::VectorXd form
    */
    void truncate_velocity_value(Eigen::VectorXd& velocity);

    /**
    * @brief truncate given state value to some threshold region
    * @param[in/out] state_vec      state_vec value in Eigen::VectorXd form
    * @param[in] upper_bound_vec    predefined high threshold
    * @param[in] lower_bound_vec    predefined low threshold
    */
    void truncate_vec_value(
        Eigen::VectorXd& state_vec, 
        const Eigen::VectorXd& upper_bound_vec,
        const Eigen::VectorXd& lower_bound_vec);

    /**
    * @brief evaluate the loss value of an existing particle
    * @param[in] particle   pointer to an existing Particle instance
    * 
    * @return the loss value of a particle
    */
    double evaluate(Particle* particle);

    /**
    * @brief evaluate the loss value of a position vec
    * @param[in] position   position value in Eigen::VectorXd form
    * 
    * @return the loss value of given position
    */
    double evaluate(Eigen::VectorXd& position);

    Eigen::VectorXd zbest_;     // the global optimal positon in history
    double global_fitness_;     // the global optimal cost value in history
    double r1_,r2_;             // uniformly destributed random number
    double z_;                  // weight parameter
    double w_;                  // inertial weight

    bool is_problem_success_;   // flag, true: problem build sucessfully, false: failed
    int max_iter_;              // max iteration number
    int cur_iter_;              // current iteration count
    int dimension_;             // the variable dimension of specific problem
    int num_particles_;         // the number of particles
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