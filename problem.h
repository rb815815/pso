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
        /*
        @brief destructor
        */
        virtual ~Problem();

        /*
        @brief constructor with given file path        
        */
        Problem(std::string response_mat_path,
                std::string observed_vec_path);

        /*
        @brief constructor with given data in Eigen::Matrix form
        */
        Problem(const Eigen::MatrixXd& response_matrix,
                const Eigen::VectorXd& observed_data);

        /*
        @brief forbid copy constructor
        */
        Problem(const Problem&) = delete;

        /*
        @brief forbid assignment operator
        */
        void operator=(const Problem&) = delete;

        /*
        @brief get dimension of the respose matrix
        */
        const int& get_dimension();

        /*
        @brief get R matrix
        */
        const Eigen::MatrixXd get_response_matrix();

        /*
        @brief get Obs vector
        */
        const Eigen::VectorXd& get_observed_data();

        /*
        @brief get load state
        */
        const bool& is_load_success();

    private:
        bool load_success_;
        int dimension_;
        Eigen::MatrixXd response_mat_;
        Eigen::VectorXd observed_vec_;
        local_mat_operator* local_mat_loader_;
    };
}

#endif