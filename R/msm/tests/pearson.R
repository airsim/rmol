source("local.R")
library(msm)
#library(msm, lib.loc="~/lib/R")
data(psor)

psor.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)), control = list(REPORT=1,trace=2), method="BFGS")
pears <- pearson.msm(psor.msm)
stopifnot(isTRUE(all.equal(4027, pears$test$stat, tol=1)))

if (developer.local) {
    load(file="../../gof/cavfit.rda")
    load("../../gof/rtimemaster") # For the maxtimes. One per observation 
    set.seed(22061976)
    cav.pears <- pearson.msm(cavfit, transitions=c(1,2,3,4,5,6,7,8,9,10,11,11,11,12,13), timegroups=1, intervalgroups=3, covgroups=2, maxtimes=rtimemaster)
    stopifnot(isTRUE(all.equal(62.3407612120636, cav.pears$test$stat, tol=1e-03)))
}

cat("gof.R: ALL TESTS PASSED\n")
