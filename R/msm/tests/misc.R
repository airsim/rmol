### TESTS OF MISCLASSIFICATION MODELS
### SPECIFIED USING THE OLD ematrix SYNTAX
source("local.R")

library(msm)
# library(msm, lib.loc="../../lib/sun/0.7.5")
data(cav)
oneway4.q <- rbind(c(0, 0.148, 0, 0.0171), c(0, 0, 0.202, 0.081), c(0, 0, 0, 0.126), c(0, 0, 0, 0))
rownames(oneway4.q) <- colnames(oneway4.q) <- c("Well","Mild","Severe","Death")
ematrix <- rbind(c(0, 0.1, 0, 0),c(0.1, 0, 0.1, 0),c(0, 0.1, 0, 0),c(0, 0, 0, 0))

## Plain misc model with no covs

misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE)
misc.msm
stopifnot(isTRUE(all.equal(4296.9155995778, misc.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                                qmatrix = oneway4.q, ematrix=ematrix, death = 4, # fixedpars=1:5,
                                control = list(trace=1, REPORT=1), method="BFGS"))
    stopifnot(isTRUE(all.equal(3951.82919869367, misc.msm$minus2loglik, tol=1e-06)))
    if(interactive()) save(misc.msm, file="~/msm/devel/models/misc.msm.rda")
}

## Does misc model with no misc reduce to simple
twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
nomisc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = twoway4.q, ematrix=matrix(0, nrow=4, ncol=4), death = 4, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4908.81676837903, nomisc.msm$minus2loglik, tol=1e-06)))
simple.msm <- msm(state ~ years, subject = PTNUM, data = cav, qmatrix = twoway4.q, death = 4, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4908.81676837903, simple.msm$minus2loglik, tol=1e-06)))

## Covs on transition rates
misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars = TRUE,
                control = list(trace=1, REPORT=1), method="BFGS",
                covariates = ~ sex, covinits=list(sex=rep(0.1, 5)))
stopifnot(isTRUE(all.equal(4299.35653620144, misccov.msm$minus2loglik, tol=1e-06)))

## Covs on misc probs, old way.
misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                   qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE,
                   misccovariates = ~dage + sex, misccovinits = list(dage=c(0.01,0.02,0.03,0.04), sex=c(-0.013,-0.014,-0.015,-0.016)),
                   control = list(trace=1, REPORT=1), method="BFGS")
misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                   qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE,
                   misccovariates = ~dage + sex, misccovinits = list(dage=c(0.01,0.02,0.03,0.04), sex=c(-0.013,-0.014,-0.015,-0.016)),
                   control = list(trace=1, REPORT=1), method="BFGS")
## stopifnot(isTRUE(all.equal(4306.82007050922, misccov.msm$minus2loglik, tol=1e-06))) # before 0.7.2
stopifnot(isTRUE(all.equal(4304.90609473048, misccov.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                                   qmatrix = oneway4.q, ematrix=ematrix, death = 4,
                                   misccovariates = ~dage + sex, # fixedpars=c(1:5,11),
                                   control = list(trace=1, REPORT=1), method="BFGS"))
    ##    stopifnot(isTRUE(all.equal(3929.39438312539, misccov.msm$minus2loglik, tol=1e-06))) ## 0.7.1 and earlier
    stopifnot(isTRUE(all.equal(3929.59504496140, misccov.msm$minus2loglik, tol=1e-06)))
    if(interactive()) save(misccov.msm, file="~/msm/devel/models/misccov.msm.rda")
}

## Covs on both
misccovboth.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                       qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE,
                       control = list(trace=1, REPORT=1), method="BFGS",
                       covariates = ~ sex, covinits=list(sex=rep(0.1, 5)),
                       misccovariates = ~dage + sex, misccovinits = list(dage=c(0.01,0.02,0.03,0.04), sex=c(-0.013,-0.014,-0.015,-0.016))
                       )
## stopifnot(isTRUE(all.equal(4309.26368021750, misccovboth.msm$minus2loglik, tol=1e-06))) ## 0.7.1 and earlier
stopifnot(isTRUE(all.equal(4307.35065423690, misccovboth.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(misccovboth.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                                       qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=FALSE,
                                       control = list(trace=1, REPORT=1), method="BFGS",
                                       covariates = ~ sex, covinits=list(sex=rep(0.1, 5)),
                                       misccovariates = ~dage + sex, misccovinits = list(dage=c(0.01,0.02,0.03,0.04), sex=c(-0.013,-0.014,-0.015,-0.016))
                                       ))
    ##    stopifnot(isTRUE(all.equal(3921.40046811911, misccovboth.msm$minus2loglik, tol=1e-06))) # 0.7.1 and earlier
    stopifnot(isTRUE(all.equal(3921.42240883417, misccovboth.msm$minus2loglik, tol=1e-06)))
    if(interactive()) save(misccovboth.msm, file="~/msm/devel/models/misccovboth.msm.rda")
    if(interactive()) load("~/msm/devel/models/misccovboth.msm.rda")
    print(misccovboth.msm)

##########    OUTPUT FUNCTIONS    ###################

    if(interactive()) load("~/msm/devel/models/misc.msm.rda")
    if(interactive()) load("~/msm/devel/models/misccov.msm.rda")
    if(interactive()) load("~/msm/devel/models/misccovboth.msm.rda")

    e <- ematrix.msm(misc.msm)
    stopifnot(isTRUE(all.equal(0.00766164690017842, e$estimates[1,2], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.00334014173130528, e$SE[1,2], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.00325308687951399, e$L[1,2], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.0179371415700995, e$U[1,2], tol=1e-06)))

    print(ematrix.msm(misc.msm), digits=2)
    print(viterbi.msm(misc.msm)[1:50,])
    vit <- viterbi.msm(misc.msm)[viterbi.msm(misc.msm)$subject==100063,]
    stopifnot(isTRUE(all.equal(c(1, 1, 1, 1, 2, 2, 2, 2, 2, 2), vit$fitted, tol=1e-06)))

    odds <- odds.msm(misccov.msm)
#    stopifnot(isTRUE(all.equal(0.924920277547759, odds$dage[1,2], tol=1e-06)))
#    stopifnot(isTRUE(all.equal(0.9350691888108385, odds$dage[2,2], tol=1e-06)))
#    stopifnot(isTRUE(all.equal(24.76686951404301, odds$sex[1,3], tol=1e-04)))
#    stopifnot(isTRUE(all.equal(30.90173037227264, odds$sex[3,3], tol=1e-04)))
    stopifnot(isTRUE(all.equal(0.92024511282455, odds$dage[1,2], tol=1e-03)))
    stopifnot(isTRUE(all.equal(0.937622692212605, odds$dage[2,2], tol=1e-03)))
    stopifnot(isTRUE(all.equal(23.6267954503319, odds$sex[1,3], tol=1e-01)))
    stopifnot(isTRUE(all.equal(30.7225710461079, odds$sex[3,3], tol=1e-01)))

    e <- ematrix.msm(misccov.msm)
    stopifnot(isTRUE(all.equal(0.00271289377320006, e$estimates[1,2], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.0351301610655661, e$SE[1,2], tol=1e-02)))

    e <- ematrix.msm(misccov.msm, covariates=0)
    stopifnot(isTRUE(all.equal(0.00523189426375198, e$estimates[1,2], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.00717339683841909, e$SE[1,2], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.000182524613416697, e$L[1,2], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.0389554284408482, e$U[1,2], tol=1e-02)))

    e <- ematrix.msm(misccov.msm, covariates=list(dage=50, sex=0))
    stopifnot(isTRUE(all.equal(0.0126402839581582, e$estimates[1,2], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.0127991364840901, e$SE[1,2], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.000364352259872661, e$L[1,2], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.0198983271598344, e$U[1,2], tol=1e-02)))

### Non misclassification-specific output functions

    q <- qmatrix.msm(misccov.msm)
    stopifnot(isTRUE(all.equal(0.234871828782083, q$estimates[2,3], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.0388940534715571, q$SE[2,3], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.169775324070530, q$L[2,3], tol=1e-02)))
    stopifnot(isTRUE(all.equal(0.324928114597637, q$U[2,3], tol=1e-02)))

    soj <- sojourn.msm(misccov.msm)
    stopifnot(isTRUE(all.equal(c(6.83075273024829, 3.81966398452026, 3.29901891409971, 0.499352190044205,
0.41662507532632, 0.395976119914232, 5.91892340913934, 3.08447614101601,
2.60745249850692, 7.88305231146405, 4.73008455492069, 4.17400731243225
), as.numeric(unlist(soj)), tol=1e-02)))

    p <- pmatrix.msm(misccov.msm, 10)
    stopifnot(isTRUE(all.equal(0.122616549949547, p[1,3], tol=1e-03)))

    q <- qratio.msm(misccov.msm, c(1,2), c(2,3), cl=0.99)
    stopifnot(isTRUE(all.equal(c(0.449639898189716, 0.0948158687296418, 0.261198374155947, 0.774032528714554), as.numeric(q), tol=1e-02)))

    p <- prevalence.msm(misccov.msm)
    stopifnot(isTRUE(all.equal(158, p$Observed[5,4], tol=1e-03)))
    stopifnot(isTRUE(all.equal(134.668020428293, p$Expected[5,4], tol=1e-03)))
    stopifnot(isTRUE(all.equal(31.43564356435644, p$"Observed percentages"[4,4], tol=1e-03)))
    stopifnot(isTRUE(all.equal(27.5796638007428, p$"Expected percentages"[4,4], tol=1e-03)))

    summ <- summary.msm(misccov.msm)
    p <- summ$prevalences
    stopifnot(isTRUE(all.equal(158, p$Observed[5,4], tol=1e-03)))
    stopifnot(isTRUE(all.equal(134.668020428293, p$Expected[5,4], tol=1e-03)))
    stopifnot(isTRUE(all.equal(31.43564356435644, p$"Observed percentages"[4,4], tol=1e-03)))
    stopifnot(isTRUE(all.equal(27.5796638007428, p$"Expected percentages"[4,4], tol=1e-03)))

    if (interactive()) plot.msm(misccov.msm)

    cf <- coef.msm(misccovboth.msm)
    stopifnot(isTRUE(all.equal(-0.535346454908361, cf$Qmatrices$sex[1,2], tol=1e-04)))
    stopifnot(isTRUE(all.equal(-6.71038434136682, cf$Ematrices$sex[1,2], tol=1e-04)))

    stopifnot(isTRUE(all.equal(c(1,2,3), as.numeric(transient.msm(misccov.msm)), tol=1e-03)))

    stopifnot(isTRUE(all.equal(4, as.numeric(absorbing.msm(misccov.msm)), tol=1e-03)))

    tot <- totlos.msm(misccov.msm)
    stopifnot(isTRUE(all.equal(c(6.83075273082287, 2.75543070960308, 2.13503613252349), as.numeric(tot), tol=1e-03)))

    stopifnot(isTRUE(all.equal(-1964.79752248070, as.numeric(logLik.msm(misccov.msm)), tol=1e-03)))
}


##########    OTHER FEATURES      ###################

if (developer.local) {
    ## Baseline intens constraints
    misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                    qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=4:7,
                    qconstraint = c(1, 2, 1, 2, 3),
                    control = list(trace=1, REPORT=1), method="BFGS")
    stopifnot(isTRUE(all.equal(4209.65938095232, misc.msm$minus2loglik, tol=1e-06)))
    q <- qmatrix.msm(misc.msm)
    stopifnot(isTRUE(all.equal(-0.145819054714827, q$estimates[1,1], tol=1e-06)))

    ## Baseline misc constraints
    ematrix2 <- rbind(c(0, 0.1, 0, 0),c(0.1, 0, 0.11, 0),c(0, 0.11, 0, 0),c(0, 0, 0, 0))
    misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                    qmatrix = oneway4.q, ematrix=ematrix2, death = 4, fixedpars=1:5,
                    econstraint = c(1, 1, 2, 2),
                    control = list(trace=1, REPORT=1), method="BFGS")
    stopifnot(isTRUE(all.equal(4161.05767600322, misc.msm$minus2loglik, tol=1e-06)))
    e <- ematrix.msm(misc.msm)
    stopifnot(isTRUE(all.equal(0.970221499780077, e$estimates[1,1], tol=1e-06)))

    ## intens covariate constraints
    ## Give replicated inits for replicated cov effs, as that's consistent with constraints on q, e and h.

    misc.msm <- msm(state ~ years, subject = PTNUM, data = cav, fixedpars=c(1:5, 9:12),
                    qmatrix = oneway4.q, ematrix=ematrix, death = 4,
                    control = list(trace=1, REPORT=1), method="BFGS",
                    covariates = ~ sex, covinits=list(sex=c(0, 0, 0.1, 0, 0)),
                    constraint = list(sex = c(1, 2, 1, 2, 3))  )
    stopifnot(isTRUE(all.equal(4277.77801412343, misc.msm$minus2loglik, tol=1e-06)))
    q <- qmatrix.msm(misc.msm, covariates=0)
    stopifnot(isTRUE(all.equal(-0.17619654476216, q$estimates[1,1], tol=1e-06)))

    ## misc covariate constraints.
    misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                       qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=c(1:5),
                       misccovariates = ~dage + sex,
                       misccovinits = list(dage=c(0.01,0.01,0.001,0.001), sex=c(0.0131,0.0132,0.0133,0.0134)),
                       miscconstraint = list(dage = c(1, 1, 2, 2)),
                       control = list(trace=1, REPORT=1), method="BFGS")
    stopifnot(isTRUE(all.equal(4017.02699645160, misccov.msm$minus2loglik, tol=1e-06)))
    e <- ematrix.msm(misccov.msm)
    stopifnot(isTRUE(all.equal(0.999683601766175, e$estimates[1,1], tol=1e-06)))
    e <- ematrix.msm(misccov.msm, covariates=0)
    stopifnot(isTRUE(all.equal(0.992813688955682, e$estimates[1,1], tol=1e-06)))

    ## fixedpars for misc covariates.  Parameters are ordered within covariate, within parameter, within state.
    misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                       qmatrix = oneway4.q, ematrix=ematrix, death = 4,
                       misccovariates = ~dage + sex,
                       misccovinits = list(dage=c(0.01,0.02,0.03,0.04), sex=c(-0.013,-0.014,-0.015,-0.016)),
                       fixedpars = c(10, 11, 12, 15),
                       control = list(trace=1, REPORT=1), method="BFGS")
    stopifnot(isTRUE(all.equal(3946.96900738597, misccov.msm$minus2loglik, tol=1e-06)))
}

## multiple death states (Jean-Luc's data)
## Misclassification between states 2 and 3

if (developer.local) {
  c2.df <- read.table("~/msm/tests/jeanluc/donneesaveccancerPT.txt", header=TRUE)
  print(statetable.msm(state, PTNUM, c2.df))
  qx <- rbind( c(0, 0.005, 0, 0, 0), c(0, 0, 0.01, 0.02,0), c(0, 0, 0, 0.04, 0.03), c(0, 0, 0, 0, 0), c(0, 0, 0, 0, 0))
  ex <- rbind( c(0, 0, 0, 0, 0), c(0, 0, 0.1, 0, 0), c(0, 0.1, 0, 0, 0), c(0, 0, 0, 0, 0), c(0, 0, 0, 0, 0) )
  c2.msm <- msm(state~years, subject=PTNUM, data=c2.df, qmatrix=qx, ematrix=ex, death=c(4, 5), method="BFGS", fixedpars = TRUE)
  stopifnot(isTRUE(all.equal(70084.3665626129, c2.msm$minus2loglik, tol=1e-06)))

  ## multiple death states specified using an obstype vector
  d45 <- rep(1, nrow(c2.df)); d45[c2.df$state %in% c(4,5)] <- 3
  c2.msm <- msm(state~years, subject=PTNUM, data=c2.df, qmatrix=qx, ematrix=ex, obstype=d45, method="BFGS", fixedpars = TRUE)
  stopifnot(isTRUE(all.equal(70084.3665626129, c2.msm$minus2loglik, tol=1e-06)))
}

## exact times
misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, exacttimes=TRUE, fixedpars=TRUE,
                control = list(trace=1, REPORT=1), method="BFGS") # should warn about redundant death argument
stopifnot(isTRUE(all.equal(4864.14764195147, misc.msm$minus2loglik, tol=1e-06)))

misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, exacttimes=TRUE, fixedpars=TRUE,
                control = list(trace=1, REPORT=1), method="BFGS")
stopifnot(isTRUE(all.equal(4864.14764195147, misc.msm$minus2loglik, tol=1e-06)))

## exact times specified using an obstype vector
misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, obstype=rep(2, nrow(cav)), fixedpars=TRUE,
                control = list(trace=1, REPORT=1), method="BFGS")
stopifnot(isTRUE(all.equal(4864.14764195147, misc.msm$minus2loglik, tol=1e-06)))

## initprobs
misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, initprobs=c(0.7, 0.1, 0.1, 0.1), fixedpars=TRUE,
                control = list(trace=1, REPORT=1), method="BFGS")
stopifnot(isTRUE(all.equal(4725.9078185031, misc.msm$minus2loglik, tol=1e-06)))

## initprobs in Viterbi : bug fix for 0.6.1
if (developer.local) {
    miscinitp.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                    qmatrix = oneway4.q, ematrix=ematrix, death = 4, initprobs=c(0.6, 0.4, 0, 0),
                    control = list(trace=1, REPORT=1), method="BFGS")
    if(interactive()) save(miscinitp.msm, file="~/msm/devel/models/miscinitp.msm.rda")
    if(interactive()) load(file="~/msm/devel/models/miscinitp.msm.rda")
    vitinitp <- viterbi.msm(miscinitp.msm)
    table(vitinitp$fitted[vitinitp$time==0]) / nrow(vitinitp[vitinitp$time==0,])
}

## Censored states
## Different in 0.4 or less, censored states are not subject to misclassification in >= 0.4.1
## Reverted in 0.8, since obstrue can be used for censored states that are not misclassified. 

cav.cens <- cav
cav.cens$state[cav$state==4][1:50] <- 99
cav.cens2 <- cav
cav.cens2$state[cav$state==4][1:50] <- 99
cav.cens2$state[cav$state==4][51:100] <- 999
cav.cens3 <- cav
ns <- c(cav$state[2:nrow(cav)], 0)
cav.cens3$state[cav$state==4][1:50] <- 99
cav.cens3$state[ns==4][1:50] <- 999

misc.msm <- msm(state ~ years, subject = PTNUM, data = cav.cens,
                qmatrix = oneway4.q, ematrix=ematrix, death=TRUE, censor=99, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4025.42265024404, misc.msm$minus2loglik, tol=1e-06)))

## Two types of censoring
misc.msm <- msm(state ~ years, subject=PTNUM, data=cav.cens2, qmatrix=oneway4.q, ematrix=ematrix, censor=c(99, 999), death=4, censor.states=list(c(1,2,3), c(2,3)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(3811.69640533587, misc.msm$minus2loglik, tol=1e-06)))
cav.cens2$obstrue <- as.numeric(cav.cens2$state %in% c(999))
misc.msm <- msm(state ~ years, subject=PTNUM, data=cav.cens2, qmatrix=oneway4.q, ematrix=ematrix, censor=c(99, 999), death=4, obstrue=obstrue, censor.states=list(c(1,2,3), c(2,3)), fixedpars=TRUE)
stopifnot(isTRUE(all.equal(3822.04540210944, misc.msm$minus2loglik, tol=1e-06)))

## Does misc model with no misc reduce to simple, with censoring

twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
misc.msm <- msm(state ~ years, subject = PTNUM, data = cav.cens,
                qmatrix = twoway4.q, ematrix=matrix(0, nrow=4, ncol=4), censor=99, death=TRUE, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4759.28151596975, misc.msm$minus2loglik, tol=1e-06)))

simple.msm <- msm(state ~ years, subject = PTNUM, data = cav.cens, qmatrix = twoway4.q, death=TRUE, censor=99, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4759.28151596975, simple.msm$minus2loglik, tol=1e-06)))

misc.msm <- msm(state ~ years, subject = PTNUM, data = cav.cens,
                qmatrix = twoway4.q, ematrix=matrix(0, nrow=4, ncol=4), censor=99, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4724.26606344485, misc.msm$minus2loglik, tol=1e-06)))

simple.msm <- msm(state ~ years, subject = PTNUM, data = cav.cens, qmatrix = twoway4.q, censor=99, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4724.26606344485, simple.msm$minus2loglik, tol=1e-06)))


## Viterbi with non-HMM model
twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
cav.msm <- msm(state ~ years, subject=PTNUM, data = cav, qmatrix = twoway4.q, fixedpars=TRUE)
vit <- viterbi.msm(cav.msm)[1:50,] # no error, returns observed states.
stopifnot(all.equal(vit$observed, vit$fitted))


#### Estimating initprobs

if (developer.local)
  misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                  qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=FALSE, initprobs=rep(0.25, 4), est.initprobs=TRUE,
                  control = list(trace=1, REPORT=1), method="BFGS")
### just converges to 1,0,0,0

#### Simulate data with known initprobs.
nsubj <- 50; nobspt <- 6
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt),
                     x = rnorm(nsubj*nobspt), y = rnorm(nsubj*nobspt)* 5 + 2 )
(three.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
## (three.q <- msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
ematrix3 <- rbind(c(0, 0.1, 0), c(0.1, 0, 0), c(0,0,0))
initprobs <- c(0.5, 0.5, 0)
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, ematrix=ematrix3, start=sample(1:3, 50, prob=initprobs, replace=TRUE))
misc.msm <- msm(obs ~ time, subject = subject, data = sim2.df,
                qmatrix = three.q, ematrix=ematrix3, initprobs=c(0.1, 0.9, 0.05), fixedpars=7, est.initprobs=TRUE,
                control = list(trace=1, REPORT=1), method="BFGS")
stopifnot(misc.msm$hmodel$initprobs["State 2","LCL"] < 0.5 && 0.5 < misc.msm$hmodel$initprobs["State 2","UCL"])

#### Covariate effects on initprobs: simulation test.
if (developer.local) {
    nsubj <- 500; nobspt <- 6
    sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt),
                         time = seq(0, 20, length=nobspt),
                         x = rnorm(nsubj*nobspt))
    (three.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)),
                                                c(0, 0, exp(-3)),
                                                c(0, 0, 0))))
    ematrix3 <- rbind(c(0, 0.1, 0), c(0.1, 0, 0), c(0,0,0))
    ip.base <- c(0.5, 0.2, 0.3)
    beta <- 0.5 # covariate effect of 0.5 on log(ip2/ip1) and log(ip3/ip1)
    ipl2 <- exp(log(ip.base[2]/ip.base[1]) + beta*sim.df$x[sim.df$time==0])
    ipl3 <- exp(log(ip.base[3]/ip.base[1]) + beta*sim.df$x[sim.df$time==0])
    initprobs <- cbind(1, ipl2, ipl3)/(1 + ipl2 + ipl3)
    start <- numeric(nsubj)
    for (i in 1:nsubj)
      start[i] <- sample(1:3, 1, prob=initprobs[i,], replace=TRUE)
    set.seed(22061976)
    sim2.df <- simmulti.msm(sim.df, qmatrix=three.q, ematrix=ematrix3,
                            start=start, covariates=list(x=c(0,0,0)))
    misc.msm <- msm(obs ~ time, subject = subject, data = sim2.df,
                    qmatrix = three.q, ematrix=ematrix3, center=FALSE,
                    initcovariates = ~ x,
                    est.initprobs=TRUE, fixedpars=1:5)
    misc.msm
    stopifnot(misc.msm$hmodel$initprobs["State 2","LCL"] < 0.2 &&
              0.2 < misc.msm$hmodel$initprobs["State 2","UCL"])
    stopifnot(misc.msm$hmodel$initprobs["State 3","LCL"] < 0.3 &&
              0.3 < misc.msm$hmodel$initprobs["State 3","UCL"])
    stopifnot(misc.msm$hmodel$icoveffect["x, State 2","LCL"] < 0.5
              && 0.5 < misc.msm$hmodel$icoveffect["x, State 2","UCL"])
    stopifnot(misc.msm$hmodel$icoveffect["x, State 3","LCL"] < 0.5
              && 0.5 < misc.msm$hmodel$icoveffect["x, State 3","UCL"])
}

                                        #library(nnet)
                                        #xstart <- sim.df$x[sim.df$time==0]
                                        #summary(multinom(start ~ xstart))  # regress true known start state on covs.

### Allow some observations to be observed without error. (first observation)
## cav$firstobs <- as.numeric(c(TRUE, cav$PTNUM[2:nrow(cav)] != cav$PTNUM[1:(nrow(cav)-1)]))
misc.msm <- msm(state ~ years, subject = PTNUM, data = cav, obstrue=firstobs,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE)
stopifnot(all.equal(misc.msm$minus2loglik, 4165.84711809003))
### test against dummy covariate hack
misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE, center=FALSE,
                misccovariates=~firstobs, misccovinits = list(firstobs=rep(-1e+06,4)))
stopifnot(all.equal(misc.msm$minus2loglik, 4165.84711809003))

### ignore default initprobs if first obs is true state 2 
cav2 <- cav
cav2$state[cav2$firstobs==1] <- 2
misc.msm <- msm(state ~ years, subject = PTNUM, data = cav2, obstrue=firstobs,
                qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE)
misc.msm

### why nan on old version with initp 0,1,0,0 ? 

### Are new results same as old when only two classification probs?
### slightly diff with no covs: numeric fuzz due to different scale of opt.
### with onoe cov:

## c2.df <- read.table("~/msm/tests/jeanluc/donneesaveccancerPT.txt", header=TRUE)
## print(statetable.msm(state, PTNUM, c2.df))
## qx <- rbind( c(0, 0.005, 0, 0, 0), c(0, 0, 0.01, 0.02,0), c(0, 0, 0, 0.04, 0.03), c(0, 0, 0, 0, 0), c(0, 0, 0, 0, 0))
## ex <- rbind( c(0, 0, 0, 0, 0), c(0, 0, 0.1, 0, 0), c(0, 0.1, 0, 0, 0), c(0, 0, 0, 0, 0), c(0, 0, 0, 0, 0) )
## c2.msm <- msm(state~years, subject=PTNUM, data=c2.df, qmatrix=qx, ematrix=ex,
##               death=c(4, 5), method="BFGS", fixedpars = 1:5, control=list(REPORT=1,trace=1,fnscale=50000))
## c3.msm <- msm(state~years, subject=PTNUM, data=c2.df, qmatrix=qx, ematrix=ex,
##               misccovariates=~age, death=c(4, 5), method="BFGS", fixedpars = 1:5, control=list(REPORT=1,trace=1,fnscale=50000))

## Norm Good's example

nsubj <- 50; nobspt <- 6
sim.df <- data.frame(subject = rep(1:nsubj, each=nobspt), time = seq(0, 20, length=nobspt), 
                     x = rnorm(nsubj*nobspt), y = rnorm(nsubj*nobspt)* 5 + 2 )
(three.q <- msm:::msm.fixdiag.qmatrix(rbind(c(0, exp(-3), exp(-6)), c(0, 0, exp(-3)), c(0, 0, 0))))
(three.e <- msm:::msm.fixdiag.ematrix(rbind(c(0, 0.1, 0.1), c(0.1, 0, 0.1), c(0.1, 0.1, 0))))
set.seed(22061976)
sim2.df <- simmulti.msm(sim.df[,1:2], qmatrix=three.q, ematrix=three.e)
sim2.df[1:100,]
sim2.df$obs[sample(which(sim2.df$obs %in% 1:2), 50)] <- 99
misc.msm <- msm(obs ~ time, subject=subject, data=sim2.df, censor=99, censor.states=list(1:2), ematrix=three.e, qmatrix=three.q)

cat("misc.R: ALL TESTS PASSED\n")
