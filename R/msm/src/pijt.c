/* *****************************************************************

   pijt.c: Linear algebra routines for msm. To obtain Markov
   transition probabilities (the P-matrix) from transition intensities
   (the Q-matrix).

   Copyright (c) Chris Jackson 2001-2005

   Pade approximants method of calculating matrix exponentials is
   based on matexp.cc from JAGS, Copyright (c) 2004, Martyn Plummer.  
   http://www-fis.iarc.fr/~martyn/software/jags
   
   ******************************************************************  */ 

#include "msm.h"
/* Crude benchmarks have shown that using the eigensystem routines
   from LINPACK, and the matrix inversion routines from LAPACK, is the
   faster combination. However...
   Occasional crashes on extremely flat optimisations. 
   Valgrind reveals memory errors within LINPACK Fortran eigen code. 
   Crashes don't occur if use LAPACK code. 
*/
#define _USE_LAPACK_EIGEN_
#define _USE_LAPACK_INVERSE_
#define _MEXP_METHOD_ 1 /* 1 for Pade approximation, 2 for series. Pade is more robust. */
#include "R_ext/Lapack.h"

/* Set A to be an n x n identity matrix */

void FormIdentity(Matrix A, int n)
{
    int i;
    for (i = 0; i < (n*n); ++i)
	A[i] = 0;
    for (i = 0; i < n; ++i)
	A[MI(i, i, n)] = 1;
}

/* Invert a matrix by calling LINPACK QR decomposition routines */
/* DGETRF/DGETRI method (current)  is from LAPACK. This is the fastest.   */
/* DQR method (used in <=0.4.1) is from LINPACK */ 

void MatInvDGE(Matrix A, Matrix Ainv, int n)
{
    int i, j;
    Matrix temp = (Matrix) Calloc(n*n, double);
    Matrix work = (Matrix) Calloc(n*n, double);
    int nsq=n*n, info, *pivot = Calloc(n, int);
    for (i=0; i<nsq; ++i)
      temp[i] = A[i];
    F77_CALL(dgetrf) (&n, &n, temp, &n, pivot, &info);
    if (info < 0)
	REprintf("error code %d from Lapack routine dgetrf\n", info);
    F77_CALL(dgetri) (&n, temp, &n, pivot, work, &nsq, &info);
    if (info < 0)
	REprintf("error code %d from Lapack routine dgetri\n", info);
    for (i=0; i<n; ++i)
	for (j=0; j<n; ++j)
	    Ainv[MI(i,j,n)] = temp[MI(i,j,n)];
    Free(work); Free(pivot); Free(temp); 
}

void MatInvDQR(Matrix A, Matrix Ainv, int n)
{
    int i, rank;
    Matrix temp = (Matrix) Calloc(n*n, double);
    Matrix work = (Matrix) Calloc(n*n, double);
    Matrix qraux = (Matrix) Calloc(n*n, double);
    Matrix ident = (Matrix) Calloc(n*n, double); 
    int nsq=n*n, info, *pivot = Calloc(n, int);
    double tol=1e-07;
    for (i=0; i<nsq; ++i)
      temp[i] = A[i];
    F77_CALL(dqrdc2) (temp, &n, &n, &n, &tol, &rank, qraux, pivot, work); 
    FormIdentity(ident, n); 
    F77_CALL(dqrcf) (temp, &n, &rank, qraux, ident, &n, Ainv, &info); 
    if (info < 0)
	REprintf("error code %d from Linpack routine dqrcf\n", info);
    Free(temp); Free(work); Free(qraux); Free(ident);Free(pivot); 
}

void MatInv(Matrix A, Matrix Ainv, int n)
{
#ifdef _USE_LAPACK_INVERSE_
	MatInvDGE(A, Ainv, n);
#endif
#ifdef _USE_LINPACK_INVERSE_
	MatInvDQR(A, Ainv, n);
#endif
}

/* Multiply two matrices together */

void MultMat(Matrix A, Matrix B, int arows, int acols, int bcols, Matrix AB)
{
    int i, j, k;  
    for (i = 0; i < arows; i++) {
	for (j = 0; j < bcols; j++) {
	    AB[MI(i, j, bcols)] = 0;
	    for (k = 0; k < acols; k++) 
		AB[MI(i, j, bcols)] += A[MI(i, k, acols)] * B[MI(k, j, bcols)];
	}
    }
}

/* Copy one matrix A to another B */

void CopyMat(Matrix A, Matrix B, int arows, int acols) 
{
    int i;
    for (i = 0; i < arows*acols; i++)
	B[i] = A[i];
}

/* Pre-multiply a general matrix by a diagonal matrix (given by a vector) */

void MultMatDiag(vector diag, Matrix B, int n, Matrix AB)
{
    int i, j;
    for (i = 0; i < (n*n); ++i)
	AB[i] = 0;
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    AB[MI(i, j, n)] += diag[i] * B[MI(i, j, n)];
	}
    }
}

/* Calculate a matrix exponential using a power series approximation
   Adapted from mexp in Jim Lindsey's "rmutil" package
   exp(A)  =  I + A + AA/2  + AAA/2*3 + AAAA/2*3*4 + ...
   Overflow correction: 
   exp(A)  =  exp(A/2^3) exp(A/2^3) exp(A/2^3)
*/

void MatrixExpSeries(Matrix A, int n, Matrix expmat, double t)
{
    int i, j;
    int order = 20;   /* number of terms in series */
    int overflow_correct = 3;
    Matrix Apower = Calloc(n*n, double);
    Matrix Temp = Calloc(n*n, double);
    Matrix AA = Calloc(n*n, double);
    for (i=0; i<(n*n); ++i)
	AA[i] = A[i] * (t / pow(2, overflow_correct));
    FormIdentity(expmat, n);
    FormIdentity(Apower, n);
    for (i=1; i<=order; i++) {
	MultMat(AA, Apower, n, n, n, Temp);
	for (j=0; j<(n*n); ++j){
	    Apower[j] = Temp[j] / i;
	    expmat[j] += Apower[j];
	}
    }
    for (i=0; i<overflow_correct; ++i){
	MultMat(expmat, expmat, n, n, n, Temp);
	CopyMat(Temp, expmat, n, n);
    }
    Free(Apower); Free(Temp); Free(AA);
}

/* Pade approximants method of calculating matrix exponentials 
   From matexp.cc from JAGS by Martyn Plummer  Copyright (c) 2004
   http://www-fis.iarc.fr/~martyn/software/jags
*/

static void solve(double *X, double const *A, double const *B, int n)
{
    /* Solve AX = B, where all matrices are square */
    int N = n*n;
    double *Acopy = Calloc(N, double);
    double *work = Calloc(N, double);
    int *ipiv = Calloc(N, int);
    int info = 0;
    static int c_1 = 1;
    F77_CALL(dcopy)(&N, A, &c_1, Acopy, &c_1);
    F77_CALL(dcopy)(&N, B, &c_1, X, &c_1);
    F77_CALL(dgesv)(&n, &n, Acopy, &n, ipiv, X, &n, &info);
    if (info < 0)
	REprintf("argument %d of Lapack routine dgesv had illegal value\n", -info);
    if (info > 0)
	REprintf("Lapack routine dgesv: system is exactly singular\n");
    Free(Acopy); 
    Free(ipiv);
    Free(work);
}

static void
padeseries (double *Sum, double *A, int m, int order, 
            double scale, double *Temp)
{
    int i, j, r; 
    int N = m*m;
    FormIdentity(Sum, m);
    for (j = order; j >= 1; --j) {
	double s = (order-j+1) / (j*(2*order-j+1) * scale);
	MultMat(Sum, A, m, m, m, Temp);
	for (i = 0; i < N; ++i) {
	    Sum[i] = Temp[i] * s;
	}
	for (r = 0; r < m; ++r) {
	    Sum[r*m+r] += 1;
	}
    }
}

void 
MatrixExpPade(double *ExpAt, double *A, int n, double t)
{
  /* Calculate exp(A*t) by diagonal Pade approximation with scaling and
     squaring */
    int i, j; 
  int order = 8;
  int N = n*n;
  double *workspace =  Calloc( 4*N, double);
  double * Temp = workspace;
  double * At = workspace + N;
  double * Num = workspace + 2*N;
  double * Denom = workspace + 3*N;
  double l1 = F77_CALL(dlange)("1", &n, &n, At, &n, 0); /* L-1 norm */
  double linf = F77_CALL(dlange)("i", &n, &n, At, &n, Temp); /* L-Infinity norm */
  double K = (log(l1) + log(linf))/log(4);
  int npower =  (int)(K) + 4;
  double scale = 1;

  /* Multiply by t */

  for (i = 0; i < N; ++i) {
    At[i] = A[i] * t;  
  }

  /* Scale the matrix by a power of 2 */
  /* 
     The expression below is not clear because it is optimized.  The
     idea is that sqrt(l1 * linf) is an upper bound on the L2 norm of
     the matrix At (i.e the largest eigenvalue). We want to take the
     log, to base 2 of this to get the smallest K, st ||At/2^K|| <= 1.
  */
  if (npower < 0) {
      npower = 0;
  }
  for (i = 0; i < npower; ++i) {
    scale *= 2;
  }

  /* Calculate exp(A/scale) by Pade series  */

  padeseries (Num, At, n, order, scale, Temp);
  for (i = 0; i < N; ++i) {
    At[i] = -At[i];
  }
  padeseries (Denom, At, n, order, scale, Temp);
  solve(ExpAt, Denom, Num, n);

  /* Now repeatedly square the result */
  for (i = 0; i < npower; ++i) {
    for (j = 0; j < N; ++j) {
      Temp[j] = ExpAt[j];
    }
    MultMat(Temp, Temp, n, n, n, ExpAt);
  }
  Free(workspace);
}

/* R interface to Pade method */

void MatrixExpPadeR(double *ExpAt, double *A, int *n, double *t)
{
    MatrixExpPade(ExpAt, A, *n, *t);
}

/* Tests if a vector has any non-unique entries */

int repeated_entries(vector vec, int n)
{
    int i, j;
    for (i=1; i<n; ++i)
	for (j=0; j<i; ++j)
	    if (vec[j] == vec[i]) 
		return 1;
    return 0;
}

void Eigen(Matrix mat, int n, vector revals, vector ievals, Matrix evecs, int *err)
{
    int i, nsq=n*n;
#ifdef _USE_LINPACK_EIGEN_
    int matz = 1;
#endif
#ifdef _USE_LAPACK_EIGEN_	
    int lwork = -1;
    char jobVL[1], jobVR[1];
    double *left=0, tmp;
#endif
    Matrix work = (Matrix) Calloc(nsq, double);
    iMatrix worki = (iMatrix) Calloc(nsq, int);
    Matrix temp = (Matrix) Calloc(nsq, double);
    for (i=0; i<nsq; ++i) {
	/* Check whether any of the elements of Q have overflowed.  If
	   so, Fortran eigen function will hang in a infinite loop, so
	   bail out before this happens.  */
	if (!R_FINITE(mat[i]))
	    error("numerical overflow in calculating likelihood\n");
	temp[i] = mat[i];
    }
#ifdef _USE_LINPACK_EIGEN_
    F77_CALL(rg) (&n, &n, temp, revals, ievals, &matz, evecs, worki, work, err);
#endif
#ifdef _USE_LAPACK_EIGEN_	
    jobVL[0] = 'N'; jobVR[0] = 'V';
    /* calculate optimal size of workspace */
    F77_CALL(dgeev)(jobVL, jobVR, &n, temp, &n, revals, ievals, left, &n, evecs, &n, &tmp, &lwork, err);
    lwork = (int) tmp;
    work = (Matrix) Realloc(work, lwork, double);
    /* calculate eigensystem */
    F77_CALL(dgeev)(jobVL, jobVR, &n, temp, &n, revals, ievals, left, &n, evecs, &n, work, &lwork, err);
#endif
    Free(work); Free(worki); Free(temp);
}

/* Compute exponential of a matrix */
/* First try to use eigensystem decomposition */
/* If matrix has repeated eigenvalues, then use Pade approximation
   with scaling and squaring, or (less robust) power series.  */

/* TODO: Would it be more economical in the long run to test for
   invertibility by calculating determinant, thus reducing number of
   cases where it is necessary to use power series or Pade? */

void MatrixExp(Matrix mat, int n, Matrix expmat, double t, int debug, int degen)
{  
    int i, err=0, complex_evals=0, nsq=n*n;
    Matrix work = (Matrix) Calloc(nsq, double);
    vector revals = (vector) Calloc(n, double);
    vector ievals = (vector) Calloc(n, double);
    Matrix evecs = (Matrix) Calloc(nsq, double);
    Matrix evecsinv = (Matrix) Calloc(nsq, double);
    /* calculate eigensystem */
    if (!degen) 
	Eigen(mat, n, revals, ievals, evecs, &err);
    /* Check for eigenvalues with nonzero imaginary part */
    for (i=0; i<n; ++i)
      if (!all_equal(ievals[i],0)){
	complex_evals = 1;
	break;
      }
    if (repeated_entries (revals, n) || (err != 0) || degen || complex_evals){
#if _MEXP_METHOD_==1 
	MatrixExpPade(expmat, mat, n, t);
#elif _MEXP_METHOD_==2 
	MatrixExpSeries(mat, n, expmat, t);
#endif
    }
    else {
	for (i=0; i<n; ++i)
	    revals[i] = exp(revals[i] * t);
	MatInv(evecs, evecsinv, n);
	MultMatDiag(revals, evecsinv, n, work);
	MultMat(evecs, work, n, n, n, expmat);
    }
    Free(work);  Free(revals);  Free(ievals); Free(evecs);  Free(evecsinv); 
}

/* Fills the required entries of the intensity matrix with the current intensities */
/* qvector supplied filled by row. intens ordered by row, qmat filled by column */
/* TODO can probably optimise by passing this from R */

void FillQmatrix(ivector qvector, vector intens, Matrix qmat, int nstates)
{
    int i, j, k=0;
    for (i=0; i<nstates; ++i) {
	qmat[MI(i, i, nstates)] = 0;
	for (j=0; j<nstates; ++j) {
	    if (j != i) {
		qmat[MI(i, j, nstates)] = 0;
		if (qvector[MI(j, i, nstates)] == 1) {
		    qmat[MI(i, j, nstates)] += intens[k];
		    qmat[MI(i, i, nstates)] -= intens[k];
		    ++k;
		}
	    }
	}
    }
}

/* Returns i-j transition intensity time t given vectors of intensities and transition indicators */
/* TODO can probably save time by passing filled Qmatrix from R */

double qij(int i, int j, vector intens, ivector qvector, int nstates)
{
    double q; 
    Matrix qmat = Calloc( (nstates)*(nstates), double);
    FillQmatrix(qvector, intens, qmat, nstates);
    q = qmat[MI(i,j,nstates)];
    Free(qmat);
    return q;
}

/* Calculates the whole transition matrix in time t given an intensity matrix */

void Pmat(Matrix pmat, double t, vector intens, int nintens, ivector qvector, int nstates, int exacttimes, 
	  int analyticp, int iso, ivector perm, ivector qperm, int debug)
{
    int i,j,degen=0;
    double pii;
    Matrix qmat = (Matrix) Calloc( (nstates)*(nstates), double);
    FillQmatrix(qvector, intens, qmat, nstates);
    if (exacttimes) { 
	for (i=0; i<nstates; ++i) {
	  pii = exp(t * qmat[MI(i, i, nstates)] );
	  for (j=0; j<nstates; ++j) {
	    pmat[MI(i, j, nstates)] = ( i==j  ?  pii  : pii * qmat[MI(i, j, nstates)] );
	  }
	}
    }
    else {
	if ((iso > 0) && (analyticp))
	    AnalyticP(pmat, t, nstates, iso, perm, qperm, intens, nintens, &degen);
	else 
	    MatrixExp(qmat, nstates, pmat, t, debug, degen);
    }
    /* Floating point fuzz sometimes causes trouble */
    for (i=0; i<nstates; ++i) 
	for (j=0; j<nstates; ++j) {
	    if (pmat[MI(i, j, nstates)] < DBL_EPSILON) pmat[MI(i, j, nstates)] = 0;
	    if (pmat[MI(i, j, nstates)] > 1 - DBL_EPSILON) pmat[MI(i, j, nstates)] = 1;
	}
    Free(qmat);
}

double pijdeath(int r, int s, Matrix pmat, vector intens, ivector qvector, int n)
{
    int j;
    double contrib;
    if (r == s) return 1;  /* absorbing-same absorbing transition has probability 1 */
    else {    /* sum over unobserved state at the previous instant */
	contrib = 0;			
	for (j = 0; j < n; ++j)
	    if (j != s)
		contrib += pmat[MI(r, j, n)] * qij(j, s, intens, qvector, n);	
    }
    return contrib;
}




/***************************************************

 CODE FOR DERIVATIVES OF P MATRIX.  

***************************************************/

/* 
   Derivatives of Q matrix wrt q
   
   With constraints on q
   p is the index of the current distinct intensity parameter being considered
   nc is length of constraint vector, ie number of intensities inc duplicates
   qmat includes duplicates. 
   ic loops over non-distinct intensities in constr
   constr indexed from 1

   diag: - no of times that parameter appears in the current row 
   other: 1 if that parameter appears. 

   for example 4x4 reversible 
   constr =  1 1 1 2 2 3 4
   q with constr =  *  1  *  1 
   1  *  2  2
   *  *  3  4
   *  *  *  *
   consider parameter 1 .   
   DQ =            -2  1  0  1
   1  -1 0  0
   0  0  ...
*/

void FormDQ(Matrix DQ, Matrix qmat, Matrix qbase, int p, int n, ivector qconstr, int np) {
    int i, j, ic=0;
    int found=0; /* found parameter in current row */ 
    /* Loop through entries of result matrix */
    for (i=0; i<n; ++i) {
	found = 0;
	for (j=0; j<n; ++j) {
	    if ((i != j) || ((i==j) && !found))
		DQ[MI(i,j,n)] = 0;
	    if (ic < np) {
		if (qmat[MI(i,j,n)] > 0) { 
		    /* check which distinct intens this one corresponds to */
		    if (qconstr[ic]-1 == p) { /* the pth intensity parameter starting from 0 */
			DQ[MI(i,j,n)] = qmat[MI(i,j,n)] / qbase[MI(i,j,n)];
			DQ[MI(i,i,n)] += -qmat[MI(i,j,n)] / qbase[MI(i,j,n)];
			found = 1;
		    }
		    ++ic;
		}
	    }
	}
    }
}

/* Derivative of Q  with respect to covariate coefficients */

void FormDQCov(Matrix DQ, Matrix qmat, int p, int n, ivector bconstr, ivector wcov, int np, vector x) {
    int i, j, ic=0, found=0; /* found parameter in current row */ 
    /* Loop through entries of result matrix */
    for (i=0; i<n; ++i) {
	found = 0;
	for (j=0; j<n; ++j) {
	    if ((i != j) || ((i==j) && !found))
		DQ[MI(i,j,n)] = 0;
	    if (ic < np) {  /* np is number of (non-distinct, non-zero, non-diagonal) intensity parameters */
		if (qmat[MI(i,j,n)] > 0) { 
		    /* check which distinct intens this one corresponds to */
		    if (bconstr[(wcov[p]-1)*np + ic] - 1 == p) { /* the pth intensity parameter starting from 0 */
			DQ[MI(i,j,n)] = x[wcov[p]-1]*qmat[MI(i,j,n)];
			DQ[MI(i,i,n)] += -x[wcov[p]-1]*qmat[MI(i,j,n)];
			found = 1;
		    }
		    ++ic;
		}
	    }
	}
    }
}

/* Derivs for exact times
   P_rr  =  P =    exp(-(qrs + rest of row r..)*t) 
   P_rs  =  P q =  exp(-(qrs + rest of row r..)*t) qrs 

   WRT qrs: for row r of dP:
   dP/dqrs _ rr  =  -t*P =  - t exp(-(qrs + ..)*t) 
   dP/dqrs _ rs  =  P - t*q*P  =  exp(-(qrs + rest)*t)  - t qrs exp(-(qrs + rest)*t) 
   dP/dqrs _ ru (Pru >0)  =  -t*q*P  =  - t qru exp(-(qrs + rest)*t) 

   for other rows of dP:
   dP/dqrs _ vs = 0
*/

/* 
   With constraints on Q. 

   P_rr  =  P =    exp(-(n*qrs + rest of row r..)*t) 
   P_rs  =  P q =  exp(-(n*qrs + rest of row r..)*t) qrs 

   rr entries: -n*t*P,  where n is no of times qrs appears in row r
   rs entries: P - n*t*q*P.  This appears for each qrs
   ru entries: -n*t*q*P    (other distinct qru in same row)
   vs entries: 0     (other distinct qru in different rows) 

   With covariates.  qrs = qrs0 exp(betars x)
   WRT qrs0: 
   rr entries: -sum(exp(betars x))*t*P
   rs entries: P*exp(betars x) - sum(exp betars x)*t*q*P
   ru entries: -sum(exp betars x)*t*q*P
   vs entries: 0
   WRT betars: 
   rr entries: -sum(x qrs)*t*P
   rs entries: P*x*qrs - sum(x qrs)*t*q*P
   ru entries: -sum(x qrs)*t*q*P
   vs entries: 0
*/

void DPmatEXACT(Array3 dpmat, double t, vector x, Matrix qmat, Matrix qbase, int n, 
		ivector constr, ivector bconstr, ivector wcov, int np, int ndp, int ndc)
{
    int i, j, p, q, dp;
    double pii, dqsum;
    for (dp=0; dp<ndp+ndc; ++dp) {  /* dp indexes distinct pars */
	p = q = 0;                  /* p, q index positive pars in transition matrix */
	for (i=0; i<n; ++i) { /* rows */
	    pii = exp(t * qmat[MI(i, i, n)] );
	    dqsum=0;
	    for (j=0; j<n; ++j) { /* columns */
		if (qmat[MI(i,j,n)] > 0) {
		    if ((dp < ndp) && (constr[p]-1 == dp))
			dqsum += qmat[MI(i,j,n)] / qbase[MI(i,j,n)];
		    else if ((dp >=ndp) && (bconstr[(wcov[dp-ndp]-1)*np + p]-1 == dp-ndp))
			dqsum += x[wcov[dp-ndp]-1] * qmat[MI(i,j,n)];
		    ++p;
		}
	    }
	    for (j=0; j<n; ++j) {
		if (i == j) 
		    dpmat[MI3(i, j, dp, n, n)] = -dqsum*t*pii;
		else if (qmat[MI(i,j,n)] > 0) { 
		    if ((dp < ndp) && (constr[q]-1 == dp))
			dpmat[MI3(i, j, dp, n, n)] = (1 / qbase[MI(i,j,n)] - dqsum*t)*pii*qmat[MI(i,j,n)];
		    else if ((dp >=ndp) && (bconstr[(wcov[dp-ndp]-1)*np + q]-1 == dp-ndp))
			dpmat[MI3(i, j, dp, n, n)] = (x[wcov[dp-ndp]-1] - dqsum*t)*pii*qmat[MI(i,j,n)];			
		    else dpmat[MI3(i, j, dp, n, n)] = - dqsum*t*pii*qmat[MI(i,j,n)];
		    ++q;
		}
		else dpmat[MI3(i, j, dp, n, n)] = 0;
	    }
	}
    }
}

/* Derivative of matrix exponential using a power series approximation

dP(t) / dq   =  sum_s=0^inf  d/dq Q^s t^s / s! 
             =  sum_s=0^inf ( sum_k=0^{s-1} Q^k dQ/dq Q^{s-1-k} )  t^s / s!
Calc: 
at each s need to have stored previous 0..s-1 powers of Q. 

TODO - overflow correction.

*/

void DMatrixExpSeries(Matrix A, Matrix Abase, int n, int np, int ndp, int ndc, 
		      ivector constr, ivector bconstr, ivector wcov, Array3 DexpA, double t, vector x)
{
    int i, j, k, p;
    int order = 20;
    int nsq = n*n;
    vector tpower = Calloc(order+1, double); /* values of t^i / i! */
    Matrix DApower = Calloc(nsq, double); /* cumulative outer sum */
    Array3 Apower = Calloc(nsq*(order+1), double);  /* storage for successive powers of A  */
    Matrix Temp = Calloc(nsq, double); /* workspace  */
    Matrix Inner = Calloc(nsq, double); /* one term of inner sum */
    Matrix CInner = Calloc(nsq, double); /* cumulative inner sum */
    Matrix DA = Calloc(nsq, double); /* workspace for derivative of A  */

    FormIdentity(&Apower[0], n);  /* A to the power 0 is identity */
    tpower[0] = 1;
    for (i=1; i<=order; ++i) {
	/* calculate ith power of A and store it in next nsq entries of Apower.  */
	MultMat(A, &Apower[(i-1)*nsq], n, n, n, &Apower[i*nsq]);
	tpower[i] = tpower[i-1] * t/i;
    }
    for (p=0; p<ndp+ndc; ++p) { 
	if (p < ndp)
	    FormDQ(DA, A, Abase, p, n, constr, np); /* derivative of A WRT pth parameter.  */
	else FormDQCov(DA, A, p-ndp, n, bconstr, wcov, np, x); /* derivative of A WRT pth parameter.  */
	for (k=0; k<nsq; ++k)
	    DexpA[p*nsq + k] =  DA[k]*tpower[1];
	for (i=2; i<=order; ++i) {	 
	    for (k=0; k<nsq; ++k) 
		CInner[k] = 0;
	    for (j=0; j <=(i-1); ++j) {
		MultMat(&Apower[j*nsq], DA, n, n, n, Temp);
		MultMat(Temp, &Apower[(i-1-j)*nsq], n, n, n, Inner);
		for (k=0; k<nsq; ++k)
		    CInner[k] += Inner[k];
	    }
	    for (k=0; k<nsq; ++k)
		DexpA[p*nsq + k] += CInner[k]*tpower[i]; /* Fill in next nsq entries of DexpA with derivative WRT pth parameter.  */
	}
    }
    
    Free(tpower); Free(DApower); Free(Apower); Free(Temp); Free(Inner); Free(CInner); Free(DA);
}

/* Derivs of P(t)_rs wrt every q,   for s death 
   P(t)_rs  =  sum_(k!=s) (P(t)_rk qks)
   dP/dqij  =  sum_(k!=s) d/dqij P(t)_rk qks     
               for j!=s   qij not included in qks's, j not the death state. 
   dP/dqij  =  sum_(k!=s,k!=i) d/dqij P(t)_rk qks  +  P(t)_ri + qij d/dqij P(t)_ri   
               for j = s       qij included in qks's,   j is the death state
   
   e.g. 2 state model r=0, s=1   P(t)_rs = p(t)rr qrs 

*/

void dpijdeath(int r, int s, vector x, Array3 dpmat, Matrix pmat, vector intens, vector oldintens, ivector qvector, 
	       int n, ivector constr, ivector bconstr, int ndp, int ndc, int ncovs, vector dcontrib)
{
    int i, j, k, p=0;
    double dq;
    Matrix qmat = Calloc(n*n, double);
    Matrix qbase = Calloc(n*n, double);
    FillQmatrix(qvector, intens, qmat, n);
    FillQmatrix(qvector, oldintens, qbase, n);
    for (p=0; p<ndp+ndc; ++p) {  /* p indexes distinct pars */
	dcontrib[p] = 0;
	for (k=0; k<n; ++k)
	    if (k != s)
		/* all derivatives have this contribution */
		dcontrib[p] += dpmat[MI3(r, k, p, n, n)] * qij(k, s, intens, qvector, n);
    }
    p=0;
    /* derivatives with respect to baseline intensity pars */
    for (i=0; i<n; ++i) {
	for (j=0; j<n; ++j)  {
	    if (qmat[MI(i,j,n)] > 0) {
		if (j == s) {
		    dq = qmat[MI(i,j,n)] / qbase[MI(i,j,n)];
		    dcontrib[constr[p]-1] += pmat[MI(r, i, n)] * dq;
		}
		++p;  /* p indexes constraint vector */
	    }
	}    
    }
    p=0;
    /* derivatives with respect to covariate coefficients */
    for (k=0; k<ncovs; ++k) {
	for (i=0; i<n; ++i) {
	    for (j=0; j<n; ++j)  {
		if (qmat[MI(i,j,n)] > 0) {
		    if (j == s) {
			dq = x[k] * qmat[MI(i,j,n)];
			dcontrib[ndp+bconstr[p]-1] += pmat[MI(r, i, n)] * dq;
		    }
		    ++p;
		}
	    }
	}
    }
    Free(qmat); Free(qbase);
}

/* Derivatives of P matrix */

void DPmat(Array3 dpmat, double t, vector x, vector intens, vector oldintens, ivector qvector, 
	   int n, int np, int ndp, int ndc, ivector qconstr, ivector bconstr, ivector wcov, int exacttimes)
{
    int i, j, p, err=0;
    double eit, ejt; 
    Matrix DQ = (Matrix) Calloc(n*n, double); /* should initialize to zero */
    vector revals = (vector) Calloc(n, double);
    vector ievals = (vector) Calloc(n, double);
    Matrix evecs = (Matrix) Calloc(n*n, double);
    Matrix evecsinv = (Matrix) Calloc(n*n, double); 
    Matrix work = (Matrix) Calloc(n*n, double);
    Matrix G = (Matrix) Calloc(n*n, double);
    Matrix V = (Matrix) Calloc(n*n, double);
    Matrix qmat = (Matrix) Calloc(n*n, double);
    Matrix qbase = (Matrix) Calloc(n*n, double);

    FillQmatrix(qvector, intens, qmat, n);
    FillQmatrix(qvector, oldintens, qbase, n);
    if (exacttimes) { 
	DPmatEXACT(dpmat, t, x, qmat, qbase, n, qconstr, bconstr, wcov, np, ndp, ndc);
    }
    else {
	Eigen(qmat, n, revals, ievals, evecs, &err);
	if (err > 0) 
	    REprintf("error code %d from EISPACK eigensystem routine rg\n", err);
	if (repeated_entries (revals, n)) {
	    DMatrixExpSeries(qmat, qbase, n, np, ndp, ndc, qconstr, bconstr, wcov, dpmat, t, x);
	}
	else { 
	    MatInv(evecs, evecsinv, n);
	    for (p=0; p<ndp+ndc; ++p) { 
		if (p < ndp) 
		    FormDQ(DQ, qmat, qbase, p, n, qconstr, np);
		else FormDQCov(DQ, qmat, p-ndp, n, bconstr, wcov, np, x);
		MultMat(DQ, evecs, n, n, n, work);
		MultMat(evecsinv, work, n, n, n, G);
		for (i=0; i<n; ++i) {
		    eit = exp(revals[i] * t);
		    for (j=0; j<n; ++j) {
			if (i==j) 
			    V[MI(i,j,n)] = G[MI(i,i,n)] * t * eit;
			else { 
			    ejt = exp(revals[j] * t);
			    V[MI(i,j,n)] = G[MI(i,j,n)] * (eit - ejt) / (revals[i] - revals[j]);
			}
		    }    
		}
		MultMat(V, evecsinv, n, n, n, work);
		MultMat(evecs, work, n, n, n, &(dpmat[MI3(0, 0, p, n, n)]));
	    }
	}
    }
    Free(DQ); Free(revals); Free(ievals); Free(evecs); Free(evecsinv); Free(work); Free(G); Free(V); Free(qmat); Free(qbase);
}
