// You must modify this file
#include <stdio.h>
#include <stdbool.h>
#include "hw3.h"

// must enclose the function by #ifdef TEST_INTEGRATE 
// and #endif to enable particial credits
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  double lower = intrg -> lowerlimit;
  double upper = intrg -> upperlimit;
  int intvl = intrg -> intervals;
  double intvlwidth = (upper - lower) / intvl;
  funcptr func = intrg -> func;
  double sum = 0;
  for (int cnt = 0; cnt < intvl; cnt ++)
    {
      sum += func(lower);
      lower += intvlwidth;
    }
  sum *= intvlwidth;
  intrg -> answer = sum;
}
#endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE
// and #endif to enable particial credits

#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
{
  FILE * infptr = fopen(infilename, "r");
  if (infptr == NULL)
    {
      fprintf(stderr, "fopen fail\n");
      return false;
    }
  Integration intrg;
  int rtv;
  rtv = fscanf(infptr, "%lf\n", & intrg.lowerlimit);
  if (rtv != 1)
    {
      fclose (infptr);
      return false;
    }
  rtv = fscanf(infptr, "%lf\n", & intrg.upperlimit);
  if (rtv != 1)
    {
      fclose (infptr);
      return false;
    }
  rtv = fscanf(infptr, "%d\n", & intrg.intervals);
  if (rtv != 1)
    {
      fclose (infptr);
      return false;
    }
  fclose (infptr);
  FILE * outfptr = fopen(outfilename, "w");
  if (outfptr == NULL)
    {
      fprintf(stderr, "fopen fail\n");
      return false;
    }
  funcptr funcs[] = {func1, func2, func3, func4, func5};
  int numfunc = sizeof(funcs) / sizeof(funcptr);
  for (int ind = 0; ind < numfunc; ind ++)
    {
      intrg.func = funcs[ind];
      integrate(& intrg);
      double ans = intrg.answer;
      rtv = fprintf(outfptr, "%lf\n", ans);
      if (rtv < 1) // fprintf fails
  {
    fclose (outfptr);
    return false;
  }
    }
  fclose (outfptr);
  return true;
}
#endif // RUN_INTEGRATE
