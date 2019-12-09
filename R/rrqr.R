#' @title Add title here.
#'
#' @description Add description here.
#'
#' @param X Describe parameter here.
#'
#' @param tol Describe parameter here.
#' 
#' @examples
#'
#' set.seed(1)
#' X <- crossprod(matrix(rnorm(30),3,10))
#' rrqr(X)
#' 
#' @useDynLib rrqr
#'
#' @importFrom Rcpp evalCpp
#' 
#' @export
#' 
rrqr <- function (X, tol = 1e-8)
  rrqr_rcpp(X,tol)
