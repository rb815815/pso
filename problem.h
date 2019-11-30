// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#ifndef __PSO_PROBLEM_
#define __PSO_PROBLEM_

#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

namespace pso {

// forward declaration
class local_mat_operator;

class Problem {
public:
    virtual ~Problem();

    /**
    * @brief init response_mat_ and observed_data_ from local file
    * @param[in] response_mat_path  local file path of response matrix
    * @param[in] observed_vec_path  local file path of observed data
    */
    Problem(std::string response_mat_path,
            std::string observed_vec_path);

    /**
    * @brief init response_mat_ and observed_data_ from matrix instance in memory
    * @param[in] response_matrix    an instance of R in memory
    * @param[in] observed_data      an instance of Ncode in memory
    */
    Problem(const Eigen::MatrixXd& response_matrix,
                const Eigen::VectorXd& observed_data);

    /**
    * @brief forbid copy constructor
    */
    Problem(const Problem&) = delete;

    /**
    * @brief forbid assignment operator
    */
    void operator=(const Problem&) = delete;

    /**
    * @brief get dimension of the respose matrix
    * 
    * @return a const reference to dimension_
    */
    const int& get_dimension();

    /**
    * @brief get R matrix
    * 
    * @return a const reference to response_matrix_
    */
    const Eigen::MatrixXd get_response_matrix();

    /**
    * @brief get Obs vector
    * 
    * @return a const reference to observed_data_
    */
    const Eigen::VectorXd& get_observed_data();

    /**
    * @brief get load state
    * 
    * @return is problem built successful
    *  -- 0: failed
    *  -- 1: success
    */
    const bool& is_load_success();

private:
    bool load_success_;                 // has problem built successful
    int dimension_;                     // the dimension of 
    Eigen::MatrixXd response_mat_;      // R matrix
    Eigen::VectorXd observed_vec_;      // Ncode
    local_mat_operator* local_mat_loader_;  // pointer to local_mat_operator
};

}

#endif