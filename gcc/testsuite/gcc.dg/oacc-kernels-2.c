/* { dg-do compile } */
/* { dg-require-effective-target fopenacc } */
/* { dg-options "-fopenacc -ftree-parallelize-loops=32 -O2 -std=c99 -fdump-tree-parloops_oacc_kernels-all -fdump-tree-copyrename" } */

#include <stdlib.h>
#include <stdio.h>

#define N (1024 * 512)
#define N_REF 4293394432

#if 1
#define COUNTERTYPE unsigned int
#else
#define COUNTERTYPE int
#endif

int
main (void)
{
  unsigned int i;

  unsigned int *__restrict a;
  unsigned int *__restrict b;
  unsigned int *__restrict c;

  a = malloc (N * sizeof (unsigned int));
  b = malloc (N * sizeof (unsigned int));
  c = malloc (N * sizeof (unsigned int));


#pragma acc kernels pcopyin(a[0:N], b[0:N]) pcopyout(c[0:N])
  {
  for (COUNTERTYPE i = 0; i < N; i++)
    a[i] = i * 2;
  }

#pragma acc kernels pcopyin(a[0:N], b[0:N]) pcopyout(c[0:N])
  {
  for (COUNTERTYPE i = 0; i < N; i++)
    b[i] = i * 4;
  }

#pragma acc kernels pcopyin(a[0:N], b[0:N]) pcopyout(c[0:N])
  {
    for (COUNTERTYPE ii = 0; ii < N; ii++)
      c[ii] = a[ii] + b[ii];
  }

  {
    unsigned int sum = 0;

    for (COUNTERTYPE i = 0; i < N; i++)
      sum += c[i];

  printf ("sum: %u\n", sum);

  if (sum != N_REF)
    abort ();
  }

  free (a);
  free (b);
  free (c);

  return 0;
}

/* Check that only one loop is analyzed, and that it can be parallelized.  */
/* { dg-final { scan-tree-dump-times "SUCCESS: may be parallelized" 3 "parloops_oacc_kernels" } } */
/* { dg-final { scan-tree-dump-not "FAILED:" "parloops_oacc_kernels" } } */

/* Check that the loop has been split off into a function. It pops up first in
   all_passes/pass_all_optimizations/pass_rename_ssa_copies .*/
/* { dg-final { scan-tree-dump-times "Function main._omp_fn.0 " 1 "copyrename2" } } */
/* { dg-final { scan-tree-dump-times "Function main._omp_fn.1 " 1 "copyrename2" } } */
/* { dg-final { scan-tree-dump-times "Function main._omp_fn.2 " 1 "copyrename2" } } */

/* { dg-final { cleanup-tree-dump "parloops_oacc_kernels" } } */
/* { dg-final { cleanup-tree-dump "copyrename*" } } */
