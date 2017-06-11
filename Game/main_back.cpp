#include <stdio.h>
#include <stdlib.h>
#include <algorithm>    // For max()
#include <cuda.h>
#include <cuda_runtime.h>

extern "C"
// {
// int saxpy(int n, float a, float *x, float *y);
void launchCuda();
// }

int main(void)
{
  launchCuda();
}
