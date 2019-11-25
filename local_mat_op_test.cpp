#include "local_mat_operator.h"

void test_default_constructor()
{
    local_mat_operator* op = new local_mat_operator();
    op->print_basic_properties();
    delete op;
    op = nullptr;
}

void test_constructor_with_existing_mat()
{
    Eigen::MatrixXd mat;
    mat = Eigen::MatrixXd::Random(5,5);
    std::cout << "origin mat : " << std::endl;
    std::cout << mat << std::endl;

    local_mat_operator* op = new local_mat_operator(mat);
    op->print_basic_properties();
    delete op;
    op = nullptr;
}

void test_saver()
{
    Eigen::MatrixXd mat;
    mat = Eigen::MatrixXd::Random(5,5);

    local_mat_operator* op = new local_mat_operator(mat);
    op->save_txt_file("local_mat.txt");
    delete op;
    op = nullptr;
}

void test_loader()
{
    local_mat_operator* op = new local_mat_operator();
    op->print_basic_properties();
    // test with non existing file
    bool success = op->load_local_file("local_mat1.txt");
    if(success == false)
    {
        std::cout << "success , tesing read non-existing file " << std::endl;         
    }
    else
    {
        std::cout << "falied , tesing read non-existing file " << std::endl;
    }
    
    // test with existing file
    success = op->load_local_file("local_mat.txt");
    if(success == true)
    {        
        std::cout << "success , tesing read existing file " << std::endl;
        op->print_basic_properties();
    }
    else
    {
        std::cout << "failed , tesing read existing file " << std::endl;
    }
    

    delete op;
    op = nullptr;
}

int main(int argc, char** argv)
{
    test_default_constructor();
    test_constructor_with_existing_mat();
    test_saver();
    test_loader();

    return 0;
}