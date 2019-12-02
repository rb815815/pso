// PSO solver for neutron spectrum unfolding problem
// Copyright 2019 CDUT. All rights reserved.
//
// Author: 819701938@qq.com (Heyi Tan)
// Date :  2019.11.25

#include "local_mat_operator.h"

namespace pso {

LocalMatOperator::LocalMatOperator()
{}

LocalMatOperator::LocalMatOperator(const Eigen::MatrixXd& existing_mat) {
    local_mat_ = existing_mat;
}

LocalMatOperator::~LocalMatOperator() {}

bool LocalMatOperator::save_to_file(const std::string path) {
    std::ofstream out_file(path);
    // check whether the file had been opened
    if(!out_file.is_open()) {
        std::cout << "failed to open" << path << std::endl;
        return false;    
    }
    // write the elements to the local file in row major form
    for(int i=0; i<local_mat_.rows(); i++) {
        for(int j=0; j<local_mat_.cols(); j++) {
            out_file << local_mat_(i,j) << " ";
        }
        out_file << "\n";
    }
    std::cout << "save mat to " << path << std::endl;
    out_file.close();
    return true;
}

bool LocalMatOperator::load_local_file(const std::string path) {
    // allocate space to hold variables
    std::vector<double> values;
    int row = 0;
    int col = 0;

    std::string cur_line;
    std::ifstream in_file(path);
    if(!in_file.is_open()) {
        std::cout << "file dose not exits" << std::endl;
        return false;
    }

    // read elements in local file
    // compute the rows and cols at the same time
    while(getline(in_file, cur_line)) {
        std::stringstream ss(cur_line);
        std::string cell;
        while (std::getline(ss, cell, ' '))
        {
            double val = std::stod(cell);
            values.push_back(val);
        }
        ++row;
    }
    // check whether we load the correct data
    if(row > 0) {
        col = values.size()/row;

        // use Eigen::Map<> to convert C raw arrays to Eigen::Matrix format    
        local_mat_ = Eigen::Map<const Eigen::Matrix<
                Eigen::MatrixXd::Scalar,
                Eigen::MatrixXd::RowsAtCompileTime,
                Eigen::MatrixXd::ColsAtCompileTime,
                Eigen::RowMajor> >(values.data(), row, col);
    }
    else {
        std::cout << "empty mat" << std::endl;
        return false;
    }
}

void LocalMatOperator::print_basic_properties() {
    std::cout << "mat.rows = " << local_mat_.rows() << std::endl;
    std::cout << "mat.cols = " << local_mat_.cols() << std::endl;
}

const Eigen::MatrixXd& LocalMatOperator::get_local_mat() {
    return local_mat_;
}

}
