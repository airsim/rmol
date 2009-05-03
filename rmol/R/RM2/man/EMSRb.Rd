\name{EMSRb}
\alias{EMSRb}
\title{ Perform EMSR-b with Buy-up Heuristic for the Single-Resource Problem }
\description{
  \code{EMSRb} heuristic sets the protection levels for multiple fare classes.
}
\usage{
EMSRb(Fare = Fare, Mean = Mean, Var = Var, p_up = numeric(length(Fare)), cap = cap)
}
\arguments{
  \item{Fare}{ revenue vector associated with selling the offered products }
  \item{Mean}{ mean product demand }
  \item{Var}{ product demand variance }
  \item{p_up}{ buy-up probabilities. The default entails no buy-up probabilities. }
  \item{cap}{ available capacity }
}
\details{
  \code{EMSRb} sorts internally the \code{Fare} vector together with all other input vectors in descending order of the revenues. If \code{p_up} is missing, \code{EMSRb} performs the classical EMSRb heuristic. 
}
\value{
  \item{p}{ protection levels }
}
\author{ 
Tudor Bodea \email{tudor.bodea@ihg.com} \cr 
Dev Koushik \email{dev.koushik@ihg.com} \cr
Mark Ferguson \email{mark.ferguson@mgt.gatech.edu}
}
\examples{
## Run a simple EMRSb instance
Fare <- c(150, 100, 50, 250)
Mean <- c(75, 125, 500, 50)
Var <- c(75, 125, 500, 50)
cap <- 400
p <- EMSRb(Fare = Fare, Mean = Mean, Var = Var, cap = cap)
p
}
\keyword{ optimize }
