#include "problem.h"
#include "local_mat_operator.h"
using namespace pso;

int main()
{
    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(3,3);
    Eigen::MatrixXd vec = Eigen::MatrixXd::Random(3,1);
    //Problem *p = new Problem(mat, vec);
    Problem *p = new Problem("R.txt", "observe_data.txt");
    std::cout << "Response matrix : " << std::endl;
    std::cout << p->get_response_matrix() << std::endl << std::endl;

    std::cout << "N_code : " << std::endl;
    std::cout << p->get_observed_data() << std::endl <<std::endl;

    std::cout << "N_cal : " << std::endl;
    Eigen::VectorXd phi = Eigen::Vector3d(0.2, 0.3, 0.5);
    std::cout << p->get_response_matrix()*phi << std::endl;

    std::cout << "built success = " << p->is_load_success() << std::endl;

    delete p;
    p = nullptr;
}