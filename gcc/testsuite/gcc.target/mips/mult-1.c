/* For SI->DI widening multiplication we should use DINS to combine the two
   halves.  */
/* { dg-options "-O -mgp64 isa_rev>=2" } */
/* { dg-final { scan-assembler "\tdins\t" } } */
/* { dg-final { scan-assembler-not "\tdsll\t" } } */
/* { dg-final { scan-assembler-not "\tdsrl\t" } } */
/* { dg-final { scan-assembler-not "\tor\t" } } */

NOMIPS16 unsigned long long
f (unsigned int i, unsigned int j)
{
  i++;
  return (unsigned long long) i * j;
}
