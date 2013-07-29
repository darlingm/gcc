/* { dg-do run { xfail *-*-* } } */
/* { dg-options "-fmpx -mmpx" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */
/* { dg-additional-options "-fmpx-narrow-to-innermost-array" } */

#define XFAIL

#include "mpx-check.h"

struct S {
  int arr[100];
} S;

struct S sa[10];

int rd (int *p, int i)
{
  int res = p[i];
  printf ("%d\n", res);
  return res;
}

int mpx_test (int argc, const char **argv)
{
  rd (&sa[argc].arr[0], 100);

  return 0;
}
