#include "problem.h"
#include "local_mat_operator.h"
using namespace pso;

int main()
{
    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(3,3);
    Eigen::MatrixXd vec = Eigen::MatrixXd::Random(3,1);
    //Problem *p = new Problem(mat, vec);
    Problem *p = new Problem("local_mat.txt", "local_mat.txt");
    std::cout << "Response matrix : " << std::endl;
    std::cout << p->get_response_matrix() << std::endl;

    std::cout << "Observed data : " << std::endl;
    std::cout << p->get_observed_data();

    std::cout << "form success = " << p->is_load_success() << std::endl;
    
    delete p;
    p = nullptr;
    
/*
   local_mat_operator *p = new local_mat_operator();
   p->load_local_file("local_mat.txt");
   Eigen::MatrixXd mat = p->get_local_mat();

   p->load_local_file("local_mat.txt");
   Eigen::MatrixXd mat1 = p->get_local_mat();

   delete p;
   p = nullptr;
*/
}