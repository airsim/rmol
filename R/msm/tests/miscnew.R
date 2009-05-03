### TESTS OF MISCLASSIFICATION MODELS IMPLEMENTED WITH hmodel OBJECTS
### CHECK THESE against misc.R.
source("local.R")
library(msm)
data(cav)

## Plain misc model using hmmCat

oneway4.q <- rbind(c(0, 0.148, 0, 0.0171), c(0, 0, 0.202, 0.081), c(0, 0, 0, 0.126), c(0, 0, 0, 0))
rownames(oneway4.q) <- colnames(oneway4.q) <- c("Well","Mild","Severe","Death")
ematrix <- rbind(c(0, 0.1, 0, 0),c(0.1, 0, 0.1, 0),c(0, 0.1, 0, 0),c(0, 0, 0, 0))

miscnew.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, death = 4, fixedpars=TRUE,
                hmodel=list(
                  hmmCat(prob=c(0.9, 0.1, 0, 0)),
                  hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                  hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent())
                )
stopifnot(isTRUE(all.equal(4296.9155995778, miscnew.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(miscnew.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                                   qmatrix = oneway4.q, death = 4,
                                   hmodel=list(
                                     hmmCat(prob=c(0.9, 0.1, 0, 0)),
                                     hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                                     hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent()),
                                   control = list(trace=1, REPORT=1), method="BFGS"
                                   ))
    stopifnot(isTRUE(all.equal(3951.82919869367, miscnew.msm$minus2loglik, tol=1e-06)))
    if(interactive()) save(miscnew.msm, file="~/msm/devel/models/miscnew.msm.rda")
}

## Covs on misc probs, new way, with hmodel

misccovnew.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                      qmatrix = oneway4.q, death = 4, fixedpars=TRUE,
                      hmodel=list(
                        hmmCat(prob=c(0.9, 0.1, 0, 0)),
                        hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                        hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent()),
                      hcovariates=list(~dage + sex, ~dage + sex, ~dage + sex, ~1),
                      hcovinits = list(c(0.01,-0.013), c(0.02,-0.014,0.03,-0.015), c(0.04,-0.016), NULL)
                )
stopifnot(isTRUE(all.equal(4304.90609473048, misccovnew.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    system.time(misccovnew.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                                      qmatrix = oneway4.q, death = 4, fixedpars=FALSE,
                                      hmodel=list(
                                        hmmCat(prob=c(0.9, 0.1, 0, 0)),
                                        hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                                        hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent()),
                                      hcovariates=list(~dage + sex, ~dage + sex, ~dage + sex, ~1),
                                      hcovinits = list(c(0.01,-0.013), c(0.02,-0.014,0.03,-0.015), c(0.04,-0.016), NULL),
                                      control = list(trace=1, REPORT=1), method="BFGS"
                                      ))
    stopifnot(isTRUE(all.equal(3929.6179549396, misccovnew.msm$minus2loglik, tol=1e-06)))
    if(interactive()) save(misccovnew.msm, file="~/msm/devel/models/misccovnew.msm.rda")

    ## Misclassification-specific output functions with misc model specified new way

    if(interactive()) load("~/msm/devel/models/miscnew.msm.rda")
    if(interactive()) load("~/msm/devel/models/misccovnew.msm.rda")

    ## Don't allow ematrix
    try(ematrix.msm(miscnew.msm))
                                        #ematrix.msm(miscnew.msm)[c("estimates","SE")]
                                        #print(ematrix.msm(miscnew.msm), digits=2)
    ## Instead extract parameters like so
    pars <- misccovnew.msm$hmodel$pars
    stopifnot(all.equal(c(4, 1, 0.99511198872804, 0.00488801127196052, 0, 0, 4, 2, 0.300766185058357,
                          0.664644326560132, 0.0345894883815110, 0, 4, 3, 0, 0.176011390721266,
                          0.823988609278734, 0, 4), as.numeric(pars), tol=1e-06))

    vit <- viterbi.msm(miscnew.msm)[viterbi.msm(miscnew.msm)$subject==100063,]
    stopifnot(isTRUE(all.equal(c(1, 1, 1, 1, 2, 2, 2, 2, 2, 2), vit$fitted, tol=1e-06)))
    vit <- viterbi.msm(misccovnew.msm)[viterbi.msm(miscnew.msm)$subject==100063,]
    stopifnot(isTRUE(all.equal(c(1, 1, 1, 1, 2, 2, 2, 2, 2, 2), vit$fitted, tol=1e-06)))

    ## Don't alllow odds.msm. need model fitted with ematrix.
    try(odds.msm(misccovnew.msm))

    ## Non misclassification-specific output functions.  All OK.

    q <- qmatrix.msm(misccovnew.msm)
    stopifnot(isTRUE(all.equal(0.234542167875117, q$estimates[2,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.0388079388733554, q$SE[2,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.169581698201651, q$L[2,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.324386588263472, q$U[2,3], tol=1e-06)))

    soj <- sojourn.msm(misccovnew.msm)
    stopifnot(isTRUE(all.equal(c(6.83321639410394, 3.81936090620942, 3.30166754574029, 0.497944557109818,
                                 0.415723310862545, 0.396549984844218, 5.92375531526262, 3.08560662413694,
                                 2.60914943494788, 7.88230502504826, 4.72760124954717, 4.17799319448044
                                 ), as.numeric(unlist(soj)), tol=1e-06)))

    p <- pmatrix.msm(misccovnew.msm, 10)
    stopifnot(isTRUE(all.equal(0.122508740003521, p[1,3], tol=1e-06)))

    q <- qratio.msm(misccovnew.msm, c(1,2), c(2,3), cl=0.99)
    stopifnot(isTRUE(all.equal(c(0.45013308887982, 0.0947649865214795, 0.261716725744956, 0.774195065782466), as.numeric(q), tol=1e-06)))

    p <- prevalence.msm(misccovnew.msm)
    stopifnot(isTRUE(all.equal(158, p$Observed[5,4], tol=1e-06)))
    stopifnot(isTRUE(all.equal(134.675751173943, p$Expected[5,4], tol=1e-06)))
    stopifnot(isTRUE(all.equal(31.4356435643564, p$"Observed percentages"[4,4], tol=1e-06)))
    stopifnot(isTRUE(all.equal(27.5832155341627, p$"Expected percentages"[4,4], tol=1e-06)))

    summ <- summary.msm(misccovnew.msm)
    p <- summ$prevalences
    stopifnot(isTRUE(all.equal(158, p$Observed[5,4], tol=1e-06)))
    stopifnot(isTRUE(all.equal(134.675751173943, p$Expected[5,4], tol=1e-06)))
    stopifnot(isTRUE(all.equal(31.4356435643564, p$"Observed percentages"[4,4], tol=1e-06)))
    stopifnot(isTRUE(all.equal(27.5832155341627, p$"Expected percentages"[4,4], tol=1e-06)))

    if (interactive()) plot.msm(misccovnew.msm)
                                        #coef.msm(misccovbothnew.msm)
                                        #hazard.msm(misccovbothnew.msm)
    stopifnot(isTRUE(all.equal(c(1,2,3), as.numeric(transient.msm(misccovnew.msm)), tol=1e-06)))

    stopifnot(isTRUE(all.equal(4, as.numeric(absorbing.msm(misccovnew.msm)), tol=1e-06)))

    tot <- totlos.msm(misccovnew.msm)
    stopifnot(isTRUE(all.equal(c(6.83321639468168, 2.7553561747237, 2.1336934417779), as.numeric(tot), tol=1e-06)))

    stopifnot(isTRUE(all.equal(1964.8089774698, as.numeric(logLik.msm(misccovnew.msm)), tol=1e-06)))

}

## Covariate initial values defaulting to 0

misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, death = 4, fixedpars=TRUE,
                hmodel=list(
                  hmmCat(prob=c(0.9, 0.1, 0, 0)),
                  hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                  hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent()),
                hcovariates=list(~dage + sex, ~dage + sex, ~dage + sex, ~1)
                )
stopifnot(isTRUE(all.equal(4296.9155995778, misc.msm$minus2loglik, tol=1e-06)))


## Covs on misc probs, new way, with ematrix
## Don't allow, since hcovariates doesn't logically correspond to ematrix.
try ( misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                         qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=1:17,
                         hcovariates=list(~dage + sex, ~dage + sex, ~dage + sex, ~1),
                         hcovinits = list(c(0.01,0.013), c(0.01,0.013,0.01,0.013), c(0.01,0.013), NULL),
                         control = list(trace=1, REPORT=1), method="BFGS") )

## initprobs

misc.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                qmatrix = oneway4.q, death = 4, fixedpars=TRUE,
                initprobs=c(0.7, 0.1, 0.1, 0.1),
                hmodel=list(
                  hmmCat(prob=c(0.9, 0.1, 0, 0)),
                  hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                  hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent())
                )
misc.msm
stopifnot(isTRUE(all.equal(4725.9078185031, misc.msm$minus2loglik, tol=1e-06)))


## Does misc model with no misc reduce to simple
twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
miscnew.msm <- msm(state ~ years, subject = PTNUM, data = cav, qmatrix = twoway4.q,
                   hmodel=list(hmmCat(prob=c(1, 0, 0, 0)), hmmCat(prob=c(0, 1, 0, 0)), hmmCat(prob=c(0, 0, 1, 0)), hmmIdent()),
                   death = 4, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4908.81676837903, miscnew.msm$minus2loglik, tol=1e-06)))
miscnew.msm <- msm(state ~ years, subject = PTNUM, data = cav, qmatrix = twoway4.q, death = 4, fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4908.81676837903, miscnew.msm$minus2loglik, tol=1e-06)))

### Estimating initprobs
if (developer.local)
  miscnew.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                     qmatrix = oneway4.q, death = 4,
                     hmodel=list(
                       hmmCat(prob=c(0.9, 0.1, 0, 0)),
                       hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
                       hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent()),
                     est.initprobs=TRUE,
                     control = list(trace=1, REPORT=1), method="BFGS"
                     )



cat("miscnew.R: ALL TESTS PASSED\n")

