\name{msm}
\title{Multi-state Markov and hidden Markov models in continuous time}
\alias{msm}
\description{
  Fit a continuous-time Markov or hidden Markov multi-state model
  by maximum likelihood. Observations of the process
  can be made at arbitrary times, or the exact times of
  transition between states can be known. 
  Covariates can be fitted to the Markov chain transition intensities or
  to the hidden Markov observation process. 
}
\usage{
msm ( formula, subject=NULL, data = list(), qmatrix, gen.inits = FALSE,
      ematrix=NULL, hmodel=NULL, obstype=NULL, obstrue=NULL,
      covariates = NULL, covinits = NULL, constraint = NULL,
      misccovariates = NULL, misccovinits = NULL, miscconstraint = NULL,
      hcovariates = NULL, hcovinits = NULL, hconstraint = NULL,
      qconstraint=NULL, econstraint=NULL, initprobs = NULL,
      est.initprobs=FALSE, initcovariates = NULL, initcovinits = NULL, 
      death = FALSE, exacttimes = FALSE, censor=NULL, 
      censor.states=NULL, pci=NULL, cl = 0.95, fixedpars = NULL, center=TRUE,
      opt.method=c("optim","nlm"), hessian=TRUE, use.deriv=TRUE,
      analyticp=TRUE, ... )
}
\arguments{
  \item{formula}{ A formula giving the vectors containing the observed
    states and the corresponding observation times. For example,
    
    \code{state ~ time}

    Observed states should be in the set \code{1, \dots, n},
    where \code{n} is the number of states.
  }

  \item{subject}{Vector of subject identification numbers for the data
    specified by \code{formula}. If missing, then all observations
    are assumed to be on the same subject. These must be sorted so that
    all observations on the same subject are adjacent.}

  \item{data}{Optional data frame in which to interpret the variables
    supplied in \code{formula}, \code{subject}, \code{covariates},
    \code{misccovariates}, \code{hcovariates}, \code{obstype} and 
    \code{obstrue}.}

  \item{qmatrix}{Initial transition intensity matrix of the Markov
    chain.  If an instantaneous transition is not allowed  from state
    \eqn{r} to state \eqn{s}, then \code{qmatrix} should have
    \eqn{(r,s)} entry 0, otherwise it should be non-zero. Any 
    diagonal entry of \code{qmatrix} is ignored, as it is constrained to
    be equal to minus the sum of the rest of the row. For example,\cr
    
    \code{
    rbind(
    c( 0, 0.1, 0.01 ),
    c( 0.1, 0, 0.2 ),
    c( 0, 0, 0 )
    )
  }\cr
  
    represents a 'health - disease - death' model, with transition intensities
    0.1 from health to disease, 0.01 from health to death, 0.1 from disease to health, 
    and 0.2 from disease to death.  The initial intensities given here
    are with any covariates set to their means in the data (or set to
    zero, if \code{center} = FALSE). If any intensities are constrained
    to be equal using \code{qconstraint}, then the initial value is
    taken from the first of these (reading across rows). 
  }

  \item{gen.inits}{If \code{TRUE}, then initial values for the
    transition intensities are estimated by assuming that the data
    represent the exact transition times of the process. The non-zero
    entries of the supplied \code{qmatrix} are assumed to indicate the
    allowed transitions of the model.}
  
  \item{ematrix}{
    If misclassification between states is to be modelled, this should
    be a matrix of initial values for the misclassification probabilities.
    The rows represent underlying states, and the columns represent
    observed states.
    If an observation of state \eqn{s} is not possible when the subject
    occupies underlying state \eqn{r}, then \code{ematrix} should have
    \eqn{(r,s)} entry 0.  Otherwise \code{ematrix} should 
    have \eqn{(r,s)} entry corresponding to the probability of
    observing \eqn{s} conditionally on occupying true state \eqn{r}. The
    diagonal of \code{ematrix} is ignored, as rows are constrained to
    sum to 1.  For example, \cr

    \code{
      rbind(
    c( 0, 0.1, 0 ),
    c( 0.1, 0, 0.1 ),
    c( 0, 0.1, 0 )
    )
  }\cr
  
    represents a model in which misclassifications are only permitted
    between adjacent states. 

    If any probabilities are constrained to be equal using
    \code{econstraint}, then the initial value is
    taken from the first of these (reading across rows).
    
    For an alternative way of specifying misclassification models, see
    \code{hmodel}.
  }

  \item{hmodel}{
    Specification of the hidden Markov model.  This should be a list of   
    return values from the constructor functions described in the
    \code{\link{hmm-dists}} help
    page.  Each element of the list corresponds to the outcome model 
    conditionally on the corresponding underlying state.

    For example, consider a three-state hidden Markov model.  Suppose
    the observations in underlying state 1 are
    generated from a Normal distribution with mean 100 and standard
    deviation 16, while observations in underlying state 2 are Normal
    with mean 54 and standard deviation 18. Observations in state 3,
    representing death, are exactly observed, and coded as 999 in the
    data.  This model is specified as 

    \code{hmodel = list(hmmNorm(mean=100, sd=16), hmmNorm(mean=54, sd=18), hmmIdent(999))}

    The mean and standard deviation parameters are estimated starting
    from these initial values. If multiple parameters are constrained
    to be equal using \code{hconstraint}, then the initial value is
    taken from the value given on the first occasion that
    parameter appears in \code{hmodel}. 

    See the \code{\link{hmm-dists}} help page
    for details of the constructor functions for each available distribution. 
    
    A misclassification model, that is, a hidden Markov model where
    the outcomes are misclassified observations of the underlying
    states, can either be specified using a list of \code{\link{hmmCat}}
    objects, or by using an \code{ematrix} as in previous versions of
    \pkg{msm}.

    For example, \cr

     \code{
      ematrix = rbind(
    c( 0, 0.1, 0, 0 ),
    c( 0.1, 0, 0.1, 0 ),
    c( 0, 0.1, 0, 0),
    c( 0, 0, 0, 0)
    )
  }\cr

    is equivalent to \cr

    \code{hmodel = list(
    hmmCat(prob=c(0.9, 0.1, 0, 0)),
    hmmCat(prob=c(0.1, 0.8, 0.1, 0)),
    hmmCat(prob=c(0, 0.1, 0.9, 0)), hmmIdent())
    }\cr

  }

  \item{obstype}{A vector specifying the observation scheme for each row
    of the data. This can be included in the data frame \code{data}
    along with the  state, time, subject IDs and covariates.  Its
    elements should be either 1, 2 or 3, meaning as follows:
    
    \describe{
      \item{1}{An observation of the process at an arbitrary time (a "snapshot"
	of the process, or "panel-observed" data)}
      \item{2}{An exact transition time, with the state at the previous
	observation retained until the current observation.}
      \item{3}{An exact transition time, but the state at the instant before
	entering this state is unknown. A common example is death times in
	studies of chronic diseases.}    
    } 
    If \code{obstype} is not specified, this defaults to all 1. If
    \code{obstype} is a single number, all observations are assumed to
    be of this type. 

    This is a generalisation of the \code{death} and \code{exacttimes}
    arguments to allow different schemes per observation.
    
    \code{exacttimes=TRUE} specifies that all observations are of
    obstype 2.

    \code{death = death.states} specifies that all observations of
    \code{death.states} are of type 3.  \code{death =
      TRUE} specifies that all observations in the final absorbing state
    are of type 3. 
  }

  \item{obstrue}{A vector of logicals (\code{TRUE} or \code{FALSE}) or
  numerics (1 or 0) specifying which observations (\code{TRUE}, 1) are
  observations of the underlying state without error, and which
  (\code{FALSE}, 0) are realisations of a hidden Markov model. Only
  used in misclassification or hidden Markov models.

  In HMMs where there are also censored states, \code{obstrue} should be
  set to 1 for observed states which are \emph{censored} but not
  \emph{misclassified}.
  }
    
  \item{covariates}{Formula representing the covariates on the
  transition intensities via a log-linear model. For example,

    \code{~ age + sex + treatment}
    
  }
  
  \item{covinits}{Initial values for log-linear effects of covariates on the
    transition intensities. This should be a named list with each element
    corresponding to a covariate.  A single element contains the initial
    values for that covariate on each transition intensity, reading
    across the rows in order.  For a pair of effects constrained to be
    equal, the initial value for the first of the two effects is used. 
    
    For example, for a model with the above \code{qmatrix} and age and sex
    covariates, the following initialises all covariate effects to zero
    apart from the age effect on the 2-1 transition, and the sex
    effect on the 1-3 transition.  
    \code{ covinits = list(sex=c(0, 0, 0.1, 0), age=c(0, 0.1, 0, 0))}

    For factor covariates, name each level by concatenating the name of
    the covariate with the level name, quoting if necessary. For example,
    for a covariate  \code{agegroup} with three levels \code{0-15,
      15-60, 60-}, use something like

    \code{ covinits = list("agegroup15-60"=c(0, 0.1, 0, 0),
      "agegroup60-"=c(0.1, 0.1, 0, 0))}

    If not specified or wrongly specified, initial values are assumed
    to be zero. 
    }
  
    \item{constraint}{ A list of one numeric vector for each named covariate. The
  vector indicates which covariate effects on intensities are
  constrained to be equal. Take, for example, a model with five
  transition intensities and two covariates. Specifying\cr
    
    \code{constraint = list (age = c(1,1,1,2,2),  treatment = c(1,2,3,4,5))}\cr

    constrains the effect of age to be equal for the first three
    intensities, and equal for the fourth and fifth. The effect of
    treatment is assumed to be different for each intensity. Any vector of
    increasing numbers can be used as indicators. The intensity parameters are
    assumed to be ordered by reading across the rows of the
    transition matrix, starting at the first row, ignoring the
    diagonals.

    Negative elements of the vector can be used to indicate that particular
    covariate effects are constrained to be equal to minus some other
    effects.  For example:

    \code{constraint = list (age = c(-1,1,1,2,-2), treatment = c(1,2,3,4,5)) }\cr

    constrains the second and third age effects to be equal, the first effect
    to be minus the second, and the fifth age effect to be minus the
    fourth.  For example, it may be realisitic that the effect of a
    covariate on the "reverse" transition rate from state 2 to state 1
    is minus the effect on the "forward" transition rate, state 1 to state
    2.  Note that it is not possible to specify exactly which of the
    covariate effects are constrained to be positive and which negative.
    The maximum likelihood estimation chooses the combination of signs
    which has the higher likelihood.

    For categorical covariates, defined using \code{factor(covname)},
    specify constraints as follows:\cr

    \code{list(..., covnameVALUE1 = c(...), covnameVALUE2 = c(...), ...)}\cr
    
    where \code{covname} is the name of the factor, and \code{VALUE1},
    \code{VALUE2}, ... are the levels of the factor.
    Make sure the \code{contrasts} option is set appropriately, for
    example, the default

    \code{options(contrasts=c(contr.treatment, contr.poly))}

    sets the first (baseline) level of unordered factors to zero.

    To assume no covariate effect on a certain transition, set its
    initial value to zero and use the \code{fixedpars} argument to fix
    it during the optimisation.
    
  }

  \item{misccovariates}{A formula representing the covariates on the 
    misclassification probabilities, analogously to \code{covariates},
    via multinomial logistic regression. Only used if the model is
    specified using \code{ematrix}, rather than \code{hmodel}. 
  }

  \item{misccovinits}{Initial values for the covariates on the 
    misclassification probabilities, defined in the same way as \code{covinits}. 
    Only used if the model is specified using \code{ematrix}. 
  }

  \item{miscconstraint}{A list of one vector for each named covariate on
    misclassification probabilities. The vector indicates which
    covariate effects on misclassification probabilities are
    constrained to be equal, analogously to \code{constraint}.
    Only used if the model is specified using \code{ematrix}. 
  }

  \item{hcovariates}{
    List of formulae the same length as \code{hmodel}, defining any covariates
    governing the hidden Markov outcome models.  The covariates operate
    on a suitably link-transformed linear scale, for example, log scale
    for a Poisson outcome model. If there are no covariates for a certain
    hidden state, then insert a NULL in the corresponding place in the
    list.  For example, 
    \code{hcovariates = list(~acute + age, ~acute, NULL).}
    }

  \item{hcovinits}{
    Initial values for the hidden Markov model covariate effects. A list of the
    same length as \code{hcovariates}. Each element is a vector with
    initial values for the effect of each covariate on that state.  For example, the
    above \code{hcovariates} can be initialised with 
    \code{hcovariates = list(c(-8, 0), -8, NULL)}. Initial values must
    be given for all or no covariates, if none are given these are all
    set to zero.  The initial value given in the \code{hmodel}
    constructor function for the corresponding baseline parameter is
    interpreted as the value of that parameter with any covariates fixed
    to their means in the data.  If multiple effects are constrained
    to be equal using \code{hconstraint}, then the
    initial value is taken from the first of the multiple initial values
    supplied. 
    }

  \item{hconstraint}{
    A named list. Each element is a vector of constraints on the named hidden
    Markov model parameter. The vector has length equal to the number of
    times that class of parameter appears in the whole model. 

    For example consider the three-state hidden Markov model described
    above, with normally-distributed outcomes for states 1 and 2. 
    To constrain the outcome variance to be equal for states 1 and 2,
    and to also constrain the effect of \code{acute} on the outcome mean
    to be equal for states 1 and 2, specify

    \code{hconstraint = list(sd = c(1,1), acute=c(1,1))}    
    }

  \item{qconstraint}{A vector of indicators specifying which baseline
    transition intensities are equal. For example,
    
    \code{qconstraint = c(1,2,3,3)}

    constrains the third and fourth intensities to be equal, in a model
    with four allowed instantaneous transitions.   When there are
    covariates on the intensities and \code{center=TRUE} (the default),
    \code{qconstraint} is applied to the intensities with covariates
    taking the values of the means in the data.  When \code{center=FALSE},
    \code{qconstraint} is applied to the intensities with covariates set
    to zero. 
  }

  \item{econstraint}{A similar vector of indicators specifying which
    baseline misclassification probabilities are constrained to be
    equal.      Only used if the model is specified using \code{ematrix}, rather
    than \code{hmodel}.  }
  
  \item{initprobs}{Currently only used in hidden Markov models.
    Vector of assumed underlying state occupancy probabilities at each
    individual's first observation. If these are estimated (see
    \code{est.initprobs}), then this defaults to equal probability for
    each state.  Otherwise this defaults to
    \code{c(1, rep(0, nstates-1))}, that is, in state 1 with a
    probability of 1.  Scaled to sum to 1 if necessary.  The state 1
    occupancy probability should be non-zero. 
  }

  \item{est.initprobs}{If \code{TRUE}, then the underlying state
    occupancy probabilities at the first observation will be estimated,
    starting from initial values taken from the \code{initprobs}
    argument.  Structural zeroes are allowed: if any of these initial
    values are zero they will be fixed at zero during optimisation, and
    no covariate effects on them are estimated.  The exception is 
    state 1, which should have non-zero occupancy probability.

    Be warned that if any of these initial values are 1,
    then \code{\link{optim}} will give an "non-finite value" error,
    since these are logit-transformed during estimation.  If you wish to
    fix any initial probabilities to 1, then that implies all the others are
    fixed to zero, and there is no need to use \code{est.initprobs} at
    all.

    Note that the free parameters during this estimation exclude the state 1
    occupancy probability, which is fixed at one minus the sum of the
    other probabilities.
  }

  \item{initcovariates}{ Formula representing covariates on the initial
    state occupancy probabilities, via multinomial logistic regression.  The
    linear effects of these covariates, observed at the individual's first
    observation time, operate on the log ratio of the state \eqn{r}
    occupancy probability to the state 1 occupancy probability, for each 
    \eqn{r = 2} to the number of states.  Thus the state 1 occupancy
    probability should be non-zero. If \code{est.initprobs} is
    \code{TRUE}, these effects are estimated starting from their initial
    values.  If \code{est.initprobs} is \code{FALSE}, these effects are fixed at
    theit initial values.}

  \item{initcovinits}{ Initial values for the covariate effects
    \code{initcovariates}.  A named list with each element corresponding
    to a covariate, as in \code{covinits}. Each element is a vector with
    (1 - number of states) elements, containing the initial values for
    the linear effect of that covariate on the log odds of that state
    relative to state 1, from state 2 to the final state.  If
    \code{initcovinits} is not specified, all covariate effects are
    initialised to zero.}

  \item{death}{Vector of indices of exactly-observed "death" states.
    These are absorbing states whose time of entry is known exactly, but the
    individual is assumed to be in an unknown transient state ("alive")
    at the previous instant.  This is the usual situation for times of death in
    chronic disease monitoring data.  For example, if you specify
    \code{death = c(4, 5)} then states 4 and 5 are assumed to be
    exactly-observed death states.

    \code{death = TRUE} indicates that the final state is a death state,
    and \code{death = FALSE} (the default) indicates that there is no
    death state. See the \code{obstype} argument.  
  }

  \item{censor}{ A state, or vector of states, which indicates
    censoring.  Censoring means that the observed state is known only to be
    one of a particular set of states. For example, \code{censor=999}
    indicates that all observations of \code{999} in the vector of observed
    states denote censoring times.  By default, this means that the true
    state could have been anything other than an absorbing state. To
    specify corresponding true states explicitly, use a \code{censor.states}
    argument. 

    Note that in contrast to the usual terminology of survival
    analysis, here it is the \emph{state} which is considered to be censored,
    rather than the \emph{event time}.  If at the end of a study, an individual
    has not died, but their true state is \emph{known}, then \code{censor} is
    unnecessary, since the standard multi-state model likelihood is
    applicable. 
    
    Note in particular that general time-inhomogenous Markov models with
    piecewise constant transition
    intensities can be constructed using the \code{censor}
    facility. If the true state is unknown on occasions when a
    piecewise constant covariate is known to change, then censored
    states can be inserted in the data on those occasions.
    The covariate may represent time itself, or some other
    time-dependent variable.  The \code{pci} option to msm can be used
    to perform this trick automatically.
  }

  \item{censor.states}{
    Specifies the underlying states which censored observations can
    represent. If \code{censor} is a single number (the default) this
    can be a vector, or a list with one element.  If \code{censor} is a
    vector with more than one element, this should be a list, with each
    element a vector corresponding to the equivalent element of
    \code{censor}.  For example

    \code{censor = c(99, 999), censor.states = list(c(2,3), c(3,4))}
    
    means that observations coded 99 represent either state 2 or state
    3, while observations coded 999 are really either state 3 or
    state 4. 
  }

  \item{pci}{Model for piecewise-constant intensities.  Vector of cut
     points defining the times, since the start of the process, at 
     which intensities change.  For example 

     \code{pci = c(5, 10)} 

     specifies that the intensity changes at time points 5 and 10.
     This will automatically construct a model with a categorical
     (factor) covariate called \code{timeperiod}, with levels \code{"timeperiod[-Inf,5)"},
     \code{"timeperiod[5,10)"} and \code{"timeperiod[10,Inf)"}, where
     the first
     level is the baseline.  This covariate defines the time period in
     which the observation was made.  Initial values and
     constraints on covariate effects are specified the same way as for
     a model with a covariate of this name, for example,

     \code{covinits = list("timeperiod[5,10)"=c(0.1,0.1),
                           "timeperiod[10,Inf)"=c(0.1,0.1))}

     Internally, this works by inserting censored observations in the
     data at times when the intensity changes but the state is not
     observed.  

     If the supplied times are outside the range of the time variable in
     the data, \code{pci} is ignored and a time-homogeneous model is
     fitted.

     After fitting a time-inhomogeneous model \code{\link{qmatrix.msm}}
     can be used to obtain the fitted intensity matrices for each time
     period, for example,

     \code{qmatrix.msm(example.msm, covariates=list(timeperiod="[5,Inf)"))}
     
     This facility does not support interactions between time and
     other covariates.  Such models need to be specified by hand, using 
     a state variable with censored observations inserted.
     Note that the \code{data} component of the \code{msm} object
     returned from a call to \code{msm} with \code{pci} supplied contains the
     states with inserted censored observations and time period
     indicators.  These can be used to construct such models.

     }

  \item{exacttimes}{By default, the transitions of the Markov process
    are assumed to take place at unknown occasions in between the
    observation times.  If \code{exacttimes} is
    set to \code{TRUE}, then all observation times are assumed to
    represent the exact and complete times of transition of the process.
    This is equivalent to every row of the data having \code{obstype =
    2}.  See the \code{obstype} argument.
  }

  \item{cl}{Width of symmetric confidence intervals for maximum
    likelihood estimates, by default 0.95.}
  
  \item{fixedpars}{Vector of indices of parameters whose values will be
    fixed at their initial values during the optimisation. These are
    given in the order: transition intensities (reading across rows of
    the transition matrix), covariates on intensities (ordered by
    intensities within covariates), hidden Markov model parameters
    (ordered by parameters within states), hidden Markov model covariate
    parameters (ordered by covariates within parameters within states),
    initial state occupancy probabilities (excluding the first
    probability, which is fixed at one minus the sum of the others).

    If there are equality constraints on certain parameters, then    
    \code{fixedpars} refers to the set of unique parameters, excluding
    those which are constrained to be equal to previous parameters. 
    
    For covariates on misclassification probabilities, this is a change
    from version 0.4 in the parameter ordering. Previously these were
    ordered by misclassification probabilities within covariates. 
    
    This can be useful for profiling likelihoods, and building complex
    models stage by stage. To fix all parameters, specify
    \code{fixedpars = TRUE}. }

  \item{center}{If \code{TRUE} (the default) then covariates are centered at
    their means during the maximum likelihood estimation. This usually
    improves stability of the numerical optimisation. }

  \item{opt.method}{Quoted name of the R function to perform
    minimisation of the minus twice log likelihood.  Either "optim" or
    "nlm". \code{\link{optim}} is the default. }

  \item{hessian}{If \code{TRUE} (the default) then the Hessian matrix is
    computed at the maximum likelihood estimates, to obtain standard
    errors and confidence intervals.}

  \item{use.deriv}{If \code{TRUE} then analytic first derivatives are
    used in the optimisation of the likelihood, when an appropriate
    quasi-Newton optimisation method, such as BFGS, is being used.  Note
    that the default for \code{\link{optim}} is a Nelder-Mead method
    which cannot use derivatives. However, these derivatives, if
    supplied, are always used to calculate the Hessian. }

  \item{analyticp}{By default, the likelihood for certain simpler 3, 4
    and 5 state models is calculated using an analytic expression for
    the transition probability (P) matrix.  To revert to the original method
    of using the matrix exponential, specify \code{analyticp=FALSE}. See
    the PDF manual for a list of the models for which analytic P
    matrices are implemented. }
  
  \item{...}{Optional arguments to the general-purpose \R
    optimisation routines, \code{\link{optim}} or
    \code{\link{nlm}}. Useful options for \code{\link{optim}} include
    \code{method="BFGS"} for using a quasi-Newton optimisation
    algorithm, which can often be faster than the default Nelder-Mead.
    If the optimisation fails to converge, consider normalising the
    problem using, for example, \code{control=list(fnscale = 2500)}, for
    example, replacing 2500 by a number of the order of magnitude of the
    likelihood. If 'false' convergence is reported and the standard
    errors cannot be calculated due to a non-positive-definite Hessian,
    then consider tightening the tolerance criteria for convergence. If
    the optimisation takes a long time, intermediate steps can be
    printed using the \code{trace} argument of the control list. See
    \code{\link{optim}} for details.
  }
}
\value{
  A list of class \code{msm}, with components:

  \item{call}{The original call to \code{msm}.}
    \item{Qmatrices}{A list of matrices. The first component, labelled
    \code{logbaseline}, is a matrix containing the estimated
    transition intensities on the log scale with any covariates fixed at
    their means in the data. Each remaining component is a matrix giving the linear
    effects of the labelled covariate on the matrix of log
    intensities.  To extract an estimated intensity matrix on the natural
    scale, at an arbitrary combination of covariate values, use the
    function \code{\link{qmatrix.msm}}.
  }
  \item{QmatricesSE}{The standard error matrices corresponding to
    \code{Qmatrices}.
  }
  \item{QmatricesL,QmatricesU}{Corresponding lower and upper symmetric
    confidence limits, of width 0.95 unless specified otherwise by the
    \code{cl} argument.
  }
  \item{Ematrices}{A list of matrices. The first component, labelled
    \code{logitbaseline}, is the estimated misclassification probability
    matrix (expressed as as log odds relative to the probability of the
    true state) with any covariates fixed at their means in the data. Each
    remaining component is a matrix giving the linear
    effects of the labelled covariate on the matrix of logit
    misclassification probabilities.   To extract an estimated misclassification
    probability matrix on the natural scale, at an arbitrary combination
    of covariate values, use the function \code{\link{ematrix.msm}}.}
  \item{EmatricesSE}{The standard error matrices corresponding to \code{Ematrices}.}
  \item{EmatricesL,EmatricesU}{Corresponding lower and upper symmetric
    confidence limits, of width 0.95 unless specified otherwise by the
    \code{cl} argument.
  }
  \item{sojourn}{
    A list with components:

    \code{mean} = estimated mean sojourn times in the transient states,
    with covariates fixed at their means.

    \code{se} = corresponding standard errors.
  }
  \item{minus2loglik}{Minus twice the maximised log-likelihood.}
  \item{deriv}{Derivatives of the minus twice log-likelihood at its maximum.}
  \item{estimates}{Vector of untransformed maximum likelihood estimates
    returned from \code{\link{optim}}.  Transition intensities are on
    the log scale and misclassification probabilities are given as log
    odds relative to the probability of the true state.}
  \item{estimates.t}{Vector of transformed maximum likelihood estimates
    with intensities and probabilities on their natural scales.}
  \item{fixedpars}{Indices of \code{estimates} which were fixed during
    the maximum likelihood estimation.}
  \item{center}{Indicator for whether the estimation was performed with
    covariates centered on their means in the data.}
  \item{covmat}{Covariance matrix corresponding to \code{estimates}.}
  \item{ci}{Matrix of confidence intervals corresponding to \code{estimates.t}}
  \item{opt}{Return value from \code{\link{optim}} or \code{\link{nlm}},
    giving information about the results of the optimisation.}
  \item{foundse}{Logical value indicating whether the Hessian was positive-definite
    at the supposed maximum of the likelihood.  If not, the covariance matrix of the
    parameters is unavailable. In these cases the optimisation has
    probably not converged to a maximum.
  }
  \item{data}{A list of constants and vectors giving the data, for use
    in post-processing.}
  \item{qmodel}{A list of objects specifying the
    model for transition intensities, for use in post-processing.}
  \item{emodel}{A list of objects specifying the model for
    misclassification.}
  \item{qcmodel}{A list of objects specifying the
    model for covariates on the transition intensities.}
  \item{ecmodel}{A list of objects specifying the model for
    covariates on misclassification probabilities.}
  \item{hmodel}{A list of class "hmodel", containing objects specifying the hidden Markov model.
    Estimates of "baseline" location parameters are
    presented with any covariates fixed to their means in the data.  }  
  \item{cmodel}{A list of objects specifying any model for censoring.}

  Printing a \code{msm} object by typing the object's name at the
  command line implicitly invokes \code{print.msm}.  This
  formats and prints the important information in the model fit.
  This includes the fitted transition intensity matrix, matrices
  containing covariate effects on intensities, and mean sojourn times
  from a fitted \code{\link{msm}} model.  When there is a hidden Markov
  model, the chief information in the
  \code{hmodel} component is also formatted and printed. This includes
  estimates and confidence intervals for each
  parameter.

  To extract summary information from the fitted model, it is
  recommended to use the more flexible extractor functions, such as
  \code{\link{qmatrix.msm}}, \code{\link{pmatrix.msm}},
  \code{\link{sojourn.msm}}, instead of directly reading from list
  components of \code{msm} objects.
  
}
\details{
  For full details about the methodology behind the \pkg{msm} package,
  refer to the PDF manual \file{msm-manual.pdf} in the \file{doc}
  subdirectory of the package. This includes a tutorial in the typical
  use of \pkg{msm}.

  Note that \pkg{msm} is for fitting \emph{continuous-time} Markov
  models, processes where transitions can occur at any time.
  These models are defined by \emph{intensities}, which govern both the
  time spent in the current state and the probabilities of the next
  state.  In \emph{discrete-time models}, transitions are known in
  advance to only occur at multiples of some time unit, and the model is
  purely governed by the probability distributions of the state at the
  next time point, conditionally on the state at the current time. These
  are more appropriately fitted using multinomial logistic regression,
  for example, using \code{multinom} from the
  R package \pkg{nnet} (Venables and Ripley, 2002).

  For simple continuous-time multi-state Markov models,
  the likelihood is calculated in terms of the transition intensity
  matrix \eqn{Q}. When the data consist of observations of the Markov
  process at arbitrary times, the exact transition times are not known.
  Then the likelihood is calculated using the transition probability
  matrix \eqn{P(t) = \exp(tQ)}{P(t) = exp(tQ)}, where \eqn{\exp}{exp} is
  the matrix exponential.  If state \eqn{i} is observed at time
  \eqn{t} and  state \eqn{j} is observed at time \eqn{u}, then the
  contribution to the likelihood from this pair of observations is
  the \eqn{i,j} element of \eqn{P(u - t)}. See, for example, Kalbfleisch
  and Lawless (1985), Kay (1986), or Gentleman \emph{et al.} (1994).

  For hidden Markov models, the likelihood for an individual
  with \eqn{k} observations is calculated directly by summing over the
  unknown state at each time,  producing a product of \eqn{k} matrices. The
  calculation is a generalisation of the method described by Satten and
  Longini (1996), and also by Jackson and Sharples (2002), and Jackson
  \emph{et al.} (2003).

  There must be enough information in the data on each state to estimate
  each transition rate, otherwise the likelihood will be flat and the
  maximum will not be found.  It may be appropriate to reduce the
  number of states in the model, the number of allowed transitions, or
  the number of covariate effects, to ensure convergence.   Hidden
  Markov models, and situations where the value of the process is only
  known at a series of snapshots, are particularly susceptible to
  non-identifiability, especially when combined with a complex
  transition matrix. 

  Choosing an appropriate set of initial values for the optimisation can
  also be important.  For flat likelihoods, 'informative' initial values
  will often be required.
  
  Users upgrading from versions of \pkg{msm} less than 0.5 will need to
  change some of their model fitting syntax. In particular, initial
  values are now specified in the \code{qmatrix} and \code{covinits}
  arguments instead of \code{inits}, and \code{qmatrix} is no longer a
  matrix of \code{0/1} indicators.  See the appendix to the PDF manual
  or the NEWS file in the top-level installation directory for a full
  list of changes.

}
\references{
  Kalbfleisch, J., Lawless, J.F., The analysis of panel data under a
  Markov assumption \emph{Journal of the Americal Statistical
    Association} (1985) 80(392): 863--871.
    
  Kay, R.  A Markov model for analysing cancer markers and disease
  states in survival studies.  \emph{Biometrics} (1986) 42: 855--865.
  
  Gentleman, R.C., Lawless, J.F., Lindsey, J.C. and Yan, P.  Multi-state
  Markov models for analysing incomplete disease history data with
  illustrations for HIV disease.  \emph{Statistics in Medicine} (1994) 13(3):
  805--821.
  
  Satten, G.A. and Longini, I.M.  Markov chains with measurement error:
  estimating the 'true' course of a marker of the progression of human
  immunodeficiency virus disease (with discussion) \emph{Applied
    Statistics} 45(3): 275-309 (1996)
    
  Jackson, C.H. and Sharples, L.D. Hidden Markov models for the
  onset and progression of bronchiolitis obliterans syndrome in lung
  transplant recipients \emph{Statistics in Medicine}, 21(1): 113--128
  (2002).

  Jackson, C.H., Sharples, L.D., Thompson, S.G. and Duffy, S.W. and
  Couto, E.  Multi-state Markov models for disease progression with
  classification error. \emph{The Statistician}, 52(2): 193--209 (2003)

  Venables, W.N. and Ripley, B.D. (2002) \emph{Modern Applied Statistics with
    S}, second edition. Springer.
}

\seealso{
  \code{\link{simmulti.msm}}, \code{\link{plot.msm}},
  \code{\link{summary.msm}}, \code{\link{qmatrix.msm}},
  \code{\link{pmatrix.msm}},  \code{\link{sojourn.msm}}. 
}
\examples{
### Heart transplant data
### For further details and background to this example, see
### the PDF manual in the doc directory. 
data(cav)
print(cav[1:10,])
twoway4.q <- rbind(c(-0.5, 0.25, 0, 0.25), c(0.166, -0.498, 0.166, 0.166),
c(0, 0.25, -0.5, 0.25), c(0, 0, 0, 0))
statetable.msm(state, PTNUM, data=cav)
crudeinits.msm(state ~ years, PTNUM, data=cav, qmatrix=twoway4.q)
cav.msm <- msm( state ~ years, subject=PTNUM, data = cav, 
                 qmatrix = twoway4.q, death = 4,
                 control = list ( trace = 2, REPORT = 1 )  )
cav.msm
qmatrix.msm(cav.msm)
pmatrix.msm(cav.msm, t=10)
sojourn.msm(cav.msm)
}
\author{C. H. Jackson \email{chris.jackson@mrc-bsu.cam.ac.uk}}
\keyword{models}
