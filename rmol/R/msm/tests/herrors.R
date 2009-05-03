source("local.R")
library(msm)
data(fev)

### TESTS OF ERROR HANDLING FOR HMMs.

three.q <- rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))
four.q <-  rbind(c(0, exp(-3), 0, exp(-6)), c(0, 0, exp(-3.01), exp(-6)), c(0, 0, 0, exp(-3.02)), c(0, 0, 0, 0))
five.q <-  rbind(c(0, exp(-3), 0, 0, exp(-6)),
                 c(0, 0, exp(-3.01), 0, exp(-6)),
                 c(0, 0, 0, exp(-3.02), exp(-3.03)),
                 c(0, 0, 0, 0, exp(-3.04)),
                 c(0, 0, 0, 0, 0))

hmodel3 <- list(hmmMETNorm(mean=100, sd=16, sderr=8, lower=80, upper=Inf, meanerr=0),
                hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                hmmIdent(999))
hmodel4 <- list(hmmMETNorm(mean=100, sd=16, sderr=8, lower=80, upper=Inf, meanerr=0),
                hmmMEUnif(sderr=8, lower=65, upper=80, meanerr=0),
                hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=65, meanerr=0),
                hmmIdent(999))
hmodel5 <- list(hmmMETNorm(mean=100, sd=16, sderr=8, lower=80, upper=Inf, meanerr=0),
                hmmMEUnif(sderr=8, lower=65, upper=80, meanerr=0),
                hmmMEUnif(sderr=8, lower=50, upper=65, meanerr=0),
                hmmMETNorm(mean=42, sd=18, sderr=8, lower=0, upper=50, meanerr=0),
                hmmIdent(999))

## hmodel with wrong named parameters
try(
    hmodel3 <- list(hmmMETNorm(mean=100, sd=16, splat=8, lower=80, upper=Inf, meanerr=0),
                    hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                    hmmIdent(999))
    )
## hmodel with extra unnamed parameter
try(
hmodel3 <- list(hmmMETNorm(mean=100, sd=16, sderr=8, lower=80, upper=Inf, meanerr=0),
                hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                hmmIdent(999, 3))
    )
## hmodel with parameters unnamed, but correct number - OK. 
hmodel.OK <- list(hmmMETNorm(100, 16, 8, 80, Inf, 0),
                  hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                  hmmIdent(999))
## hmodel with too few parameters (named or unnamed) 
try(
hmodel3 <- list(hmmMETNorm(100, 16, 80, Inf),
                hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                hmmIdent(999))
    )

### Initial values for certain parameters in wrong ranges. 
try(
hmodel3 <- list(hmmMETNorm(mean=100, sd=-16, sderr=8, lower=80, upper=Inf, meanerr=0),
                hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                hmmIdent(999))
    )
try(
hmodel3 <- list(hmmMETNorm(mean=100, sd=16, sderr="splat", lower=80, upper=Inf, meanerr=0),
                hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                hmmIdent(999))
    )
try(
hmodel3 <- list(
                hmmBinom(size=0.1, prob=0.5),
                hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent())
    )

### Wrong number of states in the hmodel, versus the qmatrix. 
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel4, fixedpars=1:9))
### Rubbish in hmodel list
hmodel.rubbish <- list("should be a ", " list of ", "hmodel objects")
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel.rubbish, fixedpars=1:9))
## Death state wrong (not HMM-specific error, but no harm putting it in this file anyway) 
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=10, hmodel=hmodel3, fixedpars=1:9))

## Covariate list of wrong length
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~acute), hcovinits = list(-8, -8, NULL),))

## Covariate list has rubbish in it 
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list("should be formulae", "rubbish", NULL), hcovinits = list(-8, -8, NULL)))

## Covariates not in the data 
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~nonexistent, NULL), hcovinits = list(-8, -8, NULL)))

## Covariate inits of wrong length (just warning, ignores)
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, -8), fixedpars=TRUE))

## Rubbish in hcovinits (just warning, ignores)
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~acute, NULL), hcovinits = list("fooo", -8, NULL), fixedpars=TRUE))

## hconstraint has unknown parameters 
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                    hconstraint = list(nonexistent = c(1,1), acute = c(1,1))))

## hconstraint has rubbish in (note character vectors are allowed)
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                    hconstraint = list("rubbish", acute = c(1,1))))
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                    hconstraint = list(sderr=c("wrong length"), acute = c(1,1))))

### can we think of any more errors?

### what about for misc models? put in different file. 

if (0) {
try(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                    hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                    hconstraint = list(sderr = c(1,1), acute = c(1,1)), 
                    method="BFGS", control=list(trace=3, REPORT=1, reltol=1e-16, ndeps=rep(1e-06, 9)), 
                    fixedpars=FALSE))

}

cat("herrors.R: ALL TESTS PASSED\n")
