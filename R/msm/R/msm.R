### Function to fit Markov multi-state models in continuous time
### with either arbitrary observation times or observed exact transition times
### with or without misclassification between true and underlying states

msm <- function(formula,   # formula with  observed Markov states   ~  observation times (required)
                subject = NULL, # optional, defaults to all the same if not given
                data=list(),       # data frame in which to interpret variable names
                qmatrix,    # matrix of 1s and 0s with indices of allowed transitions (diagonal is ignored) (required)
                gen.inits = FALSE, # generate initial values for transition intensities using crudeinits.msm
                ematrix = NULL,    # matrix of 1s and 0s with indices of allowed misclassfications (diagonal is ignored) (required)
                hmodel = NULL,  # list of constructors for hidden emission distributions
                obstype = NULL, # optional, defaults to all 1 (snapshots) if not given
                obstrue = NULL, # for hidden Markov models, which observations represent the true state
                covariates = NULL, # formula specifying covariates on transition rates.
                covinits = NULL,      # initial values for covariate effects
                constraint = NULL, # which intensities have covariates on them (as in Marshall et al.)
                misccovariates = NULL, # formula specifying covariates on misclassification probs
                misccovinits = NULL,      # initial values for misclassification covariate effects
                miscconstraint = NULL, # which misc probs have covariates on them
                hcovariates = NULL, # list of formulae specifying covariates model for each hidden state
                hcovinits = NULL,      # initial values for covariate effects on hidden emission distribution
                hconstraint = NULL, # constraints on hidden Markov model parameters
                qconstraint = NULL, # constraints on equality of baseline intensities
                econstraint = NULL, # constraints on equality of baseline misc probs
                initprobs = NULL,  # initial state occupancy probabilities
                est.initprobs = FALSE, # should these be estimated, starting from the given values?
                initcovariates = NULL, # If these are specified, then assume est.initprobs=TRUE, and initprobs gives initial values with these covs set to zero.
                initcovinits = NULL,
                death = FALSE,  # 'death' states, ie, entry time known exactly, but unknown transient state at previous instant
                exacttimes = FALSE, # TRUE is shortcut for all obstype 2.
                censor = NULL,
                censor.states = NULL,
                pci = NULL,
                cl = 0.95, # width of confidence intervals
                fixedpars = NULL, # specify which parameters to fix. TRUE for all parameters
                center = TRUE, # center covariates at their means
                opt.method = c("optim","nlm"),
                hessian = TRUE,
                use.deriv = TRUE,
                analyticp = TRUE,
                ... # options to optim or nlm
                )
{
    if (missing(formula)) stop("state ~ time formula not given")
    subject <- if (missing(subject)) NULL else eval(substitute(subject), data, parent.frame())
    obstype <- if (missing(obstype)) NULL else eval(substitute(obstype), data, parent.frame())
    obstrue <- if (missing(obstrue)) NULL else eval(substitute(obstrue), data, parent.frame())
    if (missing(data)) data <- environment(formula)

### MODEL FOR TRANSITION INTENSITIES
    qmodel <- msm.form.qmodel(qmatrix, qconstraint, exacttimes, gen.inits, formula, subject, data, censor, censor.states, analyticp)

### MISCLASSIFICATION MODEL
    if (!missing(ematrix)) {
        emodel <- msm.form.emodel(ematrix, econstraint, initprobs, est.initprobs, qmodel)
    }
    else emodel <- list(misc=FALSE, npars=0, ndpars=0)

### GENERAL HIDDEN MARKOV MODEL
    if (!missing(hmodel)) {
        msm.check.hmodel(hmodel, qmodel$nstates)
        if (!missing(hcovariates)) msm.check.hcovariates(hcovariates, qmodel)
        hmodel <- msm.form.hmodel(hmodel, hconstraint, initprobs, est.initprobs, qmodel)
    }
    else {
        if (!missing(hcovariates)) stop("hcovariates have been specified, but no hmodel")
        hmodel <- list(hidden=FALSE, models=rep(0, qmodel$nstates), nipars=0, nicoveffs=0, totpars=0, ncoveffs=0) # might change later if misc
    }

### CONVERT OLD STYLE MISCLASSIFICATION MODEL TO NEW GENERAL HIDDEN MARKOV MODEL
    if (emodel$misc) {
        hmodel <- msm.emodel2hmodel(emodel, qmodel)
    }
    else emodel <- list(misc=FALSE, npars=0, ndpars=0, nipars=0, nicoveffs=0)

### DEATH STATES. Logical values allowed for backwards compatibility (TRUE means final state is death, FALSE means no death state)
    dmodel <- msm.form.dmodel(death, qmodel, hmodel)  # returns death, ndeath,
    if (dmodel$ndeath > 0 && qmodel$exacttimes) warning("Ignoring death argument, as all states have exact entry times")

### CENSORING MODEL
    cmodel <- msm.form.cmodel(censor, censor.states, qmodel$qmatrix)

    msmdata.obs <- msm.form.data(formula, subject, obstype, obstrue, covariates, data,
                                 hcovariates, misccovariates, initcovariates,
                                 qmodel, emodel, hmodel, cmodel, dmodel, exacttimes, center)
### EXPAND DATA AND MODEL FOR TIME DEPENDENT INTENSITIES 
    if (!is.null(pci)) { 
        tdmodel <- msm.pci(pci, msmdata.obs, qmodel, cmodel, center)
        if (is.null(tdmodel)) # supplied cut points not in range of data 
            pci <- NULL
        else { 
            cmodel <- tdmodel$cmodel
            msmdata.obs.orig <- msmdata.obs
            names(msmdata.obs.orig)[names(msmdata.obs.orig) %in% c("covmat","covmat.orig")] <- c("cov","cov.orig") # used in bootstrap
            msmdata.obs <- tdmodel$dat
        }
    }
    if (hmodel$hidden || (cmodel$ncens > 0)) {
        msmdata <- msm.aggregate.hmmdata(msmdata.obs)
        msmdata$fromstate <- msmdata$tostate <- msmdata$timelag <- numeric(0)
    }
    else {
        ## To speed calculation of the likelihood for the simple model (no
        ## HMM or censoring) data are aggregated by distinct fromstate,
        ## tostate, timelag, covariates combinations
        msmdata <- msm.obs.to.fromto(msmdata.obs)
        msm.check.model(msmdata$fromstate, msmdata$tostate, msmdata$obs, msmdata$subject, msmdata$obstype, qmodel$qmatrix, cmodel)
        msmdata <- msm.aggregate.data(msmdata)
        msmdata$subject <- msmdata$state <- msmdata$time <- numeric(0)
        for (i in c("subject", "time", "state", "n")) msmdata[[i]] <- msmdata.obs[[i]]
        msmdata$obstype.obs <- msmdata.obs$obstype
        msmdata$firstobs <- msmdata.obs$firstobs
    }
    if (is.null(pci)) {
      msmdata.obs.orig <- NULL
      msmdata$pci.imp <- rep(0, msmdata$n)
    }
    msmdata$cov <- msmdata.obs$covmat
    msmdata$cov.orig <- msmdata.obs$covmat.orig
    msmdata$covlabels.orig <- msmdata.obs$covlabels.orig
    
### MODEL FOR COVARIATES ON INTENSITIES
    qcmodel <-
        if (msmdata$covdata$ncovs > 0)
            msm.form.covmodel(msmdata$covdata, constraint, qmodel$npars, covinits)
        else {
            if (!is.null(constraint)) warning("constraint specified but no covariates")
            list(npars=0, ncovs=0, ndpars=0)
        }

### MODEL FOR COVARIATES ON MISCLASSIFICATION PROBABILITIES
    if (!emodel$misc || is.null(misccovariates))
        ecmodel <- list(npars=0, ncovs=0)
    if (!is.null(misccovariates)) {
        if (!emodel$misc) {
            warning("misccovariates have been specified, but misc is FALSE. Ignoring misccovariates.")
        }
        else {
            ecmodel <- msm.form.covmodel(msmdata$misccovdata, miscconstraint, emodel$npars, misccovinits)
            hcovariates <- msm.misccov2hcov(misccovariates, emodel)
            hcovinits <- msm.misccovinits2hcovinits(misccovinits, hcovariates, emodel, ecmodel)
        }
    }

### MODEL FOR COVARIATES ON GENERAL HIDDEN PARAMETERS
    if (!is.null(hcovariates)) {
        hmodel <- msm.form.hcmodel(hmodel, msmdata$hcovdata, hcovinits, hconstraint)
        if (emodel$misc)
            hmodel$covconstr <- msm.form.hcovconstraint(miscconstraint, hmodel)
    }
    else if (hmodel$hidden) {
        hmodel <- c(hmodel, list(ncovs=rep(rep(0, hmodel$nstates), hmodel$npars), ncoveffs=0))
        class(hmodel) <- "hmodel"
    }
    if (!is.null(initcovariates)) {
        hmodel <- msm.form.icmodel(hmodel, msmdata$icovdata, initcovinits)
    }
    else if (hmodel$hidden) {
        hmodel <- c(hmodel, list(nicovs=rep(0, hmodel$nstates-1), nicoveffs=0))
        class(hmodel) <- "hmodel"
    }
    if (hmodel$hidden && !emodel$misc) {
        hmodel$constr <- msm.form.hconstraint(hconstraint, hmodel)
        hmodel$covconstr <- msm.form.hcovconstraint(hconstraint, hmodel)
    }

### FORM LIST OF INITIAL PARAMETERS, MATCHING PROVIDED INITS WITH SPECIFIED MODEL, FIXING SOME PARS IF REQUIRED
    p <- msm.form.params(qmodel, qcmodel, emodel, hmodel, fixedpars, est.initprobs)

### CALCULATE LIKELIHOOD AT INITIAL VALUES...
    if (p$fixed) {
        p$lik <- lik.msm(p$inits, msmdata, qmodel, qcmodel, cmodel, hmodel, p)
        p$deriv <- if (!hmodel$hidden && cmodel$ncens==0) deriv.msm(p$inits, msmdata, qmodel, qcmodel, cmodel, hmodel, p) else NULL
        p$allinits[p$hmmpars] <- msm.mninvlogit.transform(p$allinits[p$hmmpars], hmodel$plabs, hmodel$parstate)
        p$params.uniq <- p$allinits[!duplicated(abs(p$constr))]
        p$params <- p$allinits[!duplicated(abs(p$constr))][abs(p$constr)]*sign(p$constr)
        p$foundse <- FALSE
        p$covmat <- NULL
    }

### ... OR DO MAXIMUM LIKELIHOOD ESTIMATION
    else {
        p$params <- p$allinits
        gr <- if (!hmodel$hidden && cmodel$ncens==0 && use.deriv) deriv.msm else NULL
        opt.method <- match.arg(opt.method)
        if (opt.method == "optim") {
            opt <- optim(p$inits, lik.msm, hessian=hessian, gr=gr, ...,# arguments to optim
                         msmdata=msmdata, qmodel=qmodel, qcmodel=qcmodel,
                         cmodel=cmodel, hmodel=hmodel, paramdata=p)
            p$lik <- opt$value
            p$deriv <- if (!hmodel$hidden && cmodel$ncens==0) deriv.msm(opt$par, msmdata, qmodel, qcmodel, cmodel, hmodel, p) else NULL
            p$params[p$optpars] <- opt$par
        }
        else if (opt.method == "nlm") {
            nlmfn <- function(par) {
                ret <- lik.msm(par, msmdata=msmdata, qmodel=qmodel, qcmodel=qcmodel,
                               cmodel=cmodel, hmodel=hmodel, paramdata=p)
                if (!is.null(gr))
                    attr(ret, "gradient") <- deriv.msm(par, msmdata=msmdata, qmodel=qmodel, qcmodel=qcmodel,
                                                       cmodel=cmodel, hmodel=hmodel, paramdata=p)
                ret
            }
            opt <- nlm(nlmfn, p$inits, hessian=hessian, ...)
            p$lik <- opt$minimum
            p$deriv <- if (!hmodel$hidden && cmodel$ncens==0) deriv.msm(opt$estimate, msmdata, qmodel, qcmodel, cmodel, hmodel, p) else NULL
            p$params[p$optpars] <- opt$estimate
        }
        p$opt <- opt
        ## Replicate constrained pars. (Replicate pr, not log(pr/pbase), then recalculate baseline)
        p$params[p$hmmpars] <- msm.mninvlogit.transform(p$params[p$hmmpars], hmodel$plabs, hmodel$parstate)
        p$params.uniq <- p$params[!duplicated(abs(p$constr))]
        p$params <- p$params[!duplicated(abs(p$constr))][abs(p$constr)]*sign(p$constr)
        if (hessian && all(eigen(opt$hessian)$values > 0)) {
            p$foundse <- TRUE
            p$covmat <- matrix(0, nrow=p$npars, ncol=p$npars)
            p$covmat[p$optpars,p$optpars] <- solve(0.5 * opt$hessian)
            p$covmat.uniq <- p$covmat[!duplicated(abs(p$constr)),!duplicated(abs(p$constr)), drop=FALSE]
            p$covmat <- p$covmat[!duplicated(abs(p$constr)),!duplicated(abs(p$constr)), drop=FALSE][abs(p$constr),abs(p$constr), drop=FALSE]
            p$ci <- cbind(p$params - qnorm(1 - 0.5*(1-cl))*sqrt(diag(p$covmat)),
                          p$params + qnorm(1 - 0.5*(1-cl))*sqrt(diag(p$covmat)))
            p$ci[p$fixedpars,] <- NA
        }
        else {
            p$foundse <- FALSE
            p$covmat <- p$ci <- NULL
            if (hessian)
                warning("Could not calculate asymptotic standard errors - Hessian is not positive definite. Optimisation has probably not converged to the maximum likelihood")
        }
        p$params[p$hmmpars] <- msm.recalc.basep(p$params[p$hmmpars], hmodel$plabs, hmodel$parstate)
        p$params[p$hmmpars] <- msm.mnlogit.transform(p$params[p$hmmpars], hmodel$plabs, hmodel$parstate)
    }

    p$estimates.t <- p$params  # Calculate estimates and CIs on natural scale
    p$estimates.t[p$hmmpars] <- msm.mninvlogit.transform(p$estimates.t[p$hmmpars], hmodel$plabs, hmodel$parstate)
    for (lab in rownames(.msm.TRANSFORMS)) {
        p$estimates.t[p$plabs==lab] <- get(.msm.TRANSFORMS[lab,"inv"])(p$params[p$plabs==lab])
        if (p$foundse)
            p$ci[p$plabs==lab] <- get(.msm.TRANSFORMS[lab,"inv"])(p$ci[p$plabs==lab, ])
    }
    ## calculate CIs for misclassification probabilities (needs multivariate transform and delta method)
    if (any(p$plabs=="p")){
        if (p$foundse) {
            p.se <- p.se.msm(qmodel,emodel,hmodel,qcmodel,ecmodel,p,center, covariates = if(center) "mean" else 0)
            if (p$foundse)
                p$ci[p$plabs %in% c("p","pbase"),] <- as.numeric(unlist(p.se[,c("LCL","UCL")]))
        }
    }

### REARRANGE THE VECTOR OF PARAMETER ESTIMATES (LOG-INTENSITIES, MISC PROBS AND
### COVARIATE EFFECTS) INTO LISTS OF MATRICES
    output <- msm.form.output("intens", qmodel, qcmodel, p)
    Qmatrices <- output$Matrices
    QmatricesSE <- if (p$fixed) NULL else output$MatricesSE
    QmatricesL <- if (p$fixed) NULL else output$MatricesL
    QmatricesU <- if (p$fixed) NULL else output$MatricesU

    if (emodel$misc) {
        output <- msm.form.output("misc", emodel, ecmodel, p)
        Ematrices <- output$Matrices
        EmatricesSE <- if (p$fixed) NULL else output$MatricesSE
        EmatricesL <- if (p$fixed) NULL else output$MatricesL
        EmatricesU <- if (p$fixed) NULL else output$MatricesU
        names(Ematrices)[1] <- "logitbaseline"
        if (p$foundse & !p$fixed) names(EmatricesSE)[1] <- names(EmatricesL)[1] <-
            names(EmatricesU)[1] <- "logitbaseline"
    }
    else {
        Ematrices <- EmatricesSE <- EmatricesL <- EmatricesU <- NULL
    }
    if (hmodel$hidden) {
        hmodel <- msm.form.houtput(hmodel, p)
    }

### FORM A MSM OBJECT FROM THE RESULTS
    msmobject <- list (
                       call = match.call(),
                       Qmatrices = Qmatrices,
                       QmatricesSE = QmatricesSE,
                       QmatricesL = QmatricesL,
                       QmatricesU = QmatricesU,
                       minus2loglik = p$lik,
                       deriv = p$deriv,
                       estimates = p$params,
                       estimates.t = p$estimates.t,
                       fixedpars = p$fixedpars,
                       center = center,
                       covmat = p$covmat,
                       ci = p$ci,
                       opt = p$opt,
                       foundse = p$foundse,
                       data = msmdata,
                       data.orig = msmdata.obs.orig, # before any pci imputation, NULL if no pci
                       qmodel = qmodel,
                       emodel = emodel,
                       qcmodel = qcmodel,
                       ecmodel = ecmodel,
                       hmodel = hmodel,
                       cmodel = cmodel,
                       pci = pci,
                       paramdata=p
                       )
    attr(msmobject, "fixed") <- p$fixed
    class(msmobject) <- "msm"
    q <- qmatrix.msm(msmobject) # intensity matrix with centered covariates
    msmobject$Qmatrices$baseline <- q$estimates
    msmobject$QmatricesSE$baseline <- q$SE
    msmobject$QmatricesL$baseline <- q$L
    msmobject$QmatricesU$baseline <- q$U
    if (emodel$misc) {
        msmobject$Ematrices <- Ematrices
        msmobject$EmatricesSE <- EmatricesSE
        msmobject$EmatricesL <- EmatricesL
        msmobject$EmatricesU <- EmatricesU
        e <- ematrix.msm(msmobject) # misc matrix with centered covariates
        msmobject$Ematrices$baseline <- e$estimates
        msmobject$EmatricesSE$baseline <- e$SE
        msmobject$EmatricesL$baseline <- e$L
        msmobject$EmatricesU$baseline <- e$U
    }
    ## Calculate mean sojourn times with centered covariates
    msmobject$sojourn <- sojourn.msm(msmobject)
    msmobject
}

msm.check.qmatrix <- function(qmatrix)
{
    if (!is.numeric(qmatrix) || ! is.matrix(qmatrix))
        stop("qmatrix should be a numeric matrix")
    if (nrow(qmatrix) != ncol(qmatrix))
        stop("Number of rows and columns of qmatrix should be equal")
    q2 <- qmatrix; diag(q2) <- 0
    if (any(q2 < 0))
        stop("off-diagonal entries of qmatrix should not be negative")
    invisible()
}

msm.fixdiag.qmatrix <- function(qmatrix)
{
    diag(qmatrix) <- 0
    diag(qmatrix) <- - rowSums(qmatrix)
    qmatrix
}

msm.fixdiag.ematrix <- function(ematrix)
{
    diag(ematrix) <- 0
    diag(ematrix) <- 1 - rowSums(ematrix)
    ematrix
}

msm.form.qmodel <- function(qmatrix, qconstraint=NULL, exacttimes=FALSE, gen.inits=FALSE, formula, subject, data, censor, censor.states, analyticp)
{
### INTENSITY MATRIX (INPUT: qmatrix, qconstraint; OUTPUT: nstates, nintens, qmatrix, qvector, baseconstr, nintenseffs)
    if (gen.inits)
        qmatrix <- crudeinits.msm(formula, subject, qmatrix, data, censor, censor.states)
    msm.check.qmatrix(qmatrix)
    nstates <- dim(qmatrix)[1]
    qmatrix <- msm.fixdiag.qmatrix(qmatrix)
    if (is.null(rownames(qmatrix)))
        rownames(qmatrix) <- colnames(qmatrix) <- paste("State", seq(nstates))
    else if (is.null(colnames(qmatrix))) colnames(qmatrix) <- rownames(qmatrix)
    imatrix <- ifelse(qmatrix > 0, 1, 0)
    inits <- t(qmatrix)[t(imatrix)==1]
    npars <- sum(imatrix)
    if (!is.null(qconstraint)) {
        if (!is.numeric(qconstraint)) stop("qconstraint should be numeric")
        if (length(qconstraint) != npars)
            stop("baseline intensity constraint of length " ,length(qconstraint), ", should be ", npars)
        constr <- match(qconstraint, unique(qconstraint))
    }
    else
        constr <- 1:npars
    ndpars <- max(constr)
    ipars <- t(imatrix)[t(lower.tri(imatrix) | upper.tri(imatrix))]
    graphid <- paste(which(ipars==1), collapse="-")
    if (graphid %in% names(.msm.graphs[[paste(nstates)]])) {
        ## analytic P matrix is implemented for this particular intensity matrix
        iso <- .msm.graphs[[paste(nstates)]][[graphid]]$iso
        perm <- .msm.graphs[[paste(nstates)]][[graphid]]$perm
        iperm <- match(1:nstates, perm)
        imatrix.ind <- t(imatrix)
        imatrix.ind[t(imatrix)>0] <- 1:npars
        imatrix.ind <- t(imatrix.ind)
        qperm <- imatrix.ind[iperm,iperm]
        qperm <- t(qperm)[t(qperm)>0]
    }
    else {
        iso <- 0
        perm <- qperm <- NA
    }
    qmodel <- list(nstates=nstates, analyticp=analyticp, iso=iso, perm=perm, qperm=qperm,
                   npars=npars, imatrix=imatrix, qmatrix=qmatrix, inits=inits,
                   constr=constr, ndpars=ndpars, exacttimes=exacttimes)
    class(qmodel) <- "msmqmodel"
    qmodel
}

msm.check.ematrix <- function(ematrix, nstates)
{
    if (!is.numeric(ematrix) || ! is.matrix(ematrix))
        stop("ematrix should be a numeric matrix")
    if (nrow(ematrix) != ncol(ematrix))
        stop("Number of rows and columns of ematrix should be equal")
    if (!all(dim(ematrix) == nstates))
        stop("Dimensions of qmatrix and ematrix should be the same")
    if (!all ( ematrix >= 0 | ematrix <= 1) )
        stop("Not all elements of ematrix are between 0 and 1")
    invisible()
}

msm.form.emodel <- function(ematrix, econstraint=NULL, initprobs=NULL, est.initprobs, qmodel)
{
    msm.check.ematrix(ematrix, qmodel$nstates)
    diag(ematrix) <- 0
    imatrix <- ifelse(ematrix > 0 & ematrix < 1, 1, 0)
    diag(ematrix) <- 1 - rowSums(ematrix)
    if (is.null(rownames(ematrix)))
        rownames(ematrix) <- colnames(ematrix) <- paste("State", seq(qmodel$nstates))
    else if (is.null(colnames(ematrix))) colnames(ematrix) <- rownames(ematrix)
    dimnames(imatrix) <- dimnames(ematrix)
    npars <- sum(imatrix)
    nstates <- nrow(ematrix)
    inits <- t(ematrix)[t(imatrix)==1]
    if (is.null(initprobs)) {
        initprobs <- if (est.initprobs) rep(1/qmodel$nstates, qmodel$nstates) else c(1, rep(0, qmodel$nstates-1))
    }
    else {
        if (!is.numeric(initprobs)) stop("initprobs should be numeric")
        if (length(initprobs) != qmodel$nstates) stop("initprobs of length ", length(initprobs), ", should be ", qmodel$nstates)
        initprobs <- initprobs / sum(initprobs)
    }
    nipars <- qmodel$nstates - 1
    if (!is.null(econstraint)) {
        if (!is.numeric(econstraint)) stop("econstraint should be numeric")
        if (length(econstraint) != npars)
            stop("baseline misclassification constraint of length " ,length(econstraint), ", should be ", npars)
        constr <- match(econstraint, unique(econstraint))
    }
    else
        constr <- 1:npars
    ndpars <- max(constr)
    emodel <- list(misc=TRUE, npars=npars, nstates=nstates, imatrix=imatrix, ematrix=ematrix, inits=inits,
                   constr=constr, ndpars=ndpars, nipars=nipars, initprobs=initprobs)
    class(emodel) <- "msmemodel"
    emodel
}

### Extract data from supplied arguments, check consistency, drop missing data.
### Returns dataframe of cleaned data in observation time format
### Covariates returned in covmat

msm.form.data <- function(formula, subject=NULL, obstype=NULL, obstrue=NULL, covariates=NULL, data=NULL,
                          hcovariates=NULL, misccovariates=NULL, initcovariates=NULL,
                          qmodel, emodel, hmodel, cmodel, dmodel, exacttimes, center)
{
    ## Parse the model formula of subject and time, getting missing values
    if (!inherits(formula, "formula")) stop("\"formula\" argument should be a formula")
    mf <- model.frame(formula, data=data)
    state <- mf[,1]
    if (!hmodel$hidden || emodel$misc)
        msm.check.state(qmodel$nstates, state=state, cmodel$censor)  ## replace after splitting form.hmodel
    time <- mf[,2]
    if (is.null(subject)) subject <- rep(1, nrow(mf))
    obstype <- msm.form.obstype(obstype, length(state), state, dmodel, exacttimes)
    obstrue <- msm.form.obstrue(obstrue, length(state), hmodel)
    droprows <- as.numeric(attr(mf, "na.action"))
    n <- length(c(state, droprows))
    statetimerows.kept <- (1:n)[! ((1:n) %in% droprows)]
    subjrows.kept <- (1:n) [!is.na(subject)]
    otrows.kept <- statetimerows.kept[!is.na(obstype)]
    omrows.kept <- statetimerows.kept[!is.na(obstrue)]

    ## Don't drop NA covariates on the transition process at the subject's final observation, since they are not used
    lastobs <- c(which(subject[1:(n-1)] != subject[2:n]), n)
    ## Parse covariates formula and extract data
    covdata <- misccovdata <- icovdata <- list(ncovs=0, covmat=numeric(0))
    if (!is.null(covariates)) {
        covdata <- msm.form.covdata(covariates, data, lastobs, center)
    }
    if (!is.null(misccovariates) && emodel$misc) {
        misccovdata <- msm.form.covdata(misccovariates, data, NULL, center)
        hcovariates <- lapply(ifelse(rowSums(emodel$imatrix)>0, deparse(misccovariates), deparse(~1)), as.formula)
    }
    hcovdata <- vector(qmodel$nstates, mode="list")
    if (!is.null(hcovariates)) {
        for (i in seq(qmodel$nstates)) {
            if (!is.null(hcovariates) && !is.null(hcovariates[[i]]))
                hcovdata[[i]] <- msm.form.covdata(hcovariates[[i]], data, NULL, center)
            else hcovdata[[i]] <- list(ncovs=0)
        }
    }
    ## Only drop NA covariates on initprobs at initial observation
    firstobs <- c(1, which(subject[2:n] != subject[1:(n-1)]) + 1)
    if (!is.null(initcovariates)) {
        icovdata <- msm.form.covdata(initcovariates, data, !firstobs, center)
    }
    ## List of which covariates are in which model
    all.covlabels <- unique(c(covdata$covlabels, unlist(lapply(hcovdata, function(x)x$covlabels)), icovdata$covlabels)) # factors as numeric contrasts
    orig.covlabels <- unique(c(covdata$covlabels.orig, unlist(lapply(hcovdata, function(x)x$covlabels.orig)), icovdata$covlabels.orig)) # factors as single variables
    covdata$whichcov <- match(covdata$covlabels, all.covlabels)
    covdata$whichcov.orig <- match(covdata$covlabels.orig, orig.covlabels)
    if(!is.null(hcovariates)) {
        for (i in seq(along=hcovdata)){
            hcovdata[[i]]$whichcov <- match(hcovdata[[i]]$covlabels, all.covlabels)
            hcovdata[[i]]$whichcov.orig <- match(hcovdata[[i]]$covlabels.orig, orig.covlabels)
        }
    }
    if (!is.null(initcovariates))
        icovdata$whichcov <- match(icovdata$covlabels, all.covlabels)

    ## Drop missing data
    final.rows <- intersect(statetimerows.kept, subjrows.kept)
    final.rows <- intersect(final.rows, otrows.kept)
    final.rows <- intersect(final.rows, omrows.kept)
    if (covdata$ncovs > 0)
        final.rows <- intersect(final.rows, covdata$covrows.kept)
    if (!is.null(hcovariates))
        for (i in seq(along=hcovariates))
            if (hcovdata[[i]]$ncovs > 0)
                final.rows <- intersect(final.rows, hcovdata[[i]]$covrows.kept)
    if (icovdata$ncovs > 0)
        final.rows <- intersect(final.rows, icovdata$covrows.kept)
    subject <- subset(subject, subjrows.kept %in% final.rows)
    ##      subject <- match(subject, unique(subject)) # convert to ordinal
    time <- subset(time, statetimerows.kept %in% final.rows)
    msm.check.times(time, subject)
    state <- subset(state, statetimerows.kept %in% final.rows)
    obstype <- subset(obstype, otrows.kept %in% final.rows)
    obstrue <- subset(obstrue, omrows.kept %in% final.rows)
    covmat <- covmat.orig <- numeric()
    if (covdata$ncovs > 0) {
        covmat <- subset(covdata$covmat, covdata$covrows.kept %in% final.rows)
        covmat.orig <- subset(covdata$covmat.orig, covdata$covrows.kept %in% final.rows)
        covdata$covmat <- covdata$covmat.orig <- NULL
    }
    for (i in seq(along=hcovariates)) {
        if (hcovdata[[i]]$ncovs > 0) {
            hcovdata[[i]]$covmat <- subset(hcovdata[[i]]$covmat, hcovdata[[i]]$covrows.kept %in% final.rows)
            hcovdata[[i]]$covmat.orig <- subset(hcovdata[[i]]$covmat.orig, hcovdata[[i]]$covrows.kept %in% final.rows)
            covmat <- cbind(covmat, as.matrix(hcovdata[[i]]$covmat))
            covmat.orig <- cbind(covmat.orig, as.matrix(hcovdata[[i]]$covmat.orig))
            hcovdata[[i]]$covmat <- hcovdata[[i]]$covmat.orig <- NULL
        }
    }
    if (icovdata$ncovs > 0) {
        icovdata$covmat <- subset(icovdata$covmat, icovdata$covrows.kept %in% final.rows)
        icovdata$covmat.orig <- subset(icovdata$covmat.orig, icovdata$covrows.kept %in% final.rows)
        covmat <- cbind(covmat, as.matrix(icovdata$covmat))
        covmat.orig <- cbind(covmat.orig, as.matrix(icovdata$covmat.orig))
        icovdata$covmat <- icovdata$covmat.orig <- NULL
    }
    if (length(all.covlabels) > 0) {
        covmat <- as.data.frame(covmat, optional=TRUE)[all.covlabels]
        covmat.orig <- as.data.frame(covmat.orig, optional=TRUE)[orig.covlabels]
    }
    nobs <- length(final.rows)
    nmiss <- n - nobs
    plural <- if (nmiss==1) "" else "s"
    if (nmiss > 0) warning(nmiss, " record", plural, " dropped due to missing values")
    dat <- list(state=state, time=time, subject=subject, obstype=obstype, obstrue=obstrue,
                nobs=nobs, n=nobs, npts=length(unique(subject)),
                firstobs = c(1, which(subject[2:n] != subject[1:(n-1)]) + 1, n+1),
                ncovs=length(all.covlabels), covlabels=all.covlabels, covlabels.orig=orig.covlabels,
                covdata=covdata, misccovdata=misccovdata, hcovdata=hcovdata, icovdata=icovdata,
                covmat=covmat, # covariates including factors as 0/1 contrasts
                covmat.orig=covmat.orig # covariates in which a factor is a single variable
                )
    class(dat) <- "msmdata"
    dat
}

### Check elements of state vector. For simple models and misc models specified with ematrix
### No check is performed for hidden models

msm.check.state <- function(nstates, state=NULL, censor)
{
    statelist <- if (nstates==2) "1, 2" else if (nstates==3) "1, 2, 3" else paste("1, 2, ... ,",nstates)
    states <- c(1:nstates, censor)
    if (!is.null(state)) {
        if (length(setdiff(unique(state), states)) > 0)
            stop("State vector contains elements not in ",statelist)
        miss.state <- setdiff(states, unique(state))
        if (length(miss.state) > 0)
            warning("State vector doesn't contain observations of ",paste(miss.state, collapse=","))
    }
    invisible()
}

msm.check.times <- function(time, subject)
{
### Check if any individuals have only one observation (after excluding missing data)
    subj.num <- match(subject,unique(subject)) # avoid problems with factor subjects with empty levels
    nobspt <- table(subj.num)
    if (any (nobspt == 1)) {
        badsubjs <- sort(unique(subject))[ nobspt == 1 ]
        badlist <- paste(badsubjs, collapse=", ")
        plural <- if (length(badsubjs)==1) "" else "s"
        has <-  if (length(badsubjs)==1) "has" else "have"
        warning ("Subject", plural, " ", badlist, " only ", has, " one complete observation")
    }
### Check if observations within a subject are adjacent
    ind <- tapply(1:length(subj.num), subj.num, length)
    imin <- tapply(1:length(subj.num), subj.num, min)
    imax <- tapply(1:length(subj.num), subj.num, max)
    adjacent <- (ind == imax-imin+1)
    if (any (!adjacent)) {
        badsubjs <- sort(unique(subject))[ !adjacent ]
        badlist <- paste(badsubjs, collapse=", ")
        plural <- if (length(badsubjs)==1) "" else "s"
        stop ("Observations within subject", plural, " ", badlist, " are not adjacent in the data")
    }
### Check if observations are ordered in time within subject
    orderedpt <- ! tapply(time, subj.num, is.unsorted)
    if (any (!orderedpt)) {
        badsubjs <- sort(unique(subject))[ !orderedpt ]
        badlist <- paste(badsubjs, collapse=", ")
        plural <- if (length(badsubjs)==1) "" else "s"
        stop ("Observations within subject", plural, " ", badlist, " are not ordered by time")
    }
    invisible()
}

### Convert observation time data to from-to format

msm.obs.to.fromto <- function(dat)
{
    n <- length(dat$state)
    subj.num <- match(dat$subject, unique(dat$subject))
    prevsubj <- c(-Inf, subj.num[1:(n-1)])
    firstsubj <- subj.num != prevsubj
    nextsubj <- c(subj.num[2:n], Inf)
    lastsubj <- subj.num != nextsubj
    fromstate <- c(-Inf, dat$state[1:(n-1)])[!firstsubj]
    tostate <- dat$state[!firstsubj]
    timelag <- diff(dat$time)[!firstsubj[-1]]
    subject <- dat$subject[!firstsubj]
    obstype <- dat$obstype[!firstsubj]
    obs <- seq(n)[!firstsubj]
    datf <- list(fromstate=fromstate, tostate=tostate, timelag=timelag, subject=subject, obstype=obstype,
                 time=dat$time, obs=obs, firstsubj=firstsubj, npts=dat$npts, ncovs=dat$ncovs, covlabels=dat$covlabels,
                 obstype.obs=dat$obstype, # need to keep this, e.g. for bootstrap resampling.
                 covdata=dat$covdata, hcovdata=dat$hcovdata)
    if (datf$ncovs > 0) {
        ## match time-dependent covariates with the start of the transition
                                        #          datf <- c(datf, subset(as.data.frame(dat[dat$covlabels], optional=TRUE), !lastsubj))
        datf$covmat <- subset(as.data.frame(dat$covmat, optional=TRUE), !lastsubj)
    } ## n.b. don't need to  use this function for misc models
    class(datf) <- "msmfromtodata"
    datf
}

## Replace censored states by state with highest probability that they
## could represent. Used in msm.check.model to check consistency of
## data with transition parameters

msm.impute.censored <- function(fromstate, tostate, Pmat, cmodel)
{
    ## e.g. cmodel$censor 99,999;  cmodel$states 1,2,1,2,3;  cmodel$index 1, 3, 6
    ## Both from and to are censored
    wb <- which ( fromstate %in% cmodel$censor & tostate %in% cmodel$censor)
    for (i in wb) {
        si <- which(cmodel$censor==fromstate[i])
        fc <- cmodel$states[(cmodel$index[si]) : (cmodel$index[si+1]-1)]
        ti <- which(cmodel$censor==tostate[i])
        tc <- cmodel$states[(cmodel$index[ti]) : (cmodel$index[ti+1]-1)]
        mp <- which.max(Pmat[fc, tc])
        fromstate[i] <- fc[row(Pmat[fc, tc])[mp]]
        tostate[i] <- tc[col(Pmat[fc, tc])[mp]]
    }
    ## Only from is censored
    wb <- which(fromstate %in% cmodel$censor)
    for (i in wb) {
        si <- which(cmodel$censor==fromstate[i])
        fc <- cmodel$states[(cmodel$index[si]) : (cmodel$index[si+1]-1)]
        fromstate[i] <- fc[which.max(Pmat[fc, tostate[i]])]
    }
    ## Only to is censored
    wb <- which(tostate %in% cmodel$censor)
    for (i in wb) {
        si <- which(cmodel$censor==tostate[i])
        tc <- cmodel$states[(cmodel$index[si]) : (cmodel$index[si+1]-1)]
        tostate[i] <- tc[which.max(Pmat[fromstate[i], tc])]
    }
    list(fromstate=fromstate, tostate=tostate)
}

### CHECK IF TRANSITION PROBABILITIES FOR DATA ARE ALL NON-ZERO
### (e.g. check for backwards transitions when the model is irreversible)
### obstype 1 must have unitprob > 0
### obstype 2 must have qunit != 0, and unitprob > 0.
### obstype 3 must have unitprob > 0

msm.check.model <- function(fromstate, tostate, obs, subject, obstype=NULL, qmatrix, cmodel)
{
    n <- length(fromstate)
    Pmat <- MatrixExp(qmatrix)
    Pmat[Pmat < 1e-16] <- 0
    imputed <- msm.impute.censored(fromstate, tostate, Pmat, cmodel)
    fs <- imputed$fromstate; ts <- imputed$tostate
    unitprob <- apply(cbind(fs, ts), 1, function(x) { Pmat[x[1], x[2]] } )
    qunit <- apply(cbind(fs, ts), 1, function(x) { qmatrix[x[1], x[2]] } )

    if (identical(all.equal(min(unitprob, na.rm=TRUE), 0),  TRUE))
    {
        badobs <- min (obs[unitprob==0], na.rm = TRUE)
        warning ("Data inconsistent with transition matrix for model without misclassification:\n",
                 "individual ", if(is.null(subject)) "" else subject[obs==badobs], " moves from state ", fromstate[obs==badobs],
                 " to state ", tostate[obs==badobs], " at observation ", badobs, "\n")
    }
    if (any(qunit[obstype==2]==0)) {
        badobs <- min (obs[qunit==0 & obstype==2], na.rm = TRUE)
        warning ("Data inconsistent with intensity matrix for observations with exact transition times and no misclassification:\n",
                 "individual ", if(is.null(subject)) "" else subject[obs==badobs], " moves from state ", fromstate[obs==badobs],
                 " to state ", tostate[obs==badobs], " at observation ", badobs)
    }
    absorbing <- absorbing.msm(qmatrix=qmatrix)
    absabs <- (fromstate %in% absorbing) & (tostate %in% absorbing)
    if (any(absabs)) {
        badobs <- min( obs[absabs] )
        warning("Absorbing - absorbing transition at observation ", badobs)
    }
    invisible()
}


## Extract covariate information from a formula.
## Find which columns and which rows to keep from the original data

msm.form.covdata <- function(covariates, data, ignore.obs, center=TRUE)
{
    if (!inherits(covariates, "formula")) stop(deparse(substitute(covariates)), " should be a formula")
    mf1 <- model.frame(covariates, data=data, na.action=NULL)
    ## We shouldn't drop NA covariates at the subject's final
    ## observation, since they are not used in the analysis, therefore
    ## we impute observed zeros when final observations are NA.
    mf.imp <- mf1
    for (i in names(mf.imp))
        if (!is.null(ignore.obs))
            mf.imp[ignore.obs,i][is.na(mf.imp[ignore.obs,i])] <- if (is.factor(mf.imp[,i])) levels(mf.imp[,i])[1] else 0
    mm <- na.omit(as.data.frame(model.matrix(covariates, data=mf.imp)))
    n <- nrow(mf.imp)
    covlabels <- names(mm)[-1]
    ncovs <- length(covlabels)
    mm <- subset(mm, select=-1)
    mf2 <- na.omit(mf.imp)
    droprows <- as.numeric(attr(mf2, "na.action"))
    covrows.kept <- (1:n)[! ((1:n) %in% droprows)]
    covfactor <- sapply(mf2, is.factor)
    covfactorlevels <- lapply(mf2, levels)
    ## for consistency with version 0.7 and earlier, don't include imputed last obs when calculating covariate means
    covmeans <- apply(na.omit(model.matrix(covariates, data=data)), 2, mean, na.rm=TRUE)[-1]
    ## centre the covariates about their means if requested
    if (center && ncovs > 0) mm <- sweep(mm, 2, covmeans)
    colnames(mm) <- covlabels # ( ) in names are converted into . in sweep, breaks factor covs
    covdata <- list(covlabels=covlabels, ncovs=ncovs, covmeans=covmeans,
                    covfactor=covfactor,
                    covfactorlevels=covfactorlevels,
                    covmat=mm, # data with factors as set of 0/1 contrasts, and centered.  (for model fitting)
                    covmat.orig=mf2, # with factors kept as one variable, and not centered (for bootstrap refitting)
                    covlabels.orig=colnames(mf2),
                    covrows.kept=covrows.kept)
    class(covdata) <- "msmcovdata"
    covdata
}

### Aggregate the data by distinct values of time lag, covariate values, from state, to state, observation type
### Result is passed to the C likelihood function (for non-hidden multi-state models)

msm.aggregate.data <- function(dat)
{
    dat2 <- as.data.frame(dat[c("fromstate","tostate","timelag","obstype")], optional=TRUE)
    dat2$covmat <- dat$covmat
    nobsf <- length(dat2$fromstate)
    apaste <- do.call("paste", c(dat2[,c("fromstate","tostate","timelag","obstype")], dat2$covmat))
    msmdata <- dat2[!duplicated(apaste),]
    msmdata <- msmdata[order(unique(apaste)),]
    msmdata$nocc <- as.numeric(table(apaste))
    apaste2 <- msmdata[,"timelag"]
    if (dat$ncovs > 0) apaste2 <- paste(apaste2,  do.call("paste", msmdata$covmat))
    ## which unique timelag/cov combination each row of aggregated data corresponds to
    ## lik.c needs this to know when to recalculate the P matrix.
    msmdata$whicha <- match(apaste2, unique(apaste2))
    msmdata <- as.list(msmdata[order(apaste2),])
    msmdata <- c(msmdata, dat[c("covdata", "hcovdata", "npts", "covlabels")])
    msmdata$nobs <- length(msmdata[[1]])
    class(msmdata) <- "msmaggdata"
    msmdata
}

### Make indicator for which distinct from, to, timelag, covariate combination each observation corresponds to
### HMM only. This indicator is not used at the moment, but may be in the future.

msm.aggregate.hmmdata <- function(dat)
{
    dat2 <- msm.obs.to.fromto(dat)
    firstsubj <- dat2$firstsubj
    dat2 <- as.data.frame(c(dat2[c("fromstate","tostate","timelag")], dat2$covmat), optional=TRUE)
    apaste <- as.character(do.call("paste", dat2))
    dat$whicha <- rep(0, dat$nobs)
    dat$whicha[!firstsubj] <- match(apaste, unique(apaste))
    ## index of patient's first observation, plus extra element for
    ## last person's last observation plus one. This is used.
    dat$firstobs <- c(which(firstsubj), dat$nobs+1)
    dat
}

### Process covariates constraints, in preparation for being passed to the likelihood optimiser
### This function is called for both sets of covariates (transition rates and the misclassification probs)

msm.form.covmodel <- function(covdata,
                              constraint,
                              nmatrix,     # number of transition intensities / misclassification probs
                              covinits
                              )
{
    ncovs <- covdata$ncovs
    covlabels <- covdata$covlabels
    covlabels.orig <- covdata$covlabels.orig
    covfactor <- covdata$covfactor
    if (is.null(constraint)) {
        constraint <- rep(list(1:nmatrix), ncovs)
        names(constraint) <- covlabels
        constr <- 1:(nmatrix*ncovs)
    }
    else {
        if (!is.list(constraint)) stop(deparse(substitute(constraint)), " should be a list")
        if (!all(sapply(constraint, is.numeric)))
            stop(deparse(substitute(constraint)), " should be a list of numeric vectors")
        if (!all(names(constraint) %in% covlabels))
            stop("covariate ", paste(setdiff(names(constraint), covlabels), collapse=", "), " in ", deparse(substitute(constraint)), " unknown")
        ## check and parse the list of constraints on covariates
        for (i in names(constraint))
            if (!(is.element(i, covlabels))){
                factor.warn <- if (covfactor[i])
                    "\n\tFor factor covariates, specify constraints using covnameCOVVALUE = c(...)"
                else ""
                stop("Covariate \"", i, "\" in constraint statement not in model.", factor.warn)
            }
        constr <- inits <- numeric()
        maxc <- 0
        for (i in seq(along=covlabels)){
            ## build complete vectorised list of constraints for covariates in covariates statement
            ## so. e.g. constraints = (x1=c(3,3,4,4,5), x2 = (0.1,0.2,0.3,0.4,0.4))
            ##     turns into constr = c(1,1,2,2,3,4,5,6,7,7) with seven distinct covariate effects
            ## Allow constraints such as: some elements are minus others. Use negative elements of constr to do this.
            ## e.g. constr = c(1,1,-1,-1,2,3,4,5)
            ## obtained by match(abs(x), unique(abs(x))) * sign(x)
            if (is.element(covlabels[i], names(constraint))) {
                if (length(constraint[[covlabels[i]]]) != nmatrix)
                    stop("\"",names(constraint)[i],"\" constraint of length ",
                         length(constraint[[covlabels[i]]]),", should be ",nmatrix)
            }
            else
                constraint[[covlabels[i]]] <- seq(nmatrix)
            constr <- c(constr, (maxc + match(abs(constraint[[covlabels[i]]]),
                                             unique(abs(constraint[[covlabels[i]]]))))*sign(constraint[[covlabels[i]]]) )
            maxc <- max(abs(constr))
        }
    }
    inits <- numeric()
    if (!is.null(covinits)) {
        if (!is.list(covinits)) warning(deparse(substitute(covinits)), " should be a list")
        else if (!all(sapply(covinits, is.numeric)))
            warning(deparse(substitute(covinits)), " should be a list of numeric vectors")
        else if (!all(names(covinits) %in% covlabels))
            warning("covariate ", paste(setdiff(names(covinits), covlabels), collapse=", "), " in ", deparse(substitute(covinits)), " unknown")
    }
    for (i in seq(along=covlabels)) {
        if (!is.null(covinits) && is.element(covlabels[i], names(covinits))) {
            thisinit <- covinits[[covlabels[i]]]
            if (!is.numeric(thisinit)) {
                warning("initial values for covariates should be numeric, ignoring")
                thisinit <- rep(0, nmatrix)
            }
            if (length(thisinit) != nmatrix) {
                warning("\"", covlabels[i], "\" initial values of length ", length(thisinit), ", should be ", nmatrix, ", ignoring")
                thisinit <- rep(0, nmatrix)
            }
            inits <- c(inits, thisinit)
        }
        else {
            inits <- c(inits, rep(0, nmatrix))
        }
    }
    npars <- ncovs*nmatrix
    ndpars <- max(unique(abs(constr)))
    ## which covariate each distinct covariate parameter corresponds to. Used in C (FormDQCov)
    whichdcov <- rep(1:ncovs, each=nmatrix)[!duplicated(abs(constr))]
    list(npars=npars,
         ndpars=ndpars,    # number of distinct covariate effect parameters
         ncovs=ncovs,
         constr=constr,
         whichdcov=whichdcov,
         covlabels=covlabels, # factors as separate contrasts
         covlabels.orig=covlabels.orig, # factors as one variable
         inits = inits,
         covmeans=covdata$covmeans
         )
}


msm.form.dmodel <- function(death, qmodel, hmodel)
{
    nstates <- qmodel$nstates
    statelist <- if (nstates==2) "1, 2" else if (nstates==3) "1, 2, 3" else paste("1, 2, ... ,",nstates)
    if (is.logical(death) && death==TRUE)
        states <- nstates
    else if (is.logical(death) && death==FALSE)
        states <- numeric(0) ## Will be changed to -1 when passing to C
    else if (!is.numeric(death)) stop("Death states indicator must be numeric")
    else if (length(setdiff(death, 1:nstates)) > 0)
        stop("Death states indicator contains states not in ",statelist)
    else states <- death
    ndeath <- length(states)
    if (hmodel$hidden) {
        ## Form death state info from hmmIdent parameters.
        ## Special observations in outcome data which denote death states
        ## are given as the parameter to hmmIdent()
        if (!all(hmodel$models[states] == match("identity", .msm.HMODELS)))
            stop("Death states should have the identity hidden distribution hmmIdent()")
        obs <- ifelse(hmodel$npars[states]>0, hmodel$pars[hmodel$parstate %in% states], states)
    }
    else obs <- states
    if (any (states %in% transient.msm(qmatrix=qmodel$qmatrix)))
        stop("Not all the \"death\" states are absorbing states")
    list(ndeath=ndeath, states=states, obs=obs)
}

msm.form.cmodel <- function(censor=NULL, censor.states=NULL, qmatrix)
{
    if (is.null(censor)) {
        ncens <- 0
        if (!is.null(censor.states)) warning("censor.states supplied but censor not supplied")
    }
    else {
        if (!is.numeric(censor)) stop("censor must be numeric")
        if (any(censor %in% 1:nrow(qmatrix))) warning("some censoring indicators are the same as actual states")
        ncens <- length(censor)
        if (is.null(censor.states)) {
            if (ncens > 1) {
                warning("more than one type of censoring given, but censor.states not supplied. Assuming only one type of censoring")
                ncens <- 1; censor <- censor[1]
            }
            absorbing <- absorbing.msm(qmatrix=qmatrix)
            if (!length(absorbing)) {
                warning("No absorbing state and no censor.states supplied. Ignoring censoring.")
                ncens <- 0
            }
            else {
                transient <- setdiff(seq(length=nrow(qmatrix)), absorbing)
                censor.states <- transient
                states.index <- c(1, length(censor.states)+1)
            }
        }
        else {
            if (ncens == 1) {
                if (!is.vector(censor.states) ||
                    (is.list(censor.states) && (length(censor.states) > 1)) )
                    stop("if one type of censoring, censor.states should be a vector, or a list with one vector element")
                if (!is.numeric(unlist(censor.states))) stop("censor.states should be all numeric")
                states.index <- c(1, length(unlist(censor.states))+1)
            }
            else {
                if (!is.list(censor.states)) stop("censor.states should be a list")
                if (length(censor.states) != ncens) stop("expected ", ncens, " elements in censor.states list, found ", length(censor.states))
                states.index <- cumsum(c(0, lapply(censor.states, length))) + 1
            }
            censor.states <- unlist(censor.states)
        }
    }
    if (ncens==0) censor <- censor.states <- states.index <- NULL
    ## Censoring information to be passed to C
    list(ncens = ncens, # number of censoring states
         censor = censor, # vector of their labels in the data
         states = censor.states, # possible true states that the censoring represents
         index = states.index # index into censor.states for the start of each true-state set, including an extra length(censor.states)+1
         )
}

### Observation scheme
### 1: snapshots,
### 2: exact transition times (states unchanging between observation times),
### 3: death (exact entry time but state at previous instant unknown)

msm.form.obstype <- function(obstype, nobs, state, dmodel, exacttimes)
{
    if (!is.null(obstype)) {
        if (!is.numeric(obstype)) stop("obstype should be numeric")
        if (length(obstype) == 1) obstype <- rep(obstype, nobs)
        else if (length(obstype) != nobs) stop("obstype of length ", length(obstype), ", expected 1 or ", nobs)
        if (any(! obstype %in% 1:3)) stop("elements of obstype should be 1, 2, or 3")
    }
    else if (!is.null(exacttimes) && exacttimes)
        obstype <- rep(2, nobs)
    else {
        obstype <- rep(1, nobs)
        if (dmodel$ndeath > 0)
            obstype[state %in% dmodel$obs] <- 3
    }
    obstype
}

msm.form.obstrue <- function(obstrue, nobs, hmodel) {
    if (!is.null(obstrue)) {
        if (!is.numeric(obstrue) && !is.logical(obstrue)) stop("obstrue should be logical or numeric")
        else if (length(obstrue) != nobs) stop("obstrue of length ", length(obstrue), ", expected ", nobs)
        if (!hmodel$hidden) warning("Specified obstrue for a non-hidden model, ignoring.")
    }
    else if (hmodel$hidden) obstrue <- rep(0, nobs)
    else obstrue <- rep(1, nobs)
    obstrue
}

### Transform set of sets of probs {prs} to {log(prs/pr1)}
msm.mnlogit.transform <- function(pars, plabs, states){
    res <- pars
    if (any(plabs=="p")) {
        whichst <- match(states[plabs == "p"], unique(states[plabs == "p"]))
        res[plabs == "p"] <- log(pars[plabs=="p"] / pars[plabs=="pbase"][whichst])
    }
    res
}

### Recalculate baseline misclassification probabilities to be 1 - the sum of the rest
msm.recalc.basep <- function(pars, plabs, states){
    res <- pars
    if (any(plabs=="p")) {
        psum <- tapply(pars[plabs=="p"], states[plabs=="p"], sum)
        whichst <- match(states[plabs == "p"], unique(states[plabs == "p"]))
        res[plabs == "pbase"] <- 1 - psum
    }
    res
}

### Transform set of sets of murs = {log(prs/pr1)} to probs {prs}
### ie psum = sum(exp(mus)),  pr1 = 1 / (1 + psum),  prs = exp(mus) / (1 + psum)
msm.mninvlogit.transform <- function(pars, plabs, states){
    res <- pars
    if (any(plabs=="p")) {
        psum <- tapply(exp(pars[plabs=="p"]), states[plabs=="p"], sum)
        res[plabs=="pbase"] <- 1 / (1 + psum)
        whichst <- match(states[plabs=="p"], unique(states[plabs=="p"]))
        res[plabs=="p"] <- exp(pars[plabs=="p"]) / (1 + psum[whichst])
    }
    res
}

msm.form.params <- function(qmodel, qcmodel, emodel, hmodel, fixedpars, est.initprobs)
{
    ## Categories of parameter:
    inits <- c(qmodel$inits, qcmodel$inits)
    ## Transition intensities
    ni <- qmodel$npars
    ## Covariates on transition intensities
    nc <- qcmodel$npars;
    plabs <- c(rep("qbase",ni), rep("qcov", nc))
    ## HMM response parameters
    nh <- sum(hmodel$npars)
    ## Covariates on HMM response distribution
    nhc <- sum(hmodel$ncoveffs)
    ## Initial state occupancy probabilities in HMM
    nip <- hmodel$nipars
    ## Covariates on initial state occupancy probabilities.
    nipc <- hmodel$nicoveffs
    npars <- ni + nc + nh + nhc + nip + nipc
    hmodel$pars <- msm.mnlogit.transform(hmodel$pars, hmodel$plabs, hmodel$parstate)
    inits <- c(inits, hmodel$pars, unlist(hmodel$coveffect))
    plabs <- c(plabs, hmodel$plabs, rep("hcov", nhc))
    if (nip > 0) {
        inits <- c(inits, hmodel$initprobs[-1])
        initplabs <- rep("initp",nip)
        initplabs[hmodel$initprobs[-1]==0] <- "initp0" # those initialised to zero will be fixed at zero
        plabs <- c(plabs, initplabs)
        if (nipc > 0) {
            inits <- c(inits, unlist(hmodel$icoveffect))
            plabs <- c(plabs, rep("initpcov",nipc))
        }
    }
    ## store indicator for which parameters are HMM location parameters (not HMM cov effects or initial state probs)
    hmmpars <- which(!(plabs %in% c("qbase","qcov","hcov","initp","initp0","initpcov")))
    for (lab in rownames(.msm.TRANSFORMS))
        inits[plabs==lab] <- get(.msm.TRANSFORMS[lab,"fn"])(inits[plabs==lab])
    names(inits) <- plabs
    ## Form constraint vector for complete set of parameters
    ## No constraints allowed on initprobs and their covs for the moment
    constr <- c(qmodel$constr, if(is.null(qcmodel$constr)) NULL else (ni + abs(qcmodel$constr))*sign(qcmodel$constr),
                ni + nc + hmodel$constr,
                ni + nc + nh + hmodel$covconstr, ni + nc + nh + nhc + seq(length=nip),
                ni + nc + nh + nip + seq(length=nipc))
    constr <- match(abs(constr), unique(abs(constr)))*sign(constr)
    ## parameters which are always fixed and not included in user-supplied fixedpars
    auxpars <- which(plabs %in% .msm.AUXPARS)
    duppars <- which(duplicated(abs(constr)))
    naux <- length(auxpars)
    ndup <- length(duppars)
    realpars <- setdiff(seq(npars), union(auxpars, duppars))
    nrealpars <- npars - naux - ndup
    if (is.logical(fixedpars))
        fixedpars <- if (fixedpars == TRUE) seq(nrealpars) else numeric()
    if (any(! (fixedpars %in% seq(along=realpars))))
        stop ( "Elements of fixedpars should be in 1, ..., ", npars - naux - ndup)
    fixedpars <- sort(c(realpars[fixedpars], auxpars))
    if (!est.initprobs)
        fixedpars <- union(fixedpars, which(plabs %in% c("initp","initp0","initpcov")))
    notfixed <- setdiff(seq(npars), fixedpars)
    allinits <- inits
    nfix <- length(fixedpars)
    optpars <- intersect(notfixed, which(!duplicated(abs(constr))))
    nopt <- length(optpars)
    inits <- inits[optpars]
    fixed <- (nfix + ndup == npars) # TRUE if all parameters are fixed, then no optim needed, just eval likelihood
    names(allinits) <- plabs; names(fixedpars) <- plabs[fixedpars]; names(plabs) <- NULL
    paramdata <- list(inits=inits, plabs=plabs, allinits=allinits, hmmpars=hmmpars,
                      fixed=fixed, notfixed=notfixed, optpars=optpars,
                      fixedpars=fixedpars, constr=constr,
                      npars=npars, nfix=nfix, nopt=nopt, ndup=ndup)
    paramdata
}

### Wrapper for the C code which evaluates the -2*log-likelihood for a Markov multi-state model with misclassification
### This is optimised by optim

likderiv.msm <- function(params, deriv=0, msmdata, qmodel, qcmodel, cmodel, hmodel, paramdata)
{
    do.what <- deriv
    p <- paramdata
    pars <- p$allinits;  plabs <- p$plabs
    pars[p$optpars] <- params
    ## Untransform parameters optimized on log/logit scale
    for (lab in rownames(.msm.TRANSFORMS))
        pars[plabs==lab] <- get(.msm.TRANSFORMS[lab,"inv"])(pars[plabs==lab])
    ## Before replication, transform probs on log(pr/pbase scale) back to pr scale,
    ## so that econstraint applies to pr not log(pr/pbase). After, transform back.
    pars[p$hmmpars] <- msm.mninvlogit.transform(pars[p$hmmpars], hmodel$plabs, hmodel$parstate)
    ## Replicate constrained parameters
    plabs <- plabs[!duplicated(abs(p$constr))][abs(p$constr)]
    pars <- pars[!duplicated(abs(p$constr))][abs(p$constr)]*sign(p$constr)
    pars[p$hmmpars] <- msm.mnlogit.transform(pars[p$hmmpars], hmodel$plabs, hmodel$parstate)
    ## In R, work with states / parameter indices / model indices 1, ... n. In C, work with 0, ... n-1
    msmdata$fromstate <- msmdata$fromstate - 1
    msmdata$tostate <- msmdata$tostate - 1
    msmdata$firstobs <- msmdata$firstobs - 1
    hmodel$models <- hmodel$models - 1
    hmodel$links <- hmodel$links - 1
    pars[plabs == "p"] <- exp(pars[plabs == "p"])
    initprobs <- c(1 - sum(pars[plabs=="initp"]), pars[plabs %in% c("initp","initp0")])
    initprobs <- initprobs / initprobs[1] ## initprobs[1] documented as not allowed to be zero. 
    
    lik <- .C("msmCEntry",
              as.integer(do.what),
              as.integer(as.vector(t(qmodel$imatrix))),
              as.double(pars[plabs=="qbase"]),
              as.double(as.vector(t(matrix(pars[plabs=="qcov"], nrow=qmodel$npars)))),
              as.double(pars[!(plabs %in% c("qbase", "qcov", "hcov","initp","initp0","initpcov"))]),
              as.double(pars[plabs=="hcov"]),

              ## data for non-HMM
              as.integer(msmdata$fromstate),
              as.integer(msmdata$tostate),
              as.double(msmdata$timelag),
              as.double(unlist(msmdata$covmat)), # covariate matrix by unique transition (non-HMM) or by obs (HMM/cens)
              as.double(unlist(msmdata$cov)), # covariate matrix by observation (non-HMM and calculating derivs by individual)
              as.integer(msmdata$covdata$whichcov), # this is really part of the model
              as.integer(msmdata$nocc),
              as.integer(msmdata$whicha),
              as.integer(msmdata$obstype),

              ## data for HMM or censored
              as.integer(match(msmdata$subject, unique(msmdata$subject))),
              as.double(msmdata$time),
              as.double(msmdata$state), # If this is a misc or censored state, this is indexed from 1.
              as.integer(msmdata$firstobs),
              as.integer(msmdata$obstrue),

              ## HMM specification
              as.integer(hmodel$hidden),
              as.integer(hmodel$models),
              as.integer(hmodel$npars),
              as.integer(hmodel$totpars),
              as.integer(hmodel$firstpar),
              as.integer(hmodel$ncovs),
              as.integer(hmodel$whichcovh),
              as.integer(hmodel$links),
              as.double(initprobs),
              as.integer(hmodel$nicovs),
              as.double(pars[plabs=="initpcov"]),
              as.integer(hmodel$whichcovi),

              ## various constants
              as.integer(qmodel$nstates),
              as.integer(qmodel$analyticp),
              as.integer(qmodel$iso),
              as.integer(qmodel$perm),
              as.integer(qmodel$qperm),
              as.integer(qmodel$npars),
              as.integer(qmodel$ndpars),
              as.integer(qcmodel$ndpars),
              as.integer(msmdata$nobs), # number of aggregated observations 
              as.integer(msmdata$n), # number of observations
              as.integer(msmdata$npts),  # HMM only
              as.integer(rep(qcmodel$ncovs, qmodel$npars)),

              as.integer(cmodel$ncens),
              as.integer(cmodel$censor),
              as.integer(cmodel$states),
              as.integer(cmodel$index - 1),

              ## constraints needed in C to calculate derivatives
              as.integer(qmodel$constr),
              as.integer(qcmodel$constr),
              as.integer(qcmodel$whichdcov),

              returned = double(if (deriv==1) qmodel$ndpars + qcmodel$ndpars
              else if (deriv==3) msmdata$npts*(qmodel$ndpars + qcmodel$ndpars)
              else 1),
              ## so that Inf values are allowed for parameters denoting truncation points of truncated distributions
              NAOK = TRUE
#              ,
#              PACKAGE = "msm"
              )
    ## transform derivatives wrt Q to derivatives wrt log Q
    if (deriv==1) {
        lik$returned[1:qmodel$ndpars] <-
            if (length(params)==0) lik$returned[1:qmodel$ndpars]*exp(p$allinits[!duplicated(p$constr)][1:qmodel$ndpars])
            else lik$returned[1:qmodel$ndpars]*exp(params[1:qmodel$ndpars])
    }
    ## subject-specific derivatives, to use for score residuals
    else if (deriv==3) {
        lik$returned <- matrix(lik$returned, nrow=msmdata$npts)
        lik$returned[,1:qmodel$ndpars] <-
            if (length(params)==0) lik$returned[,1:qmodel$ndpars]*rep(exp(p$allinits[!duplicated(p$constr)][1:qmodel$ndpars]), each=msmdata$npts)
            else lik$returned[,1:qmodel$ndpars]*rep(exp(params[1:qmodel$ndpars]), each=msmdata$npts)
    }
    lik$returned
}

lik.msm <- function(params, ...)
{
    likderiv.msm(params, deriv=0, ...)
}

deriv.msm <- function(params, ...)
{
    likderiv.msm(params, deriv=1, ...)
}

## Convert vector of MLEs into matrices 

msm.form.output <- function(whichp, model, cmodel, p)
{
    Matrices <- MatricesSE <- MatricesL <- MatricesU <- list()
    for (i in 0:cmodel$ncovs) {
        matrixname <- if (i==0) "logbaseline" else cmodel$covlabels[i] # name of the current output matrix.
        mat <- t(model$imatrix) # I fill matrices by row, while R fills them by column. Is this sensible...?
        if (whichp=="intens")
            parinds <- if (i==0) which(p$plabs=="qbase") else which(p$plabs=="qcov")[(i-1)*model$ndpars + 1:model$npars]
        if (whichp=="misc")
            parinds <- if (i==0) which(p$plabs=="p") else which(p$plabs=="hcov")[i + cmodel$ncovs*(1:model$npars - 1)]
        mat[t(model$imatrix)==1] <- p$params[parinds]
        mat <- t(mat)
        dimnames(mat) <- dimnames(model$imatrix)
        if (p$foundse && !p$fixed){
            intenscov <- p$covmat[parinds, parinds]
            intensse <- sqrt(diag(as.matrix(intenscov)))
            semat <- lmat <- umat <- t(model$imatrix)
            semat[t(model$imatrix)==1] <- intensse
            lmat[t(model$imatrix)==1] <- p$ci[parinds,1]
            umat[t(model$imatrix)==1] <- p$ci[parinds,2]
            semat <- t(semat); lmat <- t(lmat); umat <- t(umat)
            diag(semat) <- diag(lmat) <- diag(umat) <- 0
            dimnames(semat)  <- dimnames(mat)
        }
        else if (!p$fixed){
            semat <- lmat <- umat <- NULL
        }
        Matrices[[matrixname]] <- mat
        if (!p$fixed) {
            MatricesSE[[matrixname]] <- semat
            MatricesL[[matrixname]] <- lmat
            MatricesU[[matrixname]] <- umat
        }
    }
    list(Matrices=Matrices,     # list of baseline log intensities/logit misc probability matrix
                                        # and linear effects of covariates
         MatricesSE=MatricesSE,  # corresponding matrices of standard errors
         MatricesL=MatricesL,  # corresponding matrices of standard errors
         MatricesU=MatricesU  # corresponding matrices of standard errors
         )
}

## Format hidden Markov model estimates and CIs 

msm.form.houtput <- function(hmodel, p)
{
    hmodel$pars <- p$estimates.t[!(p$plabs %in% c("qbase","qcov","hcov","initp","initp0","initpcov"))]
    hmodel$coveffect <- p$estimates.t[p$plabs == "hcov"]
    hmodel$fitted <- !p$fixed
    hmodel$foundse <- p$foundse
    if (hmodel$nip > 0) {
        if (hmodel$foundse) {
            initpsum <- sum(p$estimates.t[p$plabs == "initp"])
            hmodel$initprobs <- rbind(c(1 - initpsum, NA, NA),
                                      cbind(p$estimates.t[p$plabs %in% c("initp","initp0")],
                                            p$ci[p$plabs %in% c("initp","initp0"),,drop=FALSE]))
            rownames(hmodel$initprobs) <- paste("State",1:hmodel$nstates)
            colnames(hmodel$initprobs) <- c("Estimate", "LCL", "UCL")
            if (any(hmodel$nicovs > 0)) {
                covnames <- names(hmodel$icoveffect)
                hmodel$icoveffect <- cbind(p$estimates.t[p$plabs == "initpcov"],  p$ci[p$plabs == "initpcov",,drop=FALSE])
                iplabs <- p$plabs[p$plabs %in% c("initp","initp0")]
                whichst <- which(iplabs == "initp") + 1  # init probs for which states have covs on them (not the zero probs)
                rownames(hmodel$icoveffect) <- paste(covnames, paste("State",whichst), sep=", ")
                colnames(hmodel$icoveffect) <- c("Estimate", "LCL", "UCL")
            }
        }
        else {
            hmodel$initprobs <- c(1 - sum(p$estimates.t[p$plabs == "initp"]),
                                  p$estimates.t[p$plabs %in% c("initp","initp0")])
            names(hmodel$initprobs) <- paste("State", 1:hmodel$nstates)
            if (any(hmodel$nicovs > 0)) {
                covnames <- names(hmodel$icoveffect)
                hmodel$icoveffect <- p$estimates.t[p$plabs == "initpcov"]
                names(hmodel$icoveffect) <- paste(covnames, paste("State",2:hmodel$nstates), sep=", ")
            }
        }
    }
    if (hmodel$foundse) {
        hmodel$ci <- p$ci[!(p$plabs %in% c("qbase","qcov","hcov","initp","initp0","initpcov")), , drop=FALSE]
        hmodel$covci <- p$ci[p$plabs %in% c("hcov"), ]
    }
    names(hmodel$pars) <- hmodel$plabs
    hmodel
}

## Table of 'transitions': previous state versus current state

statetable.msm <- function(state, subject, data=NULL)
{
    if(!is.null(data)) {
        data <- as.data.frame(data)
        state <- eval(substitute(state), data, parent.frame())
    }
    n <- length(state)
    if (!is.null(data))
        subject <-
            if(missing(subject)) rep(1,n) else eval(substitute(subject), data, parent.frame())
    subject <- match(subject, unique(subject))
    prevsubj <- c(NA, subject[1:(n-1)])
    previous <- c(NA, state[1:(n-1)])
    previous[prevsubj!=subject] <- NA
    ntrans <- table(previous, state)
    names(dimnames(ntrans)) <- c("from", "to")
    ntrans
}

## Calculate crude initial values for transition intensities by assuming observations represent the exact transition times

crudeinits.msm <- function(formula, subject, qmatrix, data=NULL, censor=NULL, censor.states=NULL)
{
    cens <- msm.form.cmodel(censor, censor.states, qmatrix)
    mf <- model.frame(formula, data=data)
    state <- mf[,1]
    time <- mf[,2]
    msm.check.qmatrix(qmatrix)
    msm.check.state(nrow(qmatrix), state, cens$censor)
    n <- length(state)
    if (missing(subject)) subject <- rep(1, n)
    if (!is.null(data))
        subject <- eval(substitute(subject), as.list(data), parent.frame())
    subject <- match(subject, unique(subject))
    nocens <- (! (state %in% cens$censor) )
    state <- state[nocens]; subject <- subject[nocens]; time <- time[nocens]
    n <- length(state)
    nextsubj <- c(subject[2:n], NA)
    lastsubj <- (subject != nextsubj)
    timecontrib <- ifelse(lastsubj, NA, c(time[2:n], 0) - time)
    tottime <- tapply(timecontrib[!lastsubj], state[!lastsubj], sum) # total time spent in each state
    ntrans <- statetable.msm(state, subject, data=NULL) # table of transitions
    nst <- nrow(qmatrix)
    estmat <- matrix(0, nst, nst)
    rownames(estmat) <- colnames(estmat) <- paste(1:nst)
    tab <- sweep(ntrans, 1, tottime, "/")
    for (i in 1:nst) # Include zero rows for states for which there were no transitions
        for (j in 1:nst)
            if ((paste(i) %in% rownames(tab)) && (paste(j) %in% colnames(tab)))
                estmat[paste(i), paste(j)] <- tab[paste(i),paste(j)]
    estmat[qmatrix == 0] <- 0 #
    estmat <- msm.fixdiag.qmatrix(estmat)
    rownames(estmat) <- rownames(qmatrix)
    colnames(estmat) <- colnames(qmatrix)
    estmat
}

### Construct a model with time-dependent transition intensities. 
### Form a new dataset with censored states and extra covariate, and
### form a new censor model, given change times in tcut

msm.pci <- function(tcut, dat, qmodel, cmodel, center)
{
    if (!is.numeric(tcut)) stop("Expected \"tcut\" to be a numeric vector of change points")
    old <- as.data.frame(dat[c("subject","time","state","obstype","obstrue")])
    if (dat$ncovs > 0)
        old[c("covmat","covmat.orig")] <- dat[c("covmat","covmat.orig")]
    ## new dataset
    ntcut <- length(tcut)
    nextra <- ntcut*dat$npts
    extra <- data.frame(subject = rep(unique(dat$subject), each=ntcut),
                        time = rep(tcut, dat$npts),
                        state = rep(NA, nextra),
                        obstype = rep(1, nextra),
                        obstrue = rep(TRUE, nextra),
                        pci.imp = 1
                        )
    old$pci.imp <- 0
    if (dat$ncovs > 0){
        extra$covmat <- as.data.frame(matrix(NA, nrow=nextra, ncol=ncol(old$covmat)))
        extra$covmat.orig <- as.data.frame(matrix(NA, nrow=nextra, ncol=ncol(old$covmat.orig)))
        rownames(old$covmat.orig) <- rownames(old$covmat) <- 1:nrow(old) 
        rownames(extra$covmat.orig) <- rownames(extra$covmat) <- nrow(old) + 1:nrow(extra) # get rid of dup / null rownames errors
    }
    ## merge new and old observations 
    new <- rbind(old, extra)
    new <- new[order(new$subject, new$time),]
    label <- if (cmodel$ncens > 0) max(cmodel$censor)*2 else qmodel$nstates + 1 
    new$state[is.na(new$state)] <- label
    ## Only keep cutpoints within range of each patient's followup
    mintime <- tapply(old$time, old$subject, min)[as.character(unique(old$subject))]
    maxtime <- tapply(old$time, old$subject, max)[as.character(unique(old$subject))]
    nobspt <- as.numeric(table(new$subject)[as.character(unique(new$subject))])
    new <- new[new$time >= rep(mintime, nobspt) & new$time <= rep(maxtime, nobspt), ]

    ## drop imputed observations at times when there was already an observation
    ## assumes there wasn't already duplicated obs times 
    prevsubj <- c(NA,new$subject[1:(nrow(new)-1)]); nextsubj <- c(new$subject[2:nrow(new)], NA)
    prevtime <- c(NA,new$time[1:(nrow(new)-1)]); nexttime <- c(new$time[2:nrow(new)], NA)
    prevstate <- c(NA,new$state[1:(nrow(new)-1)]); nextstate <- c(new$state[2:nrow(new)], NA)
    new <- new[!((new$subject==prevsubj & new$time==prevtime & new$state==label & prevstate!=label) |
                 (new$subject==nextsubj & new$time==nexttime & new$state==label & nextstate!=label))
               ,]
    
    ## Carry last value forward for other covariates
    if (dat$ncovs > 0) {
        eind <- which(is.na(new$covmat[,1]))
        while(length(eind) > 0){
            new$covmat[eind,] <- new$covmat[eind - 1,]
            new$covmat.orig[eind,] <- new$covmat.orig[eind - 1,]
            eind <- which(is.na(new$covmat[,1]))
        }
    }
    
    ## constants in dataset
    new <- as.list(new)
    new$nobs <- new$n <- n <- length(new$state)
    new$npts <- dat$npts
    new$firstobs <- c(1, which(new$subject[2:n] != new$subject[1:(n-1)]) + 1, n+1)
    new$ncovs <- dat$ncovs + ntcut

    ## Check range of cut points
    if (any(tcut < min(dat$time)))
      warning("Time cut point", if (sum(tcut < min(dat$time)) > 1) "s " else " ",
                paste(tcut[tcut<min(dat$time)],collapse=","),
                " less than minimum observed time of ",min(dat$time))
    if (any(tcut > max(dat$time)))
        warning("Time cut point", if (sum(tcut > max(dat$time)) > 1) "s " else " ",
                paste(tcut[tcut>max(dat$time)],collapse=","),
                " greater than maximum observed time of ",max(dat$time))
    tcut <- tcut[tcut > min(dat$time) & tcut < max(dat$time)]
    ntcut <- length(tcut)
    if (ntcut==0) 
        res <- NULL # no cut points in range of data, continue with no time-dependent model
    else {
        ## Insert new covariate in data representing time period
        tcovlabel <- "timeperiod"
        while (tcovlabel %in% dat$covlabels)
            tcovlabel <- paste(tcovlabel, ".1", sep="")
        tcov <- factor(cut(new$time, c(-Inf,tcut,Inf), right=FALSE))
        levs <- levels(tcov)
        levels(tcov) <- gsub(" ","", levs) # get rid of spaces in e.g. [10, Inf) levels 
        assign(tcovlabel, tcov)
        mm <- model.matrix(as.formula(paste("~", tcovlabel)))[,-1,drop=FALSE]
        new$covmat <- cbind(new$covmat, mm)
        new$covmat.orig <- if(is.null(new$covmat.orig)) data.frame(timeperiod=tcov) else cbind(new$covmat.orig, timeperiod=tcov)
        if (center) new$covmat <- sweep(new$covmat, 2, colMeans(new$covmat))
        
        ## new censoring model 
        cmodel$ncens <- cmodel$ncens + 1
        cmodel$censor <- c(cmodel$censor, label)
        cmodel$states <- c(cmodel$states, 1:qmodel$nstates)
        cmodel$index <- if (is.null(cmodel$index)) 1 else cmodel$index
        cmodel$index <- c(cmodel$index, length(cmodel$states) + 1)

        ## new auxiliary information about covariates
        for (i in c("covdata","misccovdata","hcovdata","icovdata")) new[[i]] <- dat[[i]]
        new$covlabels <- c(dat$covlabels, colnames(mm))
        new$covlabels.orig <- c(dat$covlabels.orig, tcovlabel)
        new$covdata$covlabels <- c(dat$covdata$covlabels, colnames(mm))
        new$covdata$ncovs <- dat$covdata$ncovs + ntcut
        new$covdata$covmeans <- c(dat$covdata$covmeans, colMeans(mm))
        new$covdata$covfactor <- c(dat$covdata$covfactor, timeperiod=TRUE)
        new$covdata$covfactorlevels <- c(dat$covdata$covfactorlevels, list(timeperiod=levels(tcov)))
        new$covdata$covlabels.orig <- c(dat$covdata$covlabels.orig, tcovlabel)
        new$covdata$whichcov <- match(new$covdata$covlabels, new$covlabels)
        new$covdata$whichcov.orig <- match(new$covdata$covlabels.orig, new$covlabels.orig)

        res <- list(dat=new, cmodel=cmodel)
    }
    res
}


### Unload shared library when package is detached with unloadNamespace("msm")
.onUnload <- function(libpath) { library.dynam.unload("msm", libpath) }

