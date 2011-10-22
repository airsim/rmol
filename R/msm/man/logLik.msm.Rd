\name{logLik.msm}
\alias{logLik.msm}
\title{Extract model log-likelihood}
\description{
  Extract the log-likelihood and the number of parameters of a model
  fitted with \code{\link{msm}}.  
}
\usage{
\method{logLik}{msm}(object, \dots)
}
\arguments{
  \item{object}{A fitted multi-state model object, as returned by
    \code{\link{msm}}.}
  \item{...}{(unused) further arguments passed to or from other methods.}
}
\value{
  The log-likelihood of the model represented by
  'object' evaluated at the maximum likelihood estimates.
}
\seealso{
  \code{\link{msm}}
}
\author{C. H. Jackson \email{chris.jackson@mrc-bsu.cam.ac.uk}}
\keyword{models}
