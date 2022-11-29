#ifndef DIFF_H
#define DIFF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float MaxDiff(float *C, float *C2, int size, int len, int B);

float MaxDiff(float *C, float *C2, int size, int len);

float MaxDiff(float *C, float *C2, int size);

float AvgDiff(float *C, float *C2, int size);

float MinDiff(float *C, float *C2, int size);

float RelMaxDiff(float *C, float *C2, int size);

float RelAvgDiff(float *C, float *C2, int size);

float RelMinDiff(float *C, float *C2, int size);

int PrintDiff(float *C, float *C2, int size, int len);

int PrintDiff(float *C, float *C2, int size, int len, int B, 
              bool minDiff = false, bool v3 = false, bool v3B = false);

int PrintDiffV2(float *C, float *C2, int size, int len);

int PrintDiffV3(float *C, float *C2, int size, int len);

#define PrintDiffV2B(C, C2, size, len, B) PrintDiffV2(C, C2, size, len)

int PrintDiffV3(float *C, float *C2, int size, int len, int B);

#endif