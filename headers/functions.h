#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _OPENMP
    #include <omp.h>
#endif

#include "diff.h"

#define p2(x) 1 << x
#define p8(x) 1 << (3 * x)

#define ToDouble(x) static_cast<double>(x)

#define CPU_freq    (1.5 * GHz)  
#define throughput  (76.8 * GBps)  

#define initby1(x)  if (!x) x = 1
#define assign1(x)  x = !x ? 1 : x

#define v_conv1_forward(inp, wts, bias, out, Q, L, F) \
        v_conv_forward(inp, wts, bias, out, 1, Q, 1, Q, 1, L, F, 1, 1, 1, 0, 0)

#define v_conv1_backward(dLdinp, wts, dLdD, Q, L, F) \
        v_conv_backward(dLdinp, wts, dLdD, 1, Q, 1, Q, 1, L, F, 1, 1, 1, 0, 0)

#define v_conv1_backwardBXY(dLdinp, wts, dLdD, B, X, Y, L, F) \
        v_conv_backward(dLdinp, wts, dLdD, B, X, Y, X, Y, L, F, 1, 1, 1, 0, 0)

#define v_conv1_gradient(inp, dLdwts, dLdbias, dLdD, Q, L, F) \
        v_conv_gradient(inp, dLdwts, dLdbias, dLdD, 1, Q, 1, Q, 1, L, F, 1, 1, 1, 0, 0)

#define v_conv1_gradientBXY(inp, dLdwts, dLdbias, dLdD, B, X, Y, L, F) \
        v_conv_gradient(inp, dLdwts, dLdbias, dLdD, B, X, Y, X, Y, L, F, 1, 1, 1, 0, 0)

#define v_softmax_forward_size(inp, out, size, L) \
        v_softmax_forward(inp, out, size, 1, 1, L)

timespec diff(timespec start, timespec end);

double GetEfficiency(timespec tdiff, double t_ideal);

int BackwardsStrokeGradientVerify(float *dLdout, float *D, float *wtst, float *inpt,
                                  long Q, long L, long F, 
                                  float *dLdD, float *dLdbias, float *dLdinp, float *dLdwts);

int BackwardsStrokeVerify(float *dLdout, float *D, float *wtst, 
                          long Q, long L, long F, 
                          float *dLdD, float *dLdbias, float *dLdinp);

int MatrixCopy(float *src, float *dst, int size);

int MatrixCopyParallel(float *src, float *dst, int size);

int MatrixSub(float *inp1, float *inp2, float *out, int size);

int ElbrusMatrixMulVerify(float *inp, float *wts, float* out, int Q, int L, int F);

int ElbrusMatrixMulReluVerify(float *inp, float *wts, float *bias, float* out, int Q, int L, int F);

#define Conv1x1Verify(inp, wts, bias, out, Q, L, F) \
        ElbrusMatrixMulReluVerify(inp, wts, bias, out, Q, L, F)

int ElbrusConvVefify(float *inp, float *wts, float *bias, float *out, 
                     int X, int Y, int L, int F, int Rx, int Ry, int Xout, int Yout);

int MatrixTranspose(float *M, float *Mt, int lines, int cols);

int MatrixTransposeB(float *M, float *Mt, int lines, int cols, int B);

int MatrixTransposeTime(float *M, float *Mt, long lines, long cols);

int MatrixMul(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixMul1(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixMulTest(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int is_cmp(const char* s1, const char* s2);

int compare(const char* s1, const char* s2);

#endif

