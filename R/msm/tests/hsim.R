source("local.R")
library(msm)

if (developer.local) {

### SIMULATION FROM HIDDEN MARKOV MODELS

nsubj <- 100; nobspt <- 6
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt),
                     time = seq(0, 20, length=nobspt), 
                     x = rnorm(nsubj*nobspt),
                     y = rnorm(nsubj*nobspt)* 5 + 20)
three.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0)))

### BINOMIAL RESPONSE

hmodel3 <- list(hmmBinom(size=40, prob=0.1),
                hmmBinom(size=40, prob=0.5),
                hmmIdent(999))

set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)

## Fit model.  

hmodel3 <- list(hmmBinom(size=40, prob=0.05),
                hmmBinom(size=40, prob=0.3),
                hmmIdent(999))

sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4429.68550926276, sim.hid$minus2loglik)))

## Be careful of initial values - some might not give global maximum of likelihood

hmodel3 <- list(hmmBinom(size=40, prob=0.1),
                hmmBinom(size=40, prob=0.5),
                hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))
stopifnot(all (sim.hid$hmodel$ci [c(2,4),1] <= c(0.1, 0.5)  &  sim.hid$hmodel$ci [c(2,4),2] >= c(0.1, 0.5)  ))


### POISSON RESPONSE

hmodel3 <- list(hmmPois(6), hmmPois(12), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
statetable.msm(state, subject, data=sim2.df) #  very few deaths from state 1 : parameter will be poorly estimated
hmodel3 <- list(hmmPois(9), hmmPois(9), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot(all (sim.hid$hmodel$ci [1:2,1] <= c(6, 12)  &  sim.hid$hmodel$ci [1:2,2] >= c(6, 12)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))

three.diff.q <- rbind(c(0, exp(-2), exp(-5)), c(0, 0, exp(-2)), c(0, 0, 0))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.diff.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(6, 12)  &  sim.hid$hmodel$ci [1:2,2] >= c(6, 12)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))



### NORMAL 

hmodel3 <- list(hmmNorm(6, 2), hmmNorm(12, 2), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
statetable.msm(state, subject, data=sim2.df) #  very few deaths from state 1 : parameter will be poorly estimated
hmodel3 <- list(hmmNorm(9, 1), hmmNorm(9, 1), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(6, 2)  &  sim.hid$hmodel$ci [1:2,2] >= c(6, 2)  ))
stopifnot (all (sim.hid$hmodel$ci [3:4,1] <= c(12, 2)  &  sim.hid$hmodel$ci [3:4,2] >= c(12, 2)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### LOG-NORMAL

hmodel3 <- list(hmmLNorm(log(6), log(2)), hmmLNorm(log(12), log(2)), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmLNorm(log(9), log(1.5)), hmmLNorm(log(9), log(1.5)), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= log(c(6, 2))  &  sim.hid$hmodel$ci [1:2,2] >= log(c(6, 2))  ))
stopifnot (all (sim.hid$hmodel$ci [3:4,1] <= log(c(12, 2))  &  sim.hid$hmodel$ci [3:4,2] >= log(c(12, 2))  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))



### EXPONENTIAL

hmodel3 <- list(hmmExp(6), hmmExp(12), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmExp(9), hmmExp(9), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(6, 12)  &  sim.hid$hmodel$ci [1:2,2] >= c(6, 12)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### GAMMA

hmodel3 <- list(hmmGamma(2, 6), hmmGamma(6, 18), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmGamma(4, 12), hmmGamma(4, 12), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(2, 6)  &  sim.hid$hmodel$ci [1:2,2] >= c(2, 6)  ))
stopifnot (all (sim.hid$hmodel$ci [3:4,1] <= c(6, 18)  &  sim.hid$hmodel$ci [3:4,2] >= c(6, 18)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### WEIBULL

hmodel3 <- list(hmmWeibull(2, 6), hmmWeibull(6, 18), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmWeibull(4, 12), hmmWeibull(4, 12), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(2, 6)  &  sim.hid$hmodel$ci [1:2,2] >= c(2, 6)  ))
stopifnot (all (sim.hid$hmodel$ci [3:4,1] <= c(6, 18)  &  sim.hid$hmodel$ci [3:4,2] >= c(6, 17.9)  )) # just outside CI
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))



### NEGATIVE BINOMIAL

hmodel3 <- list(hmmNBinom(10, 0.4), hmmNBinom(5, 0.3), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmNBinom(12, 0.6), hmmNBinom(7, 0.6), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(10, 0.4)  &  sim.hid$hmodel$ci [1:2,2] >= c(10,0.4)  ))
stopifnot (all (sim.hid$hmodel$ci [3:4,1] <= c(5, 0.3)  &  sim.hid$hmodel$ci [3:4,2] >= c(5, 0.3)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### BETA 

hmodel3 <- list(hmmBeta(0.6, 0.3), hmmBeta(0.3, 0.6), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmBeta(0.3, 0.6), hmmBeta(0.6, 0.3), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)


### TRUNCATED NORMAL
### Again watch out for dodgy local maxima

hmodel3 <- list(hmmTNorm(90, 3, 80, 100), hmmTNorm(65, 3, 50, 80), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)

hmodel3 <- list(hmmTNorm(87, 2, 80, 100), hmmTNorm(63, 10, 50, 80), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
print(sim.hid)

hmodel3 <- list(hmmTNorm(90, 5, 80, 100), hmmTNorm(65, 3, 50, 80), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(90, 3)  &  sim.hid$hmodel$ci [1:2,2] >= c(90, 3)  ))
stopifnot (all (sim.hid$hmodel$ci [5:6,1] <= c(65, 3)  &  sim.hid$hmodel$ci [5:6,2] >= c(65, 3)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### TRUNCATED NORMAL (Infinite bounds are allowed) 

hmodel3 <- list(hmmTNorm(85, 10, 80, Inf), hmmTNorm(65, 15, -Inf, 80), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmTNorm(95, 2, 80, Inf), hmmTNorm(55, 25, -Inf, 80), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [1:2,1] <= c(85, 10)  &  sim.hid$hmodel$ci [1:2,2] >= c(85, 10)  ))
stopifnot (all (sim.hid$hmodel$ci [5:6,1] <= c(65, 15)  &  sim.hid$hmodel$ci [5:6,2] >= c(62.9, 15)  )) # outside CI 
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### SATTEN AND LONGINI TRUNCATED NORMAL WITH MEASUREMENT ERROR 

hmodel3 <- list(hmmMETNorm(85, 10, 80, 100, 7), hmmMETNorm(65, 15, 50, 80, 7), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)

hmodel3 <- list(hmmMETNorm(95, 2, 80, 100, 4), hmmMETNorm(55, 25, 50, 80, 4), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
print(sim.hid) ## Local maximum

hmodel3 <- list(hmmMETNorm(85, 10, 80, 100, 7), hmmMETNorm(65, 15, 50, 80, 7), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
print(sim.hid) ## Global maximum, but model is not really identifiable from data 
print(viterbi.msm(sim.hid)[1:30,])

hmodel3 <- list(hmmMETNorm(85, 10, 80, Inf, 7), hmmMETNorm(65, 15, -Inf, 80, 7), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmMETNorm(95, 2, 80, Inf, 4), hmmMETNorm(55, 25, -Inf, 80, 4), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
print(sim.hid)
print(viterbi.msm(sim.hid)[1:30,])
## TODO  with bigger dataset.


### SATTEN AND LONGINI UNIFORM WITH MEASUREMENT ERROR 

hmodel3 <- list(hmmMEUnif(80, 100, 7), hmmMEUnif(50, 80, 13), hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmMEUnif(80, 100, 4), hmmMEUnif(50, 80, 4), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [c(3,7),1] <= c(7, 13)  &  sim.hid$hmodel$ci [c(3,7),2] >= c(7, 13)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### CATEGORICAL 

hmodel3 <- list(hmmCat(c(0.8, 0.2), basecat=2),
                hmmCat(c(0.9, 0.1), basecat=2),
                hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3)
hmodel3 <- list(hmmCat(c(0.5, 0.5), basecat=2),
                hmmCat(c(0.5, 0.5), basecat=2),
                hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [c(3,7),1] <= c(0.8, 0.9)  &  sim.hid$hmodel$ci [c(3,7),2] >= c(0.8, 0.9)  ))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### COVARIATES 
    
## Example with contrived 4-modal data, to ensure estimation of covariate effects works. 
three.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0)))
hmodel3 <- list(hmmNorm(6, 0.2), hmmNorm(12, 0.2), hmmIdent(999))
nsubj <- 100; nobspt <- 8
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt),
                     time = seq(0, 20, length=nobspt), 
                     x = rnorm(nsubj*nobspt),
                     y = sample(c(0,1), nsubj*nobspt, replace=TRUE)
                     )
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df, qmatrix=three.q, hmodel = hmodel3, hcovariates=list(c(y=2), c(y=2), NULL))
if (interactive()) plot(density(sim2.df$obs[sim2.df$obs < 999], adjust=1)) # 

hmodel3 <- list(hmmNorm(6, 0.2), hmmNorm(12, 0.2), hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q,
               hmodel=hmodel3, hcovariates = list (~y, ~y, NULL), hcovinits = list(c(0), c(0), NULL), 
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
print(sim.hid) # Doesn't converge, can't tell between state 1 and 2 

### Parameters are returned with covariates centered around their means.
### Model fitted using  x - xbar.     mu  =  mu0 + beta(x - xbar).    Estimate of mu presented as  mu0  =  mu + beta xbar.
### Would it be better to transform mu0 to mu0 - beta xbar =  mu ?  

### A less identifiable example. Still works. 

hmodel3 <- list(hmmNorm(6, 0.2), hmmNorm(12, 0.2), hmmIdent(999))
nsubj <- 250; nobspt <- 6
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), 
                     x = rnorm(nsubj*nobspt), y = rnorm(nsubj*nobspt)* 5 + 20)
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df, qmatrix=three.q, hmodel = hmodel3, hcovariates=list(c(x=0.4, y=-0.02), c(y=0.02), NULL))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q,
               hmodel=hmodel3, hcovariates = list (~x + y, ~y, NULL), 
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (sim.hid$hmodel$ci [c(1,2,3,4),1] <= c(6, 0.2, 12+1, 0.2)  &  sim.hid$hmodel$ci [c(1:4),2] >= c(6-1, 0.2, 12, 0.2)))
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))


### CONSTRAINTS ON HIDDEN PARS 

sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q,
               hmodel=hmodel3, hcovariates = list (~x + y, ~y, NULL),
               hconstraint=list(y = c(1,1), sd=c(1,1)), 
               method="BFGS", control=list(trace=3, REPORT=1), fixedpars=FALSE)
stopifnot (all (qmatrix.msm(sim.hid)$L <= three.q &  qmatrix.msm(sim.hid)$U >= three.q))
print(sim.hid) # OK but outside CIs. 



### FIXEDPARS



### INITPROBS 

hmodel3 <- list(hmmCat(c(0.8, 0.2), basecat=2),
                hmmCat(c(0.9, 0.1), basecat=2),
                hmmIdent(999))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, hmodel = hmodel3,
                        start=sample(1:3, nsubj, replace=TRUE, prob=c(0.2, 0.8, 0)))
hmodel3 <- list(hmmCat(c(0.5, 0.5), basecat=2),
                hmmCat(c(0.5, 0.5), basecat=2),
                hmmIdent(999))
sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               initprobs=c(0, 1, 0), method="BFGS", control=list(trace=3, REPORT=1), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(2210.70540132316, sim.hid$minus2loglik)))

sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               initprobs=c(1, 0, 0), method="BFGS", control=list(trace=3, REPORT=1), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(2363.51471971064, sim.hid$minus2loglik)))

sim.hid <- msm(obs ~ time, subject=subject, data=sim2.df, qmatrix=three.q, hmodel=hmodel3,
               initprobs=c(0.2, 0.8, 0), method="BFGS", control=list(trace=3, REPORT=1), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(2211.22289520440, sim.hid$minus2loglik)))


### OBSTYPE 

### CENSORING


}

cat("hsim.R: ALL TESTS PASSED\n")
