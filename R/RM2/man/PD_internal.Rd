\name{PD_internal}
\alias{PD_internal}
\title{ Unconstrain the demand using the Projection-Detruncation algorithm }
\description{
  \code{PD_internal} is the internal function called by \code{PD} .
}
\usage{
PD_internal(demand = demand, tau = 0.5, eps = 0.005)
}
\arguments{
  \item{demand}{ demand vector with constrained and unconstrained entries. A 0 in the name of an entry means that the corresponding demand is unconstrained. Conversely, a 1 in the name of an entry suggests that the corresponding demand is constrained. }
  \item{tau}{ fixed constant that reflects how aggresive the unconstrainig is. The default value is 0.5.}
  \item{eps}{ small number used as the stopping criterion. The default value is 0.005.}
}
\details{
  \code{PD_internal} unconstrains demand data in quantity-based revenue management. 
}
\value{
  \item{param}{ parameters of demand distribution }
  \item{niter}{ number of iterations }
  \item{demand}{ unconstrained demand }
  \item{history}{ convergence history }
}
\references{ Talluri, K. T. and Van Ryzin, G. (2004) \emph{The Theory and Practice of Revenue Management}. New York, NY: Springer Science + Business Media, Inc. (Pages 485-486).}
\author{ 
Tudor Bodea \email{tudor.bodea@ihg.com} \cr 
Dev Koushik \email{dev.koushik@ihg.com} \cr
Mark Ferguson \email{mark.ferguson@mgt.gatech.edu}
}
\keyword{ internal }
