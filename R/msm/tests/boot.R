source("local.R")
library(msm)

if (developer.local) {
  data(psor)
  psor.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
  psor.msm <- msm(state ~ months, subject=ptnum, data=psor, qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn, constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)), fixedpars=FALSE, control = list(REPORT=1,trace=2), method="BFGS")
  
  set.seed(22061976)
  q.list <- boot.msm(psor.msm, function(x)x$Qmatrices$baseline, file="~/msm/devel/psor.q.boot.rda")
  ## new SEs, if more accurate, should be greater than asymp SE from Hessian.  OK. 
  apply(array(unlist(q.list), dim=c(4,4,5)), c(1,2), sd)
  apply(array(unlist(q.list), dim=c(4,4,5)), c(1,2), function(x)quantile(x, c(0.025, 0.975)))
  ## old SEs
  psor.msm$QmatricesSE$baseline

  ## Pmatrix CI utility function
  pmatrix.msm(psor.msm)
  (p.ci <- pmatrix.msm(psor.msm, ci.boot=TRUE, B=5))

  t.list <- boot.msm(psor.msm, totlos.msm, B=5)
  t.ci <- totlos.ci.msm(psor.msm, B=3)
  totlos.msm(psor.msm, ci.boot=TRUE, B=3)
  
  ## test on a HMM
  load(file="~/msm/devel/models/misc.msm.rda")
  pmatrix.msm(misc.msm, 1)
  oneway4.q <- rbind(c(0, 0.148, 0, 0.0171), c(0, 0, 0.202, 0.081), c(0, 0, 0, 0.126), c(0, 0, 0, 0))
  rownames(oneway4.q) <- colnames(oneway4.q) <- c("Well","Mild","Severe","Death")
  ematrix <- rbind(c(0, 0.1, 0, 0),c(0.1, 0, 0.1, 0),c(0, 0.1, 0, 0),c(0, 0, 0, 0))
  p.list <- boot.msm(misc.msm, function(x)pmatrix.msm(x, t=1), 3)

  ### models with censoring 
  cav.cens <- cav
  cav.cens$state[cav$state==4][1:50] <- 99
  twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
  cavcens.msm <- msm(state ~ years, subject=PTNUM, data=cav.cens, qmatrix=twoway4.q, censor=99, fixedpars=FALSE, control = list(REPORT=1,trace=2), method="BFGS")
  p.list <- boot.msm(cavcens.msm, B=3)
}



