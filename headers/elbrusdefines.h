#ifndef ELBRUSDEFINES_H
#define ELBRUSDEFINES_H

#define adds    __builtin_e2k_qpfadds
#define hadds   __builtin_e2k_qpfhadds
#define subs    __builtin_e2k_qpfsubs
#define hsubs   __builtin_e2k_qpfhsubs
#define addsubs __builtin_e2k_qpfaddsubs
#define maxs    __builtin_e2k_qpfmaxs
#define mins    __builtin_e2k_qpfmins
#define muls    __builtin_e2k_qpfmuls
#define cmpeqs  __builtin_e2k_qpfcmpeqs
#define cmplts  __builtin_e2k_qpfcmplts
#define cmples  __builtin_e2k_qpfcmples
#define cmpuods __builtin_e2k_qpfcmpuods
#define cmpneqs __builtin_e2k_qpfcmpneqs
#define cmpnlts __builtin_e2k_qpfcmpnlts
#define cmpnles __builtin_e2k_qpfcmpnles
#define cmpods  __builtin_e2k_qpfcmpods
#define scales  __builtin_e2k_fscales

#define cmpgts  cmpnles
#define cmpges  cmpnlts

#define and     __builtin_e2k_qpand
#define andn    __builtin_e2k_qpandn
#define or      __builtin_e2k_qpor
#define xor     __builtin_e2k_qpxor

#define broadcast(ptr)  __builtin_ia32_vbroadcastss(ptr)
#define float_reg(x)    (v2uint64_t)__builtin_ia32_vbroadcastss_ps(*(__v4sf*)x)
//#define fillregby(x)    (__v2di)((__v4sf){scales(1, x[0]), scales(1, x[1]), scales(1, x[2]), scales(1, x[3])})
//#define fillregby(x)    (v2uint64_t)__builtin_ia32_vbroadcastss_ps(*(__v4sf*)&x[0])
//#define fillregby(x)    (v2uint64_t)__builtin_ia32_vbroadcastss_ps((__v4sf)x)
//#define fillregby(x)    (v2uint64_t)__builtin_ia32_vbroadcastss_ps(*(__v4sf*)&x)
#define frombc(x)       *(__v2di*)(&(x))

//#define rev_bc(x)       fillregby(1.0 / *(float*)(&x))
#define rev(x)          (__v2di)((__v4sf){1.0 / *(float*)(&x), 1.0 / *(((float*)(&x)) + 1), 1.0 / *(((float*)(&x)) + 2), 1.0 / *(((float*)(&x)) + 3)})
#define rcpps(x)        (__v2di)(__builtin_ia32_rcpps((__v4sf)(x)))
//#define rev(x)          (__v2di)((__v4sf){1.0 / sum1[0], 1.0 / sum1[1], 1.0 / sum1[2], 1.0 / sum1[3]})
//#define rev_bc(x)       fillregby(1.0 / *(float*)(&x))
// #define rev_bc(x)       dsum[0] = 1.0 / *(float*)(&x);\
//                         fillregby(*(__v4sf*)dsum)
//#define divs_bc(x, y)   muls(x, rev_bc(x))

#define zeros                           (__v2di)((__v4sf){0.0, 0.0, 0.0, 0.0})
#define ones                            (__v2di)((__v4sf){1.0, 1.0, 1.0, 1.0})
#define float4(x)                       (__v2di)((__v4sf){x, x, x, x})
#define regfrom(x1, x2, x3, x4)         (__v2di)((__v4sf){x1, x2, x3, x4})
#define regfromarr(x)                   (__v2di)((__v4sf)x)
#define regfromarr2(x)                  (__v2di)((__v4sf){x[0], x[1], x[2], x[3]})
#define regfrom4arrs(x1, x2, x3, x4, i) (__v2di)((__v4sf){x1[i], x2[i], x3[i], x4[i]})
#define regfrom4regs(x1, x2, x3, x4, i) (__v2di)((__v4sf){*(((float*)(&x1)) + i), *(((float*)(&x2)) + i), *(((float*)(&x3)) + i), *(((float*)(&x4)) + i)})
#define regfrom4regs0(x1, x2, x3, x4)   (__v2di)((__v4sf){*(float*)(&x1), *(float*)(&x2), *(float*)(&x3), *(float*)(&x4)})
//#define regfrombcregs(x1, x2, x3, x4)   regfrom4regs(x1, x2, x3, x4, 0) 
#define regfrombcregs(x1, x2, x3, x4)   regfrom4regs0(x1, x2, x3, x4) 
#define addr(ptr)                       *((__v2di*)(ptr))

#define addaddr(x, ptr)             adds(x, addr(ptr))
#define muladds(a, b, c)            adds(muls(a, b), c)
#define hadds4(a, b, c, d)          hadds(hadds(a, b), hadds(c, d))
#define hadds4bias(a, b, c, d, e)   adds(hadds4(a, b, c, d), e)
#define haddsreg(x)                 hadds4(x, zerosreg, zerosreg, zerosreg)
#define haddsfullreg(x)             hadds4(x, x, x, x)
#define relu(x)                     maxs(zerosreg, x)
#define bitmaskcmpnlts0(x)          cmpnlts(x, zerosreg)
#define bitmaskcmplts0(x)           cmplts(x, zerosreg)
#define bitmaskcmplts0f(x)          cmplts(zerosreg, x)
#define bitmaskcmpnles0(x)          cmpnles(x, zerosreg)
#define invbitmask(x)               subs(onesreg, x)
#define drelu(x, y)                 muls(x, invbitmask(bitmaskcmplts0(y)))

#define intpart(x)                  __builtin_e2k_qpfstoifs(_TOIF_RC_ZERO, x)
#define fracpart(x)                 subs(x, intpart(x))
//#define powof2(x)                   scales(1, x)
//#define powof2(x)                   (__v2di)((__v4sf){scales(1, x[0]), scales(1, x[1]), scales(1, x[2]), scales(1, x[3])})
//#define powof2(x)                   (__v2di)((__v4sf){1 << x[0], 1 << x[1], 1 << x[2], 1 << x[3]})
//#define powof2(x)                   (__v2di)((__v4sf){1 << *(float*)(&x), 1 << *(((float*)(&x)) + 1), 1 << *(((float*)(&x)) + 2), 1 << *(((float*)(&x)) + 3)})
#define powof2(x)                   (__v2di)((__v4sf){1 << (int)*(float*)(&x), 1 << (int)*(((float*)(&x)) + 1), 1 << (int)*(((float*)(&x)) + 2), 1 << (int)*(((float*)(&x)) + 3)})
#define pow2(x)                     scales(1, x)
#define intpowof2(x)                powof2(intpart(x))
#define powof2_2m_p3(x)             muladds(x, muladds(x, muladds(x, p3, p2), p1), p0)
#define exp_if(xi, xf)              muls(powof2(xi), powof2_2m(xf))

typedef unsigned long long vuint64_t;
typedef unsigned long long uint64b;
typedef __attribute((vector_size(16))) long long v2uint64_t;
typedef __attribute((vector_size(16))) long long* v2uint64_t_ptr;

#define clrpartsums6x8()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                            partsum13 = zerosreg;\
                            partsum14 = zerosreg;\
                            partsum15 = zerosreg;\
                            partsum16 = zerosreg;\
                            partsum17 = zerosreg;\
                            partsum18 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                            partsum23 = zerosreg;\
                            partsum24 = zerosreg;\
                            partsum25 = zerosreg;\
                            partsum26 = zerosreg;\
                            partsum27 = zerosreg;\
                            partsum28 = zerosreg;\
                                                 \
                            partsum31 = zerosreg;\
                            partsum32 = zerosreg;\
                            partsum33 = zerosreg;\
                            partsum34 = zerosreg;\
                            partsum35 = zerosreg;\
                            partsum36 = zerosreg;\
                            partsum37 = zerosreg;\
                            partsum38 = zerosreg;\
                                                 \
                            partsum41 = zerosreg;\
                            partsum42 = zerosreg;\
                            partsum43 = zerosreg;\
                            partsum44 = zerosreg;\
                            partsum45 = zerosreg;\
                            partsum46 = zerosreg;\
                            partsum47 = zerosreg;\
                            partsum48 = zerosreg;\
                                                 \
                            partsum51 = zerosreg;\
                            partsum52 = zerosreg;\
                            partsum53 = zerosreg;\
                            partsum54 = zerosreg;\
                            partsum55 = zerosreg;\
                            partsum56 = zerosreg;\
                            partsum57 = zerosreg;\
                            partsum58 = zerosreg;\
                                                 \
                            partsum61 = zerosreg;\
                            partsum62 = zerosreg;\
                            partsum63 = zerosreg;\
                            partsum64 = zerosreg;\
                            partsum65 = zerosreg;\
                            partsum66 = zerosreg;\
                            partsum67 = zerosreg;\
                            partsum68 = zerosreg

#define clrpartsums4x8()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                            partsum13 = zerosreg;\
                            partsum14 = zerosreg;\
                            partsum15 = zerosreg;\
                            partsum16 = zerosreg;\
                            partsum17 = zerosreg;\
                            partsum18 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                            partsum23 = zerosreg;\
                            partsum24 = zerosreg;\
                            partsum25 = zerosreg;\
                            partsum26 = zerosreg;\
                            partsum27 = zerosreg;\
                            partsum28 = zerosreg;\
                                                 \
                            partsum31 = zerosreg;\
                            partsum32 = zerosreg;\
                            partsum33 = zerosreg;\
                            partsum34 = zerosreg;\
                            partsum35 = zerosreg;\
                            partsum36 = zerosreg;\
                            partsum37 = zerosreg;\
                            partsum38 = zerosreg;\
                                                 \
                            partsum41 = zerosreg;\
                            partsum42 = zerosreg;\
                            partsum43 = zerosreg;\
                            partsum44 = zerosreg;\
                            partsum45 = zerosreg;\
                            partsum46 = zerosreg;\
                            partsum47 = zerosreg;\
                            partsum48 = zerosreg

#define clrpartsums2x8()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                            partsum13 = zerosreg;\
                            partsum14 = zerosreg;\
                            partsum15 = zerosreg;\
                            partsum16 = zerosreg;\
                            partsum17 = zerosreg;\
                            partsum18 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                            partsum23 = zerosreg;\
                            partsum24 = zerosreg;\
                            partsum25 = zerosreg;\
                            partsum26 = zerosreg;\
                            partsum27 = zerosreg;\
                            partsum28 = zerosreg

#define clrpartsums1x8()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                            partsum13 = zerosreg;\
                            partsum14 = zerosreg;\
                            partsum15 = zerosreg;\
                            partsum16 = zerosreg;\
                            partsum17 = zerosreg;\
                            partsum18 = zerosreg

#define clrpartsums6x2()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                                                 \
                            partsum31 = zerosreg;\
                            partsum32 = zerosreg;\
                                                 \
                            partsum41 = zerosreg;\
                            partsum42 = zerosreg;\
                                                 \
                            partsum51 = zerosreg;\
                            partsum52 = zerosreg;\
                                                 \
                            partsum61 = zerosreg;\
                            partsum62 = zerosreg

#define clrpartsums8x2()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                                                 \
                            partsum31 = zerosreg;\
                            partsum32 = zerosreg;\
                                                 \
                            partsum41 = zerosreg;\
                            partsum42 = zerosreg;\
                                                 \
                            partsum51 = zerosreg;\
                            partsum52 = zerosreg;\
                                                 \
                            partsum61 = zerosreg;\
                            partsum62 = zerosreg;\
                                                 \
                            partsum71 = zerosreg;\
                            partsum72 = zerosreg;\
                                                 \
                            partsum81 = zerosreg;\
                            partsum82 = zerosreg

#define clrpartsums8x4()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                            partsum13 = zerosreg;\
                            partsum14 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                            partsum23 = zerosreg;\
                            partsum24 = zerosreg;\
                                                 \
                            partsum31 = zerosreg;\
                            partsum32 = zerosreg;\
                            partsum33 = zerosreg;\
                            partsum34 = zerosreg;\
                                                 \
                            partsum41 = zerosreg;\
                            partsum42 = zerosreg;\
                            partsum43 = zerosreg;\
                            partsum44 = zerosreg;\
                                                 \
                            partsum51 = zerosreg;\
                            partsum52 = zerosreg;\
                            partsum53 = zerosreg;\
                            partsum54 = zerosreg;\
                                                 \
                            partsum61 = zerosreg;\
                            partsum62 = zerosreg;\
                            partsum63 = zerosreg;\
                            partsum64 = zerosreg;\
                                                 \
                            partsum71 = zerosreg;\
                            partsum72 = zerosreg;\
                            partsum73 = zerosreg;\
                            partsum74 = zerosreg;\
                                                 \
                            partsum81 = zerosreg;\
                            partsum82 = zerosreg;\
                            partsum83 = zerosreg;\
                            partsum84 = zerosreg

#define clrpartsums8x6()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                            partsum13 = zerosreg;\
                            partsum14 = zerosreg;\
                            partsum15 = zerosreg;\
                            partsum16 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                            partsum23 = zerosreg;\
                            partsum24 = zerosreg;\
                            partsum25 = zerosreg;\
                            partsum26 = zerosreg;\
                                                 \
                            partsum31 = zerosreg;\
                            partsum32 = zerosreg;\
                            partsum33 = zerosreg;\
                            partsum34 = zerosreg;\
                            partsum35 = zerosreg;\
                            partsum36 = zerosreg;\
                                                 \
                            partsum41 = zerosreg;\
                            partsum42 = zerosreg;\
                            partsum43 = zerosreg;\
                            partsum44 = zerosreg;\
                            partsum45 = zerosreg;\
                            partsum46 = zerosreg;\
                                                 \
                            partsum51 = zerosreg;\
                            partsum52 = zerosreg;\
                            partsum53 = zerosreg;\
                            partsum54 = zerosreg;\
                            partsum55 = zerosreg;\
                            partsum56 = zerosreg;\
                                                 \
                            partsum61 = zerosreg;\
                            partsum62 = zerosreg;\
                            partsum63 = zerosreg;\
                            partsum64 = zerosreg;\
                            partsum65 = zerosreg;\
                            partsum66 = zerosreg;\
                                                 \
                            partsum71 = zerosreg;\
                            partsum72 = zerosreg;\
                            partsum73 = zerosreg;\
                            partsum74 = zerosreg;\
                            partsum75 = zerosreg;\
                            partsum76 = zerosreg;\
                                                 \
                            partsum81 = zerosreg;\
                            partsum82 = zerosreg;\
                            partsum83 = zerosreg;\
                            partsum84 = zerosreg;\
                            partsum85 = zerosreg;\
                            partsum86 = zerosreg

#define clrpartsums8x8()    partsum11 = zerosreg;\
                            partsum12 = zerosreg;\
                            partsum13 = zerosreg;\
                            partsum14 = zerosreg;\
                            partsum15 = zerosreg;\
                            partsum16 = zerosreg;\
                            partsum17 = zerosreg;\
                            partsum18 = zerosreg;\
                                                 \
                            partsum21 = zerosreg;\
                            partsum22 = zerosreg;\
                            partsum23 = zerosreg;\
                            partsum24 = zerosreg;\
                            partsum25 = zerosreg;\
                            partsum26 = zerosreg;\
                            partsum27 = zerosreg;\
                            partsum28 = zerosreg;\
                                                 \
                            partsum31 = zerosreg;\
                            partsum32 = zerosreg;\
                            partsum33 = zerosreg;\
                            partsum34 = zerosreg;\
                            partsum35 = zerosreg;\
                            partsum36 = zerosreg;\
                            partsum37 = zerosreg;\
                            partsum38 = zerosreg;\
                                                 \
                            partsum41 = zerosreg;\
                            partsum42 = zerosreg;\
                            partsum43 = zerosreg;\
                            partsum44 = zerosreg;\
                            partsum45 = zerosreg;\
                            partsum46 = zerosreg;\
                            partsum47 = zerosreg;\
                            partsum48 = zerosreg;\
                                                 \
                            partsum51 = zerosreg;\
                            partsum52 = zerosreg;\
                            partsum53 = zerosreg;\
                            partsum54 = zerosreg;\
                            partsum55 = zerosreg;\
                            partsum56 = zerosreg;\
                            partsum57 = zerosreg;\
                            partsum58 = zerosreg;\
                                                 \
                            partsum61 = zerosreg;\
                            partsum62 = zerosreg;\
                            partsum63 = zerosreg;\
                            partsum64 = zerosreg;\
                            partsum65 = zerosreg;\
                            partsum66 = zerosreg;\
                            partsum67 = zerosreg;\
                            partsum68 = zerosreg;\
                                                 \
                            partsum71 = zerosreg;\
                            partsum72 = zerosreg;\
                            partsum73 = zerosreg;\
                            partsum74 = zerosreg;\
                            partsum75 = zerosreg;\
                            partsum76 = zerosreg;\
                            partsum77 = zerosreg;\
                            partsum78 = zerosreg;\
                                                 \
                            partsum81 = zerosreg;\
                            partsum82 = zerosreg;\
                            partsum83 = zerosreg;\
                            partsum84 = zerosreg;\
                            partsum85 = zerosreg;\
                            partsum86 = zerosreg;\
                            partsum87 = zerosreg;\
                            partsum88 = zerosreg

#endif