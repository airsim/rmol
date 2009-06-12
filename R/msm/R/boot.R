### Take a bootstrap sample from the data contained in a fitted msm
### model. Sample pairs of consecutive observations, i.e. independent
### transitions.  Not applicable if model is hidden or some states are
### censored.

bootdata.trans.msm <- function(x) {
    dat <- if (!is.null(x$data.orig)) x$data.orig else x$data
    subj.num <- match(dat$subject, unique(dat$subject))
    nextsubj <- c(subj.num[2:length(subj.num)], Inf)
    lastsubj <- subj.num != nextsubj
    inds <- sample(which(!lastsubj), replace=TRUE)
    data.boot <- as.data.frame(matrix(nrow=length(inds)*2, ncol=length(dat$covlabels.orig) + 4))
    state.name <- deparse(as.list(x$call$formula)[[2]])
    time.name <- deparse(as.list(x$call$formula)[[3]])
    colnames(data.boot) <- c("subject.name", time.name, state.name, "obstype.name", dat$covlabels.orig)
    data.boot[,state.name] <- as.vector(rbind(dat$state[inds], dat$state[inds+1]))
                                        # in the bootstrap data, label each transition as being from a different subject
    data.boot[,"subject.name"] <- rep(seq(along=inds), each=2)
    data.boot[,time.name] <- as.vector(rbind(dat$time[inds], dat$time[inds+1]))
    data.boot[,"obstype.name"] <- as.vector(rbind(dat$obstype.obs[inds], dat$obstype.obs[inds+1]))
    for (j in dat$covlabels.orig) {
        frominds <- seq(1, 2*length(inds)-1, 2)
        data.boot[frominds, j] <- data.boot[frominds+1,j] <- dat$cov.orig[inds, j]
        if (dat$covdata$covfactor[j])
            data.boot[,j] <- factor(data.boot[,j], labels=levels(dat$cov.orig[,j]))
    }
    colnames(data.boot) <- gsub("factor\\((.+)\\)", "\\1", colnames(data.boot))
    data.boot
}

### Take a bootstrap sample from the data contained in a fitted msm
### model. Sample subjects. Used for hidden models or models with
### censoring, in which the transitions within a subject are not
### independent.

bootdata.subject.msm <- function(x) {
    dat <- if (!is.null(x$data.orig)) x$data.orig else x$data
    subj.num <- match(dat$subject, unique(dat$subject))
    subjs <- sample(unique(subj.num), replace=TRUE)
    inds <- new.subj <- NULL
    for (i in seq(along=subjs)) {
        subj.inds <- which(subj.num == subjs[i])
        inds <- c(inds, subj.inds)
        new.subj <- c(new.subj, rep(i, length(subj.inds)))
    }
    data.boot <- as.data.frame(matrix(nrow=length(inds), ncol=length(dat$covlabels.orig) + 5))
    state.name <- deparse(as.list(x$call$formula)[[2]])
    time.name <- deparse(as.list(x$call$formula)[[3]])
    colnames(data.boot) <- c("subject.name", time.name, state.name, "obstype.name", "obstrue.name", dat$covlabels.orig)
    data.boot[,"subject.name"] <- new.subj
    data.boot[,time.name] <- dat$time[inds]
    data.boot[,state.name] <- dat$state[inds]
    data.boot[,"obstype.name"] <- dat$obstype[inds]
    data.boot[,"obstrue.name"] <- dat$obstrue[inds]
    for (j in dat$covlabels.orig) {
        data.boot[, j] <- dat$cov.orig[inds, j]
        if (dat$covdata$covfactor[j]){
          data.boot[,j] <- factor(data.boot[,j], labels=levels(dat$cov.orig[,j]))
        }
    }
    colnames(data.boot) <- gsub("factor\\((.+)\\)", "\\1", colnames(data.boot))
    data.boot
}

### Given a fitted msm model, draw a bootstrap dataset, refit the
### model, and optionally compute a statistic on the refitted model.
### Repeat B times, store the results in a list.
### msm objects tend to be large, so it is advised to compute a statistic on them by specifying "stat", instead
### of using this function to return a list of refitted msm objects.
### To compute more than one statistic, specify, e.g. stat=function(x)list(stat1(x),stat2(x))

### Some of the arguments to the msm call might be user-defined objects.
### e.g. qmatrix, ematrix, hmodel, ...
### Put in help file that these must be in the working environment.

### a) if call supplied as factor(), strip factor() from name. 

boot.msm <- function(x, stat=pmatrix.msm, B=1000, file=NULL){
    boot.list <- vector(B, mode="list")
    if (!is.null(x$call$subject)) x$call$subject <- substitute(subject.name)
    if (!is.null(x$call$obstype)) x$call$obstype <- substitute(obstype.name)
    if (!is.null(x$call$obstrue)) x$call$obstrue <- substitute(obstrue.name)
    for (i in 1:B) {
        boot.data <- if (x$hmodel$hidden || x$cmodel$ncens) bootdata.subject.msm(x) else bootdata.trans.msm(x)
        x$call$data <- substitute(boot.data)
        boot.list[[i]] <- try(eval(x$call))
        if (!is.null(stat))
            boot.list[[i]] <- stat(boot.list[[i]])
        if (!is.null(file)) save(boot.list, file=file)
    }
    boot.list
}

### Utilities for calculating bootstrap CIs for particular statistics

qematrix.ci.msm <- function(x, covariates="mean", intmisc="intens", sojourn=FALSE, cl=0.95, B=1000) {
    q.list <- boot.msm(x, function(x)qematrix.msm(x=x, covariates=covariates, intmisc=intmisc)$estimates, B)
    q.array <- array(unlist(q.list), dim=c(dim(q.list[[1]]), length(q.list)))
    q.ci <- apply(q.array, c(1,2), function(x)(c(quantile(x, c(0.5 - cl/2, 0.5 + cl/2)), sd(x))))
    q.ci <- aperm(q.ci, c(2,3,1))
    if (sojourn) {
        soj.array <- apply(q.array, 3, function(x) -1/diag(x))
        soj.ci <- apply(soj.array, 1, function(x)(c(quantile(x, c(0.5 - cl/2, 0.5 + cl/2)), sd(x))))
        list(q=q.ci, soj=soj.ci)
    }
    else q.ci
}

qratio.ci.msm <- function(x, ind1, ind2, covariates="mean", cl=0.95, B=1000) {
    q.list <- boot.msm(x, function(x)qratio.msm(x=x, ind1=ind1, ind2=ind2, covariates=covariates)["estimate"], B)
    q.vec <- unlist(q.list)
    c(quantile(q.vec, c(0.5 - cl/2, 0.5 + cl/2)), sd(q.vec))
}

pmatrix.ci.msm <- function(x, t, t1, covariates="mean", cl=0.95, B=1000) {
    p.list <- boot.msm(x, function(x)pmatrix.msm(x=x, t=t, t1=t1, covariates=covariates,ci="none"), B)
    p.array <- array(unlist(p.list), dim=c(dim(p.list[[1]]), length(p.list)))
    p.ci <- apply(p.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    aperm(p.ci, c(2,3,1))
}

pmatrix.piecewise.ci.msm <- function(x, t1, t2, times, covariates="mean", cl=0.95, B=1000) {
    p.list <- boot.msm(x, function(x)pmatrix.piecewise.msm(x=x, t1=t1, t2=t2, times=times, covariates=covariates,ci="none"), B)
    p.array <- array(unlist(p.list), dim=c(dim(p.list[[1]]), length(p.list)))
    p.ci <- apply(p.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    aperm(p.ci, c(2,3,1))
}

totlos.ci.msm <- function(x, start=1, fromt=0, tot=Inf, covariates="mean", cl=0.95, B=1000, ...) {
    t.list <- boot.msm(x, function(x)totlos.msm(x, start, fromt, tot, covariates), B)
    t.array <- do.call("rbind", t.list)
    apply(t.array, 2, function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
}

expected.ci.msm <- function(x,
                            times=NULL,
                            timezero=NULL,
                            initstates=NULL,
                            covariates="mean",
                            misccovariates="mean",
                            piecewise.times=NULL,
                            piecewise.covariates=NULL,
                            risk=NULL,
                            cl=0.95, B=1000) {
    if(is.null(risk)) risk <- observed.msm(x)$risk
    e.list <- boot.msm(x, function(x){
        expected.msm(x, times, timezero, initstates, covariates, misccovariates, piecewise.times, piecewise.covariates, risk)
    }, B)
    e.tab.array <- array(unlist(lapply(e.list, function(x)x[[1]])), dim=c(dim(e.list[[1]][[1]]), length(e.list)))
    e.perc.array <- array(unlist(lapply(e.list, function(x)x[[2]])), dim=c(dim(e.list[[1]][[2]]), length(e.list)))
    e.tab.ci <- apply(e.tab.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    e.perc.ci <- apply(e.perc.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    res <- list(aperm(e.tab.ci, c(2,3,1)),  aperm(e.perc.ci, c(2,3,1)))
    names(res) <- c("Expected", "Expected percentages")
    res
}

### Compute a CI for a statistic using a sample from the assumed MVN
### distribution of MLEs of log Q, logit E and covariate effects on these
### Not user visible: only support a limited set of statistics based on Q matrix and E matrix.

normboot.msm <- function(x, stat, B=100) {
    ## simulate from vector of unreplicated parameters, to avoid numerical problems with rmvnorm when lots of correlations are 1 
    if (!x$foundse) stop("Asymptotic standard errors not available in fitted model")
    sim <- rmvnorm(B, x$opt$par, solve(0.5 * x$opt$hessian))
    params <- matrix(nrow=B, ncol=x$paramdata$npars)  # replicate constrained parameters.
    params[,x$paramdata$optpars] <- sim 
    params[,x$paramdata$hmmpars] <- msm.mninvlogit.transform(x$paramdata$params[x$paramdata$hmmpars], x$hmodel$plabs, x$hmodel$parstate)
    params <- params[, !duplicated(abs(x$paramdata$constr))][, abs(x$paramdata$constr)]*rep(sign(x$paramdata$constr), each=B)

    sim.stat <- vector(B, mode="list")
    for (i in 1:B) {
        x.rep <- x
        x.rep$paramdata$params <- params[i,]
        output <- msm.form.output("intens", x.rep$qmodel, x.rep$qcmodel, x.rep$paramdata)
        x.rep$Qmatrices <- output$Matrices
        if (x$emodel$misc) {
            output <- msm.form.output("misc", x.rep$emodel, x.rep$ecmodel, x.rep$paramdata)
            x.rep$Ematrices <- output$Matrices
            names(x.rep$Ematrices)[1] <- "logitbaseline"
        }
        sim.stat[[i]] <- stat(x.rep)
    }
    sim.stat
}

qematrix.normci.msm <- function(x, covariates="mean", intmisc="intens", sojourn=FALSE, cl=0.95, B=1000) {
    q.list <- normboot.msm(x, function(x)qematrix.msm(x=x, covariates=covariates, intmisc=intmisc, ci="none"), B)
    q.array <- array(unlist(q.list), dim=c(dim(q.list[[1]]), length(q.list)))
    q.ci <- apply(q.array, c(1,2), function(x)(c(quantile(x, c(0.5 - cl/2, 0.5 + cl/2)), sd(x))))
    q.ci <- aperm(q.ci, c(2,3,1))
    if (sojourn) {
        soj.array <- apply(q.array, 3, function(x) -1/diag(x))
        soj.ci <- apply(soj.array, 1, function(x)(c(quantile(x, c(0.5 - cl/2, 0.5 + cl/2)), sd(x))))
        list(q=q.ci, soj=soj.ci)
    }
    else q.ci
}

qratio.normci.msm <- function(x, ind1, ind2, covariates="mean", cl=0.95, B=1000) {
    q.list <- normboot.msm(x, function(x)qratio.msm(x=x, ind1=ind1, ind2=ind2, covariates=covariates)["estimate"], B)
    q.vec <- unlist(q.list)
    c(quantile(q.vec, c(0.5 - cl/2, 0.5 + cl/2)), sd(q.vec))
}

pmatrix.normci.msm <- function(x, t, t1, covariates="mean", cl=0.95, B=1000) {
    p.list <- normboot.msm(x, function(x)pmatrix.msm(x=x, t=t, t1=t1, covariates=covariates, ci="none"), B)
    p.array <- array(unlist(p.list), dim=c(dim(p.list[[1]]), length(p.list)))
    p.ci <- apply(p.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    aperm(p.ci, c(2,3,1))
}

pmatrix.piecewise.normci.msm <- function(x, t1, t2, times, covariates="mean", cl=0.95, B=1000) {
    p.list <- normboot.msm(x, function(x)pmatrix.piecewise.msm(x=x, t1=t1, t2=t2, times=times, covariates=covariates, ci="none"), B)
    p.array <- array(unlist(p.list), dim=c(dim(p.list[[1]]), length(p.list)))
    p.ci <- apply(p.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    aperm(p.ci, c(2,3,1))
}

totlos.normci.msm <- function(x, start=1, fromt=0, tot=Inf, covariates="mean", cl=0.95, B=1000, ...) {
    t.list <- normboot.msm(x, function(x)totlos.msm(x, start, fromt, tot, covariates, ci="none"), B)
    t.array <- do.call("rbind", t.list)
    apply(t.array, 2, function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
}

expected.normci.msm <- function(x,
                                times=NULL,
                                timezero=NULL,
                                initstates=NULL,
                                covariates="mean",
                                misccovariates="mean",
                                piecewise.times=NULL,
                                piecewise.covariates=NULL,
                                risk=NULL,
                                cl=0.95, B=1000) {
    if(is.null(risk)) risk <- observed.msm(x)$risk
    e.list <- normboot.msm(x, function(x){
        expected.msm(x, times, timezero, initstates, covariates, misccovariates, piecewise.times, piecewise.covariates, risk)
    }, B)
    e.tab.array <- array(unlist(lapply(e.list, function(x)x[[1]])), dim=c(dim(e.list[[1]][[1]]), length(e.list)))
    e.perc.array <- array(unlist(lapply(e.list, function(x)x[[2]])), dim=c(dim(e.list[[1]][[2]]), length(e.list)))
    e.tab.ci <- apply(e.tab.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    e.perc.ci <- apply(e.perc.array, c(1,2), function(x)(quantile(x, c(0.5 - cl/2, 0.5 + cl/2))))
    res <- list(aperm(e.tab.ci, c(2,3,1)),  aperm(e.perc.ci, c(2,3,1)))
    names(res) <- c("Expected", "Expected percentages")
    res
}
