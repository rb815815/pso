#include "particle.h"

using namespace pso;

// check whether the defaul constructor works correctly
void test_default_constructor() {
    particle p;
    std::cout << "the fitness value : " << p.get_fitness()
        << std::endl << std::endl;;
}

// check the get/set methods
void test_get_set_methods() { 
    Eigen::VectorXd vec_pos = Eigen::VectorXd::Random(5,1);
    Eigen::VectorXd vec_vel = Eigen::VectorXd::Random(5,1);
    double fitness = 10.0;

    particle p;
    p.update_particle_state(vec_pos, vec_vel, fitness);

    std::cout << "position : "<< std::endl << p.get_position() << std::endl;
    std::cout << "velocity : " << std::endl << p.get_veloctiy() << std::endl;
    std::cout << "pbest : " << std::endl<< p.get_pbest() << std::endl;
    std::cout << "fitness : " << std::endl << p.get_fitness() << std::endl;
}

int main() {

    std::cout << "test_particle_constructor " << std::endl;
    test_default_constructor();

    std::cout << "test_particle_get_set_methods " << std::endl;
    test_get_set_methods();

    return 0;
}