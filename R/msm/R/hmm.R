### FUNCTIONS FOR HIDDEN MARKOV MODELS IN CONTINUOUS TIME
### WITH ARBITRARY RESPONSE DISTRIBUTION

print.hmmdist <- function(x, ...)
  {
      cat("Hidden Markov model", x$label, "distribution\n\n")
      pnames <- if(x$label=="categorical") paste("P(",seq(x$pars[1]),")",sep="") else names(x$pars)
      pars <- if(x$label=="categorical") x$pars[3:(2+x$pars[1])] else x$pars
      cat("Parameters: ", paste(paste(pnames, pars, sep=" = "), collapse=", "))
      cat("\n")
  }

msm.check.hmodel <- function(hmodel, nstates)
  {
      if (is.null(hmodel)) stop("Hidden model not specified")
      if (!is.list(hmodel)) stop("Hidden model should be a list")
      if (length(hmodel) != nstates) stop("hmodel of length ", length(hmodel), ", expected ", nstates)
      for (i in hmodel) {
          if (class(i) != "hmmdist") stop("hmodel should be a list of HMM distribution objects")
      }
  }

msm.check.hcovariates <- function(hcovariates, qmodel)
  {
      if (!is.list(hcovariates)) stop("hcovariates should be a list")
      if (length(hcovariates) != qmodel$nstates)
        stop("hcovariates of length ", length(hcovariates), ", expected ", qmodel$nstates)
      for (i in hcovariates) {
          if (!is.null(i) )
            if ( class(i) != "formula") stop("hcovariates should be a list of formulae or NULLs")
      }
  }

msm.form.hmodel <- function(hmodel, hconstraint=NULL, initprobs=NULL, est.initprobs, qmodel)
  {
      nst <- length(hmodel)
      if (is.null(initprobs))
          initprobs <- if (est.initprobs) rep(1/nst, nst) else c(1, rep(0, nst-1))
      else {
          if (!is.numeric(initprobs)) stop("initprobs should be numeric")
          if (length(initprobs) != nst) stop("initprobs of length ", length(initprobs), ", should be ", nst)
          initprobs <- initprobs / sum(initprobs)
      }
      nipars <- nst - 1
      labels <- sapply(hmodel, function(x) x$label)
      models <- match(labels, .msm.HMODELS)
      pars <- lapply(hmodel, function(x) x$pars)
      plabs <- lapply(hmodel, function(x) names(x$pars))
      ## where non-misclassified outcome for hmmIdent distribution is not specified, this is
      ## just the state
      pars[labels=="identity"][sapply(pars[labels=="identity"], length) == 0] <- which(labels=="identity")
      plabs[labels=="identity"] <- "which"
      names(plabs) <- paste("state", 1:nst, sep=".")
      npars <- sapply(pars, length)
      links <- lapply(hmodel, function(x) x$link)
      links <- match(links, .msm.LINKFNS)
      parstate <- rep(1:nst, npars)
      firstpar <- c(0, cumsum(npars)[-qmodel$nstates])
      pars <- unlist(pars)
      plabs <- unlist(plabs)
      locpars <- which(plabs == rep(.msm.LOCPARS[labels], npars))
      names(pars) <- plabs
      hmod <- list(hidden=TRUE, nstates=qmodel$nstates, fitted=FALSE, models=models, labels=labels,
                   npars=npars, nipars=nipars, totpars=sum(npars), pars=pars, plabs=plabs, parstate=parstate,
                   firstpar=firstpar, links=links, locpars=locpars, initprobs=initprobs)
      class(hmod) <- "hmodel"
      hmod
  }

msm.form.hcmodel <- function(hmodel, hcovdata, hcovinits, hconstraint)
  {
      nst <- hmodel$nstates
      ncovs <- if (is.null(hcovdata)) rep(0, nst) else sapply(hcovdata, function(x) x$ncovs)
      ncovs2 <- rep(rep(0, nst), hmodel$npars)
      ncovs2[hmodel$locpars] <- ncovs[hmodel$parstate[hmodel$locpars]]
      coveffstate <- rep(1:nst, tapply(ncovs2, hmodel$parstate, sum))
      if (is.null(hcovinits)){
          coveffect <- rep(0, sum(ncovs2))
      }
      else {
          if (!(sum(ncovs2) == length(unlist(hcovinits)))) {
              warning("Initial values for hidden covariate effects do not match numbers of covariates, ignoring")
              coveffect <- rep(0, sum(ncovs2))
          }
          coveffect <- unlist(hcovinits)
          if (!is.numeric(coveffect)) {
              warning("hcovinits should be numeric")
              coveffect <- rep(0, sum(ncovs2))
          }
      }
      covlabels <- lapply(hcovdata, function(x) x$covlabels)
      covlabels <- unlist(covlabels[hmodel$parstate[hmodel$locpars]])
      names(coveffect) <- covlabels
      hcmod <- list(ncovs=ncovs2, coveffect=coveffect, covlabels=covlabels,
                    coveffstate=coveffstate, ncoveffs=length(coveffect))
      hmodel <- c(hmodel, hcmod)
      hmodel$plabs[hmodel$plabs=="hcov"] <- paste("hcov.",covlabels,sep="")
      whichcovh <- lapply(hcovdata, function(x) x$whichcov) # factor contrasts as separate covariates
      hmodel$whichcovh <- unlist(rep(whichcovh, tapply(ncovs2>0, hmodel$parstate, sum)))
      whichcovh.orig <- lapply(hcovdata, function(x) x$whichcov.orig) # factors considered as one variable 
      hmodel$whichcovh.orig <- unlist(rep(whichcovh.orig, tapply(ncovs2>0, hmodel$parstate, sum)))
      class(hmodel) <- "hmodel"
      hmodel
  }

msm.form.icmodel <- function(hmodel, icovdata, icovinits) {
  nst <- hmodel$nstates
  nicovs <- if (is.null(icovdata)) 0 else icovdata$ncovs # distinct covariates
  nicovs <- rep(nicovs, nst-1)
  nicovs[hmodel$initprobs[-1] == 0] <- 0 # don't estimate cov effects on probs which are fixed to zero
  if (is.null(icovinits))
    icoveffect <- rep(0, sum(nicovs))
  else {
      icoveffect <- unlist(icovinits)
      if (!(length(icoveffect) == sum(nicovs))) {
          warning("Initial values for initial state covariate effects do not match numbers of covariates, ignoring")
          icoveffect <- rep(0, sum(nicovs))
      }
      else if (!is.numeric(icoveffect)) {
          warning("icovinits should be numeric")
          icoveffect <- rep(0, sum(nicovs))
      }
  }
  names(icoveffect) <- rep(icovdata$covlabels, each=sum(nicovs>0))
  icmod <- list(nicovs=nicovs, icoveffect=icoveffect,
                nicoveffs=length(icoveffect), whichcovi=icovdata$whichcov)
  hmodel <- c(hmodel, icmod)
  class(hmodel) <- "hmodel"
  hmodel
}

## Convert old-style misclassification model specification to a new-style HMM with categorical response

msm.emodel2hmodel <- function(emodel, qmodel)
  {
      nst <- qmodel$nstates
      if (emodel$misc) {
          hidden <- TRUE
          nepars <- rowSums(emodel$imatrix)
          npars <- ifelse(nepars > 0, 2 + nst, 1)
          models <- ifelse(nepars > 0, 1, 2)
          pars <- plabs <- vector(nst, mode="list")
          parstate <- rep(1:nst, npars)
          names(pars) <- names(plabs) <- paste("state", 1:nst, sep=".")
          for (i in seq(nst)) {
              if (models[i]==1) {
                  ppars <- emodel$ematrix[i,]
                  plab <- rep("p", nst)
                  plab[ppars==0] <- "p0"
                  plab[i] <- "pbase"
                  plabs[[i]] <- c("ncats", "basecat", plab)
                  ## Baseline category is the probability of no misclassification (diagonal of ematrix)
                  pars[[i]] <- c(nst, i, ppars)
              }
              else {
                  plabs[[i]] <- "which"
                  pars[[i]] <- i
              }
          }
          firstpar <- c(0, cumsum(npars)[-qmodel$nstates])
          pars <- unlist(pars)
          plabs <- unlist(plabs)
          names(pars) <- plabs
          links <- ifelse(models==1, "log", "identity")
          links <- match(links, .msm.LINKFNS)
          labels <- .msm.HMODELS[models]
          locpars <- which(plabs == rep(.msm.LOCPARS[labels], npars))

          hmod <- list(hidden=TRUE, fitted=FALSE, nstates=nst, models=models, labels=labels,
                       npars=npars, totpars=sum(npars), links=links, locpars=locpars,
                       pars=pars, plabs=plabs, parstate=parstate, firstpar=firstpar, nipars=emodel$nipars, initprobs=emodel$initprobs)
          hmod$constr <- msm.econstr2hconstr(emodel$constr, hmod)
      }
      else {
          hmod <- list(hidden=FALSE, fitted=FALSE, models=rep(0, qmodel$nstates), npars=0, ndpars=0)
      }
      class(hmod) <- "hmodel"
      hmod
  }

msm.misccov2hcov <- function(misccovariates, emodel)
  {
      nst <- nrow(emodel$imatrix)
      whichst <- rep(1:nst, rowSums(emodel$imatrix))
      hcov <- vector(nst, mode="list")
      for (i in 1:nst) {
          if (!any(whichst==i)) hcov[[i]] <-  ~ 1
          else hcov[[i]] <- misccovariates
      }
      hcov
  }

msm.misccovinits2hcovinits <- function(misccovinits, hcovariates, emodel, ecmodel)
  {
      nst <- nrow(emodel$imatrix)
      whichst <- rep(1:nst, rowSums(emodel$imatrix))
      hcovinits <- vector(nst, mode="list")
      for (i in 1:nst) {
          if (is.null(misccovinits)) hcovinits[[i]] <- rep(0, ecmodel$ncovs * rowSums(emodel$imatrix)[i])
          else if (!any(whichst==i)) hcovinits[[i]] <- numeric(0)
          else hcovinits[[i]] <- as.vector(t(sapply(misccovinits, function(x)x[whichst==i])))
      }
      hcovinits
  }

msm.econstr2hconstr <- function(econstr, hmodel)
  {
      constr <- seq(length=hmodel$totpars)
      for (i in unique(econstr)) {
          constr[hmodel$plabs == "p"][econstr == i] <-
            min(constr[hmodel$plabs == "p"][econstr == i])
      }
      constr
  }

print.hmodel <- function(x, ...)
  {
      ci <- (x$fitted && x$foundse)
      cols <- if (ci) c("Estimate","LCL","UCL") else ("")
      if (!x$hidden)
        cat("Non-hidden Markov model\n")
      else {
          cat("Hidden Markov model, ")
          nst <- length(x$models)
          cat(nst, "states\n")
          cat("Initial state occupancy probabilities:")
          if (x$nipars > 0) {
            cat("\n")
            print(x$initprobs)
            cat("\n")
            if (any(x$nicovs > 0)) {
              cat("Covariates on log odds of initial states relative to state 1\n")
              print(x$icoveffect)
            }
            cat("\n")
          }
          else cat(paste(x$initprobs, collapse=","), "\n\n")
          for (i in 1:nst) {
              cat("State", i, "-", x$labels[i], "distribution\n")
              cat("Parameters: \n")
              if (x$label[i]=="categorical")
                pars <- print.hmmcat(x, i)
              else {
                  pars <- as.matrix(x$pars[x$parstate==i])
                  if (ci) pars <- cbind(pars, matrix(x$ci[x$parstate==i ,], ncol=2))
                  dimnames(pars) <- list(x$plabs[x$parstate==i], cols)
              }
              if (any(x$ncovs[x$parstate==i] > 0)){
                  coveffs <- as.matrix(x$coveffect[x$coveffstate==i])
                  if (ci) coveffs <- cbind(coveffs, matrix(x$covci[x$coveffstate==i,], ncol=2))
                  rownames(coveffs) <- x$covlabels[x$coveffstate==i]
                  pars <- rbind(pars, coveffs)
              }
              print(pars)
              cat("\n")
          }
      }
  }

print.hmmcat <- function(x, i)
{
    pars <- x$pars[x$parstate==i]
    res <- matrix(pars[3:(2+pars[1])], ncol=1)
    rownames(res) <- paste("P(",seq(length=pars[1]),")",sep="")
    if (x$fitted && x$foundse) {
        ci <- matrix(x$ci[x$parstate==i,], ncol=2)
        res <- cbind(res,  ci[3:(2+pars[1]),])
        colnames(res) <- c("Estimate","LCL","UCL")
    }
    else colnames(res) <- "prob"
    res
}

msm.form.hconstraint <- function(constraint, hmodel)
  {
      constr <- seq(length=hmodel$totpars)
      for (con in names(constraint)) {
          if ( ! (con %in% c(hmodel$plabs, hmodel$covlabels)))
            stop("parameter \"", con, "\" in hconstraint unknown")
          if (con %in% hmodel$plabs) {
              tc <- constraint[[con]]
              np <- length(tc)
              if (np != sum(hmodel$plabs==con))
                stop("constraint for \"", con, "\" of length ",
                     np, ", should be ", sum(hmodel$plabs==con))
              for (i in unique(tc))
                constr[hmodel$plabs == con][tc == i] <-
                  min(constr[hmodel$plabs == con][tc == i])
          }
      }
      match(constr, unique(constr))
  }

msm.form.hcovconstraint <- function(constraint, hmodel)
  {
      constr <- seq(length=hmodel$ncoveffs)
      for (con in names(constraint)) {
          if ( ! (con %in% c(hmodel$plabs, hmodel$covlabels)))
            stop("parameter \"", con, "\" in hconstraint unknown")
          if (con %in% hmodel$covlabels) {
              tc <- constraint[[con]]
              np <- length(tc)
              if (np != sum(hmodel$covlabels==con))
                stop("constraint for \"", con, "\" of length ",
                     np, ", should be ", sum(hmodel$covlabels==con))
              for (i in unique(tc))
                constr[hmodel$covlabels == con][tc == i] <-
                  min(constr[hmodel$covlabels == con][tc == i])
          }
      }
      match(constr, unique(constr))
  }
