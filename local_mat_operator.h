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
        /*
        @brief default constructor
        */
        local_mat_operator();

        /*
        @brief constructor with exitsting matrix
        */
        local_mat_operator(const Eigen::MatrixXd& existing_mat);

        /*
        @brief destructor
        */
        virtual ~local_mat_operator();

        /*
        @brief save matrix to local txt file  
        @param path output file path
        */
        bool save_to_file(const std::string path);

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
}

#endif