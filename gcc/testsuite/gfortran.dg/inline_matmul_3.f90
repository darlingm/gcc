! { dg-do  run }
! { dg-options "-O3 -finline-matmul-limit=2 -fdump-tree-optimized" }
! PR 37131 - all calls to matmul should be kept
program main
  real, dimension(3,2) :: a
  real, dimension(2,4) :: b
  real, dimension(3,4) :: c
  real, dimension(3,4) :: cres
  real, dimension(:,:), allocatable :: calloc
  integer :: a1 = size(a,1), a2 = size(a,2)
  integer :: b1 = size(b,1), b2 = size(b,2)
  integer :: c1 = size(c,1), c2 = size(c,2)

  data a / 2.,  -3.,  5.,  -7., 11., -13./
  data b /17., -23., 29., -31., 37., -39., 41., -47./
  data cres /195., -304.,  384.,  275., -428.,  548.,  347., -540.,  692.,  411., -640.,  816./
  c = matmul(a,b)
  if (sum(c-cres)>1e-4) call abort

  calloc = matmul(a,b)
  if (sum(calloc-cres)>1e-4) call abort
  if (any([size(calloc,1), size(calloc,2)] /= [3,4])) call abort
  deallocate(calloc)

  allocate(calloc(4,4))
  calloc = matmul(a,b)
  if (sum(calloc-cres)>1e-4) call abort
  if (any([size(calloc,1), size(calloc,2)] /= [3,4])) call abort
  deallocate(calloc)

  allocate(calloc(3,3))
  calloc = matmul(a,b)
  if (sum(calloc-cres)>1e-4) call abort
  if (any([size(calloc,1), size(calloc,2)] /= [3,4])) call abort
  deallocate(calloc)
  
  block
    real :: aa(a1, a2), bb(b1, b2), cc(c1, c2)
    aa = a
    bb = b

    cc = matmul(aa,bb)
    if (sum(cc-cres)>1e-4) call abort
    calloc = matmul(aa,bb)
    if (sum(calloc-cres)>1e-4) call abort
    if (any([size(calloc,1), size(calloc,2)] /= [3,4])) call abort
    calloc = 42.
    deallocate(calloc)

    allocate(calloc(4,4))
    calloc = matmul(aa,bb)
    if (sum(calloc-cres)>1e-4) call abort
    if (any([size(calloc,1), size(calloc,2)] /= [3,4])) call abort
    deallocate(calloc)

    allocate(calloc(3,3))
    calloc = matmul(aa,bb)
    if (sum(calloc-cres)>1e-4) call abort
    if (any([size(calloc,1), size(calloc,2)] /= [3,4])) call abort
    deallocate(calloc)
  end block

end program main
! { dg-final { scan-tree-dump-times "_gfortran_matmul" 8 "optimized" } }
! { dg-final { cleanup-tree-dump "optimized" } }
