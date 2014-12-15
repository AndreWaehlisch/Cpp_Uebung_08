#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class DawsonF
{
  static const double c1osqrtpi = 0.564189583547756286948079451560;
  static const double taylor[4];

  double h, x0, xs, exph, f3;
  int n, n0;

public:
    DawsonF (double H, int N)
  {
    h = H;
    n = N % 2 ? N : N - 1;
    exph = exp (-h * h);
  }

  double operator   () (double x)
  {
    //    cout << x << "\t" << x/h << "\t" << aux << "\t" <<  n0 << endl; 
    if (abs (x) < 0.2)
      return eval_taylor (x);
    else
      return eval (x);
  }

  double eval (double x)
  {
    double aux1 = 0.;
    int aux2;

    aux2 = (int) (x / h);
    n0 = aux2 % 2 ? aux2 + 1 : aux2;
    x0 = n0 * h;
    xs = x - x0;

    for (int i = 1; i <= n; i += 2)
      {
	f3 = pow (exp (2 * xs * h), i);
	aux1 += (1. / (-i + n0) * 1 / f3 + 1. / (i + n0) * f3) * pow (exph, i * i);
      }
    return c1osqrtpi * exp (-xs * xs) * aux1;
  }

  double eval_taylor (double x)
  {
    double aux = taylor[3];

    for (int i = 2; i >= 0; i--)
      {
	aux *= x * x;
	aux += taylor[i];
      }

    return aux * x;
  }


};

const double
DawsonF::taylor[] = { 1., -2. / 3., 4. / 15., -8. / 105. };


int
main ()
{
  int
    k = 0;
  const double
    epsilon = 1e-9;
  DawsonF
  d (0.4, 11);
  ofstream
  file ("aufg3.txt", ios::trunc);

  for (double x = -10; x < 10; x += 0.01)
    {
      file << x << "\t" << d (x) << endl;
    }

  for (double x = -10; x <= 0; x += 0.01)
    {
      if (d (-x) + d (x) > epsilon)
	k = 1;
    }

  if (k)
    cout << "Die Funktion ist auf dem Intervall [-10,0] nicht punktsymmetrisch mit einer Genauigkeit < " << epsilon << "." << endl;
  else
    cout << "Die Funktion ist auf dem Intervall [-10,0] punktsymmetrisch mit einer Genauigkeit < " << epsilon << "." << endl;

  //Die Funktion ist mit einer Genauigkeit < 1e-9 punktsymmetrisch auf dem Intervall [-10,0] ( unter der gewählten Schrittweite). 


  file.close ();
}
