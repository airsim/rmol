source("local.R")
library(msm)

### SIMULATIONS TO TEST ANALYTIC P MATRICES

if (developer.local) { 

nsubj <- 50; nobspt <- 6
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), x = rnorm(nsubj*nobspt), y = rnorm(nsubj*nobspt)* 5 + 2 )
set.seed(22061976)

## 2 STATES
## 1
(two.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-2)), c(0, 0))))
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=two.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-3)), c(0, 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-3)), c(0, 0)), analyticp=FALSE))

## 1,2
(two.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-2)), c(exp(-2), 0))))
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=two.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-3)), c(exp(-1), 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-3)), c(exp(-1), 0)), analyticp=FALSE))

## 3 STATES
## 1,2 
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-3)), c(0, 0, 0), c(0, 0, 0))))
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-1)), c(0, 0, 0), c(0, 0, 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-1)), c(0, 0, 0), c(0, 0, 0)), analyticp=FALSE))

## 1,4
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), 0), c(0, 0, exp(-3)), c(0, 0, 0))))
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0), c(0, 0, exp(-1)), c(0, 0, 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0), c(0, 0, exp(-1)), c(0, 0, 0)), analyticp=FALSE))

# 4,5 (== 1,4)
nsubj <- 500; nobspt <- 6
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), 
                     x = rnorm(nsubj*nobspt), y = rnorm(nsubj*nobspt)* 5 + 2 )
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, 0, 0), c(0, 0, exp(-2)), c(exp(-3), 0, 0))))
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, start=rep(2,500))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, 0, 0), c(0, 0, exp(-3)), c(exp(-2), 0, 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, 0, 0), c(0, 0, exp(-3)), c(exp(-2), 0, 0)), analyticp=FALSE))

## 1,6
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), 0), c(0, 0, 0), c(0, exp(-3), 0))))
nsubj <- 50; nobspt <- 6
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), x = rnorm(nsubj*nobspt), y = rnorm(nsubj*nobspt)* 5 + 2 )
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, start=c(rep(3,25),rep(1,25)))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0), c(0, 0, 0), c(0, exp(-1), 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0), c(0, 0, 0), c(0, exp(-1), 0)), analyticp=FALSE))

#1,2,4 (= 3,4,5)
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, 0, 0), c(exp(-3), 0, exp(-3)), c(exp(-3), 0, 0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, start=rep(2, 50))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, 0, 0), c(exp(-2), 0, exp(-2)), c(2*exp(-2), 0, 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, 0, 0), c(exp(-2), 0, exp(-2)), c(2*exp(-2), 0, 0)), analyticp=FALSE))

# 1,2,4
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, exp(-1)), c(0, 0, 0)), analyticp=FALSE))

# 1,2,4 (=1,2,6)
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, 0), c(0, exp(-3), 0))))
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, 0), c(0, exp(-2), 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-2)), c(0, 0, 0), c(0, exp(-2), 0)), analyticp=FALSE))

#1,3,5  (= 2,4,5)
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, 0, exp(-3)), c(0, 0, exp(-3)), c(exp(-3), 0, 0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, start=c(rep(1, 25), rep(2,25)))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, 0, exp(-1)), c(0, 0, exp(-1)), c(exp(-2), 0, 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, 0, exp(-1)), c(0, 0, exp(-1)), c(exp(-2), 0, 0)), analyticp=FALSE))

#1,2,4,6
(three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-3)), c(0, 0, exp(-3)), c(0, exp(-3), 0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, start=c(rep(1, 25), rep(2,25)))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-1)), c(0, 0, exp(-1)), c(0, exp(-2), 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-1)), c(0, 0, exp(-1)), c(0, exp(-2), 0)), analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-1)), c(0, 0, exp(-1)), c(0, exp(-1), 0)), analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), exp(-1)), c(0, 0, exp(-1)), c(0, exp(-1), 0)), analyticp=FALSE))

## FOUR STATES
#1,5,9
(four.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), 0, 0), c(0, 0, exp(-3), 0), c(0, 0, 0, exp(-3)), c(0,0,0,0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=four.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-1)), c(0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-1)), c(0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-2)), c(0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-2)), c(0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0, 0), c(0, 0, exp(-2), 0), c(0, 0, 0, exp(-1)), c(0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-1), 0, 0), c(0, 0, exp(-2), 0), c(0, 0, 0, exp(-1)), c(0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-1)), c(0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-1)), c(0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-3)), c(0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, 0), c(0, 0, exp(-1), 0), c(0, 0, 0, exp(-3)), c(0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

#13569
(four.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), 0, exp(-3)), c(0, 0, exp(-3), exp(-3)), c(0, 0, 0, exp(-3)), c(0,0,0,0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=four.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-2), exp(-2)), c(0, 0, 0, 2*exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-2), exp(-2)), c(0, 0, 0, 2*exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-2), exp(-2)), c(0, 0, 0, exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-2), exp(-2)), c(0, 0, 0, exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-3), exp(-3)), c(0, 0, 0, 2*exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-3), exp(-3)), c(0, 0, 0, 2*exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-3), 0, exp(-3)), c(0, 0, exp(-2), exp(-2)), c(0, 0, 0, 2*exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-3), 0, exp(-3)), c(0, 0, exp(-2), exp(-2)), c(0, 0, 0, 2*exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-3), exp(-3)), c(0, 0, 0, exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0, exp(-2), 0, exp(-2)), c(0, 0, exp(-3), exp(-3)), c(0, 0, 0, exp(-2)), c(0,0,0,0)), fixedpars=FALSE, analyticp=FALSE))


## FIVE STATES
#1_6_11_16
(five.q <- msm.fixdiag.qmatrix(rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=five.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-4),0), c(0,0,0,0,exp(-5)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-4),0), c(0,0,0,0,exp(-5)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-3),0), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-3),0), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-4),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-4),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-4),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-4),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-4),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-4),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-3)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-3)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-3),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-3),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),0,0), c(0,0,0,exp(-2),0), c(0,0,0,0,exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

#1_4_6_8_11_12_16
(five.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,exp(-2)), c(0,0,0,0,0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=five.q)
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,exp(-5)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,exp(-5)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-3),exp(-3)), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-3),exp(-3)), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,exp(-4)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-4),0,exp(-4)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-4),0,exp(-4)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,exp(-3)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,exp(-3)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-3),exp(-3)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-3),exp(-3)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-3),0,exp(-3)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,exp(-3)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,exp(-2)), c(0,0,exp(-2),0,exp(-2)), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,2*exp(-2)), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

#1_6_7_11_12
(five.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),exp(-2),0), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,0), c(0,0,0,0,0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=five.q)

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),exp(-3),0), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-3),exp(-3),0), c(0,0,0,exp(-4),exp(-4)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,2*exp(-2),0,0,0), c(0,0,exp(-2),exp(-2),0), c(0,0,0,exp(-3),exp(-3)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,2*exp(-2),0,0,0), c(0,0,exp(-2),exp(-2),0), c(0,0,0,exp(-3),exp(-3)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,2*exp(-2),0,0,0), c(0,0,exp(-3),exp(-3),0), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,2*exp(-2),0,0,0), c(0,0,exp(-3),exp(-3),0), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),exp(-2),0), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-3),0,0,0), c(0,0,exp(-2),exp(-2),0), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))

(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),exp(-2),0), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=TRUE))
(sim.mod <- msm(state ~ time, subject=subject, data=sim2.df, qmatrix = rbind(c(0,exp(-2),0,0,0), c(0,0,exp(-2),exp(-2),0), c(0,0,0,exp(-2),exp(-2)), c(0,0,0,0,0), c(0,0,0,0,0)), fixedpars=TRUE, analyticp=FALSE))


### APPLICATIONS 
## one-way cav misc
## Takes 34% of the time using new method. 
oneway4.q <- rbind(c(0, 0.148, 0, 0.0171), c(0, 0, 0.202, 0.081), c(0, 0, 0, 0.126), c(0, 0, 0, 0))
rownames(oneway4.q) <- colnames(oneway4.q) <- c("Well","Mild","Severe","Death")
ematrix <- rbind(c(0, 0.1, 0, 0),c(0.1, 0, 0.1, 0),c(0, 0.1, 0, 0),c(0, 0, 0, 0))
system.time(misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=FALSE, analyticp=FALSE,
                control = list(trace=1, REPORT=1), method="BFGS"))
misc.msm
system.time(misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=FALSE, analyticp=TRUE,
                control = list(trace=1, REPORT=1), method="BFGS"))
misc.msm

## psoriatic
## half of the time using new method
psor <- read.table("../data/psor.txt", header=TRUE)
psor.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
system.time(psor.msm <- msm(state ~ months, subject=ptnum, data=psor,
                            qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                            constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)),
                            fixedpars=FALSE, control = list(REPORT=1,trace=2), method="BFGS",analyticp=FALSE))
system.time(psor.msm <- msm(state ~ months, subject=ptnum, data=psor,
                            qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                            constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)),
                            fixedpars=FALSE, control = list(REPORT=1,trace=2), method="BFGS",analyticp=TRUE))


## Jean-Luc
c2.df <- read.table("~/msm/tests/jeanluc/donneesaveccancerPT.txt", header=TRUE)
qx <- rbind( c(0, 0.005, 0, 0, 0), c(0, 0, 0.01, 0.02,0), c(0, 0, 0, 0.04, 0.03), c(0, 0, 0, 0, 0), c(0, 0, 0, 0, 0))
system.time(c2.msm <- msm(state~years, subject=PTNUM, data=c2.df,
              qmatrix=qx, death=c(4, 5), method="BFGS", # fixedpars = 1:5, 
              control=list(trace=2, REPORT=1, fnscale=100000)))
c2.msm
system.time(c2.msm <- msm(state~years, subject=PTNUM, data=c2.df, analyticp=FALSE,
              qmatrix=qx, death=c(4, 5), method="BFGS", # fixedpars = 1:5, 
              control=list(trace=2, REPORT=1, fnscale=100000)))
c2.msm

}
