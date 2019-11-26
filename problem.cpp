// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#include "problem.h"
#include "local_mat_operator.h"

namespace pso {

    Problem::~Problem() {
        delete local_mat_loader_;
        local_mat_loader_ = nullptr;
    }

    Problem::Problem(std::string response_mat_path,
            std::string observed_vec_path) {
        local_mat_loader_ = new local_mat_operator();
        bool success = false;

        // try to load local response matrix file
        success = local_mat_loader_->load_local_file(response_mat_path);
        response_mat_ = local_mat_loader_->get_local_mat();
        
        // try to load local observed data
        success &= local_mat_loader_->load_local_file(observed_vec_path);
        observed_vec_ = local_mat_loader_->get_local_mat();

        // check whether the problem formed correctly
        if(!success) {
            std::cout << "build the problem failed due to file loading error" 
                << std::endl;
            load_success_ = false;
        }
        else {
            if(response_mat_.cols() != observed_vec_.cols()) {
                std::cout << "build the problem failed due to the dimension \
                    of R and Obs mismatch" << std::endl;
                load_success_ = false;
            }
        }

        dimension_ = response_mat_.cols();
        load_success_ = true;
    }

    Problem::Problem(const Eigen::MatrixXd& response_matrix,
            const Eigen::VectorXd& observed_data) {
        response_mat_ = response_matrix;
        observed_vec_ = observed_data;
        dimension_ = response_mat_.rows();
    }

    const int& Problem::get_dimension() {
        return dimension_;
    }

    const Eigen::MatrixXd Problem::get_response_matrix() {
        return response_mat_;
    }

    const Eigen::VectorXd& Problem::get_observed_data(){
        return observed_vec_;
    }

    const bool& Problem::is_load_success() {
        return load_success_;
    }
}