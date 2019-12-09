#include <RcppEigen.h>

// This depends statement is needed to tell R where to find the
// additional header files.
//
// [[Rcpp::depends(RcppEigen)]]

using namespace Rcpp;
using namespace Eigen;

typedef Map<MatrixXd> MapMatrixXd;

// FUNCTION DEFININTIONS
// ---------------------
// TO DO: Explain briefly what this function  does.
// 
// [[Rcpp::export]]
double rrqr_rcpp (const NumericMatrix& x) {
  const MapMatrixXd X(as<MapMatrixXd>(x));
  FullPivHouseholderQR<MatrixXd> qr(X);
  qr.setThreshold(1e-8);
  return (double) qr.rank();
}

Eigen::MatrixXd rcppeigen_hello_world() {
  MatrixXd m1 = MatrixXd::Identity(3,3);
  MatrixXd m2 = MatrixXd::Zero(3,3);
  for (auto i = 0; i < m2.rows(); i++)
    for (auto j = 0; j < m2.cols(); j++)
      m2(i,j) = R::rnorm(0,1);
  return m1 + 3*(m1 + m2);
}

Eigen::MatrixXd rcppeigen_outerproduct (const Eigen::VectorXd& x) {
  MatrixXd m = x * x.transpose();
  return m;
}

double rcppeigen_innerproduct (const Eigen::VectorXd& x) {
  double v = x.transpose() * x;
  return v;
}

Rcpp::List rcppeigen_bothproducts (const Eigen::VectorXd& x) {
  MatrixXd op = x * x.transpose();
  double   ip = x.transpose() * x;
  return List::create(Named("outer") = op,
		      Named("inner") = ip);
}
