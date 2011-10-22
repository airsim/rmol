### TESTS OF ERROR CHECKING
source("local.R")
print(developer.local)
library(msm)
data(cav)

twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
oneway4.q <- rbind(c(0, 0.148, 0, 0.0171), c(0, 0, 0.202, 0.081), c(0, 0, 0, 0.126), c(0, 0, 0, 0))
rownames(twoway4.q) <- colnames(twoway4.q) <- c("Well","Mild","Severe","Death")
rownames(oneway4.q) <- colnames(oneway4.q) <- c("Well","Mild","Severe","Death")
oneway4.i <- oneway4.q; oneway4.i[oneway4.i!=0] <- 1
ematrix <- rbind(c(0, 0.1, 0, 0),c(0.1, 0, 0.1, 0),c(0, 0.1, 0, 0),c(0, 0, 0, 0))

### Rubbish in formula 

try(cav.msm <- msm(state, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE))
try(cav.msm <- msm(~1, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE))
try(cav.msm <- msm("foo", subject=PTNUM, data = cav, qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE))

### Rubbish in qmatrix 
wrong.q <- cbind(c(0,1,2), c(0,1,2))
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = wrong.q, death = TRUE, fixedpars=TRUE))
wrong.q <- cbind(c(0,1), c(0,1))
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = wrong.q, death = TRUE, fixedpars=TRUE))
wrong.q <- "foo"
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = wrong.q, death = TRUE, fixedpars=TRUE))
wrong.q <- 1
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = wrong.q, death = TRUE, fixedpars=TRUE))

### Rubbish in ematrix 
wrong.e <- "foo"
try(misc.msm <- msm(state ~ years, subject = PTNUM, data = cav, qmatrix = oneway4.q, ematrix=wrong.e, death = 4, fixedpars=TRUE))
wrong.e <- 1
try(misc.msm <- msm(state ~ years, subject = PTNUM, data = cav, qmatrix = oneway4.q, ematrix=wrong.e, death = 4, fixedpars=TRUE))
wrong.e <- cbind(c(0,1,2), c(0,1,2))
try(misc.msm <- msm(state ~ years, subject = PTNUM, data = cav, qmatrix = oneway4.q, ematrix=wrong.e, death = 4, fixedpars=TRUE))
wrong.e <- cbind(c(0,1), c(0,2))
try(misc.msm <- msm(state ~ years, subject = PTNUM, data = cav, qmatrix = oneway4.q, ematrix=wrong.e, death = 4, fixedpars=TRUE))

### Rubbish in subject
try(cav.msm <- msm(state~years, subject="foo", data = cav, qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE))
try(cav.msm <- msm(state~years, subject=foo, data = cav, qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE))

### Rubbish in obstype 
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = twoway4.q, obstype="foo", death = TRUE, fixedpars=TRUE))
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = twoway4.q, obstype=rep(1,10), death = TRUE, fixedpars=TRUE))
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = twoway4.q, obstype=rep(4, nrow(cav)), death = TRUE, fixedpars=TRUE))

### covariates not in data
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = "wibble"))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sux))

### misccovariates not in data
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, fixedpars=TRUE, misccovariates = "wobble"))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sox))

### covinits not in data, wrong length, rubbish 
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, covinits="foo", fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, covinits=list(sex="foo", age="bar"), fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, covinits=list(sex=c(1,2,3), age="bar"), fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, covinits=list(age=rep(0.1, 7)), fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, covinits=list(age=rep(0.1, 7), foo=1, bar=2), fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, covinits=list(sex=1), fixedpars=TRUE))
### misccovinits not in data, wrong length, rubbish 
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, misccovariates = ~ sex, misccovinits="foo", fixedpars=TRUE))
if (developer.local) { 
    try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, misccovinits=list(sex="foo", age="bar"), fixedpars=TRUE)) # covariates but misccovinits,  no error
    cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, misccovariates = ~ sex, misccovinits=list(sex="foo", age="bar"), fixedpars=TRUE)
}
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, misccovariates = ~ sex, misccovinits=list(sex=1, age="bar"), fixedpars=TRUE))
## misccovs specified but misc false 
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, misccovariates = ~ sex, misccovinits=list(sex=1, age="bar"), fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, ematrix=ematrix, misccovariates = ~ sex, misccovinits=list(sex=1, age="bar"), fixedpars=TRUE))

### constraint not in data, wrong length, rubbish 
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, constraint="foo"))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, constraint=list(foo="bar")))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, constraint=list(foo=1)))

### miscconstraint
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, misccovariates = ~ sex, constraint="foo", fixedpars=TRUE)) # constraint but no covs 
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, misccovariates = ~ sex, miscconstraint=list(foo="bar")))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, misccovariates = ~ sex, miscconstraint=list(foo=1)))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, misccovariates = ~ sex, miscconstraint=list(sex=1)))

### initprobs
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, initprobs="poo", fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, initprobs=c(1,2), fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, initprobs=c(2,1,1,1), fixedpars=TRUE)) # correct - scaled to sum to 1.

### qconstraint
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, qconstraint="foo", fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, qconstraint=list(c(1,1,2)), fixedpars=TRUE))
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, qconstraint=c(1,1,2), fixedpars=TRUE))

### econstraint
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, econstraint="foo", fixedpars=TRUE) )
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, econstraint=list(c(1,1,2)), fixedpars=TRUE) )
try(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, econstraint=c(1,1,2), fixedpars=TRUE))

### States in data not in state set specified with qmatrix 
wrong.q <- cbind(c(0,1), c(0,1)) # extra states in data 
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = wrong.q, fixedpars=TRUE))
wrong.q <- rbind(c(0,1,2,3,1), c(0,1,3,4,1), c(0,1,2,3,2), c(0,1,2,3,4), c(0,0,0,0,0))
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = wrong.q, fixedpars=TRUE)) # too few states in data, warning only 
wrong.q <- rbind(c(0,1,2,3,1,0), c(0,1,3,4,1,0), c(0,1,2,3,2,0), c(0,1,2,3,4,0), c(0,0,0,0,0,0), c(0,0,0,0,0,0))
try(cav.msm <- msm(state~years, subject=PTNUM, data = cav, qmatrix = wrong.q, fixedpars=TRUE))

### Observations not increasing with time
cav.wrong <- cav
cav.wrong$years[3:5] <- 4:2
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.wrong, qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE))

### Observations from a subject not all adjacent
cav.wrong <- cav
cav.wrong$PTNUM[4:5] <- 100003
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.wrong, qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE))

### Data inconsistent with P matrix (snapshot) 
cav.wrong <- cav
cav.wrong$state[4] <- 1
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.wrong, qmatrix = oneway4.q, death = TRUE, fixedpars=TRUE))
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.i, gen.inits=TRUE, fixedpars=TRUE))

cav.cens <- cav
cav.cens$state[cav$state==4][1:50] <- 99
### censored states inconsistent (currently gives Inf) 
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.cens, qmatrix = oneway4.q, censor=99, censor.states=list(c(1,2)), fixedpars=TRUE))
cav.msm
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.cens, qmatrix = oneway4.q, censor=99, censor.states=list(c(1,2,3)), fixedpars=TRUE))
cav.msm
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.cens, qmatrix = oneway4.q, censor=99, censor.states=list(c(1,2)), exacttimes=TRUE, fixedpars=TRUE))
cav.msm

### Data inconsistent with Q matrix (exacttimes) 
cav.wrong <- cav
cav.wrong$state[4] <- 1
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.wrong, qmatrix = twoway4.q, exacttimes=TRUE, fixedpars=TRUE))
obstype <- rep(2, nrow(cav))
obstype[10] <- 1
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.wrong, qmatrix = twoway4.q, obstype=obstype, fixedpars=TRUE))
cav.msm

### rubbish in death
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = "foo", fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = 5, fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = 1:5, fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = 3, fixedpars=TRUE) ) # non-absorbing death state

### rubbish in censor 
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, censor="rubbish", fixedpars=TRUE))
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, censor=1, fixedpars=TRUE)) # warning, censor=actual state
# cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, censor=1, fixedpars=FALSE, method="BFGS", control=list(trace=5, REPORT=1)) # works but extreme estimates 
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, censor.states="rubbish", fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.cens, qmatrix = twoway4.q, censor=99, censor.states="rubbish", fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.cens, qmatrix = twoway4.q, censor=99, censor.states=list(c(1,2,3), "rubbish"), fixedpars=TRUE) )

### obstype
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, obstype="rubbish", fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, obstype=c(1,2,3), fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, obstype=4, fixedpars=TRUE) )
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, obstype=rep(4,nrow(cav)), fixedpars=TRUE) )

### fixedpars
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, fixedpars="foo"))
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, fixedpars=list(c(1,3,4))))
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, fixedpars=1:8))
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, fixedpars=0.5))

### crudeinits
cav.wrong <- cav
cav.wrong$state[4] <- 1
crudeinits.msm(state ~ years, PTNUM, twoway4.q, cav.wrong) # no error. ignores inconsistent transitions 
crudeinits.msm(state ~ years, PTNUM, oneway4.q, cav) # no error. ignores inconsistent transitions 
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.wrong, qmatrix = twoway4.q, exacttimes=TRUE, fixedpars=TRUE))
obstype <- rep(2, nrow(cav))
obstype[10] <- 1
try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav.wrong, qmatrix = twoway4.q, obstype=obstype, fixedpars=TRUE))
cav.msm


#### OUTPUTS #####

try(cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, fixedpars=TRUE))
try(cavfit.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q))
try(cavcov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ sex, covinits=list(sex=rep(0.1,7)), fixedpars=TRUE))
try(cavmisc.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, fixedpars=TRUE))
try(cavmisccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = oneway4.q, ematrix=ematrix, misccovariates = ~ sex, misccovinits=list(sex=rep(0.1,4)), fixedpars=TRUE))

### qematrix 
try(qmatrix.msm("foo"))
try(qmatrix.msm(cav.msm))
try(qmatrix.msm(cav.msm, covariates="foo"))
try(qmatrix.msm(cav.msm, covariates=list(foo=1)))
try(qmatrix.msm(cavcov.msm, covariates=list(foo=1)))

### ematrix 
try(ematrix.msm("Foo"))
try(ematrix.msm(cav.msm)) # not a misc model, returns NULL.
try(ematrix.msm(cavmisc.msm, covariates="foo"))
try(ematrix.msm(cavmisc.msm, covariates=list(foo=1)))
try(ematrix.msm(cavmisccov.msm, covariates=list(foo=1)))

### sojourn
try(sojourn.msm("foo"))
try(sojourn.msm(cav.msm, covariates="foo"))
try(sojourn.msm(cav.msm, covariates=list(foo=1)))

### pmatrix
try(pmatrix.msm("foo"))
try(pmatrix.msm(cav.msm, t="foo"))
try(pmatrix.msm(cav.msm, -9))
try(pmatrix.msm(cav.msm, 0))
try(pmatrix.msm(cav.msm, 1, covariates=list(foo=1)))

### pmatrix.piecewise
try(pmatrix.piecewise.msm("foo", 1,2, c(1, 2), c(1,2)))
try(pmatrix.piecewise.msm("foo", 1, 2, c(1, 0.5, 2), list(0, 1, 0, 1)))
try(pmatrix.piecewise.msm(cav.msm, 1, 2, c(1, 0.5, 2), list(0, 1, 0, 1)))
try(pmatrix.piecewise.msm(cav.msm, 1, 2, "rubbish", list(0, 1, 0, 1)))
try(pmatrix.piecewise.msm(cavcov.msm, 1, 2, c(1, 1.5, 2), "rubbish"))
try(pmatrix.piecewise.msm(cavcov.msm, 1, 2, c(1, 1.5, 2), list("rubbish", "foo","bar","boing")))
try(pmatrix.piecewise.msm(cavcov.msm, 1, 2, c(1, 1.5, 2), list(0, 1, 0, 1)))
pmatrix.piecewise.msm(cavcov.msm, 1, 2, c(1, 1.5, 2), list(list(0), list(1), list(0), list(1))) # OK
pmatrix.msm(cavcov.msm, 1) # OK

### qratio
try(qratio.msm("foo"))
try(qratio.msm(cav.msm, "foo"))
try(qratio.msm(cav.msm, c(1,8), c(1,0)))
try(qratio.msm(cav.msm, c(1,2), c(1,0)))
qratio.msm(cav.msm, c(1,2), c(2,3)) # OK
qratio.msm(cavfit.msm, c(1,2), c(2,3)) # OK 
try(qratio.msm(cavfit.msm, c(1,2), c(2,3), cl="foo"))
try(qratio.msm(cavfit.msm, c(1,2), c(2,3), cl=2))

### summary, prevalence, observed
try(prevalence.msm("foo"))
try(summary.msm("foo"))

### plot
if (interactive()) { 
    try(plot.msm("foo"))
    try(plot.msm(cav.msm, from="foo"))
    try(plot.msm(cav.msm, to="foo"))
    try(plot.msm(cav.msm, from = 1:8, to=3))
    try(plot.msm(cav.msm, to = 3))
    try(plot.msm(cav.msm, range="foo"))
    try(plot.msm(cav.msm, range=1:6))
    try(plot.msm(cav.msm))
    try(plot.msm(cavfit.msm))
}

### coef, hazard, odds
try(coef.msm("foo"))
try(hazard.msm("foo"))
try(hazard.msm(cavcov.msm, hazard.scale="foo"))
try(hazard.msm(cavcov.msm))
try(hazard.msm(cavcov.msm, hazard.scale=c(1,2,3,4)))
try(hazard.msm(cavcov.msm, hazard.scale=c(1,2,3)))
try(hazard.msm(cavcov.msm, hazard.scale=2))

try(odds.msm("foo"))
try(odds.msm(cavcov.msm, odds.scale="foo"))
try(odds.msm(cavmisccov.msm, odds.scale="foo"))
odds.msm(cavmisccov.msm) # OK
try(odds.msm(cavmisccov.msm, odds.scale=c(1,2,3,4)))
try(odds.msm(cavmisccov.msm, odds.scale=c(1,2,3)))
odds.msm(cavmisccov.msm, odds.scale=2) # OK 

### transient, absorbing
try(transient.msm("foo"))
try(absorbing.msm("foo"))
try(transient.msm(qmatrix="foo"))
try(absorbing.msm(qmatrix="foo"))
try(transient.msm(qmatrix=c(1,4,5,6)))
try(absorbing.msm(qmatrix=c(1,4,5,6)))
try(transient.msm(qmatrix=cbind(c(1,2,3),c(1,3,2))))
try(absorbing.msm(qmatrix=cbind(c(1,2,3),c(1,3,2))))
try(transient.msm())
try(absorbing.msm())

### totlos
try(totlos.msm("foo"))
try(totlos.msm(cav.msm, start="foo"))
try(totlos.msm(cav.msm, start=-1))
try(totlos.msm(cav.msm, start=1, fromt=1, tot=0))
try(totlos.msm(cav.msm, start=1, fromt=c(1,2), tot=c(3,4)))
try(totlos.msm(cav.msm, start=1, fromt="foo", tot=2))
try(totlos.msm(cav.msm, start=1, fromt=-3, tot=-2))
totlos.msm(cav.msm, start=1, fromt=1, tot=2) # OK

### logLik
try(logLik.msm("foo"))
logLik.msm(cav.msm)

### viterbi
try(viterbi.msm("foo"))

cat("errors.R: ALL TESTS PASSED\n")
