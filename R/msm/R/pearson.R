### Pearson-type goodness-of fit test (Aguirre-Hernandez and Farewell, 2002; Titman and Sharples, 2007)

### TODO for pci models, don't group by 

pearson.msm <- function(x, transitions=NULL, timegroups=3, intervalgroups=3, covgroups=3, groups=NULL,
                        boot=FALSE, B=500, 
                        next.obstime=NULL, # user-supplied next observation times, if known.
                        N=100,
                        indep.cens=TRUE, # use censoring times when calculating the empirical distribution of sampling times
                        maxtimes=NULL # upper limit for imputed next observation times
                        ) {

    dat <- x$data
    ## Error handling    
    if (!inherits(x, "msm")) stop("expected \"x\" t to be a msm model")
    if (x$hmodel$hidden && !x$emodel$misc) stop("only HMMs handled are misclassification models specified using \"ematrix\"")
    if (any(dat$obstype==2)) stop("exact transition times are not supported, only panel-observed data")
    if (!is.null(transitions) && !is.numeric(transitions)) stop("expected \"transitions\" to be numeric")
    if (!is.numeric(timegroups) || length(timegroups) != 1) stop ("expected \"timegroups\" to be a single number")
    if (!is.numeric(intervalgroups) || length(intervalgroups) != 1) stop ("expected \"intervalgroups\" to be a single number")
    if (!is.numeric(covgroups) || length(covgroups) != 1) stop ("expected \"covgroups\" to be a single number")
    if (!is.numeric(B) || length(B) != 1) stop ("expected \"B\" to be a single number")
    if (!is.numeric(N) || length(N) != 1) stop ("expected \"N\" to be a single number")

    ## Use only one covariate group for pci models with no other covariates
    if (!is.null(x$pci) && length(grep("timeperiod\\[([0-9]+|Inf),([0-9]+|Inf)\\)", x$qcmodel$covlabels)) == x$qcmodel$ncovs)
        covgroups <- 1

    ## Label various constants 
    nst <- x$qmodel$nstates
    exact.death <- any(dat$obstype == 3)
    dstates <- if (exact.death) absorbing.msm(x) else NULL
    ndstates <- if (exact.death) transient.msm(x) else 1:nst
    nndstates <- length(ndstates)

    ## Add a few useful variables to the data
    obstypename <- if (x$hmodel$hidden || x$cmodel$ncens > 0) "obstype" else "obstype.obs"
    od <- as.data.frame(dat[c("subject","time","state",obstypename)])
    od$cov <- dat$cov.orig
    od$state <- factor(od$state, levels=sort(unique(od$state)))
    n <- dat$n
    od$ind <- 1:n # index into original data (useful if any rows of od are dropped)
    od$prevstate <- factor(c(NA,od$state[1:(n-1)]),  levels=1:nndstates)
    od$prevtime <- c(NA, od$time[1:(n-1)])
    od$firstobs <- rep(tapply(1:n,od$subject,min)[as.character(unique(od$subject))],
                    table(od$subject)[as.character(unique(od$subject))])
    od$obsno <- 1:n - od$firstobs + 1
    if (!is.null(next.obstime) && (!is.numeric(next.obstime) || length(next.obstime) != n)) stop (paste("expected \"next.obstime\" to be a numeric vector length", n))
    od$timeinterval <- if (is.null(next.obstime)) (od$obsno>1)*(od$time - od$time[c(1,1:(n-1))]) else next.obstime
    if (!is.null(maxtimes) && (!is.numeric(maxtimes) || !(length(maxtimes) %in% c(1,n)))) stop (paste("expected \"maxtimes\" to be a numeric vector length 1 or", n))
    if (!is.null(groups) && (!(length(groups) == n))) stop (paste("expected \"groups\" to be a vector length", n))
    od$maxtimes <- if (is.null(maxtimes))
        ifelse(od$state %in% dstates, max(od$timeinterval) + 1, od$timeinterval) ## Set max possible obs time for deaths to be max observed plus arbitrary one unit
    else rep(maxtimes, length=n) # if supplied as a scalar, use it for all obs
    od$usergroup <- factor(if (!is.null(groups)) groups else rep(1, n)) ## User-supplied groups 

    ## Method is restricted to "terminal" censoring (means not dead, occurs at end)
    ## Drop censored states not at the end of individual series 
    lastobs <- c(od$subject[1:(n-1)] != od$subject[2:n], TRUE)
    cens.notend <- (od$state %in% x$cmodel$censor) &  (!lastobs)
    if (any(cens.notend)) {
        od <- od[!cens.notend,]
        warning("Omitting censored states not at the end of individual series")
    }
    ## Drop observations of censoring types other than "not dead"
    if (length(x$cmodel$censor) >= 2) {
        ind <- NULL
        for (i in 1:length(x$cmodel$censor)) {
            if (identical(x$cmodel$states[x$cmodel$index[i] : (x$cmodel$index[i+1]-1)], as.numeric(transient.msm(x))))
            {ind <- i; break}
        }
        if (is.null(ind))
            warning("Omitting all censored states")
        else {
            cens.drop <- od$state %in% x$cmodel$censor[-ind]
            warning("Omitting censored states of types other than ",x$cmodel$censor[ind])
        }
        od <- od[!cens.drop,]
    }
    n <- nrow(od)
    nstcens <- length(unique(od$state)) # no. unique states in data, should be same as number of markov states plus number of censor types (max 1)
    cens <- nstcens > nst # is there any remaining censoring 
    
    ## Check and label transition groupings. Store data in a list
    ## Includes transitions to terminal censoring as separate states
    trans <- list()
    trans$allowed <- intervaltrans.msm(x, exclude.absabs=TRUE, censor=cens)
    trans$labsall <- paste(trans$allowed[,1], trans$allowed[,2], sep="-")
    trans$allowed[trans$allowed[,2] > nst, 2] <- nst+1 # these are to be used as indices, so label censoring as nst+1 not e.g. 99
    trans$na <- nrow(trans$allowed)
    trans$use <- if (is.null(transitions)) 1:trans$na else transitions  # why was this a matrix before? 
    if (length(trans$use) != trans$na)
        stop("Supplied ", length(trans$use), " transition indices, expected ", trans$na)
    else if (!x$emodel$misc &&
             ! all(tapply(trans$allowed[,1], trans$use, function(u)length(unique(u))) == 1) )
        stop("Only transitions from the same origin can be grouped")
    ## convert ordinal transition indices to informative labels
    trans$labsagg <- tapply(trans$labsall, trans$use, function(u)paste(u,collapse=",")) 
    trans$from <- trans$allowed[,1][!duplicated(trans$use)] # from-state corresp to each element of trans$labsagg
    trans$to <- trans$allowed[,2][!duplicated(trans$use)] # to-state corresp to each element of trans$labsagg
    trans$ngroups <- length(unique(trans$use))

    ## Determine unique Q matrices determined by covariate combinations
    ncovs <- x$qcmodel$ncovs
    if (ncovs>0) {
        uniq <- unique(as.data.frame(od$cov[,dat$covdata$whichcov.orig,drop=FALSE]))
        nouniq <- dim(uniq)[1]
        pastedu <- do.call("paste",uniq)
        pastedc <- do.call("paste",as.data.frame(od$cov[,dat$covdata$whichcov.orig,drop=FALSE]))
        qmatindex <- match(pastedc,pastedu)
        qmat <- array(0,dim=c(nst,nst,nouniq))
        for (i in 1:nouniq)
            qmat[,,i] <- qmatrix.msm(x, covariates=as.list(uniq[i,]), ci="none")
    }else{
        qmatindex <- rep(1,n)
        nouniq <- 1
        qmat <- array(qmatrix.msm(x,ci="none"),dim=c(nst,nst,1))
    }
    qmatmaster <- qmat
    qmat <- qmat[,,qmatindex]
    od$rates <- apply(qmat,3,function(u) sum(diag(u)))

    ## Now work with a dataset with one row per transition
    md <- od[od$obsno>1,]
    qmat <- qmat[,,od$obsno>1]
    qmatindex <- qmatindex[od$obsno>1]
    ntrans <- nrow(md)
    nfromstates <- length(unique(md$prevstate)) 

    ## Groups based on time since initiation (not observation number)
    timegroups.use <- min(length(unique(md$time)), timegroups)
    md$timegroup <- qcut(md$time, timegroups.use)    

    ## Group time differences by quantiles within time since initiation
    intervalq <- tapply(md$timeinterval[md$state %in% ndstates],
                        md$timegroup[md$state %in% ndstates],
                        ## Categorise quantiles based only on full observations, not deaths or censoring.
                        function(x) quantile(x,probs=seq(0,1,1/intervalgroups)))
    md$intervalgroup <- rep(1, ntrans)
    for (i in levels(md$timegroup))
        md$intervalgroup[md$timegroup==i] <- unclass(qcut(md$timeinterval[md$timegroup==i], qu = intervalq[[i]]))
    md$intervalgroup <- factor(md$intervalgroup)

    ## Groups based on covariates
    covgroups.use <- min(length(unique(md$rates)), covgroups)
    md$covgroup <- if (ncovs > 0) qcut(md$rates, covgroups.use) else factor(rep(1,ntrans))
    groupdims <- c(length(levels(md$timegroup)),length(levels(md$intervalgroup)),length(levels(md$covgroup)),length(levels(md$usergroup)))
    groupdimnames <- list(levels(md$timegroup),levels(md$intervalgroup),levels(md$covgroup),levels(md$usergroup))

    ## Determine empirical distribution of time interval lengths.  
    ## Then impute next scheduled observation for transitions which end in exact death times
    md$obtype <- rep(0, ntrans)
    if (exact.death) md$obtype[md$state %in% dstates] <- 1
    md$obtype[md$state %in% x$cmodel$censor] <- 2 
    md$cens <- factor(md$obtype==2, levels=c(0,1))
    ndeath  <-  sum(md$obtype==1)
    if (exact.death && is.null(next.obstime)) {
        cat("Imputing sampling times after deaths...\n")
        incl <- if (indep.cens) (0:2) else (0:1)
        empiricaldist <- empiricaldists(md$timeinterval[md$obtype %in% incl], md$state[md$obtype %in% incl],
                                        as.numeric(md$timegroup[md$obtype %in% incl]), timegroups, ndstates)
        imputation <- array(0,c(ndeath,N,4))
        dimnames(imputation) <- list(NULL, NULL, c("times","cens","intervalgroup","timeqmatindex"))
        deathindex <- which(md$obtype==1)
        for (i in 1:ndeath) {
            mintime <- md$timeinterval[deathindex[i]]
            centime <- md$maxtimes[deathindex[i]] # - md$time[deathindex[i]] + mintime
            tg <- md$timegroup[deathindex[i]]
            ## returns list of times, whether would have ended in censoring, and time category.
            st <- sampletimes(mintime, centime, empiricaldist[,tg,empiricaldist["time",tg,]>0], N, tg, intervalq)            
            for (j in c("times","cens","intervalgroup"))
                imputation[i,,j] <- st[,j]
        }
    }
    else imputation <- deathindex <- NULL
    ndeathindex <- setdiff(1:ntrans, deathindex)
    
    ## Transition probability matrices are indexed by unique combinations of time intervals and Q matrices.
    timeint <- c(md$timeinterval[md$obtype != 1],c(imputation[,,"times"])) # time intervals, excluding deaths, concatenated with imputations of next interval after death
    qmatint <- c(qmatindex[md$obtype != 1],rep(qmatindex[deathindex],N)) # index into unique Q matrices
    timeqmata <- unique(data.frame(timeint,qmatint))
    timeqmat <- paste(timeint,qmatint,sep="-")
    pastedu <- unique(timeqmat)
    timeqmatindex <- match(timeqmat,pastedu)
    ## Work out the transition probability matrix for each unique time interval and Q matrix
    npmats<-length(pastedu)
    pmi <- array(0,dim=c(nst,nst,npmats))
    for (i in unique(timeqmata[,2]))
        pmi[,,timeqmata[,2]==i] <- MatrixExp(qmatmaster[,,i], timeqmata[timeqmata[,2]==i,1])
    md$timeqmatindex<-rep(0,ntrans)
    md$timeqmatindex[md$obtype != 1] <- timeqmatindex[1:(ntrans-ndeath)]
    if (exact.death && is.null(next.obstime))
        imputation[,,"timeqmatindex"] <- timeqmatindex[(ntrans-ndeath+1):length(timeqmatindex)]

    ### Calculate transition probabilities for non-death intervals
    prob <- array(0,dim=c(nst,ntrans)) ## array of obs state probs, conditional on previous obs state
    if (x$emodel$misc) {         
        misccov <-
            if (x$ecmodel$ncovs > 0) od$cov[x$hmodel$whichcovh.orig[1:x$ecmodel$ncovs]][od$obsno>1,,drop=FALSE]
            else NULL
        p.true <- array(dim=c(nst, ntrans)) # prob of each true state conditional on complete history including current obs
        initp <- if (x$foundse) x$hmodel$initprobs[,"Estimate"] else x$hmodel$initprobs
        if (x$ecmodel$ncovs > 0) {
            uniqmisc <- unique(misccov)
            ematindex <- match(do.call("paste",misccov), do.call("paste", uniqmisc))
            emat <- array(0,dim=c(nst,nst,nrow(uniqmisc)))
            for (i in 1:nrow(uniqmisc))
                emat[,,i] <- ematrix.msm(x, covariates=as.list(uniqmisc[i,]),ci="none")
        }
        else emat <- ematrix.msm(x, ci="none")
        for (i in 1:ntrans) {            
            ematrix <- if (x$ecmodel$ncovs>0) emat[,,ematindex[i]] else emat
	    if (md$state[i] %in% ndstates) {
              T <- pmi[,,md$timeqmatindex[i]] * matrix(ematrix[,md$state[i]], nrow=nst, ncol=nst, byrow=TRUE)
              p.true[,i] <- if (md$obsno[i] == 2) t(initp) %*% T else t(p.true[,i-1]) %*% T
              p.true[,i] <- p.true[,i] / sum(p.true[,i])  # prob of each true state
            }
	    if (!(md$state[i] %in% dstates)) {
                prob[,i] <-
                    if (md$obsno[i] == 2) initp %*% pmi[,,md$timeqmatindex[i]] %*% ematrix
                    else p.true[,i-1] %*% pmi[,,md$timeqmatindex[i]] %*% ematrix
            }
        }
    }
    else
        prob[cbind(rep(1:nst,ntrans-ndeath),rep((1:ntrans)[ndeathindex],each=nst))] <-
            pmi[cbind(rep(md$prevstate[(1:ntrans)[ndeathindex]],each=nst),
                      rep(1:nst,ntrans - ndeath),rep(md$timeqmatindex[(1:ntrans)[ndeathindex]],each=nst))]

    if (exact.death && is.null(next.obstime)) {
        stat.sim <- rep(0,N)
        obs.rep <- exp.rep <- dev.rep <- array(0, dim=c(groupdims, trans$ngroups, N))
        dimnames(obs.rep) <- dimnames(exp.rep) <- dimnames(dev.rep) <- c(groupdimnames, list(trans$labsagg), list(1:N))
        cat("Calculating replicates of test statistics for imputations...\n")
        for (i in 1:N) {
            ## Calculate transition probabilities for death intervals 
            if (x$emodel$misc) {
                for (j in 1:ndeath) {
                    k <- deathindex[j]
                    ematrix <- if (x$ecmodel$ncovs>0) emat[,,ematindex[k]] else emat
                    prob[,k] <-
                        if (md$obsno[k] == 2) initp %*% pmi[,,imputation[j,i,"timeqmatindex"]] %*% ematrix
                        else p.true[,k-1] %*% pmi[,,imputation[j,i,"timeqmatindex"]] %*% ematrix
                }
            }
            else
                prob[cbind(rep(1:nst,ndeath),rep(deathindex,each=nst))] <-
                    pmi[cbind(rep(md$prevstate[deathindex],each=nst),rep(1:nst,ndeath),rep(imputation[,i,"timeqmatindex"],each=nst))]

            md$intervalgroup[deathindex] <- factor(imputation[,i,"intervalgroup"], labels=levels(md$intervalgroup[deathindex])[sort(unique(imputation[,i,"intervalgroup"]))])

            md$cens[deathindex] <- as.numeric(imputation[,i,"cens"]) # factor levels 0/1

            ## Observed transition table, including to censoring indicators
            obs.rep.i <- table(md$state, md$prevstate, md$timegroup, md$intervalgroup, md$covgroup, md$usergroup)
            
            ## Expected transition table
            exp.cens <- array(0, dim = c(nst, nndstates, groupdims, 2))
            for (j in 1:nst)
                exp.cens[j,,,,,,] <- tapply(prob[j,], list(md$prevstate,md$timegroup,md$intervalgroup,md$covgroup,md$usergroup,md$cens), sum)
            exp.cens <- replace(exp.cens,is.na(exp.cens),0)
            exp.unadj <- array(0, dim=c(nstcens, nndstates, groupdims))
            exp.unadj[1:nst,,,,,] <- exp.cens[,,,,,,1]
            for (j in dstates)
                exp.unadj[j,,,,,] <- exp.cens[j,,,,,,1] + exp.cens[j,,,,,,2]

            if (cens)
                exp.unadj[nst+1,,,,,] <- apply(exp.cens[1:nndstates,,,,,,2,drop=FALSE], 2:6, sum) # total censored from any non-death state
            ## Remove very small values, caused by inaccuracy in numerical matrix exponential.
            exp.unadj <- replace(exp.unadj,(exp.unadj<sqrt(.Machine$double.eps)),0)
            ## Adjust it for censoring 
            exp.rep.i <- adjust.expected.cens(exp.unadj, obs.rep.i, nst, ndstates, dstates, groupdims, N, cens, md, nstcens)

            agg <- agg.tables(obs.rep.i, exp.rep.i, groupdims, groupdimnames, trans)
            obs.rep.i <- agg$obs; exp.rep.i <- agg$exp
            dev.rep.i <- (obs.rep.i - exp.rep.i)^2/(exp.rep.i + (exp.rep.i==0))
            obs.rep[,,,,,i] <- obs.rep.i
            exp.rep[,,,,,i] <- exp.rep.i
            dev.rep[,,,,,i] <- dev.rep.i
            stat.sim[i] <- sum(dev.rep.i)
        }
        obstable <- apply(obs.rep, 1:5, mean)
        exptable <- apply(exp.rep, 1:5, mean)
        exptable <- replace(exptable,(exptable < sqrt(.Machine$double.eps)), 0)
        devtable <- apply(dev.rep, 1:5, mean)
        stat <- mean(stat.sim)
    }
    else {
        obstable <- exptable <- array(0,dim=c(nstcens, nndstates, groupdims))
        dimnames(obstable) <- dimnames(exptable) <- c(list(1:nstcens, 1:nndstates), groupdimnames)
        obstable <- table(md$state, md$prevstate, md$timegroup, md$intervalgroup, md$covgroup, md$usergroup)
        exp.cens <- array(0, dim = c(nst,nndstates,groupdims,2))
        for (j in 1:nst)
            exp.cens[j,,,,,,] <- tapply(prob[j,], list(md$prevstate,md$timegroup,md$intervalgroup,md$covgroup,md$usergroup,md$cens), sum)
        exp.cens <- replace(exp.cens,is.na(exp.cens),0)
        exptable <- array(0, dim=c(nstcens, nndstates, groupdims))
        exptable[1:nst,,,,,] <- exp.cens[,,,,,,1]
        exptable[nst,,,,,] <- exp.cens[nst,,,,,,1] + exp.cens[nst,,,,,,2]
        if (cens)
            exptable[nst+1,,,,,] <- apply(exp.cens[1:nndstates,,,,,,2,drop=FALSE], 2:6, sum) # total censored from any non-death state
        exptable <- replace(exptable,(exptable < sqrt(.Machine$double.eps)), 0)
        ## adjust expected values for censoring if necessary
        if (cens) 
            exptable <- adjust.expected.cens(exptable, obstable, nst, ndstates, dstates, groupdims, N, cens, md, nstcens)
        agg <- agg.tables(obstable, exptable, groupdims, groupdimnames, trans)
        obstable <- agg$obs; exptable <- agg$exp
        devtable <- (obstable-exptable)^2/(exptable+(exptable==0))            
        stat <- sum(devtable)
    }        

    n.indep.trans <- length(trans$from[trans$to <= nst]) - length(unique(trans$from[trans$to <= nst]))
    ## number of states x categories from which there were zero transitions, excluding states with only one destination (which were already removed in the previous line)
    n.zerofrom <- sum(apply(obstable, 1:4, function(u)tapply(u, trans$from, sum)) [ table(trans$from) > 1 , , , ,] == 0) 
    df.upper <- prod(dim(obstable)[1:4])*n.indep.trans - n.zerofrom
    df.lower <- df.upper - length(x$opt$par)
    test <- data.frame(stat=stat,
                       df.lower = if (exact.death && is.null(next.obstime)) NA else df.lower,
                       p.lower = if (exact.death && is.null(next.obstime)) NA else 1-pchisq(stat, df.lower),
                       df.upper=df.upper, p.upper=1-pchisq(stat, df.upper)); rownames(test) <- ""

    ## Simulated observation times to use as sampling frame for bootstrapped data
    if (!is.null(imputation)) {
      imp.times <- matrix(rep(dat$time, N), nrow=length(dat$time), ncol=N)
      prevtime <- imp.times[which(dat$state %in% dstates) - 1,]
      imp.times[dat$state %in% dstates, ] <- prevtime + imputation[,,"times"]
    }
    else imp.times <- NULL
    
    if (boot) {
        cat("Starting bootstrap refitting...\n")
        boot.stats <- pearson.boot.msm(x, imp.times=imp.times, transitions=transitions, timegroups=timegroups, intervalgroups=intervalgroups, covgroups=covgroups, groups=groups,
                                       B=B, df=df.upper)
        test$p.boot <- sum(boot.stats > stat) / B
    }
    pearson <- list(observed=obstable, expected=exptable, deviance=devtable*sign(obstable-exptable), test=test, intervalq=intervalq)    
    names(pearson) <- c("Observed","Expected","Deviance*sign(O-E)","test","intervalq")    
    if (exact.death && is.null(next.obstime)) pearson$sim <- list(observed=obs.rep, expected=exp.rep, deviances=dev.rep, stat=stat.sim, imputation=imputation)    
    if (boot) pearson$boot <- boot.stats
    pearson <- reformat.pearson.msm(pearson)
    class(pearson) <- "pearson.msm"
    pearson
}

### Reformat array output from Pearson test as a matrix with transition type in columns

reformat.pearson.msm <- function(pearson) {
    pp <- pearson
    nd <- length(dim(pearson$Observed))
    for (i in 1:3) {
        dim(pp[[i]]) <- c(prod(dim(pp[[i]])[-nd]), dim(pp[[i]])[nd])
        rnames <- do.call("expand.grid", dimnames(pearson$Observed)[1:4])
        colnames(pp[[i]]) <- dimnames(pearson$Observed)[[nd]]
        pp[[i]] <- as.data.frame(pp[[i]])
        pp[[i]] <- cbind(rnames, pp[[i]])
        colnames(pp[[i]])[1:4] <- c("Time","Interval","Cov","User")
        drop <- NULL # drop columns labelling categories with only one value
        for (j in 1:4)
            if (length(unique(pp[[i]][,j]))==1) drop <- c(drop,j)
        pp[[i]] <- pp[[i]][,-drop]
    }
    pp
}

### Keep the simulation and bootstrap output but don't print it

print.pearson.msm <- function(x, ...){
    print(x[!(names(x) %in% c("sim","boot","intervalq"))])
}

### Adaptation of cut(quantile()) so that if two quantiles are equal, a unique category is created for x equal to that
### For point intervals, the label is just the value of the point
### Else, the labels are in (a,b] or [a,b) type interval notation

qcut <- function(x, n, qu=NULL, eps=1e-06, digits=2, drop.unused.levels=FALSE) {
    if (is.null(qu))
        qu <- quantile(x, probs = seq(0, 1, 1/n))
    q2.equal <- sequence(table(qu)) <= 2
    qu <- qu[q2.equal] ## If three or more quantiles are equal, only keep two of them.
    ## Ensure all x fall within intervals, widening upper and lower intervals if necessary. 
    qu[qu==max(qu)] <- max(max(qu),x)
    qu[qu==min(qu)] <- min(min(qu),x)
    n <- length(qu)-1
    lagq <- c(-Inf, qu[1:n])
    qlabs <- paste("[",round(qu[1:n],digits),",",round(qu[2:(n+1)],digits),")",sep="")
    inti <- qu[1:n]==qu[2:(n+1)] # which intervals are points
    qlabs[inti] <- round(qu[1:n][inti], digits)
    lastopen <- if (n==1) FALSE else c(FALSE, inti[1:(n-1)])
    substr(qlabs[lastopen],1,1) <- "(" # interval with a point interval just before it is open on the left
    if (!inti[n])
       substr(qlabs[length(qlabs)], nchar(qlabs[length(qlabs)]), nchar(qlabs[length(qlabs)])) <- "]" # last interval is closed on the right
    qu[qu==lagq] <- qu[qu==lagq] + eps
    x.cut <- cut(x, qu, right=FALSE, include.lowest=TRUE, labels=qlabs)
    tx <- tapply(x, x.cut, unique)
    nxcats <- sapply(tx, length) # number of unique x values in each category
    nxcats[is.na(tx)] <- 0
    ## If only one unique x value is in a category, then label the category with that value
    if (any(nxcats==1))
        levels(x.cut)[nxcats == 1] <- round(unlist(tx[nxcats==1]), digits)
    if (drop.unused.levels) 
      x.cut <- factor(x.cut, exclude=NULL) # drop unused factor levels
    x.cut
}

### Parametric bootstrap  
### Simulate data from fitted model with same observation scheme 

boot.param.msm <- function(x){
    dat <- x$data
    sim.df <- as.data.frame(dat[c("subject","time","cens")])
    sim.df$obstrue <- dat$obstrue # NULL if not HMM
    sim.df$obstype <- if (!is.null(dat$obstype.obs)) dat$obstype.obs else dat$obstype
    sim.df$pci.imp <- dat$pci.imp
    if (x$qcmodel$ncovs > 0) {
        sim.df <- cbind(sim.df, dat$cov[,x$qcmodel$covlabels,drop=FALSE])
        sim.df <- cbind(sim.df, dat$cov.orig[,x$qcmodel$covlabels.orig,drop=FALSE])
        cov.effs <- lapply(x$Qmatrices, function(y)t(y)[t(x$qmodel$imatrix)==1])[x$qcmodel$covlabels]
    }
    else cov.effs <- NULL
    if (x$ecmodel$ncovs > 0) {
        sim.df <- cbind(sim.df, dat$cov[,setdiff(x$ecmodel$covlabels,x$qcmodel$covlabels),drop=FALSE])
        sim.df <- cbind(sim.df, dat$cov.orig[,setdiff(x$ecmodel$covlabels.orig,x$qcmodel$covlabels.orig),drop=FALSE])
        misccov.effs <- lapply(x$Ematrices, function(y)t(y)[t(x$emodel$imatrix)==1])[x$ecmodel$covlabels]
    }
    else misccov.effs <- NULL
    boot.df <- simmulti.msm(data=sim.df,
                            qmatrix=qmatrix.msm(x, covariates=0, ci="none"),
                            covariates=cov.effs,
                            death=FALSE,
                            ematrix=ematrix.msm(x, covariates=0, ci="none"),
                            misccovariates=misccov.effs
                            )
}


pearson.boot.msm <- function(x, imp.times=NULL, transitions=NULL, timegroups=4, intervalgroups=4, covgroups=4, groups=NULL, B=500, df){
  bootstat <- numeric(B)
  x$call$formula <- if (x$emodel$misc) substitute(obs ~ time) else substitute(state ~ time)
  x$call$qmatrix <- qmatrix.msm(x,ci="none") # put MLE in inits.
  x$call$hessian <- x$call$death <- FALSE
  x$call$obstype <- NULL
  x$call$subject <- substitute(subject)
  i <- 1
  while (i <= B) {
    if (!is.null(imp.times))
     x$data$time <- imp.times[,sample(ncol(imp.times), size=1)]  # resample one of the imputed sets of observation times
    x$data$cens <- ifelse(x$data$state %in% 1:x$qmodel$nstates, 0, x$data$state) # 0 if not censored, cens indicator if censored, so that censoring is retained in simulated data
    boot.df <- boot.param.msm(x)
    boot.df <- boot.df[!boot.df$pci.imp,]
    x$call$data <- substitute(boot.df)
    refit.msm <- try(eval(x$call))        
    if (inherits(refit.msm, "msm")) {
      p <- pearson.msm(refit.msm, transitions=transitions, timegroups=timegroups,
                       intervalgroups=intervalgroups, covgroups=covgroups, groups=groups, boot=FALSE)
      bootstat[i] <- p$test$stat
      i <- i + 1
    }
  }
  bootstat
}

### Work out empirical distribution of sampling times for each observation (or time since initiation) group:
    
empiricaldists  <-  function(timeinterval, state, obgroup, obgroups, ndstates) {
    empdist <- array(0,c(3, obgroups, max(table(obgroup[state %in% ndstates])))) # Need times, cum value and point mass value
    dimnames(empdist) <- list(c("time", "surv", "pdeath"), levels(obgroup), NULL)
    ## First dimension:   1: time, 2: surv prob 3: death prob in prev interval
    ## Second dim: observation group.  Third dim: size of biggest obs group (i.e. maximum number of event times for KM estimate)
    for (i in 1:obgroups) {
        ##s1 <- survfit(Surv(timeinterval[obgroup==i],(state[obgroup==i] %in% ndstates))~1,type="kaplan-meier")
        ##survfit seems to ignore increments of small size ## TODO investigate this
        ##Instead use own code to create KM
        elig <- (obgroup==i & state %in% ndstates)
        eligt <- sort(unique(timeinterval[elig]))
        events <- table(timeinterval[elig])
        allt <- sort(timeinterval[obgroup==i])
        empdist["time",i,1:length(eligt)] <- eligt
        for (j in 1:length(eligt)) {
            empdist["surv",i,j] <-  if (j>1) (empdist["surv",i,j-1]*(1 - events[j]/sum(allt>=eligt[j]))) else  (1 - events[j]/sum(allt>=eligt[j]))
            empdist["pdeath",i,j] <-  if (j>1) (empdist["surv",i,j-1] - empdist["surv",i,j]) else  (1 - empdist["surv",i,j])
            ## Now deals with ties correctly
        }
    }
    empdist
}


### For a single death, sample N points from the distribution of the next sampling time
### mintime, centime: minimum and maximum possible times
### dist: matrix of times, survival probs and previous-interval death probs 
    
sampletimes <- function(mintime, centime, dist, N, obgroup, intervalq) {
    ## dist takes the overall distribution from the relevant obgroup, but since we supply obgroup it might be better to just supply the whole thing
    dist <- dist[,dist[1,]>mintime,drop=FALSE] # Remove times before the minimum possible time.
    if (length(dist) > 0) {
        dist[c("surv","pdeath"),] <- dist[c("surv","pdeath"),] / dist["surv",1] # Normalise
        ## Compute the censoring fraction
        cen <- 1 - sum(dist["pdeath",dist["time",]<centime])
        dist <- dist[, dist["time",]<centime, drop=FALSE]
        if (length(dist)>0) {
            cend <- as.numeric(runif(N) < cen)
            if (length(dist["time",])>1) {
                ## Suppress "Walker's alias method used, results incompatible with R < 2.2.0" warning
                times <- suppressWarnings(sample(dist["time",],N,replace=TRUE,prob=dist["pdeath",])) * (cend==0) + centime*(cend==1)
            }else{
                times <- dist["time",]*(cend==0) + centime*(cend==1)
            }
        }else{
            cend <- rep(1,N)
            times <- rep(centime,N)
        }
    }else{
        cend <- rep(1,N)
        times <- rep(centime,N)
    }
    intervalgroup <- qcut(times,qu=intervalq[[obgroup]])
    cbind(times=times, cens=cend, intervalgroup=intervalgroup)
}

## make internal to pearson function 
## requires table of expected values with dims:  nstcens, nndstates, groupdims
## also observed table with same dims
## prob need to calculate these in every case.
## why not do this calculation with the ungrouped version of the table, collapse the first two dims, then aggregate the table by trans$use 


### Replace fromstate,tostate dimensions at beginning by a single allowed-transition dimension at end

agg.tables <- function(obs.full, exp.full, groupdims, groupdimnames, trans) {
    obstable <- exptable <- array(dim=c(groupdims, trans$na))
    for (i in 1:trans$na) {
        obstable[,,,,i] <- obs.full[trans$allowed[i,2],trans$allowed[i,1],,,,]
        exptable[,,,,i] <- exp.full[trans$allowed[i,2],trans$allowed[i,1],,,,]
    }
    obstable <- replace(obstable,is.na(obstable),0) 
    exptable <- replace(exptable,is.na(exptable),0)
    ## Aggregate by transition groups 
    obstable  <-  aperm(apply(obstable, 1:4, function(u)tapply(u, trans$use, sum)), c(2:5,1))
    exptable <- aperm(apply(exptable, 1:4, function(u)tapply(u, trans$use, sum)), c(2:5,1))
    dimnames(obstable) <- dimnames(exptable) <- c(groupdimnames, list(trans$labsagg))
    list(obs=obstable, exp=exptable)
}

### Adjust expected counts to account for informative censoring times, according to method in paper addendum.

adjust.expected.cens <- function(exp.unadj, obs,
                                 nst, ndstates, dstates, groupdims, N, cens, md, nstcens)
{
    ## Compute total expected counts from each from-state, summed over destination state (n-tilde in paper addendum)
    nndstates <- length(ndstates)
    dims <- c(nndstates, groupdims)
    nobs <- apply(obs, 2:6, sum)  # Obs trans summed over first dimension = destination state = Number of trans from state r in group
    nobs.xd <- nobs - array(obs[nst,,,,,], dim=dims)  # Number of trans excluding death 
    nobs.xdc <- if (cens) nobs.xd - array(obs[nst+1,,,,,,drop=FALSE], dim=dims) else nobs.xd # excluding death and censoring 
    po <- array(0, dim = c(nst+1, dims))  # p-hat in appendix to paper, MLEs from unrestricted alternative model
    for (j in ndstates) # prop of uncensored trans from state r (and group) ending in state j (not death), multiplied by prop of trans not ending in death. 
        po[j,,,,,] <- (array(obs[j,,,,,], dim=dims) * nobs.xd)/(nobs.xdc*nobs + (nobs.xdc*nobs==0))
    for (j in dstates)
        po[nst,,,,,] <- array(obs[j,,,,,], dim=dims) / (nobs + (nobs==0)) # prop of trans from state r (and group) ending in death. (if zero in denom, this is 0)
    po[nst+1,,,,,] <- 1 - apply(po[dstates,,,,,,drop=FALSE], 2:6, sum)
    po <- replace(po, is.na(po), 0)

    nexp <- apply(exp.unadj, 2:6, sum)
    nexp.xd <- nexp - array(exp.unadj[nst,,,,,], dim=dims)
    nexp.xdc <- if (cens) nexp.xd - array(exp.unadj[nst+1,,,,,,drop=FALSE],dim=dims) else nexp.xd
    ps <- array(0,dim=c(nst+1, dims)) # p-tilde-star in addendum to paper. "robustified" MLEs from null Markov model
    for (j in ndstates)
        ps[j,,,,,] <- (array(exp.unadj[j,,,,,], dim=dims)*nexp.xd)/(nexp.xdc*nexp + (nexp.xdc*nexp==0))
    for (j in dstates)
        ps[j,,,,,] <- array(exp.unadj[j,,,,,], dim=dims)/(nexp + (nexp==0))
    ps[nst+1,,,,,] <- 1 - apply(ps[dstates,,,,,,drop=FALSE], 2:6, sum)
    ps <- replace(ps,is.na(ps),0)

    ncen <- tapply(md$cens, list(md$prevstate,md$timegroup,md$intervalgroup,md$covgroup,md$usergroup), function(x)sum(x==1))
    dim(ncen) <- dims
    ncen <- replace(ncen, is.na(ncen), 0)
    exp.adj <- array(0, dim=c(nstcens,dims)) #  = p-tilde-star * n / phat  (in notation of paper)  =   ps * obs / po
    exp.adj[ndstates,,,,,] <-
        ps[ndstates,,,,,,drop=FALSE] *
            rep(nobs.xdc * nobs,each=nndstates) /
                rep(nobs.xd + (nobs.xd==0),each=nndstates)
    for (j in dstates) 
        exp.adj[j,,,,,] <- array(ps[j,,,,,], dim=dims) * nobs
    if (cens)
        exp.adj[nst+1,,,,,] <- nobs - apply(exp.adj[1:nst,,,,,,drop=FALSE], 2:6, sum)

    exp.adj
}


