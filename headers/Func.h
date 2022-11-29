#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <math.h>
#include <ctime>
#include <omp.h>
#include <time.h>



#include "elbrusfunctions.h"
#include "elbrusdefines.h"
#include "functions.h"

using namespace std;
/////////////////////////////////////????/////////////////////???///////////
#define GHz         1.2e8
#define GB          1.0e9
#define GBps        1.0e9
#define GiB         1 << 30
#define GiBps       1 << 30
#define nsec        1.0e-9

#define CPU_freq    (1.5 * GHz)  
#define throughput  (76.8 * GBps) 

//#define zeros   (__v2di)((__v4sf){0.0, 0.0, 0.0, 0.0});

#define ZerCore6x8()    p_sum11 = zerosreg;\
                        p_sum12 = zerosreg;\
                        p_sum13 = zerosreg;\
                        p_sum14 = zerosreg;\
                        p_sum15 = zerosreg;\
                        p_sum16 = zerosreg;\
                        p_sum17 = zerosreg;\
                        p_sum18 = zerosreg;\
                        \
                        p_sum21 = zerosreg;\
                        p_sum22 = zerosreg;\
                        p_sum23 = zerosreg;\
                        p_sum24 = zerosreg;\
                        p_sum25 = zerosreg;\
                        p_sum26 = zerosreg;\
                        p_sum27 = zerosreg;\
                        p_sum28 = zerosreg;\
                        \
                        p_sum31 = zerosreg;\
                        p_sum32 = zerosreg;\
                        p_sum33 = zerosreg;\
                        p_sum34 = zerosreg;\
                        p_sum35 = zerosreg;\
                        p_sum36 = zerosreg;\
                        p_sum37 = zerosreg;\
                        p_sum38 = zerosreg;\
                        \
                        p_sum41 = zerosreg;\
                        p_sum42 = zerosreg;\
                        p_sum43 = zerosreg;\
                        p_sum44 = zerosreg;\
                        p_sum45 = zerosreg;\
                        p_sum46 = zerosreg;\
                        p_sum47 = zerosreg;\
                        p_sum48 = zerosreg;\
                        \
                        p_sum51 = zerosreg;\
                        p_sum52 = zerosreg;\
                        p_sum53 = zerosreg;\
                        p_sum54 = zerosreg;\
                        p_sum55 = zerosreg;\
                        p_sum56 = zerosreg;\
                        p_sum57 = zerosreg;\
                        p_sum58 = zerosreg;\
                        \
                        p_sum61 = zerosreg;\
                        p_sum62 = zerosreg;\
                        p_sum63 = zerosreg;\
                        p_sum64 = zerosreg;\
                        p_sum65 = zerosreg;\
                        p_sum66 = zerosreg;\
                        p_sum67 = zerosreg;\
                        p_sum68 = zerosreg;


void Multiply(float* a, float* b, float* c, int M, int N, int K);
void Transpond (float* mass1, float* mass2, int M, int K);
void MultiplyCore(float* a, float* b, float* c, int M, int N, int K);
void MultiplyIntrin(float* a, float* b, float* c, int M, int N, int K);
void MultiplyIntrin_Paralell(float* a, float* b, float* c, int M, int N, int K);
float AvgDeffect (float *a, float *b, int M, int N, int test);
