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

  // Compute a QR factorization of matrix X,
  //
  //   X * P = Q * R,
  //
  // where P a the permutation matrix.
  const MapMatrixXd X(as<MapMatrixXd>(x));
  ColPivHouseholderQR<MatrixXd> qr(X);

  // Return the Q and R factors of the truncated decomposition. The
  // rank is determined by the number of nonzero pivots.
  qr.setThreshold(tol);
  int      k = qr.rank();
  MatrixXd R = qr.matrixQR().triangularView<Upper>();
  MatrixXd Q = qr.matrixQ();
  R *= qr.colsPermutation().inverse();
  return List::create(Named("Q") = Q.leftCols(k),
		      Named("R") = R.topRows(k));
}
