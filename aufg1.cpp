#include <iostream>
#include <cmath>
#include <fstream>
#include "helfer.h"
#include "pade.h"
using namespace std;

class F
{
public:

  inline double operator     () (const double x)
  {
    return pow (7. + pow (1. + x, 4. / 3.), 1. / 3.);
  }
};

class Taylor
{
public:

  VecDoub V;			// Koeffizienten der Entwicklung
  int N;			// Anzahl der Koeffizienten

    Taylor (VecDoub v, const int n)
  {
    V = v;
    N = n;
  }

  double operator     () (const double x, int n)
  {
    if (n > N || n < 1)
      {
	n = N;			// Mehr Koeffizienten angefordert als wir zur Verfügung haben
      }

    double result = V[n - 1];

    for (int i = n - 2; i >= 0; --i)
      {
	result *= x;
	result += V[i];
      }

    return result;
  }
};

int
main ()
{
  F testfunc;			// eigentliche Funktion
  const double a0 = testfunc (0.);	// Nullter Koeffizient der Taylor-Entwicklung
  const int length = 5;		// Ordnung der Taylor-Entwicklung
  const double coeff[length] = { a0, 1. / 9., 1. / 81., -49. / 8748., 175. / 78732. };	// Taylor-Koeffizienten
  VecDoub init (length, coeff);	// Taylor-Koeffizienten als Vektor Objekt
  Taylor myTaylor (init, length);	// Taylor-Entwicklung

  Pade myPade (init);

  ofstream file ("aufg1.txt", ios::trunc);

  for (int i = 0; i <= 1000; i++)
    {
      const double x = i / 100.;
      file << x << '\t' << myTaylor (x, length) << '\t' << testfunc (x) << '\t' << myPade (x) << endl;
    }

  file.close ();

  cout << "0 <= x <= 10" << endl;
  cout << "Taylor-Approximation, Funktionswerte und Pade-Approximation in aufg1.txt geschrieben" << endl;


  // Die Taylor-Approximation (hier in 5. Ord) weicht für x>1 stark von der originalen Funktion ab, wie sich auch vermuten ließe, da sie ja für den Entwicklungspunkt x=0 bestimmt wurde. Der Pade-Algorithmus approximiert hingegen die Funktion über das gesamte betrachte Intervall sehr gut. Ist hier also zu bevorzugen.
}
