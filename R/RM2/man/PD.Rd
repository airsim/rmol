\name{PD}
\alias{PD}
\title{ Unconstrain the demand using the Projection-Detruncation algorithm }
\description{
  \code{PD} unconstrains demand data in quantity-based revenue management.
}
\usage{
PD(demand = demand, tau = 0.5, eps = 0.005)
}
\arguments{
  \item{demand}{ demand vector with constrained and unconstrained entries. A 0 in the name of an entry means that the corresponding demand is unconstrained. Conversely, a 1 in the name of an entry suggests that the corresponding demand is constrained. }
  \item{tau}{ fixed constant that reflects how aggresive the unconstrainig is. The default value is 0.5.}
  \item{eps}{ small number used as the stopping criterion. The default value is 0.005.}
}
\details{
  \code{PD} unconstrains demand data in quantity-based revenue management. The observed demand entries, some of which are constrained because the product class was closed, are assumed to be realizations from an underlying normal distribution with mean \eqn{\mu} and standard deviation \eqn{\sigma}. The objective is to find the parameters \eqn{\mu} and \eqn{\sigma} of this underlying demand distribution.
}
\value{
  \item{param}{ parameters of demand distribution }
  \item{niter}{ number of iterations }
  \item{demand}{ unconstrained demand vector}
  \item{history}{ parameter convergence history }
}
\references{ Talluri, K. T. and Van Ryzin, G. (2004) \emph{The Theory and Practice of Revenue Management}. New York, NY: Springer Science + Business Media, Inc. (Pages 485--486).}
\author{ 
Tudor Bodea \email{tudor.bodea@ihg.com} \cr 
Dev Koushik \email{dev.koushik@ihg.com} \cr
Mark Ferguson \email{mark.ferguson@mgt.gatech.edu}
}
\examples{
# SPECIFY THE SEED
set.seed(333)
# SPECIFY REAL PARAMETERS OF THE DEMAND DISTRIBUTION
rmean <- 20
rsd <- 4
nrn <- 20
# GENERATE REAL DEMAND
rdemand <- round(rnorm(nrn, rmean, rsd))
# GENERATE BOOKING LIMITS
bl <- round(rnorm(nrn, rmean, rsd))
# GENERATE OBSERVED DEMAND
demand <- rdemand * (rdemand <= bl) + bl * (rdemand > bl)
# IDENTIFIED PERIODS WITH CONSTRAINED DEMAND: 1 - CONSTRAINED DEMAND
names(demand) <- as.character(as.numeric(rdemand>bl))
demand
# UNTRUNCATE DEMAND
PD(demand)
PD(demand, tau=0.5, eps=0.005)
PD(demand, tau=0.5, eps=0.00005)
# MODIFY DEMAND VECTOR - NO CONSTRAINED INSTANCES ARE OBSERVED
names(demand) <- rep(0, length(demand))
# ATTEMPT TO UNTRUNCATE THE DEMAND
PD(demand, tau=0.5, eps=0.005)
}
\keyword{ optimize }
