#include "Round.h"

double tstd::Round(double val, int digits)
{
	double places = pow(10.0, digits);
	return round(val * places) / places;
}
