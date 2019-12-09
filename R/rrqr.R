#' @title Rank-revealing QR factorization
#'
#' @description This is a simple R front-end to the Householder
#' rank-revealing QR factorization with column-pivoting as implemented
#' in the Eigen library.
#'
#' @param X The n x m matrix to be factorized.
#'
#' @param tol The threshold for determining which pivots are zero; the
#'   rank of the QR decomposition is determined 
#'
#' @return The return value is a list containing the factors: the n x
#'   k matrix \code{Q} and the k x m matrix \code{R}, were k is the
#'   estimated numerical rank of \code{X}.
#' 
#' @examples
#' # Generate a 10 x 5 matrix that effectively has a rank of 3.
#' set.seed(1)
#' x <- matrix(rnorm(30),3,10)
#' y <- matrix(rnorm(15),3,5)
#' X <- crossprod(x,y) + 1e-8 * rnorm(50)
#' print(svd(X)$d,digits = 2)
#'
#' # Compute full-rank and low-rank QR factorizations of X; the 
#' # full-rank factorization recovers X exactly (up to numerical
#' # precision), whereas the low-rank factorization recovers the full
#' # matrix X with only a slight loss in accuracy.
#' out1 <- rrqr(X,tol = 0)
#' out2 <- rrqr(X)
#' cat("Estimated rank:",ncol(out2$Q),"\n")
#' cat("Largest error in full-rank QR:",max(abs(X - with(out1,Q %*% R))),"\n")
#' cat("Largest error in low-rank QR:",max(abs(X - with(out2,Q %*% R))),"\n")
#' 
#' @useDynLib rrqr
#'
#' @importFrom Rcpp evalCpp
#' 
#' @export
#' 
rrqr <- function (X, tol = 1e-8)
  rrqr_rcpp(X,tol)
