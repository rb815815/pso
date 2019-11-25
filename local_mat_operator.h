#ifndef __LOCAL_MAT_OPERATOR_
#define __LOCAL_MAT_OPERATOR_

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

class local_mat_operator
{
public:
    // default constructor
    local_mat_operator();

    // constructor with exitsting matrix
    local_mat_operator(const Eigen::MatrixXd& existing_mat);

    /*
    @brief save matrix to local txt file  
    @param path output file path
    */
    bool save_txt_file(const std::string path);

    /*
    @brief load local matrix file to memory
    */
    bool load_local_file(const std::string path);

    /*
    @brief print basic properties of local_mat_
    */
    void print_basic_properties();

private:
    Eigen::MatrixXd local_mat_;
};

#endif