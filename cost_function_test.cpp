#include "cost_function.h"
#include "problem.h"
#include "particle.h"

using namespace pso;

int main() {
    Particle *particle = new Particle();
    Problem *problem = new Problem("R.txt", "observe_data.txt");
    CostFunction *func = new CostFunction();

    particle->set_position(Eigen::VectorXd::Ones(3,1));

    double loss = func->compute_loss_value_of_particle(problem, particle);
    std::cout << "loss of a particle = " << loss << std::endl;

    loss = func->compute_loss_value_with_given_position(problem, Eigen::VectorXd::Ones(3,1));
    std::cout << "loss of a position = " << loss << std::endl;
    return 0;
}