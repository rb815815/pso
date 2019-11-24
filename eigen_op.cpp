#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
using namespace Eigen;

int main()
{
    MatrixXd mat;
    mat = MatrixXd::Random(5,5);

    std::cout << "mat : " << std::endl;
    std::cout << mat << std::endl;

    return 0;
}