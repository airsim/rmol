\name{msm.summary}
\title{Summarise a fitted multi-state model}
\alias{summary.msm}
\alias{print.summary.msm}
\description{
  Summary method for fitted \code{\link{msm}} models. Currently, this produces a table of observed and
  expected state prevalences for each time. For models with covariates, prints
  hazard ratios with confidence intervals for covariate effects.
}
\usage{
\method{summary}{msm}(object, times=NULL, timezero=NULL, initstates=NULL,
covariates="mean", misccovariates="mean", hazard.scale=1, \dots)
}
\arguments{
  \item{object}{A fitted multi-state model object, as returned by
    \code{\link{msm}}.}
  \item{times}{A sequence of times at which to compare observed
    and expected prevalences of each state. Defaults to
    \code{seq(min(times), max(times), (max(times) - min(times))/10).
    }
  }
  \item{timezero}{Initial time of the Markov process. Expected values
    are forecasted from here. Defaults to the minimum of the observation
    times given in the data. }
  \item{initstates}{ Optional vector of the same length as the number of
    states. Gives the numbers of individuals occupying each state at
    \code{timezero}. The default is that all individuals are in state 1.
  }
  \item{covariates}{Covariate values for which to forecast expected
    state occupancy.  See \code{\link{qmatrix.msm}}.  Defaults to the
    mean values of the covariates in the data set.}
  \item{misccovariates}{(Misclassification models only) Values of covariates on the misclassification
    probability matrix for which to forecast expected state occupancy.
    Defaults to the mean values of the covariates in the data set.}
  \item{hazard.scale}{Vector with same elements as number of covariates
    on transition rates. Corresponds to the increase in each covariate
    used to calculate its hazard ratio. Defaults to all 1.}  
  \item{...}{further arguments passed to or from other methods.}
}
\value{
  A list of class \code{summary.msm}, with components:
  
  \item{prevalences}{Output from \code{\link{prevalence.msm}}.}

  \item{hazard}{Output from \code{\link{hazard.msm}}}.

  \item{hazard.scale}{Value of the \code{hazard.scale} argument}
}
\seealso{
  \code{\link{msm}},\code{\link{prevalence.msm}}, \code{\link{hazard.msm}}
}
\author{C. H. Jackson \email{chris.jackson@mrc-bsu.cam.ac.uk}}
\keyword{models}
