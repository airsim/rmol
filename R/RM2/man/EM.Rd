\name{EM}
\alias{EM}
\title{ Unconstrain the demand using the Expectation-Maximization algorithm }
\description{
  \code{EM} unconstrains demand data in quantity-based revenue management.
}
\usage{
EM(demand = demand, eps = 0.005)
}
\arguments{
  \item{demand}{ demand vector with constrained and unconstrained entries. A 0 in the name of an entry means that the corresponding demand is unconstrained. Conversely, a 1 in the name of an entry suggests that the corresponding demand is constrained. }
  \item{eps}{ small number used as the stopping criterion. The default value is 0.005.}
}
\details{
  \code{EM} unconstrains demand data in quantity-based revenue management. The observed demand entries, some of which are constrained because the product class was closed, are assumed to be realizations from an underlying normal distribution with mean \eqn{\mu} and standard deviation \eqn{\sigma}. The objective is to find the parameters \eqn{\mu} and \eqn{\sigma} of this underlying demand distribution.
}
\value{
  \item{param}{ parameters of demand distribution }
  \item{niter}{ number of iterations }
  \item{demand}{ unconstrained demand vector}
  \item{history}{ parameter convergence history }
}
\references{ Talluri, K. T. and Van Ryzin, G. (2004) \emph{The Theory and Practice of Revenue Management}. New York, NY: Springer Science + Business Media, Inc. (Pages 474--477).}
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
EM(demand)
EM(demand, eps=0.005)
EM(demand, eps=0.00005)
# MODIFY DEMAND VECTOR - NO CONSTRAINED INSTANCES ARE OBSERVED
names(demand) <- rep(0, length(demand))
# ATTEMPT TO UNTRUNCATE THE DEMAND
EM(demand, eps=0.005)
}
\keyword{ optimize }
