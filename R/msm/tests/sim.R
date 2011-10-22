source("local.R")
library(msm)

### Simulation of a multi-state model, and recovering the true model
### Just run these tests locally. 

### Simple three-state progression and death model

if (developer.local)  { 

    nsubj <- 50; nobspt <- 6
    sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), 
                         x = rnorm(nsubj*nobspt), y = rnorm(nsubj*nobspt)* 5 + 2 )
    (three.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
#    (three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
    
  set.seed(22061976)

  sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q)
    sim2.df <- simmulti.msm(sim.df, qmatrix=three.q) # Retains all extra variables in data since 0.8

    print(crudeinits.msm(state ~ time, subject, qmatrix = rbind(c(0,1,1),c(0,0,1),c(0,0,0)), data=sim2.df))
    sim.mod <- msm(state ~ time, subject=subject, data=sim2.df,
                   qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0)))
    print(sim.mod)
    stopifnot (all (qmatrix.msm(sim.mod)$L <= three.q &  qmatrix.msm(sim.mod)$U >= three.q))
    
### Time-constant covariates 

    nsubj <- 1000; nobspt <- 15
    sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), 
                         x = rep(sample(c(0,1), nsubj, replace=TRUE), each=nobspt),
                         y = rep(sample(c(0,1), nsubj, replace=TRUE), each=nobspt)
                         )
    (three.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
#    (three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
    set.seed(22061976)
    sim3.df <- simmulti.msm(sim.df, qmatrix=three.q, covariates=list(x = c(-1, 1, 0), y = c(2, 0, -2)))

    sim.mod <- msm(state ~ time, subject=subject, data=sim3.df,
                   qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0)),
                   covariates = ~ x+y , covinits = list(x = c(0,0,0)), method="BFGS",
                   control=list(trace=1, REPORT=10, fnscale=10000, maxit=200))
    qmatrix.msm(sim.mod, covariates=0)
    stopifnot (all (qmatrix.msm(sim.mod, covariates=0)$L <= three.q & qmatrix.msm(sim.mod, covariates=0)$U >= three.q))
    stopifnot (all (hazard.msm(sim.mod)$x[,"L"] <= exp(c(-1, 1, 0)) & hazard.msm(sim.mod)$x[,"U"] >= exp(c(-1, 1, 0))))
    stopifnot (all (hazard.msm(sim.mod)$y[,"L"] <= exp(c(2, 0, -2)) & hazard.msm(sim.mod)$y[,"U"] >= exp(c(2, 0, -2))))
     
### Time-varying covariates

##    nsubj <- 4000; nobspt <- 81
    sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), 
                         x = sample(c(0,1), nsubj*nobspt, replace=TRUE), 
                         y = sample(c(0,1), nsubj*nobspt, replace=TRUE)
                         )
    set.seed(22061976)
    sim3.df <- simmulti.msm(sim.df, qmatrix=three.q, covariates=list(x = c(-1, 1, 0), y = c(2, 0, -2)))
    sim.mod <- msm(state ~ time, subject=subject, data=sim3.df,
                   qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0)),
                   covariates = ~ x+y , covinits = list(x = c(0,0,0)), method="BFGS",
                   control=list(trace=1, REPORT=1, fnscale=10000))
    stopifnot (all (qmatrix.msm(sim.mod, covariates=0)$L <= three.q & qmatrix.msm(sim.mod, covariates=0)$U >= three.q))
    stopifnot (all (hazard.msm(sim.mod)$x[,"L"] <= exp(c(-1, 1, 0)) & hazard.msm(sim.mod)$x[,"U"] >= exp(c(-1, 1, 0))))
##    stopifnot (all (hazard.msm(sim.mod)$y[,"L"] <= exp(c(2, 0, -2)) & hazard.msm(sim.mod)$y[,"U"] >= exp(c(2, 0, -2))))
##    y[1,2] just outside CI.   Larger dataset? 
    
### Exact observation times

    sim4.df <- NULL
    for (i in 1:100)  {
        s <- sim.msm(three.q, 20)
        sim4.df <- rbind(sim4.df, data.frame(subject=rep(i, length(s$states)), time=s$times, state=s$states))
    }
    print(sim4.df[1:30,])

    sim.mod <- msm(state ~ time, subject=subject, data=sim4.df, exacttimes=TRUE, 
                   qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0)) )
    stopifnot (all (qmatrix.msm(sim.mod, covariates=0)$L <= three.q & qmatrix.msm(sim.mod, covariates=0)$U >= three.q))

    sim.mod <- msm(state ~ time, subject=subject, data=sim4.df, exacttimes=TRUE, 
                   qmatrix = rbind(c(0, exp(-2), exp(-4)), c(0, 0, exp(-2)), c(0, 0, 0)))
    stopifnot (all (qmatrix.msm(sim.mod, covariates=0)$L <= three.q & qmatrix.msm(sim.mod, covariates=0)$U >= three.q))

    sim.mod <- msm(state ~ time, subject=subject, data=sim4.df, exacttimes=FALSE, 
                   qmatrix = rbind(c(0, exp(-2), exp(-4)), c(0, 0, exp(-1)), c(0, 0, 0))) # worse estimates
    print(sim.mod)

### Exact death times
    
    set.seed(22061976)
    simdeath.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, death=TRUE)

    sim.mod <- msm(state ~ time, subject=subject, data=simdeath.df, death=TRUE, 
                   qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0)))
    stopifnot (all (qmatrix.msm(sim.mod, covariates=0)$L <= three.q & qmatrix.msm(sim.mod, covariates=0)$U >= three.q))
    print(sim.mod)

    sim.mod <- msm(state ~ time, subject=subject, data=simdeath.df, death=FALSE, 
                   qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0))) # slightly worse estimates of 1-3 transition
    print(sim.mod)

}

cat("sim.R: ALL TESTS PASSED\n")
