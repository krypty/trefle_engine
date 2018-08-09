// main.cpp
#include "fis.h"
#include "linear_interpolation.h"
#include "omp.h"
#include "trilv.h"
#include "trimf.h"
#include <Eigen/Dense>
#include <iostream>
#include <membershipfunction_i.h>
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
  double d = LinearInterpolation::interp(xs, ys, x);
  cout << "d: " << d << endl;

  TriMF mf(10, 20, 30);
  cout << mf.fuzzify(1.3) << endl;
  cout << mf.fuzzify(15) << endl;
  cout << mf.fuzzify(20) << endl;
  cout << mf.fuzzify(29) << endl;


  cout << "Test TriLV 2" << endl;
  TriLV lv({20, 30});
  cout << lv.fuzzify(0, 20) << endl;
  cout << lv.fuzzify(0, 25) << endl;
  cout << lv.fuzzify(0, 30) << endl;
  cout << lv.fuzzify(1, 20) << endl;
  cout << lv.fuzzify(1, 25) << endl;
  cout << lv.fuzzify(1, 30) << endl;
  cout << endl << endl;

  cout << "Test TriLV 3" << endl;
  TriLV lv3({20, 30, 35});
  cout << lv3.fuzzify(0, 20) << endl;
  cout << lv3.fuzzify(0, 25) << endl;
  cout << lv3.fuzzify(0, 30) << endl;
  cout << lv3.fuzzify(1, 20) << endl;
  cout << lv3.fuzzify(1, 25) << endl;
  cout << lv3.fuzzify(1, 30) << endl;
  cout << lv3.fuzzify(2, 20) << endl;
  cout << lv3.fuzzify(2, 30) << endl;
  cout << lv3.fuzzify(2, 33) << endl;


//  int nthreads, tid;

///* Fork a team of threads giving them their own copies of variables */
//#pragma omp parallel private(nthreads, tid)
//  {

//    /* Obtain thread number */
//    tid = omp_get_thread_num();
//    printf("Hello World from thread = %d\n", tid);

//    /* Only master thread does this */
//    if (tid == 0) {
//      nthreads = omp_get_num_threads();
//      printf("Number of threads = %d\n", nthreads);
//    }

//  } /* All threads join master thread and disband */

//  //   assert(false);

  return 0;
}
