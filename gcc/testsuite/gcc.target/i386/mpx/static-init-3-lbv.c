/* { dg-do run { xfail *-*-* } } */
/* { dg-options "-fmpx -mmpx" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */

#define XFAIL

#include "mpx-check.h"

int buf[100];
int *p = buf;

int foo (int i)
{
  static int **pp = &p;

  return (*pp)[i];
}

int mpx_test (int argc, const char *argv[])
{
  printf ("%d\n", foo (-1));

  return 0;
}
