source("local.R")
library(msm)
data(fev)

### TESTS FOR HIDDEN MARKOV MODELS WITH CONTINUOUS RESPONSES
### USING LUNG TRANSPLANT FEV1 DATA

three.q <- rbind(c(0, exp(-6), exp(-9)), c(0, 0, exp(-6)), c(0, 0, 0))

four.q <-  rbind(c(0, exp(-6), 0, exp(-9)), c(0, 0, exp(-6.01), exp(-9)), c(0, 0, 0, exp(-6.02)), c(0, 0, 0, 0))

five.q <-  rbind(c(0, exp(-6), 0, 0, exp(-9)),
                 c(0, 0, exp(-6.01), 0, exp(-9)),
                 c(0, 0, 0, exp(-6.02), exp(-6.03)),
                 c(0, 0, 0, 0, exp(-6.04)),
                 c(0, 0, 0, 0, 0))

## One-level model

hmodel3 <- list(hmmNorm(mean=100, sd=16), hmmNorm(mean=54, sd=18), hmmIdent(999))
hmodel4 <- list(hmmNorm(mean=100, sd=16), hmmNorm(mean=72.5, sd=10), hmmNorm(mean=42.5, sd=18), hmmIdent(999))
hmodel5 <- list(hmmNorm(mean=100, sd=16), hmmNorm(mean=72.5, sd=10), hmmNorm(mean=62.5, sd=10), hmmNorm(mean=42.5, sd=18), hmmIdent(999))

(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3, fixedpars=TRUE))
stopifnot(isTRUE(all.equal(52388.7381942858, fev3.hid$minus2loglik, tol=1e-06)))

(fev4.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=four.q, death=4, hmodel=hmodel4, fixedpars=TRUE))
stopifnot(isTRUE(all.equal(50223.9497625937, fev4.hid$minus2loglik, tol=1e-06)))

(fev5.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=five.q, death=5, hmodel=hmodel5, fixedpars=TRUE))
stopifnot(isTRUE(all.equal(49937.9840668066, fev5.hid$minus2loglik, tol=1e-06)))

## test new obstrue facility. death states are observed exactly.
fev$obstrue <- as.numeric(fev$fev==999)
fev$fev2 <- fev$fev; fev$fev2[fev$obstrue==1] <- 3
hmodel32 <- list(hmmNorm(mean=100, sd=16), hmmNorm(mean=54, sd=18), hmmIdent(3))
(fev3.hid <- msm(fev2 ~ days, subject=ptnum, obstrue=obstrue, data=fev, qmatrix=three.q, death=3, hmodel=hmodel32, fixedpars=TRUE))
stopifnot(isTRUE(all.equal(52388.7381942858, fev3.hid$minus2loglik, tol=1e-06)))

## One-level model with covariate on response - indicator for acute events within 14 days

(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                 hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                 hconstraint = list(acute = c(1,1)),
                 fixedpars=TRUE, center=FALSE))
stopifnot(isTRUE(all.equal(52134.2372359988, fev3.hid$minus2loglik, tol=1e-06)))

(fev4.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=four.q, death=4, hmodel=hmodel4,
                 hcovariates=list(~acute, ~acute, ~acute, NULL), hcovinits = list(-8, -8, -8, NULL),
                 hconstraint = list(acute = c(1,1,1)),
                 fixedpars=TRUE, center=FALSE))
stopifnot(isTRUE(all.equal(50095.8606697016, fev4.hid$minus2loglik, tol=1e-06)))

(fev5.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=five.q, death=5, hmodel=hmodel5,
                 hcovariates=list(~acute, ~acute, ~acute, ~acute, NULL), hcovinits = list(-8, -8, -8, -8, NULL),
                 hconstraint = list(acute = c(1,1,1,1)),
                 fixedpars=TRUE, center=FALSE))
stopifnot(isTRUE(all.equal(49839.1627881087, fev5.hid$minus2loglik, tol=1e-06)))

## Two-level Satten and Longini model

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

(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3, fixedpars=TRUE))
stopifnot(isTRUE(all.equal(52567.734400762, fev3.hid$minus2loglik, tol=1e-06)))

(fev4.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=four.q, death=4, hmodel=hmodel4, fixedpars=TRUE))
stopifnot(isTRUE(all.equal(50202.2171575953, fev4.hid$minus2loglik, tol=1e-06)))

(fev5.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=five.q, death=5, hmodel=hmodel5, fixedpars=TRUE))
stopifnot(isTRUE(all.equal(49308.4942559547, fev5.hid$minus2loglik, tol=1e-06)))


## Two-level Satten and Longini model with acute event covariate on the measurement error model

(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                 hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                 fixedpars=TRUE, center=FALSE))
stopifnot(isTRUE(all.equal(52219.7372318393, fev3.hid$minus2loglik, tol=1e-06)))

(fev4.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=four.q, death=4, hmodel=hmodel4,
                 hcovariates=list(~acute, ~acute, ~acute, NULL), hcovinits = list(-8, -8, -8, NULL),
                 fixedpars=TRUE, center=FALSE))
stopifnot(isTRUE(all.equal(49933.2168265887, fev4.hid$minus2loglik, tol=1e-06)))

(fev5.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=five.q, death=5, hmodel=hmodel5,
                 hcovariates=list(~acute, ~acute, ~acute, ~acute, NULL), hcovinits = list(-8, -8, -8, -8, NULL),
                 fixedpars=TRUE, center=FALSE))
stopifnot(isTRUE(all.equal(49167.8668910928, fev5.hid$minus2loglik, tol=1e-06)))


#### MODELS ACTUALLY FITTED. These are the two models presented in the manual.

### On some platforms (not bumblebee) doesn't converge (no SEs) with days - use months instead.

if (developer.local) {

    three.q <- rbind(c(0, exp(-6), exp(-9)), c(0, 0, exp(-6)), c(0, 0, 0))
    months <- fev$days * 12 / 365
    hmodel1 <- list(hmmNorm(mean=100, sd=16), hmmNorm(mean=54, sd=18), hmmIdent(999))
    (fev1.msm <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel1,
                     hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                     hconstraint = list(acute = c(1,1)),
                     fixedpars=FALSE, center=FALSE, method="BFGS", control=list(trace=1, REPORT=1)))
    stopifnot(isTRUE(all.equal(51597.8909140275, fev1.msm$minus2loglik, tol=1e-06)))
##    stopifnot(isTRUE(all.equal(51600.522477903, fev1.msm$minus2loglik, tol=1e-06)))  # with NM alg

    if (interactive()) save(fev1.msm, file="~/msm/devel/models/fev1.msm.rda")

    hmodel2 <- list(hmmMETNorm(mean=100, sd=16, sderr=8, lower=80, upper=Inf, meanerr=0),
                    hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                    hmmIdent(999))
    (fev2.msm <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel2,
                     hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                     hconstraint = list(sderr = c(1,1), acute = c(1,1)),
                     method="BFGS", control=list(trace=3, REPORT=1),
                     fixedpars=FALSE))
##    stopifnot(isTRUE(all.equal(50950.3548197944, fev2.msm$minus2loglik, tol=1e-06))) ## ??
##    stopifnot(isTRUE(all.equal(51445.9726641155, fev2.msm$minus2loglik, tol=1e-06))) ## with center=FALSE
    stopifnot(isTRUE(all.equal(51411.1704398278, fev2.msm$minus2loglik, tol=1e-06))) ## with center=TRUE.

    if (interactive()) save(fev2.msm, file="~/msm/devel/models/fev2.msm.rda")

#    hmodel3 <- list(hmmNorm(mean=100, sd=16), hmmNorm(mean=54, sd=18), hmmIdent(999))
#    (fev2.msm <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
#                     hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
#                     hconstraint = list(sderr = c(1,1), acute = c(1,1)),
#                     method="BFGS", control=list(trace=3, REPORT=1),
#                     fixedpars=FALSE))
#    stopifnot(isTRUE(all.equal(51411.1704398273, fev2.msm$minus2loglik, tol=1e-06)))



#########  OUTPUT FUNCTIONS FOR HIDDEN MARKOV MODELS  ############################

    if (interactive()) load(file="~/msm/devel/models/fev1.msm.rda")
    if (interactive()) load(file="~/msm/devel/models/fev2.msm.rda")

    q <- qmatrix.msm(fev1.msm)
    stopifnot(isTRUE(all.equal(0.000801187880305464, q$estimates[2,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(9.58183762450542e-05, q$SE[2,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.000633774251918255, q$L[2,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(0.00101282438913463, q$U[2,3], tol=1e-06)))

    soj <- sojourn.msm(fev1.msm)
    stopifnot(isTRUE(all.equal(c(1420.72074451740, 1248.14668891239, 122.388402735689, 149.272588848484, 1200.00130050446, 987.337993365677, 1682.03770533710, 1577.8488901581), as.numeric(unlist(soj)), tol=1e-06)))

    p <- pmatrix.msm(fev1.msm, 10)
    stopifnot(isTRUE(all.equal(0.00078422374144033, p[1,3], tol=1e-06)))

    q <- qratio.msm(fev1.msm, c(1,2), c(2,3), cl=0.99)
    stopifnot(isTRUE(all.equal(c(0.783436818353553, 0.116122835486391, 0.534801142340726, 1.14766630016078), as.numeric(q), tol=1e-06)))

    p <- prevalence.msm(fev1.msm)
    stopifnot(isTRUE(all.equal(68, p$Observed[5,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(56.5227543655685, p$Expected[5,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(63.5593220338983, p$"Observed percentages"[6,3], tol=1e-06)))
    stopifnot(isTRUE(all.equal(52.6044241323229, p$"Expected percentages"[6,3], tol=1e-06)))

    if (interactive()) plot.msm(fev1.msm)

    stopifnot(isTRUE(all.equal(c(1,2), as.numeric(transient.msm(fev1.msm)), tol=1e-06)))

    stopifnot(isTRUE(all.equal(3, as.numeric(absorbing.msm(fev1.msm)), tol=1e-06)))

    tot <- totlos.msm(fev1.msm)
    stopifnot(isTRUE(all.equal(c(1420.72075298143, 1113.04493977146), as.numeric(tot), tol=1e-06)))

    stopifnot(isTRUE(all.equal(-25798.9454570137, as.numeric(logLik.msm(fev1.msm)), tol=1e-06)))


### example of Viterbi algorithm in the PDF manual

    keep <- fev$ptnum==1 & fev$fev<999
    vit <- viterbi.msm(fev1.msm)[keep,]
    print(max1 <- max(vit$time[vit$fitted==1]))
    print(min2 <- min(vit$time[vit$fitted==2]))
    stopifnot(isTRUE(all.equal(2406, max1)))
    stopifnot(isTRUE(all.equal(2433, min2)))
    if (interactive())  {
        plot(fev$days[keep], fev$fev[keep], type="l", ylab=expression(paste("% baseline ", FEV[1])), xlab="Days after transplant")
        abline(v = mean(max1,min2), lty=2)
        text(max1 - 500, 50, "STATE 1")
        text(min2 + 500, 50, "STATE 2")
    }
}

### Estimating initprobs.
if (developer.local) {
#    months <- fev$days/365.25*12
#    (fev3.hid <- msm(fev ~ months, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3, est.initprobs=TRUE)) # no SEs
#    (fev3.hid <- msm(fev ~ months, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
#                     hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
#                     hconstraint = list(acute = c(1,1)),
#                     est.initprobs=TRUE, center=FALSE)) # no SEs
    hmodel3 <- list(hmmMETNorm(mean=100, sd=16, sderr=8, lower=80, upper=Inf, meanerr=0),
                    hmmMETNorm(mean=54, sd=18, sderr=8, lower=0, upper=80, meanerr=0),
                    hmmIdent(999))
    (fev3.hid <- msm(fev ~ months, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3, est.initprobs=TRUE, method="BFGS",control=list(trace=1,REPORT=1))) # OK
}

cat("fev.R: ALL TESTS PASSED\n")
