#include "problem.h"
#include "particle.h"
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

using namespace pso;

double compute_residual(Problem& problem, Particle& particle)
{
	Eigen::VectorXd result = problem.get_response_matrix() * particle.get_position();
	Eigen::VectorXd residual = problem.get_observed_data() - result;
	double loss = 0;
	for(int i=0; i<residual.cols(); i++)
	{
		loss += residual[i]*residual[i];
	}
	return loss;
}

int main()
{
	Eigen::MatrixXd mat = Eigen::MatrixXd::Random(5,5);
	Eigen::VectorXd obs = Eigen::MatrixXd::Random(5,1);
	Eigen::VectorXd pos = Eigen::MatrixXd::Random(5,1);	

	pso::Problem problem(mat, obs);
	pso::Particle particle;
	particle.set_position(pos);

	Eigen::VectorXd result = problem.get_response_matrix() * particle.get_position();
//	std::cout << result << std::endl;

	double loss = compute_residual(problem, particle);
	std::cout << "loss = " << loss << std::endl;
	
	return 0;
}

