### METHODS FOR MSM OBJECTS

print.msm <- function(x, ...)
{
    cat("\nCall:\n", deparse(x$call), "\n\n", sep = "")

    if (!attr(x,"fixed")) {
        cat ("Maximum likelihood estimates: \n")
        covmessage <- if (x$qcmodel$ncovs == 0) "" else "with covariates set to their means"
        for (i in c("baseline", x$qcmodel$covlabels)) {
            title <-
                if (i == "baseline") paste("Transition intensity matrix",covmessage,"\n")
                else paste("Log-linear effects of", i, "\n")
            cat (title, "\n")
            print.ci(x$Qmatrices[[i]], x$QmatricesL[[i]], x$QmatricesU[[i]])
            cat("\n")
        }
        if (x$emodel$misc) {
            for (i in c("baseline", x$ecmodel$covlabels)) {
                title <-
                    if (i == "baseline") paste("Misclassification matrix",covmessage,"\n")
                    else paste("Effects of", i, "on log (P(state r)/P(baseline state))\n")
                cat (title, "\n")
                print.ci(x$Ematrices[[i]], x$EmatricesL[[i]], x$EmatricesU[[i]])
                cat("\n")
            }
            if (any(x$paramdata$plabs[x$paramdata$notfixed] == "initp")) {
                cat("Initial state occupancy probabilities\n\n")
                print(x$hmodel$initprobs)
                cat("\n")
                if (any(x$hmodel$nicovs > 0)) {
                    cat("Covariates on logit initial state probabilities\n")
                    print(x$hmodel$icoveffect)
                }
                cat("\n")
            }
        }
        else if (x$hmodel$hidden) {print(x$hmodel); cat("\n")}
    }
    cat ("-2 * log-likelihood: ", x$minus2loglik, "\n")

}

summary.msm <- function(object, # fitted model
                        times = NULL,  # times at which to compare observed and expected prevalences
                        timezero = NULL,
                        initstates = NULL,
                        covariates = "mean",
                        misccovariates = "mean",
                        hazard.scale = 1,
                        ...
                        )
{
    if (!inherits(object, "msm")) stop("expected object to be a msm model")
    prevalences <- prevalence.msm(object, times, timezero, initstates, covariates, misccovariates)
    if (object$qcmodel$ncovs > 0) {
        if (missing (hazard.scale))
            hazard.scale <- rep(1, object$data$covdata$ncovs)
        hazard <- hazard.msm(object)
    }
    else {hazard <- hazard.scale <- NULL}
    ret <- list(prevalences=prevalences,
                hazard=hazard,
                hazard.scale=hazard.scale)
    class(ret) <- "summary.msm"
    ret
}

print.summary.msm <- function(x,...)
{
    if (!is.null(x$prevalences)) {
        cat("\nObserved numbers of individuals occupying states at each time\n\n")
        print(x$prevalences$Observed)
        cat("\nExpected numbers of individuals occupying states at each time\n\n")
        print(x$prevalences$Expected)
        cat("\nObserved prevalences of states (percentages of population at risk)\n\n")
        print(x$prevalences$"Observed percentages")
        cat("\nExpected prevalences of states (percentages of population at risk)\n\n")
        print(x$prevalences$"Expected percentages")
    }
    i <- 1
    for (cov in names(x$hazard)) {
        cat ("\nTransition hazard ratios corresponding to covariate effects\n\n" )
        cat (cov, " ( unit of",x$hazard.scale[i],")\n")
        print(round(x$hazard[[cov]], 2))
        i <- i+1
    }
    invisible()
}

### Estimated survival probability from each state 

plot.msm <- function(x, from=NULL, to=NULL, range=NULL, covariates="mean", legend.pos=NULL, xlab="Time", ylab="Fitted survival probability", lwd=1,...)
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    if (is.null(from))
        from <- transient.msm(x)
    else {
        if (!is.numeric(from)) stop("from must be numeric")
        if (any (! (from %in% 1:x$qmodel$nstates ) ) )
            stop("from must be a vector of states in 1, ..., ", x$qmodel$nstates)
    }
    if (is.null(to))
        to <- max(absorbing.msm(x))
    else {
        if (!is.numeric(to)) stop("to must be numeric")
        if (! (to %in% absorbing.msm(x) ) ) stop("to must be an absorbing state")
    }
    if (is.null(range))
        rg <- range(x$data$time)
    else {
        if (!is.numeric(range) || length(range)!= 2) stop("range must be a numeric vector of two elements")
        rg <- range
    }
    timediff <- (rg[2] - rg[1]) / 50
    times <- seq(rg[1], rg[2], timediff)
    pr <- numeric()
    cols <- rainbow(length(from))
    for (t in times)
        pr <- c(pr, pmatrix.msm(x, t, times[1], covariates)[from[1], to])
    plot(times, 1 - pr, type="l", xlab=xlab, ylab=ylab, lwd=lwd,
         ylim=c(0,1), lty = 1, col=cols[1],...)
    lt <- 2
    for (st in from[-1]){
        pr <- numeric()
        for (t in times)
            pr <- c(pr, pmatrix.msm(x, t, times[1], covariates)[st, to])
        lines(times, 1 - pr, type="l", lty = lt, lwd=lwd, col=cols[lt],...)
        lt <- lt+1
    }
    if (!is.numeric(legend.pos) || length(legend.pos) != 2)
        legend.pos <- c(max(times) - 15*timediff, 1)
    legend(legend.pos[1], legend.pos[2], legend=paste("From state",from), lty = seq(lt-1), col=cols, lwd=lwd)
    invisible()
}

### Plot KM estimate of time to first occurrence of each state

plotprog.msm <- function(formula, subject, data, legend.pos=NULL, xlab="Time", ylab="1 - incidence probability", lwd=1, xlim=NULL, ...) {
    data <- na.omit(data)
    mf <- model.frame(formula, data=data)
    state <- mf[,1]
    time <- mf[,2]
    if (!is.null(data))
        subject <- eval(substitute(subject), as.list(data), parent.frame())
    subject <- match(subject, unique(subject))
    rg <- range(time)
    if (is.null(xlim)) xlim=rg
    plot(0, xlim=xlim, ylim=c(0,1), type="n", xlab=xlab, ylab=ylab, lwd=lwd, ...)
    states <- sort(unique(state))[-1]
    cols <- rainbow(length(states))
    for (i in states) {
        dat <- cbind(subject, time, state)
        st <- as.data.frame(
                            do.call("rbind", by(dat, subject, function(x)
                                            {
                                                c(anystate = if(any(x[,"state"]>=i)) 1 else 0, 
                                                  mintime = if(any(x[,"state"]>=i)) min(x[x[,"state"] >= i, "time"]) else max(x[,"time"]))
                                            }
                                                ))) # slow 
        lines(survfit(Surv(st$mintime,st$anystate) ~ 1),col=cols[i-1],lty=i-1, lwd=lwd,...)
    }
    timediff <- (rg[2] - rg[1]) / 50
    if (!is.numeric(legend.pos) || length(legend.pos) != 2)
        legend.pos <- c(max(time) - 25*timediff, 1)
    legend(legend.pos[1], legend.pos[2], lty=states-1, lwd=lwd, col=cols,
           legend=paste("To state", states, c(rep("or greater", length(states)-1), "")))
    invisible()
}


### Likelihood surface plots

surface.msm <- function(x, params=c(1,2), np=10, type=c("contour","filled.contour","persp","image"),
                        point=NULL, xrange=NULL, yrange=NULL,...)
{
    type <- match.arg(type)
    if (is.null(point))
        point <- x$paramdata$opt$par
    se <- sqrt(diag(solve(0.5 * x$paramdata$opt$hessian)))
    i1 <- params[1]; i2 <- params[2]
    if (is.null(xrange)) {
        pmin <- point[i1] - 2*se[i1]
        pmax <- point[i1] + 2*se[i1]
        p1 <- seq(pmin, pmax, length=np)
    }
    else p1 <- seq(xrange[1], xrange[2], length=np)
    if (is.null(yrange)){
        pmin <- point[i2] - 2*se[i2]
        pmax <- point[i2] + 2*se[i2]
        p2 <- seq(pmin, pmax, length=np)
    }
    else p2 <- seq(yrange[1], yrange[2], length=np)

    z <- matrix(nrow=np, ncol=np)
    for (i in 1:np) {
        for (j in 1:np) {
            point[i1] <- p1[i]; point[i2] <- p2[j]
            z[i,j] <- -0.5*likderiv.msm(point, 0, x$data, x$qmodel, x$qcmodel, x$cmodel, x$hmodel, x$paramdata)
        }
    }

    switch(type,
           contour = contour(p1, p2, z, ...),
           filled.contour = filled.contour(p1, p2, z, ...),
           image = image(p1, p2, z, ...),
           persp = persp(p1, p2, z, zlab="Log-likelihood",...)
           )
    invisible()
}

contour.msm <- function(x, ...)
{
    surface.msm(x, type="contour",...)
}

persp.msm <- function(x, ...)
{
    surface.msm(x, type="persp",...)
}

image.msm <- function(x, ...)
{
    surface.msm(x, type="image",...)
}

### Given a "covariates" argument of an extractor function containing
### covariates which interact in the model, form the corresponding
### "covariates" argument with the interactions expanded.

expand.interactions.msm <- function(covariates, covlabels){
    cn.nointer <- names(covariates)
    elist <- strsplit(covlabels, ":")
    elist <- lapply(elist, function(x)covariates[x])
    elist <- lapply(elist, function(x)prod(unlist(x)))
    names(elist) <- covlabels
    elist
}

### Given a "covariates" argument of an extractor function containing
### factor covariates, convert the factor covariates to numeric
### contrasts.  For example, for a categorical covariate "smoke" with
### three levels "NON","CURRENT","EX", with baseline level "NON",
### convert list(smoke="CURRENT") to list(smokeCURRENT=1, smokeEX=0)
### Any unspecified covariate values are set to zero. 
### Any unknown covariates are dropped with a warning.

### covlabels includes interactions

factorcov2numeric.msm <- function(covariates, x, intmisc="intens") {
    covdata <- if (intmisc=="intens") x$data$covdata else x$data$misccovdata
    covnames <- names(covdata$covfactor)
    if (is.null(names(covariates))) {
        if (length(covariates)!=length(covnames)) stop("Expected covariate list of length ",length(covnames))
        names(covariates) <- covnames
    }
    all.covnames <- union(x$data$covdata$covlabels,covnames) # including both factor and contrast names
    miss.covs <- ! names(covariates) %in% all.covnames
    if (any(miss.covs)){
        plural <- if(sum(miss.covs)>1) "s" else ""
        warning("Covariate",plural," \"", paste(names(covariates)[which(!names(covariates)  %in% all.covnames)], collapse=", "), "\" unknown, ignoring")
    }
    cfac <- covariates[names(covariates) %in% covnames[which(covdata$covfactor)]]
    cnum <- covariates[! names(covariates) %in% covnames[which(covdata$covfactor)]]
    cfac.new <- list()
    for (i in seq(along=cfac)) {
        levs.i <- covdata$covfactorlevels[[names(cfac)[[i]]]]
        cfac.i <- rep(0, length(levs.i))
        if (! cfac[[i]] %in% levs.i) stop("Level \"", cfac[[i]], "\" of covariate ", names(cfac)[[i]], " unknown")
        cfac.i[match(cfac[[i]], levs.i)] <- 1
        names(cfac.i) <- paste(names(cfac)[[i]], levs.i, sep="")
        cfac.i <- as.list(cfac.i[-1])
        cfac.new <- c(cfac.new, cfac.i)
    }
    covlabels.noint <- covdata$covlabels[setdiff(seq(along=covdata$covlabels), grep(":", covdata$covlabels))]
    covs.out <- as.list(numeric(length(covlabels.noint)))
    names(covs.out) <- covlabels.noint
    covs.out[names(cnum)] <- cnum
    covs.out[names(cfac.new)] <- cfac.new
    covs.out <- expand.interactions.msm(covs.out, covdata$covlabels)
    covs.out
}

### Extract the transition intensity matrix at given covariate values

qmatrix.msm <- function(x, # fitted msm model
                        covariates = "mean",  # covariate values to calculate transition matrix for
                        sojourn = FALSE,      # also calculate mean sojourn times and their standard errors
                        ci=c("delta","normal","bootstrap","none"), 
                        cl=0.95,
                        B=1000
                        )
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    qematrix.msm(x, covariates, intmisc="intens", sojourn=sojourn, ci=ci, cl=cl, B=B)
}

### Extract the misclassification probability matrix at given covariate values

ematrix.msm <- function(x,
                        covariates = "mean",
                        ci=c("delta","normal","bootstrap","none"), 
                        cl=0.95, B=1000)
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    if (!x$emodel$misc)
        NULL
    else
        qematrix.msm(x, covariates, intmisc="misc", sojourn=FALSE, ci=ci, cl=cl, B=B)
}

### Extract either intensity or misclassification matrix

qematrix.msm <- function(x, covariates="mean", intmisc="intens", sojourn=FALSE, ci=c("delta","normal","bootstrap","none"), cl=0.95, B=1000)
{
    nst <- x$qmodel$nstates
    if (intmisc=="intens"){
        ni <- x$qmodel$npars
        if (is.list(covariates))
            nc <- x$qcmodel$ncovs
        else if (((covariates == "mean") && x$center) || ((covariates == 0 ) && !x$center))
            nc <- 0
        else nc <- x$qcmodel$ncovs
        if (nc==0){
            logest <- x$Qmatrices$logbaseline
            mat <- exp(logest)
            mat[x$qmodel$imatrix == 0] <- 0
            mat <- msm.fixdiag.qmatrix(mat)
        }
        covlabels <- x$qcmodel$covlabels
        covmeans <- x$qcmodel$covmeans
    }
    else if (intmisc=="misc"){
        ni <- x$emodel$npars
        nc <- if (!is.list(covariates) &&
                  ((covariates == "mean") && x$center) ||
                  ((covariates == 0) && !x$center))
            0 else x$ecmodel$ncovs
        if (nc==0){
            logest <- x$Ematrices$logitbaseline
            plabs <- x$emodel$imatrix; plabs[x$emodel$imatrix==1] <- "p"; diag(plabs)[rowSums(x$emodel$imatrix)>0] <- "pbase"
            mat <- matrix(msm.mninvlogit.transform(t(logest), t(plabs), rep(1:nst, each=nst)), nrow=nst, byrow=TRUE)
            diag(mat)[rowSums(x$emodel$imatrix)==0] <- 1
        }
        covlabels <- x$ecmodel$covlabels
        covmeans <- x$ecmodel$covmeans
    }

    se <- lse <- numeric(ni)
    if ((nc == 0) && (is.list(covariates)) && (length(covariates) > 0))
        warning(paste("Ignoring covariates - no covariates in model for",
                      if (intmisc=="intens") "transition intensities" else "misclassification probabilities"))

    covs.orig <- covariates # with factors as labels 
    if (nc > 0) {
        if (!is.list(covariates)) {
            if (covariates == 0 && x$center) # if no centering, then can't end up in this block, as no need to adjust. 
            {covariates <- list();  for (i in 1 : nc) covariates[[covlabels[i]]] <- 0}
            else if (covariates == "mean" && !x$center) # if center, then can't end up in this block, as no need to adjust. 
            {covariates <- list();  for (i in 1 : nc) covariates[[covlabels[i]]] <- covmeans[i]}
            else stop("covariates argument must be 0, \"mean\", or a list of values for each named covariate")
        }
        else {
            ## Check supplied list of covariate values, convert factors to numeric contrasts, expand interactions, set unknown values to zero. 
            ## Maybe merge above block of code with this? tidy up other calls e.g. qratio.se, qmatrix.diagse? 
            covariates <- factorcov2numeric.msm(covariates, x, intmisc)
        }
        if (intmisc=="intens"){
            logest <- x$Qmatrices$logbaseline
            for (i in 1 : nc) {
                covi <- if (x$center) covariates[[i]] - covmeans[i] else covariates[[i]]
                logest <- logest + x$Qmatrices[[i+1]] * covi
            }
            mat <- exp(logest)
            mat[x$qmodel$imatrix == 0] <- 0
            mat <- msm.fixdiag.qmatrix(mat)
        }
        else if (intmisc=="misc"){
            logest <- x$Ematrices$logitbaseline
            for (i in 1 : nc) {
                covi <- if (x$center) covariates[[i]] - covmeans[i] else covariates[[i]]
                logest <- logest + x$Ematrices[[i+1]] * covi
            }
            plabs <- x$emodel$imatrix; plabs[x$emodel$imatrix==1] <- "p"; diag(plabs)[rowSums(x$emodel$imatrix)>0] <- "pbase"
            mat <- matrix(msm.mninvlogit.transform(t(logest), t(plabs), rep(1:nst, each=nst)), nrow=nst, byrow=TRUE)
            diag(mat)[rowSums(x$emodel$imatrix)==0] <- 1
        }
    }
    if (sojourn) soj = -1 / diag(mat)

    ci <- match.arg(ci)
    if (x$foundse && (ci!="none")) {
        if (ci == "delta") { 
            ## Work out standard errors.
            ## Transformation for delta method is (intensities)
            ##  exp (x1 + x2 (cov1 - covmean1) + x3 (cov2 - covmean2) + ... )
            ## expit(sum covs)  / (1 + expit(sum(covs)))    or   1  /  (1  +  expit(sum(covs)))
            ## Use delta method to find approximate SE of the transform on log scale
            ## Work out a CI for this by assuming normal and transforming back
            coefs <- if (!is.list(covariates) && (covariates=="mean")) 1 else c(1, unlist(covariates) - covmeans)
            semat <- lsemat <- lmat <- umat <- matrix(0, nst, nst)
            if (intmisc=="intens") {
                form <- as.formula(paste("~", expsum(seq(nc + 1), coefs)))
                lform <- as.formula(paste("~", lsum(seq(nc + 1), coefs)))
                ## indices into estimates vector of all intens/miscs, intens covs / misc covs
                inds <- seq(length=x$qmodel$npars + x$qcmodel$npars)
                for (i in 1 : ni){
                    ## indices into estimates vector of all intens/miscs, intens covs / misc covs for that particular fromstate-tostate.
                    parinds <- inds[seq(i, (nc * ni + i), ni)]
                    ests <- x$estimates[parinds]
                    cov <- x$covmat[parinds, parinds]
                    se[i] <- deltamethod(form, ests, cov)
                    lse[i] <- deltamethod(lform, ests, cov)
                }
                ivector <- as.numeric(t(x$qmodel$imatrix))
                semat[ivector == 1] <- se; semat <- t(semat)
                lsemat[ivector == 1] <- lse; lsemat <- t(lsemat)
                lmat <- exp(logest - qnorm(1 - 0.5*(1 - cl))*lsemat)
                umat <- exp(logest + qnorm(1 - 0.5*(1 - cl))*lsemat)
                imatrix <- x$qmodel$imatrix
                lmat[imatrix == 0] <- umat[imatrix == 0] <- 0
                ## SEs of diagonal entries
                diagse <- qmatrix.diagse.msm(x, covariates, sojourn, ni, ivector, nc, covlabels, covmeans)
                diag(semat) <- diagse$diagse
                diag(lmat) <- sign(diag(mat)[1]) * (exp(log(abs(diag(mat))) - sign(diag(mat)[1]) * qnorm(1 - 0.5*(1 - cl))*diagse$diaglse))
                diag(umat) <- sign(diag(mat)[1]) * (exp(log(abs(diag(mat))) + sign(diag(mat)[1]) * qnorm(1 - 0.5*(1 - cl))*diagse$diaglse))
                if (sojourn) {
                    sojse <- diagse$sojse
                    sojl <- exp(log(soj) - qnorm(1 - 0.5*(1 - cl))*diagse$sojlse)
                    soju <- exp(log(soj) + qnorm(1 - 0.5*(1 - cl))*diagse$sojlse)
                }
            }
            else if (intmisc=="misc"){
                p.se <- p.se.msm(x$qmodel, x$emodel, x$hmodel, x$qcmodel, x$ecmodel, x$paramdata, x$center, covariates)
                ivector <- as.numeric(t(x$emodel$imatrix))
                semat[ivector==1] <- p.se$se[p.se$lab=="p"]; semat <- t(semat)
                lmat[ivector==1] <- p.se$LCL[p.se$lab=="p"]; lmat <- t(lmat)
                umat[ivector==1] <- p.se$UCL[p.se$lab=="p"]; umat <- t(umat)
                diag(semat)[rowSums(x$emodel$imatrix)>0] <- p.se$se[p.se$lab=="pbase"]
                diag(lmat)[rowSums(x$emodel$imatrix)>0] <- p.se$LCL[p.se$lab=="pbase"]
                diag(umat)[rowSums(x$emodel$imatrix)>0] <- p.se$UCL[p.se$lab=="pbase"]
                diag(lmat)[rowSums(x$emodel$imatrix)==0] <- diag(umat)[rowSums(x$emodel$imatrix)==0] <- 1
            }
        }
        else if (ci %in% c("normal","bootstrap")) {
            q.ci <- if (ci=="normal")
                qematrix.normci.msm(x, covs.orig, intmisc, sojourn, cl, B) else qematrix.ci.msm(x, covs.orig, intmisc, sojourn, cl, B)
            if (sojourn) {
                soj.ci <- q.ci$soj
                q.ci <- q.ci$q                
                sojl <- soj.ci[1,]; soju <- soj.ci[2,]; sojse <- soj.ci[3,]
            }
            lmat <- q.ci[,,1]; umat <- q.ci[,,2]; semat <- q.ci[,,3]
        }
        dimnames(semat) <- dimnames(lmat) <- dimnames(umat) <- dimnames(x$qmodel$qmatrix)
    }
    else semat <- lmat <- umat <- sojse <- sojl <- soju <- NULL

    dimnames(mat) <-  dimnames(x$qmodel$qmatrix)
    if (ci=="none") res <- if (sojourn) soj else mat
    else {
        if (sojourn)
            res <- list(estimates=mat, SE=semat, L=lmat, U=umat, sojourn=soj, sojournSE=sojse, sojournL=sojl, sojournU=soju)
        else
            res <- list(estimates=mat, SE=semat, L=lmat, U=umat)
        class(res) <- "msm.est"
    }
    res
}

print.msm.est <- function(x, digits=NULL, ...)
{
    if (is.list(x))
        print.ci(x$estimates, x$L, x$U, digits=digits)
    else print(unclass(x))
}

print.ci <- function(x, l, u, digits=NULL)
{
    est <- formatC(x, digits=digits)
    if (!is.null(l)) {
        low <- formatC(l, digits=digits)
        upp <- formatC(u, digits=digits)
        res <- paste(est, " (", low, ",", upp, ")", sep="")
        res[x==0] <- 0
    }
    else res <- est
    dim(res) <- dim(x)
    dimnames(res) <- dimnames(x)
    names(res) <- names(x)
    print(res, quote=FALSE)
}

### Work out standard errors of diagonal entries of intensity matrix, or sojourn times, using delta method

qmatrix.diagse.msm <- function(x, covariates="mean", sojourn, ni, ivector, nc, covlabels, covmeans)
{
    nst <- x$qmodel$nstates
    diagse <- diaglse <- sojse <- sojlse <- numeric(nst)
    indmat <- matrix(ivector, nst, nst)
    indmat[indmat==1] <- seq(length = ni)
    indmat <- t(indmat) # matrix of indices of estimate vector
    inds <- seq(length = ni + ni*nc)
    cur.i <- 1
    if (covariates == 0 && nc > 0)
    {covariates <- list();  for (i in 1 : nc) covariates[[covlabels[i]]] <- 0}
    coefs <- if (!is.list(covariates) && (covariates=="mean")) 1 else c(1, unlist(covariates) - covmeans)
    for (i in 1:nst){
        ## Transformation for delta method is
        ## exp(x1 + x2 (cov1 - covmean1) + x3 (cov2 - covmean2) + ... ) +
        ##  exp(x4 + x5 (cov1 - covmean1) + x6 (cov2 - covmean2) + ... ) +   (or expit(...))
        nir <- sum(indmat[i,-i] > 0) # number of intens/misc for current state
        if (nir > 0) {
            qf <- expsum.formstr(nir, inds, cur.i, ni, nc, coefs)
            form <- as.formula(paste("~", paste(qf$formstr, collapse = " + ")))
            lform <- as.formula(paste("~ log (", paste(qf$formstr, collapse = " + "), ")"))
            ests <- x$estimates[qf$parinds2]
            cov <- x$covmat[qf$parinds2, qf$parinds2]
            diagse[i] <- deltamethod(form, ests, cov)
            diaglse[i] <- deltamethod(lform, ests, cov)
            if (sojourn){
                ## Mean sojourn times are -1 / diagonal entries of q matrix. Calculate their SEs and CIs.
                form <- as.formula(paste("~ 1 / (", paste(qf$formstr, collapse = " + "), ")"))
                lform <- as.formula(paste("~ log ( 1 / (", paste(qf$formstr, collapse = " + "), ")", ")"))
                sojse[i] <- deltamethod(form, ests, cov)
                sojlse[i] <- deltamethod(lform, ests, cov)
            }
            cur.i <- cur.i + nir
        }
        else diagse[i] <- 0
    }
    list(diagse=diagse, diaglse=diaglse, sojse=sojse, sojlse=sojlse)
}

### Work out SE and CIs of misclassification probabilities for given covariate values.
### Know SEs of beta_rs, use delta method to calculate.
###  SE of p_rs = exp(beta_rs x) / (1 + sum(exp(beta_rs x)))  (non-baseline p) or  1 / (1 + sum(exp(beta_rs x))) (baseline p).
### To calculate symmetric CI for resulting p_rs, assume logit(p_rs) normal, and use SE(logit(p_rs)) calculated by delta method.

p.se.msm <- function(qmodel, emodel, hmodel, qcmodel, ecmodel, paramdata, center, covariates="mean")
{
    nst <- qmodel$nstates
    inds <- (qmodel$npars + qcmodel$npars + 1) : (qmodel$npars + qcmodel$npars + sum(hmodel$npars) + hmodel$ncoveffs)
    ni <- emodel$npars
    nc <- if (!is.list(covariates) && ((covariates == "mean") && center) || ((covariates == 0) && !center)) 0 else ecmodel$ncovs
    coefs <- if (!is.list(covariates) && (covariates=="mean")) 1 else c(1, unlist(covariates) - ecmodel$covmeans)
    ppars <- hmodel$plabs %in% c("p","pbase")
    res <- data.frame(lab=hmodel$plabs[ppars])
    hmmallpars <- !(paramdata$plabs %in% c("qbase","qcov","initp","initp0","initpcov"))
    res$est <- msm.mninvlogit.transform(paramdata$params[paramdata$hmmpars], hmodel$plabs, hmodel$parstate)[ppars]
    res$parstate <- hmodel$parstate[ppars]
    res$se <- res$lse <- res$LCL <- res$UCL <- res$inds <- res$strs <- 0
    cur.i <- 1
    for (i in unique(res$parstate)) {
        nir <- sum(hmodel$parstate[hmodel$plabs=="p"] == i) # number of independent misc probs for current state
        p.inds <- which(hmodel$plabs=="p" & hmodel$parstate==i) # indices into HMM parameter vector of logit baseline p for that state
        cov.inds <- sum(hmodel$npars) + (cur.i-1)*nc + seq(length=(nc*nir)) # indices into HMM parameter vector of corresp cov effects
        parinds <- numeric(); formstr <- character(nir)
        for (j in 1:nir) {
            formstr[j] <- expsum(1:((nc+1)*nir), coefs) # string of form exp(1*x1+beta1*x2*beta2*x3), exp(x4+beta*x5+...)
            parinds <- c(parinds, p.inds[j], cov.inds[(j-1)*nc + seq(length=nc)]) # indices into HMM par vector corresp to x1,x2,x3,...
        }
        sumstr <- paste(formstr, collapse = " + ") # "parinds" are
        formstr <- paste("1 / (1 + ", sumstr, ")")
        form <- as.formula(paste("~ ",formstr))
        lform <- as.formula(paste("~ log( (", formstr, ") / (1 - ", formstr, "))"))
        ests <- paramdata$params[hmmallpars][parinds]
        cov <- paramdata$covmat[hmmallpars,hmmallpars][parinds, parinds]
        res$se[res$parstate==i & res$lab=="pbase"] <- deltamethod(form, ests, cov)
        res$lse[res$parstate==i & res$lab=="pbase"] <- deltamethod(lform, ests, cov)
        res$strs[res$parstate==i & res$lab=="pbase"] <- paste(as.character(form),collapse="")
        res$inds[res$parstate==i & res$lab=="pbase"] <- paste(parinds,collapse=",")
        for (j in 1:nir){
            istr <- expsum(((j-1)*(nc+1)+1):(j*(nc+1)), coefs)
            formstr <- paste(istr, "/ (1 + ", sumstr, ")")
            form <- as.formula(paste("~ ",formstr))
            lform <- as.formula(paste("~ log( (", formstr, ") / (1 - ", formstr, "))"))
            res$se[res$parstate==i & res$lab=="p"][j] <- deltamethod(form, ests, cov)
            res$lse[res$parstate==i & res$lab=="p"][j] <- deltamethod(lform, ests, cov)
            res$strs[res$parstate==i & res$lab=="p"][j] <- paste(as.character(form), collapse="")
            res$inds[res$parstate==i & res$lab=="p"][j] <- paste(parinds,collapse=",")
        }
        cur.i <- cur.i + nir
    }
    res$LCL <- plogis(qlogis(res$est) - qnorm(0.975)*res$lse)
    res$UCL <- plogis(qlogis(res$est) + qnorm(0.975)*res$lse)
    res
}

## Form a string,  exp ( x1 1 + x2 (cov1 - covmean1) + x3 (cov2 - covmean2) + ... )
## to be made into a formula for deltamethod.
## Also return indices of estimates and covariance matrix output from optim() to use
## to inform deltamethod

expsum.formstr <- function(nir, inds, cur.i, ni, nc, coefs)
{
    formstr <- character(nir)
    parinds <- numeric()
    for (j in (cur.i : (cur.i + nir - 1))) {
        indj <- seq(j, (nc * ni + j), ni)
        parinds <- c(parinds, inds[indj])  # first 1 5 7, then 2 5 7
    }
    ## e.g. parinds = 1 5 7 2 5 7 becomes xinds = 1 3 4 2 3 4
    parinds2 <- sort(unique(parinds))
    xinds <- rank(parinds2)[match(parinds, parinds2)]
    for (j in 1:nir)
        formstr[j] <- expsum(xinds[1:(nc+1) + (j-1)*(nc+1)], coefs)
    list(formstr=formstr, parinds=parinds, parinds2=parinds2)
}

## Form a string,  exp ( x1 1 + x2 (cov1 - covmean1) + x3 (cov2 - covmean2) + ... )
## to be made into a formula for deltamethod

expsum <- function(inds, coefs)
{
    xseq <- paste("x", inds, sep="")
    inprod <- paste(paste(coefs, xseq, sep="*"), collapse=" + ")
    paste("exp(", inprod, ")", sep="")
}

lsum <- function(inds, coefs)
{
    xseq <- paste("x", inds, sep="")
    paste(paste(coefs, xseq, sep="*"), collapse=" + ")
}


### Extract a ratio of transition intensities at given covariate values

qratio.msm <- function(x, ind1, ind2,
                       covariates = "mean",
                       ci=c("delta","normal","bootstrap","none"),
                       cl=0.95, B=1000)
{
    q <- qmatrix.msm(x, covariates)$estimates
    if (!is.numeric(ind1) || length(ind1) != 2 || !is.numeric(ind2) || length(ind2) != 2)
        stop("ind1 and ind2 must be numeric vectors of length 2")
    if (any (! (ind1 %in% 1 : x$qmodel$nstates))  |  any (! (ind2 %in% 1 : x$qmodel$nstates) ) )
        stop("ind1 and ind2 must be pairs of states in 1, ..., ", x$qmodel$nstates)
    if (q[ind2[1], ind2[2]] == 0)
        stop (paste("Denominator q[",ind2[1],",",ind2[2],"", "] is zero\n", sep=""))
    else if (q[ind1[1], ind1[2]] ==  0) {
        warning(paste ("Numerator q[",ind1[1],",",ind1[2],"", "] is zero\n", sep=""))
        estimate <- se <- 0
    }
    else {
        estimate <- q[ind1[1], ind1[2]]  /  q[ind2[1], ind2[2]]
        ci <- match.arg(ci)
        if (x$foundse && (ci != "none")) {
            if (ci == "delta") { 
                se <- qratio.se.msm(x, ind1, ind2, covariates, cl)$se
                lse <- qratio.se.msm(x, ind1, ind2, covariates, cl)$lse
                L <- exp ( log(abs(estimate)) - sign(estimate)*qnorm(1 - 0.5*(1 - cl)) * lse ) * sign(estimate)
                U <- exp ( log(abs(estimate)) + sign(estimate)*qnorm(1 - 0.5*(1 - cl)) * lse ) * sign(estimate)
            }
            else if (ci=="normal") {
                q.ci <- qratio.normci.msm(x, ind1, ind2, covariates, cl, B)
                L <- q.ci[1]; U <- q.ci[2]; se=q.ci[3]
            }
            else if (ci=="bootstrap") {
                q.ci <- qratio.ci.msm(x, ind1, ind2, covariates, cl, B)
                L <- q.ci[1]; U <- q.ci[2]; se=q.ci[3]
            }         
        }
        else {se <- L <- U <- NULL}
    }
    c(estimate=estimate, se=se, L=L, U=U)
}

### Work out standard error of a ratio of intensities using delta method
### Uuugh.  What a fuss for one little number.

qratio.se.msm <- function(x, ind1, ind2, covariates="mean", cl=0.95)
{
    nst <- x$qmodel$nstates
    ni <- x$qmodel$npars
    nc <- if (!is.list(covariates) && (covariates == "mean")) 0 else x$qcmodel$ncovs
    indmat <- t(x$qmodel$imatrix)
    indmat[indmat == 1] <- seq(length = x$qmodel$npars)
    indmat <- t(indmat) # matrix of indices of estimate vector
    inds <- seq(length = x$qmodel$npars+x$qcmodel$npars) # identifiers for q and beta parameters
    if (is.list(covariates)) {
        covariates <- factorcov2numeric.msm(covariates, x)
    }
    if (!is.list(covariates) && covariates == 0)
    {covariates <- list();  for (i in 1 : nc) covariates[[x$qcmodel$covlabels[i]]] <- 0}
    coefs <- if (!is.list(covariates) && (covariates=="mean")) 1 else c(1, unlist(covariates) - x$qcmodel$covmeans)
    parinds <- numeric()
    indmatrow.n <- indmat[ind1[1],-ind1[1]]
    nir.n <- sum(indmatrow.n > 0)
    indmatrow.d <- indmat[ind2[1],-ind2[1]]
    nir.d <- sum(indmatrow.d > 0)
    formstr.n <- character(nir.n)
    formstr.d <- character(nir.d)

    if (ind1[1]!=ind1[2] && ind2[1]!=ind2[2]) { # both intensities are off-diagonal
        parinds <- c(inds[indmat[ind1[1],ind1[2]] - 1 + seq(1, (nc * ni + 1), ni)],
                     inds[indmat[ind2[1],ind2[2]] - 1 + seq(1, (nc * ni + 1), ni)])
        parinds2 <- sort(unique(parinds))
        xinds <- rank(parinds2)[match(parinds, parinds2)]
        formstr.n <- expsum(xinds[1:(nc+1)], coefs)
        formstr.d <- expsum(xinds[1:(nc+1) + nc+1] , coefs)
    }

    else if (ind1[1]!=ind1[2] && ind2[1]==ind2[2]) { # numerator off-diagonal, denom diagonal
        parinds <- inds[indmat[ind1[1],ind1[2]] - 1 + seq(1, (nc * ni + 1), ni)]
        cur.i <- min(indmatrow.d[indmatrow.d>0])
        for (j in 1:nir.d)
            parinds <- c(parinds, inds[cur.i - 1 + seq(j, (nc * ni + j), ni)])
        parinds2 <- sort(unique(parinds))
        xinds <- rank(parinds2)[match(parinds, parinds2)]
        formstr.n <- expsum(xinds[1:(nc+1)], coefs)
        for (j in 1:nir.d)
            formstr.d[j] <- expsum(xinds[1:(nc+1) + j*(nc+1)], coefs)
    }

    else if (ind1[1]==ind1[2] && ind2[1]!=ind2[2]) { # numerator diagonal, denom off-diagonal
        cur.i <- min(indmatrow.n[indmatrow.n>0])
        for (j in 1:nir.n)
            parinds <- c(parinds, inds[cur.i - 1 + seq(j, (nc * ni + j), ni)])
        parinds <- c(parinds, inds[indmat[ind2[1],ind2[2]] - 1 + seq(1, (nc * ni + 1), ni)])
        parinds2 <- sort(unique(parinds))
        xinds <- rank(parinds2)[match(parinds, parinds2)]
        for (j in 1:nir.n)
            formstr.n[j] <- expsum(xinds[1:(nc+1) + (j-1)*(nc+1)], coefs)
        formstr.d <- expsum(xinds[nir.n*(nc+1) + 1:(nc+1)], coefs)
    }

    else if (ind1[1]==ind1[2] && ind2[1]==ind2[2]) { # both intensities diagonal
        cur.i <- min(indmatrow.n[indmatrow.n>0])
        for (j in 1:nir.n)
            parinds <- c(parinds, inds[cur.i - 1 + seq(j, (nc * ni + j), ni)])
        cur.i <- min(indmatrow.d[indmatrow.d>0])
        for (j in 1:nir.d)
            parinds <- c(parinds, inds[cur.i - 1 + seq(j, (nc * ni + j), ni)])
        parinds2 <- sort(unique(parinds))
        xinds <- rank(parinds2)[match(parinds, parinds2)]
        for (j in 1:nir.n)
            formstr.n[j] <- expsum(xinds[1:(nc+1) + (j-1)*(nc+1)], coefs)
        for (j in 1:nir.d)
            formstr.d[j] <- expsum(xinds[nir.n*(nc+1) + 1:(nc+1) + (j-1)*(nc+1)], coefs)
    }

    num <- paste(formstr.n, collapse = " + ")
    denom <- paste(formstr.d, collapse = " + ")
    form <- as.formula(paste("~", "(", num, ") / (", denom, ")"))
    lform <- as.formula(paste("~ ", "log (", num, ") - log (", denom, ")"))
    ests <- x$estimates[parinds2]
    cov <- x$covmat[parinds2,parinds2]
    se <- deltamethod(form, ests, cov)
    lse <- deltamethod(lform, ests, cov)
    list(se=se, lse=lse)
}


### Extract the transition probability matrix at given covariate values

pmatrix.msm <- function(x, # fitted msm model
                        t = 1, # time interval
                        t1 = 0, # start time for pci models
                        covariates = "mean",  # covariate values to calculate transition matrix for
                        ci=c("none","normal","bootstrap"), # calculate a confidence interval
                                        # using either simulation from asymptotic normal dist of MLEs, or bootstrap
                        cl = 0.95, # width of symmetric confidence interval
                        B = 1000 # number of bootstrap replicates or normal simulations
                        )
{
    if (!is.numeric(t) || (t < 0)) stop("t must be a positive number")
    if (is.null(x$pci)) {
        q <- qmatrix.msm(x, covariates)
        p <- MatrixExp(q$estimates, t)
        colnames(p) <- rownames(p) <- rownames(q$estimates)
        ci <- match.arg(ci)
        p.ci <- switch(ci,
                       bootstrap = pmatrix.ci.msm(x=x, t=t, t1=t1, covariates=covariates, cl=cl, B=B),
                       normal = pmatrix.normci.msm(x=x, t=t, t1=t1, covariates=covariates, cl=cl, B=B),
                       none = NULL)
        res <- if (ci=="none") p else list(estimates = p, L=p.ci[,,1], U=p.ci[,,2])
    }    
    else {
        piecewise.covariates <- msm.fill.pci.covs(x, covariates)
        res <- pmatrix.piecewise.msm(x, t1, t1 + t, x$pci, piecewise.covariates, ci, cl, B)
    } 
    class(res) <- "msm.est"
    res
}

### Extract the transition probability matrix at given covariate values - where the Q matrix is piecewise-constant

pmatrix.piecewise.msm <- function(x, # fitted msm model
                                  t1, # start time
                                  t2, # stop time
                                  times,  # vector of cut points
                                  covariates, # list of lists of covariates, for (, times1], (times1, times2], ...
                                        # of length one greater than times
                                  ci=c("none","normal","bootstrap"),
                                  cl = 0.95, # width of symmetric confidence interval
                                  B = 1000 # number of bootstrap replicates or normal simulations
                                  )
{
    x$pci <- NULL # to avoid infinite recursion when calling pmatrix.msm
    ## Input checks
    if (t2 < t1) stop("Stop time t2 should be greater than or equal to start time t1")
    if (!is.numeric(times) || is.unsorted(times)) stop("times should be a vector of numbers in increasing order")
    if (length(covariates) != length(times) + 1)
        stop("Number of covariate lists must be one greater than the number of cut points")
    ## Locate which intervals t1 and t2 fall in, as indices ind1, ind2 into "times".
    if (t1 <= times[1]) ind1 <- 1
    else if (length(times)==1) ind1 <- 2
    else {
        for (i in 2:length(times))
            if ((t1 > times[i-1]) && (t1 <= times[i]))
            {ind1 <- i; break}
        if (t1 > times[i]) ind1 <- i+1
    }
    if (t2 <= times[1]) ind2 <- 1
    else if (length(times)==1) ind2 <- 2
    else {
        for (i in 2:length(times))
            if ((t2 > times[i-1]) && (t2 <= times[i]))
            {ind2 <- i; break}
        if (t2 > times[i]) ind2 <- i+1
    }

    ## Calculate accumulated pmatrix
    ## Three cases: ind1, ind2 in the same interval
    if (ind1 == ind2) {
        P <- pmatrix.msm(x, t = t2 - t1, covariates=covariates[[ind1]])
    }
    ## ind1, ind2 in successive intervals
    else if (ind2 == ind1 + 1) {
        P.start <- pmatrix.msm(x, t = times[ind1] - t1 , covariates=covariates[[ind1]])
        P.end <- pmatrix.msm(x, t = t2 - times[ind2-1], covariates=covariates[[ind2]])
        P <- P.start %*% P.end
    }
    ## ind1, ind2 separated by one or more whole intervals
    else {
        P.start <- pmatrix.msm(x, t = times[ind1] - t1, covariates=covariates[[ind1]])
        P.end <- pmatrix.msm(x, t = t2 - times[ind2-1], covariates=covariates[[ind2]])
        P.middle <- diag(x$qmodel$nstates)
        for (i in (ind1+1):(ind2-1)) {
            P.middle <- P.middle %*% pmatrix.msm(x, t = times[i] - times[i-1], covariates=covariates[[i]])
        }
        P <- P.start %*% P.middle %*% P.end
    }

    ci <- match.arg(ci)
    P.ci <- switch(ci,
                   bootstrap = pmatrix.piecewise.ci.msm(x=x, t1=t1, t2=t2, times=times, covariates=covariates, cl=cl, B=B),
                   normal = pmatrix.piecewise.normci.msm(x=x, t1=t1, t2=t2, times=times, covariates=covariates, cl=cl, B=B),
                   none = NULL)
    res <- if (ci=="none") P else list(estimates = P, L=P.ci[,,1], U=P.ci[,,2])
    res
}

### Make a list of covariate lists to supply to pmatrix.piecewise.msm for models with "pci" time-dependent intensities. 
### One for each time period, with time constant covariates replicated. 
### For use in model assessment functions
### Returns factor covariates as contrasts, not factor levels. 

msm.fill.pci.covs <- function(x, covariates="mean"){
    nc <- x$qcmodel$ncovs
    ## indices of covariates representing time periods
    ti <- grep("timeperiod\\[([0-9]+|Inf),([0-9]+|Inf)\\)", x$qcmodel$covlabels) 
    ni <- setdiff(1:nc, ti) # indices of other covariates
    covlist <- vector(nc, mode="list")
    names(covlist) <- x$qcmodel$covlabels
    if (!is.list(covariates)){
        if (covariates == 0){
            for (i in ni) covlist[[i]] <- 0
        }
        else if (covariates == "mean"){
            for (i in ni) covlist[[i]] <- x$qcmodel$covmeans[i]
        }
    }
    else {
        ## supplied values of non-time covariates
        covariates <- factorcov2numeric.msm(covariates, x, intmisc="intens") # convert any factors to numeric contrasts
        for (i in names(covariates))
            if (length(grep("^timeperiod",i))==0) {
                if (i %in% union(x$qcmodel$covlabels.orig,x$qcmodel$covlabels))
                    covlist[[i]] <- covariates[[i]]
                else warning("Covariate ",i," unknown")
            }
    }
    for (i in ti) covlist[[i]] <- 0
    ## set contrasts for each successive time period to 1
    ncut <- length(x$pci)
    covlistlist <- vector(ncut+1, mode="list")
    names(covlistlist) <- x$data$covdata$covfactorlevels$timeperiod
    covlistlist[[1]] <- covlist
    for (i in seq(length=ncut)){
        covlistlist[[i+1]] <- covlist
        covlistlist[[i+1]][[ti[i]]] <- 1
    }
    covlistlist
} 


### Extract the mean sojourn times for given covariate values

sojourn.msm <- function(x, covariates = "mean", ci=c("delta","normal","bootstrap","none"), cl=0.95, B=1000)
{
    qmatrix <- qmatrix.msm(x, covariates, sojourn=TRUE, ci=ci, cl=cl, B=B)
    sojstates <- (1 : x$qmodel$nstates) [transient.msm(x)]
    soj <- qmatrix$sojourn[sojstates]
    names (soj) <- rownames(x$qmodel$qmatrix)[sojstates]
    if (x$foundse && (ci != "none")){
        sojse <- qmatrix$sojournSE[sojstates]
        sojl <- qmatrix$sojournL[sojstates]
        soju <- qmatrix$sojournU[sojstates]
        names(sojse) <- names(sojl) <- names(soju) <- names(soj)
        res <- data.frame(estimates=soj, SE=sojse, L=sojl, U=soju)
    }
    else res <- list(estimates=soj)
    res
}

### Extract the coefficients

coef.msm <- function(object, ...)
{
    if (!inherits(object, "msm")) stop("expected object to be a msm model")
    if (object$emodel$misc)
        object[c("Qmatrices", "Ematrices")]
    else object$Qmatrices
}

### Extract the log-likelihood

logLik.msm <- function(object, ...)
{
    if (!inherits(object, "msm")) stop("expected object to be a msm model")
    val <- - 0.5 * object$minus2loglik
    attr(val, "df") <- object$paramdata$nopt
    class(val) <- "logLik"
    val
}

### Likelihood ratio test between two or more models

lrtest.msm <- function(...){
    mods <- list(...)
    if (length(mods) < 2) stop("Expected 2 or more models as arguments")
    lx <- logLik(mods[[1]])
    res <- matrix(nrow=length(mods)-1, ncol=3)
    colnames(res) <- c("-2 log LR","df","p")
    rownames(res) <- sapply(as.list(match.call())[-(1:2)], deparse)
    for (i in 2:length(mods)) {
        if (!inherits(mods[[i]], "msm"))
            stop("Expected argument",i,"to be a msm object")
        ly <- logLik(mods[[i]])
        lr <- as.numeric(-2 * (lx - ly))
        df <- attr(ly,"df") - attr(lx,"df")    
        res[i-1,] <- c(lr, df, 1 - pchisq(lr, df))
    }
    res
}

## Estimate total length of stay in a given state.

totlos.msm <- function(x, start=1, end=NULL, fromt=0, tot=Inf, covariates="mean",
                       ci=c("none","normal","bootstrap"), # calculate a confidence interval
                       cl = 0.95, # width of symmetric confidence interval
                       B = 1000, # number of bootstrap replicates
                       ...)
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    if (! start %in% 1 : x$qmodel$nstates) stop("start should be a state in 1, ..., ", x$qmodel$nstates)
    if (is.null(end)) end <- 1 : x$qmodel$nstates
    if (! all(end %in% 1 : x$qmodel$nstates)) stop("end should be a set of states in 1, ..., ", x$qmodel$nstates)
    if (!is.numeric(fromt) || !is.numeric(tot) || length(fromt) != 1 || length(tot) != 1 || fromt < 0 || tot < 0)
        stop("fromt and tot must be single non-negative numbers")
    if (fromt > tot) stop("tot must be greater than fromt")
    if (length(absorbing.msm(x)) == 0)
        if (tot==Inf) stop("Must specify a finite end time for a model with no absorbing state")    
    tr <- seq(length=x$qmodel$nstates) # transient.msm(x)
    totlos <- numeric(length(end))
    if (tot==Inf) {
        totlos[end %in% absorbing.msm(x)] <- Inf # set by hand or else integrate() will fail
        rem <- seq(along=end)[!(end %in% absorbing.msm(x))]
    }
    else rem <- seq(along=end)
    for (j in rem){
        f <- function(time) {
            y <- numeric(length(time))
            for (i in seq(along=y))
                y[i] <- pmatrix.msm(x, time[i], covariates=covariates)[start,end[j]]
            y
        }
        totlos[j] <- integrate(f, fromt, tot, ...)$value
    }
    names(totlos) <- rownames(x$qmodel$qmatrix)[end]
    ci <- match.arg(ci)
    t.ci <- switch(ci,
                   bootstrap = totlos.ci.msm(x=x, start=start, fromt=fromt, tot=tot, covariates=covariates, cl=cl, B=B),
                   normal = totlos.normci.msm(x=x, start=start, fromt=fromt, tot=tot, covariates=covariates, cl=cl, B=B),
                   none = NULL)
    if (ci=="none") totlos else rbind(totlos, t.ci)
}

## Return indices of transient states (can either call for a fitted model or a qmatrix)

transient.msm <- function(x=NULL, qmatrix=NULL)
{
    if (!is.null(x)) {
        if (!inherits(x, "msm")) stop("expected x to be a msm model")
        qmatrix <- x$Qmatrices[[1]]
        nst <- x$qmodel$nstates
    }
    else if (!is.null(qmatrix)) {
        nst <- nrow(qmatrix)
    }
    else stop("Neither a fitted msm model nor a qmatrix have been supplied")
    which(diag(msm.fixdiag.qmatrix(qmatrix)) != 0)
}

## Return indices of absorbing states (can either call for a fitted model or a qmatrix)

absorbing.msm <- function(x=NULL, qmatrix=NULL)
{
    if (!is.null(x)) {
        if (!inherits(x, "msm")) stop("expected x to be a msm model")
        qmatrix <- x$Qmatrices[[1]]
        nst <- x$qmodel$nstates
    }
    else if (!is.null(qmatrix)) {
        nst <- nrow(qmatrix)
    }
    else stop("Neither a fitted msm model nor a qmatrix have been supplied")
    which(diag(msm.fixdiag.qmatrix(qmatrix)) == 0)
}

## Return two-column matrix containing pairs of states with allowed
## transitions in an interval.  Handles transitions between observed
## states in misclassification models

intervaltrans.msm <- function(x=NULL, qmatrix=NULL, ematrix=NULL, exclude.absabs=FALSE, censor=FALSE) {
    if (!is.null(x)) {
        if (!inherits(x, "msm")) stop("expected x to be a msm model")
        qmatrix <- qmatrix.msm(x, ci="none")
        if (is.null(ematrix) & x$emodel$misc)
            ematrix <- ematrix.msm(x, ci="none") > 0
        abs <- absorbing.msm(x)
    }
    else if (!is.null(qmatrix)) {
        abs <- absorbing.msm(qmatrix=qmatrix)
    }
    else if (is.null(qmatrix))
        stop("Neither a fitted msm model nor a qmatrix have been supplied")
    P <- MatrixExp(qmatrix) 
    if (!is.null(ematrix))
        P <- t(ematrix) %*% P %*% ematrix # > 0 iff P(obs state=s | prev obs state = r) > 0 
    ## P(obs state = s | obs prev = r)  =  Sum_ij  P(obsst = s | truest = j) P(truest = j | trueprev = i) P(trueprev = i | obsprev = r)
    ##  Sum_ij   Ejs Pij Eir    =  Eir Pij Ejs
    gt0 <- abs(P) > .Machine$double.eps ^ 0.5
    at <- cbind(row(P)[gt0], col(P)[gt0])
    if (exclude.absabs)
        at <- at[!(at[,1] %in% abs & at[,2] %in% abs),]
    if (censor && x$cmodel$ncens > 0) { # consider censoring as separate state
        atcens.all <- numeric()
        for (i in 1:x$cmodel$ncens) {
            truestates <- x$cmodel$states[x$cmodel$index[i] : (x$cmodel$index[i+1] - 1)]
            atcens <- at[at[,2] %in% truestates,]
            atcens[,2] <- 99
            atcens <- unique(atcens)
            atcens.all <- rbind(atcens.all, atcens)
        }
        at <- rbind(at, atcens.all)
    }
    at[order(at[,1],at[,2]),]
}

### Estimate observed state occupancies in the data at a series of times
### Assume previous observed state is retained until next observation time
### Assumes times are sorted within patient (they are in data in msm objects)

observed.msm <- function(x, times=NULL, interp=c("start","midpoint"))
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    ## For general HMMs use the Viterbi estimate of the observed state.
    state <- if ((x$hmodel$hidden && !x$emodel$misc) || (!x$hmodel$hidden && x$cmodel$ncens>0) )
        viterbi.msm(x)$fitted else x$data$state
    subject <- x$data$subject ## fixme subj char/factor?
    time <- x$data$time
    if (is.null(times))
        times <- seq(min(time), max(time), (max(time) - min(time))/10)
    states.expand <- matrix(nrow=length(unique(subject)), ncol=length(times))
    pts <- unique(subject)
    absorb <- absorbing.msm(x)
    interp <- match.arg(interp)
    for (i in seq(along=pts)){
        state.i <- state[subject==pts[i]]
        time.i <- time[subject==pts[i]]
        j <- 1
        while(j <= length(times)) {
            if (times[j] < time.i[1]) {
                mtime <- max(which(times-time.i[1] < 0))
                states.expand[i, j:mtime] <- NA
                j <- mtime + 1
                next;
            }
            else if (times[j] > time.i[length(time.i)]) {
                if (state.i[length(time.i)] %in% absorb) {
                    states.expand[i, j:(length(times))] <-  state.i[length(time.i)]
                }
                else states.expand[i, j:(length(times))] <-  NA
                break;
            }
            else {
                prevtime <- max(which(time.i <= times[j]))
                if (interp=="midpoint") {
                    nexttime <- min(which(time.i >= times[j]))
                    midpoint <- (prevtime + nexttime) / 2
                    states.expand[i,j] <- state.i[if (times[j] <= midpoint) prevtime else nexttime]
                }
                else
                    states.expand[i,j] <- state.i[prevtime]

            }
            j <- j+1
        }
    }
    obstab <- t(apply(states.expand, 2, function(y) table(factor(y, levels=seq(length=x$qmodel$nstates)))))
    obsperc <- 100*obstab / rep(rowSums(obstab), ncol(obstab))
    dimnames(obstab) <- dimnames(obsperc) <- list(times, paste("State", 1:x$qmodel$nstates))
    obstab <- cbind(obstab, Total=rowSums(obstab))
    list(obstab=obstab, obsperc=obsperc, risk=obstab[,ncol(obstab)])
}

expected.msm <- function(x,
                         times=NULL,
                         timezero=NULL,
                         initstates=NULL,
                         covariates="mean",
                         misccovariates="mean",
                         piecewise.times=NULL,
                         piecewise.covariates=NULL,
                         risk=NULL,
                         ci=c("none","normal","bootstrap"),
                         cl = 0.95,
                         B = 1000
                         )
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    time <- x$data$time
    if (is.null(times))
        times <- seq(min(time), max(time), (max(time) - min(time))/10)
    if (is.null(timezero))  timezero <- min(time)
    if (is.null(risk)) risk <- observed.msm(x, times=times)$risk
    exptab <- matrix(nrow=length(times), ncol=x$qmodel$nstates)
    if (x$emodel$misc){
                                        #        exptab <- x$emodel$initprobs * risk[1]
        start <- min(which(times - timezero > 0))
        if (length(times) >= start) {
            for (j in start:length(times)) {
                pmat <-
                    if (is.null(piecewise.times))
                        pmatrix.msm(x, t=times[j] - timezero, t1=timezero, covariates=covariates)
                    else
                        pmatrix.piecewise.msm(x, timezero, times[j], piecewise.times, piecewise.covariates)
                emat <- ematrix.msm(x, covariates=misccovariates)$estimates
                exptruej <- risk[j] * x$emodel$initprobs %*% pmat
                expobsj <- exptruej %*% emat
                exptab[j,] <- expobsj
            }
        }
    }
    else {
        if (is.null(initstates)) initstates <- observed.msm(x, times=timezero)$obstab[1:x$qmodel$nstates]
        initprobs <- initstates / sum(initstates)
                                        #        exptab <- matrix(initstates, nrow=1)
        start <- min(which(times - timezero >= 0))
        if (length(times) >= start) {
            for (j in start:length(times)) {
                pmat <-
                    if (is.null(piecewise.times))
                        pmatrix.msm(x, t=times[j] - timezero, t1=timezero, covariates=covariates)
                    else
                        pmatrix.piecewise.msm(x, timezero, times[j], piecewise.times, piecewise.covariates)
                expj <- risk[j] * initprobs %*% pmat
                exptab[j,] <- expj
            }
        }
    }
    exptab <- cbind(exptab, apply(exptab, 1, sum))
    dimnames(exptab) <- list(times, c(rownames(x$qmodel$qmatrix),"Total"))
    expperc <- 100*exptab[,1:x$qmodel$nstates] / exptab[, x$qmodel$nstates+1]

    ci <- match.arg(ci)    
    e.ci <- switch(ci,
                   bootstrap = expected.ci.msm(x, times, timezero, initstates, covariates, misccovariates,
                   piecewise.times, piecewise.covariates, risk, cl, B),
                   normal = expected.normci.msm(x, times, timezero, initstates, covariates, misccovariates,
                   piecewise.times, piecewise.covariates, risk, cl, B),
                   none = NULL)    
    res <-
        if (ci=="none") list(exptab=exptab, expperc=expperc)
        else list(exptab=list(estimates=exptab, ci=e.ci[[1]]),
                  expperc=list(estimates=expperc, ci=e.ci[[2]]))
    names(res) <- c("Expected","Expected percentages")
    res
}

### Table of observed and expected prevalences (works for misclassification and non-misclassification models)

prevalence.msm <- function(x,
                           times=NULL,
                           timezero=NULL,
                           initstates=NULL,
                           covariates="mean",
                           misccovariates="mean",
                           piecewise.times=NULL,
                           piecewise.covariates=NULL,
                           ci=c("none","normal","bootstrap"),
                           cl = 0.95,
                           B = 1000,
                           interp=c("start","midpoint"),
                           plot = FALSE, ...
                           )
{
    ## Estimate observed state occupancies in the data at a series of times
    time <- x$data$time
    if (is.null(times))
        times <- seq(min(time), max(time), (max(time) - min(time))/10)
    obs <- observed.msm(x, times, interp)
    risk <- obs$obstab[,ncol(obs$obstab)]
    ## Work out expected state occupancies by forecasting from transition probabilities
    expec <- expected.msm(x, times, timezero, initstates, covariates, misccovariates,
                          piecewise.times, piecewise.covariates, risk, ci, cl, B)
    res <- list(observed=obs$obstab, expected=expec[[1]], obsperc=obs$obsperc, expperc=expec[[2]])
    names(res) <- c("Observed", "Expected", "Observed percentages", "Expected percentages")
    if (plot) plot.prevalence.msm(x, mintime=min(times), maxtime=max(times), timezero=timezero, initstates=initstates,
                                  interp=interp, covariates=covariates, misccovariates=misccovariates,
                                  piecewise.times=piecewise.times, piecewise.covariates=piecewise.covariates, ...)
    res
}

plot.prevalence.msm <- function(x, mintime=NULL, maxtime=NULL, timezero=NULL, initstates=NULL,
                                interp=c("start","midpoint"), covariates="mean", misccovariates="mean",
                                piecewise.times=NULL, piecewise.covariates=NULL, xlab="Times",ylab="Prevalence (%)",
                                lwd=1, legend.pos=NULL,...){
    time <- x$data$time
    if (is.null(mintime)) mintime <- min(time)
    if (is.null(maxtime)) maxtime <- max(time)
    t <- seq(mintime, maxtime, length=100)
    obs <- observed.msm(x, t, interp)
    expec <- expected.msm(x, t, timezero=timezero, initstates=initstates, covariates=covariates, misccovariates=misccovariates,
                          piecewise.times=piecewise.times, piecewise.covariates=piecewise.covariates, risk=obs$risk)[[2]]
    states <- seq(length=x$qmodel$nstates)
    S <- length(states)
    ncols <- ceiling(sqrt(S))
    nrows <- if (floor(sqrt(S))^2 < S && S <= floor(sqrt(S))*ceiling(sqrt(S))) floor(sqrt(S)) else ceiling(sqrt(S))
    par(mfrow=c(nrows, ncols))
    for (i in states) {
        plot(t, obs$obsperc[,i], type="l", lty=1, ylim=c(0, 100), xlab=xlab, ylab=ylab, lwd=lwd, 
             main=rownames(x$qmodel$qmatrix)[i],...)
        lines(t, expec[,i], lty=2, lwd=lwd)
    }
    if (!is.numeric(legend.pos) || length(legend.pos) != 2)
        legend.pos <- c(0.4*maxtime, 40)
    legend(x=legend.pos[1], y=legend.pos[2], legend=c("Observed","Expected"), lty=1:2, lwd=lwd)
    invisible()
}

### Empirical versus fitted survival curve 

plot.survfit.msm <- function(x, from=1, to=NULL, range=NULL, covariates="mean", interp=c("start","midpoint"), ci=c("none","normal","bootstrap"), B=100,
                             legend.pos=NULL, xlab="Time", ylab="Survival probability", lwd=1, ...) {
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    if (is.null(to))
        to <- max(absorbing.msm(x))
    else {
        if (!is.numeric(to)) stop("to must be numeric")
        if (! (to %in% absorbing.msm(x) ) ) stop("to must be an absorbing state")
    }
    if (is.null(range))
        rg <- range(x$data$time)
    else {
        if (!is.numeric(range) || length(range)!= 2) stop("range must be a numeric vector of two elements")
        rg <- range
    }
    interp <- match.arg(interp)
    ci <- match.arg(ci)
    timediff <- (rg[2] - rg[1]) / 50
    times <- seq(rg[1], rg[2], timediff)
    pr <- lower <- upper <- numeric()

    for (t in times) {
        P <- pmatrix.msm(x, t, t1=times[1], covariates=covariates, ci=ci, B=B)
        if (ci != "none") { 
            pr <- c(pr, P$estimates[from, to])
            lower <- c(lower, P$L[from, to])
            upper <- c(upper, P$U[from, to])
        }
        else pr <- c(pr, P[from, to])
    }
    plot(times, 1 - pr, type="l", xlab=xlab, ylab=ylab, lwd=lwd,
         ylim=c(0,1), lty = 1, col="red",...)
    if (ci != "none") {
        lines(times, 1 - lower, lty=3, col="red", lwd=lwd)
        lines(times, 1 - upper, lty=3, col="red", lwd=lwd)
    }
    dat <- as.data.frame(x$data[c("subject", "time", "state")])
    st <- as.data.frame(
                        do.call("rbind", by(dat, dat$subject, function(x)
                                        {
                                            dind <- which(x[,"state"] == to)
                                            if(any(x[,"state"]==to))
                                                mintime <- if(interp=="start") min(x[dind, "time"]) else 0.5 * (x[dind, "time"] + x[dind-1, "time"])
                                            else mintime <- max(x[,"time"])
                                            c(anystate = as.numeric(any(x[,"state"]==to)), mintime = mintime)
                                        }
                                            ))) # slow 
    lines(survfit(Surv(st$mintime,st$anystate) ~ 1),col="blue",lty=2, lwd=lwd,...)
    timediff <- (rg[2] - rg[1]) / 50
    if (!is.numeric(legend.pos) || length(legend.pos) != 2)
        legend.pos <- c(max(x$data$time) - 25*timediff, 1)
    if (ci=="none")
        legend(legend.pos[1], legend.pos[2], lty=c(1,2), lwd=lwd, col=c("red","blue"),
               legend=c("Fitted","Empirical"))
    else legend(legend.pos[1], legend.pos[2], lty=c(1,3,2), lwd=lwd, col=c("red","red","blue"),
                legend=c("Fitted","Fitted (confidence interval)", "Empirical"))

    invisible()
}

### Obtain hazard ratios from estimated effects of covariates on log-transition rates

hazard.msm <- function(x, hazard.scale = 1, cl = 0.95)
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    if (length(hazard.scale) == 1) hazard.scale <- rep(hazard.scale, x$qcmodel$ncovs)
    if (length(hazard.scale) != x$qcmodel$ncovs)
        stop ("hazard.scale of length ", length(hazard.scale), ", expected ", x$qcmodel$ncovs)
    keep <- (x$qmodel$imatrix != 0)
    nst <- x$qmodel$nstates
    keepvec <- as.vector(t(keep))
    fromlabs <- rep(rownames(keep), each=nst) [keepvec]
    tolabs <- rep(colnames(keep), nst) [keepvec]
    if (x$qcmodel$ncovs > 0) {
        haz.list <- list()
        if (x$foundse) {
            for (i in 1:x$qcmodel$ncovs) {
                cov <- x$qcmodel$covlabels[i]
                haz.rat <- t(exp(hazard.scale[i]*x$Qmatrices[[cov]]))[keepvec]
                LCL <- t(exp(hazard.scale[i]*(x$Qmatrices[[cov]] - qnorm(1 - 0.5*(1 - cl))*x$QmatricesSE[[cov]]) ))[keepvec]
                UCL <- t(exp(hazard.scale[i]*(x$Qmatrices[[cov]] + qnorm(1 - 0.5*(1 - cl))*x$QmatricesSE[[cov]]) ))[keepvec]
                haz.tab <- cbind(haz.rat, LCL, UCL)
                dimnames(haz.tab) <- list(paste(fromlabs, "-", tolabs),
                                          c("HR", "L", "U"))
                haz.list[[cov]] <- haz.tab
            }
        }
        else {
            for (i in 1:x$qcmodel$ncovs) {
                cov <- x$qcmodel$covlabels[i]
                haz.tab <- as.matrix(t(exp(hazard.scale[i]*x$Qmatrices[[cov]]))[keepvec])
                dimnames(haz.tab) <- list(paste(fromlabs, "-", tolabs), "HR")
                haz.list[[cov]] <- haz.tab
            }
        }
    }
    else haz.list <- "No covariates on transition intensities"
    haz.list
}


### Obtain odds ratios from estimated effects of covariates on logit-misclassification probabilities
### TODO - equivalent for general HMMs which presents cov effects on natural scale.

odds.msm <- function(x, odds.scale = 1, cl = 0.95)
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    if (!x$emodel$misc) stop("Requires a misclassification model specified with ematrix")
    if (length(odds.scale) == 1) odds.scale <- rep(odds.scale, x$ecmodel$ncovs)
    if (length(odds.scale) != x$ecmodel$ncovs)
        stop ("odds.scale of length ", length(odds.scale), ", expected ", x$ecmodel$ncovs)
    keep <- (x$emodel$imatrix != 0)
    nst <- x$qmodel$nstates
    keepvec <- as.vector(t(keep))
    truelabs <- rep(rownames(keep), each=nst) [keepvec]
    obslabs <- rep(colnames(keep), nst) [keepvec]
    if (x$ecmodel$ncovs > 0) {
        odds.list <- list()
        if (x$foundse) {
            for (i in 1:x$ecmodel$ncovs) {
                cov <- x$ecmodel$covlabels[i]
                odds.rat <- t(exp(odds.scale[i]*x$Ematrices[[cov]]))[keepvec]
                LCL <- t(exp(odds.scale[i]*(x$Ematrices[[cov]] - qnorm(1 - 0.5*(1 - cl))*x$EmatricesSE[[cov]]) ))[keepvec]
                UCL <- t(exp(odds.scale[i]*(x$Ematrices[[cov]] + qnorm(1 - 0.5*(1 - cl))*x$EmatricesSE[[cov]]) ))[keepvec]
                odds.tab <- cbind(odds.rat, LCL, UCL)
                dimnames(odds.tab) <- list(paste("Obs", obslabs, "|", truelabs),
                                           c("OR", "L", "U"))
                odds.list[[cov]] <- odds.tab
            }
        }
        else {
            for (i in 1:x$ecmodel$ncovs) {
                cov <- x$ecmodel$covlabels[i]
                odds.tab <- as.matrix(t(exp(odds.scale[i]*x$Ematrices[[cov]]))[keepvec])
                dimnames(odds.tab) <- list(paste("Obs", obslabs, "|", truelabs), "OR")
                odds.list[[cov]] <- odds.tab
            }
        }
    }
    else odds.list <- "No covariates on misclassification probabilities"
    odds.list
}



### Viterbi algorithm for reconstructing the most likely path through underlying states
### This is all done in C



viterbi.msm <- function(x)
{
    if (!inherits(x, "msm")) stop("expected x to be a msm model")
    if (x$cmodel$ncens > 0 && !x$hmodel$hidden) {
        ## If censoring but not HMM, then define an identity HMM with
        ## true state known at every time except censoring times      
        hmod <- vector(x$qmodel$nstates, mode="list")
        for (i in 1:x$qmodel$nstates)
            hmod[[i]] <- hmmIdent(i)
        x$hmodel <- msm.form.hmodel(hmod, est.initprobs=FALSE, qmodel=x$qmodel)
        x$hmodel <- c(x$hmodel, list(ncovs=rep(rep(0,x$hmodel$nstates),x$hmodel$npars), ncoveffs=0, nicovs=rep(0,x$hmodel$nstates-1), nicoveffs=0))
        x$data$obstrue <- ifelse(x$data$state %in% x$cmodel$censor, 0, 1)
    }
    if (x$hmodel$hidden)
    {
        do.what <- 2

        x$data$fromstate <- x$data$fromstate - 1
        x$data$tostate <- x$data$tostate - 1
        x$data$firstobs <- x$data$firstobs - 1
        x$hmodel$models <- x$hmodel$models - 1
        x$hmodel$links <- x$hmodel$links - 1
        if (any(x$hmodel$plabs == "p")) {
            ## Express other probabilities relative to this baseline prob
            pst <- match(x$hmodel$parstate[x$hmodel$plabs=="p"], unique(x$hmodel$parstate[x$hmodel$plabs=="p"]))
            x$hmodel$pars[x$hmodel$plabs == "p"] <-
                x$hmodel$pars[x$hmodel$plabs == "p"] / x$hmodel$pars[x$hmodel$plabs == "pbase"][pst]
        }
        x$hmodel$initprobs <- x$hmodel$initprobs / x$hmodel$initprobs[1]

        vit <- .C("msmCEntry",
                  as.integer(do.what),

                  as.integer(as.vector(t(x$qmodel$imatrix))),
                  as.double(as.vector(t(x$Qmatrices$baseline)[t(x$qmodel$imatrix)==1])),
                  as.double(unlist(lapply(x$Qmatrices[x$qcmodel$covlabels], function(y) t(y)[t(x$qmodel$imatrix)==1]))),
                  as.double(x$hmodel$pars),
                  as.double(x$hmodel$coveffect),   # estimates

                  ## data for non-HMM
                  as.integer(x$data$fromstate),
                  as.integer(x$data$tostate),
                  as.double(x$data$timelag),
                  as.double(unlist(x$data$covmat)),
                  as.double(unlist(x$data$cov)),
                  as.integer(x$data$covdata$whichcov), # this is really part of the model
                  as.integer(x$data$nocc),
                  as.integer(x$data$whicha),
                  as.integer(x$data$obstype),

                  ## data for HMM / censored
                  as.integer(match(x$data$subject, unique(x$data$subject))),
                  as.double(x$data$time),
                  as.double(x$data$state),
                  as.integer(x$data$firstobs),
                  as.integer(x$data$obstrue),

                  ## HMM specification
                  as.integer(x$hmodel$hidden),
                  as.integer(x$hmodel$models),
                  as.integer(x$hmodel$npars),
                  as.integer(x$hmodel$totpars),
                  as.integer(x$hmodel$firstpar),
                  as.integer(x$hmodel$ncovs),
                  as.integer(x$hmodel$whichcovh),
                  as.integer(x$hmodel$links),
                  as.double(x$hmodel$initprobs),
                  as.integer(x$hmodel$nicovs),
                  as.double(x$hmodel$icoveffect),
                  as.integer(x$hmodel$whichcovi),

                  ## various dimensions
                  as.integer(x$qmodel$nstates),
                  as.integer(x$qmodel$analyticp),
                  as.integer(x$qmodel$iso),
                  as.integer(x$qmodel$perm),
                  as.integer(x$qmodel$qperm),
                  as.integer(x$qmodel$npars),
                  as.integer(x$qmodel$ndpars),
                  as.integer(x$qcmodel$ndpars),
                  as.integer(x$data$nobs),
                  as.integer(x$data$n),
                  as.integer(x$data$npts),  # HMM only
                  as.integer(rep(x$qcmodel$ncovs, x$qmodel$npars)),

                  as.integer(x$cmodel$ncens),
                  as.integer(x$cmodel$censor),
                  as.integer(x$cmodel$states),
                  as.integer(x$cmodel$index - 1),

                  as.integer(x$qmodel$constraint),
                  as.integer(x$qcmodel$constraint),
                  as.integer(x$qcmodel$whichdcov),

                  fitted = double (x$data$nobs),
                  PACKAGE = "msm",
                  NAOK = TRUE
                  )

        fitted <- vit$fitted + 1
    }
    else fitted <- x$data$state
    data.frame(subject = x$data$subject,
               time = x$data$time,
               observed = x$data$state,
               fitted = fitted)
}

scoreresid.msm <- function(x, plot=FALSE){
    if (x$hmodel$hidden | (x$cmodel$ncens > 0))
        stop("Score residuals not implemented for hidden Markov models or models with censored states")
    derivs <- likderiv.msm(x$paramdata$opt$par, deriv=3, x$data, x$qmodel, x$qcmodel, x$cmodel, x$hmodel, x$paramdata)
    cov <- solve(0.5*x$opt$hessian)
    sres <- colSums(t(derivs) * cov %*% t(derivs))
    names(sres) <- unique(x$data$subject)
    if (plot) {
        plot(sres, type="n")
        text(seq(along=sres), sres, names(sres))
    }
    sres
}
