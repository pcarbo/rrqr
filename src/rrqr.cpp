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
List rrqr_rcpp (const NumericMatrix& x) {
  const MapMatrixXd X(as<MapMatrixXd>(x));
  FullPivHouseholderQR<MatrixXd> qr(X);
  qr.setThreshold(1e-8);
  double   k = (double) qr.rank();
  MatrixXd R = qr.matrixQR().triangularView<Upper>();
  MatrixXd Q = qr.matrixQ();
  MatrixXd P = qr.colsPermutation();
  return List::create(Named("Q")    = Q,
		      Named("R")    = R,
		      Named("P")    = P,
		      Named("rank") = k);
}
