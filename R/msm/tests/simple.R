source("local.R")
library(msm)
#library(msm, lib.loc="~/lib/R")
#library(msm, lib.loc="~/msm/lib/sun/0.7.5")
data(cav)

### TESTS FOR SIMPLE NON-HIDDEN MARKOV MODELS

twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
twoway4.q2 <- rbind(c(-0.51, 0.24, 0, 0.25), c(0.162, -0.498, 0.168, 0.166), c(0, 0.26, -0.5, 0.25), c(0, 0, 0, 0))
twoway3.q <- rbind(c(-0.5, 0.25, 0), c(0.166, -0.498, 0.166), c(0, 0.25, -0.5))
oneway4.q <- rbind(c(0, 0.148, 0, 0.0171), c(0, 0, 0.202, 0.081), c(0, 0, 0, 0.126), c(0, 0, 0, 0))
rownames(twoway4.q) <- colnames(twoway4.q) <- c("Well","Mild","Severe","Death")
rownames(oneway4.q) <- colnames(oneway4.q) <- c("Well","Mild","Severe","Death")
twoway4.i <- twoway4.q; twoway4.i[twoway4.i!=0] <- 1
oneway4.i <- oneway4.q; oneway4.i[oneway4.i!=0] <- 1

### CAV DATA
(stab <- statetable.msm(state, PTNUM, data=cav))
stopifnot(all(stab == c(1367, 46, 4, 204, 134, 13, 44, 54, 107, 148, 48, 55)))
(cinits <- crudeinits.msm(state ~ years, PTNUM, data=cav, qmatrix=twoway4.q))
stopifnot(isTRUE(all.equal(c(-0.117314905786477, 0.116817878212849, 0, 0, 0.067989320398981, -0.375848825554382, 0.049084006577444, 0, 0, 0.137134030945518, -0.256747111328168, 0, 0.049325585387496, 0.121896916396016, 0.207663104750724, 0), as.numeric(cinits))))

## Simple model
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE,
                 method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4908.81676837903, cav.msm$minus2loglik, tol=1e-06)))
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = cinits, death = TRUE, fixedpars=TRUE,
                 method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4113.16601901957, cav.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE,
                                 method="BFGS", control=list(trace=5, REPORT=1, fnscale=1)) )
    stopifnot(isTRUE(all.equal(3968.7978930519, cav.msm$minus2loglik, tol=1e-06)))
}

## No death state.
system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = FALSE, fixedpars=FALSE,
                 method="BFGS", control=list(trace=1, REPORT=1, fnscale=4000)) )
stopifnot(isTRUE(all.equal(3986.08765893935, cav.msm$minus2loglik, tol=1e-06)))
cav.msm

## auto-generated initial values.
state.g <- cav$state; time.g <- cav$years; subj.g <- cav$PTNUM
cav.msm <- msm(state.g ~ time.g, subject=subj.g, qmatrix = twoway4.i, gen.inits=TRUE, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4119.9736299032, cav.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(cav.msm <- msm(state.g ~ time.g, subject=subj.g, qmatrix = twoway4.i, gen.inits=TRUE, fixedpars=TRUE))
    stopifnot(isTRUE(all.equal(4119.9736299032, cav.msm$minus2loglik, tol=1e-06)))
    cav.msm <- msm(state.g ~ time.g, subject=subj.g, qmatrix = crudeinits.msm(state ~ years, PTNUM, twoway4.i, data=cav), fixedpars=TRUE)
    stopifnot(isTRUE(all.equal(4119.9736299032, cav.msm$minus2loglik, tol=1e-06)))
}

## Covariates

cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE,
                 covariates = ~ sex, covinits = list(sex=rep(0.01, 7)), # , dage=rep(0, 7)),
                 method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4909.08442586298, cav.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE,
                                 covariates = ~ sex, method="BFGS", control=list(trace=5, REPORT=1))) # 44.13 on new, 260.14 on old
    stopifnot(isTRUE(all.equal(3954.77699876128, cav.msm$minus2loglik, tol=1e-06)))
    qmat <- qmatrix.msm(cav.msm)[c("estimates","SE")]
    stopifnot(isTRUE(all.equal(c(0.226768225214069, -0.583572966218831, 0.337068668450776, 0.0197360725539862), as.numeric(qmat$estimates[2,]), tol=1e-06)))
    stopifnot(isTRUE(all.equal(c(0.0341912476474469, 0.177757314782152, 0.0383135782775986, 0.171176619065207), as.numeric(qmat$SE[2,]), tol=1e-02)))   ### SEs slightly different on different machines.
    stopifnot(isTRUE(all.equal(5.29003443121721, sojourn.msm(cav.msm)[1,3], tol=1e-06)))
}

if (developer.local) {
    ## Baseline constraints
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                                 qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE,
                                 qconstraint = c(1,1,2,2,2,3,3),
                                 method="BFGS", control=list(trace=2, REPORT=1)
                                 )) # 3.22 on new, 17.55 on old
    stopifnot(isTRUE(all.equal(4116.22686367935, cav.msm$minus2loglik, tol=1e-06)))

    qmat <- qmatrix.msm(cav.msm)[c("estimates","SE")]
    stopifnot(isTRUE(all.equal(0.171691686850913, qmat$estimates[2,1], tol=1e-06)))
    stopifnot(isTRUE(all.equal(2.96494230954565, sojourn.msm(cav.msm)[3,1], tol=1e-06)))

    ## Covariate constraints.
    system.time(cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, death = TRUE, fixedpars=FALSE,
                                 covariates = ~ sex, covinits = list(sex=rep(0.01, 7)), constraint=list(sex=c(1,2,3,1,2,3,2)),
                                 method="BFGS", control=list(trace=1, REPORT=1))) # 21.2 on new, 86.58 on old
    stopifnot(isTRUE(all.equal(3959.35551766943, cav.msm$minus2loglik, tol=1e-06)))
    qmat <- qmatrix.msm(cav.msm)[c("estimates","SE")]
    stopifnot(isTRUE(all.equal(0.228458428847816, qmat$estimates[2,1], tol=1e-06)))
}

## Constraints with psoriatic arthritis data
data(psor)
psor.q <- rbind(c(0,0.1,0,0),c(0,0,0.1,0),c(0,0,0,0.1),c(0,0,0,0))
system.time(psor.msm <- msm(state ~ months, subject=ptnum, data=psor,
                qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn, # covinits=list(hieffusn = c(0.5, 0.1, 0), ollwsdrt=c(0.2, 0.1, -0.1)),
                constraint = list(hieffusn=c(1,1,1),ollwsdrt=c(1,1,2)),
                fixedpars=FALSE, control = list(REPORT=1,trace=2), method="BFGS"))
stopifnot(isTRUE(all.equal(1114.89946121717, psor.msm$minus2loglik, tol=1e-06)))
stopifnot(isTRUE(all.equal(0.0953882330391683, qmatrix.msm(psor.msm)$estimates[1,2], tol=1e-03)))


## pears <- pearsonnondeathbasic.msm(psor.msm, obgroups=2, timegroups=2, covgroupings=2, covvec = unlist(psor.msm$data$cov))
## names(pears)
## sum(pears$extable)
## sum(pears$obstable)
## sum(psor.msm$data$nocc)

## Constrain some covariate effects to be minus others
psor.constr.msm <- msm(state ~ months, subject=ptnum, data=psor,
                qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                constraint = list(hieffusn=c(1,-1,1),ollwsdrt=c(-1,1,2)),
                fixedpars=FALSE)
stopifnot(isTRUE(all.equal(psor.constr.msm$Qmatrices$hieffusn[1,2], -psor.constr.msm$Qmatrices$hieffusn[2,3])))
stopifnot(isTRUE(all.equal(psor.constr.msm$Qmatrices$ollwsdrt[1,2], -psor.constr.msm$Qmatrices$ollwsdrt[2,3])))
psor.constr.msm <- msm(state ~ months, subject=ptnum, data=psor,
                qmatrix = psor.q, covariates = ~ollwsdrt+hieffusn,
                constraint = list(hieffusn=c(-10, 10, -10),ollwsdrt=c(-2,2,1)),
                fixedpars=FALSE)
psor.constr.msm
stopifnot(isTRUE(all.equal(1129.52877932181, psor.constr.msm$minus2loglik, tol=1e-06)))
stopifnot(isTRUE(all.equal(psor.constr.msm$Qmatrices$hieffusn[1,2], -psor.constr.msm$Qmatrices$hieffusn[2,3])))
stopifnot(isTRUE(all.equal(psor.constr.msm$Qmatrices$ollwsdrt[1,2], -psor.constr.msm$Qmatrices$ollwsdrt[2,3])))

## No death state
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = FALSE, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4833.0064065267, cav.msm$minus2loglik, tol=1e-06)))

## how big a dataset can 
if (0) { 
  c3.df <- NULL
  for (i in 1:10) {c22.df <- c2.df; c22.df$PTNUM <- c2.df$PTNUM + 120000*(i-1); c3.df <- rbind(c3.df, c22.df)}
  length(unique(c2.df$PTNUM))
  length(unique(c3.df$PTNUM))
  qx <- rbind( c(0, 0.005, 0, 0, 0), c(0, 0, 0.01, 0.02,0), c(0, 0, 0, 0.04, 0.03), c(0, 0, 0, 0, 0), c(0, 0, 0, 0, 0))
  c2.msm <- msm(state~years, subject=PTNUM, data=c2.df,
                qmatrix=qx, death=c(4, 5), method="BFGS", 
                control=list(trace=1, REPORT=1, fnscale=100000))
  c3.msm <- msm(state~years, subject=PTNUM, data=c3.df,
                qmatrix=qx, death=c(4, 5), method="BFGS", 
                control=list(trace=1, REPORT=1, fnscale=100000))
}

## Multiple death states (Jean-Luc's data)
if (developer.local) {
    c2.df <- read.table("~/msm/tests/jeanluc/donneesaveccancerPT.txt", header=TRUE)
    qx <- rbind( c(0, 0.005, 0, 0, 0), c(0, 0, 0.01, 0.02,0), c(0, 0, 0, 0.04, 0.03), c(0, 0, 0, 0, 0), c(0, 0, 0, 0, 0))
    c2.msm <- msm(state~years, subject=PTNUM, data=c2.df,
                  qmatrix=qx, death=c(4, 5), method="BFGS", fixedpars = 1:5,
                  control=list(trace=2, REPORT=1, fnscale=100000))
    stopifnot(isTRUE(all.equal(70646.727505836, c2.msm$minus2loglik, tol=1e-06)))
    c2.msm <- msm(state~years, subject=PTNUM, data=c2.df,
                  qmatrix=qx, method="BFGS", fixedpars = 1:5,
                  control=list(trace=2, REPORT=1, fnscale=100000))
    stopifnot(isTRUE(all.equal(62915.1638036017, c2.msm$minus2loglik, tol=1e-06)))

    ## Same using an "obstype" vector.
    obstype <- ifelse(c2.df$state %in% c(4,5), 3, 1)
    c2.msm <- msm(state~years, subject=PTNUM, data=c2.df, qmatrix=qx,
                  obstype=obstype, method="BFGS", fixedpars = 1:5,
                  control=list(trace=2, REPORT=1, fnscale=100000))
    stopifnot(isTRUE(all.equal(70646.727505836, c2.msm$minus2loglik, tol=1e-06)))
    obstype <- rep(1, length(c2.df$state))
    c2.msm <- msm(state~years, subject=PTNUM, data=c2.df, obstype=obstype,
                  qmatrix=qx, method="BFGS", fixedpars = 1:5,
                  control=list(trace=2, REPORT=1, fnscale=100000))
    stopifnot(isTRUE(all.equal(62915.1638036017, c2.msm$minus2loglik, tol=1e-06)))

### G Marshall's diabetic retinopathy data
    marsh.df <- read.table("~/msm/tests/markov/test.dat", col.names=c("subject","eyes","time","duration","hba1"))
    marsh.df$hba1 <- marsh.df$hba1 - mean(marsh.df$hba1)
    marsh.msm <-
      msm(eyes ~ time, subject=subject, qmatrix = rbind(c(0,0.02039,0,0), c(0.007874,0,0.01012,0), c(0,0.01393,0,0.01045), c(0,0,0,0)),
          covariates = ~ hba1, data = marsh.df, fixedpars=TRUE)
    stopifnot(isTRUE(all.equal(335.897217906310, marsh.msm$minus2loglik, tol=1e-06)))
    system.time(marsh.msm <-
      msm(eyes ~ time, subject=subject, qmatrix = rbind(c(0,0.02039,0,0), c(0.007874,0,0.01012,0), c(0,0.01393,0,0.01045), c(0,0,0,0)),
          covariates = ~ hba1, data = marsh.df))
    stopifnot(isTRUE(all.equal(310.989863258621, marsh.msm$minus2loglik, tol=1e-06)))
    stopifnot(isTRUE(all.equal(-0.0496235211442196, qmatrix.msm(marsh.msm, covariates=0)$estimates[1,1], tol=1e-06)))
}

## Exact times (BOS data)
data(bos)
fiveq <- rbind(c(0,0.01,0,0,0.002), c(0,0,0.07,0,0.01), c(0,0,0,0.07,0.02), c(0,0,0,0,0.03), c(0,0,0,0,0))
(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, exacttimes=TRUE, fixedpars=1:7))
stopifnot(isTRUE(all.equal(3057.85781916437, msmtest5$minus2loglik, tol=1e-06)))
(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, obstype=rep(2, nrow(bos)), fixedpars=1:7))
stopifnot(isTRUE(all.equal(3057.85781916437, msmtest5$minus2loglik, tol=1e-06)))
(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, obstype=rep(1, nrow(bos)), fixedpars=1:7))
stopifnot(isTRUE(all.equal(1868.19375282517, msmtest5$minus2loglik, tol=1e-06)))
## Death and exact times (should be same!)
(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, death=5, obstype=rep(2, nrow(bos)), exacttimes=TRUE, fixedpars=1:7))
stopifnot(isTRUE(all.equal(3057.85781916437, msmtest5$minus2loglik, tol=1e-06)))
(msmtest5 <- msm(state ~ time, qmatrix = fiveq,  subject = ptnum, data = bos, death=5, obstype=rep(2, nrow(bos)), fixedpars=1:7))
stopifnot(isTRUE(all.equal(3057.85781916437, msmtest5$minus2loglik, tol=1e-06)))
## Autogenerated inits (start at MLE, shouldn't need any optimisation)
fiveq.i <- fiveq; fiveq.i[fiveq.i!=0] <- 1
(msmtest5 <- msm(state ~ time, qmatrix = fiveq.i, gen.inits=TRUE, subject = ptnum, data = bos, exacttimes=TRUE, fixedpars=1:7))
stopifnot(isTRUE(all.equal(3025.47316457165, msmtest5$minus2loglik, tol=1e-06)))
(msmtest5 <- msm(state ~ time, qmatrix = fiveq.i, gen.inits=TRUE, subject = ptnum, data = bos, exacttimes=TRUE))
stopifnot(isTRUE(all.equal(3025.47316457165, msmtest5$minus2loglik, tol=1e-06)))


### Aneurysm dataset different in 0.5 (not fromto, includes imputed initial states)


##########    OUTPUT FUNCTIONS    ###################

qmatrix.msm(psor.msm)
stopifnot(isTRUE(all.equal(c(-0.0953882330391683, 0, 0, 0, 0.0953882330391683, -0.163370011525553, 0, 0, 0, 0.163370011525553, -0.255229343798597, 0, 0, 0, 0.255229343798597, 0), as.numeric(qmatrix.msm(psor.msm)$estimates), tol=1e-03)))
stopifnot(isTRUE(all.equal(c(0.0115507014188511, 0, 0, 0, 0.0115507014188511, 0.0195265275850904, 0, 0, 0, 0.0195265275850904, 0.0378507662232158, 0, 0, 0, 0.0378507662232158, 0), as.numeric(qmatrix.msm(psor.msm)$SE), tol=1e-03)))
qmat <- qmatrix.msm(psor.msm, covariates=list(ollwsdrt=0.1, hieffusn=0.4))
stopifnot(isTRUE(all.equal(c(-0.121430585652200, 0, 0, 0, 0.121430585652200, -0.207972362475868, 0, 0, 0, 0.207972362475868, -0.257535341208494, 0, 0, 0, 0.257535341208494, 0), as.numeric(qmat$estimates), tol=1e-03)))
stopifnot(isTRUE(all.equal(c(0.0162156605802465, 0, 0, 0, 0.0162156605802465, 0.0266727053124233, 0, 0, 0, 0.0266727053124233, 0.0364321127089265, 0, 0, 0, 0.0364321127089265, 0), as.numeric(qmat$SE), tol=1e-04)))
try(qmatrix.msm(psor.msm, covariates=list(hieffusn=0.1, foo=0.4))) # deliberate error
qmat <- qmatrix.msm(psor.msm, covariates=list(ollwsdrt=0.1, hieffusn=0.4), cl=0.99)
stopifnot(isTRUE(all.equal(c(-0.171282667596986, 0, 0, 0, 0.0860880282792585, -0.289385121267802, 0, 0, 0, 0.149463467106753, -0.370756460718086, 0, 0, 0, 0.178889538008097, 0), as.numeric(qmat$L), tol=1e-04)))
soj <- qmatrix.msm(psor.msm, covariates=list(ollwsdrt=0.1, hieffusn=0.4), sojourn=TRUE)$sojourn
stopifnot(isTRUE(all.equal(c(8.23515751512713, 4.80833120370037, 3.88296221911705, Inf), as.numeric(soj), tol=1e-03)))
qmatrix.msm(psor.msm, ci="normal", B=2)
qmatrix.msm(psor.msm, ci="boot", B=2)

soj <- sojourn.msm(psor.msm, covariates=list(ollwsdrt=0.1, hieffusn=0.4))
stopifnot(isTRUE(all.equal(c(8.23515751512713, 4.80833120370037, 3.88296221911705, 1.09971073904434, 0.616674252838334, 0.549301375677405, 6.33875136203292, 3.73961380505919, 2.94271599303942, 10.6989240349703, 6.18246967994404, 5.12363260020806), as.numeric(unlist(soj)), tol=1e-04)))
soj <- sojourn.msm(psor.msm, covariates=list(ollwsdrt=0.1, hieffusn=0.4), cl=0.99)
stopifnot(isTRUE(all.equal(5.83830234564607, soj[1,"L"], tol=1e-04)))

stopifnot(isTRUE(all.equal(0.148036812842411, pmatrix.msm(psor.msm, ci="none", t=10)[1,3], tol=1e-04)))
try(pmatrix.msm(psor.msm, t=10, covariates=list(hieffusn=0.1))) # deliberate error
p <- pmatrix.msm(psor.msm, t=10, covariates=list(ollwsdrt=0.1, hieffusn=0.2))
stopifnot(isTRUE(all.equal(0.18196160265907, p[1,3], tol=1e-04)))

set.seed(22061976); stopifnot(isTRUE(all.equal(0.132271576932734, pmatrix.msm(psor.msm, ci="normal", B=3)$L[2,3], tol=1e-04)))

q <- qratio.msm(psor.msm, c(1,2), c(2,3))
stopifnot(isTRUE(all.equal(c(0.583878474075081, 0.0996029045389022, 0.417943274168735, 0.815694601537263), as.numeric(q), tol=1e-04)))
q <- qratio.msm(psor.msm, c(1,2), c(2,3), cl=0.99)
stopifnot(isTRUE(all.equal(0.376262194364283, as.numeric(q["L"]), tol=1e-04)))
q <- qratio.msm(psor.msm, c(1,1), c(2,3))
stopifnot(isTRUE(all.equal(c(-0.583878474075081, 0.0996029045389022, -0.815694601537263, -0.417943274168735), as.numeric(q), tol=1e-04)))
q <- qratio.msm(psor.msm, c(2,2), c(2,3))
stopifnot(isTRUE(all.equal(c(-1,0,-1,-1), as.numeric(q), tol=1e-06)))

qratio.msm(psor.msm, c(1,2), c(2,3), ci="norm", B=2)
qratio.msm(psor.msm, c(1,2), c(2,3), ci="boot", B=2)

p <- prevalence.msm(psor.msm)
stopifnot(isTRUE(all.equal(64, p$Observed[5,5], tol=1e-06)))
stopifnot(isTRUE(all.equal(64, p$Expected[5,5], tol=1e-06)))
stopifnot(isTRUE(all.equal(60.27397, p$"Observed percentages"[4,4], tol=1e-03)))
stopifnot(isTRUE(all.equal(47.399, p$"Expected percentages"[4,4], tol=1e-03)))
p <- prevalence.msm(psor.msm, times=seq(0,60,5))
stopifnot(isTRUE(all.equal(68, p$Observed[5,5], tol=1e-06)))
stopifnot(isTRUE(all.equal(68, p$Expected[5,5], tol=1e-06)))
stopifnot(isTRUE(all.equal(53.33333, p$"Observed percentages"[4,4], tol=1e-03)))
stopifnot(isTRUE(all.equal(39.28835, p$"Expected percentages"[4,4], tol=1e-03)))
#p <- prevalence.msm(psor.msm, ci="boot", B=3)
#p <- prevalence.msm(psor.msm, ci="norm", B=10)

summ <- summary.msm(psor.msm)
p <- summ$prevalences
stopifnot(isTRUE(all.equal(64, p$Observed[5,5], tol=1e-06)))
stopifnot(isTRUE(all.equal(64, p$Expected[5,5], tol=1e-06)))
stopifnot(isTRUE(all.equal(60.27397, p$"Observed percentages"[4,4], tol=1e-03)))
stopifnot(isTRUE(all.equal(47.399, p$"Expected percentages"[4,4], tol=1e-03)))
stopifnot(isTRUE(all.equal(0.385347226135311, summ$hazard$ollwsdrt[1,2], tol=1e-04)))
stopifnot(isTRUE(all.equal(0.385347226135311, summ$hazard$ollwsdrt[2,2], tol=1e-04)))
stopifnot(isTRUE(all.equal(2.35928404626333, summ$hazard$hieffusn[1,3], tol=1e-04)))
stopifnot(isTRUE(all.equal(2.35928404626333, summ$hazard$hieffusn[3,3], tol=1e-04)))

print(interactive())
if (interactive())
  {
      plot.msm(psor.msm)
      plot.msm(psor.msm, from=c(1,3), to=4, range=c(10,30))
      plot.msm(psor.msm, from=c(1,2), to=4, range=c(10,80), legend.pos=c(70,0.1))

      surface.msm(psor.msm)
      surface.msm(psor.msm, type="filled")
      surface.msm(psor.msm, c(3,5), type="filled")
      surface.msm(psor.msm, c(3,4))
      x <- psor.msm$paramdata$params.uniq
      x[6] <- 0
      surface.msm(psor.msm, c(3,4), point=x)
      surface.msm(psor.msm, c(3,4), point=x, xrange=c(-2, -0.6))
      surface.msm(psor.msm, c(3,4), point=x, yrange=c(-1.2, 0.1))
      surface.msm(psor.msm, c(3,4), point=x, np = 5)
      contour(psor.msm)
      persp(psor.msm)
      persp(psor.msm, np=5)
      image(psor.msm)
      plot.prevalence.msm(psor.msm)

      ##
      plotprog.msm(state ~ months, subject=ptnum, data=psor, legend.pos=c(20,0.99), lwd=3, xlab="Months")
      plot.survfit.msm(psor.msm, lwd=3, xlab="Months")
    }


co <- coef.msm(psor.msm)
stopifnot(isTRUE(all.equal(0.498319866154661, co$hieffusn[1,2], tol=1e-04)))

haz <- hazard.msm(psor.msm)
stopifnot(isTRUE(all.equal(0.385347226135311, haz$ollwsdrt[1,2], tol=1e-04)))
stopifnot(isTRUE(all.equal(0.385347226135311, haz$ollwsdrt[2,2], tol=1e-04)))
stopifnot(isTRUE(all.equal(2.35928404626333, haz$hieffusn[1,3], tol=1e-04)))
stopifnot(isTRUE(all.equal(2.35928404626333, haz$hieffusn[3,3], tol=1e-04)))

haz <- hazard.msm(psor.msm, hazard.scale=2)
stopifnot(isTRUE(all.equal(0.148492484690178, haz$ollwsdrt[1,2], tol=1e-04)))
stopifnot(isTRUE(all.equal(0.148492484690178, haz$ollwsdrt[2,2], tol=1e-04)))
#stopifnot(isTRUE(all.equal(5.56622121095267, haz$hieffusn[1,3], tol=1e-04)))
#stopifnot(isTRUE(all.equal(5.56622121095267, haz$hieffusn[3,3], tol=1e-04)))

haz <- hazard.msm(psor.msm, hazard.scale=c(1,2))
stopifnot(isTRUE(all.equal(0.385347226135311, haz$ollwsdrt[1,2], tol=1e-04)))
stopifnot(isTRUE(all.equal(0.385347226135311, haz$ollwsdrt[2,2], tol=1e-04)))
#stopifnot(isTRUE(all.equal(5.56622121095267, haz$hieffusn[1,3], tol=1e-04)))
#stopifnot(isTRUE(all.equal(5.56622121095267, haz$hieffusn[3,3], tol=1e-04)))

stopifnot(isTRUE(all.equal(c(1,2,3), as.numeric(transient.msm(psor.msm)), tol=1e-06)))

stopifnot(isTRUE(all.equal(4, as.numeric(absorbing.msm(psor.msm)), tol=1e-06)))

tot <- totlos.msm(psor.msm)
stopifnot(isTRUE(all.equal(c(10.4834733848813, 6.12107442888416, 3.91804478713086, Inf), as.numeric(tot), tol=1e-04)))
tot <- totlos.msm(psor.msm, fromt=1, tot=30)
stopifnot(isTRUE(all.equal(c(8.93029895281672, 5.30015645647272, 3.16781869820008), as.numeric(tot[1:3]), tol=1e-04)))
tot <- totlos.msm(psor.msm, start=2, fromt=10, tot=30, end=1:3)
stopifnot(isTRUE(all.equal(c(0, 1.14933919741426, 1.50453194710682), as.numeric(tot), tol=1e-04)))

stopifnot(isTRUE(all.equal(-557.449730608585, as.numeric(logLik.msm(psor.msm)), tol=1e-04)))

### pmatrix.piecewise.msm
pmatrix.msm(psor.msm, 10)
times <- c(5, 10, 15)
covariates <- list(list(ollwsdrt=0, hieffusn=0),
                   list(ollwsdrt=0, hieffusn=1),
                   list(ollwsdrt=1, hieffusn=0),
                   list(ollwsdrt=1, hieffusn=1)
                   )
p <- pmatrix.msm(psor.msm, 3, covariates=covariates[[1]])
stopifnot(isTRUE(all.equal(0.0526636335836266, p[1,3], tol=1e-04)))
p <- pmatrix.piecewise.msm(psor.msm, 0, 3, times, covariates)
stopifnot(isTRUE(all.equal(0.0526636335836266, p[1,3], tol=1e-04)))
p <- pmatrix.piecewise.msm(psor.msm, 0, 7, times, covariates)
stopifnot(isTRUE(all.equal(0.172773087945103, p[1,3], tol=1e-04)))
p <- pmatrix.piecewise.msm(psor.msm, 0, 19, times, covariates)
stopifnot(isTRUE(all.equal(0.0510873669808412, p[1,3], tol=1e-04)))
p <- pmatrix.msm(psor.msm, 5, covariates=covariates[[1]]) %*% pmatrix.msm(psor.msm, 5, covariates=covariates[[2]]) %*% pmatrix.msm(psor.msm, 5, covariates=covariates[[3]]) %*% pmatrix.msm(psor.msm, 4, covariates=covariates[[4]])
stopifnot(isTRUE(all.equal(0.0510873669808412, p[1,3], tol=1e-04)))

p <- prevalence.msm(psor.msm, piecewise.times=times, piecewise.covariates=covariates, plot=TRUE)


## bug with one time in 0.5
times <- c(5)
covariates <- list(list(ollwsdrt=0, hieffusn=0),
                   list(ollwsdrt=0, hieffusn=1)
                   )
p <- pmatrix.piecewise.msm(psor.msm, 0, 7, times, covariates)
stopifnot(isTRUE(all.equal(0.172773087945103, p[1,3], tol=1e-04)))

#######  MISCELLANEOUS FEATURES  ##########

### Variables in global environment, not a data frame.
state.g <- cav$state; time.g <- cav$years; subj.g <- cav$PTNUM
cav.msm <- msm(state.g ~ time.g, subject=subj.g, qmatrix = twoway4.q, fixedpars=TRUE)
cav.msm <- msm(state.g ~ time.g, subject=PTNUM, data=cav, qmatrix = twoway4.q, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4833.0064065267, cav.msm$minus2loglik, tol=1e-06)))

### Factor covariates

cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                       covariates = ~ factor(pdiag), covinits=list(sex=rep(0.1,7)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4793.30238295565, cavfaccov.msm$minus2loglik, tol=1e-06)))
pdiag.g <- cav$pdiag
cavfaccov.msm <- msm(state.g ~ time.g, subject=subj.g, qmatrix = twoway4.q, # covs in glob env.
                       covariates = ~ factor(pdiag.g), covinits=list(sex=rep(0.1,7)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4793.30238295565, cavfaccov.msm$minus2loglik, tol=1e-06)))
cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                       covariates = ~ factor(pdiag), covinits=list("factor(pdiag)Nonexistentlevel"=rep(0.1,7)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4793.30238295565, cavfaccov.msm$minus2loglik, tol=1e-06)))
cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                       covariates = ~ factor(pdiag), covinits=list("factor(pdiag)Hyper"=rep(0.1,7)), fixedpars=TRUE) # OK
stopifnot(isTRUE(all.equal(4793.10858368203, cavfaccov.msm$minus2loglik, tol=1e-06)))
cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                       covariates = ~ factor(pdiag), covinits=list(sex=rep(0.1,7)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4793.30238295565, cavfaccov.msm$minus2loglik, tol=1e-06)))
cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                       covariates = ~ pdiag, covinits=list(pdiag=rep(0.1,7)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4793.30238295565, cavfaccov.msm$minus2loglik, tol=1e-06)))
cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                       covariates = ~ pdiag, covinits=list(pdiagNonexistentlevel=rep(0.1,7)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4793.30238295565, cavfaccov.msm$minus2loglik, tol=1e-06)))
cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                       covariates = ~ pdiag, covinits=list(pdiagHyper=rep(0.1,7)), fixedpars=TRUE) # OK
stopifnot(isTRUE(all.equal(4793.10858368203, cavfaccov.msm$minus2loglik, tol=1e-06)))
cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, covariates = ~ pdiag,
                       covinits=list(pdiagHyper=rep(0.1,7),pdiagIDC=rep(0.1,7),pdiagIHD=rep(0.1,7),pdiagOther=rep(0.1,7),pdiagRestr=rep(0.1,7)), fixedpars=TRUE) # OK
stopifnot(isTRUE(all.equal(4793.11816516565, cavfaccov.msm$minus2loglik, tol=1e-06)))

### Factor covariates with bootstrap refitting 
if (0) { 
    psor2 <- psor
    psor2$ollwsdrt <- sample(c(0,1,2), size=nrow(psor), replace=TRUE)
    psor2$ollwsdrt <- ifelse(psor2$ollwsdrt==0, "foo", ifelse(psor2$ollwsdrt==1, "bar", "boing"))
#    psor2$state[psor2$state==4][1:5] <- 99
    system.time(psor2.msm <- msm(state ~ months, subject=ptnum, data=psor2,
                                 qmatrix = psor.q, covariates = ~factor(ollwsdrt) + hieffusn, # covinits=list(hieffusn = c(0.5, 0.1, 0), ollwsdrt=c(0.2, 0.1, -0.1)),
                                 constraint = list(hieffusn=c(1,1,1)), # censor=99, censor.states=c(3,4),
                                 fixedpars=FALSE, control = list(REPORT=1,trace=2), method="BFGS"))
    pmatrix.msm(psor2.msm, ci="boot", B=5, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo"))
    qmatrix.msm(psor2.msm, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo"))
    qmatrix.msm(psor2.msm, ci="normal", B=50, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo"))
    qmatrix.msm(psor2.msm, ci="boot", B=3, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo"))
    qratio.msm(psor2.msm, c(1,2), c(2,3), ci="delta", covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo")) # 
    qratio.msm(psor2.msm, c(1,2), c(2,3), ci="normal", B=50, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo")) # 
    qratio.msm(psor2.msm, c(1,2), c(2,3), ci="boot", B=3, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo")) # 
    sojourn.msm(psor2.msm, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo"))
    sojourn.msm(psor2.msm, ci="normal", B=2, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo"))
    sojourn.msm(psor2.msm, ci="boot", B=3, covariates=list(hieffusn=0, "factor(ollwsdrt)"="foo"))
}

### Test new way of supplying factor covariates to output functions
if (developer.local) {
    pdiag2 <- as.character(cav$pdiag); pdiag2[cav$pdiag %in% c("CVCM","Hyper","Other","Restr")] <- "Other"; pdiag2 <- factor(pdiag2, levels=c("IDC","IHD","Other"))
    cavfaccov.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                           covariates = ~ pdiag2, fixedpars=FALSE, control=list(trace=1, REPORT=1), method="BFGS")
    cavfaccov2.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q,
                           covariates = ~ sex + pdiag2, fixedpars=FALSE, control=list(trace=1, REPORT=1), method="BFGS")
    if (interactive()) {
        save(cavfaccov.msm, file="~/msm/devel/cavfaccov.msm.rda")
        save(cavfaccov2.msm, file="~/msm/devel/cavfaccov2.msm.rda")
        load(file="~/msm/devel/cavfaccov.msm.rda")
        load(file="~/msm/devel/cavfaccov2.msm.rda")
    }
    covariates <- list(pdiag2 = "IHD", sex=1)
    msm:::factorcov2numeric.msm(covariates, cavfaccov2.msm)
    covariates <- list(sex=1, pdiag2 = "IHD")
    msm:::factorcov2numeric.msm(covariates, cavfaccov2.msm)
    covariates <- list(1, pdiag2 = "IHD")
    try(msm:::factorcov2numeric.msm(covariates, cavfaccov2.msm))
    covariates <- list(pdiag2 = "IHD", 1)
    try(msm:::factorcov2numeric.msm(covariates, cavfaccov2.msm))
    covariates <- list(1, "IHD")
    msm:::factorcov2numeric.msm(covariates, cavfaccov2.msm)
    covariates <- list("IHD", 1)
    try(msm:::factorcov2numeric.msm(covariates, cavfaccov2.msm))
    qmatrix.msm(cavfaccov.msm)
    qmatrix.msm(cavfaccov.msm, covariates=list(pdiag2="IDC")) # bug in 0.7.1 here
    qmatrix.msm(cavfaccov.msm, covariates=list("IDC"))
    qmatrix.msm(cavfaccov.msm, covariates=list(pdiag2="IHD"))
    qmatrix.msm(cavfaccov.msm, covariates=list("IHD"))
    qmatrix.msm(cavfaccov.msm, covariates=list(pdiag2="Other"))
    try(qmatrix.msm(cavfaccov.msm, covariates=list(pdiag2="Nonexistent")))
    try(qmatrix.msm(cavfaccov.msm, covariates=list(nonex="Nonexistent")))
    try(qmatrix.msm(cavfaccov.msm, covariates=list(pdiag2="IDC", foo="bar")))

    qmatrix.msm(cavfaccov2.msm, covariates=list(sex=0, pdiag2="IDC"))
    qmatrix.msm(cavfaccov2.msm, covariates=list(pdiag2="IDC", sex=0))
    qmatrix.msm(cavfaccov2.msm, covariates=list(0, "IDC"))
    try(qmatrix.msm(cavfaccov2.msm, covariates=list("IDC")))
    try(qmatrix.msm(cavfaccov2.msm, covariates=list("IDC", 0)))
}

## Some data with censored states
## Replace first few death states by censorings

cav.cens <- cav
cav.cens$state[cav$state==4][1:50] <- 99
cav.cens2 <- cav
cav.cens2$state[cav$state==4][1:50] <- 99
cav.cens2$state[cav$state==4][51:100] <- 999
cav.cens3 <- cav
ns <- c(cav$state[2:nrow(cav)], 0)
cav.cens3$state[cav$state==4][1:50] <- 99
cav.cens3$state[ns==4][1:50] <- 999

twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
### Censored observations - final state censored
stab <- statetable.msm(state, PTNUM, cav.cens)
stopifnot(isTRUE(all.equal(c(1367, 46, 4, 204, 134, 13, 44, 54, 107, 127, 40, 34, 21, 8, 21), as.numeric(stab))))
cavcens.msm <- msm(state ~ years, subject=PTNUM, data=cav.cens, qmatrix=twoway4.q, censor=99, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4724.26606344485, cavcens.msm$minus2loglik, tol=1e-06)))

### Censored observations - two kinds of censoring
statetable.msm(state, PTNUM, cav.cens2)
cavcens2.msm <- msm(state ~ years, subject=PTNUM, data=cav.cens2, qmatrix=twoway4.q, censor=c(99, 999), censor.states=list(c(1,2,3), c(2,3)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4678.23348518727, cavcens2.msm$minus2loglik, tol=1e-06)))

### Censored observations - intermediate state censored
statetable.msm(state, PTNUM, cav.cens3)
cavcens3.msm <- msm(state ~ years, subject=PTNUM, data=cav.cens3, qmatrix=twoway4.q, censor=c(99, 999), censor.states=list(c(2,3), c(1,2,3)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4680.66073438518, cavcens3.msm$minus2loglik, tol=1e-06)))

### First state censored 
cav.cens4 <- cav
cav.cens4$state[c(1,8,12,22)] <- 99
cavcens4.msm <- msm(state ~ years, subject=PTNUM, data=cav.cens4, qmatrix=twoway4.q, censor=c(99), censor.states=list(c(2,3)), fixedpars=TRUE)

### crudeinits with censoring
try(crudeinits.msm(state~ years, PTNUM, twoway4.q, cav.cens))
cru <- crudeinits.msm(state~ years, PTNUM, twoway4.q, cav.cens, censor=99)
stopifnot(isTRUE(all.equal(c(-0.111798558088660, 0.122878533946307, 0, 0, 0.0689030388220138, -0.373978146793108, 0.0618112185064827, 0, 0, 0.144248713763056, -0.223471328446514, 0, 0.0428955192666458, 0.106850899083745, 0.161660109940032, 0), as.numeric(cru), tol=1e-06)))
cru <- crudeinits.msm(state~ years, PTNUM, twoway4.q, cav.cens2, censor=c(99,999), censor.states=list(c(1,2,3),c(2,3)))
stopifnot(isTRUE(all.equal(c(-0.107299472349819, 0.134927714425074, 0, 0, 0.0697104852209013, -0.369584609077378, 0.0789635719132074, 0, 0, 0.158393403890305, -0.170075385659216, 0, 0.0375889871289174, 0.0762634907619986, 0.0911118137460085, 0), as.numeric(cru), tol=1e-06)))
cru <- crudeinits.msm(state~ years, PTNUM, twoway4.q, cav.cens3, censor=c(99,999), censor.states=list(c(2,3),c(1,2,3)))
stopifnot(isTRUE(all.equal(c(-0.112107245394208, 0.124370575094641, 0, 0, 0.0686998668421821, -0.370347934726264, 0.0659650781282531, 0, 0, 0.135425737325276, -0.238489128617530, 0, 0.0434073785520255, 0.110551622306348, 0.172524050489277, 0), as.numeric(cru), tol=1e-06)))

### Viterbi to predict censored states 
v <- viterbi.msm(cavcens.msm)
stopifnot(all.equal(v$observed[v$observed<10], v$fitted[v$observed<10])) # non-censored states should be the same
stopifnot(v$fitted[v$observed==99][1] == 3)
v <- viterbi.msm(cavcens2.msm)
stopifnot(all.equal(v$observed[v$observed<10], v$fitted[v$observed<10])) # non-censored states should be the same
stopifnot(v$fitted[v$observed==99][1] == 3)
v <- viterbi.msm(cavcens3.msm)
stopifnot(all.equal(v$observed[v$observed<10], v$fitted[v$observed<10])) # non-censored states should be the same
stopifnot(all(v$fitted[v$observed==99] %in% 2:3))
stopifnot(all(v$fitted[v$observed==999] %in% 1:3))
v <- viterbi.msm(cavcens4.msm)
stopifnot(all(v$fitted[v$observed==99] %in% 2:3))


### Death with state at previous instant known - HIV model
cav.dp <- cav
ns <- c(cav.dp$state[2:nrow(cav.dp)], 0)
cav.dp$years[ns==4][1:50] <- cav.dp$years[cav.dp$state==4][1:50]
### Observations at identical times not allowed in <= 0.4.1.
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav.dp, qmatrix = twoway4.q, death = 4, fixedpars=TRUE,
                 method="BFGS", control=list(trace=5, REPORT=1))  # Works, with -2L of 2 less than baseline.
stopifnot(isTRUE(all.equal(4906.74189711688, cav.msm$minus2loglik, tol=1e-06)))

### Use "exacttimes" instead of "death" observation schemes for those obs of death with state at previous instant known
### Should be just the same.
### Lik contrib for death, sum_r p(prev, r, t=0), q(r, death) =  q(prev, death)
### Lik contrib for exacttimes, p(prev, prev, t=0), q(prev, death) =  q(prev, death)
### since p(r,r,0) = 1.
obstype <- rep(1, nrow(cav))
obstype[cav$state==4] <- 3
obstype[cav$state==4][1:50] <- 2
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav.dp, qmatrix = twoway4.q, obstype=obstype, fixedpars=TRUE,
                 method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4906.74189711688, cav.msm$minus2loglik, tol=1e-06)))
obstype[cav$state==4][1:50] <- 3 # just to make sure this is the same
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav.dp, qmatrix = twoway4.q, obstype=obstype, fixedpars=TRUE,
                 method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4906.74189711688, cav.msm$minus2loglik, tol=1e-06)))




cat("simple.R: ALL TESTS PASSED\n")

