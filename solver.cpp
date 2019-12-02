// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#include "solver.h"
#include "particle.h"
#include "problem.h"
#include "cost_function.h"

namespace pso {

Solver::Solver(
    int max_iter,            // max iteration number
    int dimension,           // the variable dimension of specific problem
    int num_particles,       // the number of particles
    double c1,               // congnition factor
    double c2,               // social factor
    double epsilon,          // stop criteria
    double w_max,            // w high threshold
    double w_min             // w low threshold
) : max_iter_(max_iter),
    dimension_(dimension),
    num_particles_(num_particles),
    c1_(c1),
    c2_(c2),
    epsilon_(epsilon),
    w_max_(w_max),
    w_min_(w_min) {
    // set default value to be false
    w_ = 0.5;
    is_problem_success_ = false;
    cur_iter_ = 0;
}

Solver::~Solver() {
    delete[] ptr_particles_;
    ptr_problem_ = nullptr;
    ptr_particles_ = nullptr;
    ptr_cost_function_ = nullptr;
}

void Solver::set_pos_max(const Eigen::VectorXd& pos_max) {
    pos_max_ = pos_max;
}

const Eigen::VectorXd& Solver::get_pos_max() {
    return pos_max_;
}

void Solver::set_pos_min(const Eigen::VectorXd& pos_min) {
    pos_min_ = pos_min;
}

const Eigen::VectorXd& Solver::get_pos_min() {
    return pos_min_;
}

void Solver::set_vel_max(const Eigen::VectorXd& vel_max) {
    vel_max_ = vel_max;
}

const Eigen::VectorXd& Solver::get_vel_max() {
    return vel_max_;
}

void Solver::set_vel_min(const Eigen::VectorXd& vel_min) {
    vel_min_ = vel_min;
}

const Eigen::VectorXd& Solver::get_vel_min() {
    return vel_min_;
}

void Solver::build_problem(Problem* problem, 
                        CostFunction* cost_function) {
    ptr_problem_ = problem;
    ptr_cost_function_ = cost_function;

    dimension_ = ptr_problem_->get_dimension();
    set_pos_max(Eigen::MatrixXd::Ones(dimension_, 1)*10);
    set_pos_min(Eigen::MatrixXd::Zero(dimension_, 1));
    set_vel_max(Eigen::MatrixXd::Ones(dimension_, 1)*10);
    set_vel_min(Eigen::MatrixXd::Ones(dimension_, 1)*(-10));

    zbest_ = Eigen::VectorXd::Zero(dimension_, 1);
    global_fitness_ = 10000;
}

void Solver::init_particles() {
    // allocate space for partilces
    ptr_particles_ = new Particle[num_particles_];
    for(int i=0; i<num_particles_; i++) {
        Eigen::VectorXd random_pos_vec = Eigen::VectorXd::Random(dimension_, 1);
        Eigen::VectorXd random_vel_vec = Eigen::VectorXd::Random(dimension_, 1);
        truncate_position_value(random_pos_vec);
        truncate_velocity_value(random_vel_vec);
        double init_fitness = evaluate(random_pos_vec);
        assign_state_to_particle(&ptr_particles_[i], random_pos_vec, random_vel_vec, init_fitness);

        if(init_fitness < global_fitness_) {
            global_fitness_ = init_fitness;
            zbest_ = random_pos_vec;
        }
    }
}

void Solver::assign_state_to_particle(
    Particle* particle,
    const Eigen::VectorXd& position,
    const Eigen::VectorXd& velocity,
    const double& fitness) {
    if(particle == nullptr) {
        return;
    }

    // assign values to particles
    particle->update_particle_state(position, velocity, fitness);
}

void Solver::truncate_position_value(Eigen::VectorXd& position_vec) {
    truncate_vec_value(position_vec, pos_max_, pos_min_);
}

void Solver::truncate_velocity_value(Eigen::VectorXd& velocity_vec) {
    truncate_vec_value(velocity_vec, vel_max_, vel_min_);
}

void Solver::truncate_vec_value(
    Eigen::VectorXd& state_vec,
    const Eigen::VectorXd& upper_bound_vec,
    const Eigen::VectorXd& lower_bound_vec) {
    for(int i=0; i<state_vec.rows(); i++) {
        // compare with predefined threshold value and truncate values to proper region
        state_vec[i] = (state_vec[i] > upper_bound_vec[i] ? upper_bound_vec[i] : state_vec[i]);
        state_vec[i] = (state_vec[i] < lower_bound_vec[i] ? lower_bound_vec[i] : state_vec[i]);
    }
}

double Solver::evaluate(Particle* particle) {
    // be sure the given pointer not to be nullptr
    if((particle == nullptr) || (ptr_problem_ == nullptr)) {
        std::cout << "problem is null" << std::endl;
        exit(0);
    }

    return ptr_cost_function_->compute_loss_value_of_particle(ptr_problem_, particle);
}

double Solver::evaluate(const Eigen::VectorXd& position) {
    return ptr_cost_function_->compute_loss_value_with_given_position(ptr_problem_, position);
}

void Solver::start() {
    Eigen::VectorXd observed_data = ptr_problem_->get_observed_data();

    for(int i=0; i<max_iter_; i++) {
        for(int j=0; j<num_particles_; j++) {
            // extract neccessary infomation from given particle
            Eigen::VectorXd pos_vec = ptr_particles_[j].get_position();
            Eigen::VectorXd vel_vec = ptr_particles_[j].get_veloctiy();
            Eigen::VectorXd pbest_vec = ptr_particles_[j].get_pbest();
            double pbest_fitness = ptr_particles_[j].get_best_fitness();

            // compute the update value of velocity
            r1_ = (double)(rand() % 50)/50;
            r2_ = (double)(rand() % 50)/50;
            vel_vec = w_*vel_vec + c1_*r1_*(pbest_vec - pos_vec) + c2_*r2_*(zbest_ - pos_vec);
            pos_vec = pos_vec + vel_vec;

            // truncate position and velocity to trust region
            truncate_position_value(pos_vec);
            truncate_velocity_value(vel_vec);

            double fitness = evaluate(pos_vec);
            std::cout << "Loop[" << i << "," << j << "] : " << fitness << std::endl;
            assign_state_to_particle(&ptr_particles_[j], pos_vec, vel_vec, fitness);

            // compare fitness to the local best fitness of the particle
            if(fitness < pbest_fitness) {
                ptr_particles_[j].set_best_fitness(pos_vec, fitness);
            }

            // compare fitness to the global best fitness
            if(fitness < global_fitness_) {
                global_fitness_ = fitness;
                zbest_ = pos_vec;
            }
        }
        cur_iter_++;
        if(global_fitness_ < epsilon_) {
            break;
        }
    }
}

void Solver::print_debug_info() {
    std::cout << "max_tier = " << max_iter_ << std::endl;
    std::cout << "cur_iter_ = " << cur_iter_ << std::endl;
    std::cout << "c1_ = " << c1_ << std::endl;
    std::cout << "c2_ = " << c2_ << std::endl;
    std::cout << "num_partilces_ = " << num_particles_ << std::endl;
    std::cout << "zbest_ = " << zbest_.transpose() << std::endl;
    std::cout << "global_fitness_ = " << global_fitness_ << std::endl;
    std::cout << "dimension_ = " << dimension_ << std::endl;
    std::cout << "epsilon_ = " << epsilon_ << std::endl;
    std::cout << "w_max_ = " << w_max_ << std::endl;
    std::cout << "w_min_ = " << w_min_ << std::endl;
    std::cout << "w_ = " << w_ << std::endl;
    std::cout << "is_problem_success_ = " << is_problem_success_ << std::endl;
}

}