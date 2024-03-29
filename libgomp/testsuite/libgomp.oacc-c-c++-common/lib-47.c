/* { dg-do run } */

#include <string.h>
#include <stdlib.h>
#include <openacc.h>

int
main (int argc, char **argv)
{
  const int N = 256;
  int i;
  unsigned char *h;
  void *d;

  h = (unsigned char *) malloc (N);

  for (i = 0; i < N; i++)
    {
      h[i] = i;
    }

  d = acc_copyin (h, N);
  if (!d)
    abort ();

  memset (&h[0], 0, N);

  acc_update_self (0, N);

  for (i = 0; i < N; i++)
    {
      if (h[i] != i)
	abort ();
    }

  acc_delete (h, N);

  free (h);

  return 0;
}

/* { dg-output "\\\[\[^\n\r]*,256\\\] is not mapped" } */
/* { dg-shouldfail "" } */
