#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
using namespace Eigen;

void write_mat()
{
    MatrixXd mat;
    mat = MatrixXd::Random(5,5);

    std::ofstream out_file("local_file.txt");

    std::cout << "mat : " << std::endl;
    std::cout << mat << std::endl;

    if(!out_file.is_open())
    {
        std::cout << "open file failed!" << std::endl;        
    }
    else
    {
        for(int i=0; i<mat.rows(); i++)
        {
            for(int j=0; j<mat.cols(); j++)
            {
                out_file << mat(i,j) << " ";
            }
            out_file << "\n";
        }
    }
    out_file.close();
}

void read_mat()
{
    std::vector<double> values;
    int row = 0;
    int col = 0;

    std::string cur_line;
    std::ifstream in_file("local_file.txt");
    if(!in_file.is_open())
    {
        std::cout << "file dose not exits" << std::endl;
        return;
    }

    while(getline(in_file, cur_line))
    {
        std::stringstream ss(cur_line);
        std::string cell;
        while (std::getline(ss, cell, ' '))
        {
            double val = std::stod(cell);
            values.push_back(val);
        }
        ++row;
    }
    col = values.size()/row;
    
    //Eigen::Matrix<double, row, col, Eigen::RowMajor> mat = 
    Eigen::MatrixXd mat = 
    Eigen::Map<const Eigen::Matrix<
        Eigen::MatrixXd::Scalar,
        Eigen::MatrixXd::RowsAtCompileTime,
        Eigen::MatrixXd::ColsAtCompileTime,
        Eigen::RowMajor> >(values.data(), row, col);

    std::cout << "mat : " << std::endl;
    std::cout << mat << std::endl;
}

/*
template <typename T>
void read_mat()
{
    std::vector<double> values;
    int row = 0;
    int col = 0;

    std::string cur_line;
    std::ifstream in_file("local_file.txt");
    if(!in_file.is_open())
    {
        std::cout << "file dose not exits" << std::endl;
        return;
    }

    while(getline(in_file, cur_line))
    {
        std::stringstream ss(cur_line);
        std::string cell;
        while (std::getline(ss, cell, ' '))
        {
            double val = std::stod(cell);
            values.push_back(val);
        }
        ++row;
    }
    col = values.size()/row;
    
    //Eigen::Matrix<double, row, col, Eigen::RowMajor> mat = 
    Eigen::MatrixXd mat = 
    Eigen::Map<const Eigen::Matrix<
        typename T::Scalar,
        T::RowsAtCompileTime,
        T::ColsAtCompileTime,
        Eigen::RowMajor> >(values.data(), row, col);

    std::cout << "mat : " << std::endl;
    std::cout << mat << std::endl;
}
*/

int main(int argc, char** argv)
{
    read_mat();
    return 0;
}