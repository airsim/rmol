\name{MatrixExp}
\title{Matrix exponential}
\alias{MatrixExp}
\concept{Matrix exponential}
\description{
  Calculates the exponential of a square matrix.
}
\usage{
MatrixExp(mat, t = 1, n = 20, k = 3, method="pade")
}
\arguments{
  \item{mat}{A square matrix}
  \item{t}{An optional scaling factor, or a vector or scaling factors, for the eigenvalues of \code{mat}}
  \item{n}{Number of terms in the series approximation to the
    exponential}
  \item{k}{Underflow correction factor, for the series approximation}
  \item{method}{\code{"pade"} for the Pade approximation, or \code{"series"} for the
    power series approximation.
  }
}
\value{
  The exponentiated matrix \eqn{\exp(mat)}{exp(mat)}. Or, if \code{t} is
  a vector of length 2 or more, an array of exponentiated matrices. 
}
\details{
  The exponential \eqn{E} of a square matrix \eqn{M} is calculated as 

  \deqn{E = U \exp(D) U^{-1}}{E = U exp(D) U^{-1}}

  where \eqn{D} is a diagonal matrix with the eigenvalues
  of \eqn{M} on the diagonal, \eqn{\exp(D)}{exp(D)} is a diagonal matrix with the
  exponentiated eigenvalues
  of \eqn{M} on the diagonal, and \eqn{U} is a matrix whose columns are the
  eigenvectors of \eqn{M}.

  This method of calculation is used if \eqn{M} has distinct
  eigenvalues.  I If \eqn{M} has repeated eigenvalues, then its
  eigenvector matrix may be non-invertible. In this case, the matrix
  exponential is calculated using the Pade approximation defined by
  Moler and van Loan (2003), or the less robust power series
  approximation,

  \deqn{\exp(M) = I + M + M^2/2 + M^3 / 3! + M^4 / 4! + ...}{exp(M) = I + M + M^2/2 + M^3 / 3! + M^4 / 4! + ...}

  For a continuous-time homogeneous Markov process with transition
intensity matrix
  \eqn{Q},  the probability of occupying state \eqn{s} at time \eqn{u + t}
  conditional on occupying state \eqn{r} at time \eqn{u} is given by the
  \eqn{(r,s)} entry of the matrix \eqn{\exp(tQ)}{exp(tQ)}. 
  
  The implementation of the Pade approximation was taken from 
  JAGS by Martyn Plummer (\url{http://www-fis.iarc.fr/~martyn/software/jags}).
  
  The series approximation method was adapted from the corresponding
  function in Jim Lindsey's R package \code{rmutil} (\url{http://popgen.unimaas.nl/~jlindsey/rcode.html}).
}
\references{
  Cox, D. R. and Miller, H. D. \emph{The theory of stochastic
    processes}, Chapman and Hall, London (1965)

  Moler, C and van Loan, C (2003).  Nineteen dubious ways to compute
  the exponential of a matrix, twenty-five years later.
  \emph{SIAM Review} \bold{45},
  3--49. \cr
  At \url{http://epubs.siam.org/sam-bin/dbq/article/41801}
}
\keyword{math}
