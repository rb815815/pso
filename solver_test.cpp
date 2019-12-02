#include <iostream>
#include "solver.h"
#include "problem.h"
#include "local_mat_operator.h"
#include "cost_function.h"

using namespace pso;

void test_the_constructor() {
	Solver* solver = new Solver(100, 3, 100, 2.5, 1.5, 1e-7, 0.0, 1.0);
	solver->print_debug_info();

	delete solver;
}

void test_build_problem() {
	Problem* problem = new Problem("R.txt", "observe_data.txt");
	CostFunction *cost_function = new CostFunction();
	Solver* solver = new Solver(100, 3, 100, 2.5, 1.5, 1e-7, 0.0, 1.0);
	solver->build_problem(problem, cost_function);

	solver->print_debug_info();

	delete problem;
	delete cost_function;
	delete solver;

	problem = nullptr;
	cost_function = nullptr;
	solver = nullptr;
}

/*
void test_truncate_vector() {
	Solver* solver = new Solver(100, 3, 100, 2.5, 1.5, 1e-7, 0.0, 1.0);

	Eigen::VectorXd threshold_high = Eigen::VectorXd::Ones(3,1);
	Eigen::VectorXd threshold_low = Eigen::VectorXd::Zero(3,1);
	Eigen::VectorXd v = Eigen::Vector3d(-1.5, 2, 0.5);

	std::cout << "before truncate : " << std::endl;
	std::cout << v << std::endl;
	solver->truncate_vec_value(v, threshold_high, threshold_low);

	std::cout << "after truncate : " << std::endl;
	std::cout << v << std::endl;

	delete solver;
}

void test_init_particles() {
	Problem* problem = new Problem("R.txt", "observe_data.txt");
	CostFunction *cost_function = new CostFunction();
	Solver* solver = new Solver(100, 3, 100, 2.5, 1.5, 1e-7, 0.0, 1.0);
	solver->build_problem(problem, cost_function);

	std::cout << "before initialization" << std::endl;
	solver->print_debug_info();
	std::cout << std::endl;

	solver->init_particles();
	std::cout << "after initialization" << std::endl;
	solver->print_debug_info();

	delete problem;
	delete cost_function;
	delete solver;
	
	problem = nullptr;
	cost_function = nullptr;
	solver = nullptr;
}

void test_assign_state_to_partilce() {
	Solver* solver =new Solver(100, 3, 100, 1.5, 2.0, 1e-7, 1.0, 0.0);
	Particle* partilce = new Particle();
	partilce->set_position(Eigen::VectorXd::Ones(3,1)*5);
	partilce->set_velocity(Eigen::VectorXd::Ones(3,1)*2);
	partilce->set_best_fitness(Eigen::VectorXd::Ones(3,1)*5, 1000);

	std::cout << "before assignment :" << std::endl;
	std::cout << "position = [" << partilce->get_position().transpose() << "]" << std::endl;
	std::cout << "velocity = [" << partilce->get_veloctiy().transpose() << "]" << std::endl;
	std::cout << "fitness = [" << partilce->get_best_fitness() << "]" << std::endl;

	solver->assign_state_to_particle(partilce, Eigen::VectorXd::Ones(3,1)*20,
		Eigen::VectorXd::Ones(3,1)*-40, 100);

	std::cout << "after assignment : " << std::endl; 
	std::cout << "position = [" << partilce->get_position().transpose() << "]" << std::endl;
	std::cout << "velocity = [" << partilce->get_veloctiy().transpose() << "]" << std::endl;
	std::cout << "fitness = [" << partilce->get_best_fitness() << "]" << std::endl;

	delete solver;
	delete partilce;
}
*/

void test_start() {
	Problem* problem = new Problem("R.txt", "observe_data.txt");
	CostFunction *cost_function = new CostFunction();
	Solver* solver = new Solver(100, 3, 100, 1.5, 2.5, 1e-7, 0.0, 1.0);
	solver->build_problem(problem, cost_function);

	solver->init_particles();
	std::cout << "before optimization :" << std::endl;
	solver->print_debug_info();

	std::cout << std::endl;
	solver->start();
	std::cout << std::endl << "after optimization :" << std::endl;
	solver->print_debug_info();

	delete solver;
	delete problem;
	delete cost_function;
}

int main(int argc, char** argv) {
	//test_build_problem();
	//test_truncate_vector();
	//test_init_particles();
	//test_assign_state_to_partilce();
	
	test_start();
	
	return 0;
}
