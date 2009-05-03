\name{viterbi.msm}
\title{Calculate the most likely path through underlying states}
\alias{viterbi.msm}

\description{
  For a fitted hidden Markov model, or a model with censored state
  observations, the Viterbi algorithm recursively constructs the path
  with the highest probability through the underlying states.
}

\usage{
viterbi.msm(x)
}
\arguments{
  \item{x}{A fitted hidden Markov multi-state model, as produced by \code{\link{msm}}}
}
\value{
    A data frame with columns:

    \code{subject} = subject identification numbers

    \code{time} = times of observations

    \code{observed} = corresponding observed states

    \code{fitted} = corresponding fitted states found by Viterbi
    recursion. If the model is not a hidden Markov model and there are
    no censored state observations, this is just the observed states. 
}
\seealso{
  \code{\link{msm}}
}
\references{
  Durbin, R., Eddy, S., Krogh, A. and Mitchison, G. \emph{Biological
    sequence analysis}, Cambridge University Press, 1998.
}
\author{C. H. Jackson \email{chris.jackson@mrc-bsu.cam.ac.uk}}
\keyword{models}
