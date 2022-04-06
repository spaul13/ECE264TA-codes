#include "hw2.h"
double integrate1(Range rng)
{
  double lower = rng.lowerlimit;
  double upper = rng.upperlimit;
  int intvl = rng.intervals;
  double intvlwidth = (upper - lower) / intvl;
  double sum = 0;
  for (int cnt = 0; cnt < intvl; cnt ++)
    {
      sum += func(lower);
	printf("%d,%lf,%lf \n", cnt, lower, sum);
      lower += intvlwidth;
    }
  sum *= intvlwidth;
  return sum;
}

void integrate2(RangeAnswer * rngans)
{
  Range rng;
  rng.lowerlimit = rngans -> rng.lowerlimit;
  rng.upperlimit = rngans -> rng.upperlimit;
  rng.intervals     = rngans -> rng.intervals;
  rngans -> answer = integrate1(rng);
}
