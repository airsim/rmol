source("local.R")

library(msm)
# library(msm, lib.loc="../../lib/sun/0.7.5")
data(cav)
twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166), c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
oneway4.q <- rbind(c(0, 0.148, 0, 0.0171), c(0, 0, 0.202, 0.081), c(0, 0, 0, 0.126), c(0, 0, 0, 0))
rownames(oneway4.q) <- colnames(oneway4.q) <- c("Well","Mild","Severe","Death")
ematrix <- rbind(c(0, 0.1, 0, 0),c(0.1, 0, 0.1, 0),c(0, 0.1, 0, 0),c(0, 0, 0, 0))

## n=3268, means 0.34088127 0.07772338 
## cav2 has 3264 rows

## Basic test - CAV with changepoints at 5 or 5+10 years 

cav5.msm <- msm( state ~ years, subject=PTNUM, data = cav,
               qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE, pci = c(5), covinits = list("timeperiod[5,Inf)"=rep(0.01,7)),
               )
stopifnot(isTRUE(all.equal(4905.59585756786, cav5.msm$minus2loglik, tol=1e-06)))
cav10.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = TRUE, pci = c(5,10), fixedpars=TRUE, 
                 covinits = list("timeperiod[5,10)"=rep(0.01,7), "timeperiod[10,Inf)"=rep(0.01,7)), 
                 )
stopifnot(isTRUE(all.equal(4905.28758421853, cav10.msm$minus2loglik, tol=1e-06)))

if (developer.local) {
    cav5.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                    qmatrix = twoway4.q, death = TRUE, pci = c(5), covinits = list("timeperiod[5,Inf)"=rep(0.01,7)), 
                    method="BFGS", control=list(trace=5, REPORT=1))
    stopifnot(isTRUE(all.equal(3919.99601396194, cav5.msm$minus2loglik, tol=1e-06)))
    cav10.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                     qmatrix = twoway4.q, death = TRUE, pci = c(5,10),
                     covinits = list("timeperiod[5,10)"=rep(0.01,7), "timeperiod[10,Inf)"=rep(0.01,7)), 
                     method="BFGS", control=list(trace=5, REPORT=1))
    stopifnot(isTRUE(all.equal(3882.08834017773, cav10.msm$minus2loglik, tol=1e-06)))
}

## Compare with old method - create artificial covariate

options(width=150)
cav$maxtime <- tapply(cav$years, cav$PTNUM, max)[as.character(cav$PTNUM)]
#cav.extra <- cav[cav$years==0 & !(cav$PTNUM %in% cav$PTNUM[cav$years==5]) & cav$maxtime > 5,]
cav.extra <- cav[cav$years==0  & cav$maxtime >= 5,]
cav.extra$years <- 5
cav.extra$state <- 99
#cav.extra10 <- cav[cav$years==0 & !(cav$PTNUM %in% cav$PTNUM[cav$years==10]) & cav$maxtime > 10,]
cav.extra10 <- cav[cav$years==0 & cav$maxtime >= 10,]
cav.extra10$years <- 10
cav.extra10$state <- 999
cav2 <- rbind(cav, cav.extra, cav.extra10)
cav2 <- cav2[order(cav2$PTNUM, cav2$years),]
cav2$after5 <- ifelse(cav2$years>=5 & cav2$years<10, 1, 0)
cav2$after10 <- ifelse(cav2$years>=10, 1, 0)
cav2$after510 <- as.numeric(cav2$after5 | cav2$after10)

cav$pdiag3 <- cav$pdiag
cav$pdiag3[!cav$pdiag %in% c("IDC","IHD")] <- "Other"
cav$pdiag3 <- factor(cav$pdiag3)

cav5.msm <- msm( state ~ years, subject=PTNUM, data = cav2[cav2$state!=999,],
                qmatrix = twoway4.q, death = TRUE, covariates = ~ after510, 
                censor=99, censor.states=list(1:4), covinits=list(after510=rep(0.01,7)), 
                fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4905.58684722393, cav5.msm$minus2loglik, tol=1e-06)))

cav10.msm <- msm( state ~ years, subject=PTNUM, data = cav2,
                 qmatrix = twoway4.q, death = TRUE, covariates = ~ after5 + after10, censor=c(99, 999), censor.states=list(1:4,1:4),
                 covinits=list(after5=rep(0.01,7), after10=rep(0.01,7)), 
                 fixedpars=TRUE)
stopifnot(isTRUE(all.equal(4905.27634460236, cav10.msm$minus2loglik, tol=1e-06)))

## Make sure works for pci outside time range, with warning
cav5.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE, pci = c(-1,5,50,60), covinits = list("timeperiod[5,Inf)"=rep(0.01,7)), 
                method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4905.59585756786, cav5.msm$minus2loglik, tol=1e-06)))

## No cuts left , degrades to time homogeneous model 
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav,
                 qmatrix = twoway4.q, death = TRUE, fixedpars=TRUE, pci = c(-1,50,60),
                 method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4908.81676835902, cav.msm$minus2loglik, tol=1e-06)))

## Use approx 10% sample of CAV data for further testing. 

set.seed(22061976)
subs <- cav$PTNUM %in% sample(unique(cav$PTNUM), 50)
cavsub <- subset(cav, subs)
cavsub$maxtime <- tapply(cavsub$years, cavsub$PTNUM, max)[as.character(cavsub$PTNUM)]
cavsub.extra <- cavsub[cavsub$years==0 & cavsub$maxtime >= 5,]
cavsub.extra$years <- 5
cavsub.extra$state <- 99
cavsub.extra10 <- cavsub[cavsub$years==0 & cavsub$maxtime >= 10,]
cavsub.extra10$years <- 10
cavsub.extra10$state <- 999
cavsub2 <- rbind(cavsub, cavsub.extra, cavsub.extra10)
cavsub2 <- cavsub2[order(cavsub2$PTNUM, cavsub2$years),]
cavsub2$after5 <- ifelse(cavsub2$years>=5 & cavsub2$years<10, 1, 0)
cavsub2$after10 <- ifelse(cavsub2$years>=10, 1, 0)
cavsub2$after510 <- as.numeric(cavsub2$after5 | cavsub2$after10)

## Works in presence of other covs
cav5cov.msm <- msm( state ~ years, subject=PTNUM, data = cavsub,
                   qmatrix = twoway4.q, covariates = ~ pdiag3 + sex, death = TRUE, pci = c(5,10), fixedpars=TRUE, 
                   covinits = list("timeperiod[5,10)"=rep(0.01,7), "timeperiod[10,Inf)"=rep(0.01,7), pdiag3IHD=rep(0.01,7), pdiag3Other=rep(0.01,7)), 
                   )
stopifnot(isTRUE(all.equal(448.061973062940, cav5cov.msm$minus2loglik, tol=1e-06)))

cav5cov.msm <- msm( state ~ years, subject=PTNUM, data = cavsub2,
                 qmatrix = twoway4.q, death = TRUE, covariates = ~ pdiag3 + sex + after5 + after10,
                   censor=c(99,999), censor.states=list(1:4,1:4), 
                   covinits = list(after5=rep(0.01,7), after10=rep(0.01,7), pdiag3IHD=rep(0.01,7), pdiag3Other=rep(0.01,7)),
                   fixedpars=TRUE
                   )
stopifnot(isTRUE(all.equal(448.061973062940, cav5cov.msm$minus2loglik, tol=1e-06)))

## uncentered covs 
cav5cov.msm <- msm( state ~ years, subject=PTNUM, data = cavsub,
                   qmatrix = twoway4.q, covariates = ~ pdiag3 + sex, death = TRUE, pci = c(5,10), fixedpars=TRUE, center=FALSE, 
                   covinits = list("timeperiod[5,10)"=rep(0.01,7), "timeperiod[10,Inf)"=rep(0.01,7), pdiag3IHD=rep(0.01,7), pdiag3Other=rep(0.01,7)), 
                   )
stopifnot(isTRUE(all.equal(449.691983558378, cav5cov.msm$minus2loglik, tol=1e-06)))

cav5cov.msm <- msm( state ~ years, subject=PTNUM, data = cavsub2,
                 qmatrix = twoway4.q, death = TRUE, covariates = ~ pdiag3 + sex + after5 + after10,
                   censor=c(99,999), censor.states=list(1:4,1:4),  center=FALSE, 
                   covinits = list(after5=rep(0.01,7), after10=rep(0.01,7), pdiag3IHD=rep(0.01,7), pdiag3Other=rep(0.01,7)),
                   fixedpars=TRUE
                   )
stopifnot(isTRUE(all.equal(449.691983558378, cav5cov.msm$minus2loglik, tol=1e-06)))


## Works with other censored states
cav.cens <- cav
cav.cens$state[cav.cens$state==4][1:50] <- 99
cav5cens.msm <- msm(state ~ years, subject=PTNUM, data = cav.cens,
                    qmatrix = twoway4.q, death = TRUE, censor=99, pci = 5,
                    covinits=list("timeperiod[5,Inf)"=rep(0.02,7)), fixedpars=TRUE, 
                    method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4753.53207003774, cav5cens.msm$minus2loglik, tol=1e-06)))

cav2.cens <- cav2[cav2$state!=999,]
cav2.cens$state[cav2.cens$state==4][1:50] <- 998
cav52cens.msm <- msm(state ~ years, subject=PTNUM, data = cav2.cens,
                     qmatrix = twoway4.q, death = TRUE, covariates = ~ after510,
                     covinits=list(after510=rep(0.02,7)), fixedpars=TRUE, center=FALSE, 
                     censor=c(99,998), censor.states=list(1:4,1:3),
                     method="BFGS", control=list(trace=5, REPORT=1))
stopifnot(isTRUE(all.equal(4753.53207003774, cav5cens.msm$minus2loglik, tol=1e-06)))


## test bootstrap with factor / other covs
if (developer.local) { 
    cav5cov.msm <- msm( state ~ years, subject=PTNUM, data = cavsub,
                       qmatrix = twoway4.q, covariates = ~ pdiag3, death = TRUE, pci = c(5,10), 
                       method="BFGS", control=list(trace=5, REPORT=1))

    pmatrix.msm(cav5cov.msm)
    pmatrix.msm(cav5cov.msm, ci="boot", B=3 )
    try(pmatrix.msm(cav5cov.msm, ci="norm", B=3 ) ) # hasn't converged 

    ## pearson with factor / other covs.
    pearson.msm(cav5cov.msm, covgroups = 3)
    pearson.msm(cav5cov.msm, covgroups = 3, boot=TRUE, B=3)

    ## Constraints just work using same syntax with "timeperiod" name
    cav5con.msm <- msm( state ~ years, subject=PTNUM, data = cavsub,
                       qmatrix = twoway4.q, constraint = list("timeperiod[5,10)"=rep(1,7),"timeperiod[10,Inf)"=rep(1,7)),
                       death = TRUE, pci = c(5,10), center=TRUE, # center=FALSE, # default
                       method="BFGS", control=list(trace=5, REPORT=1))
    cav5con.msm
}

## Misccovs
misccov.msm <- msm(state ~ years, subject = PTNUM, data = cav,
                   qmatrix = oneway4.q, ematrix=ematrix, death = 4, fixedpars=TRUE,
                   pci = 5, covinits=list("timeperiod[5,Inf)"=rep(0.0001,5)),
                   misccovariates = ~dage + sex, misccovinits = list(dage=c(0.01,0.02,0.03,0.04), sex=c(-0.013,-0.014,-0.015,-0.016)),
                   control = list(trace=1, REPORT=1), method="BFGS")
stopifnot(isTRUE(all.equal(4305.03335375452, misccov.msm$minus2loglik, tol=1e-06)))

## hcovs 
data(fev)
three.q <- rbind(c(0, exp(-6), exp(-9)), c(0, 0, exp(-6)), c(0, 0, 0))
hmodel3 <- list(hmmNorm(mean=100, sd=16), hmmNorm(mean=54, sd=18), hmmIdent(999))
(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                 hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                 pci = c(365, 730),
                 covinits = list("timeperiod[365,730)"=rep(0.01,3), "timeperiod[730,Inf)"=rep(0.01,3)), 
                 hconstraint = list(acute = c(1,1)),
                 fixedpars=TRUE, center=FALSE))

## icovs
(fev3.hid <- msm(fev ~ days, subject=ptnum, data=fev, qmatrix=three.q, death=3, hmodel=hmodel3,
                 hcovariates=list(~acute, ~acute, NULL), hcovinits = list(-8, -8, NULL),
                 initcovariates = ~ I(fev<100),                 
                 pci = c(365, 730),
                 covinits = list("timeperiod[365,730)"=rep(0.01,3), "timeperiod[730,Inf)"=rep(0.01,3)), 
                 hconstraint = list(acute = c(1,1)),
                 fixedpars=TRUE, center=FALSE))
