/* { dg-do run { xfail *-*-* } } */
/* { dg-options "-fmpx -mmpx" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */

#define XFAIL

#include "mpx-check.h"

int rd (int *p, int i)
{
  int res = p[i];
  printf ("%d\n", res);
  return res;
}

int foo (int i, int j)
{
  return rd(&i, j);
}

int mpx_test (int argc, const char **argv)
{
  foo (1, -1);

  return 0;
}
