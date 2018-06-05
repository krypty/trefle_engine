// main.cpp
#include "fis.h"
#include "omp.h"
#include <Eigen/Dense>
#include <iostream>
#include <stdio.h>

// #define NDEBUG
// #include "assert.h"


using Eigen::MatrixXd;

int main() {
  printf("Hello World\n");
  printf("Hello World\n");

  MatrixXd m(2, 2);
  m(0, 0) = 3;
  m(1, 0) = 2.5;
  m(0, 1) = -1;
  m(1, 1) = m(1, 0) + m(0, 1);
  std::cout << m << std::endl;

  double x = 1.5;
  auto xs = vector<double>{1, 2, 4};
  auto ys = vector<double>{0, 0.5, 1};
  double d = lininterp(xs, ys, x);
  cout << "d: " << d << endl;

  int nthreads, tid;

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid)
  {

    /* Obtain thread number */
    tid = omp_get_thread_num();
    printf("Hello World from thread = %d\n", tid);

    /* Only master thread does this */
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }

  } /* All threads join master thread and disband */

//   assert(false);

  return 0;
}
