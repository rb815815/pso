// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#ifndef __LOCAL_MAT_OPERATOR_
#define __LOCAL_MAT_OPERATOR_

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

namespace pso {
class local_mat_operator
{
public:
    local_mat_operator();

    /**
    * @brief init local_mat_ with an exitsting matrix
    * @param[in] existing_mat   an Eigen::MatrixXd instance in memory
    */
    local_mat_operator(const Eigen::MatrixXd& existing_mat);

    /**
    * @brief destructor
    */
    virtual ~local_mat_operator();

    /**
    * @brief save matrix to local txt file  
    * @param[in] path output file path
    * 
    * @return is save_to_file successful
    *  -- 0 : failed
    *  -- 1 : sucess
    */
    bool save_to_file(const std::string path);

    /**
    * @brief load local matrix file to memory
    * @param[in] path   local file path
    * 
    * @return is load_local_file successful
    *  -- 0 : failed
    *  -- 1 : sucess
    */
    bool load_local_file(const std::string path);

    /**
    * @brief print basic properties of local_mat_
    */
    void print_basic_properties();

    /**
    * @brief get local mat
    *
    * @return a const reference to local_mat_
    */
    const Eigen::MatrixXd& get_local_mat();

private:
    Eigen::MatrixXd local_mat_;
};

}

#endif