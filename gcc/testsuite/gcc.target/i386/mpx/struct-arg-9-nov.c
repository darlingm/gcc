/* { dg-do run } */
/* { dg-options "-fmpx -mmpx" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */

#include "mpx-check.h"

struct s1 {
  int *p[2];
} s1;

int rd (struct s1 s, int i)
{
  int res = s.p[1][i];
  printf ("%d\n", res);
  return res;
}

int buf[100];
int buf1[100];

int mpx_test (int argc, const char **argv)
{
  struct s1 s = { {buf, buf1} };

  rd (s, 0);
  rd (s, 99);

  return 0;
}
