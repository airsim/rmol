#include <math.h>
#include <stdlib.h>
#include <R.h>
#include <R_ext/Applic.h>

/* index to treat a vector as a matrix. ith row, jth column. Fills columns first, as in R */
#define MI(i, j, nrows) ( (int) ((j)*(nrows) + (i)) )
/* index to treat a vector as a 3-dimensional array. Left-most index varies fastest, as in R */
#define MI3(i, j, k, n1, n2) ( (int) ((k)*(n1*n2) + (j)*(n1) + (i)) )

/* Macros to switch quickly between C and S memory handling. Currently not used */

#define USE_CALLOC
/* #define USE_SALLOC */

#ifdef USE_CALLOC
#define MSM_ALLOC(length, type) Calloc((length), type)
#define MSM_FREE(var) Free((var))
#else
#define MSM_ALLOC(length, type) (type *) S_alloc((length), sizeof(type))
#define MSM_FREE(var) 
#endif 

typedef double * Array3;
typedef double * Matrix;
typedef int * iMatrix;
typedef double * vector;
typedef int * ivector;

struct msmdata {
    /* for non-hidden model */
    int *fromstate;
    int *tostate;
    double *timelag;
    double *cov;
    double *covobs;
    int *whichcov;
    int *nocc;
    int *whicha;
    int *obstype;
    int *obstrue;

    /* for hidden model */
    int *subject;
    double *time;
    double *obs; /* observed state or any other HMM observation */
    int *firstobs;
    int *whichcovh;
    int *whichcovi;

    int nobs;
    int n;
    int npts;
};

struct qmodel {
    int nst;
    int npars;
    int ndpars;
    int *ivector;
    double *intens;
    int analyticp;
    int iso;
    int *perm;
    int *qperm;
    int *constr;
};

struct qcmodel {
    int *ncovs;
    double *coveffect;
    int *constr;
    int ndpars;
    int *wcov;
};

struct cmodel {
    int ncens;
    int *censor;
    int *censstind;
    int *censstates;
};

struct hmodel {
    int hidden;
    int *models;
    int *npars;
    int *firstpar;
    int *ncovs;
    double *pars;
    int totpars; 
    double *coveffect;
    int *links;
    double *initp;
    int *nicovs;
    double *icoveffect;
};

typedef struct msmdata msmdata;
typedef struct qmodel qmodel;
typedef struct qcmodel qcmodel;
typedef struct cmodel cmodel;
typedef struct hmodel hmodel;

double qij(int i, int j, vector intens, ivector qvector, int nstates);
double pijdeath(int r, int s, Matrix pmat, vector intens, ivector qvector, int n);
void Pmat(Matrix pmat, double t, vector intens, int nintens, int *qvector, int nstates, int exacttimes, int analyticp, int iso, int *perm, int *qperm, int debug);
void DPmat(Array3 dpmat, double t, vector x, vector intens, vector oldintens, ivector qvector, 
	   int n, int np, int ndp, int ndc, ivector qconstr, ivector bconstr, ivector wcov, int exacttimes);
void dpijdeath(int r, int s, vector x, Array3 dpmat, Matrix pmat, vector intens, vector oldintens, ivector qvector, 
	       int n, ivector constr, ivector bconstr, int ndp, int ndc, int ncovs, vector dcontrib);
int repeated_entries(vector vec, int n);

double logit(double x);
double expit(double x);
double identity(double x);
int all_equal(double x, double y);
void relative2absolutep(double *relative, double *absolute, int n, int baseline);

void MatrixExpPadeR(double *ExpAt, double *A, int *n, double *t);

void AnalyticP(Matrix pmat, double t, int nstates, int iso, int *perm, int *qperm, vector intens, int nintens, int *degen);

