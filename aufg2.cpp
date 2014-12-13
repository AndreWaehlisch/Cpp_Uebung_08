#include <iostream>
#include "bessel.h"
using namespace std;

int main()
{
	Bessjy JY;
	Bessik IK;

	double links, rechts;

	// Gleichung 1
	cout << "Gleichung1" << endl;
	cout << "n  \t\tx\t\trechts\t\tlinks\t\tdiff" << endl;

	for ( int n = 0; n <= 15; n += 5 )
	{
		for ( double x = 0; x <= 10; x += 0.5 )
		{
			links = 2 * n * JY.jn(n, x);
			rechts = x * (JY.jn(n - 1, x) + JY.jn(n + 1, x));

			cout << n << "  " << x << "\t\t" << rechts << "\t\t" << links << "\t\t" << (rechts - links) << endl;
		}
	}

	// Gleichung 2
	cout << "\n\n\nGleichung2" << endl;
	cout << "n  \t\tx\t\trechts\t\tlinks\t\tdiff" << endl;

	for ( int n = 0; n <= 15; n += 5 )
	{
		for ( double x = 0; x <= 10; x += 0.5 )
		{
			links = 2 * n * IK.kn(n, x);
			rechts = x * (IK.kn(n + 1, x) - IK.kn(n - 1, x));

			cout << n << "  " << x << "\t\t" << rechts << "\t\t" << links << "\t\t" << (rechts - links) << endl;
		}
	}

	// Gleichung 3
	cout << "\n\n\nGleichung3" << endl;
	cout << "n  \t\tx\t\trechts\t\tlinks\t\tmitte\t\tdiff" << endl;
	double mitte;

	for ( int n = 0; n <= 15; n += 5 )
	{
		for ( double x = 0; x <= 10; x += 0.5 )
		{
			links = JY.jn(-n, x);
			mitte = pow((-1), n) * JY.jn(n, x);
			rechts = JY.jn(n, -x);

			cout << n << "  " << x << "\t\t" << rechts << "\t\t" << links << "\t\t" << mitte << "\t\t" << (rechts - links) << endl;
		}
	}
}
