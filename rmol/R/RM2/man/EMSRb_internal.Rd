\name{EMSRb_internal}
\alias{EMSRb_internal}
\title{ Perform EMSR-b with Buy-up Heuristic for the Single-Resource Problem }
\description{
  \code{EMSRb_internal} is called by \code{EMRSb} and sets the protection levels for multiple fare classes.
}
\usage{
EMSRb_internal(Fare = Fare, Mean = Mean, Var = Var, p_up = numeric(length(Fare)), cap = cap)
}
\arguments{
  \item{Fare}{ revenue vector associated with selling the offered products }
  \item{Mean}{ mean product demand }
  \item{Var}{ product demand variance }
  \item{p_up}{ buy-up probabilities. The default entails no buy-up probabilities. }
  \item{cap}{ available capacity }
}
\details{
  \code{EMSRb_internal} sorts internally the \code{Fare} vector together with all other input vectors in descending order of the revenues. If \code{p_up} is missing, \code{EMSRb_internal} performs the classical EMSRb heuristic. 
}
\value{
  \item{p}{ protection levels }
}
\author{ 
Tudor Bodea \email{tudor.bodea@ihg.com} \cr 
Dev Koushik \email{dev.koushik@ihg.com} \cr
Mark Ferguson \email{mark.ferguson@mgt.gatech.edu}
}
\keyword{ internal }
