#include <iostream>
#include <iomanip>
#include "bessel.h"
#include "wynn.h"

using namespace std;

class Kapteyn
{
  Bessjy jy;
  double aux;

public:

  double x;
  double sn;
  int n;


    Kapteyn (double X)
  {
    x = X;
    sn = 0.;
    n = 0;
  }

  double operator    () (int j)
  {
    if (j < 1)
      return 0.;
    else
      return partial (j);
  }

  double partial (int j)
  {
    if (j < n)
      sn = 0.;

    for (long i = (j < n ? 0 : n); i < j; i++)
      {
	aux = jy.jn (i, i * x);
	sn += aux * aux * i * i * i * i * i * i;
      }
    n = j;
    return sn;
  }


};

double koeff[6] = { 512, 27776, 161152, 189040, 45820, 1125 };

double
kapteyn_anal (double x)
{
  double nom, denom;
  nom = 0.0;
  for (int i = 6; i >= 0; i--)
    {
      nom += koeff[i];
      nom *= x * x;
    }
  denom = 2048 * pow (1 - x * x, 9.5);

  return nom / denom;
}




int
main ()
{
  const double epsilon = 1e-8;
  const int nmax = 3000;

  //  cout.precision(20);


  cout << "x n n_wynn" << endl;
  for (double x = 0.01; x < 1; x += 0.01)
    {
      int i = 1;
      int n = 0;
      Kapteyn kapt (x);
      double analytical = kapteyn_anal (x);

      while (abs (kapt (i) - analytical) > epsilon && i < nmax)
	i++;

      //Teil b -> Konvergenzbeschleuniger
      Wynn w (nmax, epsilon);
      while (!w.conv && n < nmax)
	{
	  ++n;
	  double part = kapt.partial (n);
	  double wynn = w.next (part);
	}


      cout << x << " " << i << " " << n << endl;
    }

  // Für  x \in { 0.85,0.88,0.89,0.9,0.93,0.94,0.95,0.96,0.97,0.98,0.99 } ergibt sich für epsilon = 1e-8 und nmax = 3000 keine Konvergenz.  Mit Hilfe des Konvergenzbeschleunigers nur für x \in {0.98, 0.99}.  Ferner konvergieren die Partialsummen für ca. n > 13 schneller, wenn der Konvergenzbeschleuniger verwendet wird. 
}
