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
        is_problem_success_ = false;
        cur_iter_ = 0;
    }

    Solver::~Solver() {
        delete ptr_problem_;
        delete ptr_particles_;
        delete ptr_cost_function_;
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
                            Cost_function* cost_function) {
        ptr_problem_ = problem;
        ptr_cost_function_ = cost_function;

        dimension_ = ptr_problem_->get_dimension();
        set_pos_max(Eigen::MatrixXd::Ones(dimension_, 1)*100);
        set_pos_min(Eigen::MatrixXd::Zero(dimension_, 1));
        set_vel_max(Eigen::MatrixXd::Ones(dimension_, 1)*100);
        set_vel_max(Eigen::MatrixXd::Ones(dimension_, 1)*(-100));
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
            assign_state_to_particle(ptr_particles_[i], random_pos_vec, random_vel_vec, init_fitness);
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

        if((position.rows() != particle->get_position.rows() ||
            (velocity.rows() != particle->get_veloctiy.rows()))) {
            std::cout << "fatal error, assignment with wrong dimensions" << std::endl;
            exit(-1);
        }

        particle->update_particle_state(position, velocity, fitness);
    }

    void Solver::truncate_position_value(Eigen::VectorXd& position_vec) {
        return truncate_vec_value(position_vec, pos_max_, pos_min_);
    }

    void Solver::truncate_velocity_value(Eigen::VectorXd& velocity_vec) {
        return truncate_vec_value(velocity_vec, vel_max_, vel_min_);
    }

    void Solver::truncate_vec_value(
        Eigen::VectorXd& state_vec,
        const Eigen::VectorXd& upper_bound_vec,
        const Eigen::VectorXd& lower_bound_vec) {
        Eigen::VectorXd result_vec = Eigen::VectorXd::Zero(dimension_, 1);
        for(int i=0; i<state_vec.rows(); i++) {
            result_vec[i] = state_vec[i] > upper_bound_vec[i] ? state_vec[i] : upper_bound_vec[i];
            result_vec[i] = state_vec[i] > lower_bound_vec[i] ? state_vec[i] : lower_bound_vec[i];
        }
    }

    double Solver::evaluate(Particle* particle) {
        if((particle == nullptr) || (ptr_problem_ == nullptr)) {
            std::cout << "problem is null" << std::endl;
            exit(0);
        }

        return ptr_cost_function_->compute_loss_value(*ptr_problem_, *particle);
    }

    double Solver::evaluate(Eigen::VectorXd& position) {
        Particle particle;
        particle.set_position(position);
        return evaluate(&particle);
    }

    void Solver::start() {
        
    }
}