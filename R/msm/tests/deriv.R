### Speed and accuracy of convergence with derivatives, for examples used in simple.R.

source("local.R")
library(msm)

if (developer.local) { 
    data(cav)
    twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))

### Cav, death 
### 4.6 seconds with derivs, 11.93 seconds without.  Same CIs. 
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, use.deriv=TRUE, 
                                 method="BFGS", control=list(trace=5, REPORT=1) ))
    stopifnot(isTRUE(all.equal(3968.7978930519, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm

    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, use.deriv=FALSE, 
                                 method="BFGS", control=list(trace=5, REPORT=1) ))
    stopifnot(isTRUE(all.equal(3968.7978930519, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm

### Cav, no death
### 4.18 seconds with derivs, 10.70 without. Same SEs. 
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = FALSE, fixedpars=FALSE, use.deriv=TRUE,
                                 method="BFGS", control=list(trace=1, REPORT=1)) )
    stopifnot(isTRUE(all.equal(3986.08765893935, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm

    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = FALSE, fixedpars=FALSE, use.deriv=FALSE,
                                 method="BFGS", control=list(trace=1, REPORT=1)) )
    cav.msm


### Cav, covariates
### 11.81 with, 51.86 without
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, use.deriv=TRUE,
                                 covariates = ~ sex, method="BFGS", control=list(trace=5, REPORT=1)))
    stopifnot(isTRUE(all.equal(3954.77699876128, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, use.deriv=FALSE,
                                 covariates = ~ sex, method="BFGS", control=list(trace=5, REPORT=1)))
    stopifnot(isTRUE(all.equal(3954.77699876128, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm


### Cav, baseline constraints
### 2.69 with, 4.00 without
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, qconstraint = c(1,1,2,2,2,3,3), use.deriv=TRUE,
                                 method="BFGS", control=list(trace=2, REPORT=1)
                                 ))
    stopifnot(isTRUE(all.equal(4116.22686367935, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, qconstraint = c(1,1,2,2,2,3,3), use.deriv=FALSE,
                                 method="BFGS", control=list(trace=2, REPORT=1)
                                 ))
    stopifnot(isTRUE(all.equal(4116.22686367935, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm

### Cav, covariate constraints
### Last (tenth) parameter fails deriv.test, and MLEs are different.  With both death FALSE and TRUE, This is probably an irregular likelihood. 
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = FALSE, fixedpars=FALSE, 
                                 covariates = ~ sex, covinits = list(sex=rep(0.01, 7)), constraint=list(sex=c(1,2,3,1,2,3,2)),                            
###                             use.deriv=TRUE,  opt.method="nlm", print.level=2))
                                 deriv.test=TRUE,
                                 use.deriv=TRUE, method="BFGS", control=list(trace=1, REPORT=1)))
    cav.msm


### Psor
### 1.62 with, 4.09 without
    data(psor)
    psor.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
    system.time(psor.msm <- msm(state ~ months, subject=ptnum, data=psor,
                                qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)),
                                fixedpars=FALSE, use.deriv=TRUE, control = list(REPORT=1,trace=2), method="BFGS"))
    stopifnot(isTRUE(all.equal(1114.89946121717, psor.msm$minus2loglik, tol=1e-06)))
    psor.msm
    system.time(psor.msm <- msm(state ~ months, subject=ptnum, data=psor,
                                qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)),
                                fixedpars=FALSE, use.deriv=FALSE, control = list(REPORT=1,trace=2), method="BFGS"))
    stopifnot(isTRUE(all.equal(1114.89946121717, psor.msm$minus2loglik, tol=1e-06)))
    psor.msm

### BOS.
### 3.04 with, 3.89 without
    data(bos)
    fiveq <- rbind(c(0,0.01,0,0,0.002), c(0,0,0.07,0,0.01), c(0,0,0,0.07,0.02), c(0,0,0,0,0.03), c(0,0,0,0,0))
    system.time(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, exacttimes=TRUE, use.deriv=TRUE))
    stopifnot(isTRUE(all.equal(3026.61453062733, msmtest5$minus2loglik, tol=1e-06)))
    msmtest5
    system.time(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, exacttimes=TRUE, use.deriv=FALSE))
    stopifnot(isTRUE(all.equal(3026.61453062733, msmtest5$minus2loglik, tol=1e-06)))
    msmtest5

### BOS, covariates,
    system.time(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, covariates=~time, covinits=list(time=rep(0.01, 7)), constraint=list(time=c(1,2,3,1,2,3,1)), death=TRUE, deriv.test=TRUE))
### FIXME no SEs. 
    system.time(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, covariates=~time, control=list(fnscale=3000), exacttimes=TRUE, use.deriv=TRUE))
    msmtest5
    system.time(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, covariates=~time, exacttimes=TRUE, use.deriv=FALSE))
    msmtest5

### BOS, covariate constraints

### Marshall
### 1.88 with, 7.59 without
    marsh.df <- read.table("~/msm/tests/markov/test.dat", col.names=c("subject","eyes","time","duration","hba1"))
    marsh.df$hba1 <- marsh.df$hba1 - mean(marsh.df$hba1)
    system.time(marsh.msm <-
                msm(eyes ~ time, subject=subject, qmatrix = rbind(c(0,0.02039,0,0), c(0.007874,0,0.01012,0), c(0,0.01393,0,0.01045), c(0,0,0,0)),
                    covariates = ~ hba1, data = marsh.df, method="BFGS", use.deriv=TRUE, control=list(reltol=1e-16)))
    stopifnot(isTRUE(all.equal(310.1006847488, marsh.msm$minus2loglik, tol=1e-06)))
    marsh.msm
    system.time(marsh2.msm <-
                msm(eyes ~ time, subject=subject, qmatrix = rbind(c(0,0.02039,0,0), c(0.007874,0,0.01012,0), c(0,0.01393,0,0.01045), c(0,0,0,0)),
                    covariates = ~ hba1, data = marsh.df, use.deriv=FALSE, control=list(reltol=1e-16)))
    try(stopifnot(isTRUE(all.equal(310.1006847488, marsh2.msm$minus2loglik, tol=1e-06))))
    ## Slightly different MLEs in this case.  Contour plot reveals flat likelihood in region of max. 
    marsh2.msm


### nlm optimization method.

    ## Less efficient with gradient.  10 seconds with, 6.7 without,
    ## Calculation of the Hessian is slower
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE,
                                 use.deriv=TRUE, opt.method="nlm", print.level=2))
    stopifnot(isTRUE(all.equal(3968.7978930519, cav.msm$minus2loglik, tol=1e-06)))
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE,
                                 use.deriv=FALSE, opt.method="nlm", print.level=2))
    stopifnot(isTRUE(all.equal(3968.7978930519, cav.msm$minus2loglik, tol=1e-06)))

    ## Covariates.  41 seconds with, 40.44 seconds without
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, use.deriv=TRUE,
                                 covariates = ~ sex, opt.method="nlm", print.level=2))
    stopifnot(isTRUE(all.equal(3954.77699876128, cav.msm$minus2loglik, tol=1e-06)))
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE, use.deriv=FALSE,
                                 covariates = ~ sex, opt.method="nlm", print.level=2))
    stopifnot(isTRUE(all.equal(3954.77699876128, cav.msm$minus2loglik, tol=1e-06)))

}


### Score residuals
data(psor)
psor.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
psor2 <- na.omit(psor); rownames(psor2) <- 1:nrow(psor2)
system.time(psor.msm <- msm(state ~ months, subject=ptnum, data=psor2,
                            qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn, # covinits=list(hieffusn = c(0.5, 0.1, 0), ollwsdrt=c(0.2, 0.1, -0.1)),
                            constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)),
                            fixedpars=FALSE, control = list(REPORT=1,trace=2), method="BFGS"))
sres <- scoreresid.msm(psor.msm)
if (interactive()) { 
    sres <- scoreresid.msm(psor.msm, plot=TRUE)
}

### Do they work intuitively as influence measure: try to manipulate a subject to have high influence 
psor2$months[psor2$ptnum==5] <- psor2$months[psor2$ptnum==5]*20
system.time(psor.msm <- msm(state ~ months, subject=ptnum, data=psor2,
                            qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn, # covinits=list(hieffusn = c(0.5, 0.1, 0), ollwsdrt=c(0.2, 0.1, -0.1)),
                            constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)),
                            fixedpars=FALSE, use.deriv=FALSE, control = list(REPORT=1,trace=2), method="BFGS"))
sres <- scoreresid.msm(psor.msm)
if (interactive()) { 
    sres <- scoreresid.msm(psor.msm, plot=TRUE)
}


cat("deriv.R: ALL TESTS PASSED\n")
