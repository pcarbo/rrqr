#include <RcppEigen.h>

// This depends statement is needed to tell R where to find the
// additional header files.
//
// [[Rcpp::depends(RcppEigen)]]

using namespace Rcpp;
using namespace Eigen;

typedef Map<MatrixXd> MapMatd;

// [[Rcpp::export]]
double rrqr_rcpp (NumericMatrix X) {
  const MapMatd Y(as<MapMatd>(X));
  FullPivHouseholderQR<MatrixXd> qr(Y);
  qr.setThreshold(1e-8);
  return (double) qr.rank();
}

// [[Rcpp::export]]
Eigen::MatrixXd rcppeigen_hello_world() {
  MatrixXd m1 = MatrixXd::Identity(3,3);
  MatrixXd m2 = MatrixXd::Zero(3,3);
  for (auto i = 0; i < m2.rows(); i++)
    for (auto j = 0; j < m2.cols(); j++)
      m2(i,j) = R::rnorm(0,1);
  return m1 + 3*(m1 + m2);
}

// [[Rcpp::export]]
Eigen::MatrixXd rcppeigen_outerproduct (const Eigen::VectorXd& x) {
  MatrixXd m = x * x.transpose();
  return m;
}

// [[Rcpp::export]]
double rcppeigen_innerproduct (const Eigen::VectorXd& x) {
  double v = x.transpose() * x;
  return v;
}

// [[Rcpp::export]]
Rcpp::List rcppeigen_bothproducts (const Eigen::VectorXd& x) {
  MatrixXd op = x * x.transpose();
  double   ip = x.transpose() * x;
  return List::create(Named("outer") = op,
		      Named("inner") = ip);
}
