/* { dg-skip-if "" { *-*-* } { "*" } { "-DACC_MEM_SHARED=0" } } */

int
main (int argc, char *argv[])
{
  int i;

#pragma acc data present_or_copy (i)
#pragma acc data copyout (i)
  ++i;

  return 0;
}

/* { dg-output "Trying to map into device \\\[\[0-9a-fA-FxX\]+..\[0-9a-fA-FxX\]+\\\) object when \\\[\[0-9a-fA-FxX\]+..\[0-9a-fA-FxX\]+\\\) is already mapped" } */
/* { dg-shouldfail "" } */
