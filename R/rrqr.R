#' @useDynLib rrqr
#'
#' @importFrom Rcpp evalCpp
#' 
#' @export
#'
outerproduct <- function (x)
  rcppeigen_outerproduct(x)
