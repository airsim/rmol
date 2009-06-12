/* *****************************************************************
   PROGRAM: lik.c 
   AUTHOR:  Chris Jackson
   DATE:    July 2004

   Routines for calculating likelihoods for multi-state Markov and
   hidden Markov models.

   ******************************************************************  */ 

#include "msm.h"
#include "hmm.h"
#include <Rmath.h>
#define NODEBUG
#define NOVITDEBUG

linkfn LINKFNS[3][2] = {
    {identity, identity},
    {log, exp},
    {logit, expit}
};

/* MUST KEEP THIS IN SAME ORDER AS .msm.HMODELPARS IN R/constants.R */
hmmfn HMODELS[] = {
    hmmCat,
    hmmIdent,
    hmmUnif,
    hmmNorm,
    hmmLNorm,
    hmmExp,
    hmmGamma,
    hmmWeibull,
    hmmPois,
    hmmBinom,
    hmmTNorm,
    hmmMETNorm,
    hmmMEUnif,
    hmmNBinom,
    hmmBeta
};

#define OBS_SNAPSHOT 1 
#define OBS_EXACT 2
#define OBS_DEATH 3

double logit(double x)
{
    return log(x / (1 - x));
}

double expit(double x)
{
    return exp(x) / ( 1 + exp(x) );
}

double identity(double x)
{
    return x;
}

/* Good-enough floating point equality comparison */

int all_equal(double x, double y) 
{
    return fabs (x - y) <= DBL_EPSILON * fabs(x);
}

/* 
   Add effects of covariates at an observation number obs to a set of link-transformed parameters
   For covs on the qmatrix, we have npars q's, each with the same number of covs on them
   For HMMs, each set is the set of parameters of the model for one state
   Only certain of these parameters (means and rates) can have
   covariates on them, ncovs[i] > 0
   whichcov[j] is the column of the (vectorised) data matrix "cov" containing the jth covariate
   totcovs is a call-by-referenced integer which counts the covariates so far, used for indexing whichcov
   coveffect is a vectorised ncovs * npars matrix, filled by rows
   (par1) cov1 cov2 ..  (par2) cov1 cov2
*/ 

void AddCovs(int obs, int nobs, int npars, int *ncovs, 
	     double *oldpars, double *newpars, 
	     double *coveffect, double *cov, int *whichcov, 
	     int *totcovs,
	     double link(double x), double invlink(double x))
{
    int i, j, k=0;
    double x;
    for (i = 0; i < npars; ++i)
	{
	    newpars[i] = oldpars[i];
	    if (ncovs[i] > 0) { 
		newpars[i] = link(newpars[i]);
		for (j = 0; j < ncovs[i]; ++j) {
			x =  cov[MI(obs, whichcov[j]-1, nobs)];
			newpars[i] += coveffect[k] * x;
			++k;
		}
		newpars[i] = invlink(newpars[i]);
		*totcovs += ncovs[i];
	    }
	}
}

void GetCovData(int obs, double *allcovs, int *whichcov, double *thiscov, int ncovs, int nobs)
{
    int i;
    for (i=0; i<ncovs; ++i)
	thiscov[i] = allcovs[MI(obs, whichcov[i]-1, nobs)];
}

/* Return a vector of the nc possible true states that a censored state could represent */ 
/* These will be summed over when calculating the likelihood */
/* Compare one-indexed obs against one-indexed cm->censor. Return one-indexed current (*states) */

void GetCensored (double obs, cmodel *cm, int *nc, double **states) 
{
    int j, k=0, n, cens=0;
    if (cm->ncens == 0)
	n = 1;
    else {
	while (!all_equal(obs, cm->censor[k]) && k < cm->ncens)
	    ++k;
	if (k < cm->ncens) { 
	    cens = 1; 
	    n =  cm->censstind[k+1] - cm->censstind[k];
	}
	else n = 1;
    } 
    if (cm->ncens == 0 || !cens)
	(*states)[0] = obs;
    else { for (j = cm->censstind[k]; j < cm->censstind[k+1]; ++j)
	(*states)[j - cm->censstind[k]] = cm->censstates[j]; }
    *nc = n;    
}

/*
  Calculate p (obs curr | true i) for hidden Markov models 
  If observation is not necessarily of the true state (!obstrue), 
  then this is just the HMM outcome probability (summed over censor set if necessary) 
  If obstrue, this observation is not misclassified. 
  e.g. censor set 1,2,3,    state set 1,2,3,4, 
  pout =   if i in curr 1, else 0 
*/

void GetOutcomeProb(double *pout, double *curr, int nc, double *newpars, hmodel *hm, qmodel *qm, int obstrue)
{
    int i, j;
    for (i=0; i<qm->nst; ++i) {
	pout[i] = 0;
	if (!obstrue) {
	    for (j=0; j<nc; ++j)
		pout[i] += (HMODELS[hm->models[i]])(curr[j], &(newpars[hm->firstpar[i]]));
	}
	else { 
	    for (j=0; j<nc; ++j) 
		if ((int) curr[j] == i+1) 
		    pout[i] = 1;
	}
    }
}

void normalize(double *in, double *out, int n, double *lweight)
{
    int i; double ave;
    for (i=0, ave=0; i<n; ++i)
	ave += in[i];
    ave /= n;
    if (ave == 0) ave = 1;   
    for (i=0; i<n; ++i)
	out[i] = in[i] / ave;
    *lweight -= log(ave);
}

/* Transform relative probabilities p2/p1, p3/p1, ... pn/p1 to 
   absolute probabilities p1,p2,...,pn.  
   element "baseline" of relative (usually first element 0) can be anything on entry. */

void relative2absolutep(double *relative, double *absolute, int n, int baseline)
{
    int i; double psum=0;
    for (i = 0; i < n; ++i)
	if (i != baseline) 
	    psum += relative[i];
    for (i = 0; i < n; ++i)
	absolute[i] = (i==baseline ? 1 : relative[i]) / (1 + psum);
}

/* Post-multiply the row-vector cump by matrix T to accumulate the likelihood */

void update_likhidden(double *curr, int nc, int obsno, msmdata *d, qmodel *qm, qcmodel *qcm, 
		      hmodel *hm, double *cump, double *newp, double *lweight)
{
    int i, j, fp, totcovs=0, ideath;
    double *pout = Calloc(qm->nst, double); 
    double *T           = Calloc((qm->nst)*(qm->nst), double);
    double *newintens   = Calloc(qm->npars, double);
    double *pmat        = Calloc((qm->nst)*(qm->nst), double);
    double *newpars = Calloc(hm->totpars, double);
    AddCovs(obsno-1, d->nobs, qm->npars, qcm->ncovs, qm->intens, newintens,
	    qcm->coveffect, d->cov, d->whichcov, &totcovs, log, exp); 	
    totcovs = 0;
    for (i = 0; i < qm->nst; ++i) {
	fp = hm->firstpar[i]; /* index into concatenated vector of parameters */
	AddCovs(obsno, d->nobs, hm->npars[i], &(hm->ncovs[fp]), &(hm->pars[fp]), 
		&(newpars[fp]), &(hm->coveffect[totcovs]), d->cov, 
		&(d->whichcovh[totcovs]), &totcovs,
		LINKFNS[hm->links[i]][0], LINKFNS[hm->links[i]][1]);
    }
    GetOutcomeProb(pout, curr, nc, newpars, hm, qm, d->obstrue[obsno]);
/*     printf("pout: %4.3f, %4.3f, %4.3f, %4.3f\n", pout[0], pout[1], pout[2], pout[3]);   */
    /* calculate the transition probability (P) matrix for the time interval dt */
    Pmat(pmat, d->time[obsno] - d->time[obsno-1], newintens, qm->npars, qm->ivector, qm->nst,
	 (d->obstype[obsno] == OBS_EXACT), qm->analyticp, qm->iso, qm->perm, qm->qperm, 0);
    for(j = 0; j < qm->nst; ++j)
	{
	    newp[j] = 0.0;
	    for(i = 0; i < qm->nst; ++i)
		{
 		    if (d->obstype[obsno] == OBS_DEATH) {
			/* Find the true state that obs represents.  This should be the state with outcome model hmmIdent(obs) */
 			if (d->obstrue[obsno])  
 			    ideath = curr[0] - 1;  
 			else 
			    for (ideath=0; ideath < qm->nst; ++ideath)
				if (hm->models[ideath] == 1 && hmmIdent(curr[0], &(newpars[hm->firstpar[ideath]])))
				    break;
			T[MI(i,j,qm->nst)] = pmat[MI(i,j,qm->nst)] * qij(j, ideath, newintens, qm->ivector, qm->nst);
		    }
		    else {
			T[MI(i,j,qm->nst)] = pmat[MI(i, j, qm->nst)] * pout[j];
		    }
		    if (T[MI(i,j,qm->nst)] < 0) T[MI(i,j,qm->nst)] = 0;
		    newp[j] = newp[j] + cump[i]*T[MI(i,j,qm->nst)];
/*   		    printf("%4.3f, ", pmat[MI(i,j,qm->nst)]);   */
		}
/*   	    printf("\n");   */
			
	}
    /* re-scale the likelihood at each step to prevent it getting too small and underflowing */
    /*  while cumulatively recording the log scale factor   */
    normalize (newp, cump, qm->nst, lweight);
    Free(pout); Free(T); Free(newintens); Free(pmat); Free(newpars); 
}

/* Likelihood for the hidden Markov model for one individual */

double likhidden(int pt, /* ordinal subject ID */
		 msmdata *d, qmodel *qm, qcmodel *qcm, 
		 cmodel *cm, hmodel *hm
		 )
{
    double *curr = Calloc (qm->nst, double);
    /* no more than nst states allowed */
    double *cump     = Calloc(qm->nst, double); 
    double *newp     = Calloc(qm->nst, double);  
    double *pout = Calloc(qm->nst, double); 
    double *newpars = Calloc(hm->totpars, double);
    double *newinitp = Calloc(qm->nst, double);
    double lweight, lik; 
    int i, fp, totcovs=0, obsno, nc=1;
    if (d->firstobs[pt] + 1 == d->firstobs[pt+1]) 
      return 0; /* individual has only one observation */ 
    /* Likelihood for individual's first observation */
    for (i = 0; i < qm->nst; ++i) {
	fp = hm->firstpar[i];
	AddCovs(d->firstobs[pt], d->nobs, hm->npars[i], &(hm->ncovs[fp]), &(hm->pars[fp]), 
		&(newpars[fp]), &(hm->coveffect[totcovs]), d->cov, &(d->whichcovh[totcovs]),
		&totcovs, LINKFNS[hm->links[i]][0], LINKFNS[hm->links[i]][1]);
    }
    GetCensored((double)d->obs[d->firstobs[pt]], cm, &nc, &curr);
    GetOutcomeProb(pout, curr, nc, newpars, hm, qm, d->obstrue[d->firstobs[pt]]);
    /* Add covariate effects on initp (expressed as p(cat) / p(baseline cat)) */
    AddCovs(d->firstobs[pt], d->nobs, qm->nst - 1, hm->nicovs, &hm->initp[1], &newinitp[1], 
	    hm->icoveffect, d->cov, d->whichcovi, &totcovs, log, exp);
    /* Transform initp from probs relative to state 1 prob back to absolute probs */
    relative2absolutep(newinitp, newinitp, qm->nst, 0);
    /* Likelihood contribution for initial observation */
    for (i = 0; i < qm->nst; ++i) {
      /* Ignore initprobs if observation is known to be the true state  */
      if (d->obstrue[d->firstobs[pt]]) newinitp[i] = 1; 
      cump[i] = pout[i] * newinitp[i];
    }
    lweight=0;
    /* Matrix product loop to accumulate the likelihood for subsequent observations */
    for (obsno = d->firstobs[pt]+1; obsno <= d->firstobs[pt+1] - 1; ++obsno)
	{
	    R_CheckUserInterrupt();
	    GetCensored((double)d->obs[obsno], cm, &nc, &curr);
	    update_likhidden(curr, nc, obsno, d, qm, qcm, hm, cump, newp, &lweight);
	}
    for (i = 0, lik = 0; i < qm->nst; ++i)
	lik = lik + cump[i];
    Free(curr); Free(cump);  Free(newp); Free(pout); Free(newpars); Free(newinitp);
    /* Transform the likelihood back to the proper scale */
    return -2*(log(lik) - lweight); 
}


void update_likcensor(int obsno, double *prev, double *curr, int np, int nc, 
			msmdata *d, qmodel *qm, qcmodel *qcm, hmodel *hm, 
			double *cump, double *newp, double *lweight)
{
    double *newintens   = Calloc(qm->npars, double);
    double *pmat        = Calloc((qm->nst)*(qm->nst), double);
    double contrib;
    int i, j, k, totcovs = 0;
    AddCovs(obsno-1, d->nobs, qm->npars, qcm->ncovs, qm->intens, newintens,
	    qcm->coveffect, d->cov, d->whichcov, &totcovs, log, exp); 	
    Pmat(pmat, d->time[obsno] - d->time[obsno-1], newintens, qm->npars, qm->ivector, qm->nst,
	 (d->obstype[obsno] == OBS_EXACT), qm->analyticp, qm->iso, qm->perm,  qm->qperm, 0);
    for(i = 0; i < nc; ++i)
	{
	    newp[i] = 0.0;
	    for(j = 0; j < np; ++j) {
		if (d->obstype[obsno] == OBS_DEATH) {
		    contrib = 0;
		    for (k = 0; k < qm->nst; ++k)
			if (k != curr[i]-1)
			    contrib += pmat[MI((int) prev[j]-1, k, qm->nst)] * 
				qij(k, (int) curr[i]-1, newintens, qm->ivector, qm->nst);
		    newp[i] += cump[j] * contrib;
		    
		}
		else {
		    newp[i] += cump[j] * pmat[MI((int) prev[j]-1, (int) curr[i]-1, qm->nst)];
		}
	    }
	}
    normalize(newp, cump, nc, lweight); 
    Free(pmat); Free(newintens);  
}

double likcensor(int pt, /* ordinal subject ID */
		 msmdata *d, qmodel *qm, qcmodel *qcm, 
		 cmodel *cm, hmodel *hm
		 )
{
    double *cump     = Calloc(qm->nst, double);
    double *newp     = Calloc(qm->nst, double);  
    double *prev     = Calloc(qm->nst, double);  
    double *curr     = Calloc(qm->nst, double);  
    double lweight = 0, lik;
    int i, obs, np=0, nc=0;
    if (d->firstobs[pt] + 1 == d->firstobs[pt+1]) 
      return 0; /* individual has only one observation */ 
    for (i = 0; i < qm->nst; ++i)
	cump[i] = 1; 
    GetCensored((double)d->obs[d->firstobs[pt]], cm, &np, &prev);
    for (obs = d->firstobs[pt]+1; obs <= d->firstobs[pt+1] - 1; ++obs)
	{
	    /* post-multiply by sub-matrix of P at each obs */
	    GetCensored((double)d->obs[obs], cm, &nc, &curr);
	    update_likcensor(obs, prev, curr, np, nc, d, qm, qcm, hm, 
			     cump, newp, &lweight);
	    np = nc; 
	    for (i=0; i<nc; ++i) prev[i] = curr[i];
	}
    for (i = 0, lik = 0; i < nc; ++i)
	lik = lik + cump[i];
    Free(cump);  Free(newp);  Free(prev); Free(curr);
    return -2*(log(lik) - lweight); 
}

/* Likelihood for the non-hidden multi-state Markov model. Data of
   form "time-difference, covariates, from-state, to-state, number of
   occurrences" */

double liksimple(msmdata *d, qmodel *qm, qcmodel *qcm, 
		 cmodel *cm, hmodel *hm)
{
    int i,totcovs=0;
    double lik=0, contrib=0;
    double *pmat        = Calloc((qm->nst)*(qm->nst), double);
    double *newintens = Calloc ( qm->npars , double);
#ifdef DEBUG
    int j;
#endif
    for (i=0; i < d->nobs; ++i)
	{
	    R_CheckUserInterrupt();
	    if ((i==0) || (d->whicha[i] != d->whicha[i-1]) || (d->obstype[i] != d->obstype[i-1])) {
		/* we have a new timelag/covariates/obstype combination. Recalculate the 
		   P matrix for this */
		AddCovs(i, d->nobs, qm->npars, qcm->ncovs, qm->intens, newintens,
			qcm->coveffect, d->cov, d->whichcov, &totcovs,
			log, exp);
		Pmat(pmat, d->timelag[i], newintens, qm->npars, qm->ivector, qm->nst, (d->obstype[i] == OBS_EXACT), qm->analyticp, qm->iso, qm->perm,  qm->qperm, i==37);
	    }
	    if (d->obstype[i] == OBS_DEATH)
		contrib = pijdeath(d->fromstate[i], d->tostate[i], pmat, newintens, qm->ivector, qm->nst);
	    else
		contrib = pmat[MI(d->fromstate[i], d->tostate[i], qm->nst)];
	    lik += d->nocc[i] * log(contrib);
#ifdef DEBUG
	    printf("obs %d, from %d, to %d, time %lf, obstype %d, ", i, d->fromstate[i], d->tostate[i], d->timelag[i], d->obstype[i]);
	    for (j = 0; j < qcm->ncovs[0]; ++j)
		printf("cov%d %lf, ", j, d->cov[MI(i, d->whichcov[j]-1, d->nobs)]);
	    printf("nocc %d, con %lf, lik %lf\n", d->nocc[i], log(contrib), lik);
#endif	    
	}
    Free(pmat); Free(newintens);
    return (-2*lik); 
}

/* Find zero-based index of maximum element of a vector x */

void pmax(double *x, int n, int *maxi)
{
    int i=0;
    *maxi = i;
    for (i=1; i<n; ++i) {
	if (x[i] > x[*maxi]) {
	    *maxi = i;
	}
    }    
}

/* Calculates the most likely path through underlying states */ 

void Viterbi(msmdata *d, qmodel *qm, qcmodel *qcm, 
	     cmodel *cm, hmodel *hm,  
	     double *fitted)
{
    int i, j, tru, fp, k, kmax, obs, totcovs=0, nc = 1;
    double *newintens   = (double *) S_alloc(qm->npars, sizeof(double));
    double *newpars = (double *) S_alloc(hm->totpars, sizeof(double));
    double *newinitp = (double *) S_alloc(qm->nst, sizeof(double));
    double *pmat = (double *) S_alloc((qm->nst)*(qm->nst), sizeof(double));
    int *ptr = (int *) S_alloc((d->nobs)*(qm->nst), sizeof(int));
    double *lvold = (double *) S_alloc(qm->nst, sizeof(double));
    double *lvnew = (double *) S_alloc(qm->nst, sizeof(double));
    double *lvp = (double *) S_alloc(qm->nst, sizeof(double));
    double *curr = (double *) S_alloc (qm->nst, sizeof(double));
    double *pout = (double *) S_alloc(qm->nst, sizeof(double)); 
    double dt;

    /* Add covariate effects on initp (expressed as p(cat) / p(baseline cat)) */
    i = 0;
    if (d->obstrue[i]) { 
      for (k = 0; k < qm->nst; ++k) 
	lvold[k] = (k+1 == d->obs[i] ? 1 : R_NegInf);
    }
    else {
      GetCensored(d->obs[i], cm, &nc, &curr);
      /* initial observation is a censored state. No HMM here, so initprobs not needed */
      if (nc > 1) {
	for (k = 0, j = 0; k < qm->nst; ++k) {
	  if (k+1 == curr[j]) {
	    lvold[k] = 1;
	    ++j;
	  }
	  else lvold[k] = R_NegInf;
	}
      } 
      else { 
	/* use initprobs */
	AddCovs(i, d->nobs, qm->nst - 1, hm->nicovs, &hm->initp[1], &newinitp[1], 
		hm->icoveffect, d->cov, d->whichcovi, &totcovs, log, exp);
	relative2absolutep(newinitp, newinitp, qm->nst, 0);
	for (k = 0; k < qm->nst; ++k) 
	  lvold[k] = log(newinitp[k]);
      }
    }

    for (i = 1; i <= d->nobs; ++i)
	{
	    R_CheckUserInterrupt();
#ifdef VITDEBUG
	    printf("obs %d\n", i);
#endif
	    if ((i < d->nobs) && (d->subject[i] == d->subject[i-1]))
		{
#ifdef VITDEBUG
		    printf("subject %d\n ", d->subject[i]);
#endif
		    dt = d->time[i] - d->time[i-1];
		    AddCovs(i - 1, d->nobs, qm->npars, qcm->ncovs, qm->intens, newintens,
			    qcm->coveffect, d->cov, d->whichcov, &totcovs,
			    log, exp); 	
		    totcovs = 0;
		    for (j = 0; j < qm->nst; ++j) {
			fp = hm->firstpar[j];
			AddCovs(i - 1, d->nobs, hm->npars[j], &(hm->ncovs[fp]), &(hm->pars[fp]), 
				&(newpars[fp]), &(hm->coveffect[totcovs]), d->cov, &(d->whichcovh[totcovs]),
				&totcovs, LINKFNS[hm->links[j]][0], LINKFNS[hm->links[j]][1]);
		    }
		    GetCensored(d->obs[i], cm, &nc, &curr);
		    GetOutcomeProb(pout, curr, nc, newpars, hm, qm, d->obstrue[i]);
#ifdef VITDEBUG			  
		    for (tru=0;tru<nc;++tru) printf("curr[%d] = %1.0lf, ",tru, curr[tru]); printf("\n");
#endif
		    Pmat(pmat, dt, newintens, qm->npars, qm->ivector, qm->nst,
			 (d->obstype[i] == OBS_EXACT), qm->analyticp, qm->iso, qm->perm,  qm->qperm, 0);

		    for (tru = 0; tru < qm->nst; ++tru)
			{
			  if (d->obstrue[i-1]) { 
			    lvnew[tru] = (tru == d->obs[i-1] - 1 ? 1 : R_NegInf);
			    ptr[MI(i, tru, d->nobs)] = kmax = d->obs[i-1] - 1;
			  }
			  else {
			    for (k = 0; k < qm->nst; ++k)
				lvp[k] = lvold[k] + log(pmat[MI(k, tru, qm->nst)]);
			    pmax(lvp, qm->nst, &kmax);			    
			    lvnew[tru] = log ( pout[tru] )  +  lvp[kmax];
			    ptr[MI(i, tru, d->nobs)] = kmax;
			  }
#ifdef VITDEBUG			  
			    printf("true %d, pout[%d] = %lf, lvold = %lf, pmat = %lf, lvnew = %lf, mi = %d, ptr=%d\n", 
				   tru, tru, pout[tru], lvold[tru], pmat[MI(kmax, tru, qm->nst)], lvnew[tru], MI(i, tru, d->nobs), ptr[MI(i, tru, d->nobs)]);
#endif
			}
		    for (k = 0; k < qm->nst; ++k)
			lvold[k] = lvnew[k];
		}
	    else 
		{
#ifdef VITDEBUG
		    printf("traceback for subject %d\n ", d->subject[i-1]);
#endif
		    /* Traceback for current individual */
		    pmax(lvold, qm->nst, &kmax);
#ifdef VITDEBUG
		    printf("kmax = %d\n", kmax);
#endif	  
		    obs = i-1;
		    fitted[obs] = (d->obstrue[obs] ? d->obs[obs]-1 : kmax);  /* if last obs censoring, then kmax=0 since pout all 0 for prev obs, wrong, should be 0,1,1,0. */
		    while   ( (obs > 0) && (d->subject[obs] == d->subject[obs-1]) ) 
			{
			    fitted[obs-1] = ptr[MI(obs, fitted[obs], d->nobs)];
#ifdef VITDEBUG
			    printf("mi = %d, ptr %d = %1.0lf, ", MI(obs, (int) fitted[obs], d->nobs), obs-1, fitted[obs-1]);
#endif
			    --obs;
			}

		    /* Add covariate effects on initp (expressed as p(cat) / p(baseline cat)) */
		    if (d->obstrue[i]) { 
		      for (k = 0; k < qm->nst; ++k) 
			lvold[k] = (k+1 == d->obs[i] ? 1 : R_NegInf);
		    }
		    else {
		      GetCensored(d->obs[i], cm, &nc, &curr);
		      /* initial observation is a censored state. No HMM here, so initprobs not needed */
		      if (nc > 1) {
			for (k = 0, j = 0; k < qm->nst; ++k) {
			  if (k+1 == curr[j]) {
			    lvold[k] = 1;
			    ++j;
			  }
			  else lvold[k] = R_NegInf;
			}
		      } 
		      else { 
			/* use initprobs */
			AddCovs(i, d->nobs, qm->nst - 1, hm->nicovs, &hm->initp[1], &newinitp[1], 
				hm->icoveffect, d->cov, d->whichcovi, &totcovs, log, exp);
			relative2absolutep(newinitp, newinitp, qm->nst, 0);
			for (k = 0; k < qm->nst; ++k) 
			  lvold[k] = log(newinitp[k]);
		      }
		    }
		}
	}
}


void msmLikelihood (msmdata *d, qmodel *qm, qcmodel *qcm, 
		    cmodel *cm, hmodel *hm, 
		    double *returned) 
{
    int pt;
    double likone;
    /* Likelihood for hidden Markov model */
    if (hm->hidden) 
	{
	    *returned = 0;
	    for (pt = 0;  pt < d->npts; ++pt){
		likone = likhidden (pt, d, qm, qcm, cm, hm);
#ifdef DEBUG
		printf("pt %d, lik %lf\n", pt, likone);
#endif
		*returned += likone;
	    }
	}
    /* Likelihood for Markov model with censored outcomes */
    else if (cm->ncens > 0)
	{
	    for (pt = 0;  pt < d->npts; ++pt){
		likone = likcensor (pt, d, qm, qcm, cm, hm);
#ifdef DEBUG
		printf("pt %d, lik %lf\n", pt, likone);
#endif
		*returned += likone;
	    }
	}
    /* Likelihood for simple non-hidden, non-censored Markov model */
    else {
	*returned = liksimple (d, qm, qcm, cm, hm);
    }
}


/* First derivatives of the log-likelihood for the non-hidden
   multi-state Markov model. */

void derivsimple(msmdata *d, qmodel *qm, qcmodel *qcm, 
		 cmodel *cm, hmodel *hm, double *deriv)
{
    int i, p, np=qm->npars, ndp=qm->ndpars, ndc=qcm->ndpars, totcovs=0; 
    double contrib=0;

    double *dcontrib = Calloc(ndp+ndc, double);
    double *dpmat = Calloc(qm->nst * qm->nst * (ndp+ndc), double); 
    double *pmat = Calloc(qm->nst * qm->nst, double);
    double *newintens = Calloc(np, double);
    double *x = Calloc(qcm->ncovs[0], double);

    for (i=0; i < d->nobs; ++i)
	{
	    R_CheckUserInterrupt();
	    if ((i==0) || (d->whicha[i] != d->whicha[i-1]) || (d->obstype[i] != d->obstype[i-1])) {
		/* we have a new timelag/covariates/obstype combination. Recalculate the 
		   P matrix and its derivatives for this */
		GetCovData(i, d->cov, d->whichcov, x, qcm->ncovs[0], d->nobs);
		AddCovs(i, d->nobs, np, qcm->ncovs, qm->intens, newintens,
			qcm->coveffect, d->cov, d->whichcov, &totcovs, log, exp);
		Pmat(pmat, d->timelag[i], newintens, qm->npars, qm->ivector, qm->nst, (d->obstype[i] == OBS_EXACT), qm->analyticp, qm->iso, qm->perm,  qm->qperm, 0);
 		DPmat(dpmat, d->timelag[i], x, newintens, qm->intens, qm->ivector, qm->nst, np, ndp, ndc,
		      qm->constr, qcm->constr, qcm->wcov, (d->obstype[i] == OBS_EXACT));
	    }
	    if (d->obstype[i] == OBS_DEATH) {
		contrib = pijdeath(d->fromstate[i], d->tostate[i], pmat, newintens, qm->ivector, qm->nst);
		dpijdeath(d->fromstate[i], d->tostate[i], x, dpmat, pmat, newintens, qm->intens, qm->ivector, 
			  qm->nst, qm->constr, qcm->constr, ndp, ndc, qcm->ncovs[0], dcontrib);
	    }
	    else {
		contrib = pmat[MI(d->fromstate[i], d->tostate[i], qm->nst)];
		for (p = 0; p < ndp+ndc; ++p)
		    dcontrib[p] = dpmat[MI3(d->fromstate[i], d->tostate[i], p, qm->nst, qm->nst)];
	    }
	    for (p = 0; p < ndp+ndc; ++p) {
		deriv[p] += d->nocc[i] * dcontrib[p] / contrib;
	    }
	}
    for (p = 0; p < ndp+ndc; ++p) 
	deriv[p] *= -2;
    Free(dcontrib); Free(dpmat); Free(pmat); Free(newintens); Free(x);
}

/* First derivatives of the likelihood for the non-hidden multi-state
   Markov model. Uses data of form "subject, time, state, covariates".
   Returns derivatives by individual and parameter for use in the
   score residual diagnostic.
*/

void derivsimple_subj(msmdata *d, qmodel *qm, qcmodel *qcm, 
			cmodel *cm, hmodel *hm, double *deriv)
{
    int pt, i, p, np=qm->npars, ndp=qm->ndpars, ndc=qcm->ndpars, totcovs=0;
    double *dcontrib = Calloc(ndp+ndc, double);
    double *dpmat = Calloc(qm->nst * qm->nst * (ndp+ndc), double); 
    double *pmat = Calloc(qm->nst * qm->nst, double);
    double *newintens = Calloc(np, double);
    double *x = Calloc(qcm->ncovs[0], double);
    double contrib=0, dt;
    int from, to;
    for (pt = 0;  pt < d->npts; ++pt){
	{
	    R_CheckUserInterrupt();
	    if (d->firstobs[pt+1] > d->firstobs[pt] + 1) { /* individual has more than one observation? */ 
		for (i = d->firstobs[pt]+1; i < d->firstobs[pt+1]; ++i) {
		    for (p = 0; p < ndp+ndc; ++p) {
			deriv[MI(pt,p,d->npts)] = 0;
		    }
		    GetCovData(i, d->covobs, d->whichcov, x, qcm->ncovs[0], d->n);
		    AddCovs(i, d->n, np, qcm->ncovs, qm->intens, newintens,
			    qcm->coveffect, d->covobs, d->whichcov, &totcovs, log, exp);
		    
		    dt = d->time[i] - d->time[i-1];
		    from = fprec(d->obs[i-1] - 1, 0); /* convert state outcome to integer */
		    to = fprec(d->obs[i] - 1, 0);
		    Pmat(pmat, dt, newintens, qm->npars, qm->ivector, qm->nst, (d->obstype[i] == OBS_EXACT), qm->analyticp, qm->iso, qm->perm,  qm->qperm, 0);
		    DPmat(dpmat, dt, x, newintens, qm->intens, qm->ivector, qm->nst, np, ndp, ndc,
			  qm->constr, qcm->constr, qcm->wcov, (d->obstype[i] == OBS_EXACT));
		    if (d->obstype[i] == OBS_DEATH) {
			contrib = pijdeath(from, to, pmat, newintens, qm->ivector, qm->nst);
			dpijdeath(from, to, x, dpmat, pmat, newintens, qm->intens, qm->ivector, 
				  qm->nst, qm->constr, qcm->constr, ndp, ndc, qcm->ncovs[0], dcontrib);
		    }
		    else {
			contrib = pmat[MI(from, to, qm->nst)];
			for (p = 0; p < ndp+ndc; ++p)
			    dcontrib[p] = dpmat[MI3(from, to, p, qm->nst, qm->nst)];		
		    }
		    for (p = 0; p < ndp+ndc; ++p) {
		      deriv[MI(pt,p,d->npts)] += dcontrib[p] / contrib; /* on loglik scale not -2*loglik */
		    }
		}
		for (p = 0; p < ndp+ndc; ++p)
		    deriv[MI(pt,p,d->npts)] *= -2;
	    }
	    else for (p = 0; p < ndp+ndc; ++p)
		deriv[MI(pt,p,d->npts)] = 0;
	}
    }
    Free(dcontrib); Free(dpmat); Free(pmat); Free(newintens); Free(x);
}

/* Derivative of log-likelihood. Not available for hidden models or
   models with censoring. */

void msmDLikelihood (msmdata *d, qmodel *qm, qcmodel *qcm, 
		     cmodel *cm, hmodel *hm, 
		     double *returned) 
{
    derivsimple (d, qm, qcm, cm, hm, returned);
}

void msmDLikelihood_subj (msmdata *d, qmodel *qm, qcmodel *qcm, 
		     cmodel *cm, hmodel *hm, 
		     double *returned) 
{
    derivsimple_subj (d, qm, qcm, cm, hm, returned);
}

/* This function is called from R to provide an entry into C code for
   evaluating likelihoods, derivatives and doing Viterbi state reconstruction  */

void msmCEntry( 
	       int *do_what,      /* 1 = eval likelihood, 2 = Viterbi */
	       int *qvector,      /* vectorised matrix of allowed transition indicators */
	       /* Parameters */
	       double *intens,    
	       double *coveffect,    
	       double *hmmpars, 
	       double *hcoveffect,

	       /* Data for non-HMM multi-state models */    
	       int *fromstate,  /* Distinct combinations of from, to, time lag, covariates */
	       int *tostate,    
	       double *timelag,
	       double *covvec,  /* vectorised matrix of covariate data (also used for HMMs) */
	       double *covobsvec,  /* vectorised matrix of covariate data (by observation) used when calculating derivs by individual */
	       int *whichcov,    /* which column in the covariate data each cov corresponds to */
	       int *nocc,       /* Number of occurrences of each distinct combination */
	       int *whicha,   /* indicator for the from, to, time lag, covs combination corresponding to the current obs */
	       int *obstype,   /* observation scheme, 1 snapshot, 2 exact, 3 death */

	       /* Data for HMMs */
	       int *subjvec,      /* vector of subject IDs */
	       double *timevec,   /* vector of observation times */
	       double *obsvec,     /* vector of observations (observed states in the case of misclassification models) */
	       int *firstobs,   /* 0-based index into data of the first observation for each individual */
	       int *obstrue,   /* which observations in a HMM represent the true underlying state (none by default) */
	       
	       /* HMM specification */
	       int *hidden,       /* well, is it or isn't it? */
	       int *hmodels,      /* which hidden Markov distribution */
	       int *hnpars,       /* number of basic HMM parameters for each state, not including covariate effects */
	       int *htotpars,      /* total number of HMM parameters */
	       int *hfirstpar,    /* index into hmmpars of first parameter for each state */
	       int *hncovs,       /* number of covariate effects on each HMM parameter */
	       int *whichcovh,    /* which column in the covariate data */
	       int *links,        /* link function for each state distribution */
	       double *initprobs, /* initial state occupancy probabilities */
	       int *nicovs,        /* number of covariate effects on these */
	       double *icoveffect, /* values of these effects */
	       int *whichcovi,    /* which column in the covariate data */

	       int *nst,      /* number of Markov states */
	       int *analyticp, /* should P matrix be calculated analytically */
	       int *iso, /* graph isomorphism ID */
	       int *perm, /* permutation to the base isomorphism */
	       int *qperm, /* permutation of intensity parameters from the base isomorphism */
	       int *nintens,      /* number of intensity parameters */
	       int *ndintens,      /* number of distinct intensity parameters */
	       int *ndcovpars,      /* number of distinct covariate parameters */
	       int *nobs,         /* number of observations in data set (hmm/cens) or number of aggregated transitions (standard) */
	       int *n,         /* number of observations in data set (used for derivs by individual in standard models. no of rows of covobsvec) */
	       int *npts,         /* number of individuals in data set */
	       int *ncovs,        /* number of covariates on transition rates */

	       int *ncens,     /* number of distinct forms of censoring */
	       int *censor,    /* censoring indicators in data, of length ncens */
	       int *censstates, /* list of possible states represented by censoring indicators */
	       int *censstind,  /* starting index into censstates for each censoring indicator */
	       
	       int *qconstraint, /* constraints for baseline intensities. needed to calculate derivs */
	       int *cconstraint, /* constraints for covariates. needed to calculate derivs */
	       int *whichcovd,  /* which covariate each _distinct_ covariate parameter corresponds to */

	       double *returned   /* returned -2 log likelihood , Viterbi fitted values, or predicted values */
	       )
{
  msmdata d; qmodel qm; qcmodel qcm; cmodel cm; hmodel hm; 
    
  d.fromstate = fromstate;     d.tostate = tostate;     d.timelag = timelag;   
  d.cov = covvec;  d.covobs = covobsvec;  d.nocc = nocc;  d.whicha = whicha; d.obstype = obstype;  d.obstrue = obstrue; 
  d.whichcov = whichcov;  d.whichcovh = whichcovh;  d.whichcovi=whichcovi;
  d.subject = subjvec; d.time = timevec; d.obs = obsvec; d.firstobs = firstobs;
  d.nobs = *nobs;  d.n = *n; d.npts = *npts;

  qm.nst = *nst; qm.npars = *nintens; qm.ndpars = *ndintens; qm.ivector = qvector; qm.intens = intens; 
  qm.analyticp = *analyticp; qm.iso = *iso; qm.perm = perm; qm.qperm = qperm; qm.constr = qconstraint;    

  qcm.ncovs = ncovs; qcm.coveffect = coveffect; qcm.constr = cconstraint; qcm.ndpars = *ndcovpars; qcm.wcov = whichcovd;

  cm.ncens = *ncens; cm.censor = censor; cm.censstates=censstates; cm.censstind=censstind;

  hm.hidden = *hidden;  hm.models = hmodels;  hm.npars = hnpars;  hm.totpars = *htotpars;
  hm.firstpar = hfirstpar;  hm.ncovs = hncovs;  hm.pars = hmmpars; 
  hm.coveffect = hcoveffect;  hm.links = links; 
  hm.initp = initprobs; hm.nicovs = nicovs; hm.icoveffect = icoveffect;

  if (*do_what == 0) {
    msmLikelihood(&d, &qm, &qcm, &cm, &hm, returned);
  }

  else if (*do_what == 1) {
    msmDLikelihood(&d, &qm, &qcm, &cm, &hm, returned);
  }

  else if (*do_what == 2) {
    Viterbi(&d, &qm, &qcm, &cm, &hm, returned);
  }
  else if (*do_what == 3) {
    msmDLikelihood_subj(&d, &qm, &qcm, &cm, &hm, returned); /* derivative of loglik by subject. used for score residuals */
  }
}
