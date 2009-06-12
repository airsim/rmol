\name{plot.survfit.msm}
\alias{plot.survfit.msm}
\title{Plot empirical and fitted survival curves}
\description{
  Plot a Kaplan-Meier estimate of the survival probability and compare
  it with the fitted survival probability from a \code{msm} model. 
}
\usage{
plot.survfit.msm(x, from=1, to=NULL, range=NULL, covariates="mean",
                 interp=c("start","midpoint"), ci=c("none","normal","bootstrap"), B=100,
                 legend.pos=NULL, xlab="Time", ylab="Survival probability", lwd=1, ...)
}
\arguments{

  \item{x}{Output from \code{\link{msm}}, representing a fitted
    multi-state model object.}

  \item{from}{State from which to consider survival. Defaults to
    state 1. }

  \item{to}{Absorbing state to consider. Defaults to the
    highest-labelled absorbing state. }

  \item{range}{Vector of two elements, giving the range of times to plot
  for.}

  \item{covariates}{Covariate values for which to evaluate the expected
    probabilities.  This can either be:\cr

    the string \code{"mean"}, denoting the means of the covariates in
    the data (this is the default),\cr

    the number \code{0}, indicating that all the covariates should be
    set to zero,\cr

    or a list of values, with optional names. For example

    \code{list (60, 1)}

    where the order of the list follows the order of the covariates
    originally given in the model formula, or a named list, 

    \code{list (age = 60, sex = 1)}
  }

  \item{ci}{If \code{"none"} (the default) no confidence intervals are
    plotted.  If \code{"normal"} or \code{"bootstrap"}, confidence
    intervals are plotted based on the respective method in
    \code{\link{pmatrix.msm}}. This is very computationally-intensive,
    since intervals must be computed at a series of times.}

  \item{B}{Number of bootstrap or normal replicates for the confidence
    interval.  The default is 100 rather than the usual 1000, since
    these plots are for rough diagnostic purposes.}
  
  \item{interp}{If \code{interp="start"} (the default) then the entry
    time into the absorbing state is assumed to be the time it is first
    observed in  the data.
  
  If \code{interp="midpoint"} then the entry time into the absorbing
  state is assumed to be halfway between the time it is first observed
  and the previous observation time. This is generally more reasonable
  for "progressive" models with observations at arbitrary times. }

  \item{legend.pos}{Vector of the \eqn{x} and \eqn{y} position,
    respectively, of the legend.}
  \item{xlab}{x axis label.}
  \item{ylab}{y axis label.}
  \item{lwd}{Line width. See \code{\link{par}}.}  
  \item{...}{Other arguments to be passed to the
    \code{\link{plot.survfit}} and \code{\link{lines.survfit}} functions.}
}
\details{
  If the data represent observations of the process at arbitrary times, then
  the first occurrence of the absorbing state in the data will usually
  be greater than the actual first transition time to that state.
  Therefore the Kaplan-Meier estimate of the survival probability will
  be an overestimate.

  This currently only handles time-homogeneous models. 
}
\seealso{\code{\link{survfit}}, \code{\link{plot.survfit}}, \code{\link{plot.prevalence.msm}}}
\keyword{models}
