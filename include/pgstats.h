
#include <math.h>
#include <gsl/gsl_sf_gamma.h>

double wattersons_theta(int nsam, int segsites, double a1 = 0) {

  if (a1 == 0) {
    int i;
    for (i = nsam - 1; i >= 1; i--)
        a1 += 1. / i;
  }

  double thetaW = segsites / a1;

  return thetaW;
}


double tajimas_theta(int nsam, int pi) {

  double tajpi;
  double choose;

  choose = gsl_sf_choose(nsam, 2);
  tajpi = pi / choose;
  
  return tajpi;
}

//double zengs_theta(int nsam, 


double tajimasD(int nsam, int s, double tw, double pi, double a1 = 0, double a2 = 0) {
  
  int i;
  double d;
  double V;
  double b1;
  double b2;
  double c1;
  double c2;
  double e1;
  double e2;
  double tajd;
  
  if (a1 == 0 || a2 == 0) {
    for (i = nsam - 1; i >= 1; i--) {
      a1 += 1. / i;
      a2 += 1. / (i * i);
    }
  }
  
  d = pi - tw;
    
  b1 = (nsam + 1.) / (3. * (nsam - 1.));
  b2 = 2. * (nsam * nsam + nsam + 3.) / (9. * nsam * (nsam - 1.));
  c1 = b1 - 1. / a1;
  c2 = b2 - (nsam + 2.) / (a1 * nsam) + a2 / (a1 * a1);
  e1 = c1 / a1;
  e2 = c2 / (a1 * a1 + a2);
  V = e1 * s + e2 * s * (s - 1.);
  
  tajd = d / sqrt(V);

  return tajd;
}
