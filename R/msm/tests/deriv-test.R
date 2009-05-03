### TEST ANALYTIC AGAINST NUMERIC DERIVATIVES IN VARIOUS CASES.
### error is abs((numeric - analytic)/numeric)

source("local.R")
library(msm)

if (developer.local) {

data(cav)

twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))

## Base heart, death
cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, 
                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, deriv.test=TRUE)
stopifnot(cav.msm$error < 1e-03)

## Base cav, no death.
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = FALSE, fixedpars=FALSE, deriv.test=TRUE)
cav.msm
stopifnot(cav.msm$error < 1e-03)

## Base cav with qconstraint, no death.
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qconstraint = c(1,1,2,2,2,3,3),
                 qmatrix = twoway4.q, death = FALSE, fixedpars=FALSE, deriv.test=TRUE)
stopifnot(cav.msm$error < 1e-03)
cav.msm 

## Psor with no covs
data(psor)
psor.q <- rbind(c(0,0.1,0,0),c(0,0,0.2,0),c(0,0,0,0.3),c(0,0,0,0))
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, deriv.test=TRUE, use.deriv=FALSE)
psor.msm
stopifnot(psor.msm$error < 1e-02)

## Psor with no covs, repeated eigenvalues
psor.1.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, deriv.test=TRUE, use.deriv=FALSE)
psor.msm
stopifnot(psor.msm$error < 1e-02)

## Repeated eigenvalues and qconstraint. 
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, qconstraint=c(1,1,2), deriv.test=TRUE, use.deriv=FALSE)
psor.msm
stopifnot(psor.msm$error < 1e-03)


## BOS 5, exacttimes
data(bos)
fiveq <- rbind(c(0,0.01,0,0,0.002), c(0,0,0.07,0,0.01), c(0,0,0,0.07,0.02), c(0,0,0,0,0.03), c(0,0,0,0,0))
msmtest5 <- msm(state ~ time, qmatrix = fiveq, subject = ptnum, data = bos, exacttimes=TRUE, deriv.test=TRUE)
msmtest5
stopifnot(msmtest5$error < 1e-02)

## exacttimes and qconstraint
msmtest5 <- msm(state ~ time, qmatrix = fiveq, subject = ptnum, data = bos, exacttimes=TRUE, qconstraint=c(1,2,1,2,1,2,1), deriv.test=TRUE)
msmtest5
stopifnot(msmtest5$error < 1e-04)

## psor, covariates and constraint
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)), deriv.test=TRUE)
psor.msm
stopifnot(psor.msm$error < 1e-01)

## psor, covariates, repeated eigenvalues
if (0) { psor.1.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.1.q, covariates = ~ollwsdrt+hieffusn,
                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)), fixedpars=FALSE, analyticp=TRUE, deriv.test=TRUE)
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.1.q, covariates = ~ollwsdrt+hieffusn,
                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)), fixedpars=FALSE, analyticp=FALSE)
stopifnot(psor.msm$error < 1e-02)
psor.msm
## Can't calculate numeric deriv with analytic p, get inf lik in calculation. 
     }

## psor, death, covariates
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)), death=TRUE, deriv.test=TRUE)
psor.msm
stopifnot(psor.msm$error < 1e-04)

## psor, death, covariates, no constraint
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                death=TRUE, deriv.test=TRUE)
psor.msm
stopifnot(psor.msm$error < 1e-02)

## BOS, exact times, covariates
bos.msm <- msm(state ~ time, qmatrix = fiveq, covariates = ~time, subject = ptnum, data = bos, exacttimes=TRUE, deriv.test=TRUE)
stopifnot(bos.msm$error < 1e-03)

## BOS, exact times, covariates, qconstraint
bos.msm <- msm(state ~ time, qmatrix = fiveq, covariates = ~time, constraint=list(time=c(1,2,1,2,1,2,2)),
               subject = ptnum, data = bos, exacttimes=TRUE, deriv.test=TRUE)
bos.msm
stopifnot(bos.msm$error < 1e-03)

## Marshall, covariates
if (developer.local) { 
    marsh.df <- read.table("~/msm/tests/markov/test.dat", col.names=c("subject","eyes","time","duration","hba1"))
    marsh.df$hba1 <- marsh.df$hba1 - mean(marsh.df$hba1)
    marsh.msm <-
      msm(eyes ~ time, subject=subject, qmatrix = rbind(c(0,0.02039,0,0), c(0.007874,0,0.01012,0), c(0,0.01393,0,0.01045), c(0,0,0,0)),
          covariates = ~ hba1, data = marsh.df, deriv.test=TRUE, use.deriv=TRUE)
    marsh.msm
    stopifnot(marsh.msm$error < 1e-03)
}

}
cat("deriv-test.R: ALL TESTS PASSED\n")
