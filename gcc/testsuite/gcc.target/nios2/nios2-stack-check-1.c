/* { dg-do compile } */
/* { dg-options "-fstack-limit-register=et" } */
/* { dg-final { scan-assembler "bgeu\\tsp, et" } } */
/* { dg-final { scan-assembler "trap\\t3" } } */
/* check stack checking */
void test()
{
  int a, b, c;
}
