# pso
particle swarm optimization for nuclear identification

[Dependency]
Eigen

[Build & Run test]
The demo solved a regression probelm and the observed data was sampled from a function:

y = 0.3*sin(x) + 0.3*cos(x) + 0.4*sin(1.5x), where x = (0, 0.1, 0.2 ... 1).

R = [
     
     0       1.000000000000000    0
     0.841   0.540302305868140    0.997
     0.909  -0.416146836547142    0.141
     0.141  -0.989992496600445   -0.977
     -0.756 -0.653643620863612   -0.279
     -0.958  0.283662185463226    0.937
     -0.279  0.960170286650366    0.412
     0.656   0.753902254343305   -0.879
     0.989  -0.145500033808614   -0.536
     0.412  -0.911130261884677    0.803
     -0.544 -0.839071529076452    0.650]

Obs_data = [

      0.300
      0.813
      0.204
     -0.645
     -0.534
      0.172
      0.369
      0.071
      0.038
      0.171
     -0.154]

g++ -std=c++11 local_mat_operator.cpp problem.cpp particle.cpp cost_function.cpp solver.cpp solver_test.cpp -o pso_test
./pso_test
