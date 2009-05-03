
typedef double (*hmmfn)(double x, double *pars);
typedef double (*linkfn)(double x);

double hmmCat(double x, double *pars);
double hmmIdent(double x, double *pars);
double hmmUnif(double x, double *pars);
double hmmNorm(double x, double *pars);
double hmmLNorm(double x, double *pars);
double hmmExp(double x, double *pars);
double hmmGamma(double x, double *pars);
double hmmWeibull(double x, double *pars);
double hmmPois(double x, double *pars);
double hmmBinom(double x, double *pars);
double hmmTNorm(double x, double *pars);
double hmmMETNorm(double x, double *pars);
double hmmMEUnif(double x, double *pars);
double hmmNBinom(double x, double *pars);
double hmmBeta(double x, double *pars);
