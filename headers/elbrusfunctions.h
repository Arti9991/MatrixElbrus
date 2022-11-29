#ifndef ELBRUSFUNCTIONS_H
#define ELBRUSFUNCTIONS_H

#include <e2kintrin.h>
#include <stdio.h>
#include <omp.h>

#include "functions.h"
#include "elbrusdefines.h"

int ElbrusMatrixMul(float *inp, float *wts, float *out, long Q, long L, long F);

int ElbrusMatrixMulParallel(float *inp, float *wts, float *out, long Q, long L, long F);

int ElbrusMatrixMulBias(float *inp, float *wts, float *bias, float *out, long Q, long L, long F);

#define Conv1x1Bias(inp, wts, bias, out, Q, L, F) ElbrusMatrixMulBias(inp, wts, bias, out, Q, L, F)

int ElbrusMatrixReLU(float *inp, float *out, long Q, long F);

int ElbrusMatrixMulRelu(float *inp, float *wts, float *bias, float *out, long Q, long L, long F);

#define Conv1x1(inp, wts, bias, out, Q, L, F) ElbrusMatrixMulRelu(inp, wts, bias, out, Q, L, F)

int ElbrusMatrixMulReluD(float *inp, float *wts, float *bias, float *D, float *out, long Q, long L, long F);

#define Conv1x1D(inp, wts, bias, D, out, Q, L, F) ElbrusMatrixMulReluD(inp, wts, bias, D, out, Q, L, F)

int Conv3x3(float *inp, float *wts, float *bias, float *out, 
            long Q, long L, long F, 
            long X, long Xout, long Yout, 
            long Rx, long Ry, 
            long Qout);

int ElbrusMatrixAdd(float *inp1, float *inp2, float *out, long Q, long F);

int ElbrusMatrixSub(float *inp1, float *inp2, float *out, long Q, long F);

int ElbrusMatrixDReLU(float *inp, float *D, float *out, long Q, long F);

int ElbrusMatrixCopy(float *inp, float *out, long Q, long F);

int Elbrusdldbias(float *inp, float *out, long Q, long F);

#define BackwardsStrokeElbrusVerify(dLdout, D, wtst, Q, L, F, dLdD, dLdinp) ElbrusMatrixDReLU(dLdout, D, dLdD, Q, F);\
                                                                            ElbrusMatrixMulParallel(dLdD, wtst, dLdinp, Q, F, L)

#define GradientElbrusVerify(dLdout, D, inpt, Q, L, F, dLdD, dLdwts, dLdbias) ElbrusMatrixDReLU(dLdout, D, dLdD, Q, F);\
                                                                              Elbrusdldbias(dLdD, dLdbias, Q, F);\
                                                                              ElbrusMatrixMulParallel(inpt, dLdD, dLdwts, L, Q, F)

// int BackwardsStrokeGradient_(float *dLdout, float *D, float *inpt, float *wtst, 
//                              long Q, long L, long F,
//                              float *dLdbias, float *dLdwts, float *dLdinp);

// int BackwardsStroke_(float *dLdout, float *D, float *wtst, 
//                      long Q, long L, long F, 
//                      float *dLdD, float *dLdinp);

int BackwardsStroke(float *dLdout, float *D, float *wtst, float *dLdD, float *dLdinp, long Q, long L, long F);

int Gradient(float *inpt, float *dLdD, float *dLdbias, float *dLdwts, long Q, long L, long F); 

#endif