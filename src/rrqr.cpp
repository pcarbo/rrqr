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
// This is the C++ backend to the rrqr function.
// 
// [[Rcpp::export]]
List rrqr_rcpp (const NumericMatrix& x, double tol) {

  // Compute a QR factorization of matrix X.
  const MapMatrixXd X(as<MapMatrixXd>(x));
  FullPivHouseholderQR<MatrixXd> qr(X);

  // Return the factors Q and R in the truncated (low-rank) QR
  // decomposition. The rank is determined by the number of nonzero
  // pivots.
  qr.setThreshold(tol);
  double   k = (double) qr.rank();
  MatrixXd R = qr.matrixQR().triangularView<Upper>();
  MatrixXd Q = qr.matrixQ();
  MatrixXd P = qr.colsPermutation();
  return List::create(Named("Q")    = Q,
		      Named("R")    = R,
		      Named("P")    = P,
		      Named("rank") = k);
}
