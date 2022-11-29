/* Copyright (c) 2008-2018 ZAO "MCST". All rights reserved. */

#ifndef _E2KBUILTIN_H
#define _E2KBUILTIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <e2kintrin.h>

/* Internal data types for implementing the builtins */
typedef char __v32qi __attribute__ ((__vector_size__ (32)));
typedef unsigned char __v32qu __attribute__ ((__vector_size__ (32)));
typedef short __v16hi __attribute__ ((__vector_size__ (32)));
typedef unsigned short __v16hu __attribute__ ((__vector_size__ (32)));
typedef int __v8si __attribute__ ((__vector_size__ (32)));
typedef unsigned int __v8su __attribute__ ((__vector_size__ (32)));
typedef long long __v4di __attribute__ ((__vector_size__ (32)));
typedef unsigned long long __v4du __attribute__ ((__vector_size__ (32)));
typedef float __v8sf __attribute__ ((__vector_size__ (32)));
typedef double __v4df __attribute__ ((__vector_size__ (32)));

typedef union {
    struct {
        double d0, d1, d2, d3;
    } d;
    struct {
        unsigned long long l0, l1, l2, l3;
    } l;
    struct {
        int i0, i1, i2, i3, i4, i5, i6, i7;
    } i;
    struct {
        float f0, f1, f2, f3, f4, f5, f6, f7;
    } f;
    struct {
        short h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12, h13, h14, h15;
    } h;
    struct {
        char c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15,
             c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28, c29, c30, c31;
    } c;
    struct {
        type_union_128 u0, u1;
    } u128;
    char __v32qi __attribute__ ((__vector_size__ (32)));
    short __v16hi __attribute__ ((__vector_size__ (32)));
    int __v8si __attribute__ ((__vector_size__ (32)));
    long long __v4di __attribute__ ((__vector_size__ (32)));
    float __v8sf __attribute__ ((__vector_size__ (32)));
    double __v4df __attribute__ ((__vector_size__ (32)));
    struct {
        __v16qi v0, v1;
    } u__v32qi;
    struct {
        __v8hi v0, v1;
    } u__v16hi;
    struct {
        __v4si v0, v1;
    } u__v8si;
    struct {
        __v2di v0, v1;
    } u__v4di;
    struct {
        __v4sf v0, v1;
    } u__v8sf;
    struct {
        __v2df v0, v1;
    } u__v4df;
} __attribute__ ((__may_alias__)) type_union_256;


/* Define the default attributes for the functions in this file */
#define __DEFAULT_FUNCS_ATTRS __attribute__((__always_inline__))

#ifdef DONT_NEED_IA32_BUILTINS_WARNINGS
#define __E2K_WARNING(function) function
#else /* DONT_NEED_IA32_BUILTINS_WARNINGS */
#define __E2K_WARNING(function) __attribute__((__deprecated__("The function may be slow due to inefficient implementation, please try to avoid it"))) function
#endif /* DONT_NEED_IA32_BUILTINS_WARNINGS */

/* *****************************************************************************
 *                         Реализация IA32 интринсиков
 * *****************************************************************************/

#ifdef __MMX__

/*******************************************************************************/
/****************************** MMX builtins ***********************************/
/*******************************************************************************/

#define ONE_OPERAND_AND_LITERAL_BUILTINS(name,instr,src_type,dst_type)        \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                   \
__builtin_ia32_##name (src_type src1, __di src2)                              \
{                                                                             \
    __di dst;                                                                 \
_Pragma ("asm_inline")                                                        \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"                   \
        : [dst_name] "=r" (dst)                                               \
        : [src1_name] "rI" ((__di) (src1)), [src2_name] "ri" (src2));         \
    return (dst_type) dst;                                                    \
}

#define TWO_OPERANDS_BUILTINS(name,instr,src_type,dst_type)                   \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                   \
__builtin_ia32_##name (src_type src1, src_type src2)                          \
{                                                                             \
    __di dst;                                                                 \
_Pragma ("asm_inline")                                                        \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"                   \
        : [dst_name] "=r" (dst)                                               \
        : [src1_name] "rI" ((__di) (src1)), [src2_name] "ri" ((__di) (src2)));\
    return (dst_type) dst;                                                    \
}

#define TWO_OPERANDS_BUILTINS_REVERSE(name,instr,src_type,dst_type)           \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                   \
__builtin_ia32_##name (src_type src2, src_type src1)                          \
{                                                                             \
    __di dst;                                                                 \
_Pragma ("asm_inline")                                                        \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"                   \
        : [dst_name] "=r" (dst)                                               \
        : [src1_name] "rI" ((__di) (src1)), [src2_name] "ri" ((__di) (src2)));\
    return (dst_type) dst;                                                    \
}

/* *****************************************************************************
 *                         Инициализация режима (MMX/FP)
 * *****************************************************************************/

#define __builtin_ia32_emms()

/* *****************************************************************************
 *                         Сложение и вычитание по модулю
 * *****************************************************************************/

/* сложение 8-ми байт (8S/8U) */
TWO_OPERANDS_BUILTINS (paddb, paddb, __v8qi, __v8qi)

/* сложение 4-х шортов (16S/16U) */
TWO_OPERANDS_BUILTINS (paddw, paddh, __v4hi, __v4hi)

/* сложение 2-х интов (32S/32U) */
TWO_OPERANDS_BUILTINS (paddd, paddw, __v2si, __v2si)

/* сложение лонгов (64S/64U) */
TWO_OPERANDS_BUILTINS (paddq, addd, __v1di, __v1di)

/* вычитание 8-ми байт (8S/8U) */
TWO_OPERANDS_BUILTINS (psubb, psubb, __v8qi, __v8qi)

/* вычитание 4-х шортов (16S/16U) */
TWO_OPERANDS_BUILTINS (psubw, psubh, __v4hi, __v4hi)

/* вычитание 2-х интов (32S/32U) */
TWO_OPERANDS_BUILTINS (psubd, psubw, __v2si, __v2si)

/* вычитание лонгов (64S/64U) */
TWO_OPERANDS_BUILTINS (psubq, subd, __v1di, __v1di)

/* *****************************************************************************
 *                         Сложение и вычитание c насыщением
 * *****************************************************************************/

/* сложение 8-ми знаковых байт (8S) */
TWO_OPERANDS_BUILTINS (paddsb, paddsb, __v8qi, __v8qi)

/* сложение 4-х знаковых шортов (16S) */
TWO_OPERANDS_BUILTINS (paddsw, paddsh, __v4hi, __v4hi)

/* вычитание 8-ми знаковых байт (8S) */
TWO_OPERANDS_BUILTINS (psubsb, psubsb, __v8qi, __v8qi)

/* вычитание 4-х знаковых шортов (16S) */
TWO_OPERANDS_BUILTINS (psubsw, psubsh, __v4hi, __v4hi)

/* сложение 8-ми беззнаковых байт (8U) */
TWO_OPERANDS_BUILTINS (paddusb, paddusb, __v8qi, __v8qi)

/* сложение 4-х беззнаковых шортов (16U) */
TWO_OPERANDS_BUILTINS (paddusw, paddush, __v4hi, __v4hi)

/* вычитание 8-ми беззнаковых байт (8U) */
TWO_OPERANDS_BUILTINS (psubusb, psubusb, __v8qi, __v8qi)

/* вычитание 4-х беззнаковых шортов (16U) */
TWO_OPERANDS_BUILTINS (psubusw, psubush, __v4hi, __v4hi)

/* *****************************************************************************
 *                             Умножение шортов
 * *****************************************************************************/

/* умножение 4-х знаковых шортов (16S) и выдача младших 16 разрядов произведений */
TWO_OPERANDS_BUILTINS (pmullw, pmullh, __v4hi, __v4hi)

/* умножение 4-х знаковых шортов (16S) и выдача старших 16 разрядов произведений */
TWO_OPERANDS_BUILTINS (pmulhw, pmulhh, __v4hi, __v4hi)

/* *****************************************************************************
 *                           Логические операции
 * *****************************************************************************/

/* поразрядное логическое AND 64-х разрядов (64S/64U) */
TWO_OPERANDS_BUILTINS (pand, pandd, __v2si, __v2si)

/* поразрядное логическое AND 64-х разрядов c инверсией первого операнда (64S/64U) */
TWO_OPERANDS_BUILTINS_REVERSE (pandn, pandnd, __v2si, __v2si)

/* поразрядное логическое OR 64-х разрядов (64S/64U) */
TWO_OPERANDS_BUILTINS (por, pord, __v2si, __v2si)

/* поразрядное логическое XOR 64-х разрядов (64S/64U) */
TWO_OPERANDS_BUILTINS (pxor, pxord, __v2si, __v2si)

/* *****************************************************************************
 *                                Cравнение
 * *****************************************************************************/

/* сравнение на "равно" 8-ми байт (8S/8U) */
TWO_OPERANDS_BUILTINS (pcmpeqb, pcmpeqb, __v8qi, __v8qi)

/* сравнение на "равно" 4-х шортов (16S/16U) */
TWO_OPERANDS_BUILTINS (pcmpeqw, pcmpeqh, __v4hi, __v4hi)

/* сравнение на "равно" 2-х интов (32S/32U) */
TWO_OPERANDS_BUILTINS (pcmpeqd, pcmpeqw, __v2si, __v2si)

/* сравнение на "больше" 8-ми знаковых байт (8S) */
TWO_OPERANDS_BUILTINS (pcmpgtb, pcmpgtb, __v8qi, __v8qi)

/* сравнение на "больше" 4-х знаковых шортов (16S) */
TWO_OPERANDS_BUILTINS (pcmpgtw, pcmpgth, __v4hi, __v4hi)

/* сравнение на "больше" 2-х знаковых интов (32S) */
TWO_OPERANDS_BUILTINS (pcmpgtd, pcmpgtw, __v2si, __v2si)

/* *****************************************************************************
 *                                Распаковка
 * *****************************************************************************/

/* чередование 4-х старших байт (8U) операнда 1 и 4-х старших байт (8U) операнда 2 */
TWO_OPERANDS_BUILTINS_REVERSE (punpckhbw, punpckhbh, __v8qi, __v8qi)

/* чередование 2-х старших шортов (16U) операнда 1 и 2-х старших шортов (16U) операнда 2 */
TWO_OPERANDS_BUILTINS_REVERSE (punpckhwd, punpckhhw, __v4hi, __v4hi)

/* чередование старшего инта (32U) операнда 1 и старшего инта (32U) операнда 2 */
TWO_OPERANDS_BUILTINS_REVERSE (punpckhdq, punpckhwd, __v2si, __v2si)

/* чередование 4-х младших байт (8U) операнда 1 и 4-х младших байт (8U) операнда 2 */
TWO_OPERANDS_BUILTINS_REVERSE (punpcklbw, punpcklbh, __v8qi, __v8qi)

/* чередование 2-х младших шортов (16U) операнда 1 и 2-х младших шортов (16U) операнда 2 */
TWO_OPERANDS_BUILTINS_REVERSE (punpcklwd, punpcklhw, __v4hi, __v4hi)

/* чередование младшего инта (32U) операнда 1 и младшего инта (32U) операнда 2 */
TWO_OPERANDS_BUILTINS_REVERSE (punpckldq, punpcklwd, __v2si, __v2si)

/* *****************************************************************************
 *                                 Упаковка
 * *****************************************************************************/

/* упаковка 8-ми знаковых шортов (16S) в знаковые байты (8S) с насыщением */
TWO_OPERANDS_BUILTINS_REVERSE (packsswb, packsshb, __v4hi, __v8qi)

/* упаковка 4-х знаковых интов (32S) в знаковые шорты (16S) с насыщением */
TWO_OPERANDS_BUILTINS_REVERSE (packssdw, packsswh, __v2si, __v4hi)

/* упаковка 8-ми знаковых шортов (16S) в беззнаковые байты (8U) с насыщением */
TWO_OPERANDS_BUILTINS_REVERSE (packuswb, packushb, __v4hi, __v8qi)

/* *****************************************************************************
 *                 Умножение шортов с горизонтальным сложением
 * *****************************************************************************/

/* умножение 4-х знаковых шортов (16S) и попарное сложение смежных интовых произведений */
TWO_OPERANDS_BUILTINS (pmaddwd, pmaddh, __v4hi, __v2si)

/* *****************************************************************************
 *                               Битовый сдвиг
 * *****************************************************************************/

/* сдвиг влево 4-х шортов (16S/16U) */
TWO_OPERANDS_BUILTINS            (psllw, psllh, __v4hi, __v4hi)
ONE_OPERAND_AND_LITERAL_BUILTINS (psllwi, psllh, __v4hi, __v4hi)

/* сдвиг влево 2-х интов (32S/32U) */
TWO_OPERANDS_BUILTINS            (pslld, psllw, __v2si, __v2si)
ONE_OPERAND_AND_LITERAL_BUILTINS (pslldi, psllw, __v2si, __v2si)

/* сдвиг влево лонга (64S/64U) */
TWO_OPERANDS_BUILTINS            (psllq, pslld, __v1di, __v1di)
ONE_OPERAND_AND_LITERAL_BUILTINS (psllqi, pslld, __v1di, __v1di)

/* логический сдвиг вправо 4-х шортов (16S/16U) */
TWO_OPERANDS_BUILTINS            (psrlw, psrlh, __v4hi, __v4hi)
ONE_OPERAND_AND_LITERAL_BUILTINS (psrlwi, psrlh, __v4hi, __v4hi)

/* логический сдвиг вправо 2-х интов (32S/32U) */
TWO_OPERANDS_BUILTINS            (psrld, psrlw, __v2si, __v2si)
ONE_OPERAND_AND_LITERAL_BUILTINS (psrldi, psrlw, __v2si, __v2si)

/* логический сдвиг вправо лонга (64S/64U) */
TWO_OPERANDS_BUILTINS            (psrlq, psrld, __v1di, __v1di)
ONE_OPERAND_AND_LITERAL_BUILTINS (psrlqi, psrld, __v1di, __v1di)

/* арифметический сдвиг вправо 4-х знаковых шортов (16S) */
TWO_OPERANDS_BUILTINS            (psraw, psrah, __v4hi, __v4hi)
ONE_OPERAND_AND_LITERAL_BUILTINS (psrawi, psrah, __v4hi, __v4hi)

/* арифметический сдвиг вправо 2-х знаковых интов (32S) */
TWO_OPERANDS_BUILTINS            (psrad, psraw, __v2si, __v2si)
ONE_OPERAND_AND_LITERAL_BUILTINS (psradi, psraw, __v2si, __v2si)

/* *****************************************************************************
 *                                Заполнение
 * *****************************************************************************/

/* Creates a vector of two 32-bit values; I1 is least significant */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_init_v2si (int __i0, int __i1)
{
    __di dst;
#pragma asm_inline
    asm ("pshufw %[src1_name], %[src2_name], 2, %[dst_name]"
        : [dst_name] "=r" (dst)
        : [src1_name] "r" ((__di) __i0),
          [src2_name] "ri" ((__di) __i1));
    return (__v2si) dst;
}

/* Creates a vector of four 16-bit values; W3 is least significant */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_init_v4hi (short __w0, short __w1, short __w2, short __w3)
{
    unsigned int __i1 = (unsigned short)__w3 << 16 | (unsigned short)__w2;
    unsigned int __i0 = (unsigned short)__w1 << 16 | (unsigned short)__w0;
    return (__v4hi)__builtin_ia32_vec_init_v2si (__i0, __i1);
}

/* Creates a vector of eight 8-bit values; B7 is least significant */
__E2K_INLINE __v8qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_init_v8qi (char __b0, char __b1, char __b2, char __b3,
                              char __b4, char __b5, char __b6, char __b7)
{
    unsigned int __i1, __i0;

    __i1 = (unsigned char)__b7;
    __i1 = __i1 << 8 | (unsigned char)__b6;
    __i1 = __i1 << 8 | (unsigned char)__b5;
    __i1 = __i1 << 8 | (unsigned char)__b4;

    __i0 = (unsigned char)__b3;
    __i0 = __i0 << 8 | (unsigned char)__b2;
    __i0 = __i0 << 8 | (unsigned char)__b1;
    __i0 = __i0 << 8 | (unsigned char)__b0;
    return (__v8qi)__builtin_ia32_vec_init_v2si (__i0, __i1);
}

/*#undef TWO_OPERANDS_BUILTINS_REVERSE*/
#undef ONE_OPERAND_AND_LITERAL_BUILTINS

#endif /* __MMX__ */

#ifdef __SSE__

/*******************************************************************************/
/****************************** SSE builtins ***********************************/
/*******************************************************************************/

#define SCALAR_SSE_BUILTINS(name,instr,src_type,dst_type)              \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src1, src_type src2)                   \
{                                                                      \
    type_union_128 s1, s2;                                             \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
    int tmp;                                                           \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp)                                         \
       : [src1_name] "rI" (s1.f.f0), [src2_name] "ri" (s2.f.f0));      \
    s1.i.i0 = tmp;                                                     \
    return s1.dst_type;                                                \
}

#define PACKED_SSE_BUILTINS_WITH_SCALAR_OPS(name,instr,src_type, dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src1, src_type src2)                   \
{                                                                      \
    type_union_128 s1, s2, dst;                                        \
    __di tmp0, tmp1;                                                   \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp0)                                        \
       : [src1_name] "rI" (s1.l.l0), [src2_name] "ri" (s2.l.l0));      \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp1)                                        \
       : [src1_name] "rI" (s1.l.l1), [src2_name] "ri" (s2.l.l1));      \
    dst.l.l0 = tmp0;                                                   \
    dst.l.l1 = tmp1;                                                   \
    return dst.dst_type;                                               \
}

#if __iset__ <= 4

#define PACKED_SSE_BUILTINS PACKED_SSE_BUILTINS_WITH_SCALAR_OPS

#define PACKED_SSE_BUILTINS_REVERSE(name,instr,src_type,dst_type)      \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src2, src_type src1)                   \
{                                                                      \
    type_union_128 s1, s2, dst;                                        \
    __di tmp0, tmp1;                                                   \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp0)                                        \
       : [src1_name] "rI" (s1.l.l0), [src2_name] "ri" (s2.l.l0));      \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp1)                                        \
       : [src1_name] "rI" (s1.l.l1), [src2_name] "ri" (s2.l.l1));      \
    dst.l.l0 = tmp0;                                                   \
    dst.l.l1 = tmp1;                                                   \
    return dst.dst_type;                                               \
}

#else /* __iset__ <= 4 */

#define PACKED_SSE_BUILTINS(name,instr,src_type, dst_type)             \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src1, src_type src2)                   \
{                                                                      \
    type_union_128 s1, s2, dst;                                        \
    __v2di tmp;                                                        \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"           \
       : [dst_name] "=r" (tmp)                                         \
       : [src1_name] "rI" (s1.__v2di), [src2_name] "ri" (s2.__v2di));  \
    dst.__v2di = tmp;                                                  \
    return dst.dst_type;                                               \
}

#define PACKED_SSE_BUILTINS_REVERSE(name,instr,src_type,dst_type)      \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src2, src_type src1)                   \
{                                                                      \
    type_union_128 s1, s2, dst;                                        \
    __v2di tmp;                                                        \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"           \
       : [dst_name] "=r" (tmp)                                         \
       : [src1_name] "rI" (s1.__v2di), [src2_name] "ri" (s2.__v2di));  \
    dst.__v2di = tmp;                                                  \
    return dst.dst_type;                                               \
}

#endif /* __iset__ <= 4 */

#define SCALAR_COMPARE_SSE_BUILTINS(name, mask, compare)               \
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS                                 \
__builtin_ia32_##name (__v4sf src1, __v4sf src2)                       \
{                                                                      \
    type_union_128 s1, s2;                                             \
    s1.__v4sf = src1;                                                  \
    s2.__v4sf = src2;                                                  \
    return (__builtin_e2k_fcmpodsf (s1.l.l0, s2.l.l0) & mask) compare; \
}

#define SCALAR_UCOMPARE_SSE_BUILTINS(name, mask, compare)              \
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS                                 \
__builtin_ia32_##name (__v4sf src1, __v4sf src2)                       \
{                                                                      \
    type_union_128 s1, s2;                                             \
    s1.__v4sf = src1;                                                  \
    s2.__v4sf = src2;                                                  \
    return (__builtin_e2k_fcmpudsf (s1.l.l0, s2.l.l0) & mask) compare; \
}

#define SCALAR_ONE_OPERAND_SSE_BUILTINS(name,instr)          \
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS                    \
__builtin_ia32_##name (__v4sf src)                           \
{                                                            \
    type_union_128 s;                                        \
    s.__v4sf = src;                                          \
    float tmp;                                               \
_Pragma ("asm_inline")                                       \
    asm (""#instr" %[src_name], %[dst_name]"                 \
        : [dst_name] "=r" (tmp)                              \
        : [src_name] "ri" (s.f.f0));                         \
    s.f.f0 = tmp;                                            \
    return s.__v4sf;                                         \
}

#define PACKED_ONE_OPERAND_SSE_BUILTINS(name,instr)          \
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS                    \
__builtin_ia32_##name (__v4sf src)                           \
{                                                            \
    type_union_128 s, dst;                                   \
    unsigned int tmp0, tmp1, tmp2, tmp3;                     \
    s.__v4sf = src;                                          \
_Pragma ("asm_inline")                                       \
    asm (""#instr" %[src_name], %[dst_name]"                 \
        : [dst_name] "=r" (tmp0)                             \
        : [src_name] "ri" (s.i.i0));                         \
    dst.i.i0 = tmp0;                                         \
_Pragma ("asm_inline")                                       \
    asm (""#instr" %[src_name], %[dst_name]"                 \
        : [dst_name] "=r" (tmp1)                             \
        : [src_name] "ri" (s.i.i1));                         \
    dst.i.i1 = tmp1;                                         \
_Pragma ("asm_inline")                                       \
    asm (""#instr" %[src_name], %[dst_name]"                 \
        : [dst_name] "=r" (tmp2)                             \
        : [src_name] "ri" (s.i.i2));                         \
    dst.i.i2 = tmp2;                                         \
_Pragma ("asm_inline")                                       \
    asm (""#instr" %[src_name], %[dst_name]"                 \
        : [dst_name] "=r" (tmp3)                             \
        : [src_name] "ri" (s.i.i3));                         \
    s.i.i0 = tmp0;                                           \
    s.i.i1 = tmp1;                                           \
    s.i.i2 = tmp2;                                           \
    s.i.i3 = tmp3;                                           \
    return s.__v4sf;                                         \
}

/* Generates the pause machine instruction with a compiler memory barrier */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pause (void)
{
   __asm__ __volatile__ ("nop" : : );
}

/* *****************************************************************************
 *                          Плавающие операции
 * *****************************************************************************/

/* сложение младшего из 4-х флотов (32F) */
SCALAR_SSE_BUILTINS (addss, fadds, __v4sf, __v4sf)

/* вычитание младшего из 4-х флотов (32F) */
SCALAR_SSE_BUILTINS (subss, fsubs, __v4sf, __v4sf)

/* умножение младшего из 4-х флотов (32F) */
SCALAR_SSE_BUILTINS (mulss, fmuls, __v4sf, __v4sf)

/* деление младшего из 4-х флотов (32F) */
SCALAR_SSE_BUILTINS (divss, fdivs, __v4sf, __v4sf)

/* приближение к обратной величине младшего из 4-х флотов (32F) */
SCALAR_ONE_OPERAND_SSE_BUILTINS(rcpss, frcps);

/* квадратный корень из младшего из 4-х флотов (32F) */
SCALAR_ONE_OPERAND_SSE_BUILTINS(sqrtss, pfsqrts);

/* приближение обратной величины квадратного корня из младшего из 4-х флотов (32F) */
SCALAR_ONE_OPERAND_SSE_BUILTINS(rsqrtss, frsqrts);

/* максимум младшего из 4-х флотов (32F) */
SCALAR_SSE_BUILTINS (maxss, fmaxs, __v4sf, __v4sf)

/* минимум младшего из 4-х флотов (32F) */
SCALAR_SSE_BUILTINS (minss, fmins, __v4sf, __v4sf)

/* сложение 4-х флотов (32F) */
PACKED_SSE_BUILTINS (addps, pfadds, __v4sf, __v4sf)

/* вычитание 4-х флотов (32F) */
PACKED_SSE_BUILTINS (subps, pfsubs, __v4sf, __v4sf)

/* умножение 4-х флотов (32F) */
PACKED_SSE_BUILTINS (mulps, pfmuls, __v4sf, __v4sf)

/* деление 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_divps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    dst.f.f0 = s1.f.f0 / s2.f.f0;
    dst.f.f1 = s1.f.f1 / s2.f.f1;
    dst.f.f2 = s1.f.f2 / s2.f.f2;
    dst.f.f3 = s1.f.f3 / s2.f.f3;
    return dst.__v4sf;
}

/* приближение к обратной величине 4-х флотов (32F) */
PACKED_ONE_OPERAND_SSE_BUILTINS(rcpps, frcps);

/* квадратный корень из 4-х флотов (32F) */
PACKED_ONE_OPERAND_SSE_BUILTINS(sqrtps, pfsqrts);

/* приближение обратной величины квадратного корня из 4-х флотов (32F) */
PACKED_ONE_OPERAND_SSE_BUILTINS(rsqrtps, frsqrts);

/* максимум 4-х флотов (32F) */
PACKED_SSE_BUILTINS (maxps, pfmaxs, __v4sf, __v4sf)

/* минимум 4-х флотов (32F) */
PACKED_SSE_BUILTINS (minps, pfmins, __v4sf, __v4sf)

/* *****************************************************************************
 *                          Логические операции
 * *****************************************************************************/

/* AND 4-х флотов (32F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS (andps, pandd, __v4sf, __v4sf)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS (andps, pand, __v4sf, __v4sf)
#endif /* __iset__ <= 4 */

/* ANDNOT 4-х флотов (32F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS_REVERSE (andnps, pandnd, __v4sf, __v4sf)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS_REVERSE (andnps, pandn, __v4sf, __v4sf)
#endif /* __iset__ <= 4 */

/* OR 4-х флотов (32F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS (orps, pord, __v4sf, __v4sf)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS (orps, por, __v4sf, __v4sf)
#endif /* __iset__ <= 4 */

/* XOR 4-х флотов (32F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS (xorps, pxord, __v4sf, __v4sf)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS (xorps, pxor, __v4sf, __v4sf)
#endif /* __iset__ <= 4 */

/* *****************************************************************************
 *                          Плавающие операции сравнения
 * *****************************************************************************/

/* сравнение на равно младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpeqss, fcmpeqs, __v4sf, __v4sf)

/* сравнение на меньше младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpltss, fcmplts, __v4sf, __v4sf)

/* сравнение на меньше или равно младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpless, fcmples, __v4sf, __v4sf)

/* сравнение на не упорядочены младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpunordss, fcmpuods, __v4sf, __v4sf)

/* сравнение на не равны младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpneqss, fcmpneqs, __v4sf, __v4sf)

/* сравнение на не меньше младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpnltss, fcmpnlts, __v4sf, __v4sf)

/* сравнение на не меньше или равно младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpnless, fcmpnles, __v4sf, __v4sf)

/* сравнение на упорядочены младшего из 4-х флотов (32F) c формированием битовой маски */
SCALAR_SSE_BUILTINS (cmpordss, fcmpods, __v4sf, __v4sf)

/* сравнение на равно 4-х флотов (32F) c формированием битовой маски */
PACKED_SSE_BUILTINS (cmpeqps, pfcmpeqs, __v4sf, __v4sf)

/* сравнение на меньше 4-х флотов (32F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpltps, pfcmplts, __v4sf, __v4sf)

/* сравнение на меньше или равно 4-х флотов (32F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpleps, pfcmples, __v4sf, __v4sf)

/* сравнение на не упорядочены 4-х флотов (32F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpunordps, pfcmpuods, __v4sf, __v4sf)

/* сравнение на не равны 4-х флотов (32F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpneqps, pfcmpneqs, __v4sf, __v4sf)

/* сравнение на не меньше 4-х флотов (32F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpnltps, pfcmpnlts, __v4sf, __v4sf)

/* сравнение на не меньше или равно 4-х флотов (32F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpnleps, pfcmpnles, __v4sf, __v4sf)

/* сравнение на упорядочены 4-х флотов (32F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpordps, pfcmpods, __v4sf, __v4sf)

/* сравнение на больше 4-х флотов (32F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpgtps, pfcmplts, __v4sf, __v4sf)

/* сравнение на больше или равно 4-х флотов (32F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpgeps, pfcmples, __v4sf, __v4sf)

/* сравнение на не больше 4-х флотов (32F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpngtps, pfcmpnlts, __v4sf, __v4sf)

/* сравнение на не больше или равно 4-х флотов (32F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpngeps, pfcmpnles, __v4sf, __v4sf)

/* сравнение на равно младшего из 4-х флотов (32F) c формированием 0/1 */
SCALAR_COMPARE_SSE_BUILTINS (comieq, 0x40, != 0)
SCALAR_UCOMPARE_SSE_BUILTINS (ucomieq, 0x40, != 0)

/* сравнение на не равно младшего из 4-х флотов (32F) c формированием 0/1 */
SCALAR_COMPARE_SSE_BUILTINS (comineq, 0x40, == 0)
SCALAR_UCOMPARE_SSE_BUILTINS (ucomineq, 0x40, == 0)

/* сравнение на меньше младшего из 4-х флотов (32F) c формированием 0/1 */
SCALAR_COMPARE_SSE_BUILTINS (comilt, 0x1, != 0)
SCALAR_UCOMPARE_SSE_BUILTINS (ucomilt, 0x1, != 0)

/* сравнение на меньше или равно младшего из 4-х флотов (32F) c формированием 0/1 */
SCALAR_COMPARE_SSE_BUILTINS (comile, 0x41, != 0)
SCALAR_UCOMPARE_SSE_BUILTINS (ucomile, 0x41, != 0)

/* сравнение на больше младшего из 4-х флотов (32F) c формированием 0/1 */
SCALAR_COMPARE_SSE_BUILTINS (comigt, 0x41, == 0)
SCALAR_UCOMPARE_SSE_BUILTINS (ucomigt, 0x41, == 0)

/* сравнение на больше или равно младшего из 4-х флотов (32F) c формированием 0/1 */
SCALAR_COMPARE_SSE_BUILTINS (comige, 0x1, == 0)
SCALAR_UCOMPARE_SSE_BUILTINS (ucomige, 0x1, == 0)

/* *****************************************************************************
 *                          Операции преобразования
 * *****************************************************************************/

/* преобразование 2-х интов (32S) в 2 флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtpi2ps (__v4sf src1, __v2si src2)
{
    type_union_128 s1;
    s1.__v4sf = src1;
    s1.l.l0 = __builtin_e2k_pistofs ((__di) src2);
    return s1.__v4sf;
}

/* преобразование интa (32S) во флоат (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtsi2ss (__v4sf src1, int src2)
{
    type_union_128 s1;
    s1.__v4sf = src1;
    s1.f.f0 = (float) src2;
    return s1.__v4sf;
}

/* преобразование 2-х флотов (32F) в 2 инта (32S) в текущем режиме округления */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtps2pi (__v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    return (__v2si) __builtin_e2k_pfstois (s.l.l0);
}

/* преобразование флота (32F) в инт (32S) в текущем режиме округления */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtss2si (__v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    return (int) __builtin_e2k_pfstois (s.l.l0);
}

/* преобразование 2-х флотов (32F) в 2 инта (32S) c обрубанием */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttps2pi (__v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    return (__v2si) __builtin_e2k_pfstoistr (s.l.l0);
}

/* преобразование флота (32F) в инт (32S) c обрубанием */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttss2si (__v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    return (int) s.f.f0;
}

/* Convert src2 to a SPFP value and insert it as element zero in src1 */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtsi642ss (__v4sf src1, __di src2)
{
    type_union_128 s1;
    s1.__v4sf = src1;
    s1.f.f0 = (float) (long long) src2;
    return s1.__v4sf;
}

/* Convert the lower SPFP value to a 64-bit integer according to the current
   rounding mode */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtss2si64 (__v4sf src)
{
    __di dst;
    type_union_128 s;
    s.__v4sf = src;
#pragma asm_inline
    asm ("fstoid %[src_name], %[dst_name]"
        : [dst_name] "=r" (dst)
        : [src_name] "ri" (s.f.f0));
    return dst;
}

/* Truncate the lower SPFP value to a 64-bit integer */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttss2si64 (__v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    return (__di) s.f.f0;
}

/* *****************************************************************************
 *                             Пересылки
 * *****************************************************************************/

/* Sets the low SPFP value of src1 from the low value of src2 */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movss (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s1.f.f0 = s2.f.f0;
    return s1.__v4sf;
}

/* Moves the upper two values of src2 into the lower two values of src1 */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movhlps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s1.l.l0 = s2.l.l1;
    return s1.__v4sf;
}

/* Moves the lower two values of src2 into the upper two values of src1 */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movlhps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s1.l.l1 = s2.l.l0;
    return s1.__v4sf;
}

/* *****************************************************************************
 *                             Перестановки
 * *****************************************************************************/

/* выделение из 8-ми входных флотов 4-х, положение которых определяется 8-ю
 * младшими разрядами константы 3-го операнда */
#define __builtin_ia32_shufps(src1, src2, mask) ({                                \
    type_union_128 __s1, __s2, __dst;                                             \
    __s1.__v4sf = src1;                                                           \
    __s2.__v4sf = src2;                                                           \
    __dst.l.l0 = __builtin_e2k_pshufw (__s1.l.l1, __s1.l.l0, (mask) & 15);        \
    __dst.l.l1 = __builtin_e2k_pshufw (__s2.l.l1, __s2.l.l0, ((mask) >> 4) & 15); \
    __dst.__v4sf;                                                                 \
})

/* Selects and interleaves the upper two SPFP values from src1 and src2 */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpckhps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhwd (s2.l.l1, s1.l.l1);
    dst.l.l0 = __builtin_e2k_punpcklwd (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,
                                        __builtin_e2k_qppackdl (0x1f1e1d1c0f0e0d0cLL, 0x1b1a19180b0a0908LL));
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* Selects and interleaves the lower two SPFP values from src1 and src2 */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpcklps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhwd (s2.l.l0, s1.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklwd (s2.l.l0, s1.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,
                                        __builtin_e2k_qppackdl (0x1716151407060504LL, 0x1312111003020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* перестановка 4-х шортов в соответствии с порядком, определенным в 8-ми младших
 * разрядах константы 2-го операнда */
#define __builtin_ia32_pshufw(src1, src2) ({                         \
    __di __dst = __builtin_e2k_pshufh ((__di)(src1), (src2) & 0xff); \
    (__v4hi) __dst;                                                  \
})

/* *****************************************************************************
 *                         Целочисленные операции
 * *****************************************************************************/

/* умножение 4-х беззнаковых шортов (16U) и выдача старших 16 разрядов произведений */
TWO_OPERANDS_BUILTINS (pmulhuw, pmulhuh, __v4hi, __v4hi)

/* среднее 8-ми беззнаковых байт (8U) */
TWO_OPERANDS_BUILTINS (pavgb, pavgusb, __v8qi, __v8qi)

/* среднее 4-х беззнаковых шортов (16U) */
TWO_OPERANDS_BUILTINS (pavgw, pavgush, __v4hi, __v4hi)

/* cложение абсолютных разностей 8-ми беззнаковых байт (8U) */
TWO_OPERANDS_BUILTINS (psadbw, psadbw, __v8qi, __v1di)

/* максимум 8-ми беззнаковых байт (8U) */
TWO_OPERANDS_BUILTINS (pmaxub, pmaxub, __v8qi, __v8qi)

/* максимум 4-х знаковых шортов (16S) */
TWO_OPERANDS_BUILTINS (pmaxsw, pmaxsh, __v4hi, __v4hi)

/* минимум 8-ми беззнаковых байт (8U) */
TWO_OPERANDS_BUILTINS (pminub, pminub, __v8qi, __v8qi)

/* минимум 4-х знаковых шортов (16S) */
TWO_OPERANDS_BUILTINS (pminsw, pminsh, __v4hi, __v4hi)

/* *****************************************************************************
 *                               Выделение маски
 * *****************************************************************************/

/* формирование 8-разрядной маски из знаков каждого байта (8S) */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovmskb (__v8qi src)
{
    return __builtin_e2k_pmovmskb (0, (__di) src);
}

/* формирование 4-разрядной маски из знаков каждого флота (32F) */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movmskps (__v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    return __builtin_e2k_pmovmskps (s.l.l1, s.l.l0);
}

/* *****************************************************************************
 *                               Запись по маске
 * *****************************************************************************/

/* условная запись 8 байтов из src при наличии "1" в старшем разряде соответствующего
 * байта select */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskmovq (__v8qi src, __v8qi select, char *p)
{
#if __iset__ <= 4
    __di mask = __builtin_e2k_pcmpgtb (0, (__di) select);
    __di dst = *((__di *) p);
    *((__di *) p) = ((__di) src & mask) | (dst &~ mask);
/* FIXME: может быть невыровненный указатель */
/*  if (select & (0x80LL))       p[0] = src;
    if (select & (0x80LL << 8))  p[1] = src >> 8;
    if (select & (0x80LL << 16)) p[2] = src >> 16;
    if (select & (0x80LL << 24)) p[3] = src >> 24;
    if (select & (0x80LL << 32)) p[4] = src >> 32;
    if (select & (0x80LL << 40)) p[5] = src >> 40;
    if (select & (0x80LL << 48)) p[6] = src >> 48;
    if (select & (0x80LL << 56)) p[7] = src >> 56;
*/
#elif __iset__ <= 5
    __v2di *qp = (__v2di *) E2K_ALIGN_PTR_BACK (p, 16);
    int align = E2K_BYTES_FROM_ALIGN (p, 16);
    __di mask = __builtin_e2k_pmovmskb (0, (__di) select);
    __di ss = __builtin_e2k_scld ((__di) src, align * 8);
    __v2di s = __builtin_e2k_qppackdl (ss, ss);

    __builtin_e2k_pst_128 (s, qp, mask << align);
    __builtin_e2k_pst_128 (s, qp + 1, (mask << align) >> 16);
#else /* __iset__ >= 6 */
    __di mask = __builtin_e2k_pmovmskb (0, (__di) select);
    __v2di s = __builtin_e2k_qppackdl (0, (__di) src);

    __builtin_e2k_pst_128 (s, p, mask);
#endif /* __iset__ <= 4 */
}

/* *****************************************************************************
 *                            Чтения / Записи
 * *****************************************************************************/

/* Load four SPFP values from P.  The address need not be 16-byte aligned */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadups (const float *p)
{
    type_union_128 dst;
#ifdef __ALIGNED__
    dst.c.c0 = ((unsigned char *) p)[0];
    dst.c.c1 = ((unsigned char *) p)[1];
    dst.c.c2 = ((unsigned char *) p)[2];
    dst.c.c3 = ((unsigned char *) p)[3];
    dst.c.c4 = ((unsigned char *) p)[4];
    dst.c.c5 = ((unsigned char *) p)[5];
    dst.c.c6 = ((unsigned char *) p)[6];
    dst.c.c7 = ((unsigned char *) p)[7];
    dst.c.c8 = ((unsigned char *) p)[8];
    dst.c.c9 = ((unsigned char *) p)[9];
    dst.c.c10 = ((unsigned char *) p)[10];
    dst.c.c11 = ((unsigned char *) p)[11];
    dst.c.c12 = ((unsigned char *) p)[12];
    dst.c.c13 = ((unsigned char *) p)[13];
    dst.c.c14 = ((unsigned char *) p)[14];
    dst.c.c15 = ((unsigned char *) p)[15];
#else /* __ALIGNED__ */
 #if __iset__ <= 5
    dst.l.l0 = ((__di *) p)[0];
    dst.l.l1 = ((__di *) p)[1];
 #else /* __iset__ >= 6 */
    dst.__v2di = ((__v2di *) p)[0];
 #endif /* __iset__ <= 4 */
#endif /* __ALIGNED__ */
    return dst.__v4sf;
}

/* Store four SPFP values.  The address need not be 16-byte aligned */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storeups (float *p, __v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
#ifdef __ALIGNED__
    ((unsigned char *) p)[0] = s.c.c0;
    ((unsigned char *) p)[1] = s.c.c1;
    ((unsigned char *) p)[2] = s.c.c2;
    ((unsigned char *) p)[3] = s.c.c3;
    ((unsigned char *) p)[4] = s.c.c4;
    ((unsigned char *) p)[5] = s.c.c5;
    ((unsigned char *) p)[6] = s.c.c6;
    ((unsigned char *) p)[7] = s.c.c7;
    ((unsigned char *) p)[8] = s.c.c8;
    ((unsigned char *) p)[9] = s.c.c9;
    ((unsigned char *) p)[10] = s.c.c10;
    ((unsigned char *) p)[11] = s.c.c11;
    ((unsigned char *) p)[12] = s.c.c12;
    ((unsigned char *) p)[13] = s.c.c13;
    ((unsigned char *) p)[14] = s.c.c14;
    ((unsigned char *) p)[15] = s.c.c15;
#else /* __ALIGNED__ */
 #if __iset__ <= 5
    ((__di *) p)[0] = s.l.l0;
    ((__di *) p)[1] = s.l.l1;
 #else /* __iset__ >= 6 */
    ((__v2di *) p)[0] = s.__v2di;
 #endif /* __iset__ <= 4 */
#endif /* __ALIGNED__ */
}

/* Sets the upper two SPFP values with 64-bits of data loaded from p;
   the lower two values are passed through from src */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadhps (__v4sf src, const __v2sf *p)
{
    type_union_128 s;
    s.__v4sf = src;
#ifdef __ALIGNED__
    s.c.c8 = ((unsigned char *) p)[0];
    s.c.c9 = ((unsigned char *) p)[1];
    s.c.c10 = ((unsigned char *) p)[2];
    s.c.c11 = ((unsigned char *) p)[3];
    s.c.c12 = ((unsigned char *) p)[4];
    s.c.c13 = ((unsigned char *) p)[5];
    s.c.c14 = ((unsigned char *) p)[6];
    s.c.c15 = ((unsigned char *) p)[7];
#else /* __ALIGNED__ */
    s.l.l1 = *((__di *) p);
#endif /* __ALIGNED__ */
    return s.__v4sf;
}

/* Stores the upper two SPFP values of src into p */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storehps (__v2sf *p, __v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
#ifdef __ALIGNED__
    ((unsigned char *) p)[0] = s.c.c8;
    ((unsigned char *) p)[1] = s.c.c9;
    ((unsigned char *) p)[2] = s.c.c10;
    ((unsigned char *) p)[3] = s.c.c11;
    ((unsigned char *) p)[4] = s.c.c12;
    ((unsigned char *) p)[5] = s.c.c13;
    ((unsigned char *) p)[6] = s.c.c14;
    ((unsigned char *) p)[7] = s.c.c15;
#else /* __ALIGNED__ */
    *((__di *) p) = s.l.l1;
#endif /* __ALIGNED__ */
}

/* Sets the lower two SPFP values with 64-bits of data loaded from p;
   the upper two values are passed through from src */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadlps (__v4sf src, const __v2sf *p)
{
    type_union_128 s;
    s.__v4sf = src;
#ifdef __ALIGNED__
    s.c.c0 = ((unsigned char *) p)[0];
    s.c.c1 = ((unsigned char *) p)[1];
    s.c.c2 = ((unsigned char *) p)[2];
    s.c.c3 = ((unsigned char *) p)[3];
    s.c.c4 = ((unsigned char *) p)[4];
    s.c.c5 = ((unsigned char *) p)[5];
    s.c.c6 = ((unsigned char *) p)[6];
    s.c.c7 = ((unsigned char *) p)[7];
#else /* __ALIGNED__ */
    s.l.l0 = *((__di *) p);
#endif /* __ALIGNED__ */
    return s.__v4sf;
}

/* Stores the lower two SPFP values of src into p */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storelps (__v2sf *p, __v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
#ifdef __ALIGNED__
    ((unsigned char *) p)[0] = s.c.c0;
    ((unsigned char *) p)[1] = s.c.c1;
    ((unsigned char *) p)[2] = s.c.c2;
    ((unsigned char *) p)[3] = s.c.c3;
    ((unsigned char *) p)[4] = s.c.c4;
    ((unsigned char *) p)[5] = s.c.c5;
    ((unsigned char *) p)[6] = s.c.c6;
    ((unsigned char *) p)[7] = s.c.c7;
#else /* __ALIGNED__ */
    *((__di *) p) = s.l.l0;
#endif /* __ALIGNED__ */
}

/* Stores the data in src to the address p without polluting the caches */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntq (__di *p, __di src)
{
    __builtin_e2k_st_64s_nt (src, p);
}

/* Stores the data in src to the address p without polluting the caches. The address must be 16-byte aligned */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntps (float *p, __v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
#if __iset__ <= 4
    __builtin_e2k_st_64s_nt (s.l.l0, p);
    __builtin_e2k_st_64s_nt (s.l.l1, (__di *) p + 1);
#else /* __iset__ <= 4 */
    __builtin_e2k_st_128_nt (s.__v2di, p);
#endif /* __iset__ <= 4 */
}

/* Guarantees that every preceding store is globally visible before
   any subsequent store */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sfence ()
{
#pragma no_asm_inline
    asm ("wait st_c = 1");
}

/* *****************************************************************************
 *                 Обращение к статус регистру MXSCR (PFPFR)
 * *****************************************************************************/

/* Set the control register to src */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ldmxcsr (unsigned int src)
{
#pragma asm_inline
    asm ("rws  %[src_name], %%pfpfr"
        : : [src_name] "ri" (src));
}

/* Return the contents of the control register */
__E2K_INLINE unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_stmxcsr ()
{
    unsigned int dst;
#pragma asm_inline
    asm ("rrs %%pfpfr, %[dst_name]"
        : [dst_name] "=r" (dst));
    return dst;
}

/*FIXME: не понял - где эти интринсики должны быть?
  перенесены из sse4.1. потому как используются уже частично в sse. */

/* *****************************************************************************
 *                            Выделение
 * *****************************************************************************/

/* выделение беззнакового шорта из 4-х шортов с номером,
 * задаваемым константой во 2-м операнде (ноль соответствует младшему шорту) */
#define __builtin_ia32_vec_ext_v4hi(src, indx) ({                                             \
    __di __s = (__di) src;                                                                    \
    int __dst;                                                                                \
_Pragma ("asm_inline")                                                                        \
    asm ("pextrh %[src1_name], %[src2_name], %[src3_name], %[dst_name]"                       \
        : [dst_name] "=r" (__dst)                                                             \
        : [src1_name] "rI" (__s), [src2_name] "ri" (__s), [src3_name] "i" ((int)(indx) & 3)); \
    (short) __dst;                                                                            \
})

/* Extract a DPFP value from src at the offset specified by indx */
__E2K_INLINE double __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_ext_v2df (__v2df src, const int indx)
{
    type_union_128 s;
    s.__v2df = src;
    return (indx & 1) ? s.d.d1 : s.d.d0;
}

/* Extract a long long value from src at the offset specified by indx */
__E2K_INLINE long long __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_ext_v2di (__v2di src, const int indx)
{
    type_union_128 s;
    s.__v2di = src;
    return (indx & 1) ? s.l.l1 : s.l.l0;
}

/* Extract an int value from src at the offset specified by indx */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_ext_v4si (__v4si src, const int indx)
{
    type_union_128 s;
    s.__v4si = src;
    return (indx & 2) ? ((indx & 1) ? s.i.i3 : s.i.i2) : ((indx & 1) ? s.i.i1 : s.i.i0);
}

/* Extract a SPFP value from src at the offset specified by indx */
__E2K_INLINE float __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_ext_v4sf (__v4sf src, const int indx)
{
    type_union_128 s;
    s.__v4sf = src;
    return (indx & 2) ? ((indx & 1) ? s.f.f3 : s.f.f2) : ((indx & 1) ? s.f.f1 : s.f.f0);
}

/* выделение беззнакового шорта из 8-ми шортов с номером,
 * задаваемым константой во 2-м операнде (ноль соответствует младшему шорту) */
#define __builtin_ia32_vec_ext_v8hi(src, indx) ({                                                  \
    type_union_128 __s;                                                                            \
    int __dst;                                                                                     \
    __s.__v8hi = src;                                                                              \
_Pragma ("asm_inline")                                                                             \
    asm ("pextrh %[src1_name], %[src2_name], %[src3_name], %[dst_name]"                            \
        : [dst_name] "=r" (__dst)                                                                  \
        : [src1_name] "rI" (__s.l.l1), [src2_name] "ri" (__s.l.l0), [src3_name] "i" ((int)(indx)));\
    __dst;                                                                                         \
})

/* Extract an unsigned char value from src at the offset specified by indx */
#define __builtin_ia32_vec_ext_v16qi(src, indx) ({                                                 \
    type_union_128 __s;                                                                            \
    __di __dst;                                                                                    \
    __s.__v16qi = src;                                                                             \
_Pragma ("asm_inline")                                                                             \
    asm ("psrlql %[src1_name], %[src2_name], %[src3_name], %[dst_name]"                            \
        : [dst_name] "=r" (__dst)                                                                  \
        : [src1_name] "rI" (__s.l.l1), [src2_name] "ri" (__s.l.l0), [src3_name] "i" ((int)(indx)));\
    __dst & 0xff;                                                                                  \
})

/* *****************************************************************************
 *                            Вставка
 * *****************************************************************************/

/* Вставка шорта из младшей части операнда 2 в операнд 1 на место с номером,
 * задаваемым константой в 3-м операнде (ноль соответствует младшему шорту) */
#define __builtin_ia32_vec_set_v4hi(src1, src2, indx) ({                                           \
    __di __s1 = (__di) src1;                                                                       \
    __di __dst;                                                                                    \
_Pragma ("asm_inline")                                                                             \
    asm ("pinsh %[src1_name], %[src2_name], %[src3_name], %[dst_name]"                             \
        : [dst_name] "=r" (__dst)                                                                  \
        : [src1_name] "rI" (__s1), [src2_name] "ri" ((int)(src2)), [src3_name] "i" ((int)(indx))); \
    (__v4hi) __dst;                                                                                \
})

/* вставка long long-а из операнда 2 в операнд 1 на место с номером,
 * задаваемым константой в 3-м операнде (ноль соответствует младшему long long-у) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_set_v2di (__v2di src1, long long src2, const int indx)
{
    type_union_128 dst;
    dst.__v2di = src1;

    if (indx & 1) {
        dst.l.l1 = src2;
    }
    else {
        dst.l.l0 = src2;
    }
    return dst.__v2di;
}

/* вставка int-а из операнда 2 в операнд 1 на место с номером,
 * задаваемым константой в 3-м операнде (ноль соответствует младшему int-у) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_set_v4si (__v4si src1, int src2, const int indx)
{
    type_union_128 dst;
    dst.__v4si = src1;

    if (indx & 2) {
        if (indx & 1) {
            dst.i.i3 = src2;
        }
        else {
            dst.i.i2 = src2;
        }
    }
    else {
        if (indx & 1) {
            dst.i.i1 = src2;
        }
        else {
            dst.i.i0 = src2;
        }
    }
    return dst.__v4si;
}

/* вставка шорта из младшей части операнда 2 в операнд 1 на место с номером,
 * задаваемым константой в 3-м операнде (ноль соответствует младшему шорту) */
#define __builtin_ia32_vec_set_v8hi(src1, src2, indx) ({                                                      \
    type_union_128 __dst;                                                                                     \
    __di __tmp0, __tmp1;                                                                                      \
    __dst.__v8hi = src1;                                                                                      \
    if ((indx) > 3) {                                                                                         \
_Pragma ("asm_inline")                                                                                        \
        asm ("pinsh %[src1_name], %[src2_name], %[src3_name], %[dst_name]"                                    \
            : [dst_name] "=r" (__tmp1)                                                                        \
            : [src1_name] "rI" (__dst.l.l1), [src2_name] "ri" ((int)(src2)), [src3_name] "i" ((int)(indx)&3));\
       __dst.l.l1 = __tmp1;                                                                                   \
    }                                                                                                         \
    else {                                                                                                    \
_Pragma ("asm_inline")                                                                                        \
        asm ("pinsh %[src1_name], %[src2_name], %[src3_name], %[dst_name]"                                    \
            : [dst_name] "=r" (__tmp0)                                                                        \
            : [src1_name] "rI" (__dst.l.l0), [src2_name] "ri" ((int)(src2)), [src3_name] "i" ((int)(indx)&3));\
       __dst.l.l0 = __tmp0;                                                                                   \
    }                                                                                                         \
    __dst.__v8hi;                                                                                             \
})

/* вставка байта из операнда 2 в операнд 1 на место с номером,
 * задаваемым константой в 3-м операнде (ноль соответствует младшему байту) */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vec_set_v16qi (__v16qi src1, int src2, const int indx)
{
    type_union_128 dst;
    dst.__v16qi = src1;

    if (indx & 8) {
        if (indx & 4) {
            if (indx & 2) {
                if (indx & 1) {
                    dst.c.c15 = src2;
                }
                else {
                    dst.c.c14 = src2;
                }
            }
            else {
                if (indx & 1) {
                    dst.c.c13 = src2;
                }
                else {
                    dst.c.c12 = src2;
                }
            }
        }
        else {
            if (indx & 2) {
                if (indx & 1) {
                    dst.c.c11 = src2;
                }
                else {
                    dst.c.c10 = src2;
                }
            }
            else {
                if (indx & 1) {
                    dst.c.c9 = src2;
                }
                else {
                    dst.c.c8 = src2;
                }
            }
        }
    }
    else {
        if (indx & 4) {
            if (indx & 2) {
                if (indx & 1) {
                    dst.c.c7 = src2;
                }
                else {
                    dst.c.c6 = src2;
                }
            }
            else {
                if (indx & 1) {
                    dst.c.c5 = src2;
                }
                else {
                    dst.c.c4 = src2;
                }
            }
        }
        else {
            if (indx & 2) {
                if (indx & 1) {
                    dst.c.c3 = src2;
                }
                else {
                    dst.c.c2 = src2;
                }
            }
            else {
                if (indx & 1) {
                    dst.c.c1 = src2;
                }
                else {
                    dst.c.c0 = src2;
                }
            }
        }
    }
    return dst.__v16qi;
}

#undef SCALAR_SSE_BUILTINS
#undef SCALAR_COMPARE_SSE_BUILTINS
#undef SCALAR_UCOMPARE_SSE_BUILTINS
#undef SCALAR_ONE_OPERAND_SSE_BUILTINS
#undef PACKED_ONE_OPERAND_SSE_BUILTINS

#endif /* __SSE__ */

#ifdef __SSE2__

/*******************************************************************************/
/****************************** SSE2 builtins **********************************/
/*******************************************************************************/

#define SCALAR_SSE2_BUILTINS(name,instr,src_type,dst_type)      \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                     \
__builtin_ia32_##name (src_type src1, src_type src2)            \
{                                                               \
    type_union_128 s1, s2;                                      \
    __di tmp;                                                   \
    s1.src_type = src1;                                         \
    s2.src_type = src2;                                         \
_Pragma ("asm_inline")                                          \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"     \
      : [dst_name] "=r" (tmp)                                   \
      : [src1_name] "rI" (s1.l.l0), [src2_name] "ri" (s2.l.l0));\
    s1.l.l0 = tmp;                                              \
    return s1.dst_type;                                         \
}

#define SCALAR_COMPARE_SSE2_BUILTINS(name, mask, compare)              \
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS                                 \
__builtin_ia32_##name (__v2df src1, __v2df src2)                       \
{                                                                      \
    type_union_128 s1, s2;                                             \
    s1.__v2df = src1;                                                  \
    s2.__v2df = src2;                                                  \
    return (__builtin_e2k_fcmpoddf (s1.l.l0, s2.l.l0) & mask) compare; \
}

#define SCALAR_UCOMPARE_SSE2_BUILTINS(name, mask, compare)             \
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS                                 \
__builtin_ia32_##name (__v2df src1, __v2df src2)                       \
{                                                                      \
    type_union_128 s1, s2;                                             \
    s1.__v2df = src1;                                                  \
    s2.__v2df = src2;                                                  \
    return (__builtin_e2k_fcmpuddf (s1.l.l0, s2.l.l0) & mask) compare; \
}

#if __iset__ <= 4

#define PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V(name,instr,src1_type,src2_type,dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                                     \
__builtin_ia32_##name (src1_type src1, src2_type src2)                                          \
{                                                                                               \
    type_union_128 s1, s2, dst;                                                                 \
    __di tmp0, tmp1;                                                                            \
    s1.src1_type = src1;                                                                        \
    s2.src2_type = src2;                                                                        \
_Pragma ("asm_inline")                                                                          \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"                                     \
        : [dst_name] "=r" (tmp0)                                                                \
        : [src1_name] "rI" (s1.l.l0), [src2_name] "ri" (s2.l.l0));                              \
_Pragma ("asm_inline")                                                                          \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"                                     \
        : [dst_name] "=r" (tmp1)                                                                \
        : [src1_name] "rI" (s1.l.l1), [src2_name] "ri" (s2.l.l0));                              \
    dst.l.l0 = tmp0;                                                                            \
    dst.l.l1 = tmp1;                                                                            \
    return dst.dst_type;                                                                        \
}

#define PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S(name,instr,src1_type,src2_type,dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                                     \
__builtin_ia32_##name (src1_type src1, src2_type src2)                                          \
{                                                                                               \
    type_union_128 s1, dst;                                                                     \
    __di tmp0, tmp1;                                                                            \
    s1.src1_type = src1;                                                                        \
_Pragma ("asm_inline")                                                                          \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"                                     \
        : [dst_name] "=r" (tmp0)                                                                \
        : [src1_name] "rI" (s1.l.l0), [src2_name] "ri" ((__di) (src2)));                        \
_Pragma ("asm_inline")                                                                          \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"                                     \
        : [dst_name] "=r" (tmp1)                                                                \
        : [src1_name] "rI" (s1.l.l1), [src2_name] "ri" ((__di) (src2)));                        \
    dst.l.l0 = tmp0;                                                                            \
    dst.l.l1 = tmp1;                                                                            \
    return dst.dst_type;                                                                        \
}

#else /* __iset__ <= 4 */

#define PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V(name,instr,src1_type,src2_type,dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                                     \
__builtin_ia32_##name (src1_type src1, src2_type src2)                                          \
{                                                                                               \
    type_union_128 s1, s2, dst;                                                                 \
    __v2di tmp;                                                                                 \
    s1.src1_type = src1;                                                                        \
    s2.src2_type = src2;                                                                        \
_Pragma ("asm_inline")                                                                          \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"                                    \
        : [dst_name] "=r" (tmp)                                                                 \
        : [src1_name] "rI" (s1.__v2di), [src2_name] "ri" (s2.l.l0));                            \
    dst.__v2di = tmp;                                                                           \
    return dst.dst_type;                                                                        \
}

#define PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S(name,instr,src1_type,src2_type,dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                                     \
__builtin_ia32_##name (src1_type src1, src2_type src2)                                          \
{                                                                                               \
    type_union_128 s1, dst;                                                                     \
    __v2di tmp;                                                                                 \
    s1.src1_type = src1;                                                                        \
_Pragma ("asm_inline")                                                                          \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"                                    \
        : [dst_name] "=r" (tmp)                                                                 \
        : [src1_name] "rI" (s1.__v2di), [src2_name] "ri" ((__di) (src2)));                      \
    dst.__v2di = tmp;                                                                           \
    return dst.dst_type;                                                                        \
}

#endif /* __iset__ <= 4 */

/* *****************************************************************************
 *                          Плавающие операции
 * *****************************************************************************/

/* сложение младшего из 2-х даблов (64F) */
SCALAR_SSE2_BUILTINS (addsd, pfaddd, __v2df, __v2df)

/* вычитание младшего из 2-х даблов (64F) */
SCALAR_SSE2_BUILTINS (subsd, pfsubd, __v2df, __v2df)

/* умножение младшего из 2-х даблов (64F) */
SCALAR_SSE2_BUILTINS (mulsd, pfmuld, __v2df, __v2df)

/* деление младшего из 2-х даблов (64F) */
SCALAR_SSE2_BUILTINS (divsd, pfdivd, __v2df, __v2df)

/* квадратный корень из младшего из 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sqrtsd (__v2df src)
{
    type_union_128 s;
    __di tmp;
    s.__v2df = src;
#pragma asm_inline
    asm ("fsqrtid %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp)
        : [src_name] "ri" (s.l.l0));
#pragma asm_inline
    asm ("pfsqrttd %[src1_name], %[src2_name], %[dst_name]"
        : [dst_name] "=r" (tmp)
        : [src1_name] "r" (s.l.l0), [src2_name] "ri" (tmp));
    s.l.l0 = tmp;
    return s.__v2df;
}

/* максимум младшего из 2-х даблов (64F) */
SCALAR_SSE2_BUILTINS (maxsd, pfmaxd, __v2df, __v2df)

/* минимум младшего из 2-х даблов (64F) */
SCALAR_SSE2_BUILTINS (minsd, pfmind, __v2df, __v2df)

/* сложение 2-х даблов (64F) */
PACKED_SSE_BUILTINS (addpd, pfaddd, __v2df, __v2df)

/* вычитание 2-х даблов (64F) */
PACKED_SSE_BUILTINS (subpd, pfsubd, __v2df, __v2df)

/* умножение 2-х даблов (64F) */
PACKED_SSE_BUILTINS (mulpd, pfmuld, __v2df, __v2df)

/* деление 2-х даблов (64F) */
PACKED_SSE_BUILTINS_WITH_SCALAR_OPS (divpd, pfdivd, __v2df, __v2df)

/* квадратный корень из 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sqrtpd (__v2df src)
{
    type_union_128 s;
    __di tmp0, tmp1;
    s.__v2df = src;
#pragma asm_inline
    asm ("fsqrtid %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src_name] "ri" (s.l.l0));
#pragma asm_inline
    asm ("pfsqrttd %[src1_name], %[src2_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src1_name] "r" (s.l.l0), [src2_name] "ri" (tmp0));
#pragma asm_inline
    asm ("fsqrtid %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src_name] "ri" (s.l.l1));
#pragma asm_inline
    asm ("pfsqrttd %[src1_name], %[src2_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src1_name] "r" (s.l.l1), [src2_name] "ri" (tmp1));
    s.l.l0 = tmp0;
    s.l.l1 = tmp1;
    return s.__v2df;
}

/* максимум 2-х даблов (64F) */
PACKED_SSE_BUILTINS (maxpd, pfmaxd, __v2df, __v2df)

/* минимум 2-х даблов (64F) */
PACKED_SSE_BUILTINS (minpd, pfmind, __v2df, __v2df)

/* *****************************************************************************
 *                          Логические операции
 * *****************************************************************************/

/* AND 2-х даблов (64F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS (andpd, pandd, __v2df, __v2df)
PACKED_SSE_BUILTINS (pand128, pandd, __v2di, __v2di)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS (andpd, pand, __v2df, __v2df)
PACKED_SSE_BUILTINS (pand128, pand, __v2di, __v2di)
#endif /* __iset__ <= 4 */

/* ANDNOT 2-х даблов (64F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS_REVERSE (andnpd, pandnd, __v2df, __v2df)
PACKED_SSE_BUILTINS_REVERSE (pandn128, pandnd, __v2di, __v2di)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS_REVERSE (andnpd, pandn, __v2df, __v2df)
PACKED_SSE_BUILTINS_REVERSE (pandn128, pandn, __v2di, __v2di)
#endif /* __iset__ <= 4 */

/* OR 2-х даблов (64F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS (orpd, pord, __v2df, __v2df)
PACKED_SSE_BUILTINS (por128, pord, __v2di, __v2di)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS (orpd, por, __v2df, __v2df)
PACKED_SSE_BUILTINS (por128, por, __v2di, __v2di)
#endif /* __iset__ <= 4 */

/* XOR 2-х даблов (64F) */
#if __iset__ <= 4
PACKED_SSE_BUILTINS (xorpd, pxord, __v2df, __v2df)
PACKED_SSE_BUILTINS (pxor128, pxord, __v2di, __v2di)
#else /* __iset__ <= 4 */
PACKED_SSE_BUILTINS (xorpd, pxor, __v2df, __v2df)
PACKED_SSE_BUILTINS (pxor128, pxor, __v2di, __v2di)
#endif /* __iset__ <= 4 */

/* *****************************************************************************
 *                          Плавающие операции сравнения
 * *****************************************************************************/

/* сравнение на равно младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmpeqsd, pfcmpeqd, __v2df, __v2df)

/* сравнение на меньше младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmpltsd, pfcmpltd, __v2df, __v2df)

/* сравнение на меньше или равно младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmplesd, pfcmpled, __v2df, __v2df)

/* сравнение на не упорядочены младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmpunordsd, pfcmpuodd, __v2df, __v2df)

/* сравнение на не равны младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmpneqsd, pfcmpneqd, __v2df, __v2df)

/* сравнение на не меньше младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmpnltsd, pfcmpnltd, __v2df, __v2df)

/* сравнение на не меньше или равно младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmpnlesd, pfcmpnled, __v2df, __v2df)

/* сравнение на упорядочены младшего из 2-х даблов (64F) c формированием битовой маски */
SCALAR_SSE2_BUILTINS (cmpordsd, pfcmpodd, __v2df, __v2df)

/* сравнение на равно 2-х даблов (64F) c формированием битовой маски */
PACKED_SSE_BUILTINS (cmpeqpd, pfcmpeqd, __v2df, __v2df)

/* сравнение на меньше 2-х даблов (64F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpltpd, pfcmpltd, __v2df, __v2df)

/* сравнение на меньше или равно 2-х даблов (64F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmplepd, pfcmpled, __v2df, __v2df)

/* сравнение на не упорядочены 2-х даблов (64F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpunordpd, pfcmpuodd, __v2df, __v2df)

/* сравнение на не равны 2-х даблов (64F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpneqpd, pfcmpneqd, __v2df, __v2df)

/* сравнение на не меньше 2-х даблов (64F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpnltpd, pfcmpnltd, __v2df, __v2df)

/* сравнение на не меньше или равно 2-х даблов (64F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpnlepd, pfcmpnled, __v2df, __v2df)

/* сравнение на упорядочены 2-х даблов (64F) с формированием битовой маски */
PACKED_SSE_BUILTINS (cmpordpd, pfcmpodd, __v2df, __v2df)

/* сравнение на больше 2-х даблов (64F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpgtpd, pfcmpltd, __v2df, __v2df)

/* сравнение на больше или равно 2-х даблов (64F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpgepd, pfcmpled, __v2df, __v2df)

/* сравнение на не больше 2-х даблов (64F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpngtpd, pfcmpnltd, __v2df, __v2df)

/* сравнение на не больше или равно 2-х даблов (64F) c формированием битовой маски */
PACKED_SSE_BUILTINS_REVERSE (cmpngepd, pfcmpnled, __v2df, __v2df)

/* сравнение на равно младшего из 2-х даблов (64F) c формированием 0/1 */
SCALAR_COMPARE_SSE2_BUILTINS (comisdeq, 0x40, != 0)
SCALAR_UCOMPARE_SSE2_BUILTINS (ucomisdeq, 0x40, != 0)

/* сравнение на не равно младшего из 2-х даблов (64F) c формированием 0/1 */
SCALAR_COMPARE_SSE2_BUILTINS (comisdneq, 0x40, == 0)
SCALAR_UCOMPARE_SSE2_BUILTINS (ucomisdneq, 0x40, == 0)

/* сравнение на меньше младшего из 2-х даблов (64F) c формированием 0/1 */
SCALAR_COMPARE_SSE2_BUILTINS (comisdlt, 0x1, != 0)
SCALAR_UCOMPARE_SSE2_BUILTINS (ucomisdlt, 0x1, != 0)

/* сравнение на меньше или равно младшего из 2-х даблов (64F) c формированием 0/1 */
SCALAR_COMPARE_SSE2_BUILTINS (comisdle, 0x41, != 0)
SCALAR_UCOMPARE_SSE2_BUILTINS (ucomisdle, 0x41, != 0)

/* сравнение на больше младшего из 2-х даблов (64F) c формированием 0/1 */
SCALAR_COMPARE_SSE2_BUILTINS (comisdgt, 0x41, == 0)
SCALAR_UCOMPARE_SSE2_BUILTINS (ucomisdgt, 0x41, == 0)

/* сравнение на больше или равно младшего из 2-х даблов (64F) c формированием 0/1 */
SCALAR_COMPARE_SSE2_BUILTINS (comisdge, 0x1, == 0)
SCALAR_UCOMPARE_SSE2_BUILTINS (ucomisdge, 0x1, == 0)

/* *****************************************************************************
 *                          Операции преобразования
 * *****************************************************************************/

/* преобразование 2-х младших интов (32S) в 2 дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtdq2pd (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.d.d0 = (double) s.i.i0;
    dst.d.d1 = (double) s.i.i1;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpistofd (s.l.l0);
#endif /* __iset__ <= 4 */
    return dst.__v2df;
}

/* преобразование 4-х интов (32S) в 4 флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtdq2ps (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
     dst.l.l0 = __builtin_e2k_pistofs (s.l.l0);
     dst.l.l1 = __builtin_e2k_pistofs (s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpistofs (s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* преобразование 2-х даблов (64F) в 2 младших инта (32S) в текущем режиме округления */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtpd2dq (__v2df src)
{
    type_union_128 s, dst;
    s.__v2df = src;
#if __iset__ <= 4
    unsigned int tmp0, tmp1;
#pragma asm_inline
    asm ("pfdtois %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src_name] "ri" (s.l.l1));
#pragma asm_inline
    asm ("pfdtois %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src_name] "ri" (s.l.l0));
    dst.l.l0 = tmp0 | ((__di) tmp1 << 32);
#else /* __iset__ <= 4 */
    __di tmp = __builtin_e2k_qpfdtois (s.__v2di);
    dst.l.l0 = tmp;
#endif /* __iset__ <= 4 */
    dst.l.l1 = 0LL;
    return dst.__v4si;
}

/* преобразование 2-х даблов (64F) в 2 инта (32S) в текущем режиме округления */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtpd2pi (__v2df src)
{
    type_union_128 s;
    s.__v2df = src;
#if __iset__ <= 4
    unsigned int tmp0, tmp1;
#pragma asm_inline
    asm ("pfdtois %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src_name] "ri" (s.l.l1));
#pragma asm_inline
    asm ("pfdtois %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src_name] "ri" (s.l.l0));
    return (__v2si) (tmp0 | ((__di) tmp1 << 32));
#else /* __iset__ <= 4 */
    __di tmp = __builtin_e2k_qpfdtois (s.__v2di);
    return (__v2si) tmp;
#endif /* __iset__ <= 4 */
}

/* преобразование 2-х даблов (64F) в 2 младших флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtpd2ps (__v2df src)
{
    type_union_128 s, dst;
    s.__v2df = src;
#if __iset__ <= 4
    unsigned int tmp0, tmp1;
#pragma asm_inline
    asm ("pfdtofs %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src_name] "ri" (s.l.l1));
#pragma asm_inline
    asm ("pfdtofs %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src_name] "ri" (s.l.l0));
    dst.l.l0 = tmp0 | ((__di) tmp1 << 32);
#else /* __iset__ <= 4 */
    __di tmp = __builtin_e2k_qpfdtofs (s.__v2di);
    dst.l.l0 = tmp;
#endif /* __iset__ <= 4 */
    dst.l.l1 = 0LL;
    return dst.__v4sf;
}

/* преобразование 2-х даблов (64F) в 2 младших инта (32S) c обрубанием */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttpd2dq (__v2df src)
{
    type_union_128 s, dst;
    s.__v2df = src;
#if __iset__ <= 4
    unsigned int tmp0, tmp1;
#pragma asm_inline
    asm ("pfdtoistr %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src_name] "ri" (s.l.l1));
#pragma asm_inline
    asm ("pfdtoistr %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src_name] "ri" (s.l.l0));
    dst.l.l0 = tmp0 | ((__di) tmp1 << 32);
#else /* __iset__ <= 4 */
    __di tmp = __builtin_e2k_qpfdtoistr (s.__v2di);
    dst.l.l0 = tmp;
#endif /* __iset__ <= 4 */
    dst.l.l1 = 0LL;
    return dst.__v4si;
}

/* преобразование 2-х даблов (64F) в 2 инта (32S) c обрубанием */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttpd2pi (__v2df src)
{
    type_union_128 s;
    s.__v2df = src;
#if __iset__ <= 4
    unsigned int tmp0, tmp1;
#pragma asm_inline
    asm ("pfdtoistr %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src_name] "ri" (s.l.l1));
#pragma asm_inline
    asm ("pfdtoistr %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src_name] "ri" (s.l.l0));
    return (__v2si) (tmp0 | ((__di) tmp1 << 32));
#else /* __iset__ <= 4 */
    __di tmp = __builtin_e2k_qpfdtoistr (s.__v2di);
    return (__v2si) tmp;
#endif /* __iset__ <= 4 */
}

/* преобразование 2-х интов (32S) в 2 дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtpi2pd (__v2si src)
{
    type_union_128 dst;
#if __iset__ <= 4
    __di tmp0, tmp1;
#pragma asm_inline
    asm ("istofd %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp0)
        : [src_name] "ri" ((int) (__di) src));
#pragma asm_inline
    asm ("istofd %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp1)
        : [src_name] "ri" ((int) ((__di) src >> 32)));
    dst.l.l0 = tmp0;
    dst.l.l1 = tmp1;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpistofd ((__di) src);
    dst.__v2di = tmp;
#endif /* __iset__ <= 4 */
    return dst.__v2df;
}

/* преобразование младшего дабла (64F) в инт (32S) в текущем режиме округления */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtsd2si (__v2df src)
{
    type_union_128 s;
    int tmp;
    s.__v2df = src;
#pragma asm_inline
    asm ("pfdtois %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp)
        : [src_name] "ri" (s.l.l0));
    return tmp;
}

/* преобразование младшего дабла (64F) в инт (32S) c обрубанием */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttsd2si (__v2df src)
{
    type_union_128 s;
    s.__v2df = src;
    return (int) s.d.d0;
}

/* преобразование младшего дабла (64F) в лонг (64S) в текущем режиме округления */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtsd2si64 (__v2df src)
{
    type_union_128 s;
    __di tmp;
    s.__v2df = src;
#pragma asm_inline
    asm ("fdtoid %[src_name], %[dst_name]"
        : [dst_name] "=r" (tmp)
        : [src_name] "ri" (s.l.l0));
    return tmp;
}

/* преобразование младшего дабла (64F) в лонг (64S) c обрубанием */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttsd2si64 (__v2df src)
{
    type_union_128 s;
    s.__v2df = src;
    return (__di) s.d.d0;
}

/* преобразование 4-х флотов (32F) в 4 инта (32S) в текущем режиме округления */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtps2dq (__v4sf src)
{
    type_union_128 s, dst;
    s.__v4sf = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfstois (s.l.l0);
    dst.l.l1 = __builtin_e2k_pfstois (s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfstois (s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* преобразование 2-х младших флотов (32F) в 2 дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtps2pd (__v4sf src)
{
    type_union_128 s, dst;
    s.__v4sf = src;
#if __iset__ <= 4
    dst.d.d0 = (double) s.f.f0;
    dst.d.d1 = (double) s.f.f1;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfstofd (s.l.l0);
#endif /* __iset__ <= 4 */
    return dst.__v2df;
}

/* преобразование 4-х флотов (32F) в 4 инта (32S) c обрубанием */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttps2dq (__v4sf src)
{
    type_union_128 s, dst;
    s.__v4sf = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfstoistr (s.l.l0);
    dst.l.l1 = __builtin_e2k_pfstoistr (s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfstoistr (s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* преобразование интa (32S) в младший дабл (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtsi2sd (__v2df src1, int src2)
{
    type_union_128 dst;
    dst.__v2df = src1;
    dst.d.d0 = (double) src2;
    return dst.__v2df;
}

/* преобразование лонга (64S) в младший дабл (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtsi642sd (__v2df src1, __di src2)
{
    type_union_128 dst;
    dst.__v2df = src1;
    dst.d.d0 = (double) (long long) src2;
    return dst.__v2df;
}

/* преобразование младшего дабла (64F) в младший флоат (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtsd2ss (__v4sf src1, __v2df src2)
{
    type_union_128 dst, s2;
    dst.__v4sf = src1;
    s2.__v2df = src2;
    dst.f.f0 = (float) s2.d.d0;
    return dst.__v4sf;
}

/* преобразование младшего флота (32F) в младший дабл (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtss2sd (__v2df src1, __v4sf src2)
{
    type_union_128 dst, s2;
    dst.__v2df = src1;
    s2.__v4sf = src2;
    dst.d.d0 = (double) s2.f.f0;
    return dst.__v2df;
}

/* *****************************************************************************
 *                             Пересылки
 * *****************************************************************************/

/* Sets the low DPFP value of src1 from the low value of src2 */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movsd (__v2df src1, __v2df src2)
{
    type_union_128 dst, s2;
    dst.__v2df = src1;
    s2.__v2df = src2;
    dst.d.d0 = s2.d.d0;
    return dst.__v2df;
}

/* Moves the lower 64 bits to the result and sets the upper 64 bits  to zero */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movq128 (__v2di src)
{
    type_union_128 s, dst;
    dst.__v2di = src;
    dst.l.l1 = 0LL;
    return dst.__v2di;
}

/* *****************************************************************************
 *                             Перестановки
 * *****************************************************************************/

/* перестановка 4-х входных интов в соответствии с размещением, указанным в 8-ми
 * младших разрядах константы 2-го операнда */
#define __builtin_ia32_pshufd(src1, src2) ({                                      \
    type_union_128 __s1, __dst;                                                   \
    __s1.__v4si = src1;                                                           \
    __dst.l.l0 = __builtin_e2k_pshufw (__s1.l.l1, __s1.l.l0, (src2) & 15);        \
    __dst.l.l1 = __builtin_e2k_pshufw (__s1.l.l1, __s1.l.l0, ((src2) >> 4) & 15); \
    __dst.__v4si;                                                                 \
})

/* выделение из 4-х входных даблов 2-х, положение которых определяется в 2-х
 * младших разрядах константы 3-го операнда */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_shufpd (__v2df src1, __v2df src2, int mask)
{
    type_union_128 s1, s2, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    dst.l.l0 = (mask & 1) ? s1.l.l1 : s1.l.l0;
    dst.l.l1 = (mask & 2) ? s2.l.l1 : s2.l.l0;
    return dst.__v2df;
}

/* перестановка 4-х старших шортов в соответствии с порядком, определенным в 8-ми младших
 * разрядах константы 2-го операнда */
#define __builtin_ia32_pshufhw(src1, src2) ({                     \
    type_union_128 __s1;                                          \
    __s1.__v8hi = src1;                                           \
    __s1.l.l1 = __builtin_e2k_pshufh (__s1.l.l1, (src2) & 0xff);  \
    __s1.__v8hi;                                                  \
})

/* перестановка 4-х младших шортов в соответствии с порядком, определенным в 8-ми младших
 * разрядах константы 2-го операнда */
#define __builtin_ia32_pshuflw(src1, src2) ({                     \
    type_union_128 __s1;                                          \
    __s1.__v8hi = src1;                                           \
    __s1.l.l0 = __builtin_e2k_pshufh (__s1.l.l0, (src2) & 0xff);  \
    __s1.__v8hi;                                                  \
})

/* *****************************************************************************
 *                         Целочисленные операции
 * *****************************************************************************/

/* сложение 16-ти байт (8S/8U) по модулю */
PACKED_SSE_BUILTINS (paddb128, paddb, __v16qi, __v16qi)

/* сложение 8-ми шортов (16S/16U) по модулю */
PACKED_SSE_BUILTINS (paddw128, paddh, __v8hi, __v8hi)

/* сложение 4-х интов (32S/32U) по модулю */
PACKED_SSE_BUILTINS (paddd128, paddw, __v4si, __v4si)

/* сложение 2-х лонгов (64S/64U) по модулю */
PACKED_SSE_BUILTINS (paddq128, paddd, __v2di, __v2di)

/* вычитание 16-ти байт (8S/8U) по модулю */
PACKED_SSE_BUILTINS (psubb128, psubb, __v16qi, __v16qi)

/* вычитание 8-ми шортов (16S/16U) по модулю */
PACKED_SSE_BUILTINS (psubw128, psubh, __v8hi, __v8hi)

/* вычитание 4-х интов (32S/32U) по модулю */
PACKED_SSE_BUILTINS (psubd128, psubw, __v4si, __v4si)

/* вычитание 2-х лонгов (64S/64U) по модулю */
PACKED_SSE_BUILTINS (psubq128, psubd, __v2di, __v2di)

/* сложение 16-ти знаковых байт (8S) c насыщением */
PACKED_SSE_BUILTINS (paddsb128, paddsb, __v16qi, __v16qi)

/* сложение 8-ми знаковых шортов (16S) c насыщением */
PACKED_SSE_BUILTINS (paddsw128, paddsh, __v8hi, __v8hi)

/* вычитание 16-ти знаковых байт (8S) c насыщением */
PACKED_SSE_BUILTINS (psubsb128, psubsb, __v16qi, __v16qi)

/* вычитание 8-ми знаковых шортов (16S) c насыщением */
PACKED_SSE_BUILTINS (psubsw128, psubsh, __v8hi, __v8hi)

/* сложение 16-ти беззнаковых байт (8U) c насыщением */
PACKED_SSE_BUILTINS (paddusb128, paddusb, __v16qi, __v16qi)

/* сложение 8-ми беззнаковых шортов (16U) c насыщением */
PACKED_SSE_BUILTINS (paddusw128, paddush, __v8hi, __v8hi)

/* вычитание 16-ти беззнаковых байт (8U) c насыщением */
PACKED_SSE_BUILTINS (psubusb128, psubusb, __v16qi, __v16qi)

/* вычитание 8-ми беззнаковых шортов (16U) c насыщением */
PACKED_SSE_BUILTINS (psubusw128, psubush, __v8hi, __v8hi)

/* среднее 16-ти беззнаковых байт (8U) */
PACKED_SSE_BUILTINS (pavgb128, pavgusb, __v16qi, __v16qi)

/* среднее 8-ми беззнаковых шортов (16U) */
PACKED_SSE_BUILTINS (pavgw128, pavgush, __v8hi, __v8hi)

/* умножение 8-ми знаковых шортов (16S) и попарное сложение смежных интовых произведений */
PACKED_SSE_BUILTINS (pmaddwd128, pmaddh, __v8hi, __v4si)

/* умножение 8-ми знаковых шортов (16S) и выдача младших 16 разрядов произведений */
PACKED_SSE_BUILTINS (pmullw128, pmullh, __v8hi, __v8hi)

/* умножение 8-ми знаковых шортов (16S) и выдача старших 16 разрядов произведений */
PACKED_SSE_BUILTINS (pmulhw128, pmulhh, __v8hi, __v8hi)

/* умножение 8-ми беззнаковых шортов (16U) и выдача старших 16 разрядов произведений */
PACKED_SSE_BUILTINS (pmulhuw128, pmulhuh, __v8hi, __v8hi)

/* cложение абсолютных разностей 16-ти беззнаковых байт (8U) в 2 суммы */
PACKED_SSE_BUILTINS_WITH_SCALAR_OPS (psadbw128, psadbw, __v16qi, __v8hi)

/* максимум 8-ми беззнаковых байт (8U) */
PACKED_SSE_BUILTINS (pmaxub128, pmaxub, __v16qi, __v16qi)

/* максимум 8-ми знаковых шортов (16S) */
PACKED_SSE_BUILTINS (pmaxsw128, pmaxsh, __v8hi, __v8hi)

/* минимум 16-ти беззнаковых байт (8U) */
PACKED_SSE_BUILTINS (pminub128, pminub, __v16qi, __v16qi)

/* минимум 8-ми знаковых шортов (16S) */
PACKED_SSE_BUILTINS (pminsw128, pminsh, __v8hi, __v8hi)

/* умножение интов (32S) с получением лонга (64S) */
TWO_OPERANDS_BUILTINS (pmuludq, umulx, __v2si, __v1di)

/* умножение 2-х интов (32S) с получением 2-х лонгов (64S) */
PACKED_SSE_BUILTINS_WITH_SCALAR_OPS (pmuludq128, umulx, __v4si, __v2di)

/* сдвиг влево 8-ми шортов (16S/16U) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (psllw128, psllh, __v8hi, __v8hi, __v8hi)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (psllwi128, psllh, __v8hi, int, __v8hi)

/* сдвиг влево 4-х интов (32S/32U) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (pslld128, psllw, __v4si, __v4si, __v4si)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (pslldi128, psllw, __v4si, int, __v4si)

/* сдвиг влево 2-х лонгов (64S/64U) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (psllq128, pslld, __v2di, __v2di, __v2di)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (psllqi128, pslld, __v2di, int, __v2di)

/* логический сдвиг вправо 8-ми шортов (16S/16U) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (psrlw128, psrlh, __v8hi, __v8hi, __v8hi)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (psrlwi128, psrlh, __v8hi, int, __v8hi)

/* логический сдвиг вправо 4-х интов (32S/32U) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (psrld128, psrlw, __v4si, __v4si, __v4si)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (psrldi128, psrlw, __v4si, int, __v4si)

/* логический сдвиг вправо 2-х лонгов (64S/64U) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (psrlq128, psrld, __v2di, __v2di, __v2di)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (psrlqi128, psrld, __v2di, int, __v2di)

/* арифметический сдвиг вправо 8-ми знаковых шортов (16S) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (psraw128, psrah, __v8hi, __v8hi, __v8hi)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (psrawi128, psrah, __v8hi, int, __v8hi)

/* арифметический сдвиг вправо 4-х знаковых интов (32S) */
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V (psrad128, psraw, __v4si, __v4si, __v4si)
PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S (psradi128, psraw, __v4si, int, __v4si)

/* сдвиг влево 16-ти байт на число байт, равное константе во 2-м операнде */
#define __builtin_ia32_pslldqi128(src1, src2) ({                           \
    type_union_128 __s1, __dst;                                            \
    __s1.__v2di = src1;                                                    \
    __dst.l.l1 = __builtin_e2k_psllqh (__s1.l.l1, __s1.l.l0, (src2) >> 3); \
    __dst.l.l0 = ((src2) >= 64) ? 0 :                                      \
             __builtin_e2k_psllql (__s1.l.l1, __s1.l.l0, (src2) >> 3);     \
    __dst.__v2di;                                                          \
})

/* сдвиг вправо 16-ти байт на число байт, равное константе во 2-м операнде */
#define __builtin_ia32_psrldqi128(src1, src2) ({                           \
    type_union_128 __s1, __dst;                                            \
    __s1.__v2di = src1;                                                    \
    __dst.l.l1 = ((src2) >= 64) ? 0 :                                      \
             __builtin_e2k_psrlqh (__s1.l.l1, __s1.l.l0, (src2) >> 3);     \
    __dst.l.l0 = __builtin_e2k_psrlql (__s1.l.l1, __s1.l.l0, (src2) >> 3); \
    __dst.__v2di;                                                          \
})

/* *****************************************************************************
 *                                Cравнение
 * *****************************************************************************/

/* сравнение на "равно" 16-ти байт (8S/8U) */
PACKED_SSE_BUILTINS (pcmpeqb128, pcmpeqb, __v16qi, __v16qi)

/* сравнение на "равно" 8-ми шортов (16S/16U) */
PACKED_SSE_BUILTINS (pcmpeqw128, pcmpeqh, __v8hi, __v8hi)

/* сравнение на "равно" 4-х интов (32S/32U) */
PACKED_SSE_BUILTINS (pcmpeqd128, pcmpeqw, __v4si, __v4si)

/* сравнение на "больше" 16-ти знаковых байт (8S) */
PACKED_SSE_BUILTINS (pcmpgtb128, pcmpgtb, __v16qi, __v16qi)

/* сравнение на "больше" 8-ми знаковых шортов (16S) */
PACKED_SSE_BUILTINS (pcmpgtw128, pcmpgth, __v8hi, __v8hi)

/* сравнение на "больше" 4-х знаковых интов (32S) */
PACKED_SSE_BUILTINS (pcmpgtd128, pcmpgtw, __v4si, __v4si)

/* *****************************************************************************
 *                               Распаковки / упаковки
 * *****************************************************************************/

/* Selects and interleaves the upper two DPFP values from src1 and src2 */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpckhpd (__v2df src1, __v2df src2)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s2.l.l0 = s1.l.l1;
    return s2.__v2df;
}

/* чередование старшего лонга (64S) операнда 1 и старшего лонга (64S) операнда 2 */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpckhqdq128 (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2;
    s1.__v2di = src1;
    s2.__v2di = src2;
    s2.l.l0 = s1.l.l1;
    return s2.__v2di;
}

/* Selects and interleaves the lower two DPFP values from src1 and src2 */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpcklpd (__v2df src1, __v2df src2)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s1.l.l1 = s2.l.l0;
    return s1.__v2df;
}

/* чередование младшего лонга (64S) операнда 1 и младшего лонга (64S) операнда 2 */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpcklqdq128 (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2;
    s1.__v2di = src1;
    s2.__v2di = src2;
    s1.l.l1 = s2.l.l0;
    return s1.__v2di;
}

/* чередование 8-ми старших байт (8U) операнда 1 и 8-ми старших байт (8U) операнда 2 */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpckhbw128 (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhbh (s2.l.l1, s1.l.l1);
    dst.l.l0 = __builtin_e2k_punpcklbh (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,
                                        __builtin_e2k_qppackdl (0x1f0f1e0e1d0d1c0cLL, 0x1b0b1a0a19091808LL));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* чередование 8-ми младших байт (8U) операнда 1 и 8-ми младших байт (8U) операнда 2 */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpcklbw128 (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhbh (s2.l.l0, s1.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklbh (s2.l.l0, s1.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,
                                        __builtin_e2k_qppackdl (0x1707160615051404LL, 0x1303120211011000LL));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* чередование 4-х старших шортов (16U) операнда 1 и 4-х старших шортов (16U) операнда 2 */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpckhwd128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhhw (s2.l.l1, s1.l.l1);
    dst.l.l0 = __builtin_e2k_punpcklhw (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,
                                        __builtin_e2k_qppackdl (0x1f1e0f0e1d1c0d0cLL, 0x1b1a0b0a19180908LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* чередование 4-х младших шортов (16U) операнда 1 и 4-х младших шортов (16U) операнда 2 */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpcklwd128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhhw (s2.l.l0, s1.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklhw (s2.l.l0, s1.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,
                                        __builtin_e2k_qppackdl (0x1716070615140504LL, 0x1312030211100100LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* чередование 2-х старших интов (32U) операнда 1 и 2-х старших интов (32U) операнда 2 */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpckhdq128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.__v4sf = __builtin_ia32_unpckhps (s1.__v4sf, s2.__v4sf);
    return dst.__v4si;
}

/* чередование 2-х младших интов (32U) операнда 1 и 2-х младших интов (32U) операнда 2 */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_punpckldq128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.__v4sf = __builtin_ia32_unpcklps (s1.__v4sf, s2.__v4sf);
    return dst.__v4si;
}

/* упаковка 16-ти знаковых шортов (16S) в знаковые байты (8S) с насыщением */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_packsswb128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_packsshb (s2.l.l1, s2.l.l0);
    dst.l.l0 = __builtin_e2k_packsshb (s1.l.l1, s1.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpacksshb (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* упаковка 8-ми знаковых интов (32S) в знаковые шорты (16S) с насыщением */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_packssdw128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_packsswh (s2.l.l1, s2.l.l0);
    dst.l.l0 = __builtin_e2k_packsswh (s1.l.l1, s1.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpacksswh (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* упаковка 16-ти знаковых шортов (16S) в беззнаковые байты (8U) с насыщением */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_packuswb128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_packushb (s2.l.l1, s2.l.l0);
    dst.l.l0 = __builtin_e2k_packushb (s1.l.l1, s1.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpackushb (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* *****************************************************************************
 *                               Выделение маски
 * *****************************************************************************/

/* формирование 16-разрядной маски из знаков каждого байта (8S) */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovmskb128 (__v16qi src)
{
    type_union_128 s;
    s.__v16qi = src;
#if __iset__ <= 4
    return __builtin_e2k_pmovmskb (s.l.l1, s.l.l0);
#else /* __iset__ <= 4 */
    return __builtin_e2k_qpsgn2mskb (s.__v2di);
#endif /* __iset__ <= 4 */
}

/* формирование 2-разрядной маски из знаков каждого лонга (64S) */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movmskpd (__v2df src)
{
    type_union_128 s;
    s.__v2df = src;
    return __builtin_e2k_pmovmskpd (s.l.l1, s.l.l0);
}

/* *****************************************************************************
 *                               Запись по маске
 * *****************************************************************************/

/* условная запись 16 байтов из src при наличии "1" в старшем разряде соответствующего
 * байта select */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskmovdqu (__v16qi src, __v16qi select, char *p)
{
#if __iset__ <= 4
    type_union_128 s, sel;
    s.__v16qi = src;
    sel.__v16qi = select;
    __di mask_hi = (__di) __builtin_ia32_pcmpgtb ((__v8qi) 0LL, (__v8qi) sel.l.l1);
    __di mask_lo = (__di) __builtin_ia32_pcmpgtb ((__v8qi) 0LL, (__v8qi) sel.l.l0);
    __di dst_lo = *((__di *) p);
    __di dst_hi = *(((__di *) p) + 1);
    *((__di *) p)       = __builtin_e2k_pmerge (dst_lo, s.l.l0, mask_lo);
    *(((__di *) p) + 1) = __builtin_e2k_pmerge (dst_hi, s.l.l1, mask_hi);
/* FIXME: может быть невыровненный указатель
    if (sel.l.l0 & (0x80LL))       p[ 0] = s.l.l0;
    if (sel.l.l0 & (0x80LL << 8))  p[ 1] = s.l.l0 >> 8;
    if (sel.l.l0 & (0x80LL << 16)) p[ 2] = s.l.l0 >> 16;
    if (sel.l.l0 & (0x80LL << 24)) p[ 3] = s.l.l0 >> 24;
    if (sel.l.l0 & (0x80LL << 32)) p[ 4] = s.l.l0 >> 32;
    if (sel.l.l0 & (0x80LL << 40)) p[ 5] = s.l.l0 >> 40;
    if (sel.l.l0 & (0x80LL << 48)) p[ 6] = s.l.l0 >> 48;
    if (sel.l.l0 & (0x80LL << 56)) p[ 7] = s.l.l0 >> 56;
    if (sel.l.l1 & (0x80LL))       p[ 8] = s.l.l1;
    if (sel.l.l1 & (0x80LL << 8))  p[ 9] = s.l.l1 >> 8;
    if (sel.l.l1 & (0x80LL << 16)) p[10] = s.l.l1 >> 16;
    if (sel.l.l1 & (0x80LL << 24)) p[11] = s.l.l1 >> 24;
    if (sel.l.l1 & (0x80LL << 32)) p[12] = s.l.l1 >> 32;
    if (sel.l.l1 & (0x80LL << 40)) p[13] = s.l.l1 >> 40;
    if (sel.l.l1 & (0x80LL << 48)) p[14] = s.l.l1 >> 48;
    if (sel.l.l1 & (0x80LL << 56)) p[15] = s.l.l1 >> 56;
*/
#elif __iset__ <= 5
    __v2di spec, dst,
           *qp = (__v2di *) E2K_ALIGN_PTR_BACK (p, 16);
    int align = E2K_BYTES_FROM_ALIGN (p, 16);
    int mask = __builtin_e2k_qpsgn2mskb ((__v2di) select);

    E2K_PREPARE_ALIGN128 (align, spec);
    E2K_ALIGN_DATA128 ((__v2di) src, (__v2di) src, dst, spec);
    __builtin_e2k_pst_128 (dst, qp, mask << align);
    __builtin_e2k_pst_128 (dst, qp + 1, (mask << align) >> 16);
#else /* __iset__ <= 5 */
    int mask = __builtin_e2k_qpsgn2mskb ((__v2di) select);
    __builtin_e2k_pst_128 ((__v2di) src, p, mask);
#endif /* __iset__ <= 5 */
}

/* *****************************************************************************
 *                            Чтения / Записи
 * *****************************************************************************/

/* Load two DPFP values from P.  The address need not be 16-byte aligned */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadupd (const double *p)
{
    type_union_128 dst;
#if __iset__ <= 4 || (__iset__ == 5 && defined(__ALIGNED__))
    dst.l.l0 = ((__di *) p)[0];
    dst.l.l1 = ((__di *) p)[1];
#else /* __iset__ <= 4 || (__iset__ == 5 && defined(__ALIGNED__)) */
    dst.__v2df = *((__v2df *) p);
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* Store two DPFP values.  The address need not be 16-byte aligned */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storeupd (double *p, __v2df src)
{
#if __iset__ <= 4 || (__iset__ == 5 && defined(__ALIGNED__))
    type_union_128 s;
    s.__v2df = src;
    p[0] = s.d.d0;
    p[1] = s.d.d1;
#else /* __iset__ <= 4 || (__iset__ == 5 && defined(__ALIGNED__)) */
    *((__v2df *) p) = src;
#endif /* __iset__ <= 5 */
}

/* Sets the upper DPFP value with 64-bits of data loaded from p;
   the lower value is passed through from src */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadhpd (__v2df src, double const *p)
{
    type_union_128 s;
    s.__v2df = src;
    s.d.d1 = *p;
    return s.__v2df;
}

/* Sets the lower DPFP value with 64-bits of data loaded from p;
   the upper value is passed through from src */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadlpd (__v2df src, double const *p)
{
    type_union_128 s;
    s.__v2df = src;
    s.d.d0 = *p;
    return s.__v2df;
}

/* Stores the data in src to the address p without polluting the caches */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movnti (int *p, int src)
{
    __builtin_e2k_st_32u_nt (src, p);
}

/* Stores the data in src to the address p without polluting the caches */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movnti64 (long long int *p, long long int src)
{
    __builtin_e2k_st_64s_nt (src, p);
}

/* Stores the data in src to the address p without polluting the caches. The address must be 16-byte aligned */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntpd (double *p, __v2df src)
{
    type_union_128 s;
    s.__v2df = src;
    __builtin_ia32_movntps ((float *) p, s.__v4sf);
}

/* Stores the data in src to the address p without polluting the caches. The address must be 16-byte aligned */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntdq (__v2di *p, __v2di src)
{
    __builtin_ia32_movntpd ((double *) p, (__v2df) src);
}

/* Loads 128-bit value from p.  The address not need be 16-byte aligned */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loaddqu (const char *p)
{
    type_union_128 dst;
    dst.__v4sf = __builtin_ia32_loadups ((const float *) p);
    return dst.__v16qi;
}

/* Stores 128-bit value.  The address not need be 16-byte aligned */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storedqu (char *p, __v16qi src)
{
    type_union_128 s;
    s.__v16qi = src;
    __builtin_ia32_storeups ((float *) p, s.__v4sf);
}

/* Guarantees that every preceding load is globally visible before
   any subsequent load */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_lfence ()
{
#pragma no_asm_inline
    asm ("wait ld_c = 1");
}

/* Guarantees that every preceding memory access is globally visible before
   any subsequent memory access */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_mfence ()
{
#pragma no_asm_inline
    asm ("wait all_c = 1");
}

/* Cache line contining p is flushed and invalidated from all caches in the
   coherency domain */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_clflush (void const *p)
{
    __builtin_e2k_clflush (p);
}

/*#undef TWO_OPERANDS_BUILTINS*/

#undef PACKED_SSE_BUILTINS_WITH_SCALAR_OPS
#undef PACKED_SSE_BUILTINS
#undef PACKED_SSE_BUILTINS_REVERSE

#undef SCALAR_SSE2_BUILTINS
#undef SCALAR_COMPARE_SSE2_BUILTINS
#undef SCALAR_UCOMPARE_SSE2_BUILTINS
#undef PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_V
#undef PACKED_ONE_OPERAND_AND_LITERAL_SSE2_BUILTINS_S

#endif /* __SSE2__ */

#ifdef __SSE3__

/*******************************************************************************/
/****************************** SSE3 builtins **********************************/
/*******************************************************************************/

#if __iset__ <= 4

#define PACKED_HORIZONTAL_SSE_BUILTINS(name,instr,src_type, dst_type)  \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src1, src_type src2)                   \
{                                                                      \
    type_union_128 s1, s2, dst;                                        \
    __di tmp0, tmp1;                                                   \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp0)                                        \
       : [src1_name] "rI" (s1.l.l0), [src2_name] "ri" (s1.l.l1));      \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp1)                                        \
       : [src1_name] "rI" (s2.l.l0), [src2_name] "ri" (s2.l.l1));      \
    dst.l.l0 = tmp0;                                                   \
    dst.l.l1 = tmp1;                                                   \
    return dst.dst_type;                                               \
}

#else /* __iset__ <= 4 */

/*FIXME: #83341 - в p9 нет операций даблового горизонтального сложения/вычитания*/
#define PACKED_HORIZONTAL_SSE_BUILTINS(name,instr,src_type, dst_type)  \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src1, src_type src2)                   \
{                                                                      \
    type_union_128 s1, s2, dst;                                        \
    __v2di tmp;                                                        \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
    __v2di tmp0 = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,         \
        __builtin_e2k_qppackdl (0x1f1e1d1c1b1a1918LL, 0x0f0e0d0c0b0a0908LL));\
    __v2di tmp1 = __builtin_e2k_qppermb (s2.__v2di, s1.__v2di,         \
        __builtin_e2k_qppackdl (0x1716151413121110LL, 0x0706050403020100LL));\
_Pragma ("asm_inline")                                                 \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"           \
       : [dst_name] "=r" (tmp)                                         \
       : [src1_name] "r" (tmp1), [src2_name] "r" (tmp0));              \
    dst.__v2di = tmp;                                                  \
    return dst.dst_type;                                               \
}

#endif /* __iset__ <= 4 */

/* *****************************************************************************
 *                          Плавающие операции
 * *****************************************************************************/

/* сложение нечетных и вычитание четных флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_addsubps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    s2.l.l0 ^= 0x80000000LL;
    s2.l.l1 ^= 0x80000000LL;
    dst.l.l0 = __builtin_e2k_pfadds (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pfadds (s1.l.l1, s2.l.l1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pfaddsubs (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pfaddsubs (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfaddsubs (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* сложение нечетных и вычитание четных даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_addsubpd (__v2df src1, __v2df src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
#if __iset__ <= 4
    dst.d.d0 = s1.d.d0 - s2.d.d0;
    dst.d.d1 = s1.d.d1 + s2.d.d1;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfaddsubd (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2df;
}

/* горизонтальное сложение флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_haddps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0  = __builtin_e2k_pshufw (s1.l.l1, s1.l.l0, 8);
    __di tmp2 = __builtin_e2k_pshufw (s1.l.l1, s1.l.l0, 0xd);
    dst.l.l0 = __builtin_e2k_pfadds (tmp0, tmp2);
    __di tmp1  = __builtin_e2k_pshufw (s2.l.l1, s2.l.l0, 8);
    __di tmp3 = __builtin_e2k_pshufw (s2.l.l1, s2.l.l0, 0xd);
    dst.l.l1 = __builtin_e2k_pfadds (tmp1, tmp3);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pfhadds (s1.l.l0, s1.l.l1);
    dst.l.l1 = __builtin_e2k_pfhadds (s2.l.l0, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfhadds (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* горизонтальное сложение даблов (64F) */
PACKED_HORIZONTAL_SSE_BUILTINS (haddpd, pfaddd, __v2df, __v2df)

/* горизонтальное вычитание флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_hsubps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0  = __builtin_e2k_pshufw (s1.l.l1, s1.l.l0, 8);
    __di tmp2 = __builtin_e2k_pshufw (s1.l.l1, s1.l.l0, 0xd);
    dst.l.l0 = __builtin_e2k_pfsubs (tmp0, tmp2);
    __di tmp1  = __builtin_e2k_pshufw (s2.l.l1, s2.l.l0, 8);
    __di tmp3 = __builtin_e2k_pshufw (s2.l.l1, s2.l.l0, 0xd);
    dst.l.l1 = __builtin_e2k_pfsubs (tmp1, tmp3);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pfhsubs (s1.l.l0, s1.l.l1);
    dst.l.l1 = __builtin_e2k_pfhsubs (s2.l.l0, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfhsubs (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* горизонтальное вычитание даблов (64F) */
PACKED_HORIZONTAL_SSE_BUILTINS (hsubpd, pfsubd, __v2df, __v2df)

/* *****************************************************************************
 *                             Пересылки
 * *****************************************************************************/

/* Duplicates odd SPFP elements into even elements */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movshdup (__v4sf src)
{
    type_union_128 s, dst;
    s.__v4sf = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_punpckhwd (s.l.l0, s.l.l0);
    dst.l.l1 = __builtin_e2k_punpckhwd (s.l.l1, s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                __builtin_e2k_qppackdl (0x0f0e0d0c0f0e0d0cLL, 0x0706050407060504LL));
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* Duplicates even SPFP elements into odd elements */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movsldup (__v4sf src)
{
    type_union_128 s, dst;
    s.__v4sf = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_punpcklwd (s.l.l0, s.l.l0);
    dst.l.l1 = __builtin_e2k_punpcklwd (s.l.l1, s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                __builtin_e2k_qppackdl (0x0b0a09080b0a0908LL, 0x0302010003020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* *****************************************************************************
 *                            Чтения / Записи
 * *****************************************************************************/

/* Loads 128-bit value from p.  The address not need be 16-byte aligned */
#define __builtin_ia32_lddqu __builtin_ia32_loaddqu

/* *****************************************************************************
 *                            Мониторы
 * *****************************************************************************/

__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_monitor (void const *p, unsigned int __E, unsigned int __H)
{
/* FIXME: */
}

__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_mwait (unsigned int __E, unsigned int __H)
{
/* FIXME: */
}

#undef PACKED_HORIZONTAL_SSE_BUILTINS

#endif /* __SSE3__ */

#ifdef __SSSE3__

/*******************************************************************************/
/***************************** SSSE3 builtins *********************************/
/*******************************************************************************/

/* *****************************************************************************
 *                Горизонтальное сложение и вычитание по модулю
 * *****************************************************************************/

/* горизонтальное сложение 4-х пар шортов (16S) */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phaddw (__v4hi src1, __v4hi src2)
{
#if __iset__ <= 2
    __di tmp1 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0d0c090805040100LL);
    __di tmp2 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0f0e0b0a07060302LL);
    return (__v4hi) __builtin_e2k_paddh (tmp1, tmp2);
#else /* __iset__ <= 2 */
    return (__v4hi) __builtin_e2k_phaddh ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* горизонтальное сложение 8-ми пар шортов (16S) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phaddw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_phaddw ((__v4hi) s1.l.l0, (__v4hi) s1.l.l1);
    dst.l.l1 = (__di) __builtin_ia32_phaddw ((__v4hi) s2.l.l0, (__v4hi) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qphaddh (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* горизонтальное вычитание 4-х пар шортов (16S) */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phsubw (__v4hi src1, __v4hi src2)
{
#if __iset__ <= 2
    __di tmp1 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0d0c090805040100LL);
    __di tmp2 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0f0e0b0a07060302LL);
    return (__v4hi) __builtin_e2k_psubh (tmp1, tmp2);
#else /* __iset__ <= 2 */
    return (__v4hi) __builtin_e2k_phsubh ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* горизонтальное вычитание 8-ми пар шортов (16S) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phsubw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_phsubw ((__v4hi) s1.l.l0, (__v4hi) s1.l.l1);
    dst.l.l1 = (__di) __builtin_ia32_phsubw ((__v4hi) s2.l.l0, (__v4hi) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qphsubh (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* горизонтальное сложение 2-х пар интов (32S) */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phaddd (__v2si src1, __v2si src2)
{
#if __iset__ <= 2
    __di tmp1 = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 0x8);
    __di tmp2 = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 0xd);
    return (__v2si) __builtin_e2k_paddw (tmp1, tmp2);
#else /* __iset__ <= 2 */
    return (__v2si) __builtin_e2k_phaddw ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* горизонтальное сложение 4-х пар интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phaddd128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_phaddd ((__v2si) s1.l.l0, (__v2si) s1.l.l1);
    dst.l.l1 = (__di) __builtin_ia32_phaddd ((__v2si) s2.l.l0, (__v2si) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qphaddw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* горизонтальное вычитание 2-х пар интов (32S) */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phsubd (__v2si src1, __v2si src2)
{
#if __iset__ <= 2
    __di tmp1 = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 0x8);
    __di tmp2 = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 0xd);
    return (__v2si) __builtin_e2k_psubw (tmp1, tmp2);
#else /* __iset__ <= 2 */
    return (__v2si) __builtin_e2k_phsubw ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* горизонтальное вычитание 4-х пар интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phsubd128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_phsubd ((__v2si) s1.l.l0, (__v2si) s1.l.l1);
    dst.l.l1 = (__di) __builtin_ia32_phsubd ((__v2si) s2.l.l0, (__v2si) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qphsubw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* *****************************************************************************
 *                Горизонтальное сложение и вычитание c насыщением
 * *****************************************************************************/

/* горизонтальное сложение 4-х пар шортов (16S) c насыщением */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phaddsw (__v4hi src1, __v4hi src2)
{
#if __iset__ <= 2
    __di tmp1 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0d0c090805040100LL);
    __di tmp2 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0f0e0b0a07060302LL);
    return (__v4hi) __builtin_e2k_paddsh (tmp1, tmp2);
#else /* __iset__ <= 2 */
    return (__v4hi) __builtin_e2k_phaddsh ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* горизонтальное сложение 8-ми пар шортов (16S) c насыщением */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phaddsw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_phaddsw ((__v4hi) s1.l.l0, (__v4hi) s1.l.l1);
    dst.l.l1 = (__di) __builtin_ia32_phaddsw ((__v4hi) s2.l.l0, (__v4hi) s2.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qphaddsh (s1.__v2di, s2.__v2di);
    dst.__v2di = tmp;
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* горизонтальное вычитание 4-х пар шортов (16S) c насыщением */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phsubsw (__v4hi src1, __v4hi src2)
{
#if __iset__ <= 2
    __di tmp1 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0d0c090805040100LL);
    __di tmp2 = __builtin_e2k_pshufb ((__di) src2, (__di) src1, 0x0f0e0b0a07060302LL);
    return (__v4hi) __builtin_e2k_psubsh (tmp1, tmp2);
#else /* __iset__ <= 2 */
    return (__v4hi) __builtin_e2k_phsubsh ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* горизонтальное вычитание 8-ми пар шортов (16S) c насыщением */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phsubsw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_phsubsw ((__v4hi) s1.l.l0, (__v4hi) s1.l.l1);
    dst.l.l1 = (__di) __builtin_ia32_phsubsw ((__v4hi) s2.l.l0, (__v4hi) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qphsubsh (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* *****************************************************************************
 *                 Умножение байт с горизонтальным сложением
 * *****************************************************************************/

/* умножение 8-ми беззнаковых байт (8U) на 8 знаковых байт (8S) и
 * попарное сложение смежных шортовых произведений с сатурацией */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmaddubsw (__v8qi src1, __v8qi src2)
{
    __di dst;
#if  __iset__ <= 2
    __di tmp_hi = __builtin_e2k_punpckhbh ((__di) src2, 0);
    __di tmp_lo = __builtin_e2k_punpcklbh ((__di) src2, 0);
    tmp_hi = __builtin_e2k_pmulubhh ((__di) src1 >> 32, tmp_hi);
    tmp_lo = __builtin_e2k_pmulubhh ((__di) src1, tmp_lo);
    dst = (__di) __builtin_ia32_phaddsw ((__v4hi) tmp_lo, (__v4hi) tmp_hi);
#else /* __iset__ <= 2 */
    dst = __builtin_e2k_pmaddubsh ((__di) src2, (__di) src1);
#endif /* __iset__ <= 2 */
    return (__v4hi) dst;
}

/* умножение 16-ми беззнаковых байт (8U) на 16 знаковых байт (8S) и
 * попарное сложение смежных шортовых произведений с сатурацией */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmaddubsw128 (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_pmaddubsw ((__v8qi) s1.l.l0, (__v8qi) s2.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_pmaddubsw ((__v8qi) s1.l.l1, (__v8qi) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaddubsh (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* *****************************************************************************
 *                    Умножение шортов с масштабированием
 * *****************************************************************************/

/* умножение 4-х знаковых шортов (16S) c масштабированием (>> 15) и округлением */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmulhrsw (__v4hi src1, __v4hi src2)
{
    __di dst;
#if __iset__ <= 2
    __di tmp1_hi = __builtin_e2k_pmulhh    ((__di) src1, (__di) src2);
    __di tmp1_lo = __builtin_e2k_pmullh    ((__di) src1, (__di) src2);
    __di tmp2_hi = __builtin_e2k_punpckhhw (tmp1_hi, tmp1_lo);
    __di tmp2_lo = __builtin_e2k_punpcklhw (tmp1_hi, tmp1_lo);
    tmp2_hi = __builtin_e2k_paddw     (tmp2_hi, 0x400000004000LL);
    tmp2_lo = __builtin_e2k_paddw     (tmp2_lo, 0x400000004000LL);
    tmp2_hi = __builtin_e2k_psraw     (tmp2_hi, 15);
    tmp2_lo = __builtin_e2k_psraw     (tmp2_lo, 15);
    dst = __builtin_e2k_packsswh (tmp2_hi, tmp2_lo);
#else /* __iset__ <= 2 */
    dst = __builtin_e2k_pmulhrsh ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
    return (__v4hi) dst;
}

/* умножение 8-ми знаковых шортов (16S) c масштабированием (>> 15) и округлением */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmulhrsw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_pmulhrsw ((__v4hi) s1.l.l0, (__v4hi) s2.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_pmulhrsw ((__v4hi) s1.l.l1, (__v4hi) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmulhrsh (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* *****************************************************************************
 *                             Перестановка байт
 * *****************************************************************************/

/* перестановка 8-ми входных байт, положение которых определяется значениями
 * в соответствующих байтах 2-го операнда. Либо заполнение 0 */
__E2K_INLINE __v8qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pshufb (__v8qi src1, __v8qi src2)
{
    return (__v8qi) __builtin_e2k_pshufb ((__di) src1, (__di) src1, (__di) src2 & 0x8787878787878787LL);
}

/* перестановка 16-ти входных байт, положение которых определяется значениями
 * в соответствующих байтах 2-го операнда. Либо заполнение 0 */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pshufb128 (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pshufb (s1.l.l1, s1.l.l0, s2.l.l0 & 0x8f8f8f8f8f8f8f8fLL);
    dst.l.l1 = __builtin_e2k_pshufb (s1.l.l1, s1.l.l0, s2.l.l1 & 0x8f8f8f8f8f8f8f8fLL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpshufb (s1.__v2di, s1.__v2di,
                     __builtin_e2k_qpand (s2.__v2di, __builtin_e2k_qppackdl (0x8f8f8f8f8f8f8f8fLL, 0x8f8f8f8f8f8f8f8fLL)));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* *****************************************************************************
 *                            Изменение знака
 * *****************************************************************************/

/* умножение 8-ми знаковых байт (8S) на знаки 8-ми байт (8S) второго аргумента */
__E2K_INLINE __v8qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psignb (__v8qi src1, __v8qi src2)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_psubb (0, (__di) src1);
    __di zero_mask = __builtin_e2k_pcmpeqb (0, (__di) src2);
 #if __iset__ == 2
    return (__v8qi) (__builtin_e2k_pmerge ((__di) src1, dst, (__di) src2) & ~zero_mask);
 #else /* __iset__ == 2 */
    __di neg_mask = __builtin_e2k_pcmpgtb  (0, (__di) src2);
    return (__v8qi) ((((__di) src1 & ~neg_mask) | (dst & neg_mask)) & ~zero_mask);
 #endif /* __iset__ == 2 */
#else /* __iset__ <= 2 */
    return (__v8qi) __builtin_e2k_psignb ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* умножение 4-х знаковых шортов (16S) на знаки 4-х шортов (16S) второго аргумента */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psignw (__v4hi src1, __v4hi src2)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_psubh (0, (__di) src1);
    __di zero_mask = __builtin_e2k_pcmpeqh (0, (__di) src2);
    __di neg_mask = __builtin_e2k_pcmpgth  (0, (__di) src2);
 #if __iset__ == 2
    return (__v4hi) (__builtin_e2k_pmerge ((__di) src1, dst, neg_mask) & ~zero_mask);
 #else /* __iset__ == 2 */
    return (__v4hi) ((((__di) src1 & ~neg_mask) | (dst & neg_mask)) & ~zero_mask);
 #endif /* __iset__ == 2 */
#else /* __iset__ <= 2 */
    return (__v4hi) __builtin_e2k_psignh ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* умножение 2-х знаковых интов (32S) на знаки 2-х интов (32S) второго аргумента */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psignd (__v2si src1, __v2si src2)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_psubw (0, (__di) src1);
    __di zero_mask = __builtin_e2k_pcmpeqw (0, (__di) src2);
    __di neg_mask = __builtin_e2k_pcmpgtw  (0, (__di) src2);
 #if __iset__ == 2
    return (__v2si) (__builtin_e2k_pmerge ((__di) src1, dst, neg_mask) & ~zero_mask);
 #else /* __iset__ == 2 */
    return (__v2si) ((((__di) src1 & ~neg_mask) | (dst & neg_mask)) & ~zero_mask);
 #endif /* __iset__ == 2 */
#else /* __iset__ <= 2 */
    return (__v2si) __builtin_e2k_psignw ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
}

/* умножение 16-ти знаковых байт (8S) на знаки 16-ть байт (8S) второго аргумента */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psignb128 (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_psignb ((__v8qi) s1.l.l0, (__v8qi) s2.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_psignb ((__v8qi) s1.l.l1, (__v8qi) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsignb (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* умножение 8-ми знаковых шортов (16S) на знаки 8-ми шортов (16S) второго аргумента */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psignw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_psignw ((__v4hi) s1.l.l0, (__v4hi) s2.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_psignw ((__v4hi) s1.l.l1, (__v4hi) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsignh (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* умножение 4-х знаковых интов (32S) на знаки 4-х интов (32S) второго аргумента */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psignd128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_psignd ((__v2si) s1.l.l0, (__v2si) s2.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_psignd ((__v2si) s1.l.l1, (__v2si) s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsignw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* *****************************************************************************
 *                            Абсолютное значение
 * *****************************************************************************/

/* абсолютные значения 8-ми знаковых байт (8S) */
__E2K_INLINE __v8qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pabsb (__v8qi src)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_pcmpgtb (0, (__di) src);
    return (__v8qi) __builtin_e2k_psubb ((__di) src ^ dst, dst);
#else /* __iset__ <= 2 */
    return (__v8qi) __builtin_e2k_psignb ((__di) src, (__di) src);
#endif /* __iset__ <= 2 */
}

/* абсолютные значения 4-х знаковых шортов (16S) */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pabsw (__v4hi src)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_psrah ((__di) src, 15);
    return (__v4hi) __builtin_e2k_psubh ((__di) src ^ dst, dst);
#else /* __iset__ <= 2 */
    return (__v4hi) __builtin_e2k_psignh ((__di) src, (__di) src);
#endif /* __iset__ <= 2 */
}

/* абсолютные значения 2-х знаковых интов (32S) */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pabsd (__v2si src)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_psraw ((__di) src, 31);
    return (__v2si) __builtin_e2k_psubw ((__di) src ^ dst, dst);
#else /* __iset__ <= 2 */
    return (__v2si) __builtin_e2k_psignw ((__di) src, (__di) src);
#endif /* __iset__ <= 2 */
}

/* абсолютные значения 16-ти знаковых байт (8S) */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pabsb128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_pabsb ((__v8qi) s.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_pabsb ((__v8qi) s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsignb (s.__v2di, s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* абсолютные значения 8-ми знаковых шортов (16S) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pabsw128 (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_pabsw ((__v4hi) s.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_pabsw ((__v4hi) s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsignh (s.__v2di, s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* абсолютные значения 4-х знаковых интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pabsd128 (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_pabsd ((__v2si) s.l.l0);
    dst.l.l1 = (__di) __builtin_ia32_pabsd ((__v2si) s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsignw (s.__v2di, s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* *****************************************************************************
 *                            Выравнивание
 * *****************************************************************************/

/* логический сдвиг вправо 16-ти байт (сцепленные первые 2 операнда) на число байт,
 * равное константе в 3-м операнде (величина подается в битах), и выдача младших 8 байт */
#define __builtin_ia32_palignr(src1, src2, shift) \
    (__v1di) __builtin_e2k_psrlql ((__di) (src1), (__di) (src2), (shift) >> 3)

/* логический сдвиг вправо 32-х байт (сцепленные первые 2 операнда) на число байт,
 * равное константе в 3-м операнде (величина подается в битах), и выдача младших 16 байт */

#if __iset__ <= 4

#define __builtin_ia32_palignr128(src1, src2, shift) ({                                       \
    type_union_128 __s1, __s2, __dst;                                                         \
    __s1.__v2di = src1;                                                                       \
    __s2.__v2di = src2;                                                                       \
    if ((shift) < 8 * 8) {                                                                    \
        __dst.l.l0 = __builtin_e2k_psrlql (__s2.l.l1, __s2.l.l0, ((shift) >> 3) & 15);        \
        __dst.l.l1 = __builtin_e2k_psrlql (__s1.l.l0, __s2.l.l1, ((shift) >> 3) & 15);        \
    }                                                                                         \
    else if ((shift) < 16 * 8) {                                                              \
        __dst.l.l0 = __builtin_e2k_psrlql (__s1.l.l0, __s2.l.l1, (((shift) >> 3) - 8) & 15);  \
        __dst.l.l1 = __builtin_e2k_psrlql (__s1.l.l1, __s1.l.l0, (((shift) >> 3) - 8) & 15);  \
    }                                                                                         \
    else if ((shift) < 24 * 8) {                                                              \
        __dst.l.l0 = __builtin_e2k_psrlql (__s1.l.l1, __s1.l.l0, (((shift) >> 3) - 16) & 15); \
        __dst.l.l1 = __s1.l.l1 >> (((shift) - 16 * 8) & 0x3f);                                \
    }                                                                                         \
    else if ((shift) < 32 * 8) {                                                              \
        __dst.l.l0 = __s1.l.l1 >> (((shift) - 24 * 8) & 0x3f);                                \
        __dst.l.l1 = 0;                                                                       \
    }                                                                                         \
    else {                                                                                    \
        __dst.l.l0 = __dst.l.l1 = 0;                                                          \
    }                                                                                         \
    __dst.__v2di;                                                                             \
})

#else /* __iset__ <= 4 */

#define __builtin_ia32_palignr128(src1, src2, shift) ({                   \
    type_union_128 __s1, __s2, __dst;                                     \
    __v2di __spec, __zero = __builtin_e2k_qppackdl (0, 0);                \
    __s1.__v2di = src1;                                                   \
    __s2.__v2di = src2;                                                   \
    int __align = (shift) >> 3;                                           \
    E2K_PREPARE_ALIGN128 ((__align & 0xf), __spec);                       \
    if (__align < 16) {                                                   \
        E2K_ALIGN_DATA128 (__s2.__v2di, __s1.__v2di, __dst.__v2di, __spec);\
    }                                                                     \
    else if (__align < 32) {                                              \
        E2K_ALIGN_DATA128 (__s1.__v2di, __zero, __dst.__v2di, __spec);    \
    }                                                                     \
    else {                                                                \
        __dst.__v2di = __zero;                                            \
    }                                                                     \
    __dst.__v2di;                                                         \
})

#endif /* __iset__ <= 4 */


#endif /* __SSSE3__ */

#ifdef __SSE4_1__

/*******************************************************************************/
/***************************** SSE4.1 builtins *********************************/
/*******************************************************************************/

/* *****************************************************************************
 *                            Побитовое сравнение
 * *****************************************************************************/

/* логическое AND 128-битных значений. Возвращает 1, если (src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ptestz128 (__v2di src1, __v2di src2)
{
#if __iset__ <= 4
    type_union_128 s1, s2;
    s1.__v2di = src1;
    s2.__v2di = src2;
    return ((s1.l.l0 & s2.l.l0) | (s1.l.l1 & s2.l.l1)) == 0;
#elif __iset__ <= 5
    type_union_128 dst;
    dst.__v2di = __builtin_e2k_qpand (src1, src2);
    return (dst.l.l0 | dst.l.l1) == 0;
#else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (__builtin_e2k_qpand (src1, src2), __builtin_e2k_qppackdl (0, 0));
#endif /* __iset__ <= 5 */
}

/* логическое ANDNOT 128-битных значений. Возвращает 1, если (~src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ptestc128 (__v2di src1, __v2di src2)
{
#if __iset__ <= 4
    type_union_128 s1, s2;
    s1.__v2di = src1;
    s2.__v2di = src2;
    return ((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1)) == 0;
#elif __iset__ <= 5
    type_union_128 dst;
    dst.__v2di = __builtin_e2k_qpandn (src2, src1);
    return (dst.l.l0 | dst.l.l1) == 0;
#else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (__builtin_e2k_qpandn (src2, src1), __builtin_e2k_qppackdl (0, 0));
#endif /* __iset__ <= 5 */
}

/* логическое AND и ANDNOT 128-битных значений. Возвращает 1, если
 * (src1 & src2) != 0 && (~src1 & src2) != 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ptestnzc128 (__v2di src1, __v2di src2)
{
#if __iset__ <= 4
    type_union_128 s1, s2;
    s1.__v2di = src1;
    s2.__v2di = src2;
    return ((s1.l.l0 &  s2.l.l0) | (s1.l.l1 &  s2.l.l1)) != 0 &&
           ((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1)) != 0;
#else /* __iset__ <= 4 */
    type_union_128 dst, dst1;
    dst.__v2di = __builtin_e2k_qpandn (src2, src1);
    dst1.__v2di = __builtin_e2k_qpand (src1, src2);
 #if __iset__ <= 5
    return (dst.l.l0 | dst.l.l1) != 0 && (dst1.l.l0 | dst1.l.l1) != 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (dst.__v2di, __builtin_e2k_qppackdl (0, 0)) == 0 &&
           __builtin_e2k_qpcmpeqbap (dst1.__v2di, __builtin_e2k_qppackdl (0, 0)) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* *****************************************************************************
 *                            Округление
 * *****************************************************************************/

#if __iset__ <= 2

/* эмуляция e2s инструкции fdtoifd */
__E2K_INLINE long long __DEFAULT_FUNCS_ATTRS
__emulate_e2k_fdtoifd (const int rc, long long src)
{
    __extension__ union { double __f; long long __i; } __xx = { __i: src }, __absx;
    __di __tmp;
    int pfpfr;

    __absx.__i = __xx.__i & ~0x8000000000000000LL;
    if (!(__absx.__f <= 4.503599627370496e15 /* 2 ^ 52 */))
        return src;
    else {
        if (rc & 8) { /* исключение inexact не вырабатывается */
            __GETPFPFR (pfpfr);
        }
        if ((rc & 4) ||      /* режим округления из регистра pfpfr */
            (rc & 3) == 0) { /* округление к ближайшему (rint) */
#pragma asm_inline
            __asm ("fdtoid %1,%0\n\tidtofd %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x8000000000000000LL);
        }
        else if ((rc & 3) == 1) { /* округление к -inf (floor) */
#pragma asm_inline
            __asm ("fdtoid %1,%0\n\tidtofd %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x8000000000000000LL);
            if (__absx.__f > __xx.__f)
                __absx.__f -= 1.0;
        }
        else if ((rc & 3) == 2) { /* округление к +inf (ceil) */
#pragma asm_inline
            __asm ("fdtoid %1,%0\n\tidtofd %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x8000000000000000LL);
            if (__absx.__f < __xx.__f)
                __absx.__f += 1.0;
        }
        else if ((rc & 3) == 3) { /* округление к 0 (trunc) */
#pragma asm_inline
            __asm ("fdtoidtr %1,%0\n\tidtofd %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x8000000000000000LL);
        }
        if (rc & 8) { /* исключение inexact не вырабатывается */
            __SETPFPFR (pfpfr);
        }
        return __absx.__i;
    }
}

/* эмуляция e2s инструкции fstoifs */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__emulate_e2k_fstoifs (const int rc, int src)
{
    __extension__ union { float __f; int __i; } __xx = { __i: src }, __absx;
    int __tmp;
    int pfpfr;

    __absx.__i = __xx.__i & ~0x80000000;
    if (!(__absx.__f <= 8388608.0F /* 2 ^ 23 */))
        return src;
    else {
        if (rc & 8) { /* исключение inexact не вырабатывается */
            __GETPFPFR (pfpfr);
        }
        if ((rc & 4) ||      /* режим округления из регистра pfpfr */
            (rc & 3) == 0) { /* округление к ближайшему (rint) */
#pragma asm_inline
            __asm ("fstois %1,%0\n\tistofs %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x80000000);
        }
        else if ((rc & 3) == 1) { /* округление к -inf (floor) */
#pragma asm_inline
            __asm ("fstois %1,%0\n\tistofs %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x80000000);
            if (__absx.__f > __xx.__f)
                __absx.__f -= 1.0f;
        }
        else if ((rc & 3) == 2) { /* округление к +inf (ceil) */
#pragma asm_inline
            __asm ("fstois %1,%0\n\tistofs %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x80000000);
            if (__absx.__f < __xx.__f)
                __absx.__f += 1.0f;
        }
        else if ((rc & 3) == 3) { /* округление к 0 (trunc) */
#pragma asm_inline
            __asm ("fstoistr %1,%0\n\tistofs %0,%0" : "=r" (__tmp) : "r" (__absx.__f));
            __absx.__i = __tmp | (__xx.__i & 0x80000000);
        }
        if (rc & 8) { /* исключение inexact не вырабатывается */
            __SETPFPFR (pfpfr);
        }
        return __absx.__i;
    }
}

#endif /* __iset__ <= 2 */

/* Round the 2 DPFP values in the source operand using the
 * rounding mode specified in the immediate operand */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_roundpd (__v2df src, const int rc)
{
    type_union_128 s, dst;
    s.__v2df = src;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = __emulate_e2k_fdtoifd (rc, s.l.l0);
    dst.l.l1 = __emulate_e2k_fdtoifd (rc, s.l.l1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_fdtoifd (rc, s.l.l0);
    dst.l.l1 = __builtin_e2k_fdtoifd (rc, s.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfdtoifd (rc, s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2df;
}

/* Round the DPFP value in the lower part of the source operand using the
 * rounding mode specified in the immediate operand */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_roundsd (__v2df src1, __v2df src2, const int rc)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
#if __iset__ <= 2
    s1.l.l0 = __emulate_e2k_fdtoifd (rc, s2.l.l0);
#else /* __iset__ <= 2 */
    s1.l.l0 = __builtin_e2k_fdtoifd (rc, s2.l.l0);
#endif /* __iset__ <= 2 */
    return s1.__v2df;
}

/* Round the 4 SPFP values in the source operand using the
 * rounding mode specified in the immediate operand */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_roundps (__v4sf src, const int rc)
{
    type_union_128 s, dst;
    s.__v4sf = src;
#if __iset__ <= 2
    unsigned int tmp0 = __emulate_e2k_fstoifs (rc, s.i.i0);
    unsigned int tmp1 = __emulate_e2k_fstoifs (rc, s.i.i1);
    unsigned int tmp2 = __emulate_e2k_fstoifs (rc, s.i.i2);
    unsigned int tmp3 = __emulate_e2k_fstoifs (rc, s.i.i3);
    dst.i.i0 = tmp0;
    dst.i.i1 = tmp1;
    dst.i.i2 = tmp2;
    dst.i.i3 = tmp3;
#elif __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfstoifs (rc, s.l.l0);
    dst.l.l1 = __builtin_e2k_pfstoifs (rc, s.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpfstoifs (rc, s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* Round the SPFP value in the lower part of the source operand using the
 * rounding mode specified in the immediate operand */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_roundss (__v4sf src1, __v4sf src2, const int rc)
{
    type_union_128 s1, s2;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 2
    s1.i.i0 = __emulate_e2k_fstoifs (rc, s2.i.i0);
#else /* __iset__ <= 2 */
    s1.i.i0 = __builtin_e2k_fstoifs (rc, s2.i.i0);
#endif /* __iset__ <= 2 */
    return s1.__v4sf;
}

/* *****************************************************************************
 *                            Выбор (смешивание)
 * *****************************************************************************/

/* Shorts from the second source operand are conditionally merged (in dependency
 * from mask bits) with values from the first source operand */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pblendw128 (__v8hi src1, __v8hi src2, const int mask)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    __di neg_mask0 = __builtin_e2k_pcmpgth (0, (mask & 0xf) * 0x1000200040008000LL);
    __di neg_mask1 = __builtin_e2k_pcmpgth (0, (mask & 0xf0) * 0x0100020004000800LL);
    dst.l.l0 = __builtin_e2k_pmerge (s1.l.l0, s2.l.l0, neg_mask0);
    dst.l.l1 = __builtin_e2k_pmerge (s1.l.l1, s2.l.l1, neg_mask1);
#else /* __iset__ <= 4 */
    __v2di neg_mask = __builtin_e2k_qpmsk2sgnb (s1.__v2di, mask);
    neg_mask = __builtin_e2k_qppermb (neg_mask, neg_mask,
                                      __builtin_e2k_qppackdl (0x0707060605050404LL, 0x0303020201010000LL));
    dst.__v2di = __builtin_e2k_qpmerge (s1.__v2di, s2.__v2di, neg_mask);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* SPFP values from the second source operand are conditionally merged (in dependency
 * from mask bits) with values from the first source operand */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendps (__v4sf src1, __v4sf src2, const int mask)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
    __di neg_mask0 = __builtin_e2k_pcmpgtw (0, (mask & 3) * 0x4000000080000000LL);
    __di neg_mask1 = __builtin_e2k_pcmpgtw (0, (mask & 0xc) * 0x1000000020000000LL);
    dst.l.l0 = __builtin_e2k_pmerge (s1.l.l0, s2.l.l0, neg_mask0);
    dst.l.l1 = __builtin_e2k_pmerge (s1.l.l1, s2.l.l1, neg_mask1);
#else /* __iset__ <= 4 */
    __v2di neg_mask = __builtin_e2k_qpmsk2sgnb (s1.__v2di, mask);
    neg_mask = __builtin_e2k_qppermb (neg_mask, neg_mask,
                                      __builtin_e2k_qppackdl (0x0303030302020202LL, 0x0101010100000000LL));
    dst.__v2di = __builtin_e2k_qpmerge (s1.__v2di, s2.__v2di, neg_mask);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* DPFP values from the second source operand are conditionally merged (in dependency
 * from mask bits) with values from the first source operand */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendpd (__v2df src1, __v2df src2, const int mask)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
    if (mask & 1) s1.l.l0 = s2.l.l0;
    if (mask & 2) s1.l.l1 = s2.l.l1;
    return s1.__v2df;
}

/* Conditionally copy byte elements from the second source operand and the first
 * source operand depending on mask bits defined in the mask register operand. */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pblendvb128 (__v16qi src1, __v16qi src2, __v16qi mask)
{
    type_union_128 s1, s2, m, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
    m.__v16qi = mask;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pmerge (s1.l.l0, s2.l.l0, m.l.l0);
    dst.l.l1 = __builtin_e2k_pmerge (s1.l.l1, s2.l.l1, m.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmerge (s1.__v2di, s2.__v2di, m.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* Conditionally copy each SPFP value from the second source operand and the first
 * source operand depending on mask bits defined in the mask register operand. */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendvps (__v4sf src1, __v4sf src2, __v4sf mask)
{
    type_union_128 s1, s2, m, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    m.__v4sf = mask;
#if __iset__ <= 4
    __di neg_mask0 = __builtin_e2k_pcmpgtw (0, m.l.l0);
    __di neg_mask1 = __builtin_e2k_pcmpgtw (0, m.l.l1);
    dst.l.l0 = __builtin_e2k_pmerge (s1.l.l0, s2.l.l0, neg_mask0);
    dst.l.l1 = __builtin_e2k_pmerge (s1.l.l1, s2.l.l1, neg_mask1);
#else /* __iset__ <= 4 */
    __v2di neg_mask = __builtin_e2k_qpcmpgtw (__builtin_e2k_qppackdl (0, 0), m.__v2di);
    dst.__v2di = __builtin_e2k_qpmerge (s1.__v2di, s2.__v2di, neg_mask);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* Conditionally copy each DPFP value from the second source operand and the first
 * source operand depending on mask bits defined in the mask register operand. */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendvpd (__v2df src1, __v2df src2, __v2df mask)
{
    type_union_128 s1, s2, m;
    s1.__v2df = src1;
    s2.__v2df = src2;
    m.__v2df = mask;
    if ((long long) m.l.l0 < 0) s1.l.l0 = s2.l.l0;
    if ((long long) m.l.l1 < 0) s1.l.l1 = s2.l.l1;
    return s1.__v2df;
}

/* *****************************************************************************
 *                            Скалярное произведение
 * *****************************************************************************/

/* Conditionally multiplies the packed DPFP values in the first operand with the
 * packed DPFPs in the second operand depending on a mask extracted from the [5:4]
 * bits of the third operand. The two resulting DPFP values are summed into an
 * intermediate result. The intermediate result is conditionally broadcasted to
 * the destination using a broadcast mask specified by bits [1:0] of the mask. */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_dppd (__v2df src1, __v2df src2, const int mask)
{
    type_union_128 s1, s2, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    double res = (mask & 0x20) ? s1.d.d1 * s2.d.d1 : 0;
    if (mask & 0x10)
        res += s1.d.d0 * s2.d.d0;
    dst.d.d1 = (mask & 2) ? res : 0;
    dst.d.d0 = (mask & 1) ? res : 0;
    return dst.__v2df;
}

/* Conditionally multiplies the packed SPFP values in the first operand with the
 * packed SPFPs in the second operand depending on a mask extracted from the [5:4]
 * bits of the third operand. The four resulting SPFP values are summed into an
 * intermediate result. The intermediate result is conditionally broadcasted to
 * the destination using a broadcast mask specified by bits [3:0] of the mask. */
__E2K_INLINE __E2K_WARNING (__v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_dpps (__v4sf src1, __v4sf src2, const int mask))
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
    __di zero_mask0 = __builtin_e2k_pcmpgtw (0, (mask & 0x30) * 0x0400000008000000LL);
    __di zero_mask1 = __builtin_e2k_pcmpgtw (0, (mask & 0xc0) * 0x0100000002000000LL);
    __di dst_mask0 = __builtin_e2k_pcmpgtw (0, (mask & 0x3) * 0x4000000080000000LL);
    __di dst_mask1 = __builtin_e2k_pcmpgtw (0, (mask & 0xc) * 0x1000000020000000LL);
    __di res = __builtin_e2k_pfmuls (s1.l.l1, s2.l.l1 & zero_mask1);
    res = __builtin_e2k_pfadds (res, __builtin_e2k_pfmuls (s1.l.l0, s2.l.l0 & zero_mask0));
    res = __builtin_e2k_pfadds (res, __builtin_e2k_scrd (res, 32));
    dst.l.l1 = res & dst_mask1;
    dst.l.l0 = res & dst_mask0;
#else /* __iset__ <= 4 */
    __v2di dst_mask = __builtin_e2k_qpmsk2sgnb (s1.__v2di, mask);
    __v2di zero_mask = __builtin_e2k_qppermb (dst_mask, dst_mask,
                                              __builtin_e2k_qppackdl (0x0707070706060606LL, 0x0505050504040404LL));
    zero_mask = __builtin_e2k_qpcmpgtw (__builtin_e2k_qppackdl (0, 0), zero_mask);
    dst_mask = __builtin_e2k_qppermb (dst_mask, dst_mask,
                                      __builtin_e2k_qppackdl (0x0303030302020202LL, 0x0101010100000000LL));
    dst_mask = __builtin_e2k_qpcmpgtw (__builtin_e2k_qppackdl (0, 0), dst_mask);
    __v2di tmp = __builtin_e2k_qpfmuls (s1.__v2di, __builtin_e2k_qpand (s2.__v2di, zero_mask));
    tmp = __builtin_e2k_qpfhadds (tmp, tmp);
    tmp = __builtin_e2k_qpfhadds (tmp, tmp);
    dst.__v2di = __builtin_e2k_qpand (tmp, dst_mask);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* *****************************************************************************
 *                            Сравнение
 * *****************************************************************************/

/* сравнение на "равно" 2-х лонгов (64S/64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpeqq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = (s1.l.l0 == s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 == s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pcmpeqd (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqd (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* *****************************************************************************
 *                            Минимум/Максимум
 * *****************************************************************************/

/* минимум 16-ти знаковых байт (8S) */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pminsb128 (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgtb (s2.l.l0, s1.l.l0);
    __di tmp1 = __builtin_e2k_pcmpgtb (s2.l.l1, s1.l.l1);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pminsb (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pminsb (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpminsb (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* максимум 16-ти знаковых байт (8S) */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmaxsb128 (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgtb (s1.l.l0, s2.l.l0);
    __di tmp1 = __builtin_e2k_pcmpgtb (s1.l.l1, s2.l.l1);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pmaxsb (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pmaxsb (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaxsb (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* минимум 8-ми беззнаковых шортов (16U) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pminuw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgth (s2.l.l0 ^ 0x8000800080008000LL, s1.l.l0 ^ 0x8000800080008000LL);
    __di tmp1 = __builtin_e2k_pcmpgth (s2.l.l1 ^ 0x8000800080008000LL, s1.l.l1 ^ 0x8000800080008000LL);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pminuh (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pminuh (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpminuh (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* максимум 8-ми беззнаковых шортов (16U) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmaxuw128 (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgth (s1.l.l0 ^ 0x8000800080008000LL, s2.l.l0 ^ 0x8000800080008000LL);
    __di tmp1 = __builtin_e2k_pcmpgth (s1.l.l1 ^ 0x8000800080008000LL, s2.l.l1 ^ 0x8000800080008000LL);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pmaxuh (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pmaxuh (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaxuh (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* минимум 4-х знаковых интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pminsd128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgtw (s2.l.l0, s1.l.l0);
    __di tmp1 = __builtin_e2k_pcmpgtw (s2.l.l1, s1.l.l1);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pminsw (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pminsw (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpminsw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* максимум 4-х знаковых интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmaxsd128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgtw (s1.l.l0, s2.l.l0);
    __di tmp1 = __builtin_e2k_pcmpgtw (s1.l.l1, s2.l.l1);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pmaxsw (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pmaxsw (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaxsw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* минимум 4-х беззнаковых интов (32U) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pminud128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgtw (s2.l.l0 ^ 0x8000000080000000LL, s1.l.l0 ^ 0x8000000080000000LL);
    __di tmp1 = __builtin_e2k_pcmpgtw (s2.l.l1 ^ 0x8000000080000000LL, s1.l.l1 ^ 0x8000000080000000LL);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pminuw (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pminuw (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpminuw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* максимум 4-х беззнаковых интов (32U) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmaxud128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgtw (s1.l.l0 ^ 0x8000000080000000LL, s2.l.l0 ^ 0x8000000080000000LL);
    __di tmp1 = __builtin_e2k_pcmpgtw (s1.l.l1 ^ 0x8000000080000000LL, s2.l.l1 ^ 0x8000000080000000LL);
    dst.l.l0 = __builtin_e2k_pmerge (s2.l.l0, s1.l.l0, tmp0);
    dst.l.l1 = __builtin_e2k_pmerge (s2.l.l1, s1.l.l1, tmp1);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pmaxuw (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pmaxuw (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaxuw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* *****************************************************************************
 *                            Умножение
 * *****************************************************************************/

/* умножение 4-х знаковых интов (32s) и выдача младших 32 разрядов произведения. */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmulld128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.i.i0 = s1.i.i0 * s2.i.i0;
    dst.i.i1 = s1.i.i1 * s2.i.i1;
    dst.i.i2 = s1.i.i2 * s2.i.i2;
    dst.i.i3 = s1.i.i3 * s2.i.i3;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmullw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* умножение 2-х знаковых интов (32S), расположенныхв младших половинах 64-х
 * разрядных значений с получением 2-х 64-х разрядных результатов. */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmuldq128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.l.l0 = __builtin_e2k_smulx (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_smulx (s1.l.l1, s2.l.l1);
    return dst.__v2di;
}

/* *****************************************************************************
 *                            Вставка
 * *****************************************************************************/

/* Insert SPFP into packed SP array element selected by index N.
 * The bits [7-6] of N define src2 source index, the bits [5-4] define src1 dest index,
 * and bits [3-0] define zeroing mask for destination. */
#define __builtin_ia32_insertps128(src1, src2, indx) ({                            \
    type_union_128 __s2, __dst;                                                    \
    __s2.__v4sf = src2;                                                            \
    __dst.__v4sf = src1;                                                           \
    __di __tmp = __builtin_e2k_psrlql (__s2.l.l1, __s2.l.l0, ((indx) >> 4) & 0xc); \
    if ((((indx) >> 4) & 3) == 0) __dst.i.i0 = __tmp;                              \
    else if ((((indx) >> 4) & 3) == 1) __dst.i.i1 = __tmp;                         \
    else if ((((indx) >> 4) & 3) == 2) __dst.i.i2 = __tmp;                         \
    else __dst.i.i3 = __tmp;                                                       \
    if ((indx) & 1) __dst.i.i0 = 0;                                                \
    if ((indx) & 2) __dst.i.i1 = 0;                                                \
    if ((indx) & 4) __dst.i.i2 = 0;                                                \
    if ((indx) & 8) __dst.i.i3 = 0;                                                \
    __dst.__v4sf;                                                                  \
})

/* *****************************************************************************
 *                             Минимум и его позиция
 * *****************************************************************************/

#define MININDEX_16S(min, minind, src, srcind) {           \
    __di mask = __builtin_e2k_pcmpgth (min, src);          \
    min = __builtin_e2k_pmerge (min, src, mask);           \
    minind = __builtin_e2k_pmerge (minind, srcind, mask);  \
}

/* поиск минимального из 8-ми беззнаковых шортов (16U) и его позиции */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_phminposuw128 (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 2
    __di min = s.l.l0 ^ 0x8000800080000000LL,
         min1 = s.l.l1 ^ 0x8000800080000000LL;
    __di minind = 0x0003000200010000LL,
         minind1 = 0x0007000600050004LL;
    MININDEX_16S (min, minind, min1, minind1);
    min1 = __builtin_e2k_scrd (min, 32);
    minind1 = __builtin_e2k_scrd (minind, 32);
    MININDEX_16S (min, minind, min1, minind1);
    min1 = __builtin_e2k_scrd (min, 16);
    minind1 = __builtin_e2k_scrd (minind, 16);
    MININDEX_16S (min, minind, min1, minind1);
    dst.l.l0 = ((min & 0xffff) ^ 0x8000) | ((minind & 7) << 16);
#else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_phminposuh (s.l.l0, s.l.l1);
#endif /* __iset__ <= 2 */
    dst.l.l1 = 0;
    return dst.__v8hi;
}

/* *****************************************************************************
 *                            Распаковки
 * *****************************************************************************/

/* Распаковка 8-ми младших байт (8S) в шорты (16S) заполнением знаком. */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxbw128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 3
    __di tmp = __builtin_e2k_pcmpgtb (0, s.l.l0);
    dst.l.l1 = __builtin_e2k_punpckhbh (tmp, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklbh (tmp, s.l.l0);
#elif __iset__ <= 4
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4707460645054404LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4303420241014000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                        __builtin_e2k_qppackdl (0x8707860685058404LL, 0x8303820281018000LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* Распаковка 4-х младших байт (8S) в инты (32S) заполнением знаком. */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxbd128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 3
    __di tmp = __builtin_e2k_pcmpgtb (0, s.l.l0);
    dst.l.l1 = __builtin_e2k_pshufb (tmp, s.l.l0, 0x0b0b0b030a0a0a02LL);
    dst.l.l0 = __builtin_e2k_pshufb (tmp, s.l.l0, 0x0909090108080800LL);
#elif __iset__ <= 4
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343430342424202LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4141410140404000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                        __builtin_e2k_qppackdl (0x8383830382828202LL, 0x8181810180808000LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* Распаковка 4-х младших шортов (16S) в инты (32S) заполнением знаком. */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxwd128 (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 3
    __di tmp = __builtin_e2k_pcmpgth (0, s.l.l0);
    dst.l.l1 = __builtin_e2k_punpckhhw (tmp, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklhw (tmp, s.l.l0);
#elif __iset__ <= 4
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4747070645450504LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343030241410100LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                        __builtin_e2k_qppackdl (0x8787070685850504LL, 0x8383030281810100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* Распаковка 2-х младших байт (8S) в лонги (64S) заполнением знаком. */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxbq128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 3
    dst.l.l1 = ((long long) (s.l.l0 << 48)) >> 56;
    dst.l.l0 = ((long long) (s.l.l0 << 56)) >> 56;
#elif __iset__ <= 4
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4141414141414101LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4040404040404000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                        __builtin_e2k_qppackdl (0x8181818181818101LL, 0x8080808080808000LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* Распаковка 2-х младших шортов (16S) в лонги (64S) заполнением знаком. */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxwq128 (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 3
    dst.l.l1 = ((long long) (s.l.l0 << 32)) >> 48;
    dst.l.l0 = ((long long) (s.l.l0 << 48)) >> 48;
#elif __iset__ <= 4
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343434343430302LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4141414141410100LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                        __builtin_e2k_qppackdl (0x8383838383830302LL, 0x8181818181810100LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* Распаковка 2-х младших интов (32S) в лонги (64S) заполнением знаком. */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxdq128 (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l1 = ((long long) s.l.l0) >> 32;
 #if __iset__ <= 3
    dst.l.l0 = ((long long) (s.l.l0 << 32)) >> 32;
 #else /* __iset__ <= 3 */
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343434303020100LL);
 #endif /* __iset__ <= 3 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                        __builtin_e2k_qppackdl (0x8787878707060504LL, 0x8383838303020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* Распаковка 8-ми младших байт (8U) в беззнаковые шорты (16U) заполнением нулями. */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxbw128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhbh (0, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklbh (0, s.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                       __builtin_e2k_qppackdl (0x1007100610051004LL, 0x1003100210011000LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* Распаковка 4-х младших байт (8U) в беззнаковые инты (32U) заполнением нулями. */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxbd128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x8080800380808002LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x8080800180808000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                       __builtin_e2k_qppackdl (0x1010100310101002LL, 0x1010100110101000LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* Распаковка 4-х младших шортов (16U) в беззнаковые инты (32U) заполнением нулями. */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxwd128 (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l1 = __builtin_e2k_punpckhhw (0, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklhw (0, s.l.l0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                       __builtin_e2k_qppackdl (0x1010070610100504LL, 0x1010030210100100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* Распаковка 2-х младших байт (8U) в беззнаковые лонги (64U) заполнением нулями. */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxbq128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l1 = (s.l.l0 >> 8) & 0xff;
    dst.l.l0 = s.l.l0 & 0xff;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                       __builtin_e2k_qppackdl (0x1010101010101001LL, 0x1010101010101000LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* Распаковка 2-х младших шортов (16U) в беззнаковые лонги (64U) заполнением нулями. */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxwq128 (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l1 = (s.l.l0 >> 16) & 0xffff;
    dst.l.l0 = s.l.l0 & 0xffff;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                       __builtin_e2k_qppackdl (0x1010101010100302LL, 0x1010101010100100LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* Распаковка 2-х младших интов (32U) в беззнаковые лонги (64U) заполнением нулями. */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxdq128 (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l1 = s.l.l0 >> 32;
    dst.l.l0 = s.l.l0 & 0xffffffff;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                       __builtin_e2k_qppackdl (0x1010101007060504LL, 0x1010101003020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* *****************************************************************************
 *                               Упаковка интов
 * *****************************************************************************/

/* упаковка 8-ми знаковых интов (32S) в беззнаковые шорты (16U) с насыщением */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_packusdw128 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_pcmpgtw (s1.l.l0, 0) & s1.l.l0;
    __di tmp1 = __builtin_e2k_pcmpgtw (s1.l.l1, 0) & s1.l.l1;
    __di tmp2 = __builtin_e2k_pcmpgtw (s2.l.l0, 0) & s2.l.l0;
    __di tmp3 = __builtin_e2k_pcmpgtw (s2.l.l1, 0) & s2.l.l1;
    tmp0 = __builtin_e2k_psubw (tmp0, 0x0000800000008000LL);
    tmp1 = __builtin_e2k_psubw (tmp1, 0x0000800000008000LL);
    tmp2 = __builtin_e2k_psubw (tmp2, 0x0000800000008000LL);
    tmp3 = __builtin_e2k_psubw (tmp3, 0x0000800000008000LL);
    dst.l.l1 = __builtin_e2k_packsswh (tmp3, tmp2) ^ 0x8000800080008000LL;
    dst.l.l0 = __builtin_e2k_packsswh (tmp1, tmp0) ^ 0x8000800080008000LL;
 #else /* __iset__ <= 2 */
    dst.l.l1 = __builtin_e2k_packuswh (s2.l.l1, s2.l.l0);
    dst.l.l0 = __builtin_e2k_packuswh (s1.l.l1, s1.l.l0);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpackuswh (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* *****************************************************************************
 *         Множественное сложение абсолютных разностей беззнаковых байт
 * *****************************************************************************/

/* 8 сумм абсолютных разностей 4-х беззнаковых байт (8U) со сдвигом операндов
 * первого аргумента и 4-х беззнаковых байт (8U) второго аргумента с формированием 8-ми
 * беззнаковых шортов (16U) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_mpsadbw128 (__v16qi src1, __v16qi src2, const int indx)
{
    type_union_128 s1, dst;
    s1.__v16qi = src1;
    __di tmp2 = ((unsigned int *) & src2) [indx & 3];
#if __iset__ <= 4
    __di s10 = s1.l.l0;
    __di s11 = s1.l.l1;

    if (indx & 4) {
        s10 = __builtin_e2k_psrlql (s11, s10, 4); /* сдвиг вправо на 4 байта */
        s11 = s11 >> 32; /* сдвиг вправо на 4 байта */
    }
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_psadbw ((s10 >>  0) & 0xffffffffLL, tmp2);
    tmp0 |= __builtin_e2k_psadbw ((s10 >>  8) & 0xffffffffLL, tmp2) << 16;
    tmp0 |= __builtin_e2k_psadbw ((s10 >> 16) & 0xffffffffLL, tmp2) << 32;
    dst.l.l0 = tmp0 | __builtin_e2k_psadbw ((s10 >> 24) & 0xffffffffLL, tmp2) << 48;
    s10 = __builtin_e2k_psrlql (s11, s10, 4); /* сдвиг вправо на 4 байта */
    __di tmp1 = __builtin_e2k_psadbw ((s10 >>  0) & 0xffffffffLL, tmp2);
    tmp1 |= __builtin_e2k_psadbw ((s10 >>  8) & 0xffffffffLL, tmp2) << 16;
    tmp1 |= __builtin_e2k_psadbw ((s10 >> 16) & 0xffffffffLL, tmp2) << 32;
    dst.l.l1 = tmp1 | __builtin_e2k_psadbw ((s10 >> 24) & 0xffffffffLL, tmp2) << 48;
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_mpsadbh (s10, tmp2);
    s10 = __builtin_e2k_psrlql (s11, s10, 4); /* сдвиг вправо на 4 байта */
    dst.l.l1 = __builtin_e2k_mpsadbh (s10, tmp2);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    if (indx & 4) { /* сдвиг вправо на 4 байта и на 8 */
        s1.__v2di = __builtin_e2k_qppermb (s1.__v2di, s1.__v2di,
                                       __builtin_e2k_qppackdl (0x0f0e0d0c0b0a0908LL, 0x0b0a090807060504LL));
    }
    else { /* сдвиг вправо на 0 байт и на 4 */
        s1.__v2di = __builtin_e2k_qppermb (s1.__v2di, s1.__v2di,
                                       __builtin_e2k_qppackdl (0x0b0a090807060504LL, 0x0706050403020100LL));
    }
    dst.__v2di = __builtin_e2k_qpmpsadbh (s1.__v2di, tmp2);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* *****************************************************************************
 *                                   Чтение
 * *****************************************************************************/

/* Load double quadword using non-temporal aligned hint.  */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntdqa (const __v2di *p)
{
    type_union_128 dst;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_ld_64s_nta (p);
    dst.l.l1 = __builtin_e2k_ld_64s_nta ((double *) p + 1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_ld_128_nta (p);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

#undef MININDEX_16S

#endif /* __SSE4_1__ */

#define __CLZH(count, x) /* count leading zeros */ \
    (count) = __builtin_e2k_lzcnts ((unsigned short) (x)) - 16

#define __CLZ(count, x) /* count leading zeros */  \
    (count) = __builtin_e2k_lzcnts ((x))

#define __CLZD(count, x) /* count leading zeros */ \
    (count) = __builtin_e2k_lzcntd ((x))

#define __BITREV_8U(res, x) /* разворот 8 бит */   \
    res = __builtin_e2k_bitrevs ((x) << 24)

#define __BITREV_16U(res, x) /* разворот 16 бит */ \
    res = __builtin_e2k_bitrevs ((x) << 16)

#define __BITREV_32U(res, x) /* разворот 32 бит */ \
    res = __builtin_e2k_bitrevs ((x))

#define __BITREV_64U(res, x) /* разворот 64 бит */ \
    res = __builtin_e2k_bitrevd ((x))


#ifdef __SSE4_2__

/*******************************************************************************/
/***************************** SSE4.2 builtins *********************************/
/*******************************************************************************/

#if __iset__ <= 4

/* Определение длины строки.  */
#define __CALC_LEN(len, src, is_short) {               \
    __di mask0, mask1;                                 \
    if (is_short) {                                    \
        mask0 = __builtin_e2k_pcmpeqh (src.l.l0, 0);   \
        mask1 = __builtin_e2k_pcmpeqh (src.l.l1, 0);   \
    }                                                  \
    else {                                             \
        mask0 = __builtin_e2k_pcmpeqb (src.l.l0, 0);   \
        mask1 = __builtin_e2k_pcmpeqb (src.l.l1, 0);   \
    }                                                  \
    len = __builtin_e2k_pmovmskb (mask1, mask0);       \
    __CLZ (len, len & (-len));                         \
    len = 31 - len;                                    \
    if (len < 0) len = 16;                             \
    if (is_short) {                                    \
        len >>= 1;                                     \
    }                                                  \
}

/* Генерация маски валидности  */
#define __GEN_MASK(mask, len, is_short) {                 \
    int __len = (len);                                    \
    if (is_short) { /* длина в байтах */                  \
        __len <<= 1;                                      \
    }                                                     \
    mask.l.l0 = mask.l.l1 = 0;                            \
    if (__len > 8) {                                      \
        mask.l.l0 = -1LL;                                 \
        mask.l.l1 = ((__di) -1LL) >> ((16 - __len) << 3); \
    }                                                     \
    else if (__len > 0) {                                 \
        mask.l.l0 = ((__di) -1LL) >> ((8 - __len) << 3);  \
    }                                                     \
}

#else /* __iset__ <= 4 */

/* Определение длины строки.  */
#define __CALC_LEN(len, src, is_short) {                                           \
    __v2di mask;                                                                   \
    if (is_short) {                                                                \
        mask = __builtin_e2k_qpcmpeqh (src.__v2di, __builtin_e2k_qppackdl (0, 0)); \
    }                                                                              \
    else {                                                                         \
        mask = __builtin_e2k_qpcmpeqb (src.__v2di, __builtin_e2k_qppackdl (0, 0)); \
    }                                                                              \
    len = __builtin_e2k_qpsgn2mskb (mask);                                         \
    __CLZ (len, len & (-len));                                                     \
    len = 31 - len;                                                                \
    if (len < 0) len = 16;                                                         \
    if (is_short) {                                                                \
        len >>= 1;                                                                 \
    }                                                                              \
}

/* Генерация маски валидности  */
#define __GEN_MASK(mask, len, is_short) {                                                    \
    int __len = (len);                                                                       \
    if (is_short) { /* длина в байтах */                                                     \
        __len <<= 1;                                                                         \
    }                                                                                        \
    mask.__v2di = __builtin_e2k_qpmsk2sgnb (__builtin_e2k_qppackdl (0, 0), 0xffff << __len); \
    mask.__v2di = __builtin_e2k_qpcmpeqb (__builtin_e2k_qppackdl (0, 0), mask.__v2di);       \
}

#endif /* __iset__ <= 4 */

/*****************************************************************************/

#if __iset__ <= 4

/* Сравнение на "equal any" (поиск символов)  */
#define __CMP_EQUAL_ANY(res, src1, src2, len1, mask2, is_short) {                    \
    __di tmp0;                                                                       \
    int i;                                                                           \
                                                                                     \
    if (is_short) {                                                                  \
        __di pshufb_mask = 0x0100010001000100LL;                                     \
_Pragma ("loop count (2)")                                                           \
        for (i = 0; i < len1; i++) {                                                 \
            tmp0 = __builtin_e2k_pshufb (src1.l.l1, src1.l.l0, pshufb_mask); /* размножаем текущий шорт */ \
            res.l.l0 |= __builtin_e2k_pcmpeqh (tmp0, src2.l.l0);                     \
            res.l.l1 |= __builtin_e2k_pcmpeqh (tmp0, src2.l.l1);                     \
            pshufb_mask += 0x0202020202020202LL;                                     \
        }                                                                            \
    }                                                                                \
    else {                                                                           \
        __di pshufb_mask = 0;                                                        \
_Pragma ("loop count (4)")                                                           \
        for (i = 0; i < len1; i++) {                                                 \
            tmp0 = __builtin_e2k_pshufb (src1.l.l1, src1.l.l0, pshufb_mask); /* размножаем текущий байт */ \
            res.l.l0 |= __builtin_e2k_pcmpeqb (tmp0, src2.l.l0);                     \
            res.l.l1 |= __builtin_e2k_pcmpeqb (tmp0, src2.l.l1);                     \
            pshufb_mask += 0x0101010101010101LL;                                     \
        }                                                                            \
    }                                                                                \
    res.l.l0 &= mask2.l.l0; /* очищаем результат от лишних символов */               \
    res.l.l1 &= mask2.l.l1;                                                          \
}

/* Сравнение на "ranges" (поиск в диапазоне)  */
#define __CMP_RANGES(res, src1, src2, len1, mask2, is_signed, is_short) {            \
    __di tmp0, tmp1;                                                                 \
    int i;                                                                           \
                                                                                     \
    if (!(is_signed)) { /* беззнаковые числа */                                      \
        tmp0 = (is_short) ? 0x8000800080008000LL : 0x8080808080808080LL;             \
        src1.l.l0 ^= tmp0;                                                           \
        src1.l.l1 ^= tmp0;                                                           \
        src2.l.l0 ^= tmp0;                                                           \
        src2.l.l1 ^= tmp0;                                                           \
    }                                                                                \
    if (is_short) {                                                                  \
        __di pshufb_mask = 0x0100010001000100LL;                                     \
_Pragma ("loop count (2)")                                                           \
        for (i = 0; i < len1 / 2; i++) {                                             \
            tmp0 = __builtin_e2k_pshufb (src1.l.l1, src1.l.l0, pshufb_mask); /* размножаем текущий четный шорт */ \
            tmp1 = __builtin_e2k_pshufb (src1.l.l1, src1.l.l0, pshufb_mask + 0x0202020202020202LL); /* размножаем текущий нечетный шорт */ \
            res.l.l0 |= ~__builtin_e2k_pcmpgth (tmp0, src2.l.l0) & ~__builtin_e2k_pcmpgth (src2.l.l0, tmp1); \
            res.l.l1 |= ~__builtin_e2k_pcmpgth (tmp0, src2.l.l1) & ~__builtin_e2k_pcmpgth (src2.l.l1, tmp1); \
            pshufb_mask += 0x0404040404040404LL;                                     \
        }                                                                            \
    }                                                                                \
    else {                                                                           \
        __di pshufb_mask = 0;                                                        \
_Pragma ("loop count (3)")                                                           \
        for (i = 0; i < len1 / 2; i++) {                                             \
            tmp0 = __builtin_e2k_pshufb (src1.l.l1, src1.l.l0, pshufb_mask); /* размножаем текущий четный байт */ \
            tmp1 = __builtin_e2k_pshufb (src1.l.l1, src1.l.l0, pshufb_mask + 0x0101010101010101LL); /* размножаем текущий нечетный байт */ \
            res.l.l0 |= ~__builtin_e2k_pcmpgtb (tmp0, src2.l.l0) & ~__builtin_e2k_pcmpgtb (src2.l.l0, tmp1); \
            res.l.l1 |= ~__builtin_e2k_pcmpgtb (tmp0, src2.l.l1) & ~__builtin_e2k_pcmpgtb (src2.l.l1, tmp1); \
            pshufb_mask += 0x0202020202020202LL;                                     \
        }                                                                            \
    }                                                                                \
    res.l.l0 &= mask2.l.l0; /* очищаем результат от лишних символов */               \
    res.l.l1 &= mask2.l.l1;                                                          \
}

/*****************************************************************************/

#else /* __iset__ <= 4 */

/* Сравнение на "equal any" (поиск символов)  */
#define __CMP_EQUAL_ANY(res, src1, src2, len1, mask2, is_short) {                    \
    __v2di tmp0, tmp1 = res.__v2di;                                                  \
    int i;                                                                           \
                                                                                     \
    if (is_short) {                                                                  \
        __v2di pshufb_mask = __builtin_e2k_qppackdl (0x0100010001000100LL, 0x0100010001000100LL);  \
_Pragma ("loop count (2)")                                                           \
        for (i = 0; i < len1; i++) {                                                 \
            tmp0 = __builtin_e2k_qppermb (src1.__v2di, src1.__v2di, pshufb_mask); /* размножаем текущий шорт */ \
            tmp0 = __builtin_e2k_qpcmpeqh (tmp0, src2.__v2di);                       \
            tmp1 = __builtin_e2k_qpor (tmp1, tmp0);                                  \
            pshufb_mask = __builtin_e2k_qpaddb (pshufb_mask,                         \
                              __builtin_e2k_qppackdl (0x0202020202020202LL, 0x0202020202020202LL));\
        }                                                                            \
    }                                                                                \
    else {                                                                           \
        __v2di pshufb_mask = __builtin_e2k_qppackdl (0, 0);                          \
_Pragma ("loop count (4)")                                                           \
        for (i = 0; i < len1; i++) {                                                 \
            tmp0 = __builtin_e2k_qppermb (src1.__v2di, src1.__v2di, pshufb_mask); /* размножаем текущий байт */ \
            tmp0 = __builtin_e2k_qpcmpeqb (tmp0, src2.__v2di);                       \
            tmp1 = __builtin_e2k_qpor (tmp1, tmp0);                                  \
            pshufb_mask = __builtin_e2k_qpaddb (pshufb_mask,                         \
                              __builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL));\
        }                                                                            \
    }                                                                                \
    /* очищаем результат от лишних символов */                                       \
    res.__v2di = __builtin_e2k_qpand (tmp1, mask2.__v2di);                           \
}

/* Сравнение на "ranges" (поиск в диапазоне)  */
#define __CMP_RANGES(res, src1, src2, len1, mask2, is_signed, is_short) {            \
    __v2di tmp0, tmp1, tmp2, tmp3 = res.__v2di;                                      \
    int i;                                                                           \
                                                                                     \
    if (!(is_signed)) { /* беззнаковые числа */                                      \
        __di tmp = (is_short) ? 0x8000800080008000LL : 0x8080808080808080LL;         \
        tmp0 = __builtin_e2k_qppackdl (tmp, tmp);                                    \
        src1.__v2di = __builtin_e2k_qpxor (src1.__v2di, tmp0);                       \
        src2.__v2di = __builtin_e2k_qpxor (src2.__v2di, tmp0);                       \
    }                                                                                \
    if (is_short) {                                                                  \
        __v2di pshufb_mask = __builtin_e2k_qppackdl (0x0100010001000100LL, 0x0100010001000100LL);  \
_Pragma ("loop count (2)")                                                           \
        for (i = 0; i < len1 / 2; i++) {                                             \
            tmp0 = __builtin_e2k_qppermb (src1.__v2di, src1.__v2di, pshufb_mask); /* размножаем текущий четный шорт */ \
            pshufb_mask = __builtin_e2k_qpaddb (pshufb_mask,                         \
                              __builtin_e2k_qppackdl (0x0202020202020202LL, 0x0202020202020202LL));\
            tmp1 = __builtin_e2k_qppermb (src1.__v2di, src1.__v2di, pshufb_mask); /* размножаем текущий нечетный шорт */ \
            pshufb_mask = __builtin_e2k_qpaddb (pshufb_mask,                         \
                              __builtin_e2k_qppackdl (0x0202020202020202LL, 0x0202020202020202LL));\
            tmp3 = __builtin_e2k_qplog (0xab, __builtin_e2k_qpcmpgth (tmp0, src2.__v2di), /* ~(s1 | s2) | s3 */ \
                                              __builtin_e2k_qpcmpgth (src2.__v2di, tmp1), tmp3); \
        }                                                                            \
    }                                                                                \
    else {                                                                           \
        __v2di pshufb_mask = __builtin_e2k_qppackdl (0, 0);                          \
_Pragma ("loop count (3)")                                                           \
        for (i = 0; i < len1 / 2; i++) {                                             \
            tmp0 = __builtin_e2k_qppermb (src1.__v2di, src1.__v2di, pshufb_mask); /* размножаем текущий четный байт */ \
            pshufb_mask = __builtin_e2k_qpaddb (pshufb_mask,                         \
                              __builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL));\
            tmp1 = __builtin_e2k_qppermb (src1.__v2di, src1.__v2di, pshufb_mask); /* размножаем текущий нечетный байт */ \
            pshufb_mask = __builtin_e2k_qpaddb (pshufb_mask,                         \
                              __builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL));\
            tmp3 = __builtin_e2k_qplog (0xab, __builtin_e2k_qpcmpgtb (tmp0, src2.__v2di), /* ~(s1 | s2) | s3 */ \
                                              __builtin_e2k_qpcmpgtb (src2.__v2di, tmp1), tmp3); \
        }                                                                            \
    }                                                                                \
    /* очищаем результат от лишних символов */                                       \
    res.__v2di = __builtin_e2k_qpand (tmp3, mask2.__v2di);                           \
}

#endif /* __iset__ <= 4 */

/*****************************************************************************/

#if __iset__ <= 4

static const __di __bit2byte_tab[] = {
    0x0000000000000000LL, 0x00000000000000ffLL, 0x000000000000ff00LL, 0x000000000000ffffLL,
    0x0000000000ff0000LL, 0x0000000000ff00ffLL, 0x0000000000ffff00LL, 0x0000000000ffffffLL,
    0x00000000ff000000LL, 0x00000000ff0000ffLL, 0x00000000ff00ff00LL, 0x00000000ff00ffffLL,
    0x00000000ffff0000LL, 0x00000000ffff00ffLL, 0x00000000ffffff00LL, 0x00000000ffffffffLL,
    0x000000ff00000000LL, 0x000000ff000000ffLL, 0x000000ff0000ff00LL, 0x000000ff0000ffffLL,
    0x000000ff00ff0000LL, 0x000000ff00ff00ffLL, 0x000000ff00ffff00LL, 0x000000ff00ffffffLL,
    0x000000ffff000000LL, 0x000000ffff0000ffLL, 0x000000ffff00ff00LL, 0x000000ffff00ffffLL,
    0x000000ffffff0000LL, 0x000000ffffff00ffLL, 0x000000ffffffff00LL, 0x000000ffffffffffLL,
    0x0000ff0000000000LL, 0x0000ff00000000ffLL, 0x0000ff000000ff00LL, 0x0000ff000000ffffLL,
    0x0000ff0000ff0000LL, 0x0000ff0000ff00ffLL, 0x0000ff0000ffff00LL, 0x0000ff0000ffffffLL,
    0x0000ff00ff000000LL, 0x0000ff00ff0000ffLL, 0x0000ff00ff00ff00LL, 0x0000ff00ff00ffffLL,
    0x0000ff00ffff0000LL, 0x0000ff00ffff00ffLL, 0x0000ff00ffffff00LL, 0x0000ff00ffffffffLL,
    0x0000ffff00000000LL, 0x0000ffff000000ffLL, 0x0000ffff0000ff00LL, 0x0000ffff0000ffffLL,
    0x0000ffff00ff0000LL, 0x0000ffff00ff00ffLL, 0x0000ffff00ffff00LL, 0x0000ffff00ffffffLL,
    0x0000ffffff000000LL, 0x0000ffffff0000ffLL, 0x0000ffffff00ff00LL, 0x0000ffffff00ffffLL,
    0x0000ffffffff0000LL, 0x0000ffffffff00ffLL, 0x0000ffffffffff00LL, 0x0000ffffffffffffLL,
    0x00ff000000000000LL, 0x00ff0000000000ffLL, 0x00ff00000000ff00LL, 0x00ff00000000ffffLL,
    0x00ff000000ff0000LL, 0x00ff000000ff00ffLL, 0x00ff000000ffff00LL, 0x00ff000000ffffffLL,
    0x00ff0000ff000000LL, 0x00ff0000ff0000ffLL, 0x00ff0000ff00ff00LL, 0x00ff0000ff00ffffLL,
    0x00ff0000ffff0000LL, 0x00ff0000ffff00ffLL, 0x00ff0000ffffff00LL, 0x00ff0000ffffffffLL,
    0x00ff00ff00000000LL, 0x00ff00ff000000ffLL, 0x00ff00ff0000ff00LL, 0x00ff00ff0000ffffLL,
    0x00ff00ff00ff0000LL, 0x00ff00ff00ff00ffLL, 0x00ff00ff00ffff00LL, 0x00ff00ff00ffffffLL,
    0x00ff00ffff000000LL, 0x00ff00ffff0000ffLL, 0x00ff00ffff00ff00LL, 0x00ff00ffff00ffffLL,
    0x00ff00ffffff0000LL, 0x00ff00ffffff00ffLL, 0x00ff00ffffffff00LL, 0x00ff00ffffffffffLL,
    0x00ffff0000000000LL, 0x00ffff00000000ffLL, 0x00ffff000000ff00LL, 0x00ffff000000ffffLL,
    0x00ffff0000ff0000LL, 0x00ffff0000ff00ffLL, 0x00ffff0000ffff00LL, 0x00ffff0000ffffffLL,
    0x00ffff00ff000000LL, 0x00ffff00ff0000ffLL, 0x00ffff00ff00ff00LL, 0x00ffff00ff00ffffLL,
    0x00ffff00ffff0000LL, 0x00ffff00ffff00ffLL, 0x00ffff00ffffff00LL, 0x00ffff00ffffffffLL,
    0x00ffffff00000000LL, 0x00ffffff000000ffLL, 0x00ffffff0000ff00LL, 0x00ffffff0000ffffLL,
    0x00ffffff00ff0000LL, 0x00ffffff00ff00ffLL, 0x00ffffff00ffff00LL, 0x00ffffff00ffffffLL,
    0x00ffffffff000000LL, 0x00ffffffff0000ffLL, 0x00ffffffff00ff00LL, 0x00ffffffff00ffffLL,
    0x00ffffffffff0000LL, 0x00ffffffffff00ffLL, 0x00ffffffffffff00LL, 0x00ffffffffffffffLL,
    0xff00000000000000LL, 0xff000000000000ffLL, 0xff0000000000ff00LL, 0xff0000000000ffffLL,
    0xff00000000ff0000LL, 0xff00000000ff00ffLL, 0xff00000000ffff00LL, 0xff00000000ffffffLL,
    0xff000000ff000000LL, 0xff000000ff0000ffLL, 0xff000000ff00ff00LL, 0xff000000ff00ffffLL,
    0xff000000ffff0000LL, 0xff000000ffff00ffLL, 0xff000000ffffff00LL, 0xff000000ffffffffLL,
    0xff0000ff00000000LL, 0xff0000ff000000ffLL, 0xff0000ff0000ff00LL, 0xff0000ff0000ffffLL,
    0xff0000ff00ff0000LL, 0xff0000ff00ff00ffLL, 0xff0000ff00ffff00LL, 0xff0000ff00ffffffLL,
    0xff0000ffff000000LL, 0xff0000ffff0000ffLL, 0xff0000ffff00ff00LL, 0xff0000ffff00ffffLL,
    0xff0000ffffff0000LL, 0xff0000ffffff00ffLL, 0xff0000ffffffff00LL, 0xff0000ffffffffffLL,
    0xff00ff0000000000LL, 0xff00ff00000000ffLL, 0xff00ff000000ff00LL, 0xff00ff000000ffffLL,
    0xff00ff0000ff0000LL, 0xff00ff0000ff00ffLL, 0xff00ff0000ffff00LL, 0xff00ff0000ffffffLL,
    0xff00ff00ff000000LL, 0xff00ff00ff0000ffLL, 0xff00ff00ff00ff00LL, 0xff00ff00ff00ffffLL,
    0xff00ff00ffff0000LL, 0xff00ff00ffff00ffLL, 0xff00ff00ffffff00LL, 0xff00ff00ffffffffLL,
    0xff00ffff00000000LL, 0xff00ffff000000ffLL, 0xff00ffff0000ff00LL, 0xff00ffff0000ffffLL,
    0xff00ffff00ff0000LL, 0xff00ffff00ff00ffLL, 0xff00ffff00ffff00LL, 0xff00ffff00ffffffLL,
    0xff00ffffff000000LL, 0xff00ffffff0000ffLL, 0xff00ffffff00ff00LL, 0xff00ffffff00ffffLL,
    0xff00ffffffff0000LL, 0xff00ffffffff00ffLL, 0xff00ffffffffff00LL, 0xff00ffffffffffffLL,
    0xffff000000000000LL, 0xffff0000000000ffLL, 0xffff00000000ff00LL, 0xffff00000000ffffLL,
    0xffff000000ff0000LL, 0xffff000000ff00ffLL, 0xffff000000ffff00LL, 0xffff000000ffffffLL,
    0xffff0000ff000000LL, 0xffff0000ff0000ffLL, 0xffff0000ff00ff00LL, 0xffff0000ff00ffffLL,
    0xffff0000ffff0000LL, 0xffff0000ffff00ffLL, 0xffff0000ffffff00LL, 0xffff0000ffffffffLL,
    0xffff00ff00000000LL, 0xffff00ff000000ffLL, 0xffff00ff0000ff00LL, 0xffff00ff0000ffffLL,
    0xffff00ff00ff0000LL, 0xffff00ff00ff00ffLL, 0xffff00ff00ffff00LL, 0xffff00ff00ffffffLL,
    0xffff00ffff000000LL, 0xffff00ffff0000ffLL, 0xffff00ffff00ff00LL, 0xffff00ffff00ffffLL,
    0xffff00ffffff0000LL, 0xffff00ffffff00ffLL, 0xffff00ffffffff00LL, 0xffff00ffffffffffLL,
    0xffffff0000000000LL, 0xffffff00000000ffLL, 0xffffff000000ff00LL, 0xffffff000000ffffLL,
    0xffffff0000ff0000LL, 0xffffff0000ff00ffLL, 0xffffff0000ffff00LL, 0xffffff0000ffffffLL,
    0xffffff00ff000000LL, 0xffffff00ff0000ffLL, 0xffffff00ff00ff00LL, 0xffffff00ff00ffffLL,
    0xffffff00ffff0000LL, 0xffffff00ffff00ffLL, 0xffffff00ffffff00LL, 0xffffff00ffffffffLL,
    0xffffffff00000000LL, 0xffffffff000000ffLL, 0xffffffff0000ff00LL, 0xffffffff0000ffffLL,
    0xffffffff00ff0000LL, 0xffffffff00ff00ffLL, 0xffffffff00ffff00LL, 0xffffffff00ffffffLL,
    0xffffffffff000000LL, 0xffffffffff0000ffLL, 0xffffffffff00ff00LL, 0xffffffffff00ffffLL,
    0xffffffffffff0000LL, 0xffffffffffff00ffLL, 0xffffffffffffff00LL, 0xffffffffffffffffLL
};

/*****************************************************************************/

/* Сравнение на "equal each" (сравнение строк)  */
#define __CMP_EQUAL_EACH(res,src1,src2,len1,len2,mask1,mask2,is_short) {             \
    src1.l.l0 &= mask1.l.l0; /* очищаем src1 от лишних символов */                   \
    src1.l.l1 &= mask1.l.l1;                                                         \
    src2.l.l0 &= mask2.l.l0; /* очищаем src2 от лишних символов */                   \
    src2.l.l1 &= mask2.l.l1;                                                         \
    if (len1 > len2) {  /* вставляем "1" в зону пересечения длин */                  \
        src1.l.l0 |= mask1.l.l0 ^ mask2.l.l0;                                        \
        src1.l.l1 |= mask1.l.l1 ^ mask2.l.l1;                                        \
    }                                                                                \
    else if (len1 < len2) {   /* вставляем "1" в зону пересечения длин */            \
        src2.l.l0 |= mask1.l.l0 ^ mask2.l.l0;                                        \
        src2.l.l1 |= mask1.l.l1 ^ mask2.l.l1;                                        \
    }                                                                                \
    if (is_short) {                                                                  \
        res.l.l0 = __builtin_e2k_pcmpeqh (src1.l.l0, src2.l.l0);                     \
        res.l.l1 = __builtin_e2k_pcmpeqh (src1.l.l1, src2.l.l1);                     \
    }                                                                                \
    else {                                                                           \
        res.l.l0 = __builtin_e2k_pcmpeqb (src1.l.l0, src2.l.l0);                     \
        res.l.l1 = __builtin_e2k_pcmpeqb (src1.l.l1, src2.l.l1);                     \
    }                                                                                \
}

/* Сравнение на "equal ordered" (поиск подстроки)  */
#define __CMP_EQUAL_ORDERED(res, src1, src2, len1, len2, mask1, is_short) {          \
    int i;                                                                           \
    if (len1 == 0) { /* пустая строка выдает все "1" */                              \
        res.l.l0 = res.l.l1 = -1LL;                                                  \
    }                                                                                \
    else {                                                                           \
        src1.l.l0 &= mask1.l.l0; /* очищаем src1 от лишних символов */               \
        src1.l.l1 &= mask1.l.l1;                                                     \
                                                                                     \
        if (is_short) {                                                              \
_Pragma ("loop count (2)")                                                           \
            for (i = 0; i < (len2 - len1 + 1); i++) {                                \
                if ((__builtin_e2k_pcmpeqh (src1.l.l0, src2.l.l0 & mask1.l.l0) &     \
                     __builtin_e2k_pcmpeqh (src1.l.l1, src2.l.l1 & mask1.l.l1)) == -1LL) {\
                    res.l.l0 |= 0xffLL << (8 * i);                                   \
                }                                                                    \
                src2.l.l0 = __builtin_e2k_psrlql (src2.l.l1, src2.l.l0, 2);          \
                src2.l.l1 >>= 16;                                                    \
            }                                                                        \
            res.l.l1 = __builtin_e2k_punpckhbh (res.l.l0, res.l.l0);/* байты преобразуем в шорты */\
            res.l.l0 = __builtin_e2k_punpcklbh (res.l.l0, res.l.l0);                 \
        }                                                                            \
        else {                                                                       \
_Pragma ("loop count (3)")                                                           \
            for (i = 0; i < (len2 - len1 + 1); i++) {                                \
                if ((__builtin_e2k_pcmpeqb (src1.l.l0, src2.l.l0 & mask1.l.l0) &     \
                     __builtin_e2k_pcmpeqb (src1.l.l1, src2.l.l1 & mask1.l.l1)) == -1LL) {\
                    res.l.l0 |= (1 << i);                                            \
                }                                                                    \
                src2.l.l0 = __builtin_e2k_psrlql (src2.l.l1, src2.l.l0, 1);          \
                src2.l.l1 >>= 8;                                                     \
            }                                                                        \
            res.l.l1 = __bit2byte_tab[res.l.l0 >> 8]; /* биты преобразуем в байты */ \
            res.l.l0 = __bit2byte_tab[res.l.l0 & 0xff];                              \
        }                                                                            \
    }                                                                                \
}

/* Сравнение строк c заданными длинами и выдачей байтовой/шортовой маски */
#define __PCMP_STR(dst, src1, len1, src2, len2, is_short, mode) {                    \
    type_union_128 mask1, mask2;                                                     \
    int polarity  = (mode & 0x30) >> 4;                                              \
    int cmp_type  = (mode & 0xc) >> 2;                                               \
    int is_signed = mode & 0x2;                                                      \
                                                                                     \
    /* генерация масок валидности */                                                 \
    __GEN_MASK (mask1, len1, is_short);                                              \
    __GEN_MASK (mask2, len2, is_short);                                              \
    dst.l.l0 = dst.l.l1 = 0;                                                         \
                                                                                     \
    if (cmp_type == 0) { /******************* equal any (поиск символов) **********/ \
        __CMP_EQUAL_ANY (dst, src1, src2, len1, mask2, is_short);                    \
    }                                                                                \
    else if (cmp_type == 1) { /*************** ranges (поиск в диапазоне) *********/ \
        __CMP_RANGES (dst, src1, src2, len1, mask2, is_signed, is_short);            \
    }                                                                                \
    else if (cmp_type == 2) { /************ equal each (сравнение строк) **********/ \
        __CMP_EQUAL_EACH (dst, src1, src2, len1, len2, mask1, mask2, is_short);      \
    }                                                                                \
    else { /********************** equal ordered (поиск подстроки) ****************/ \
        __CMP_EQUAL_ORDERED (dst, src1, src2, len1, len2, mask1, is_short);          \
    }                                                                                \
    if (polarity & 1) { /* negative and masked negative polarity */                  \
        if (polarity & 2) { /* masked negative polarity */                           \
            dst.l.l0 ^= mask2.l.l0;                                                  \
            dst.l.l1 ^= mask2.l.l1;                                                  \
        }                                                                            \
        else {                                                                       \
            dst.l.l0 = ~dst.l.l0;                                                    \
            dst.l.l1 = ~dst.l.l1;                                                    \
        }                                                                            \
    }                                                                                \
}

/* преобразование байтовой/шортовой маски в битовую */
#define __WORDMASK_TO_BITMASK(dst, is_short) {                                       \
    if (is_short) { /* шортовую маску преобразуем в байтовую */                      \
        dst.l.l0 = __builtin_e2k_packushb (dst.l.l1 & 0x00ff00ff00ff00ffLL,          \
                                           dst.l.l0 & 0x00ff00ff00ff00ffLL);         \
        dst.l.l1 = 0;                                                                \
    }                                                                                \
    dst.l.l0 = __builtin_e2k_pmovmskb (dst.l.l1, dst.l.l0);                          \
    dst.l.l1 = 0;                                                                    \
}

/* преобразование байтовой/шортовой маски в номер первой или последней единицы */
#define __MASK_TO_INDEX(indx, mask, msb, is_short) {                                 \
    indx = __builtin_e2k_pmovmskb (mask.l.l1, mask.l.l0);                            \
    if (!(msb)) { /* least significant bit */                                        \
        __BITREV_16U (indx, indx); /* разворот младших 16 бит */                     \
    }                                                                                \
    __CLZ (indx, indx);                                                              \
    if (!(msb)) { /* least significant bit */                                        \
        indx -= 16;                                                                  \
    }                                                                                \
    else {                                                                           \
        indx = (indx == 32) ? 16 : 31 - indx;                                        \
    }                                                                                \
    if (is_short) { /* делим индекс на 2 */                                          \
        indx >>= 1;                                                                  \
    }                                                                                \
}

#else /* __iset__ <= 4 */

/*****************************************************************************/

/* Сравнение на "equal each" (сравнение строк)  */
#define __CMP_EQUAL_EACH(res,src1,src2,len1,len2,mask1,mask2,is_short) {             \
    __v2di tmp1 = __builtin_e2k_qpand (src1.__v2di, mask1.__v2di); /* очищаем src1 от лишних символов */ \
    __v2di tmp2 = __builtin_e2k_qpand (src2.__v2di, mask2.__v2di); /* очищаем src2 от лишних символов */ \
    if (len1 > len2) {  /* вставляем "1" в зону пересечения длин */                  \
        tmp1 = __builtin_e2k_qplog (0xbc, mask1.__v2di, mask2.__v2di, src1.__v2di); /* m1 ^ m2) | (m1 & s1) */\
    }                                                                                \
    else if (len1 < len2) {   /* вставляем "1" в зону пересечения длин */            \
        tmp2 = __builtin_e2k_qplog (0xbc, mask1.__v2di, mask2.__v2di, src2.__v2di); /* m1 ^ m2) | (m1 & s2) */\
    }                                                                                \
    if (is_short) {                                                                  \
        res.__v2di = __builtin_e2k_qpcmpeqh (tmp1, tmp2);                            \
    }                                                                                \
    else {                                                                           \
        res.__v2di = __builtin_e2k_qpcmpeqb (tmp1, tmp2);                            \
    }                                                                                \
}

 #if __iset__ <= 5
#define __QPCMPEQH(src1,src2)                                                        \
    __builtin_e2k_qpsgn2mskb (__builtin_e2k_qpcmpeqh (src1, src2)) == 0xffff
 #else /* __iset__ <= 5 */
#define __QPCMPEQH(src1,src2)                                                        \
    __builtin_e2k_qpcmpeqhap (src1, src2)
 #endif /* __iset__ <= 5 */

/* Сравнение на "equal ordered" (поиск подстроки)  */
#define __CMP_EQUAL_ORDERED(res, src1, src2, len1, len2, mask1, is_short) {          \
    __v2di tmp0, tmp1, tmp2;                                                         \
    int i, msk = 0;                                                                  \
    if (len1 == 0) { /* пустая строка выдает все "1" */                              \
        res.__v2di = __builtin_e2k_qppackdl (-1LL, -1LL);                            \
    }                                                                                \
    else {                                                                           \
        tmp1 = __builtin_e2k_qpand (src1.__v2di, mask1.__v2di); /* очищаем src1 от лишних символов */ \
                                                                                     \
        if (is_short) {                                                              \
_Pragma ("loop count (4)")                                                           \
            for (i = 0; i < (len2 - len1 + 1); i++) {                                \
                tmp2 = __builtin_e2k_qpand (src2.__v2di, mask1.__v2di);              \
                if (__QPCMPEQH (tmp1, tmp2)) {                                       \
                    msk |= 1 << (2 * i + 1);                                         \
                }                                                                    \
                src2.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), src2.__v2di, /* >>16 */\
                           __builtin_e2k_qppackdl (0x10100f0e0d0c0b0aLL, 0x0908070605040302LL)); \
            }                                                                        \
            tmp2 = __builtin_e2k_qpmsk2sgnb (__builtin_e2k_qppackdl (0, 0), msk); /* биты преобразуем в шорты */ \
            res.__v2di = __builtin_e2k_qpsrah (tmp2, 15);                            \
        }                                                                            \
        else {                                                                       \
_Pragma ("loop count (4)")                                                           \
            for (i = 0; i < (len2 - len1 + 1); i++) {                                \
                tmp2 = __builtin_e2k_qpand (src2.__v2di, mask1.__v2di);              \
                if (__QPCMPEQH (tmp1, tmp2)) {                                       \
                    msk |= (1 << i);                                                 \
                }                                                                    \
                src2.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), src2.__v2di, /* >>8 */\
                           __builtin_e2k_qppackdl (0x100f0e0d0c0b0a09LL, 0x0807060504030201LL)); \
            }                                                                        \
            tmp2 = __builtin_e2k_qpmsk2sgnb (__builtin_e2k_qppackdl (0, 0), msk); /* биты преобразуем в байты */ \
            res.__v2di = __builtin_e2k_qpcmpgtb (__builtin_e2k_qppackdl (0, 0), tmp2);\
        }                                                                            \
    }                                                                                \
}

/* Сравнение строк c заданными длинами и выдачей байтовой/шортовой маски */
#define __PCMP_STR(dst, src1, len1, src2, len2, is_short, mode) {                    \
    type_union_128 mask1, mask2;                                                     \
    int polarity  = (mode & 0x30) >> 4;                                              \
    int cmp_type  = (mode & 0xc) >> 2;                                               \
    int is_signed = mode & 0x2;                                                      \
                                                                                     \
    /* генерация масок валидности */                                                 \
    __GEN_MASK (mask1, len1, is_short);                                              \
    __GEN_MASK (mask2, len2, is_short);                                              \
    dst.__v2di = __builtin_e2k_qppackdl (0, 0);                                      \
                                                                                     \
    if (cmp_type == 0) { /******************* equal any (поиск символов) **********/ \
        __CMP_EQUAL_ANY (dst, src1, src2, len1, mask2, is_short);                    \
    }                                                                                \
    else if (cmp_type == 1) { /*************** ranges (поиск в диапазоне) *********/ \
        __CMP_RANGES (dst, src1, src2, len1, mask2, is_signed, is_short);            \
    }                                                                                \
    else if (cmp_type == 2) { /************ equal each (сравнение строк) **********/ \
        __CMP_EQUAL_EACH (dst, src1, src2, len1, len2, mask1, mask2, is_short);      \
    }                                                                                \
    else { /********************** equal ordered (поиск подстроки) ****************/ \
        __CMP_EQUAL_ORDERED (dst, src1, src2, len1, len2, mask1, is_short);          \
    }                                                                                \
    if (polarity & 1) { /* negative and masked negative polarity */                  \
        if (polarity & 2) { /* masked negative polarity */                           \
            dst.__v2di = __builtin_e2k_qpxor (dst.__v2di, mask2.__v2di);             \
        }                                                                            \
        else {                                                                       \
            dst.__v2di = __builtin_e2k_qpxor (dst.__v2di, __builtin_e2k_qppackdl (-1LL, -1LL));\
        }                                                                            \
    }                                                                                \
}

/* преобразование байтовой/шортовой маски в битовую */
#define __WORDMASK_TO_BITMASK(dst, is_short) {                                       \
    if (is_short) { /* шортовую маску преобразуем в байтовую */                      \
        dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), dst.__v2di,\
               __builtin_e2k_qppackdl (0x1010101010101010LL, 0x0e0c0a0806040200LL)); \
    }                                                                                \
    __di tmp = __builtin_e2k_qpsgn2mskb (dst.__v2di);                                \
    dst.__v2di = __builtin_e2k_qppackdl (0, tmp);                                    \
}

/* преобразование байтовой/шортовой маски в номер первой или последней единицы */
#define __MASK_TO_INDEX(indx, mask, msb, is_short) {                                 \
    indx = __builtin_e2k_qpsgn2mskb (mask.__v2di);                                   \
    if (!(msb)) { /* least significant bit */                                        \
        __BITREV_16U (indx, indx); /* разворот младших 16 бит */                     \
    }                                                                                \
    __CLZ (indx, indx);                                                              \
    if (!(msb)) { /* least significant bit */                                        \
        indx -= 16;                                                                  \
    }                                                                                \
    else {                                                                           \
        indx = (indx == 32) ? 16 : 31 - indx;                                        \
    }                                                                                \
    if (is_short) { /* делим индекс на 2 */                                          \
        indx >>= 1;                                                                  \
    }                                                                                \
}

#endif /* __iset__ <= 4 */

/*****************************************************************************/
/* абсолютное значение длины строки и ее сатурация  */

#define __ABS_AND_SATURATE_LEN(len, is_short) {                                      \
    int maxlen = (is_short) ? 8 : 16;                                                \
    len = __builtin_abs (len);                                                       \
    len = (len > maxlen) ? maxlen : len;                                             \
}                                                                                    \

/*****************************************************************************/
/* Сравнение строк неявной длины c генерацией битовой или байтовой/шортовой маски.  */
__E2K_INLINE __E2K_WARNING (__v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpistrm128 (__v16qi src1, __v16qi src2, const int mode))
{
    type_union_128 s1, s2, dst;
    int word_mask = mode & 0x40;
    int is_short  = mode & 0x1;
    int len1, len2;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    /* определение длины строк */
    __CALC_LEN (len1, s1, is_short);
    __CALC_LEN (len2, s2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

    if (!word_mask) { /* битовая маска */
        __WORDMASK_TO_BITMASK (dst, is_short);
    }
    return dst.__v16qi;
}

/*****************************************************************************/
/* Сравнение строк неявной длины c выдачей номера первой или последней единицы. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpistri128 (__v16qi src1, __v16qi src2, const int mode))
{
    type_union_128 s1, s2, dst;
    int msb = mode & 0x40;
    int is_short = mode & 0x1;
    int indx, len1, len2;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    /* определение длины строк */
    __CALC_LEN (len1, s1, is_short);
    __CALC_LEN (len2, s2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

    /* преобразование байтовой/шортовой маски в номер первой или последней единицы */
    __MASK_TO_INDEX (indx, dst, msb, is_short);
    return indx;
}

/*****************************************************************************/
/* Сравнение строк заданной длины c генерацией битовой или байтовой/шортовой маски.  */
__E2K_INLINE __E2K_WARNING (__v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpestrm128 (__v16qi src1, int len1, __v16qi src2, int len2, const int mode))
{
    type_union_128 s1, s2, dst;
    int word_mask = mode & 0x40;
    int is_short  = mode & 0x1;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    __ABS_AND_SATURATE_LEN (len1, is_short);
    __ABS_AND_SATURATE_LEN (len2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

    if (!word_mask) { /* битовая маска */
        __WORDMASK_TO_BITMASK (dst, is_short);
    }
    return dst.__v16qi;
}

/*****************************************************************************/
/* Сравнение строк заданной длины c выдачей номера первой или последней единицы. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpestri128 (__v16qi src1, int len1, __v16qi src2, int len2, const int mode))
{
    type_union_128 s1, s2, dst;
    int msb = mode & 0x40;
    int is_short = mode & 0x1;
    int indx;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    __ABS_AND_SATURATE_LEN (len1, is_short);
    __ABS_AND_SATURATE_LEN (len2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

    /* преобразование байтовой/шортовой маски в номер первой или последней единицы */
    __MASK_TO_INDEX (indx, dst, msb, is_short);
    return indx;
}

/*****************************************************************************/
/* Сравнение строк неявной длины. Возвращает "1", если вычисленная маска = 0 и
 * src2 не содержит конца строки. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpistria128 (__v16qi src1, __v16qi src2, const int mode))
{
    type_union_128 s1, s2, dst;
    int is_short = mode & 0x1;
    int len1, len2;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    /* определение длины строк */
    __CALC_LEN (len1, s1, is_short);
    __CALC_LEN (len2, s2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

#if __iset__ <= 5
    return (dst.l.l1 | dst.l.l0) == 0 && len2 == ((is_short) ? 8 : 16);
#else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (dst.__v2di, __builtin_e2k_qppackdl (0, 0)) && len2 == ((is_short) ? 8 : 16);
#endif /* __iset__ <= 5 */
}

/*****************************************************************************/
/* Сравнение строк неявной длины. Возвращает "1", если вычисленная маска != 0. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpistric128 (__v16qi src1, __v16qi src2, const int mode))
{
    type_union_128 s1, s2, dst;
    int is_short = mode & 0x1;
    int len1, len2;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    /* определение длины строк */
    __CALC_LEN (len1, s1, is_short);
    __CALC_LEN (len2, s2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

#if __iset__ <= 5
    return (dst.l.l1 | dst.l.l0) != 0;
#else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (dst.__v2di, __builtin_e2k_qppackdl (0, 0)) == 0;
#endif /* __iset__ <= 5 */
}

/*****************************************************************************/
/* Сравнение строк неявной длины. Возвращает младший бит вычисленной маски. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpistrio128 (__v16qi src1, __v16qi src2, const int mode))
{
    type_union_128 s1, s2, dst;
    int is_short = mode & 0x1;
    int len1, len2;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    /* определение длины строк */
    __CALC_LEN (len1, s1, is_short);
    __CALC_LEN (len2, s2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

    return dst.l.l0 & 1;
}

/*****************************************************************************/
/* Сравнение строк неявной длины. Возвращает "1", если в src1 был нулевой символ конца строки. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpistris128 (__v16qi src1, __v16qi src2, const int mode)
{
    type_union_128 s1;
    int is_short = mode & 0x1;
    int len1;
    s1.__v16qi = src1;

    /* определение длины строк */
    __CALC_LEN (len1, s1, is_short);

    return len1 != ((is_short) ? 8 : 16);
}

/*****************************************************************************/
/* Сравнение строк неявной длины. Возвращает "1", если в src2 был нулевой символ конца строки. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpistriz128 (__v16qi src1, __v16qi src2, const int mode)
{
    type_union_128 s2;
    int is_short = mode & 0x1;
    int len2;
    s2.__v16qi = src2;

    /* определение длины строк */
    __CALC_LEN (len2, s2, is_short);

    return len2 != ((is_short) ? 8 : 16);
}

/*****************************************************************************/
/* Сравнение строк заданной длины. Возвращает "1", если вычисленная маска = 0 и
 * src2 не содержит конца строки. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpestria128 (__v16qi src1, int len1, __v16qi src2, int len2, const int mode))
{
    type_union_128 s1, s2, dst;
    int is_short = mode & 0x1;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    __ABS_AND_SATURATE_LEN (len1, is_short);
    __ABS_AND_SATURATE_LEN (len2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

#if __iset__ <= 5
    return (dst.l.l1 | dst.l.l0) == 0 && len2 == ((is_short) ? 8 : 16);
#else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (dst.__v2di, __builtin_e2k_qppackdl (0, 0)) && len2 == ((is_short) ? 8 : 16);
#endif /* __iset__ <= 5 */
}

/*****************************************************************************/
/* Сравнение строк заданной длины. Возвращает "1", если вычисленная маска != 0. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpestric128 (__v16qi src1, int len1, __v16qi src2, int len2, const int mode))
{
    type_union_128 s1, s2, dst;
    int is_short = mode & 0x1;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    __ABS_AND_SATURATE_LEN (len1, is_short);
    __ABS_AND_SATURATE_LEN (len2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

#if __iset__ <= 5
    return (dst.l.l1 | dst.l.l0) != 0;
#else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (dst.__v2di, __builtin_e2k_qppackdl (0, 0)) == 0;
#endif /* __iset__ <= 5 */
}

/*****************************************************************************/
/* Сравнение строк заданной длины. Возвращает младший бит вычисленной маски. */
__E2K_INLINE __E2K_WARNING (int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpestrio128 (__v16qi src1, int len1, __v16qi src2, int len2, const int mode))
{
    type_union_128 s1, s2, dst;
    int is_short = mode & 0x1;
    s1.__v16qi = src1;
    s2.__v16qi = src2;

    __ABS_AND_SATURATE_LEN (len1, is_short);
    __ABS_AND_SATURATE_LEN (len2, is_short);

    /* сравнение строк */
    __PCMP_STR (dst, s1, len1, s2, len2, is_short, mode);

    return dst.l.l0 & 1;
}

/*****************************************************************************/
/* Сравнение строк заданной длины. Возвращает "1", если в src1 был нулевой символ конца строки. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpestris128 (__v16qi src1, int len1, __v16qi src2, int len2, const int mode)
{
    int is_short = mode & 0x1;

    __ABS_AND_SATURATE_LEN (len1, is_short);

    return len1 != ((is_short) ? 8 : 16);
}

/*****************************************************************************/
/* Сравнение строк заданной длины. Возвращает "1", если в src2 был нулевой символ конца строки. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpestriz128 (__v16qi src1, int len1, __v16qi src2, int len2, const int mode)
{
    int is_short  = mode & 0x1;

    __ABS_AND_SATURATE_LEN (len2, is_short);

    return len2 != ((is_short) ? 8 : 16);
}

/* *****************************************************************************
 *                               Сравнение
 * *****************************************************************************/

/* сравнение на "больше" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pcmpgtq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = ((long long) s1.l.l0 > (long long) s2.l.l0) ? -1LL : 0;
    dst.l.l1 = ((long long) s1.l.l1 > (long long) s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pcmpgtd (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgtd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtd (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* *****************************************************************************
 *                                    CRC32
 * *****************************************************************************/

#if 0   /* original algorithm */
/* CRC-32C (iSCSI) polynomial in reversed bit order. */
#define POLY 0x82f63b78

/* Table for a quadword-at-a-time software crc. */
static unsigned crc32c_table[8][256];

/* Construct table for software CRC-32C calculation. */
static void crc32c_init_sw(void)
{
    unsigned n, crc, k;

    for (n = 0; n < 256; n++) {
        crc = n;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc32c_table[0][n] = crc;
    }
    for (n = 0; n < 256; n++) {
        crc = crc32c_table[0][n];
        for (k = 1; k < 8; k++) {
            crc = crc32c_table[0][crc & 0xff] ^ (crc >> 8);
            crc32c_table[k][n] = crc;
        }
    }
}
#endif

/* Table for a 64-bit-at-a-time software crc. */
static const unsigned __crc32c_tab[8][256] = {
/* k=0 */
    0x00000000, 0xf26b8303, 0xe13b70f7, 0x1350f3f4, 0xc79a971f, 0x35f1141c, 0x26a1e7e8, 0xd4ca64eb,
    0x8ad958cf, 0x78b2dbcc, 0x6be22838, 0x9989ab3b, 0x4d43cfd0, 0xbf284cd3, 0xac78bf27, 0x5e133c24,
    0x105ec76f, 0xe235446c, 0xf165b798, 0x030e349b, 0xd7c45070, 0x25afd373, 0x36ff2087, 0xc494a384,
    0x9a879fa0, 0x68ec1ca3, 0x7bbcef57, 0x89d76c54, 0x5d1d08bf, 0xaf768bbc, 0xbc267848, 0x4e4dfb4b,
    0x20bd8ede, 0xd2d60ddd, 0xc186fe29, 0x33ed7d2a, 0xe72719c1, 0x154c9ac2, 0x061c6936, 0xf477ea35,
    0xaa64d611, 0x580f5512, 0x4b5fa6e6, 0xb93425e5, 0x6dfe410e, 0x9f95c20d, 0x8cc531f9, 0x7eaeb2fa,
    0x30e349b1, 0xc288cab2, 0xd1d83946, 0x23b3ba45, 0xf779deae, 0x05125dad, 0x1642ae59, 0xe4292d5a,
    0xba3a117e, 0x4851927d, 0x5b016189, 0xa96ae28a, 0x7da08661, 0x8fcb0562, 0x9c9bf696, 0x6ef07595,
    0x417b1dbc, 0xb3109ebf, 0xa0406d4b, 0x522bee48, 0x86e18aa3, 0x748a09a0, 0x67dafa54, 0x95b17957,
    0xcba24573, 0x39c9c670, 0x2a993584, 0xd8f2b687, 0x0c38d26c, 0xfe53516f, 0xed03a29b, 0x1f682198,
    0x5125dad3, 0xa34e59d0, 0xb01eaa24, 0x42752927, 0x96bf4dcc, 0x64d4cecf, 0x77843d3b, 0x85efbe38,
    0xdbfc821c, 0x2997011f, 0x3ac7f2eb, 0xc8ac71e8, 0x1c661503, 0xee0d9600, 0xfd5d65f4, 0x0f36e6f7,
    0x61c69362, 0x93ad1061, 0x80fde395, 0x72966096, 0xa65c047d, 0x5437877e, 0x4767748a, 0xb50cf789,
    0xeb1fcbad, 0x197448ae, 0x0a24bb5a, 0xf84f3859, 0x2c855cb2, 0xdeeedfb1, 0xcdbe2c45, 0x3fd5af46,
    0x7198540d, 0x83f3d70e, 0x90a324fa, 0x62c8a7f9, 0xb602c312, 0x44694011, 0x5739b3e5, 0xa55230e6,
    0xfb410cc2, 0x092a8fc1, 0x1a7a7c35, 0xe811ff36, 0x3cdb9bdd, 0xceb018de, 0xdde0eb2a, 0x2f8b6829,
    0x82f63b78, 0x709db87b, 0x63cd4b8f, 0x91a6c88c, 0x456cac67, 0xb7072f64, 0xa457dc90, 0x563c5f93,
    0x082f63b7, 0xfa44e0b4, 0xe9141340, 0x1b7f9043, 0xcfb5f4a8, 0x3dde77ab, 0x2e8e845f, 0xdce5075c,
    0x92a8fc17, 0x60c37f14, 0x73938ce0, 0x81f80fe3, 0x55326b08, 0xa759e80b, 0xb4091bff, 0x466298fc,
    0x1871a4d8, 0xea1a27db, 0xf94ad42f, 0x0b21572c, 0xdfeb33c7, 0x2d80b0c4, 0x3ed04330, 0xccbbc033,
    0xa24bb5a6, 0x502036a5, 0x4370c551, 0xb11b4652, 0x65d122b9, 0x97baa1ba, 0x84ea524e, 0x7681d14d,
    0x2892ed69, 0xdaf96e6a, 0xc9a99d9e, 0x3bc21e9d, 0xef087a76, 0x1d63f975, 0x0e330a81, 0xfc588982,
    0xb21572c9, 0x407ef1ca, 0x532e023e, 0xa145813d, 0x758fe5d6, 0x87e466d5, 0x94b49521, 0x66df1622,
    0x38cc2a06, 0xcaa7a905, 0xd9f75af1, 0x2b9cd9f2, 0xff56bd19, 0x0d3d3e1a, 0x1e6dcdee, 0xec064eed,
    0xc38d26c4, 0x31e6a5c7, 0x22b65633, 0xd0ddd530, 0x0417b1db, 0xf67c32d8, 0xe52cc12c, 0x1747422f,
    0x49547e0b, 0xbb3ffd08, 0xa86f0efc, 0x5a048dff, 0x8ecee914, 0x7ca56a17, 0x6ff599e3, 0x9d9e1ae0,
    0xd3d3e1ab, 0x21b862a8, 0x32e8915c, 0xc083125f, 0x144976b4, 0xe622f5b7, 0xf5720643, 0x07198540,
    0x590ab964, 0xab613a67, 0xb831c993, 0x4a5a4a90, 0x9e902e7b, 0x6cfbad78, 0x7fab5e8c, 0x8dc0dd8f,
    0xe330a81a, 0x115b2b19, 0x020bd8ed, 0xf0605bee, 0x24aa3f05, 0xd6c1bc06, 0xc5914ff2, 0x37faccf1,
    0x69e9f0d5, 0x9b8273d6, 0x88d28022, 0x7ab90321, 0xae7367ca, 0x5c18e4c9, 0x4f48173d, 0xbd23943e,
    0xf36e6f75, 0x0105ec76, 0x12551f82, 0xe03e9c81, 0x34f4f86a, 0xc69f7b69, 0xd5cf889d, 0x27a40b9e,
    0x79b737ba, 0x8bdcb4b9, 0x988c474d, 0x6ae7c44e, 0xbe2da0a5, 0x4c4623a6, 0x5f16d052, 0xad7d5351,
/* k=1 */
    0x00000000, 0x13a29877, 0x274530ee, 0x34e7a899, 0x4e8a61dc, 0x5d28f9ab, 0x69cf5132, 0x7a6dc945,
    0x9d14c3b8, 0x8eb65bcf, 0xba51f356, 0xa9f36b21, 0xd39ea264, 0xc03c3a13, 0xf4db928a, 0xe7790afd,
    0x3fc5f181, 0x2c6769f6, 0x1880c16f, 0x0b225918, 0x714f905d, 0x62ed082a, 0x560aa0b3, 0x45a838c4,
    0xa2d13239, 0xb173aa4e, 0x859402d7, 0x96369aa0, 0xec5b53e5, 0xfff9cb92, 0xcb1e630b, 0xd8bcfb7c,
    0x7f8be302, 0x6c297b75, 0x58ced3ec, 0x4b6c4b9b, 0x310182de, 0x22a31aa9, 0x1644b230, 0x05e62a47,
    0xe29f20ba, 0xf13db8cd, 0xc5da1054, 0xd6788823, 0xac154166, 0xbfb7d911, 0x8b507188, 0x98f2e9ff,
    0x404e1283, 0x53ec8af4, 0x670b226d, 0x74a9ba1a, 0x0ec4735f, 0x1d66eb28, 0x298143b1, 0x3a23dbc6,
    0xdd5ad13b, 0xcef8494c, 0xfa1fe1d5, 0xe9bd79a2, 0x93d0b0e7, 0x80722890, 0xb4958009, 0xa737187e,
    0xff17c604, 0xecb55e73, 0xd852f6ea, 0xcbf06e9d, 0xb19da7d8, 0xa23f3faf, 0x96d89736, 0x857a0f41,
    0x620305bc, 0x71a19dcb, 0x45463552, 0x56e4ad25, 0x2c896460, 0x3f2bfc17, 0x0bcc548e, 0x186eccf9,
    0xc0d23785, 0xd370aff2, 0xe797076b, 0xf4359f1c, 0x8e585659, 0x9dface2e, 0xa91d66b7, 0xbabffec0,
    0x5dc6f43d, 0x4e646c4a, 0x7a83c4d3, 0x69215ca4, 0x134c95e1, 0x00ee0d96, 0x3409a50f, 0x27ab3d78,
    0x809c2506, 0x933ebd71, 0xa7d915e8, 0xb47b8d9f, 0xce1644da, 0xddb4dcad, 0xe9537434, 0xfaf1ec43,
    0x1d88e6be, 0x0e2a7ec9, 0x3acdd650, 0x296f4e27, 0x53028762, 0x40a01f15, 0x7447b78c, 0x67e52ffb,
    0xbf59d487, 0xacfb4cf0, 0x981ce469, 0x8bbe7c1e, 0xf1d3b55b, 0xe2712d2c, 0xd69685b5, 0xc5341dc2,
    0x224d173f, 0x31ef8f48, 0x050827d1, 0x16aabfa6, 0x6cc776e3, 0x7f65ee94, 0x4b82460d, 0x5820de7a,
    0xfbc3faf9, 0xe861628e, 0xdc86ca17, 0xcf245260, 0xb5499b25, 0xa6eb0352, 0x920cabcb, 0x81ae33bc,
    0x66d73941, 0x7575a136, 0x419209af, 0x523091d8, 0x285d589d, 0x3bffc0ea, 0x0f186873, 0x1cbaf004,
    0xc4060b78, 0xd7a4930f, 0xe3433b96, 0xf0e1a3e1, 0x8a8c6aa4, 0x992ef2d3, 0xadc95a4a, 0xbe6bc23d,
    0x5912c8c0, 0x4ab050b7, 0x7e57f82e, 0x6df56059, 0x1798a91c, 0x043a316b, 0x30dd99f2, 0x237f0185,
    0x844819fb, 0x97ea818c, 0xa30d2915, 0xb0afb162, 0xcac27827, 0xd960e050, 0xed8748c9, 0xfe25d0be,
    0x195cda43, 0x0afe4234, 0x3e19eaad, 0x2dbb72da, 0x57d6bb9f, 0x447423e8, 0x70938b71, 0x63311306,
    0xbb8de87a, 0xa82f700d, 0x9cc8d894, 0x8f6a40e3, 0xf50789a6, 0xe6a511d1, 0xd242b948, 0xc1e0213f,
    0x26992bc2, 0x353bb3b5, 0x01dc1b2c, 0x127e835b, 0x68134a1e, 0x7bb1d269, 0x4f567af0, 0x5cf4e287,
    0x04d43cfd, 0x1776a48a, 0x23910c13, 0x30339464, 0x4a5e5d21, 0x59fcc556, 0x6d1b6dcf, 0x7eb9f5b8,
    0x99c0ff45, 0x8a626732, 0xbe85cfab, 0xad2757dc, 0xd74a9e99, 0xc4e806ee, 0xf00fae77, 0xe3ad3600,
    0x3b11cd7c, 0x28b3550b, 0x1c54fd92, 0x0ff665e5, 0x759baca0, 0x663934d7, 0x52de9c4e, 0x417c0439,
    0xa6050ec4, 0xb5a796b3, 0x81403e2a, 0x92e2a65d, 0xe88f6f18, 0xfb2df76f, 0xcfca5ff6, 0xdc68c781,
    0x7b5fdfff, 0x68fd4788, 0x5c1aef11, 0x4fb87766, 0x35d5be23, 0x26772654, 0x12908ecd, 0x013216ba,
    0xe64b1c47, 0xf5e98430, 0xc10e2ca9, 0xd2acb4de, 0xa8c17d9b, 0xbb63e5ec, 0x8f844d75, 0x9c26d502,
    0x449a2e7e, 0x5738b609, 0x63df1e90, 0x707d86e7, 0x0a104fa2, 0x19b2d7d5, 0x2d557f4c, 0x3ef7e73b,
    0xd98eedc6, 0xca2c75b1, 0xfecbdd28, 0xed69455f, 0x97048c1a, 0x84a6146d, 0xb041bcf4, 0xa3e32483,
/* k=2 */
    0x00000000, 0xa541927e, 0x4f6f520d, 0xea2ec073, 0x9edea41a, 0x3b9f3664, 0xd1b1f617, 0x74f06469,
    0x38513ec5, 0x9d10acbb, 0x773e6cc8, 0xd27ffeb6, 0xa68f9adf, 0x03ce08a1, 0xe9e0c8d2, 0x4ca15aac,
    0x70a27d8a, 0xd5e3eff4, 0x3fcd2f87, 0x9a8cbdf9, 0xee7cd990, 0x4b3d4bee, 0xa1138b9d, 0x045219e3,
    0x48f3434f, 0xedb2d131, 0x079c1142, 0xa2dd833c, 0xd62de755, 0x736c752b, 0x9942b558, 0x3c032726,
    0xe144fb14, 0x4405696a, 0xae2ba919, 0x0b6a3b67, 0x7f9a5f0e, 0xdadbcd70, 0x30f50d03, 0x95b49f7d,
    0xd915c5d1, 0x7c5457af, 0x967a97dc, 0x333b05a2, 0x47cb61cb, 0xe28af3b5, 0x08a433c6, 0xade5a1b8,
    0x91e6869e, 0x34a714e0, 0xde89d493, 0x7bc846ed, 0x0f382284, 0xaa79b0fa, 0x40577089, 0xe516e2f7,
    0xa9b7b85b, 0x0cf62a25, 0xe6d8ea56, 0x43997828, 0x37691c41, 0x92288e3f, 0x78064e4c, 0xdd47dc32,
    0xc76580d9, 0x622412a7, 0x880ad2d4, 0x2d4b40aa, 0x59bb24c3, 0xfcfab6bd, 0x16d476ce, 0xb395e4b0,
    0xff34be1c, 0x5a752c62, 0xb05bec11, 0x151a7e6f, 0x61ea1a06, 0xc4ab8878, 0x2e85480b, 0x8bc4da75,
    0xb7c7fd53, 0x12866f2d, 0xf8a8af5e, 0x5de93d20, 0x29195949, 0x8c58cb37, 0x66760b44, 0xc337993a,
    0x8f96c396, 0x2ad751e8, 0xc0f9919b, 0x65b803e5, 0x1148678c, 0xb409f5f2, 0x5e273581, 0xfb66a7ff,
    0x26217bcd, 0x8360e9b3, 0x694e29c0, 0xcc0fbbbe, 0xb8ffdfd7, 0x1dbe4da9, 0xf7908dda, 0x52d11fa4,
    0x1e704508, 0xbb31d776, 0x511f1705, 0xf45e857b, 0x80aee112, 0x25ef736c, 0xcfc1b31f, 0x6a802161,
    0x56830647, 0xf3c29439, 0x19ec544a, 0xbcadc634, 0xc85da25d, 0x6d1c3023, 0x8732f050, 0x2273622e,
    0x6ed23882, 0xcb93aafc, 0x21bd6a8f, 0x84fcf8f1, 0xf00c9c98, 0x554d0ee6, 0xbf63ce95, 0x1a225ceb,
    0x8b277743, 0x2e66e53d, 0xc448254e, 0x6109b730, 0x15f9d359, 0xb0b84127, 0x5a968154, 0xffd7132a,
    0xb3764986, 0x1637dbf8, 0xfc191b8b, 0x595889f5, 0x2da8ed9c, 0x88e97fe2, 0x62c7bf91, 0xc7862def,
    0xfb850ac9, 0x5ec498b7, 0xb4ea58c4, 0x11abcaba, 0x655baed3, 0xc01a3cad, 0x2a34fcde, 0x8f756ea0,
    0xc3d4340c, 0x6695a672, 0x8cbb6601, 0x29faf47f, 0x5d0a9016, 0xf84b0268, 0x1265c21b, 0xb7245065,
    0x6a638c57, 0xcf221e29, 0x250cde5a, 0x804d4c24, 0xf4bd284d, 0x51fcba33, 0xbbd27a40, 0x1e93e83e,
    0x5232b292, 0xf77320ec, 0x1d5de09f, 0xb81c72e1, 0xccec1688, 0x69ad84f6, 0x83834485, 0x26c2d6fb,
    0x1ac1f1dd, 0xbf8063a3, 0x55aea3d0, 0xf0ef31ae, 0x841f55c7, 0x215ec7b9, 0xcb7007ca, 0x6e3195b4,
    0x2290cf18, 0x87d15d66, 0x6dff9d15, 0xc8be0f6b, 0xbc4e6b02, 0x190ff97c, 0xf321390f, 0x5660ab71,
    0x4c42f79a, 0xe90365e4, 0x032da597, 0xa66c37e9, 0xd29c5380, 0x77ddc1fe, 0x9df3018d, 0x38b293f3,
    0x7413c95f, 0xd1525b21, 0x3b7c9b52, 0x9e3d092c, 0xeacd6d45, 0x4f8cff3b, 0xa5a23f48, 0x00e3ad36,
    0x3ce08a10, 0x99a1186e, 0x738fd81d, 0xd6ce4a63, 0xa23e2e0a, 0x077fbc74, 0xed517c07, 0x4810ee79,
    0x04b1b4d5, 0xa1f026ab, 0x4bdee6d8, 0xee9f74a6, 0x9a6f10cf, 0x3f2e82b1, 0xd50042c2, 0x7041d0bc,
    0xad060c8e, 0x08479ef0, 0xe2695e83, 0x4728ccfd, 0x33d8a894, 0x96993aea, 0x7cb7fa99, 0xd9f668e7,
    0x9557324b, 0x3016a035, 0xda386046, 0x7f79f238, 0x0b899651, 0xaec8042f, 0x44e6c45c, 0xe1a75622,
    0xdda47104, 0x78e5e37a, 0x92cb2309, 0x378ab177, 0x437ad51e, 0xe63b4760, 0x0c158713, 0xa954156d,
    0xe5f54fc1, 0x40b4ddbf, 0xaa9a1dcc, 0x0fdb8fb2, 0x7b2bebdb, 0xde6a79a5, 0x3444b9d6, 0x91052ba8,
/* k=3 */
    0x00000000, 0xdd45aab8, 0xbf672381, 0x62228939, 0x7b2231f3, 0xa6679b4b, 0xc4451272, 0x1900b8ca,
    0xf64463e6, 0x2b01c95e, 0x49234067, 0x9466eadf, 0x8d665215, 0x5023f8ad, 0x32017194, 0xef44db2c,
    0xe964b13d, 0x34211b85, 0x560392bc, 0x8b463804, 0x924680ce, 0x4f032a76, 0x2d21a34f, 0xf06409f7,
    0x1f20d2db, 0xc2657863, 0xa047f15a, 0x7d025be2, 0x6402e328, 0xb9474990, 0xdb65c0a9, 0x06206a11,
    0xd725148b, 0x0a60be33, 0x6842370a, 0xb5079db2, 0xac072578, 0x71428fc0, 0x136006f9, 0xce25ac41,
    0x2161776d, 0xfc24ddd5, 0x9e0654ec, 0x4343fe54, 0x5a43469e, 0x8706ec26, 0xe524651f, 0x3861cfa7,
    0x3e41a5b6, 0xe3040f0e, 0x81268637, 0x5c632c8f, 0x45639445, 0x98263efd, 0xfa04b7c4, 0x27411d7c,
    0xc805c650, 0x15406ce8, 0x7762e5d1, 0xaa274f69, 0xb327f7a3, 0x6e625d1b, 0x0c40d422, 0xd1057e9a,
    0xaba65fe7, 0x76e3f55f, 0x14c17c66, 0xc984d6de, 0xd0846e14, 0x0dc1c4ac, 0x6fe34d95, 0xb2a6e72d,
    0x5de23c01, 0x80a796b9, 0xe2851f80, 0x3fc0b538, 0x26c00df2, 0xfb85a74a, 0x99a72e73, 0x44e284cb,
    0x42c2eeda, 0x9f874462, 0xfda5cd5b, 0x20e067e3, 0x39e0df29, 0xe4a57591, 0x8687fca8, 0x5bc25610,
    0xb4868d3c, 0x69c32784, 0x0be1aebd, 0xd6a40405, 0xcfa4bccf, 0x12e11677, 0x70c39f4e, 0xad8635f6,
    0x7c834b6c, 0xa1c6e1d4, 0xc3e468ed, 0x1ea1c255, 0x07a17a9f, 0xdae4d027, 0xb8c6591e, 0x6583f3a6,
    0x8ac7288a, 0x57828232, 0x35a00b0b, 0xe8e5a1b3, 0xf1e51979, 0x2ca0b3c1, 0x4e823af8, 0x93c79040,
    0x95e7fa51, 0x48a250e9, 0x2a80d9d0, 0xf7c57368, 0xeec5cba2, 0x3380611a, 0x51a2e823, 0x8ce7429b,
    0x63a399b7, 0xbee6330f, 0xdcc4ba36, 0x0181108e, 0x1881a844, 0xc5c402fc, 0xa7e68bc5, 0x7aa3217d,
    0x52a0c93f, 0x8fe56387, 0xedc7eabe, 0x30824006, 0x2982f8cc, 0xf4c75274, 0x96e5db4d, 0x4ba071f5,
    0xa4e4aad9, 0x79a10061, 0x1b838958, 0xc6c623e0, 0xdfc69b2a, 0x02833192, 0x60a1b8ab, 0xbde41213,
    0xbbc47802, 0x6681d2ba, 0x04a35b83, 0xd9e6f13b, 0xc0e649f1, 0x1da3e349, 0x7f816a70, 0xa2c4c0c8,
    0x4d801be4, 0x90c5b15c, 0xf2e73865, 0x2fa292dd, 0x36a22a17, 0xebe780af, 0x89c50996, 0x5480a32e,
    0x8585ddb4, 0x58c0770c, 0x3ae2fe35, 0xe7a7548d, 0xfea7ec47, 0x23e246ff, 0x41c0cfc6, 0x9c85657e,
    0x73c1be52, 0xae8414ea, 0xcca69dd3, 0x11e3376b, 0x08e38fa1, 0xd5a62519, 0xb784ac20, 0x6ac10698,
    0x6ce16c89, 0xb1a4c631, 0xd3864f08, 0x0ec3e5b0, 0x17c35d7a, 0xca86f7c2, 0xa8a47efb, 0x75e1d443,
    0x9aa50f6f, 0x47e0a5d7, 0x25c22cee, 0xf8878656, 0xe1873e9c, 0x3cc29424, 0x5ee01d1d, 0x83a5b7a5,
    0xf90696d8, 0x24433c60, 0x4661b559, 0x9b241fe1, 0x8224a72b, 0x5f610d93, 0x3d4384aa, 0xe0062e12,
    0x0f42f53e, 0xd2075f86, 0xb025d6bf, 0x6d607c07, 0x7460c4cd, 0xa9256e75, 0xcb07e74c, 0x16424df4,
    0x106227e5, 0xcd278d5d, 0xaf050464, 0x7240aedc, 0x6b401616, 0xb605bcae, 0xd4273597, 0x09629f2f,
    0xe6264403, 0x3b63eebb, 0x59416782, 0x8404cd3a, 0x9d0475f0, 0x4041df48, 0x22635671, 0xff26fcc9,
    0x2e238253, 0xf36628eb, 0x9144a1d2, 0x4c010b6a, 0x5501b3a0, 0x88441918, 0xea669021, 0x37233a99,
    0xd867e1b5, 0x05224b0d, 0x6700c234, 0xba45688c, 0xa345d046, 0x7e007afe, 0x1c22f3c7, 0xc167597f,
    0xc747336e, 0x1a0299d6, 0x782010ef, 0xa565ba57, 0xbc65029d, 0x6120a825, 0x0302211c, 0xde478ba4,
    0x31035088, 0xec46fa30, 0x8e647309, 0x5321d9b1, 0x4a21617b, 0x9764cbc3, 0xf54642fa, 0x2803e842,
/* k=4 */
    0x00000000, 0x38116fac, 0x7022df58, 0x4833b0f4, 0xe045beb0, 0xd854d11c, 0x906761e8, 0xa8760e44,
    0xc5670b91, 0xfd76643d, 0xb545d4c9, 0x8d54bb65, 0x2522b521, 0x1d33da8d, 0x55006a79, 0x6d1105d5,
    0x8f2261d3, 0xb7330e7f, 0xff00be8b, 0xc711d127, 0x6f67df63, 0x5776b0cf, 0x1f45003b, 0x27546f97,
    0x4a456a42, 0x725405ee, 0x3a67b51a, 0x0276dab6, 0xaa00d4f2, 0x9211bb5e, 0xda220baa, 0xe2336406,
    0x1ba8b557, 0x23b9dafb, 0x6b8a6a0f, 0x539b05a3, 0xfbed0be7, 0xc3fc644b, 0x8bcfd4bf, 0xb3debb13,
    0xdecfbec6, 0xe6ded16a, 0xaeed619e, 0x96fc0e32, 0x3e8a0076, 0x069b6fda, 0x4ea8df2e, 0x76b9b082,
    0x948ad484, 0xac9bbb28, 0xe4a80bdc, 0xdcb96470, 0x74cf6a34, 0x4cde0598, 0x04edb56c, 0x3cfcdac0,
    0x51eddf15, 0x69fcb0b9, 0x21cf004d, 0x19de6fe1, 0xb1a861a5, 0x89b90e09, 0xc18abefd, 0xf99bd151,
    0x37516aae, 0x0f400502, 0x4773b5f6, 0x7f62da5a, 0xd714d41e, 0xef05bbb2, 0xa7360b46, 0x9f2764ea,
    0xf236613f, 0xca270e93, 0x8214be67, 0xba05d1cb, 0x1273df8f, 0x2a62b023, 0x625100d7, 0x5a406f7b,
    0xb8730b7d, 0x806264d1, 0xc851d425, 0xf040bb89, 0x5836b5cd, 0x6027da61, 0x28146a95, 0x10050539,
    0x7d1400ec, 0x45056f40, 0x0d36dfb4, 0x3527b018, 0x9d51be5c, 0xa540d1f0, 0xed736104, 0xd5620ea8,
    0x2cf9dff9, 0x14e8b055, 0x5cdb00a1, 0x64ca6f0d, 0xccbc6149, 0xf4ad0ee5, 0xbc9ebe11, 0x848fd1bd,
    0xe99ed468, 0xd18fbbc4, 0x99bc0b30, 0xa1ad649c, 0x09db6ad8, 0x31ca0574, 0x79f9b580, 0x41e8da2c,
    0xa3dbbe2a, 0x9bcad186, 0xd3f96172, 0xebe80ede, 0x439e009a, 0x7b8f6f36, 0x33bcdfc2, 0x0badb06e,
    0x66bcb5bb, 0x5eadda17, 0x169e6ae3, 0x2e8f054f, 0x86f90b0b, 0xbee864a7, 0xf6dbd453, 0xcecabbff,
    0x6ea2d55c, 0x56b3baf0, 0x1e800a04, 0x269165a8, 0x8ee76bec, 0xb6f60440, 0xfec5b4b4, 0xc6d4db18,
    0xabc5decd, 0x93d4b161, 0xdbe70195, 0xe3f66e39, 0x4b80607d, 0x73910fd1, 0x3ba2bf25, 0x03b3d089,
    0xe180b48f, 0xd991db23, 0x91a26bd7, 0xa9b3047b, 0x01c50a3f, 0x39d46593, 0x71e7d567, 0x49f6bacb,
    0x24e7bf1e, 0x1cf6d0b2, 0x54c56046, 0x6cd40fea, 0xc4a201ae, 0xfcb36e02, 0xb480def6, 0x8c91b15a,
    0x750a600b, 0x4d1b0fa7, 0x0528bf53, 0x3d39d0ff, 0x954fdebb, 0xad5eb117, 0xe56d01e3, 0xdd7c6e4f,
    0xb06d6b9a, 0x887c0436, 0xc04fb4c2, 0xf85edb6e, 0x5028d52a, 0x6839ba86, 0x200a0a72, 0x181b65de,
    0xfa2801d8, 0xc2396e74, 0x8a0ade80, 0xb21bb12c, 0x1a6dbf68, 0x227cd0c4, 0x6a4f6030, 0x525e0f9c,
    0x3f4f0a49, 0x075e65e5, 0x4f6dd511, 0x777cbabd, 0xdf0ab4f9, 0xe71bdb55, 0xaf286ba1, 0x9739040d,
    0x59f3bff2, 0x61e2d05e, 0x29d160aa, 0x11c00f06, 0xb9b60142, 0x81a76eee, 0xc994de1a, 0xf185b1b6,
    0x9c94b463, 0xa485dbcf, 0xecb66b3b, 0xd4a70497, 0x7cd10ad3, 0x44c0657f, 0x0cf3d58b, 0x34e2ba27,
    0xd6d1de21, 0xeec0b18d, 0xa6f30179, 0x9ee26ed5, 0x36946091, 0x0e850f3d, 0x46b6bfc9, 0x7ea7d065,
    0x13b6d5b0, 0x2ba7ba1c, 0x63940ae8, 0x5b856544, 0xf3f36b00, 0xcbe204ac, 0x83d1b458, 0xbbc0dbf4,
    0x425b0aa5, 0x7a4a6509, 0x3279d5fd, 0x0a68ba51, 0xa21eb415, 0x9a0fdbb9, 0xd23c6b4d, 0xea2d04e1,
    0x873c0134, 0xbf2d6e98, 0xf71ede6c, 0xcf0fb1c0, 0x6779bf84, 0x5f68d028, 0x175b60dc, 0x2f4a0f70,
    0xcd796b76, 0xf56804da, 0xbd5bb42e, 0x854adb82, 0x2d3cd5c6, 0x152dba6a, 0x5d1e0a9e, 0x650f6532,
    0x081e60e7, 0x300f0f4b, 0x783cbfbf, 0x402dd013, 0xe85bde57, 0xd04ab1fb, 0x9879010f, 0xa0686ea3,
/* k=5 */
    0x00000000, 0xef306b19, 0xdb8ca0c3, 0x34bccbda, 0xb2f53777, 0x5dc55c6e, 0x697997b4, 0x8649fcad,
    0x6006181f, 0x8f367306, 0xbb8ab8dc, 0x54bad3c5, 0xd2f32f68, 0x3dc34471, 0x097f8fab, 0xe64fe4b2,
    0xc00c303e, 0x2f3c5b27, 0x1b8090fd, 0xf4b0fbe4, 0x72f90749, 0x9dc96c50, 0xa975a78a, 0x4645cc93,
    0xa00a2821, 0x4f3a4338, 0x7b8688e2, 0x94b6e3fb, 0x12ff1f56, 0xfdcf744f, 0xc973bf95, 0x2643d48c,
    0x85f4168d, 0x6ac47d94, 0x5e78b64e, 0xb148dd57, 0x370121fa, 0xd8314ae3, 0xec8d8139, 0x03bdea20,
    0xe5f20e92, 0x0ac2658b, 0x3e7eae51, 0xd14ec548, 0x570739e5, 0xb83752fc, 0x8c8b9926, 0x63bbf23f,
    0x45f826b3, 0xaac84daa, 0x9e748670, 0x7144ed69, 0xf70d11c4, 0x183d7add, 0x2c81b107, 0xc3b1da1e,
    0x25fe3eac, 0xcace55b5, 0xfe729e6f, 0x1142f576, 0x970b09db, 0x783b62c2, 0x4c87a918, 0xa3b7c201,
    0x0e045beb, 0xe13430f2, 0xd588fb28, 0x3ab89031, 0xbcf16c9c, 0x53c10785, 0x677dcc5f, 0x884da746,
    0x6e0243f4, 0x813228ed, 0xb58ee337, 0x5abe882e, 0xdcf77483, 0x33c71f9a, 0x077bd440, 0xe84bbf59,
    0xce086bd5, 0x213800cc, 0x1584cb16, 0xfab4a00f, 0x7cfd5ca2, 0x93cd37bb, 0xa771fc61, 0x48419778,
    0xae0e73ca, 0x413e18d3, 0x7582d309, 0x9ab2b810, 0x1cfb44bd, 0xf3cb2fa4, 0xc777e47e, 0x28478f67,
    0x8bf04d66, 0x64c0267f, 0x507ceda5, 0xbf4c86bc, 0x39057a11, 0xd6351108, 0xe289dad2, 0x0db9b1cb,
    0xebf65579, 0x04c63e60, 0x307af5ba, 0xdf4a9ea3, 0x5903620e, 0xb6330917, 0x828fc2cd, 0x6dbfa9d4,
    0x4bfc7d58, 0xa4cc1641, 0x9070dd9b, 0x7f40b682, 0xf9094a2f, 0x16392136, 0x2285eaec, 0xcdb581f5,
    0x2bfa6547, 0xc4ca0e5e, 0xf076c584, 0x1f46ae9d, 0x990f5230, 0x763f3929, 0x4283f2f3, 0xadb399ea,
    0x1c08b7d6, 0xf338dccf, 0xc7841715, 0x28b47c0c, 0xaefd80a1, 0x41cdebb8, 0x75712062, 0x9a414b7b,
    0x7c0eafc9, 0x933ec4d0, 0xa7820f0a, 0x48b26413, 0xcefb98be, 0x21cbf3a7, 0x1577387d, 0xfa475364,
    0xdc0487e8, 0x3334ecf1, 0x0788272b, 0xe8b84c32, 0x6ef1b09f, 0x81c1db86, 0xb57d105c, 0x5a4d7b45,
    0xbc029ff7, 0x5332f4ee, 0x678e3f34, 0x88be542d, 0x0ef7a880, 0xe1c7c399, 0xd57b0843, 0x3a4b635a,
    0x99fca15b, 0x76ccca42, 0x42700198, 0xad406a81, 0x2b09962c, 0xc439fd35, 0xf08536ef, 0x1fb55df6,
    0xf9fab944, 0x16cad25d, 0x22761987, 0xcd46729e, 0x4b0f8e33, 0xa43fe52a, 0x90832ef0, 0x7fb345e9,
    0x59f09165, 0xb6c0fa7c, 0x827c31a6, 0x6d4c5abf, 0xeb05a612, 0x0435cd0b, 0x308906d1, 0xdfb96dc8,
    0x39f6897a, 0xd6c6e263, 0xe27a29b9, 0x0d4a42a0, 0x8b03be0d, 0x6433d514, 0x508f1ece, 0xbfbf75d7,
    0x120cec3d, 0xfd3c8724, 0xc9804cfe, 0x26b027e7, 0xa0f9db4a, 0x4fc9b053, 0x7b757b89, 0x94451090,
    0x720af422, 0x9d3a9f3b, 0xa98654e1, 0x46b63ff8, 0xc0ffc355, 0x2fcfa84c, 0x1b736396, 0xf443088f,
    0xd200dc03, 0x3d30b71a, 0x098c7cc0, 0xe6bc17d9, 0x60f5eb74, 0x8fc5806d, 0xbb794bb7, 0x544920ae,
    0xb206c41c, 0x5d36af05, 0x698a64df, 0x86ba0fc6, 0x00f3f36b, 0xefc39872, 0xdb7f53a8, 0x344f38b1,
    0x97f8fab0, 0x78c891a9, 0x4c745a73, 0xa344316a, 0x250dcdc7, 0xca3da6de, 0xfe816d04, 0x11b1061d,
    0xf7fee2af, 0x18ce89b6, 0x2c72426c, 0xc3422975, 0x450bd5d8, 0xaa3bbec1, 0x9e87751b, 0x71b71e02,
    0x57f4ca8e, 0xb8c4a197, 0x8c786a4d, 0x63480154, 0xe501fdf9, 0x0a3196e0, 0x3e8d5d3a, 0xd1bd3623,
    0x37f2d291, 0xd8c2b988, 0xec7e7252, 0x034e194b, 0x8507e5e6, 0x6a378eff, 0x5e8b4525, 0xb1bb2e3c,
/* k=6 */
    0x00000000, 0x68032cc8, 0xd0065990, 0xb8057558, 0xa5e0c5d1, 0xcde3e919, 0x75e69c41, 0x1de5b089,
    0x4e2dfd53, 0x262ed19b, 0x9e2ba4c3, 0xf628880b, 0xebcd3882, 0x83ce144a, 0x3bcb6112, 0x53c84dda,
    0x9c5bfaa6, 0xf458d66e, 0x4c5da336, 0x245e8ffe, 0x39bb3f77, 0x51b813bf, 0xe9bd66e7, 0x81be4a2f,
    0xd27607f5, 0xba752b3d, 0x02705e65, 0x6a7372ad, 0x7796c224, 0x1f95eeec, 0xa7909bb4, 0xcf93b77c,
    0x3d5b83bd, 0x5558af75, 0xed5dda2d, 0x855ef6e5, 0x98bb466c, 0xf0b86aa4, 0x48bd1ffc, 0x20be3334,
    0x73767eee, 0x1b755226, 0xa370277e, 0xcb730bb6, 0xd696bb3f, 0xbe9597f7, 0x0690e2af, 0x6e93ce67,
    0xa100791b, 0xc90355d3, 0x7106208b, 0x19050c43, 0x04e0bcca, 0x6ce39002, 0xd4e6e55a, 0xbce5c992,
    0xef2d8448, 0x872ea880, 0x3f2bddd8, 0x5728f110, 0x4acd4199, 0x22ce6d51, 0x9acb1809, 0xf2c834c1,
    0x7ab7077a, 0x12b42bb2, 0xaab15eea, 0xc2b27222, 0xdf57c2ab, 0xb754ee63, 0x0f519b3b, 0x6752b7f3,
    0x349afa29, 0x5c99d6e1, 0xe49ca3b9, 0x8c9f8f71, 0x917a3ff8, 0xf9791330, 0x417c6668, 0x297f4aa0,
    0xe6ecfddc, 0x8eefd114, 0x36eaa44c, 0x5ee98884, 0x430c380d, 0x2b0f14c5, 0x930a619d, 0xfb094d55,
    0xa8c1008f, 0xc0c22c47, 0x78c7591f, 0x10c475d7, 0x0d21c55e, 0x6522e996, 0xdd279cce, 0xb524b006,
    0x47ec84c7, 0x2fefa80f, 0x97eadd57, 0xffe9f19f, 0xe20c4116, 0x8a0f6dde, 0x320a1886, 0x5a09344e,
    0x09c17994, 0x61c2555c, 0xd9c72004, 0xb1c40ccc, 0xac21bc45, 0xc422908d, 0x7c27e5d5, 0x1424c91d,
    0xdbb77e61, 0xb3b452a9, 0x0bb127f1, 0x63b20b39, 0x7e57bbb0, 0x16549778, 0xae51e220, 0xc652cee8,
    0x959a8332, 0xfd99affa, 0x459cdaa2, 0x2d9ff66a, 0x307a46e3, 0x58796a2b, 0xe07c1f73, 0x887f33bb,
    0xf56e0ef4, 0x9d6d223c, 0x25685764, 0x4d6b7bac, 0x508ecb25, 0x388de7ed, 0x808892b5, 0xe88bbe7d,
    0xbb43f3a7, 0xd340df6f, 0x6b45aa37, 0x034686ff, 0x1ea33676, 0x76a01abe, 0xcea56fe6, 0xa6a6432e,
    0x6935f452, 0x0136d89a, 0xb933adc2, 0xd130810a, 0xccd53183, 0xa4d61d4b, 0x1cd36813, 0x74d044db,
    0x27180901, 0x4f1b25c9, 0xf71e5091, 0x9f1d7c59, 0x82f8ccd0, 0xeafbe018, 0x52fe9540, 0x3afdb988,
    0xc8358d49, 0xa036a181, 0x1833d4d9, 0x7030f811, 0x6dd54898, 0x05d66450, 0xbdd31108, 0xd5d03dc0,
    0x8618701a, 0xee1b5cd2, 0x561e298a, 0x3e1d0542, 0x23f8b5cb, 0x4bfb9903, 0xf3feec5b, 0x9bfdc093,
    0x546e77ef, 0x3c6d5b27, 0x84682e7f, 0xec6b02b7, 0xf18eb23e, 0x998d9ef6, 0x2188ebae, 0x498bc766,
    0x1a438abc, 0x7240a674, 0xca45d32c, 0xa246ffe4, 0xbfa34f6d, 0xd7a063a5, 0x6fa516fd, 0x07a63a35,
    0x8fd9098e, 0xe7da2546, 0x5fdf501e, 0x37dc7cd6, 0x2a39cc5f, 0x423ae097, 0xfa3f95cf, 0x923cb907,
    0xc1f4f4dd, 0xa9f7d815, 0x11f2ad4d, 0x79f18185, 0x6414310c, 0x0c171dc4, 0xb412689c, 0xdc114454,
    0x1382f328, 0x7b81dfe0, 0xc384aab8, 0xab878670, 0xb66236f9, 0xde611a31, 0x66646f69, 0x0e6743a1,
    0x5daf0e7b, 0x35ac22b3, 0x8da957eb, 0xe5aa7b23, 0xf84fcbaa, 0x904ce762, 0x2849923a, 0x404abef2,
    0xb2828a33, 0xda81a6fb, 0x6284d3a3, 0x0a87ff6b, 0x17624fe2, 0x7f61632a, 0xc7641672, 0xaf673aba,
    0xfcaf7760, 0x94ac5ba8, 0x2ca92ef0, 0x44aa0238, 0x594fb2b1, 0x314c9e79, 0x8949eb21, 0xe14ac7e9,
    0x2ed97095, 0x46da5c5d, 0xfedf2905, 0x96dc05cd, 0x8b39b544, 0xe33a998c, 0x5b3fecd4, 0x333cc01c,
    0x60f48dc6, 0x08f7a10e, 0xb0f2d456, 0xd8f1f89e, 0xc5144817, 0xad1764df, 0x15121187, 0x7d113d4f,
/* k=7 */
    0x00000000, 0x493c7d27, 0x9278fa4e, 0xdb448769, 0x211d826d, 0x6821ff4a, 0xb3657823, 0xfa590504,
    0x423b04da, 0x0b0779fd, 0xd043fe94, 0x997f83b3, 0x632686b7, 0x2a1afb90, 0xf15e7cf9, 0xb86201de,
    0x847609b4, 0xcd4a7493, 0x160ef3fa, 0x5f328edd, 0xa56b8bd9, 0xec57f6fe, 0x37137197, 0x7e2f0cb0,
    0xc64d0d6e, 0x8f717049, 0x5435f720, 0x1d098a07, 0xe7508f03, 0xae6cf224, 0x7528754d, 0x3c14086a,
    0x0d006599, 0x443c18be, 0x9f789fd7, 0xd644e2f0, 0x2c1de7f4, 0x65219ad3, 0xbe651dba, 0xf759609d,
    0x4f3b6143, 0x06071c64, 0xdd439b0d, 0x947fe62a, 0x6e26e32e, 0x271a9e09, 0xfc5e1960, 0xb5626447,
    0x89766c2d, 0xc04a110a, 0x1b0e9663, 0x5232eb44, 0xa86bee40, 0xe1579367, 0x3a13140e, 0x732f6929,
    0xcb4d68f7, 0x827115d0, 0x593592b9, 0x1009ef9e, 0xea50ea9a, 0xa36c97bd, 0x782810d4, 0x31146df3,
    0x1a00cb32, 0x533cb615, 0x8878317c, 0xc1444c5b, 0x3b1d495f, 0x72213478, 0xa965b311, 0xe059ce36,
    0x583bcfe8, 0x1107b2cf, 0xca4335a6, 0x837f4881, 0x79264d85, 0x301a30a2, 0xeb5eb7cb, 0xa262caec,
    0x9e76c286, 0xd74abfa1, 0x0c0e38c8, 0x453245ef, 0xbf6b40eb, 0xf6573dcc, 0x2d13baa5, 0x642fc782,
    0xdc4dc65c, 0x9571bb7b, 0x4e353c12, 0x07094135, 0xfd504431, 0xb46c3916, 0x6f28be7f, 0x2614c358,
    0x1700aeab, 0x5e3cd38c, 0x857854e5, 0xcc4429c2, 0x361d2cc6, 0x7f2151e1, 0xa465d688, 0xed59abaf,
    0x553baa71, 0x1c07d756, 0xc743503f, 0x8e7f2d18, 0x7426281c, 0x3d1a553b, 0xe65ed252, 0xaf62af75,
    0x9376a71f, 0xda4ada38, 0x010e5d51, 0x48322076, 0xb26b2572, 0xfb575855, 0x2013df3c, 0x692fa21b,
    0xd14da3c5, 0x9871dee2, 0x4335598b, 0x0a0924ac, 0xf05021a8, 0xb96c5c8f, 0x6228dbe6, 0x2b14a6c1,
    0x34019664, 0x7d3deb43, 0xa6796c2a, 0xef45110d, 0x151c1409, 0x5c20692e, 0x8764ee47, 0xce589360,
    0x763a92be, 0x3f06ef99, 0xe44268f0, 0xad7e15d7, 0x572710d3, 0x1e1b6df4, 0xc55fea9d, 0x8c6397ba,
    0xb0779fd0, 0xf94be2f7, 0x220f659e, 0x6b3318b9, 0x916a1dbd, 0xd856609a, 0x0312e7f3, 0x4a2e9ad4,
    0xf24c9b0a, 0xbb70e62d, 0x60346144, 0x29081c63, 0xd3511967, 0x9a6d6440, 0x4129e329, 0x08159e0e,
    0x3901f3fd, 0x703d8eda, 0xab7909b3, 0xe2457494, 0x181c7190, 0x51200cb7, 0x8a648bde, 0xc358f6f9,
    0x7b3af727, 0x32068a00, 0xe9420d69, 0xa07e704e, 0x5a27754a, 0x131b086d, 0xc85f8f04, 0x8163f223,
    0xbd77fa49, 0xf44b876e, 0x2f0f0007, 0x66337d20, 0x9c6a7824, 0xd5560503, 0x0e12826a, 0x472eff4d,
    0xff4cfe93, 0xb67083b4, 0x6d3404dd, 0x240879fa, 0xde517cfe, 0x976d01d9, 0x4c2986b0, 0x0515fb97,
    0x2e015d56, 0x673d2071, 0xbc79a718, 0xf545da3f, 0x0f1cdf3b, 0x4620a21c, 0x9d642575, 0xd4585852,
    0x6c3a598c, 0x250624ab, 0xfe42a3c2, 0xb77edee5, 0x4d27dbe1, 0x041ba6c6, 0xdf5f21af, 0x96635c88,
    0xaa7754e2, 0xe34b29c5, 0x380faeac, 0x7133d38b, 0x8b6ad68f, 0xc256aba8, 0x19122cc1, 0x502e51e6,
    0xe84c5038, 0xa1702d1f, 0x7a34aa76, 0x3308d751, 0xc951d255, 0x806daf72, 0x5b29281b, 0x1215553c,
    0x230138cf, 0x6a3d45e8, 0xb179c281, 0xf845bfa6, 0x021cbaa2, 0x4b20c785, 0x906440ec, 0xd9583dcb,
    0x613a3c15, 0x28064132, 0xf342c65b, 0xba7ebb7c, 0x4027be78, 0x091bc35f, 0xd25f4436, 0x9b633911,
    0xa777317b, 0xee4b4c5c, 0x350fcb35, 0x7c33b612, 0x866ab316, 0xcf56ce31, 0x14124958, 0x5d2e347f,
    0xe54c35a1, 0xac704886, 0x7734cfef, 0x3e08b2c8, 0xc451b7cc, 0x8d6dcaeb, 0x56294d82, 0x1f1530a5
};

/* Starting with the initial value in crc, accumulates a CRC32 value for unsigned
 * 8-bit integer v. */
__E2K_INLINE __E2K_WARNING (unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_crc32qi (unsigned int crc, unsigned char v))
{
#if __iset__ >= 6
    __di dst = __builtin_e2k_clmull (crc ^ v, 0xf1);
    dst = __builtin_e2k_clmull (dst & 0xff, 0x105ec76f1LL);
    return (dst ^ crc) >> 8;
#else /* __iset__ >= 6 */
    return __crc32c_tab[0][(crc ^ v) & 0xff] ^ (crc >> 8);
#endif /* __iset__ >= 6 */
}

/* Starting with the initial value in crc, accumulates a CRC32 value for unsigned
 * 16-bit integer v. */
__E2K_INLINE __E2K_WARNING (unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_crc32hi (unsigned int crc, unsigned short v))
{
    crc ^= v;
#if __iset__ >= 6
    __di dst = __builtin_e2k_clmull (crc, 0x13f1);
    dst = __builtin_e2k_clmull (dst & 0xffff, 0x105ec76f1LL);
    return (dst ^ crc) >> 16;
#else /* __iset__ >= 6 */
    crc = __crc32c_tab[1][crc & 0xff] ^
          __crc32c_tab[0][(crc >> 8) & 0xff] ^ (crc >> 16);
    return crc;
#endif /* __iset__ >= 6 */
}

/* Starting with the initial value in crc, accumulates a CRC32 value for unsigned
 * 32-bit integer v. */
__E2K_INLINE __E2K_WARNING (unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_crc32si (unsigned int crc, unsigned int v))
{
    crc ^= v;
#if __iset__ >= 6
    __di dst = __builtin_e2k_clmull (crc, 0xdea713f100000000LL);
    dst = __builtin_e2k_clmulh (dst, 0x105ec76f1LL);
    return dst;
#else /* __iset__ >= 6 */
    crc = __crc32c_tab[3][crc & 0xff]
        ^ __crc32c_tab[2][(crc >> 8) & 0xff]
        ^ __crc32c_tab[1][(crc >> 16) & 0xff]
        ^ __crc32c_tab[0][crc >> 24];
    return crc;
#endif /* __iset__ >= 6 */
}

/* Starting with the initial value in crc, accumulates a CRC32 value for unsigned
 * 64-bit integer v. */
__E2K_INLINE __E2K_WARNING (__di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_crc32di (__di crc, __di v))
{
    crc ^= v;
#if __iset__ >= 6
    __di dst = __builtin_e2k_clmull (crc, 0xdea713f100000000LL);
    dst = __builtin_e2k_clmull (dst >> 32, 0x105ec76f1LL);
    dst = __builtin_e2k_clmull ((dst ^ v) >> 32, 0xdea713f100000000LL);
    dst = __builtin_e2k_clmulh (dst, 0x105ec76f1LL);
    return dst;
/*
 *  т.е. CRC64 можно вычислять как-то так через два параллельных CRC32:
 *  CRC64 = CLMUL(0xa66805eb, CRC32(CRCIN,L)) XOR CRC32(0,H)
 *  __di dstl = __builtin_e2k_clmull (crc & 0xffffffff, 0xdea713f100000000LL);
 *    dstl = __builtin_e2k_clmulh (dstl, 0x105ec76f1LL);
 *    dstl = __builtin_e2k_clmulh (dstl, 0xa66805eb00000000LL);
 *    __di dsth = __builtin_e2k_clmull (crc >> 32, 0xdea713f100000000LL);
 *    dsth = __builtin_e2k_clmulh (dsth, 0x105ec76f1LL);
 *    return dstl ^ dsth;
 */
#else /* __iset__ >= 6 */
    crc = __crc32c_tab[7][crc & 0xff]
        ^ __crc32c_tab[6][(crc >> 8) & 0xff]
        ^ __crc32c_tab[5][(crc >> 16) & 0xff]
        ^ __crc32c_tab[4][(crc >> 24) & 0xff]
        ^ __crc32c_tab[3][(  v >> 32) & 0xff]
        ^ __crc32c_tab[2][(  v >> 40) & 0xff]
        ^ __crc32c_tab[1][(  v >> 48) & 0xff]
        ^ __crc32c_tab[0][   v >> 56];
    return crc;
#endif /* __iset__ >= 6 */
}

#undef __CALC_LEN
#undef __GEN_MASK
#undef __CMP_EQUAL_ANY
#undef __CMP_RANGES
#undef __CMP_EQUAL_EACH
#undef __CMP_EQUAL_ORDERED
#undef __QPCMPEQH
#undef __PCMP_STR
#undef __WORDMASK_TO_BITMASK
#undef __MASK_TO_INDEX
#undef __ABS_AND_SATURATE_LEN

#endif /* __SSE4_2__ */

#undef __BITREV_8U
#undef __BITREV_32U
#undef __BITREV_64U

#ifdef __3dNOW__

/*******************************************************************************/
/****************************** 3DNOW builtins *********************************/
/*******************************************************************************/

/* *****************************************************************************
 *                         Инициализация режима (MMX/FP)
 * *****************************************************************************/

#define __builtin_ia32_femms()

/* среднее 8-ми беззнаковых байт (8U) */
TWO_OPERANDS_BUILTINS (pavgusb, pavgusb, __v8qi, __v8qi)

/* преобразование 2-х флотов (32F) в 2 инта (32S) c обрубанием, c сатурацией */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pf2id (__v2sf src)
{
    return (__v2si) (__builtin_e2k_pfstoistr ((__di) src) ^
                     __builtin_e2k_pfcmples (0x4f0000004f000000LL, (__di) src));
}

/* горизонтальное сложение флотов (32F) */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pfacc (__v2sf src1, __v2sf src2)
{
    __di dst;
#if __iset__ <= 2
    __di tmp = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 0xd);
    dst = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 8);
    dst = __builtin_e2k_pfadds (dst, tmp);
#else /* __iset__ <= 2 */
    dst = __builtin_e2k_pfhadds ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
    return (__v2sf) dst;
}

/* сложение 2-х флотов (32F) */
TWO_OPERANDS_BUILTINS (pfadd, pfadds, __v2sf, __v2sf)

/* сравнение на равно 2-х флотов (32F) c формированием битовой маски */
TWO_OPERANDS_BUILTINS (pfcmpeq, pfcmpeqs, __v2sf, __v2si)

/* сравнение на больше или равно 2-х флотов (32F) c формированием битовой маски */
TWO_OPERANDS_BUILTINS_REVERSE (pfcmpge, pfcmples, __v2sf, __v2si)

/* сравнение на больше 2-х флотов (32F) c формированием битовой маски */
TWO_OPERANDS_BUILTINS_REVERSE (pfcmpgt, pfcmplts, __v2sf, __v2si)

/* максимум 2-х флотов (32F) */
TWO_OPERANDS_BUILTINS (pfmax, pfmaxs, __v2sf, __v2sf)

/* минимум 2-х флотов (32F) */
TWO_OPERANDS_BUILTINS (pfmin, pfmins, __v2sf, __v2sf)

/* умножение 2-х флотов (32F) */
TWO_OPERANDS_BUILTINS (pfmul, pfmuls, __v2sf, __v2sf)

/* начальное приближение обратной величины флота (32F) в младшей половине
 * с раздвоением результата в обе половины */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pfrcp (__v2sf src)
{
    unsigned int dst;
#pragma asm_inline
    asm ("frcps %[src_name], %[dst_name]"
        : [dst_name] "=r" (dst) : [src_name] "ri" ((unsigned int) (__di) src));
    return (__v2sf) (dst | ((__di) dst << 32));
}

/* Первая часть итерации Ньютона-Рапсона для обратной величины 2-х флотов (32F) : dst = 2 - src1 * src2 */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pfrcpit1 (__v2sf src1, __v2sf src2)
{
    return (__v2sf) __builtin_e2k_pfsubs (0x4000000040000000LL, __builtin_e2k_pfmuls ((__di) src1, (__di) src2));
}

/* Вторая часть итерации Ньютона-Рапсона для обратной величины 2-х флотов (32F) : dst = src1 * src2 */
TWO_OPERANDS_BUILTINS (pfrcpit2, pfmuls, __v2sf, __v2sf)

/* начальное приближение обратной величины квадратного корня от флота (32F)
 * в младшей половине с раздвоением результата в обе половины */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pfrsqrt (__v2sf src)
{
    unsigned int dst;
#pragma asm_inline
    asm ("frsqrts %[src_name], %[dst_name]"
        : [dst_name] "=r" (dst) : [src_name] "ri" (((unsigned int) (__di) src) & ~0x80000000));
    dst |= ((unsigned int) (__di) src) & 0x80000000;
    return (__v2sf) (dst | ((__di) dst << 32));
}

/* Первая часть итерации Ньютона для обратной величины квадратного корня
 * 2-х флотов (32F) : dst = 1.5 - 0.5 * src1 * src2 */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pfrsqit1 (__v2sf src1, __v2sf src2)
{
    return (__v2sf) __builtin_e2k_pfsubs (0x3fc000003fc00000LL, __builtin_e2k_pfmuls (
                    __builtin_e2k_pfmuls (0x3f0000003f000000LL, (__di) src1 & 0x7fffffff7fffffffLL), (__di) src2));
}

/* вычитание 2-х флотов (32F) */
TWO_OPERANDS_BUILTINS (pfsub, pfsubs, __v2sf, __v2sf)

/* обратное вычитание 2-х флотов (32F) */
TWO_OPERANDS_BUILTINS_REVERSE (pfsubr, pfsubs, __v2sf, __v2sf)

/* преобразование 2-х интов (32S) в 2 флота (32F) c обрубанием */
__E2K_INLINE __E2K_WARNING (__v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pi2fd (__v2si src))
{
    __di dst;
    int pfpfr;
    __GETPFPFR (pfpfr);
    __SETPFPFR (pfpfr | 0x6000); /* rc = 3 - округление к нулю или отбрасывание */
    dst = __builtin_e2k_pistofs ((__di) src);
    __SETPFPFR (pfpfr);
    return (__v2sf) dst;
}

/* умножение 4-х знаковых шортов (16S) c масштабированием (>> 16) и округлением */
__E2K_INLINE __v4hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmulhrw (__v4hi src1, __v4hi src2)
{
    __di tmp1_hi = __builtin_e2k_pmulhh ((__di) src1, (__di) src2);
    __di tmp1_lo = __builtin_e2k_pmullh ((__di) src1, (__di) src2);
    tmp1_lo = __builtin_e2k_psrah (tmp1_lo, 15);
    return (__v4hi) __builtin_e2k_psubh (tmp1_hi, tmp1_lo);
}

#endif /* __3dNOW__ */

#ifdef __3dNOW_A__

/*******************************************************************************/
/**************************** 3DNOW_A builtins *********************************/
/*******************************************************************************/

/* преобразование 2-х флотов (32F) в 2 шорта (16S) c обрубанием, с расширением знака до инта (32S) */
__E2K_INLINE __v2si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pf2iw (__v2sf src)
{
    __di max_16S = 0x46fffe0046fffe00LL;     /* раздвоенный (float) 32767 */
    __di min_16S = 0xc7000000c7000000LL;     /* раздвоенный (float) -32768 */
    return (__v2si) __builtin_e2k_pfstoistr (__builtin_e2k_pfmaxs (min_16S,
                                             __builtin_e2k_pfmins ((__di) src, max_16S)));
}

/* горизонтальное вычитание флотов (32F) */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pfnacc (__v2sf src1, __v2sf src2)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 8);
    __di tmp = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 0xd);
    dst = __builtin_e2k_pfsubs (dst, tmp);
#else /* __iset__ <= 2 */
    __di dst = __builtin_e2k_pfhsubs ((__di) src1, (__di) src2);
#endif /* __iset__ <= 2 */
    return (__v2sf) dst;
}

/* горизонтальное вычитание флотов (32F) первого аргумента и сложение
 * флотов второго аргумента */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pfpnacc (__v2sf src1, __v2sf src2)
{
#if __iset__ <= 2
    __di dst = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 8);
    __di tmp = __builtin_e2k_pshufw ((__di) src2, (__di) src1, 0xd);
    tmp ^= 0x80000000LL;
    dst = __builtin_e2k_pfadds (dst, tmp);
#else /* __iset__ <= 2 */
    __di dst = (__di) src1 ^ 0x8000000000000000LL;
    dst = __builtin_e2k_pfhadds (dst, (__di) src2);
#endif /* __iset__ <= 2 */
    return (__v2sf) dst;
}

/* преобразование 2-х интов (32S) в 2 флота (32F) c обрубанием */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pi2fw (__v2si src)
{
    __di dst = (__di) src << 16;
    dst = __builtin_e2k_psraw (dst, 16);
    dst = __builtin_e2k_pistofs (dst);
    return (__v2sf) dst;
}

/* перестановка местами 2-х флотов (32S) */
__E2K_INLINE __v2sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pswapdsf (__v2sf src)
{
    return (__v2sf) __builtin_e2k_scrd ((__di) src, 32);
}

#endif /* __3dNOW_A__ */

#ifdef __SSE4A__

/*******************************************************************************/
/****************************** SSE4A builtins *********************************/
/*******************************************************************************/

/* *****************************************************************************
 *                                Записи
 * *****************************************************************************/

/* Stores the lower 64 bits of a src to the address p using the non-temporal hint */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntsd (double *p, __v2df src)
{
    type_union_128 s;
    s.__v2df = src;
    __builtin_e2k_st_64s_nt (s.l.l0, p);
}

/* Stores the lower 32 bits of a src to the address p using the non-temporal hint */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntss (float *p, __v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    __builtin_e2k_st_32u_nt (s.l.l0, p);
}

/* *****************************************************************************
 *                        Выделение/вставление битового поля
 * *****************************************************************************/

/* выделение битового поля из младшего лонга (64U) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_extrq (__v2di src, __v16qi field)
{
    type_union_128 s, f;
    s.__v2di = src;
    f.__v16qi = field;
    int size = f.l.l0 & 0x3f;
    int shift = (f.l.l0 >> 8) & 0x3f;
    s.l.l0 = (s.l.l0 >> shift) & (((__di) -1LL) >> (64 - size));
    s.l.l1 = 0;
    return s.__v2di;
}

/* выделение битового поля из младшего лонга (64U) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_extrqi (__v2di src, const unsigned int size, const unsigned int shift)
{
    type_union_128 s;
    s.__v2di = src;
    s.l.l0 = s.l.l0 >> (shift & 0x3f) & (((__di) -1LL) >> (64 - (size & 0x3f)));
    s.l.l1 = 0;
    return s.__v2di;
}

/* вставление битового поля в младший лонг (64U) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_insertq (__v2di dst, __v2di src_field)
{
    type_union_128 sf, d;
    d.__v2di = dst;
    sf.__v2di = src_field;
    int size = sf.l.l1 & 0x3f;
    int shift = (sf.l.l1 >> 8) & 0x3f;
    __di mask = (size != 0 && (shift + size) < 64) ? (1LL << size) - 1 : -1LL;
    mask <<= shift;
    d.l.l0 = ((sf.l.l0 << shift) & mask) | (d.l.l0 & ~mask);
    d.l.l1 = 0;
    return d.__v2di;
}

/* вставление битового поля в младший лонг (64U) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_insertqi (__v2di dst, __v2di src, const unsigned int size, const unsigned int shift)
{
    type_union_128 s, d;
    d.__v2di = dst;
    s.__v2di = src;
    int ssize = size & 0x3f;
    int sshift = shift & 0x3f;
    if (ssize != 0 && (sshift + ssize) < 64) {
        __di tmp = __builtin_e2k_insfd (d.l.l0, sshift | (ssize << 6), s.l.l0);
        d.l.l0 = __builtin_e2k_scld (tmp, sshift);
    }
    else {
        d.l.l0 = (s.l.l0 << sshift) | (d.l.l0 & ~(-1LL << sshift));
    }
    d.l.l1 = 0;
    return d.__v2di;
}

#endif /* __SSE4A__ */

#ifdef __AVX__

/*******************************************************************************/
/****************************** AVX builtins ***********************************/
/*******************************************************************************/

#define PACKED_TWO_OPERAND_AVX_BUILTINS_WITH_SCALAR_OPS(name,instr,src_type, dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src1, src_type src2)                   \
{                                                                      \
    type_union_256 s1, s2, dst;                                        \
    __di tmp0, tmp1, tmp2, tmp3;                                       \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp0)                                        \
       : [src1_name] "rI" (s1.l.l0),[src2_name] "ri" (s2.l.l0));       \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp1)                                        \
       : [src1_name] "rI" (s1.l.l1),[src2_name] "ri" (s2.l.l1));       \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp2)                                        \
       : [src1_name] "rI" (s1.l.l2),[src2_name] "ri" (s2.l.l2));       \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp3)                                        \
       : [src1_name] "rI" (s1.l.l3),[src2_name] "ri" (s2.l.l3));       \
    dst.l.l0 = tmp0;                                                   \
    dst.l.l1 = tmp1;                                                   \
    dst.l.l2 = tmp2;                                                   \
    dst.l.l3 = tmp3;                                                   \
    return dst.dst_type;                                               \
}

#if __iset__ <= 4

#define PACKED_TWO_OPERAND_AVX_BUILTINS  PACKED_TWO_OPERAND_AVX_BUILTINS_WITH_SCALAR_OPS

#define PACKED_TWO_OPERAND_AVX_BUILTINS_REVERSE(name,instr,src_type,dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src2, src_type src1)                   \
{                                                                      \
    type_union_256 s1, s2, dst;                                        \
    __di tmp0, tmp1, tmp2, tmp3;                                       \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp0)                                        \
       : [src1_name] "rI" (s1.l.l0),[src2_name] "ri" (s2.l.l0));       \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp1)                                        \
       : [src1_name] "rI" (s1.l.l1),[src2_name] "ri" (s2.l.l1));       \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp2)                                        \
       : [src1_name] "rI" (s1.l.l2),[src2_name] "ri" (s2.l.l2));       \
_Pragma ("asm_inline")                                                 \
    asm (""#instr" %[src1_name], %[src2_name], %[dst_name]"            \
       : [dst_name] "=r" (tmp3)                                        \
       : [src1_name] "rI" (s1.l.l3),[src2_name] "ri" (s2.l.l3));       \
    dst.l.l0 = tmp0;                                                   \
    dst.l.l1 = tmp1;                                                   \
    dst.l.l2 = tmp2;                                                   \
    dst.l.l3 = tmp3;                                                   \
    return dst.dst_type;                                               \
}

#else /* __iset__ <= 4 */

#define PACKED_TWO_OPERAND_AVX_BUILTINS(name,instr,src_type, dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src1, src_type src2)                   \
{                                                                      \
    type_union_256 s1, s2, dst;                                        \
    __v2di tmp0, tmp1;                                                 \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"           \
       : [dst_name] "=r" (tmp0)                                        \
       : [src1_name] "r" (s1.u##src_type.v0),[src2_name] "ri" (s2.u##src_type.v0));\
_Pragma ("asm_inline")                                                 \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"           \
       : [dst_name] "=r" (tmp1)                                        \
       : [src1_name] "r" (s1.u##src_type.v1),[src2_name] "ri" (s2.u##src_type.v1));\
    dst.u__v4di.v0 = tmp0;                                             \
    dst.u__v4di.v1 = tmp1;                                             \
    return dst.dst_type;                                               \
}

#define PACKED_TWO_OPERAND_AVX_BUILTINS_REVERSE(name,instr,src_type,dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                            \
__builtin_ia32_##name (src_type src2, src_type src1)                   \
{                                                                      \
    type_union_256 s1, s2, dst;                                        \
    __v2di tmp0, tmp1;                                                 \
    s1.src_type = src1;                                                \
    s2.src_type = src2;                                                \
_Pragma ("asm_inline")                                                 \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"           \
       : [dst_name] "=r" (tmp0)                                        \
       : [src1_name] "r" (s1.u##src_type.v0),[src2_name] "ri" (s2.u##src_type.v0));\
_Pragma ("asm_inline")                                                 \
    asm ("q"#instr" %[src1_name], %[src2_name], %[dst_name]"           \
       : [dst_name] "=r" (tmp1)                                        \
       : [src1_name] "r" (s1.u##src_type.v1),[src2_name] "ri" (s2.u##src_type.v1));\
    dst.u__v4di.v0 = tmp0;                                             \
    dst.u__v4di.v1 = tmp1;                                             \
    return dst.dst_type;                                               \
}

#endif /* __iset__ <= 4 */

#define TWO_OPERAND_AVX_BUILTINS_VIA_2SSE(name_avx,name_sse,src_type,dst_type)            \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                               \
__builtin_ia32_##name_avx (src_type src1, src_type src2)                                  \
{                                                                                         \
    type_union_256 s1, s2, dst;                                                           \
    s1.src_type = src1;                                                                   \
    s2.src_type = src2;                                                                   \
    dst.u##dst_type.v0 = __builtin_ia32_##name_sse (s1.u##src_type.v0, s2.u##src_type.v0);\
    dst.u##dst_type.v1 = __builtin_ia32_##name_sse (s1.u##src_type.v1, s2.u##src_type.v1);\
    return dst.dst_type;                                                                  \
}

#define ONE_OPERAND_AVX_BUILTINS_VIA_2SSE(name_avx,name_sse,src_type,dst_type) \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                    \
__builtin_ia32_##name_avx (src_type src)                                       \
{                                                                              \
    type_union_256 s, dst;                                                     \
    s.src_type = src;                                                          \
    dst.u##dst_type.v0 = __builtin_ia32_##name_sse (s.u##src_type.v0);         \
    dst.u##dst_type.v1 = __builtin_ia32_##name_sse (s.u##src_type.v1);         \
    return dst.dst_type;                                                       \
}

/* *****************************************************************************
 *                         Обнуление регистров
 * *****************************************************************************/

/* обнуление всех YMM регистров */
#define __builtin_ia32_vzeroall()

/* обнуление старших 128 бит всех YMM регистров */
#define __builtin_ia32_vzeroupper()

/* *****************************************************************************
 *                          Плавающие операции
 * *****************************************************************************/

/* сложение 4-х даблов (64F) */
PACKED_TWO_OPERAND_AVX_BUILTINS (addpd256, pfaddd, __v4df, __v4df)

/* сложение 8-ми флотов (32F) */
PACKED_TWO_OPERAND_AVX_BUILTINS (addps256, pfadds, __v8sf, __v8sf)

/* вычитание 4-х даблов (64F) */
PACKED_TWO_OPERAND_AVX_BUILTINS (subpd256, pfsubd, __v4df, __v4df)

/* вычитание 8-ми флотов (32F) */
PACKED_TWO_OPERAND_AVX_BUILTINS (subps256, pfsubs, __v8sf, __v8sf)

/* умножение 4-х даблов (64F) */
PACKED_TWO_OPERAND_AVX_BUILTINS (mulpd256, pfmuld, __v4df, __v4df)

/* умножение 8-ми флотов (32F) */
PACKED_TWO_OPERAND_AVX_BUILTINS (mulps256, pfmuls, __v8sf, __v8sf)

/* деление 4-х даблов (64F) */
PACKED_TWO_OPERAND_AVX_BUILTINS_WITH_SCALAR_OPS (divpd256, pfdivd, __v4df, __v4df)

/* деление 8-ми флотов (32F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (divps256, divps, __v8sf, __v8sf)

/* сложение нечетных и вычитание четных даблов (64F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (addsubpd256, addsubpd, __v4df, __v4df)

/* сложение нечетных и вычитание четных флотов (32F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (addsubps256, addsubps, __v8sf, __v8sf)

/* горизонтальное сложение 4-х даблов (64F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (haddpd256, haddpd, __v4df, __v4df)

/* горизонтальное сложение 8-ми флотов (32F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (haddps256, haddps, __v8sf, __v8sf)

/* горизонтальное вычитание 4-х даблов (64F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (hsubpd256, hsubpd, __v4df, __v4df)

/* горизонтальное вычитание 8-ми флотов (32F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (hsubps256, hsubps, __v8sf, __v8sf)

/* максимум 4-х даблов (64F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (maxpd256, maxpd, __v4df, __v4df)

/* максимум 8-ми флотов (32F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (maxps256, maxps, __v8sf, __v8sf)

/* минимум 4-х даблов (64F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (minpd256, minpd, __v4df, __v4df)

/* минимум 8-ми флотов (32F) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (minps256, minps, __v8sf, __v8sf)

/* приближение к обратной величине 8-ми флотов (32F) */
ONE_OPERAND_AVX_BUILTINS_VIA_2SSE (rcpps256, rcpps, __v8sf, __v8sf)

/* приближение обратной величины квадратного корня 8-ми флотов (32F) */
ONE_OPERAND_AVX_BUILTINS_VIA_2SSE (rsqrtps256, rsqrtps, __v8sf, __v8sf)

/* квадратный корень из 4-х даблов (64F) */
ONE_OPERAND_AVX_BUILTINS_VIA_2SSE (sqrtpd256, sqrtpd, __v4df, __v4df)

/* квадратный корень из 8-ми флотов (32F) */
ONE_OPERAND_AVX_BUILTINS_VIA_2SSE (sqrtps256, sqrtps, __v8sf, __v8sf)

/* *****************************************************************************
 *                            Округление
 * *****************************************************************************/

/* округление 4-х даблов (64F) используя режим округления из второго аргумента */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_roundpd256 (__v4df src, const int rc)
{
    type_union_256 s, dst;
    s.__v4df = src;
    dst.u__v4df.v0 = __builtin_ia32_roundpd (s.u__v4df.v0, rc);
    dst.u__v4df.v1 = __builtin_ia32_roundpd (s.u__v4df.v1, rc);
    return dst.__v4df;
}

/* округление 8-ми флотов (32F) используя режим округления из второго аргумента */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_roundps256 (__v8sf src, const int rc)
{
    type_union_256 s, dst;
    s.__v8sf = src;
    dst.u__v8sf.v0 = __builtin_ia32_roundps (s.u__v8sf.v0, rc);
    dst.u__v8sf.v1 = __builtin_ia32_roundps (s.u__v8sf.v1, rc);
    return dst.__v8sf;
}

/* *****************************************************************************
 *                            Скалярное произведение
 * *****************************************************************************/

/* скалярное произведение 8-ми флотов (32F) по битовой маске */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_dpps256 (__v8sf src1, __v8sf src2, const int mask)
{
    type_union_256 s1, s2, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
    dst.u__v8sf.v0 = __builtin_ia32_dpps (s1.u__v8sf.v0, s2.u__v8sf.v0, mask);
    dst.u__v8sf.v1 = __builtin_ia32_dpps (s1.u__v8sf.v1, s2.u__v8sf.v1, mask);
    return dst.__v8sf;
}

/* *****************************************************************************
 *                          Логические операции
 * *****************************************************************************/

/* AND 4-х даблов (64F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS (andpd256, pandd, __v4df, __v4df)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS (andpd256, pand, __v4df, __v4df)
#endif /* __iset__ <= 4 */

/* AND 8-ми флотов (32F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS (andps256, pandd, __v8sf, __v8sf)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS (andps256, pand, __v8sf, __v8sf)
#endif /* __iset__ <= 4 */

/* ANDNOT 4-х даблов (64F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS_REVERSE (andnpd256, pandnd, __v4df, __v4df)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS_REVERSE (andnpd256, pandn, __v4df, __v4df)
#endif /* __iset__ <= 4 */

/* ANDNOT 8-ми флотов (32F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS_REVERSE (andnps256, pandnd, __v8sf, __v8sf)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS_REVERSE (andnps256, pandn, __v8sf, __v8sf)
#endif /* __iset__ <= 4 */

/* OR 4-х даблов (64F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS (orpd256, pord, __v4df, __v4df)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS (orpd256, por, __v4df, __v4df)
#endif /* __iset__ <= 4 */

/* OR 8-ми флотов (32F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS (orps256, pord, __v8sf, __v8sf)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS (orps256, por, __v8sf, __v8sf)
#endif /* __iset__ <= 4 */

/* XOR 4-х даблов (64F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS (xorpd256, pxord, __v4df, __v4df)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS (xorpd256, pxor, __v4df, __v4df)
#endif /* __iset__ <= 4 */

/* XOR 8-ми флотов (32F) */
#if __iset__ <= 4
PACKED_TWO_OPERAND_AVX_BUILTINS (xorps256, pxord, __v8sf, __v8sf)
#else /* __iset__ <= 4 */
PACKED_TWO_OPERAND_AVX_BUILTINS (xorps256, pxor, __v8sf, __v8sf)
#endif /* __iset__ <= 4 */

/* *****************************************************************************
 *                          Плавающие операции сравнения
 * *****************************************************************************/

#define CMP1(type, op, s1, s2, dst) {                       \
    dst.l.l0 = __builtin_e2k_##op##type (s1.l.l0, s2.l.l0); \
}

#define CMP1EQ_UOD(type, s1, s2, dst) {                          \
    dst.l.l0 = __builtin_e2k_pfcmpeq##type (s1.l.l0, s2.l.l0) |  \
               __builtin_e2k_pfcmpuod##type (s1.l.l0, s2.l.l0);  \
}

#define CMP1NEQ_OD(type, s1, s2, dst) {                          \
    dst.l.l0 = __builtin_e2k_pfcmpneq##type (s1.l.l0, s2.l.l0) ^ \
               __builtin_e2k_pfcmpuod##type (s1.l.l0, s2.l.l0);  \
}

#define FILL1(dst, val) dst.l.l0 = val

#if __iset__ <= 4

#define CMP2(type, op, s1, s2, dst) {                       \
    dst.l.l0 = __builtin_e2k_##op##type (s1.l.l0, s2.l.l0); \
    dst.l.l1 = __builtin_e2k_##op##type (s1.l.l1, s2.l.l1); \
}

#define CMP2EQ_UOD(type, s1, s2, dst) {                          \
    dst.l.l0 = __builtin_e2k_pfcmpeq##type (s1.l.l0, s2.l.l0) |  \
               __builtin_e2k_pfcmpuod##type (s1.l.l0, s2.l.l0);  \
    dst.l.l1 = __builtin_e2k_pfcmpeq##type (s1.l.l1, s2.l.l1) |  \
               __builtin_e2k_pfcmpuod##type (s1.l.l1, s2.l.l1);  \
}

#define CMP2NEQ_OD(type, s1, s2, dst) {                          \
    dst.l.l0 = __builtin_e2k_pfcmpneq##type (s1.l.l0, s2.l.l0) ^ \
               __builtin_e2k_pfcmpuod##type (s1.l.l0, s2.l.l0);  \
    dst.l.l1 = __builtin_e2k_pfcmpneq##type (s1.l.l1, s2.l.l1) ^ \
               __builtin_e2k_pfcmpuod##type (s1.l.l1, s2.l.l1);  \
}

#define FILL2(dst, val) dst.l.l0 = dst.l.l1 = val

#define CMP4(type, op, s1, s2, dst) {                       \
    dst.l.l0 = __builtin_e2k_##op##type (s1.l.l0, s2.l.l0); \
    dst.l.l1 = __builtin_e2k_##op##type (s1.l.l1, s2.l.l1); \
    dst.l.l2 = __builtin_e2k_##op##type (s1.l.l2, s2.l.l2); \
    dst.l.l3 = __builtin_e2k_##op##type (s1.l.l3, s2.l.l3); \
}

#define CMP4EQ_UOD(type, s1, s2, dst) {                          \
    dst.l.l0 = __builtin_e2k_pfcmpeq##type (s1.l.l0, s2.l.l0) |  \
               __builtin_e2k_pfcmpuod##type (s1.l.l0, s2.l.l0);  \
    dst.l.l1 = __builtin_e2k_pfcmpeq##type (s1.l.l1, s2.l.l1) |  \
               __builtin_e2k_pfcmpuod##type (s1.l.l1, s2.l.l1);  \
    dst.l.l2 = __builtin_e2k_pfcmpeq##type (s1.l.l2, s2.l.l2) |  \
               __builtin_e2k_pfcmpuod##type (s1.l.l2, s2.l.l2);  \
    dst.l.l3 = __builtin_e2k_pfcmpeq##type (s1.l.l3, s2.l.l3) |  \
               __builtin_e2k_pfcmpuod##type (s1.l.l3, s2.l.l3);  \
}

#define CMP4NEQ_OD(type, s1, s2, dst) {                          \
    dst.l.l0 = __builtin_e2k_pfcmpneq##type (s1.l.l0, s2.l.l0) ^ \
               __builtin_e2k_pfcmpuod##type (s1.l.l0, s2.l.l0);  \
    dst.l.l1 = __builtin_e2k_pfcmpneq##type (s1.l.l1, s2.l.l1) ^ \
               __builtin_e2k_pfcmpuod##type (s1.l.l1, s2.l.l1);  \
    dst.l.l2 = __builtin_e2k_pfcmpneq##type (s1.l.l2, s2.l.l2) ^ \
               __builtin_e2k_pfcmpuod##type (s1.l.l2, s2.l.l2);  \
    dst.l.l3 = __builtin_e2k_pfcmpneq##type (s1.l.l3, s2.l.l3) ^ \
               __builtin_e2k_pfcmpuod##type (s1.l.l3, s2.l.l3);  \
}

#define FILL4(dst, val) dst.l.l0 = dst.l.l1 = dst.l.l2 = dst.l.l3 = val

#else /* __iset__ <= 4 */

#define CMP2(type, op, s1, s2, dst) {                              \
    dst.__v2di = __builtin_e2k_q##op##type (s1.__v2di, s2.__v2di); \
}

#define CMP2EQ_UOD(type, s1, s2, dst) {                                     \
    dst.__v2di = __builtin_e2k_qpor (                                       \
                     __builtin_e2k_qpfcmpeq##type (s1.__v2di, s2.__v2di),   \
                     __builtin_e2k_qpfcmpuod##type (s1.__v2di, s2.__v2di)); \
}

#define CMP2NEQ_OD(type, s1, s2, dst) {                                     \
    dst.__v2di = __builtin_e2k_qpxor (                                      \
                     __builtin_e2k_qpfcmpneq##type (s1.__v2di, s2.__v2di),  \
                     __builtin_e2k_qpfcmpuod##type (s1.__v2di, s2.__v2di)); \
}

#define FILL2(dst, val) dst.__v2di = __builtin_e2k_qppackdl (val, val)

#define CMP4(type, op, s1, s2, dst) {                                          \
    dst.u__v4di.v0 = __builtin_e2k_q##op##type (s1.u__v4di.v0, s2.u__v4di.v0); \
    dst.u__v4di.v1 = __builtin_e2k_q##op##type (s1.u__v4di.v1, s2.u__v4di.v1); \
}

#define CMP4EQ_UOD(type, s1, s2, dst) {                                             \
    dst.u__v4di.v0 = __builtin_e2k_qpor (                                           \
                     __builtin_e2k_qpfcmpeq##type (s1.u__v4di.v0, s2.u__v4di.v0),   \
                     __builtin_e2k_qpfcmpuod##type (s1.u__v4di.v0, s2.u__v4di.v0)); \
    dst.u__v4di.v1 = __builtin_e2k_qpor (                                           \
                     __builtin_e2k_qpfcmpeq##type (s1.u__v4di.v1, s2.u__v4di.v1),   \
                     __builtin_e2k_qpfcmpuod##type (s1.u__v4di.v1, s2.u__v4di.v1)); \
}

#define CMP4NEQ_OD(type, s1, s2, dst) {                                             \
    dst.u__v4di.v0 = __builtin_e2k_qpxor (                                          \
                     __builtin_e2k_qpfcmpneq##type (s1.u__v4di.v0, s2.u__v4di.v0),  \
                     __builtin_e2k_qpfcmpuod##type (s1.u__v4di.v0, s2.u__v4di.v0)); \
    dst.u__v4di.v1 = __builtin_e2k_qpxor (                                          \
                     __builtin_e2k_qpfcmpneq##type (s1.u__v4di.v1, s2.u__v4di.v1),  \
                     __builtin_e2k_qpfcmpuod##type (s1.u__v4di.v1, s2.u__v4di.v1)); \
}

#define FILL4(dst, val) dst.u__v4di.v0 = dst.u__v4di.v1 = __builtin_e2k_qppackdl (val, val)

#endif /* __iset__ <= 4 */

#define CMP(type, size, dst)                                                                            \
    if (cmp_op == 0x00 /* _CMP_EQ_OQ */) { /*  Equal (ordered, non-signaling) */                        \
        CMP##size (type, pfcmpeq, s1, s2, dst);                                                         \
    }                                                                                                   \
    else if (cmp_op == 0x01 /* _CMP_LT_OS */) { /* Less-than (ordered, signaling)  */                   \
        CMP##size (type, pfcmplt, s1, s2, dst);                                                         \
    }                                                                                                   \
    else if (cmp_op == 0x02 /* _CMP_LE_OS */) { /* Less-than-or-equal (ordered, signaling)  */          \
        CMP##size (type, pfcmple, s1, s2, dst);                                                         \
    }                                                                                                   \
    else if (cmp_op == 0x03 /* _CMP_UNORD_Q */) { /* Unordered (non-signaling)  */                      \
        CMP##size (type, pfcmpuod, s1, s2, dst);                                                        \
    }                                                                                                   \
    else if (cmp_op == 0x04 /* _CMP_NEQ_UQ */) { /* Not-equal (unordered, non-signaling)  */            \
        CMP##size (type, pfcmpneq, s1, s2, dst);                                                        \
    }                                                                                                   \
    else if (cmp_op == 0x05 /* _CMP_NLT_US */) { /* Not-less-than (unordered, signaling)  */            \
        CMP##size (type, pfcmpnlt, s1, s2, dst);                                                        \
    }                                                                                                   \
    else if (cmp_op == 0x06 /* _CMP_NLE_US */) { /* Not-less-than-or-equal (unordered, signaling)  */   \
        CMP##size (type, pfcmpnle, s1, s2, dst);                                                        \
    }                                                                                                   \
    else if (cmp_op == 0x07 /* _CMP_ORD_Q */) { /* Ordered (non-signaling)  */                          \
        CMP##size (type, pfcmpod, s1, s2, dst);                                                         \
    }                                                                                                   \
    else if (cmp_op == 0x08 /* _CMP_EQ_UQ */) { /* Equal (unordered, non-signaling)  */                 \
        CMP##size##EQ_UOD (type, s1, s2, dst);                                                          \
    }                                                                                                   \
    else if (cmp_op == 0x09 /* _CMP_NGE_US */) { /* Not-greater-than-or-equal (unordered, signaling)  */\
        CMP##size (type, pfcmpnle, s2, s1, dst);                                                        \
    }                                                                                                   \
    else if (cmp_op == 0x0a /* _CMP_NGT_US */) { /* Not-greater-than (unordered, signaling)  */         \
        CMP##size (type, pfcmpnlt, s2, s1, dst);                                                        \
    }                                                                                                   \
    else if (cmp_op == 0x0b /* _CMP_FALSE_OQ */) { /* False (ordered, non-signaling)  */                \
        FILL##size (dst, 0LL);                                                                          \
    }                                                                                                   \
    else if (cmp_op == 0x0c /* _CMP_NEQ_OQ */) { /* Not-equal (ordered, non-signaling)  */              \
        CMP##size##NEQ_OD (type, s1, s2, dst);                                                          \
    }                                                                                                   \
    else if (cmp_op == 0x0d /* _CMP_GE_OS */) { /* Greater-than-or-equal (ordered, signaling)  */       \
        CMP##size (type, pfcmple, s2, s1, dst);                                                         \
    }                                                                                                   \
    else if (cmp_op == 0x0e /* _CMP_GT_OS */) { /* Greater-than (ordered, signaling)  */                \
        CMP##size (type, pfcmplt, s2, s1, dst);                                                         \
    }                                                                                                   \
    else if (cmp_op == 0x0f /* _CMP_TRUE_UQ */) { /* True (unordered, non-signaling)  */                \
        FILL##size (dst, -1LL);                                                                         \
    }
#if 0 /* инверсию выдачи invalid на qnan нам поддержать нечем */
    else if (cmp_op == 0x10 /* _CMP_EQ_OS */) { /* Equal (ordered, signaling)  */
    }
    else if (cmp_op == 0x11 /* _CMP_LT_OQ */) { /* Less-than (ordered, non-signaling)  */
    }
    else if (cmp_op == 0x12 /* _CMP_LE_OQ */) { /* Less-than-or-equal (ordered, non-signaling)  */
    }
    else if (cmp_op == 0x13 /* _CMP_UNORD_S */) { /* Unordered (signaling)  */
    }
    else if (cmp_op == 0x14 /* _CMP_NEQ_US */) { /* Not-equal (unordered, signaling)  */
    }
    else if (cmp_op == 0x15 /* _CMP_NLT_UQ */) { /* Not-less-than (unordered, non-signaling)  */
    }
    else if (cmp_op == 0x16 /* _CMP_NLE_UQ */) { /* Not-less-than-or-equal (unordered, non-signaling)  */
    }
    else if (cmp_op == 0x17 /* _CMP_ORD_S */) { /* Ordered (signaling)  */
    }
    else if (cmp_op == 0x18 /* _CMP_EQ_US */) { /* Equal (unordered, signaling)  */
    }
    else if (cmp_op == 0x19 /* _CMP_NGE_UQ */) { /* Not-greater-than-or-equal (unordered, non-signaling)  */
    }
    else if (cmp_op == 0x1a /* _CMP_NGT_UQ */) { /* Not-greater-than (unordered, non-signaling)  */
    }
    else if (cmp_op == 0x1b /* _CMP_FALSE_OS */) { /* False (ordered, signaling)  */
    }
    else if (cmp_op == 0x1c /* _CMP_NEQ_OS */) { /* Not-equal (ordered, signaling)  */
    }
    else if (cmp_op == 0x1d /* _CMP_GE_OQ */) { /* Greater-than-or-equal (ordered, non-signaling)  */
    }
    else if (cmp_op == 0x1e /* _CMP_GT_OQ */) { /* Greater-than (ordered, non-signaling)  */
    }
    else if (cmp_op == 0x1f /* _CMP_TRUE_US */) { /* True (unordered, signaling)  */
    }
#endif

/* сравнение 2-х даблов (64F) по предикату c формированием битовой маски */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cmppd (__v2df src1, __v2df src2, int cmp_op)
{
    type_union_128 s1, s2, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    cmp_op &= 0xf; /* инверсию выдачи invalid на qnan нам поддержать нечем (точнее, будет
                      сильно накладно), поэтому на старший бит предиката не реагируем */
    CMP (d, 2, dst);
    return dst.__v2df;
}

/* сравнение 4-х флотов (32F) по предикату c формированием битовой маски */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cmpps (__v4sf src1, __v4sf src2, int cmp_op)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    cmp_op &= 0xf; /* инверсию выдачи invalid на qnan нам поддержать нечем (точнее, будет
                      сильно накладно), поэтому на старший бит предиката не реагируем */
    CMP (s, 2, dst);
    return dst.__v4sf;
}

/* сравнение 4-х даблов (64F) по предикату c формированием битовой маски */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cmppd256 (__v4df src1, __v4df src2, int cmp_op)
{
    type_union_256 s1, s2, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
    cmp_op &= 0xf; /* инверсию выдачи invalid на qnan нам поддержать нечем (точнее, будет
                      сильно накладно), поэтому на старший бит предиката не реагируем */
    CMP (d, 4, dst);
    return dst.__v4df;
}

/* сравнение 8-ми флотов (32F) по предикату c формированием битовой маски */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cmpps256 (__v8sf src1, __v8sf src2, int cmp_op)
{
    type_union_256 s1, s2, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
    cmp_op &= 0xf; /* инверсию выдачи invalid на qnan нам поддержать нечем (точнее, будет
                      сильно накладно), поэтому на старший бит предиката не реагируем */
    CMP (s, 4, dst);
    return dst.__v8sf;
}

/* сравнение младшего дабла (64F) по предикату c формированием битовой маски */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cmpsd (__v2df src1, __v2df src2, int cmp_op)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
    cmp_op &= 0xf; /* инверсию выдачи invalid на qnan нам поддержать нечем (точнее, будет
                      сильно накладно), поэтому на старший бит предиката не реагируем */
    CMP (d, 1, s1);
    return s1.__v2df;
}

/* сравнение младшего флота (32F) по предикату c формированием битовой маски */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cmpss (__v4sf src1, __v4sf src2, int cmp_op)
{
    type_union_128 s1, s2, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    cmp_op &= 0xf; /* инверсию выдачи invalid на qnan нам поддержать нечем (точнее, будет
                      сильно накладно), поэтому на старший бит предиката не реагируем */
    CMP (s, 1, dst);
    s1.i.i0 = dst.i.i0;
    return s1.__v4sf;
}

/* *****************************************************************************
 *                          Операции преобразования
 * *****************************************************************************/

/* преобразование 4-х интов (32S) в 4 дабла (64F) */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtdq2pd256 (__v4si src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.d.d0 = (double) s.i.i0;
    dst.d.d1 = (double) s.i.i1;
    dst.d.d2 = (double) s.i.i2;
    dst.d.d3 = (double) s.i.i3;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qpistofd (s.l.l0);
    dst.u__v4di.v1 = __builtin_e2k_qpistofd (s.l.l1);
#endif /* __iset__ <= 4 */
    return dst.__v4df;
}

/* преобразование 8-ми интов (32S) в 8 флотов (32F) */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtdq2ps256 (__v8si src)
{
    type_union_256 s, dst;
    s.__v8si = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pistofs (s.l.l0);
    dst.l.l1 = __builtin_e2k_pistofs (s.l.l1);
    dst.l.l2 = __builtin_e2k_pistofs (s.l.l2);
    dst.l.l3 = __builtin_e2k_pistofs (s.l.l3);
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qpistofs (s.u__v4di.v0);
    dst.u__v4di.v1 = __builtin_e2k_qpistofs (s.u__v4di.v1);
#endif /* __iset__ <= 4 */
    return dst.__v8sf;
}

/* преобразование 4-х даблов (64F) в 4 флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtpd2ps256 (__v4df src)
{
    type_union_256 s;
    type_union_128 dst;
    s.__v4df = src;
#if __iset__ <= 4
    dst.f.f0 = (float) s.d.d0;
    dst.f.f1 = (float) s.d.d1;
    dst.f.f2 = (float) s.d.d2;
    dst.f.f3 = (float) s.d.d3;
#else /* __iset__ <= 4 */
    __di tmp0 = __builtin_e2k_qpfdtofs (s.u__v4di.v0);
    __di tmp1 = __builtin_e2k_qpfdtofs (s.u__v4di.v1);
    dst.__v2di = __builtin_e2k_qppackdl (tmp1, tmp0);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* преобразование 8-ми флотов (32F) в 8 интов (32S) */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtps2dq256 (__v8sf src)
{
    type_union_256 s, dst;
    s.__v8sf = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfstois (s.l.l0);
    dst.l.l1 = __builtin_e2k_pfstois (s.l.l1);
    dst.l.l2 = __builtin_e2k_pfstois (s.l.l2);
    dst.l.l3 = __builtin_e2k_pfstois (s.l.l3);
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qpfstois (s.u__v4di.v0);
    dst.u__v4di.v1 = __builtin_e2k_qpfstois (s.u__v4di.v1);
#endif /* __iset__ <= 4 */
    return dst.__v8si;
}

/* преобразование 4-х флотов (32F) в 4 дабла (64F) */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtps2pd256 (__v4sf src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v4sf = src;
#if __iset__ <= 4
    dst.d.d0 = (double) s.f.f0;
    dst.d.d1 = (double) s.f.f1;
    dst.d.d2 = (double) s.f.f2;
    dst.d.d3 = (double) s.f.f3;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qpfstofd (s.l.l0);
    dst.u__v4di.v1 = __builtin_e2k_qpfstofd (s.l.l1);
#endif /* __iset__ <= 4 */
    return dst.__v4df;
}

/* преобразование 4-х даблов (64F) в 4 инта (32S) c обрубанием */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttpd2dq256 (__v4df src)
{
    type_union_256 s;
    type_union_128 dst;
    s.__v4df = src;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_cvttpd2pi (s.u__v4df.v0);
    dst.l.l1 = (__di) __builtin_ia32_cvttpd2pi (s.u__v4df.v1);
#else /* __iset__ <= 4 */
    __di tmp0 = __builtin_e2k_qpfdtoistr (s.u__v4di.v0);
    __di tmp1 = __builtin_e2k_qpfdtoistr (s.u__v4di.v1);
    dst.__v2di = __builtin_e2k_qppackdl (tmp1, tmp0);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* преобразование 4-х даблов (64F) в 4 инта (32S) c в текущем режиме округления */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvtpd2dq256 (__v4df src)
{
    type_union_256 s;
    type_union_128 dst;
    s.__v4df = src;
#if __iset__ <= 4
    dst.l.l0 = (__di) __builtin_ia32_cvtpd2pi (s.u__v4df.v0);
    dst.l.l1 = (__di) __builtin_ia32_cvtpd2pi (s.u__v4df.v1);
#else /* __iset__ <= 4 */
    __di tmp0 = __builtin_e2k_qpfdtois (s.u__v4di.v0);
    __di tmp1 = __builtin_e2k_qpfdtois (s.u__v4di.v1);
    dst.__v2di = __builtin_e2k_qppackdl (tmp1, tmp0);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* преобразование 8-ми флотов (32F) в 8 интов (32S) c обрубанием */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_cvttps2dq256 (__v8sf src)
{
    type_union_256 s, dst;
    s.__v8sf = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfstoistr (s.l.l0);
    dst.l.l1 = __builtin_e2k_pfstoistr (s.l.l1);
    dst.l.l2 = __builtin_e2k_pfstoistr (s.l.l2);
    dst.l.l3 = __builtin_e2k_pfstoistr (s.l.l3);
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qpfstoistr (s.u__v4di.v0);
    dst.u__v4di.v1 = __builtin_e2k_qpfstoistr (s.u__v4di.v1);
#endif /* __iset__ <= 4 */
    return dst.__v8si;
}

/* *****************************************************************************
 *                             Перестановки
 * *****************************************************************************/

/* смешивание (выбор) 4-х даблов (64F) по битовой маске */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendpd256 (__v4df src1, __v4df src2, const int mask)
{
    type_union_256 s1, s2, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
    dst.u__v4df.v0 = __builtin_ia32_blendpd (s1.u__v4df.v0, s2.u__v4df.v0, mask);
    dst.u__v4df.v1 = __builtin_ia32_blendpd (s1.u__v4df.v1, s2.u__v4df.v1, mask >> 2);
    return dst.__v4df;
}

/* смешивание (выбор) 8-ми флотов (32F) по битовой маске */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendps256 (__v8sf src1, __v8sf src2, const int mask)
{
    type_union_256 s1, s2, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
    dst.u__v8sf.v0 = __builtin_ia32_blendps (s1.u__v8sf.v0, s2.u__v8sf.v0, mask);
    dst.u__v8sf.v1 = __builtin_ia32_blendps (s1.u__v8sf.v1, s2.u__v8sf.v1, mask >> 4);
    return dst.__v8sf;
}

/* смешивание (выбор) 4-х даблов (64F) по знаку дабловой маски */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendvpd256 (__v4df src1, __v4df src2, __v4df mask)
{
    type_union_256 s1, s2, m, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
    m.__v4df = mask;
    dst.u__v4df.v0 = __builtin_ia32_blendvpd (s1.u__v4df.v0, s2.u__v4df.v0, m.u__v4df.v0);
    dst.u__v4df.v1 = __builtin_ia32_blendvpd (s1.u__v4df.v1, s2.u__v4df.v1, m.u__v4df.v1);
    return dst.__v4df;
}

/* смешивание (выбор) 8-ми флотов (32F) по знаку флотовой маски */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_blendvps256 (__v8sf src1, __v8sf src2, __v8sf mask)
{
    type_union_256 s1, s2, m, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
    m.__v8sf = mask;
    dst.u__v8sf.v0 = __builtin_ia32_blendvps (s1.u__v8sf.v0, s2.u__v8sf.v0, m.u__v8sf.v0);
    dst.u__v8sf.v1 = __builtin_ia32_blendvps (s1.u__v8sf.v1, s2.u__v8sf.v1, m.u__v8sf.v1);
    return dst.__v8sf;
}

/* выделение из 8-ми входных даблов 4-х, положение которых определяется в 4-х
 * младших разрядах константы 3-го операнда */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_shufpd256 (__v4df src1, __v4df src2, const int mask)
{
    type_union_256 s1, s2, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
    dst.l.l0 = (mask & 1) ? s1.l.l1 : s1.l.l0;
    dst.l.l1 = (mask & 2) ? s2.l.l1 : s2.l.l0;
    dst.l.l2 = (mask & 4) ? s1.l.l3 : s1.l.l2;
    dst.l.l3 = (mask & 8) ? s2.l.l3 : s2.l.l2;
    return dst.__v4df;
}

/* выделение из 16-ти входных флотов 8-ми, положение которых определяется 8-ю
 * младшими разрядами константы 3-го операнда */
#define __builtin_ia32_256(src1, src2, mask) ({                                 \
    type_union_256 _s1, _s2, _dst;                                                    \
    _s1.__v8sf = src1;                                                                \
    _s2.__v8sf = src2;                                                                \
    _dst.u__v8sf.v0 = __builtin_ia32_shufps (_s1.u__v8sf.v0, _s2.u__v8sf.v0, (mask)); \
    _dst.u__v8sf.v1 = __builtin_ia32_shufps (_s1.u__v8sf.v1, _s2.u__v8sf.v1, (mask)); \
    _dst.__v8sf;                                                                      \
})

/* выделение старшей или младшей половины из 4-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vextractf128_pd256 (__v4df src, const int indx)
{
    type_union_256 s;
    s.__v4df = src;
    return (indx & 1) ? s.u__v4df.v1 : s.u__v4df.v0;
}

/* выделение старшей или младшей половины из 8-ми флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vextractf128_ps256 (__v8sf src, const int indx)
{
    type_union_256 s;
    s.__v8sf = src;
    return (indx & 1) ? s.u__v8sf.v1 : s.u__v8sf.v0;
}

/* выделение старшей или младшей половины из 8-ми интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vextractf128_si256 (__v8si src, const int indx)
{
    type_union_256 s;
    s.__v8si = src;
    return (indx & 1) ? s.u__v8si.v1 : s.u__v8si.v0;
}

#define SELECT_32F(src1, src0, dst, indx) {                                   \
    __di mask = (indx & 0x300000003LL) * 0x04040404LL + 0x0302010003020100LL; \
    dst = __builtin_e2k_pshufb (src1, src0, mask);                            \
}

#define SELECT_CONST_32F(src1, src0, dst, indx) {                                            \
    __di mask = ((indx & 3) | ((indx & 0xcLL) << 30)) * 0x04040404LL + 0x0302010003020100LL; \
    dst = __builtin_e2k_pshufb (src1, src0, mask);                                           \
}

/* перестановка 2-х даблов (64F) первого операнда в зависимости от 2-го бита каждого
 * дабла второго операнда */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermilvarpd (__v2df src, __v2di indx)
{
    type_union_128 s, in, dst;
    s.__v2df = src;
    in.__v2di = indx;
    dst.l.l0 = (in.l.l0 & 2) ? s.l.l1 : s.l.l0;
    dst.l.l1 = (in.l.l1 & 2) ? s.l.l1 : s.l.l0;
    return dst.__v2df;
}

/* перестановка 4-х даблов (64F) первого операнда в зависимости от 2-го бита каждого
 * дабла второго операнда */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermilvarpd256 (__v4df src, __v4di indx)
{
    type_union_256 s, in, dst;
    s.__v4df = src;
    in.__v4di = indx;
    dst.l.l0 = (in.l.l0 & 2) ? s.l.l1 : s.l.l0;
    dst.l.l1 = (in.l.l1 & 2) ? s.l.l1 : s.l.l0;
    dst.l.l2 = (in.l.l2 & 2) ? s.l.l3 : s.l.l2;
    dst.l.l3 = (in.l.l3 & 2) ? s.l.l3 : s.l.l2;
    return dst.__v4df;
}

/* перестановка 4-х флотов (32F) первого операнда в зависимости от 2-х младших бит
 * каждого флота второго операнда */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermilvarps (__v4sf src, __v4si indx)
{
    type_union_128 s, in, dst;
    s.__v4sf = src;
    in.__v4si = indx;
    SELECT_32F (s.l.l1, s.l.l0, dst.l.l0, in.l.l0);
    SELECT_32F (s.l.l1, s.l.l0, dst.l.l1, in.l.l1);
    return dst.__v4sf;
}

/* перестановка 8-ми флотов (32F) первого операнда в зависимости от 2-х младших бит
 * каждого флота второго операнда */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermilvarps256 (__v8sf src, __v8si indx)
{
    type_union_256 s, in, dst;
    s.__v8sf = src;
    in.__v8si = indx;
    SELECT_32F (s.l.l1, s.l.l0, dst.l.l0, in.l.l0);
    SELECT_32F (s.l.l1, s.l.l0, dst.l.l1, in.l.l1);
    SELECT_32F (s.l.l3, s.l.l2, dst.l.l2, in.l.l2);
    SELECT_32F (s.l.l3, s.l.l2, dst.l.l3, in.l.l3);
    return dst.__v8sf;
}

/* перестановка 2-х даблов (64F) первого операнда в зависимости от 2-х младших бит
 * второго операнда */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermilpd (__v2df src, const int indx)
{
    type_union_128 s, dst;
    s.__v2df = src;
    dst.l.l0 = (indx & 1) ? s.l.l1 : s.l.l0;
    dst.l.l1 = (indx & 2) ? s.l.l1 : s.l.l0;
    return dst.__v2df;
}

/* перестановка 4-х даблов (64F) первого операнда в зависимости от 4-х младших бит
 * второго операнда */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermilpd256 (__v4df src, const int indx)
{
    type_union_256 s, dst;
    s.__v4df = src;
    dst.l.l0 = (indx & 1) ? s.l.l1 : s.l.l0;
    dst.l.l1 = (indx & 2) ? s.l.l1 : s.l.l0;
    dst.l.l2 = (indx & 4) ? s.l.l3 : s.l.l2;
    dst.l.l3 = (indx & 8) ? s.l.l3 : s.l.l2;
    return dst.__v4df;
}

/* перестановка 4-х флотов (32F) первого операнда в зависимости от 8-ми младших бит
 * второго операнда */
#define __builtin_ia32_vpermilps(src, indx) ({                      \
    type_union_128 __s, __dst;                                      \
    __s.__v4sf = src;                                               \
    SELECT_CONST_32F (__s.l.l1, __s.l.l0, __dst.l.l0, (indx));      \
    SELECT_CONST_32F (__s.l.l1, __s.l.l0, __dst.l.l1, (indx) >> 4); \
    __dst.__v4sf;                                                   \
})

/* перестановка 8-ми флотов (32F) первого операнда в зависимости от 2-х младших бит
 * каждого флота второго операнда */
#define __builtin_ia32_vpermilps256(src, indx) ({                   \
    type_union_256 __s, __dst;                                      \
    __s.__v8sf = src;                                               \
    SELECT_CONST_32F (__s.l.l1, __s.l.l0, __dst.l.l0, (indx));      \
    SELECT_CONST_32F (__s.l.l1, __s.l.l0, __dst.l.l1, (indx) >> 4); \
    SELECT_CONST_32F (__s.l.l3, __s.l.l2, __dst.l.l2, (indx));      \
    SELECT_CONST_32F (__s.l.l3, __s.l.l2, __dst.l.l3, (indx) >> 4); \
    __dst.__v8sf;                                                   \
})

#define SELECT_CONST_128F(src1, src2, dst, indx) {                  \
    if ((indx) & 8) { dst.__v2di = (__v2di) {0, 0}; }               \
    else {                                                          \
        if (((indx) & 3) == 0) { dst = src1.u128.u0; }              \
        else if (((indx) & 3) == 1) { dst = src1.u128.u1; }         \
        else if (((indx) & 3) == 2) { dst = src2.u128.u0; }         \
        else if (((indx) & 3) == 3) { dst = src2.u128.u1; }         \
    }                                                               \
}

/* перестановка 128-ми бит из первых 2-х операндов в зависимости от 8-ми младших бит
 * третьего операнда */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vperm2f128_pd256 (__v4df src1, __v4df src2, const int indx)
{
    type_union_256 s1, s2, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
    SELECT_CONST_128F (s1, s2, dst.u128.u0, indx);
    SELECT_CONST_128F (s1, s2, dst.u128.u1, indx >> 4);
    return dst.__v4df;
}

/* перестановка 128-ми бит из первых 2-х операндов в зависимости от 8-ми младших бит
 * третьего операнда */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vperm2f128_ps256 (__v8sf src1, __v8sf src2, const int indx)
{
    type_union_256 s1, s2, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
    SELECT_CONST_128F (s1, s2, dst.u128.u0, indx);
    SELECT_CONST_128F (s1, s2, dst.u128.u1, indx >> 4);
    return dst.__v8sf;
}

/* перестановка 128-ми бит из первых 2-х операндов в зависимости от 8-ми младших бит
 * третьего операнда */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vperm2f128_si256 (__v8si src1, __v8si src2, const int indx)
{
    type_union_256 s1, s2, dst;
    s1.__v8si = src1;
    s2.__v8si = src2;
    SELECT_CONST_128F (s1, s2, dst.u128.u0, indx);
    SELECT_CONST_128F (s1, s2, dst.u128.u1, indx >> 4);
    return dst.__v8si;
}

/* *****************************************************************************
 *                             Размножение
 * *****************************************************************************/

/* размножение одного флота (32F) в четыре */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastss (float const *p)
{
    type_union_128 dst;
    __di tmp = __builtin_e2k_insfd (*((unsigned const *) p), (32 << 6) | 32, *((unsigned const *) p));
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = tmp;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppackdl (tmp, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* размножение одного дабла (64F) в четыре */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastsd256 (double const *p)
{
    type_union_256 dst;
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = dst.l.l2 = dst.l.l3 = *((__di const *) p);
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = dst.u__v4di.v1 = __builtin_e2k_qppackdl (*((__di const *) p), *((__di const *) p));
#endif /* __iset__ <= 4 */
    return dst.__v4df;
}

/* размножение одного флота (32F) в восемь */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastss256 (float const *p)
{
    type_union_256 dst;
    __di tmp = __builtin_e2k_insfd (*((unsigned const *) p), (32 << 6) | 32, *((unsigned const *) p));
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = dst.l.l2 = dst.l.l3 = tmp;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = dst.u__v4di.v1 = __builtin_e2k_qppackdl (tmp, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v8sf;
}

/* размножение одного 128-битного значения в два */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastf128_pd256 (__v2df const *p)
{
    type_union_256 dst;
    dst.u128.u0 = dst.u128.u1 = *((type_union_128 const *) p);
    return dst.__v4df;
}

/* размножение одного 128-битного значения в два */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastf128_ps256 (__v4sf const *p)
{
    type_union_256 dst;
    dst.u128.u0 = dst.u128.u1 = *((type_union_128 const *) p);
    return dst.__v8sf;
}

/* *****************************************************************************
 *                            Вставка
 * *****************************************************************************/

/* Вставка 2-х даблов (64F) в старшую или младшую половины src1 в зависимости
 * от младшего бита индекса */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vinsertf128_pd256 (__v4df src1, __v2df src2, const int indx)
{
    type_union_256 s1;
    s1.__v4df = src1;
    if (indx & 1) {
        s1.u__v4df.v1 = src2;
    }
    else {
        s1.u__v4df.v0 = src2;
    }
    return s1.__v4df;
}

/* Вставка 4-х флотов (32F) в старшую или младшую половины src1 в зависимости
 * от младшего бита индекса */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vinsertf128_ps256 (__v8sf src1, __v4sf src2, const int indx)
{
    type_union_256 s1;
    s1.__v8sf = src1;
    if (indx & 1) {
        s1.u__v8sf.v1 = src2;
    }
    else {
        s1.u__v8sf.v0 = src2;
    }
    return s1.__v8sf;
}

/* Вставка 4-х интов (32S) в старшую или младшую половины src1 в зависимости
 * от младшего бита индекса */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vinsertf128_si256 (__v8si src1, __v4si src2, const int indx)
{
    type_union_256 s1;
    s1.__v8si = src1;
    if (indx & 1) {
        s1.u__v8si.v1 = src2;
    }
    else {
        s1.u__v8si.v0 = src2;
    }
    return s1.__v8si;
}

/* *****************************************************************************
 *                            Чтения / Записи
 * *****************************************************************************/

/* чтение 4-х даблов (64F) по произвольно выровненному адресу */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadupd256 (const double *p)
{
    type_union_256 dst;
    dst.u__v8sf.v0 = __builtin_ia32_loadups ((const float *) p);
    dst.u__v8sf.v1 = __builtin_ia32_loadups ((const float *) (p + 2));
    return dst.__v4df;
}

/* запись 4-х даблов (64F) по произвольно выровненному адресу */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storeupd256 (double *p, __v4df src)
{
    type_union_256 s;
    s.__v4df = src;
    __builtin_ia32_storeups ((float *) p, s.u__v8sf.v0);
    __builtin_ia32_storeups ((float *) (p + 2), s.u__v8sf.v1);
}

/* чтение 8-ми флотов (32F) по произвольно выровненному адресу */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loadups256 (const float *p)
{
    type_union_256 dst;
    dst.u__v8sf.v0 = __builtin_ia32_loadups (p);
    dst.u__v8sf.v1 = __builtin_ia32_loadups (p + 4);
    return dst.__v8sf;
}

/* запись 8-ми флотов (32F) по произвольно выровненному адресу */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storeups256 (float *p, __v8sf src)
{
    type_union_256 s;
    s.__v8sf = src;
    __builtin_ia32_storeups (p, s.u__v8sf.v0);
    __builtin_ia32_storeups (p + 4, s.u__v8sf.v1);
}

/* чтение 32-х байт (8U/8S) по произвольно выровненному адресу */
__E2K_INLINE __v32qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_loaddqu256 (const char *p)
{
    type_union_256 dst;
    dst.u__v8sf.v0 = __builtin_ia32_loadups ((const float *) p);
    dst.u__v8sf.v1 = __builtin_ia32_loadups ((const float *) (p + 16));
    return dst.__v32qi;
}

/* чтение 32-х байт (8U/8S) по произвольно выровненному адресу */
#define __builtin_ia32_lddqu256 __builtin_ia32_loaddqu256

/* запись 32-х байт (8U/8S) по произвольно выровненному адресу */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_storedqu256 (char *p, __v32qi src)
{
    type_union_256 s;
    s.__v32qi = src;
    __builtin_ia32_storeups ((float *) p, s.u__v8sf.v0);
    __builtin_ia32_storeups ((float *) (p + 16), s.u__v8sf.v1);
}

/* запись 4-х лонгов (64S/64U) по выровненному на 32 байта адресу.
 * using a non-temporal memory hint */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntdq256 (__v4di *p, __v4di src)
{
    type_union_256 s;
    s.__v4di = src;
#if __iset__ <= 4
    __builtin_e2k_st_64s_nt (s.l.l0, p);
    __builtin_e2k_st_64s_nt (s.l.l1, (__di *) p + 1);
    __builtin_e2k_st_64s_nt (s.l.l2, (__di *) p + 2);
    __builtin_e2k_st_64s_nt (s.l.l3, (__di *) p + 3);
#else /* __iset__ <= 4 */
    __builtin_e2k_st_128_nt (s.u__v4di.v0, p);
    __builtin_e2k_st_128_nt (s.u__v4di.v1, (__v2di *) p + 1);
#endif /* __iset__ <= 4 */
}

/* запись 4-х даблов (64F) по выровненному на 32 байта адресу.
 * using a non-temporal memory hint */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntpd256 (double *p, __v4df src)
{
    __builtin_ia32_movntdq256 ((__v4di *) p, (__v4di) src);
}

/* запись 8-ми флотов (32F) по выровненному на 32 байта адресу.
 * using a non-temporal memory hint */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntps256 (float *p, __v8sf src)
{
    __builtin_ia32_movntdq256 ((__v4di *) p, (__v4di) src);
}

/* *****************************************************************************
 *                        Чтения / Записи по маске
 * *****************************************************************************/

/* чтение 2-х даблов (64F) по маске */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadpd (const __v2df *p, __v2di mask)
{
    type_union_128 m, dst;
    m.__v2di = mask;
#if __iset__ <= 4
    dst.d.d0 = ((long long) m.l.l0 < 0) ? ((double *) p)[0] : 0;
    dst.d.d1 = ((long long) m.l.l1 < 0) ? ((double *) p)[1] : 0;
#else /* __iset__ <= 4 */
    __v2di tmp = ((const __v2di *) p)[0];
    __v2di msk = __builtin_e2k_qpcmpgtd (__builtin_e2k_qppackdl (0, 0), m.__v2di);
    dst.__v2di = __builtin_e2k_qpand (msk, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v2df;
}

/* запись 2-х даблов (64F) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstorepd (__v2df *p, __v2di mask, __v2df src)
{
    type_union_128 s, m;
    s.__v2df = src;
    m.__v2di = mask;
#if __iset__ <= 4
    if ((long long) m.l.l0 < 0) ((double *) p)[0] = s.d.d0;
    if ((long long) m.l.l1 < 0) ((double *) p)[1] = s.d.d1;
#else /* __iset__ <= 4 */
    __di msk = __builtin_e2k_qpsgn2mskb (m.__v2di);
    msk = __builtin_e2k_pcmpgtb (0, msk);
    __builtin_e2k_pst_128 (s.__v2di, p, msk);
#endif /* __iset__ <= 4 */
}

/* чтение 4-х даблов (64F) по маске */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadpd256 (const __v4df *p, __v4di mask)
{
    type_union_256 m, dst;
    m.__v4di = mask;
    dst.u__v4df.v0 = __builtin_ia32_maskloadpd ((const __v2df *) p, m.u__v4di.v0);
    dst.u__v4df.v1 = __builtin_ia32_maskloadpd (((const __v2df *) p) + 1, m.u__v4di.v1);
    return dst.__v4df;
}

/* запись 4-х даблов (64F) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstorepd256 (__v4df *p, __v4di mask, __v4df src)
{
    type_union_256 s, m;
    s.__v4df = src;
    m.__v4di = mask;
    __builtin_ia32_maskstorepd ((__v2df *) p, m.u__v4di.v0, s.u__v4df.v0);
    __builtin_ia32_maskstorepd (((__v2df *) p) + 1, m.u__v4di.v1, s.u__v4df.v1);
}

/* чтение 4-х флотов (32F) по маске */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadps (const __v4sf *p, __v4si mask)
{
    type_union_128 m, dst;
    m.__v4si = mask;
#if __iset__ <= 4
    dst.f.f0 = (m.i.i0 < 0) ? ((float *) p)[0] : 0;
    dst.f.f1 = (m.i.i1 < 0) ? ((float *) p)[1] : 0;
    dst.f.f2 = (m.i.i2 < 0) ? ((float *) p)[2] : 0;
    dst.f.f3 = (m.i.i3 < 0) ? ((float *) p)[3] : 0;
#else /* __iset__ <= 4 */
    __v2di tmp = ((const __v2di *) p)[0];
    __v2di msk = __builtin_e2k_qpcmpgtw (__builtin_e2k_qppackdl (0, 0), m.__v2di);
    dst.__v2di = __builtin_e2k_qpand (msk, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* запись 4-х флотов (32F) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstoreps (__v4sf *p, __v4si mask, __v4sf src)
{
    type_union_128 s, m;
    s.__v4sf = src;
    m.__v4si = mask;
#if __iset__ <= 4
    if (m.i.i0 < 0) ((float *) p)[0] = s.f.f0;
    if (m.i.i1 < 0) ((float *) p)[1] = s.f.f1;
    if (m.i.i2 < 0) ((float *) p)[2] = s.f.f2;
    if (m.i.i3 < 0) ((float *) p)[3] = s.f.f3;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtw (__builtin_e2k_qppackdl (0, 0), m.__v2di);
    __di msk = __builtin_e2k_qpsgn2mskb (tmp);
    __builtin_e2k_pst_128 (s.__v2di, p, msk);
#endif /* __iset__ <= 4 */
}

/* чтение 8-ми флотов (32F) по маске */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadps256 (const __v8sf *p, __v8si mask)
{
    type_union_256 m, dst;
    m.__v8si = mask;
    dst.u__v8sf.v0 = __builtin_ia32_maskloadps ((const __v4sf *) p, m.u__v8si.v0);
    dst.u__v8sf.v1 = __builtin_ia32_maskloadps (((const __v4sf *) p) + 1, m.u__v8si.v1);
    return dst.__v8sf;
}

/* запись 8-ми флотов (32F) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstoreps256 (__v8sf *p, __v8si mask, __v8sf src)
{
    type_union_256 s, m;
    s.__v8sf = src;
    m.__v8si = mask;
    __builtin_ia32_maskstoreps ((__v4sf *) p, m.u__v8si.v0, s.u__v8sf.v0);
    __builtin_ia32_maskstoreps (((__v4sf *) p) + 1, m.u__v8si.v1, s.u__v8sf.v1);
}

/* *****************************************************************************
 *                              Пересылки
 * *****************************************************************************/

/* размножение нечетных среди пар внутри 8-ми флотов (32F) */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movshdup256 (__v8sf src)
{
    type_union_256 s, dst;
    s.__v8sf = src;
    dst.u__v8sf.v0 = __builtin_ia32_movshdup (s.u__v8sf.v0);
    dst.u__v8sf.v1 = __builtin_ia32_movshdup (s.u__v8sf.v1);
    return dst.__v8sf;
}

/* размножение четных среди пар внутри 8-ми флотов (32F) */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movsldup256 (__v8sf src)
{
    type_union_256 s, dst;
    s.__v8sf = src;
    dst.u__v8sf.v0 = __builtin_ia32_movsldup (s.u__v8sf.v0);
    dst.u__v8sf.v1 = __builtin_ia32_movsldup (s.u__v8sf.v1);
    return dst.__v8sf;
}

/* размножение четных среди пар внутри 4-х даблов (64F) */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movddup256 (__v4df src)
{
    type_union_256 s, dst;
    s.__v4df = src;
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = s.l.l0;
    dst.l.l2 = dst.l.l3 = s.l.l2;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qppackdl (s.l.l0, s.l.l0);
    dst.u__v4di.v1 = __builtin_e2k_qppackdl (s.l.l2, s.l.l2);
#endif /* __iset__ <= 4 */
    return dst.__v4df;
}

/* *****************************************************************************
 *                               Распаковки
 * *****************************************************************************/

/* перемешивание даблов (64F) от двух аргументов из старших половин 128-битных частей */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpckhpd256 (__v4df src1, __v4df src2)
{
    type_union_256 s1, s2, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
#if __iset__ <= 4
    dst.l.l0 = s1.l.l1;
    dst.l.l1 = s2.l.l1;
    dst.l.l2 = s1.l.l3;
    dst.l.l3 = s2.l.l3;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s1.u__v4di.v0, s2.u__v4di.v0,
                         __builtin_e2k_qppackdl (0x0f0e0d0c0b0a0908LL, 0x1f1e1d1c1b1a1918LL));
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s1.u__v4di.v1, s2.u__v4di.v1,
                         __builtin_e2k_qppackdl (0x0f0e0d0c0b0a0908LL, 0x1f1e1d1c1b1a1918LL));
#endif /* __iset__ <= 4 */
    return dst.__v4df;
}

/* перемешивание даблов (64F) от двух аргументов из младших половин 128-битных частей */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpcklpd256 (__v4df src1, __v4df src2)
{
    type_union_256 s1, s2, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
#if __iset__ <= 4
    dst.l.l0 = s1.l.l0;
    dst.l.l1 = s2.l.l0;
    dst.l.l2 = s1.l.l2;
    dst.l.l3 = s2.l.l2;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qppackdl (s2.l.l0, s1.l.l0);
    dst.u__v4di.v1 = __builtin_e2k_qppackdl (s2.l.l2, s1.l.l2);
#endif /* __iset__ <= 4 */
    return dst.__v4df;
}

/* перемешивание флотов (32F) от двух аргументов из старших половин 128-битных частей */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpckhps256 (__v8sf src1, __v8sf src2)
{
    type_union_256 s1, s2, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_punpcklwd (s2.l.l1, s1.l.l1);
    dst.l.l1 = __builtin_e2k_punpckhwd (s2.l.l1, s1.l.l1);
    dst.l.l2 = __builtin_e2k_punpcklwd (s2.l.l3, s1.l.l3);
    dst.l.l3 = __builtin_e2k_punpckhwd (s2.l.l3, s1.l.l3);
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s2.u__v4di.v0, s1.u__v4di.v0,
                         __builtin_e2k_qppackdl (0x1f1e1d1c0f0e0d0cLL, 0x1b1a19180b0a0908LL));
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s2.u__v4di.v1, s1.u__v4di.v1,
                         __builtin_e2k_qppackdl (0x1f1e1d1c0f0e0d0cLL, 0x1b1a19180b0a0908LL));
#endif /* __iset__ <= 4 */
    return dst.__v8sf;
}

/* перемешивание флотов (32F) от двух аргументов из младших половин 128-битных частей */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_unpcklps256 (__v8sf src1, __v8sf src2)
{
    type_union_256 s1, s2, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_punpcklwd (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_punpckhwd (s2.l.l0, s1.l.l0);
    dst.l.l2 = __builtin_e2k_punpcklwd (s2.l.l2, s1.l.l2);
    dst.l.l3 = __builtin_e2k_punpckhwd (s2.l.l2, s1.l.l2);
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s2.u__v4di.v0, s1.u__v4di.v0,
                         __builtin_e2k_qppackdl (0x1716151407060504LL, 0x1312111003020100LL));
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s2.u__v4di.v1, s1.u__v4di.v1,
                         __builtin_e2k_qppackdl (0x1716151407060504LL, 0x1312111003020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v8sf;
}

/* *****************************************************************************
 *                            Побитовое сравнение
 * *****************************************************************************/

/* логическое AND 128-битных значений (по 2 дабла (64F)). Возвращает 1,
 * если знаки обоих даблов результата (src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestzpd (__v2df src1, __v2df src2)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
#if __iset__ <= 4
    return (long long)((s1.l.l0 & s2.l.l0) | (s1.l.l1 & s2.l.l1)) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpand (s1.__v2di, s2.__v2di);
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask & 0x8080) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое ANDNOT 128-битных значений (по 2 дабла (64F)). Возвращает 1,
 * если знаки обоих даблов результата (~src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestcpd (__v2df src1, __v2df src2)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
#if __iset__ <= 4
    return (long long)((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1)) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpandn (s2.__v2di, s1.__v2di);
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask & 0x8080) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND и ANDNOT 128-битных значений (по 2 дабла (64F)). Возвращает 1,
 * если знаки хоть одного из даблов результата (src1 & src2) != 0 && (~src1 & src2) != 0. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestnzcpd (__v2df src1, __v2df src2)
{
    type_union_128 s1, s2;
    s1.__v2df = src1;
    s2.__v2df = src2;
#if __iset__ <= 4
    return (long long)(((s2.l.l0 &  s1.l.l0) | (s2.l.l1 &  s1.l.l1)) &
                       ((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1))) < 0;
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qpand (s2.__v2di, s1.__v2di);
    __v2di tmp1 = __builtin_e2k_qpandn (s2.__v2di, s1.__v2di);
 #if __iset__ <= 5
    int mask0 = __builtin_e2k_qpsgn2mskb (tmp0);
    int mask1 = __builtin_e2k_qpsgn2mskb (tmp1);
    return (mask0 & 0x8080) != 0 && (mask1 & 0x8080) != 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp0)
        && __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp1);
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND 128-битных значений (по 4 флота (32F)). Возвращает 1,
 * если знаки 4-х флотов результата (src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestzps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
    __di tmp = (s1.l.l0 & s2.l.l0) | (s1.l.l1 & s2.l.l1);
    return (long long)((tmp << 32) | tmp) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qpand (s2.__v2di, s1.__v2di);
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp0);
    return (mask & 0x8888) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp0) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое ANDNOT 128-битных значений (по 4 флота (32F)). Возвращает 1,
 * если знаки 4-х флотов результата (~src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestcps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
    __di tmp = (s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1);
    return (long long)((tmp << 32) | tmp) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qpandn (s2.__v2di, s1.__v2di);
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp0);
    return (mask & 0x8888) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp0) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND и ANDNOT 128-битных значений (по 4 флота (32F)). Возвращает 1,
 * если знаки хоть одного из 4-х флотов результата (src1 & src2) != 0 && (~src1 & src2) != 0. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestnzcps (__v4sf src1, __v4sf src2)
{
    type_union_128 s1, s2;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
#if __iset__ <= 4
    __di tmp1 = (s1.l.l0 & s2.l.l0) | (s1.l.l1 & s2.l.l1);
    __di tmp2 = (s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1);
    tmp1 |= tmp1 << 32;
    tmp2 |= tmp2 << 32;
    return (long long)(tmp1 & tmp2) < 0;
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qpand (s2.__v2di, s1.__v2di);
    __v2di tmp1 = __builtin_e2k_qpandn (s2.__v2di, s1.__v2di);
 #if __iset__ <= 5
    int mask0 = __builtin_e2k_qpsgn2mskb (tmp0);
    int mask1 = __builtin_e2k_qpsgn2mskb (tmp1);
    return (mask0 & 0x8888) != 0 && (mask1 & 0x8888) != 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp0)
        && __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp1);
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND 256-битных значений (по 4 дабла (64F)). Возвращает 1,
 * если знаки 4-х даблов результата (src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestzpd256 (__v4df src1, __v4df src2)
{
    type_union_256 s1, s2;
    s1.__v4df = src1;
    s2.__v4df = src2;
#if __iset__ <= 4
    return (long long)((s1.l.l0 & s2.l.l0) | (s1.l.l1 & s2.l.l1) |
                       (s1.l.l2 & s2.l.l2) | (s1.l.l3 & s2.l.l3)) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpand (s1.u__v4di.v0, s2.u__v4di.v0);
    tmp = __builtin_e2k_qplog (0xea, s1.u__v4di.v1, s2.u__v4di.v1, tmp); /* (s1 & s2) | s3 */
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask & 0x8080) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое ANDNOT 256-битных значений (по 4 дабла (64F)). Возвращает 1,
 * если знаки 4-х даблов результата (~src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestcpd256 (__v4df src1, __v4df src2)
{
    type_union_256 s1, s2;
    s1.__v4df = src1;
    s2.__v4df = src2;
#if __iset__ <= 4
    return (long long)((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1) |
                       (s2.l.l2 & ~s1.l.l2) | (s2.l.l3 & ~s1.l.l3)) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpandn (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp = __builtin_e2k_qplog (0xba, s2.u__v4di.v1, s1.u__v4di.v1, tmp); /* (s2 & ~s1) | s3 */
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask & 0x8080) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND и ANDNOT 256-битных значений (по 4 дабла (64F)). Возвращает 1,
 * если знаки хоть одного из 4-х даблов результата (src1 & src2) != 0 && (~src1 & src2) != 0. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestnzcpd256 (__v4df src1, __v4df src2)
{
    type_union_256 s1, s2;
    s1.__v4df = src1;
    s2.__v4df = src2;
#if __iset__ <= 4
    return (long long)(((s1.l.l0 &  s2.l.l0) | (s1.l.l1 &  s2.l.l1) |
                        (s1.l.l2 &  s2.l.l2) | (s1.l.l3 &  s2.l.l3)) &
                       ((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1) |
                        (s2.l.l2 & ~s1.l.l2) | (s2.l.l3 & ~s1.l.l3))) < 0;
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qpand (s2.u__v4di.v0, s1.u__v4di.v0);
    __v2di tmp1 = __builtin_e2k_qpandn (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp0 = __builtin_e2k_qplog (0xea, s2.u__v4di.v1, s1.u__v4di.v1, tmp0); /* (s1 & s2) | s3 */
    tmp1 = __builtin_e2k_qplog (0xba, s2.u__v4di.v1, s1.u__v4di.v1, tmp1); /* (s2 & ~s1) | s3 */
 #if __iset__ <= 5
    int mask0 = __builtin_e2k_qpsgn2mskb (tmp0);
    int mask1 = __builtin_e2k_qpsgn2mskb (tmp1);
    return (mask0 & 0x8080) != 0 && (mask1 & 0x8080) != 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp0)
        && __builtin_e2k_qpcmpgtdop (__builtin_e2k_qppackdl (0, 0), tmp1);
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND 256-битных значений (по 8 флотов (32F)). Возвращает 1,
 * если знаки 8-ми флотов результата (src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestzps256 (__v8sf src1, __v8sf src2)
{
    type_union_256 s1, s2;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
#if __iset__ <= 4
    __di tmp = (s1.l.l0 & s2.l.l0) | (s1.l.l1 & s2.l.l1) |
               (s1.l.l2 & s2.l.l2) | (s1.l.l3 & s2.l.l3);
    return (long long)((tmp << 32) | tmp) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpand (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp = __builtin_e2k_qplog (0xea, s2.u__v4di.v1, s1.u__v4di.v1, tmp); /* (s1 & s2) | s3 */
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask & 0x8888) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое ANDNOT 256-битных значений (по 8 флотов (32F)). Возвращает 1,
 * если знаки 8-ми флотов результата (~src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestcps256 (__v8sf src1, __v8sf src2)
{
    type_union_256 s1, s2;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
#if __iset__ <= 4
    __di tmp = (s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1) |
               (s2.l.l2 & ~s1.l.l2) | (s2.l.l3 & ~s1.l.l3);
    return (long long)((tmp << 32) | tmp) >= 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpandn (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp = __builtin_e2k_qplog (0xba, s2.u__v4di.v1, s1.u__v4di.v1, tmp); /* (s2 & ~s1) | s3 */
 #if __iset__ <= 5
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask & 0x8888) == 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND и ANDNOT 256-битных значений (по 8 флотов (32F)). Возвращает 1,
 * если знаки хоть одного из 8-ми флотов результата (src1 & src2) != 0 && (~src1 & src2) != 0. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vtestnzcps256 (__v8sf src1, __v8sf src2)
{
    type_union_256 s1, s2;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
#if __iset__ <= 4
    __di tmp1 = (s1.l.l0 &  s2.l.l0) | (s1.l.l1 &  s2.l.l1) |
                (s1.l.l2 &  s2.l.l2) | (s1.l.l3 &  s2.l.l3);
    __di tmp2 = (s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1) |
                (s2.l.l2 & ~s1.l.l2) | (s2.l.l3 & ~s1.l.l3);
    tmp1 |= tmp1 << 32;
    tmp2 |= tmp2 << 32;
    return (long long)(tmp1 & tmp2) < 0;
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qpand (s2.u__v4di.v0, s1.u__v4di.v0);
    __v2di tmp1 = __builtin_e2k_qpandn (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp0 = __builtin_e2k_qplog (0xea, s2.u__v4di.v1, s1.u__v4di.v1, tmp0); /* (s1 & s2) | s3 */
    tmp1 = __builtin_e2k_qplog (0xba, s2.u__v4di.v1, s1.u__v4di.v1, tmp1); /* (s2 & ~s1) | s3 */
 #if __iset__ <= 5
    int mask0 = __builtin_e2k_qpsgn2mskb (tmp0);
    int mask1 = __builtin_e2k_qpsgn2mskb (tmp1);
    return (mask0 & 0x8888) != 0 && (mask1 & 0x8888) != 0;
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp0)
        && __builtin_e2k_qpcmpgtwop (__builtin_e2k_qppackdl (0, 0), tmp1);
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND 256-битных значений. Возвращает 1, если (src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ptestz256 (__v4di src1, __v4di src2)
{
    type_union_256 s1, s2;
    s1.__v4di = src1;
    s2.__v4di = src2;
#if __iset__ <= 4
    return ((s1.l.l0 & s2.l.l0) | (s1.l.l1 & s2.l.l1) |
            (s1.l.l2 & s2.l.l2) | (s1.l.l3 & s2.l.l3)) == 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpand (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp = __builtin_e2k_qplog (0xea, s2.u__v4di.v1, s1.u__v4di.v1, tmp); /* (s1 & s2) | s3 */
 #if __iset__ <= 5
    tmp = __builtin_e2k_qpcmpeqb (tmp, __builtin_e2k_qppackdl (0, 0));
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask == 0xffff);
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (tmp, __builtin_e2k_qppackdl (0, 0));
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое ANDNOT 256-битных значений. Возвращает 1, если (~src1 & src2) == 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ptestc256 (__v4di src1, __v4di src2)
{
    type_union_256 s1, s2;
    s1.__v4di = src1;
    s2.__v4di = src2;
#if __iset__ <= 4
    return ((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1) |
            (s2.l.l2 & ~s1.l.l2) | (s2.l.l3 & ~s1.l.l3)) == 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpandn (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp = __builtin_e2k_qplog (0xba, s2.u__v4di.v1, s1.u__v4di.v1, tmp); /* (s2 & ~s1) | s3 */
 #if __iset__ <= 5
    tmp = __builtin_e2k_qpcmpeqb (tmp, __builtin_e2k_qppackdl (0, 0));
    int mask = __builtin_e2k_qpsgn2mskb (tmp);
    return (mask == 0xffff);
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (tmp, __builtin_e2k_qppackdl (0, 0));
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* логическое AND и ANDNOT 256-битных значений. Возвращает 1, если
 * (src1 & src2) != 0 && (~src1 & src2) != 0 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ptestnzc256 (__v4di src1, __v4di src2)
{
    type_union_256 s1, s2;
    s1.__v4di = src1;
    s2.__v4di = src2;
#if __iset__ <= 4
    return ((s1.l.l0 &  s2.l.l0) | (s1.l.l1 &  s2.l.l1) |
            (s1.l.l2 &  s2.l.l2) | (s1.l.l3 &  s2.l.l3)) != 0 &&
           ((s2.l.l0 & ~s1.l.l0) | (s2.l.l1 & ~s1.l.l1) |
            (s2.l.l2 & ~s1.l.l2) | (s2.l.l3 & ~s1.l.l3)) != 0;
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qpand (s2.u__v4di.v0, s1.u__v4di.v0);
    __v2di tmp1 = __builtin_e2k_qpandn (s2.u__v4di.v0, s1.u__v4di.v0);
    tmp0 = __builtin_e2k_qplog (0xea, s2.u__v4di.v1, s1.u__v4di.v1, tmp0); /* (s1 & s2) | s3 */
    tmp1 = __builtin_e2k_qplog (0xba, s2.u__v4di.v1, s1.u__v4di.v1, tmp1); /* (s2 & ~s1) | s3 */
 #if __iset__ <= 5
    tmp0 = __builtin_e2k_qpcmpeqb (tmp0, __builtin_e2k_qppackdl (0, 0));
    tmp1 = __builtin_e2k_qpcmpeqb (tmp1, __builtin_e2k_qppackdl (0, 0));
    int mask0 = __builtin_e2k_qpsgn2mskb (tmp0);
    int mask1 = __builtin_e2k_qpsgn2mskb (tmp1);
    return (mask0 != 0xffff && mask1 != 0xffff);
 #else /* __iset__ <= 5 */
    return __builtin_e2k_qpcmpeqbap (tmp0, __builtin_e2k_qppackdl (0, 0)) == 0
        && __builtin_e2k_qpcmpeqbap (tmp1, __builtin_e2k_qppackdl (0, 0)) == 0;
 #endif /* __iset__ <= 5 */
#endif /* __iset__ <= 4 */
}

/* *****************************************************************************
 *                               Выделение маски
 * *****************************************************************************/

/* формирование 4-разрядной маски из знаков каждого дабла (64F) */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movmskpd256 (__v4df src)
{
    type_union_256 s;
    s.__v4df = src;
    return __builtin_e2k_pmovmskpd (s.l.l1, s.l.l0) |
          (__builtin_e2k_pmovmskpd (s.l.l3, s.l.l2) << 2);
}

/* формирование 8-разрядной маски из знаков каждого флота (32F) */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movmskps256 (__v8sf src)
{
    type_union_256 s;
    s.__v8sf = src;
    return __builtin_e2k_pmovmskps (s.l.l1, s.l.l0) |
          (__builtin_e2k_pmovmskps (s.l.l3, s.l.l2) << 4);
}

/* *****************************************************************************
 *                          Преобразования 128 <-> 256 бит
 * *****************************************************************************/

/* Выдача младшей половины (2 дабла (64F)) 256-битного значения */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pd_pd256 (__v4df src)
{
    type_union_256 s;
    s.__v4df = src;
    return s.u__v4df.v0;
}

/* Выдача младшей половины (4 флота (32F)) 256-битного значения */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ps_ps256 (__v8sf src)
{
    type_union_256 s;
    s.__v8sf = src;
    return s.u__v8sf.v0;
}

/* Выдача младшей половины (4 инта (32S)) 256-битного значения */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_si_si256 (__v8si src)
{
    type_union_256 s;
    s.__v8si = src;
    return s.u__v8si.v0;
}

/* Младшая половина (2 дабла (64F)) 256-битного значения формируется из src.
 * Старшая половина не определена */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pd256_pd (__v2df src)
{
    type_union_256 dst;
    dst.u__v4df.v0 = src;
    return dst.__v4df;
}

/* Младшая половина (4 флота (32F)) 256-битного значения формируется из src.
 * Старшая половина не определена */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_ps256_ps (__v4sf src)
{
    type_union_256 dst;
    dst.u__v8sf.v0 = src;
    return dst.__v8sf;
}

/* Младшая половина (4 инта (32S)) 256-битного значения формируется из src.
 * Старшая половина не определена */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_si256_si (__v4si src)
{
    type_union_256 dst;
    dst.u__v8si.v0 = src;
    return dst.__v8si;
}

#undef PACKED_TWO_OPERAND_AVX_BUILTINS
#undef PACKED_TWO_OPERAND_AVX_BUILTINS_REVERSE
/*#undef TWO_OPERAND_AVX_BUILTINS_VIA_2SSE*/
/*#undef ONE_OPERAND_AVX_BUILTINS_VIA_2SSE*/
#undef CMP1
#undef CMP2
#undef CMP4
#undef CMP1EQ_UOD
#undef CMP2EQ_UOD
#undef CMP4EQ_UOD
#undef CMP1NEQ_OD
#undef CMP2NEQ_OD
#undef CMP4NEQ_OD
#undef FILL1
#undef FILL2
#undef FILL4
#undef CMP
#undef SELECT_32F
/*#undef SELECT_CONST_32F*/
#undef SELECT_CONST_128F

#endif /* __AVX__ */

#if defined (__FMA4__) || defined (__FMA__)

/*******************************************************************************/
/*************************** FMA4 & FMA builtins *******************************/
/*******************************************************************************/

#define FMA256_BUILTINS_VIA_FMA128(name,src_type,dst_type)                                           \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                                          \
__builtin_##name##256 (src_type src1, src_type src2, src_type src3)                                  \
{                                                                                                    \
    type_union_256 s1, s2, s3, dst;                                                                  \
    s1.src_type = src1;                                                                              \
    s2.src_type = src2;                                                                              \
    s3.src_type = src3;                                                                              \
    dst.u##dst_type.v0 = __builtin_##name (s1.u##src_type.v0, s2.u##src_type.v0, s3.u##src_type.v0); \
    dst.u##dst_type.v1 = __builtin_##name (s1.u##src_type.v1, s2.u##src_type.v1, s3.u##src_type.v1); \
    return dst.dst_type;                                                                             \
}

/* fmadd 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfmaddps (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    __di tmp0 = __builtin_e2k_pfadds (__builtin_e2k_pfmuls (s1.l.l0, s2.l.l0), s3.l.l0);
    __di tmp1 = __builtin_e2k_pfadds (__builtin_e2k_pfmuls (s1.l.l1, s2.l.l1), s3.l.l1);
    dst.l.l0 = tmp0;
    dst.l.l1 = tmp1;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfadds (__builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di), s3.__v2di);
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmas (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fmadd 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfmaddpd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s1.d.d0 * s2.d.d0 + s3.d.d0;
    dst.d.d1 = s1.d.d1 * s2.d.d1 + s3.d.d1;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfaddd (__builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di), s3.__v2di);
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmad (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fmadd младшего флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfmaddss (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.f.f0 = s1.f.f0 * s2.f.f0 + s3.f.f0;
    dst.f.f1 = dst.d.d1 = 0;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfadds (__builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di), s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmas (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fmadd младшего дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfmaddsd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s1.d.d0 * s2.d.d0 + s3.d.d0;
    dst.d.d1 = 0;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfaddd (__builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di), s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmad (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fmadd нечетных элементов и fmsub четных элементов из 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfmaddsubps (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = __builtin_e2k_pfadds (__builtin_e2k_pfmuls (s1.l.l0, s2.l.l0), s3.l.l0 ^ 0x80000000LL);
    dst.l.l1 = __builtin_e2k_pfadds (__builtin_e2k_pfmuls (s1.l.l1, s2.l.l1), s3.l.l1 ^ 0x80000000LL);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pfaddsubs  (__builtin_e2k_pfmuls (s1.l.l0, s2.l.l0), s3.l.l0);
    dst.l.l1 = __builtin_e2k_pfaddsubs  (__builtin_e2k_pfmuls (s1.l.l1, s2.l.l1), s3.l.l1);
 #endif /* __iset__ <= 2 */
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfaddsubs (__builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di), s3.__v2di);
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmsas (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fmadd нечетных элементов и fmsub четных элементов из 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfmaddsubpd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s1.d.d0 * s2.d.d0 - s3.d.d0;
    dst.d.d1 = s1.d.d1 * s2.d.d1 + s3.d.d1;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfaddsubd (__builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di), s3.__v2di);
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmsad (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fmadd 8-ми флотов (32F) */
FMA256_BUILTINS_VIA_FMA128 (ia32_vfmaddps, __v8sf, __v8sf)

/* fmadd 4-х даблов (64F) */
FMA256_BUILTINS_VIA_FMA128 (ia32_vfmaddpd, __v4df, __v4df)

/* fmadd нечетных элементов и fmsub четных элементов из 8-ми флотов (32F) */
FMA256_BUILTINS_VIA_FMA128 (ia32_vfmaddsubps, __v8sf, __v8sf)

/* fmadd нечетных элементов и fmsub четных элементов из 4-х даблов (64F) */
FMA256_BUILTINS_VIA_FMA128 (ia32_vfmaddsubpd, __v4df, __v4df)

/*******************************************************************************
 * E2K интринсики, поскольку lcc не умеет делать операции над векторными типами */
/*******************************************************************************/

/* fmsub 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfmsubps (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfsubs (__builtin_e2k_pfmuls (s1.l.l0, s2.l.l0), s3.l.l0);
    dst.l.l1 = __builtin_e2k_pfsubs (__builtin_e2k_pfmuls (s1.l.l1, s2.l.l1), s3.l.l1);
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubs (__builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di), s3.__v2di);
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmss (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fmsub 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfmsubpd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s1.d.d0 * s2.d.d0 - s3.d.d0;
    dst.d.d1 = s1.d.d1 * s2.d.d1 - s3.d.d1;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubd (__builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di), s3.__v2di);
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmsd (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fmsub младшего флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfmsubss (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.f.f0 = s1.f.f0 * s2.f.f0 - s3.f.f0;
    dst.f.f1 = dst.d.d1 = 0;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubs (__builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di), s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmss (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fmsub младшего дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfmsubsd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s1.d.d0 * s2.d.d0 - s3.d.d0;
    dst.d.d1 = 0;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubd (__builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di), s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmsd (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fnmadd 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmaddps (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfsubs (s3.l.l0, __builtin_e2k_pfmuls (s1.l.l0, s2.l.l0));
    dst.l.l1 = __builtin_e2k_pfsubs (s3.l.l1, __builtin_e2k_pfmuls (s1.l.l1, s2.l.l1));
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubs (s3.__v2di, __builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmas (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fnmadd 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmaddpd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s3.d.d0 - s1.d.d0 * s2.d.d0;
    dst.d.d1 = s3.d.d1 - s1.d.d1 * s2.d.d1;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubd (s3.__v2di, __builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmad (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fnmadd младшего флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmaddss (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.f.f0 = s3.f.f0 - s1.f.f0 * s2.f.f0;
    dst.f.f1 = dst.d.d1 = 0;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubs (s3.__v2di, __builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di));
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmas (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fnmadd младшего дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmaddsd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s3.d.d0 - s1.d.d0 * s2.d.d0;
    dst.d.d1 = 0;
#elif __iset__ <= 5
    dst.__v2di = __builtin_e2k_qpfsubd (s3.__v2di, __builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di));
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmad (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fnmsub 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmsubps (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfsubs (s3.l.l0 ^ 0x8000000080000000LL, __builtin_e2k_pfmuls (s1.l.l0, s2.l.l0));
    dst.l.l1 = __builtin_e2k_pfsubs (s3.l.l1 ^ 0x8000000080000000LL, __builtin_e2k_pfmuls (s1.l.l1, s2.l.l1));
#elif __iset__ <= 5
    __v2di tmp = __builtin_e2k_qpxor (s3.__v2di, __builtin_e2k_qppackdl (0x8000000080000000LL, 0x8000000080000000LL));
    dst.__v2di = __builtin_e2k_qpfsubs (tmp, __builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmss (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fnmsub 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmsubpd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = -s3.d.d0 - s1.d.d0 * s2.d.d0;
    dst.d.d1 = -s3.d.d1 - s1.d.d1 * s2.d.d1;
#elif __iset__ <= 5
    __v2di tmp = __builtin_e2k_qpxor (s3.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL));
    dst.__v2di = __builtin_e2k_qpfsubd (tmp, __builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmsd (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fnmsub младшего флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmsubss (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.f.f0 = -s3.f.f0 - s1.f.f0 * s2.f.f0;
    dst.f.f1 = dst.d.d1 = 0;
#elif __iset__ <= 5
    __v2di tmp = __builtin_e2k_qpxor (s3.__v2di, __builtin_e2k_qppackdl (0x8000000080000000LL, 0x8000000080000000LL));
    dst.__v2di = __builtin_e2k_qpfsubs (tmp, __builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di));
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmss (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, 0xffffffff));
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fnmsub младшего дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfnmsubsd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = -s3.d.d0 - s1.d.d0 * s2.d.d0;
    dst.d.d1 = 0;
#elif __iset__ <= 5
    __v2di tmp = __builtin_e2k_qpxor (s3.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL));
    dst.__v2di = __builtin_e2k_qpfsubd (tmp, __builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di));
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfnmsd (s1.__v2di, s2.__v2di, s3.__v2di);
    dst.__v2di = __builtin_e2k_qpand (dst.__v2di, __builtin_e2k_qppackdl (0, -1LL));
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fmadd четных элементов и fmsub нечетных элементов из 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfmsubaddps (__v4sf src1, __v4sf src2, __v4sf src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    s3.__v4sf = src3;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pfadds (__builtin_e2k_pfmuls (s1.l.l0, s2.l.l0), s3.l.l0 ^ 0x8000000000000000LL);
    dst.l.l1 = __builtin_e2k_pfadds (__builtin_e2k_pfmuls (s1.l.l1, s2.l.l1), s3.l.l1 ^ 0x8000000000000000LL);
#elif __iset__ <= 5
    __v2di tmp = __builtin_e2k_qpxor (s3.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL));
    dst.__v2di = __builtin_e2k_qpfadds (tmp, __builtin_e2k_qpfmuls (s1.__v2di, s2.__v2di));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmass (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v4sf;
}

/* fmadd четных элементов и fmsub нечетных элементов из 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_e2k_vfmsubaddpd (__v2df src1, __v2df src2, __v2df src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    s3.__v2df = src3;
#if __iset__ <= 4
    dst.d.d0 = s1.d.d0 * s2.d.d0 + s3.d.d0;
    dst.d.d1 = s1.d.d1 * s2.d.d1 - s3.d.d1;
#elif __iset__ <= 5
    __v2di tmp = __builtin_e2k_qpxor (s3.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0LL));
    dst.__v2di = __builtin_e2k_qpfaddd (tmp, __builtin_e2k_qpfmuld (s1.__v2di, s2.__v2di));
#else /* __iset__ <= 5 */
    dst.__v2di = __builtin_e2k_qpfmasd (s1.__v2di, s2.__v2di, s3.__v2di);
#endif /* __iset__ <= 5 */
    return dst.__v2df;
}

/* fmsub 8-ми флотов (32F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfmsubps, __v8sf, __v8sf)

/* fmsub 4-х даблов (64F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfmsubpd, __v4df, __v4df)

/* fnmadd 8-ми флотов (32F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfnmaddps, __v8sf, __v8sf)

/* fnmadd 4-х даблов (64F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfnmaddpd, __v4df, __v4df)

/* fnmsub 8-ми флотов (32F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfnmsubps, __v8sf, __v8sf)

/* fnmsub 4-х даблов (64F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfnmsubpd, __v4df, __v4df)

/* fmadd четных элементов и fmsub нечетных элементов из 8-ми флотов (32F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfmsubaddps, __v8sf, __v8sf)

/* fmadd четных элементов и fmsub нечетных элементов из 4-х даблов (64F) */
FMA256_BUILTINS_VIA_FMA128 (e2k_vfmsubaddpd, __v4df, __v4df)

#undef FMA256_BUILTINS_VIA_FMA128

#endif /* defined (__FMA4__) || defined (__FMA__) */

#ifdef __FMA__

/*******************************************************************************/
/******************************* FMA builtins **********************************/
/*******************************************************************************/

#define __builtin_ia32_vfmaddsd3 __builtin_ia32_vfmaddsd
#define __builtin_ia32_vfmaddss3 __builtin_ia32_vfmaddss

#endif /* __FMA__ */

#ifdef __XOP__

/*******************************************************************************/
/******************************* XOP builtins **********************************/
/*******************************************************************************/

/* *****************************************************************************
 *                          Целые умножения со сложением
 * *****************************************************************************/

#if __iset__ <= 4

#define MULADD_SAT_16S(src1, src2, src3, dst) {                                                   \
    __di tmp_hi = __builtin_e2k_pmaddh (__builtin_e2k_pshufb (1, src1, 0x0706800805048008LL),     \
                                        __builtin_e2k_pshufb (src2, src3, 0x0f0e07060d0c0504LL)); \
    __di tmp_lo = __builtin_e2k_pmaddh (__builtin_e2k_pshufb (1, src1, 0x0302800801008008LL),     \
                                        __builtin_e2k_pshufb (src2, src3, 0x0b0a030209080100LL)); \
    dst = __builtin_e2k_packsswh (tmp_hi, tmp_lo);                                                \
}

#else /* __iset__ <= 4 */

#define MULADD_SAT_16S(src1, src2, src3, dst) {                                                              \
    __v2di tmp_lo = __builtin_e2k_qpmaddh (__builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 1), src1,       \
                                      __builtin_e2k_qppackdl (0x0706111005041110LL, 0x0302111001001110LL)),  \
                                        __builtin_e2k_qppermb (src2, src3,                                   \
                                      __builtin_e2k_qppackdl (0x1716070615140504LL, 0x1312030211100100LL))); \
    __v2di tmp_hi = __builtin_e2k_qpmaddh (__builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 1), src1,       \
                                      __builtin_e2k_qppackdl (0x0f0e11100d0c1110LL, 0x0b0a111009081110LL)),  \
                                        __builtin_e2k_qppermb (src2, src3,                                   \
                                      __builtin_e2k_qppackdl (0x1f1e0f0e1d1c0d0cLL, 0x1b1a0b0a19180908LL))); \
    dst = __builtin_e2k_qpacksswh (tmp_hi, tmp_lo);                                                          \
}

#endif /* __iset__ <= 4 */

/* mac 8-ми шортов (16S) c сатурацией */
__E2K_INLINE __E2K_WARNING (__v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacssww (__v8hi src1, __v8hi src2, __v8hi src3))
{
    type_union_128 s1, s2, s3, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
    s3.__v8hi = src3;
#if __iset__ <= 4
    MULADD_SAT_16S (s1.l.l0, s2.l.l0, s3.l.l0, dst.l.l0);
    MULADD_SAT_16S (s1.l.l1, s2.l.l1, s3.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    MULADD_SAT_16S (s1.__v2di, s2.__v2di, s3.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* mac 8-ми шортов (16S) по модулю */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacsww (__v8hi src1, __v8hi src2, __v8hi src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
    s3.__v8hi = src3;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_paddh (__builtin_e2k_pmullh (s1.l.l0, s2.l.l0), s3.l.l0);
    dst.l.l1 = __builtin_e2k_paddh (__builtin_e2k_pmullh (s1.l.l1, s2.l.l1), s3.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpaddh (__builtin_e2k_qpmullh  (s1.__v2di, s2.__v2di), s3.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

#if __iset__ <= 4

#define MULADD_SAT_16S_32S(src1, src2, src3, dst) {                                \
    __di mul, mask, sat;                                                           \
    mul = __builtin_e2k_pmaddh (src1 & 0xffff0000ffffLL, src2 & 0xffff0000ffffLL); \
    dst = __builtin_e2k_paddw (mul, src3);                                         \
    /* сатурация для интового сложения */                                          \
    mask = __builtin_e2k_psraw ((mul ^ dst) & ~(mul ^ src3), 31);                  \
    sat = __builtin_e2k_psraw (mul, 31) ^ 0x7fffffff7fffffffLL;                    \
    dst = __builtin_e2k_pmerge (dst, sat, mask);                                   \
}

#else /* __iset__ <= 4 */

#define MULADD_SAT_16S_32S(src1, src2, src3, dst) {                                         \
    __v2di mul, mask, sat, tmp1, tmp2;                                                      \
    tmp1 = __builtin_e2k_qpand (src1, __builtin_e2k_qppackdl (0xffff0000ffffLL, 0xffff0000ffffLL));       \
    tmp2 = __builtin_e2k_qpand (src2, __builtin_e2k_qppackdl (0xffff0000ffffLL, 0xffff0000ffffLL));       \
    mul = __builtin_e2k_qpmaddh (tmp1, tmp2);                                               \
    dst = __builtin_e2k_qpaddw (mul, src3);                                                 \
    /* сатурация для интового сложения */                                                   \
    tmp1 = __builtin_e2k_qplog (0x24, mul, dst, src3); /* (mul ^ dst) & (mul ^ ~src3) */    \
    mask = __builtin_e2k_qpsraw (tmp1, 31);                                                 \
    sat = __builtin_e2k_qpsraw (mul, 31);                                                   \
    sat = __builtin_e2k_qpxor (sat, __builtin_e2k_qppackdl (0x7fffffff7fffffffLL, 0x7fffffff7fffffffLL)); \
    dst = __builtin_e2k_qpmerge (dst, sat, mask);                                           \
}

#endif /* __iset__ <= 4 */

/* умножение 4-х четных шортов (16S) в инты (32S) и сложение с интами c сатурацией */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacsswd (__v8hi src1, __v8hi src2, __v4si src3))
{
    type_union_128 s1, s2, s3, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
    s3.__v4si = src3;
#if __iset__ <= 4
    MULADD_SAT_16S_32S (s1.l.l0, s2.l.l0, s3.l.l0, dst.l.l0);
    MULADD_SAT_16S_32S (s1.l.l1, s2.l.l1, s3.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    MULADD_SAT_16S_32S (s1.__v2di, s2.__v2di, s3.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

#if __iset__ <= 4

#define MULADD_MOD_16S_32S(src1, src2, src3, dst) {                                        \
    dst = __builtin_e2k_paddw (__builtin_e2k_pmaddh (src1 & 0xffff0000ffffLL, src2 & 0xffff0000ffffLL), src3); \
}

#else /* __iset__ <= 4 */

#define MULADD_MOD_16S_32S(src1, src2, src3, dst) {                                          \
    __v2di tmp1 = __builtin_e2k_qpand (src1, __builtin_e2k_qppackdl (0xffff0000ffffLL, 0xffff0000ffffLL)); \
    __v2di tmp2 = __builtin_e2k_qpand (src2, __builtin_e2k_qppackdl (0xffff0000ffffLL, 0xffff0000ffffLL)); \
    dst = __builtin_e2k_qpaddw (__builtin_e2k_qpmaddh (tmp1, tmp2), src3);                   \
}

#endif /* __iset__ <= 4 */

/* умножение 4-х четных шортов (16S) в инты (32S) и сложение с интами по модулю */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacswd (__v8hi src1, __v8hi src2, __v4si src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
    s3.__v4si = src3;
#if __iset__ <= 4
    MULADD_MOD_16S_32S (s1.l.l0, s2.l.l0, s3.l.l0, dst.l.l0);
    MULADD_MOD_16S_32S (s1.l.l1, s2.l.l1, s3.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    MULADD_MOD_16S_32S (s1.__v2di, s2.__v2di, s3.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

#define MULADD_SAT_32S(src1, src2, src3, dst) {                                                                 \
    long long mul1, mul0;                                                                                       \
    mul1 = __builtin_e2k_smulx (((long long) src1 >> 32), ((long long) src2 >> 32)) + ((long long) src3 >> 32); \
    mul0 = __builtin_e2k_smulx (src1, src2) + (((long long) src3 << 32) >> 32);                                 \
    mul1 = (mul1 > (long long) 0x7fffffffLL) ? 0x7fffffffLL :                                                   \
           (mul1 < (long long) 0xffffffff80000000LL) ? 0xffffffff80000000LL : mul1;                             \
    mul0 = (mul0 > (long long) 0x7fffffffLL) ? 0x7fffffffLL :                                                   \
           (mul0 < (long long) 0xffffffff80000000LL) ? 0xffffffff80000000LL : mul0;                             \
    dst = (mul1 << 32) | (mul0 & 0xffffffffLL);                                                                 \
}

/* mac 4-х интов (32S) c сатурацией */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacssdd (__v4si src1, __v4si src2, __v4si src3))
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    s3.__v4si = src3;
    MULADD_SAT_32S (s1.l.l0, s2.l.l0, s3.l.l0, dst.l.l0);
    MULADD_SAT_32S (s1.l.l1, s2.l.l1, s3.l.l1, dst.l.l1);
    return dst.__v4si;
}

#if __iset__ <= 4

#define MULADD_MOD_32S(src1, src2, src3, dst) {                                        \
    __di mul1, mul0;                                                                   \
    mul1 = (src1 & ~0xffffffffLL) * ((long long) src2 >> 32) + (src3 & ~0xffffffffLL); \
    mul0 = src1 * src2 + src3;                                                         \
    dst = mul1 | (mul0 & 0xffffffffLL);                                                \
}

#else /* __iset__ <= 4 */

#define MULADD_MOD_32S(src1, src2, src3, dst) \
    dst = __builtin_e2k_qpaddw (__builtin_e2k_qpmullw (src1, src2), src3)

#endif /* __iset__ <= 4 */

/* mac 4-х интов (32S) по модулю */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacsdd (__v4si src1, __v4si src2, __v4si src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    s3.__v4si = src3;
#if __iset__ <= 4
    MULADD_MOD_32S (s1.l.l0, s2.l.l0, s3.l.l0, dst.l.l0);
    MULADD_MOD_32S (s1.l.l1, s2.l.l1, s3.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    MULADD_MOD_32S (s1.__v2di, s2.__v2di, s3.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

#define MULADD_SAT_32S_64S(src1, src2, src3, dst) {                                                 \
    long long mul, mask;                                                                            \
    mul = __builtin_e2k_smulx (src1, src2);                                                         \
    dst = mul + src3;                                                                               \
    mask = (mul ^ dst) & (mul ^ ~src3);                                                             \
    dst = (mask < 0) ? (((long long) dst < 0) ? 0x7fffffffffffffffLL : 0x8000000000000000LL) : dst; \
}

/* умножение 2-х четных интов (32S) в лонги (64S) и сложение с лонгами c сатурацией */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacssdql (__v4si src1, __v4si src2, __v2di src3))
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    s3.__v2di = src3;
    MULADD_SAT_32S_64S (s1.l.l0, s2.l.l0, s3.l.l0, dst.l.l0);
    MULADD_SAT_32S_64S (s1.l.l1, s2.l.l1, s3.l.l1, dst.l.l1);
    return dst.__v2di;
}

/* умножение 2-х четных интов (32S) в лонги (64S) и сложение с лонгами по модулю */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacsdql (__v4si src1, __v4si src2, __v2di src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    s3.__v2di = src3;
    dst.l.l0 = __builtin_e2k_smulx (s1.l.l0, s2.l.l0) + s3.l.l0;
    dst.l.l1 = __builtin_e2k_smulx (s1.l.l1, s2.l.l1) + s3.l.l1;
    return dst.__v2di;
}

/* умножение 2-х нечетных интов (32S) в лонги (64S) и сложение с лонгами c сатурацией */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacssdqh (__v4si src1, __v4si src2, __v2di src3))
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    s3.__v2di = src3;
    MULADD_SAT_32S_64S (s1.l.l0 >> 32, s2.l.l0 >> 32, s3.l.l0, dst.l.l0);
    MULADD_SAT_32S_64S (s1.l.l1 >> 32, s2.l.l1 >> 32, s3.l.l1, dst.l.l1);
    return dst.__v2di;
}

/* умножение 2-х нечетных интов (32S) в лонги (64S) и сложение с лонгами по модулю */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmacsdqh (__v4si src1, __v4si src2, __v2di src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    s3.__v2di = src3;
    dst.l.l0 = __builtin_e2k_smulx (s1.l.l0 >> 32, s2.l.l0 >> 32) + s3.l.l0;
    dst.l.l1 = __builtin_e2k_smulx (s1.l.l1 >> 32, s2.l.l1 >> 32) + s3.l.l1;
    return dst.__v2di;
}

#if __iset__ <= 4

#define MULADDHOR_SAT_16S_32S(src1, src2, src3, dst) {                                  \
    __di mul, over, mask, sat, tmp;                                                     \
    mul = __builtin_e2k_pmaddh (src1, src2);                                            \
    over = __builtin_e2k_pcmpeqw (mul, 0x8000000080000000LL); /* было переполнение */   \
    mul = __builtin_e2k_paddw (mul, over); /* вычитание 1 при переполнении */           \
    /* прибавление 1 к src3 при переполнении и если src3 != 0x7fffffff */               \
    tmp = __builtin_e2k_psubw (src3, over & ~__builtin_e2k_pcmpeqw (src3, 0x7fffffff7fffffffLL)); \
    dst = __builtin_e2k_paddw (mul, tmp);                                               \
    /* сатурация для интового сложения */                                               \
    mask = __builtin_e2k_psraw ((mul ^ dst) & ~(mul ^ tmp), 31);                        \
    sat = __builtin_e2k_psraw (mul, 31) ^ 0x7fffffff7fffffffLL;                         \
    dst = (dst & ~mask) | (sat & mask);                                                 \
}

#else /* __iset__ <= 4 */

#define MULADDHOR_SAT_16S_32S(src1, src2, src3, dst) {                                      \
    __v2di mul, over, mask, sat, tmp0, tmp1;                                                \
    mul = __builtin_e2k_qpmaddh (src1, src2);                                               \
    over = __builtin_e2k_qpcmpeqw (mul, __builtin_e2k_qppackdl (0x8000000080000000LL, 0x8000000080000000LL)); /* было переполнение */\
    mul = __builtin_e2k_qpaddw (mul, over); /* вычитание 1 при переполнении */              \
    /* прибавление 1 к src3 при переполнении и если src3 != 0x7fffffff */                   \
    tmp0 = __builtin_e2k_qpcmpeqw (src3, __builtin_e2k_qppackdl (0x7fffffff7fffffffLL, 0x7fffffff7fffffffLL)); \
    tmp0 = __builtin_e2k_qpsubw (src3, __builtin_e2k_qpandn (over, tmp0));                  \
    dst = __builtin_e2k_qpaddw (mul, tmp0);                                                 \
    /* сатурация для интового сложения */                                                   \
    tmp1 = __builtin_e2k_qplog (0x24, mul, dst, src3); /* (mul ^ dst) & (mul ^ ~tmp0) */    \
    mask = __builtin_e2k_qpsraw (tmp1, 31);                                                 \
    sat = __builtin_e2k_qpsraw (mul, 31);                                                   \
    sat = __builtin_e2k_qpxor (sat, __builtin_e2k_qppackdl (0x7fffffff7fffffffLL, 0x7fffffff7fffffffLL)); \
    dst = __builtin_e2k_qpmerge (dst, sat, mask);                                           \
}

#endif /* __iset__ <= 4 */

/* умножение 8-ми шортов (16S) в инты (32S), сложение смежных произведений и
 * сложение с интами c сатурацией */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmadcsswd (__v8hi src1, __v8hi src2, __v4si src3))
{
    type_union_128 s1, s2, s3, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
    s3.__v4si = src3;
#if __iset__ <= 4
    MULADDHOR_SAT_16S_32S (s1.l.l0, s2.l.l0, s3.l.l0, dst.l.l0);
    MULADDHOR_SAT_16S_32S (s1.l.l1, s2.l.l1, s3.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    MULADDHOR_SAT_16S_32S (s1.__v2di, s2.__v2di, s3.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* умножение 8-ми шортов (16S) в инты (32S), сложение смежных произведений и
 * сложение с интами по модулю */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpmadcswd (__v8hi src1, __v8hi src2, __v4si src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
    s3.__v4si = src3;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_paddw (__builtin_e2k_pmaddh (s1.l.l0, s2.l.l0), s3.l.l0);
    dst.l.l1 = __builtin_e2k_paddw (__builtin_e2k_pmaddh (s1.l.l1, s2.l.l1), s3.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpaddw (__builtin_e2k_qpmaddh (s1.__v2di, s2.__v2di), s3.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* *****************************************************************************
 *                  Целые горизонтальные сложения/вычитания
 * *****************************************************************************/

/* сложение 8-ми пар соседних знаковых байт (8S) с получением знаковых шортов (16S) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddbw (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = __builtin_e2k_paddh (__builtin_e2k_psrah (s.l.l0, 8), __builtin_e2k_psrah (s.l.l0 << 8, 8));
    dst.l.l1 = __builtin_e2k_paddh (__builtin_e2k_psrah (s.l.l1, 8), __builtin_e2k_psrah (s.l.l1 << 8, 8));
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pmaddubsh (s.l.l0, 0x0101010101010101LL);
    dst.l.l1 = __builtin_e2k_pmaddubsh (s.l.l1, 0x0101010101010101LL);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaddubsh (s.__v2di, __builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сложение 4-х наборов из 4-х соседних знаковых байт (8S) с получением знаковых интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddbd (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_paddh (__builtin_e2k_psrah (s.l.l0, 8), __builtin_e2k_psrah (s.l.l0 << 8, 8));
    __di tmp1 = __builtin_e2k_paddh (__builtin_e2k_psrah (s.l.l1, 8), __builtin_e2k_psrah (s.l.l1 << 8, 8));
 #else /* __iset__ <= 2 */
    __di tmp0 = __builtin_e2k_pmaddubsh (s.l.l0, 0x0101010101010101LL);
    __di tmp1 = __builtin_e2k_pmaddubsh (s.l.l1, 0x0101010101010101LL);
 #endif /* __iset__ <= 3 */
    dst.l.l0 = __builtin_e2k_pmaddh (tmp0, 0x1000100010001LL);
    dst.l.l1 = __builtin_e2k_pmaddh (tmp1, 0x1000100010001LL);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpmaddubsh (s.__v2di, __builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL));
    dst.__v2di = __builtin_e2k_qpmaddh (tmp, __builtin_e2k_qppackdl (0x1000100010001LL, 0x1000100010001LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сложение 2-х наборов из 8-ми соседних знаковых байт (8S) с получением знаковых лонгов (64S) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddbq (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = __builtin_e2k_paddh (__builtin_e2k_psrah (s.l.l0, 8), __builtin_e2k_psrah (s.l.l0 << 8, 8));
    __di tmp1 = __builtin_e2k_paddh (__builtin_e2k_psrah (s.l.l1, 8), __builtin_e2k_psrah (s.l.l1 << 8, 8));
    tmp0 = __builtin_e2k_pmaddh (tmp0, 0x1000100010001LL);
    tmp1 = __builtin_e2k_pmaddh (tmp1, 0x1000100010001LL);
    dst.l.l0 = (long long) (tmp0 + (tmp0 << 32)) >> 32;
    dst.l.l1 = (long long) (tmp1 + (tmp1 << 32)) >> 32;
 #elif __iset__ <= 3
    __di tmp0 = __builtin_e2k_pmaddubsh (s.l.l0, 0x0101010101010101LL);
    __di tmp1 = __builtin_e2k_pmaddubsh (s.l.l1, 0x0101010101010101LL);
    tmp0 = __builtin_e2k_phaddh (tmp0, tmp1);
    tmp0 = __builtin_e2k_phaddh (tmp0, tmp0);
    __di tmp2 = __builtin_e2k_pcmpgth (0, tmp0);
    dst.l.l1 = __builtin_e2k_pshufb (tmp2, tmp0, 0x0b0b0b0b0b0b0302LL);
    dst.l.l0 = __builtin_e2k_pshufb (tmp2, tmp0, 0x0909090909090100LL);
 #else /* __iset__ <= 3 */
    __di tmp0 = __builtin_e2k_pmaddubsh (s.l.l0, 0x0101010101010101LL);
    __di tmp1 = __builtin_e2k_pmaddubsh (s.l.l1, 0x0101010101010101LL);
    tmp0 = __builtin_e2k_phaddh (tmp0, tmp1);
    tmp0 = __builtin_e2k_phaddh (tmp0, tmp0);
    dst.l.l1 = __builtin_e2k_pshufb (tmp0, tmp0, 0x4343434343430302LL);
    dst.l.l0 = __builtin_e2k_pshufb (tmp0, tmp0, 0x4141414141410100LL);
 #endif /* __iset__ <= 3 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpmaddubsh (s.__v2di, __builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL));
    tmp = __builtin_e2k_qphaddh (tmp, tmp);
    tmp = __builtin_e2k_qphaddh (tmp, tmp);
    dst.__v2di = __builtin_e2k_qppermb (tmp, tmp, __builtin_e2k_qppackdl (0x8383838383830302LL, 0x8181818181810100LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сложение 4-х пар соседних знаковых шортов (16S) с получением знаковых интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddwd (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pmaddh (s.l.l0, 0x1000100010001LL);
    dst.l.l1 = __builtin_e2k_pmaddh (s.l.l1, 0x1000100010001LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaddh (s.__v2di, __builtin_e2k_qppackdl (0x1000100010001LL, 0x1000100010001LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сложение 2-х наборов из 4-х соседних знаковых шортов (16S) с получением знаковых лонгов (64S) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddwq (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    __di tmp0 = __builtin_e2k_pmaddh (s.l.l0, 0x1000100010001LL);
    __di tmp1 = __builtin_e2k_pmaddh (s.l.l1, 0x1000100010001LL);
 #if __iset__ <= 3
    dst.l.l0 = (long long) (tmp0 + (tmp0 << 32)) >> 32;
    dst.l.l1 = (long long) (tmp1 + (tmp1 << 32)) >> 32;
 #else /* __iset__ <= 3 */
    tmp0 = __builtin_e2k_phaddw (tmp0, tmp1);
    dst.l.l1 = __builtin_e2k_pshufb (tmp0, tmp0, 0x4747474707060504LL);
    dst.l.l0 = __builtin_e2k_pshufb (tmp0, tmp0, 0x4343434303020100LL);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpmaddh (s.__v2di, __builtin_e2k_qppackdl (0x1000100010001LL, 0x1000100010001LL));
    tmp = __builtin_e2k_qphaddw (tmp, tmp);
    dst.__v2di = __builtin_e2k_qppermb (tmp, tmp, __builtin_e2k_qppackdl (0x8787878707060504LL, 0x8383838303020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сложение 2-х пар соседних знаковых интов (32S) с получением знаковых лонгов (64S) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphadddq (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l0 = ((long long) s.l.l0 >> 32) + ((long long) (s.l.l0 << 32) >> 32);
    dst.l.l1 = ((long long) s.l.l1 >> 32) + ((long long) (s.l.l1 << 32) >> 32);
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di, __builtin_e2k_qppackdl (0x8b8b8b8b0b0a0908LL, 0x8383838303020100LL));
    __v2di tmp1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di, __builtin_e2k_qppackdl (0x8f8f8f8f0f0e0d0cLL, 0x8787878707060504LL));
    dst.__v2di = __builtin_e2k_qpaddd (tmp0, tmp1);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сложение 8-ми пар соседних беззнаковых байт (8U) с получением беззнаковых шортов (16U) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddubw (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = (s.l.l0 & 0xff00ff00ff00ffLL) + ((s.l.l0 >> 8) & 0xff00ff00ff00ffLL);
    dst.l.l1 = (s.l.l1 & 0xff00ff00ff00ffLL) + ((s.l.l1 >> 8) & 0xff00ff00ff00ffLL);
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pmaddubsh (0x0101010101010101LL, s.l.l0);
    dst.l.l1 = __builtin_e2k_pmaddubsh (0x0101010101010101LL, s.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaddubsh (__builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL), s.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сложение 4-х наборов из 4-х соседних беззнаковых байт (8U) с получением беззнаковых интов (32U) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddubd (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
 #if __iset__ <= 2
    __di tmp0 = (s.l.l0 & 0xff00ff00ff00ffLL) + ((s.l.l0 >> 8) & 0xff00ff00ff00ffLL);
    __di tmp1 = (s.l.l1 & 0xff00ff00ff00ffLL) + ((s.l.l1 >> 8) & 0xff00ff00ff00ffLL);
 #else /* __iset__ <= 2 */
    __di tmp0 = __builtin_e2k_pmaddubsh (0x0101010101010101LL, s.l.l0);
    __di tmp1 = __builtin_e2k_pmaddubsh (0x0101010101010101LL, s.l.l1);
 #endif /* __iset__ <= 3 */
    dst.l.l0 = __builtin_e2k_pmaddh (tmp0, 0x1000100010001LL);
    dst.l.l1 = __builtin_e2k_pmaddh (tmp1, 0x1000100010001LL);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpmaddubsh (__builtin_e2k_qppackdl (0x0101010101010101LL, 0x0101010101010101LL), s.__v2di);
    dst.__v2di = __builtin_e2k_qpmaddh (tmp, __builtin_e2k_qppackdl (0x1000100010001LL, 0x1000100010001LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сложение 2-х наборов из 8-ми соседних беззнаковых байт (8U) с получением беззнаковых лонгов (64U) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddubq (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_psadbw (s.l.l0, 0);
    dst.l.l1 = __builtin_e2k_psadbw (s.l.l1, 0);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsadbw (s.__v2di, __builtin_e2k_qppackdl (0, 0));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сложение 4-х пар соседних беззнаковых шортов (16U) с получением беззнаковых интов (32U) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphadduwd (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_psrlw (s.l.l0, 16) + (s.l.l0 & 0xffff0000ffffLL);
    dst.l.l1 = __builtin_e2k_psrlw (s.l.l1, 16) + (s.l.l1 & 0xffff0000ffffLL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpaddw (__builtin_e2k_qpsrlw (s.__v2di, 16),
        __builtin_e2k_qpshufb (s.__v2di, s.__v2di, __builtin_e2k_qppackdl (0x80800d0c80800908LL, 0x8080050480800100LL)));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сложение 2-х наборов из 4-х соседних беззнаковых шортов (16U) с получением беззнаковых лонгов (64U) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphadduwq (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    __di tmp0 = __builtin_e2k_psrlw (s.l.l0, 16) + (s.l.l0 & 0xffff0000ffffLL);
    __di tmp1 = __builtin_e2k_psrlw (s.l.l1, 16) + (s.l.l1 & 0xffff0000ffffLL);
 #if __iset__ <= 2
    dst.l.l0 = (tmp0 & 0xffffffffLL) + (tmp0 >> 32);
    dst.l.l1 = (tmp1 & 0xffffffffLL) + (tmp1 >> 32);
 #else /* __iset__ <= 3 */
    tmp0 = __builtin_e2k_phaddw (tmp0, tmp1);
    dst.l.l1 = tmp0 >> 32;
    dst.l.l0 = tmp0 & 0xffffffffLL;
 #endif /* __iset__ <= 3 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpaddd (__builtin_e2k_qpsrlw (s.__v2di, 16),
        __builtin_e2k_qpand (s.__v2di, __builtin_e2k_qppackdl (0xffff0000ffffLL, 0xffff0000ffffLL)));
    tmp = __builtin_e2k_qphaddw (tmp, tmp);
    dst.__v2di = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), tmp,
                                        __builtin_e2k_qppackdl (0x1010101007060504LL, 0x1010101003020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сложение 2-х пар соседних беззнаковых (32U) с получением беззнаковыховых лонгов (64U) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphaddudq (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l0 = (s.l.l0 >> 32) + (s.l.l0 & 0xffffffffLL);
    dst.l.l1 = (s.l.l1 >> 32) + (s.l.l1 & 0xffffffffLL);
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di, __builtin_e2k_qppackdl (0x101010100b0a0908LL, 0x1010101003020100LL));
    __v2di tmp1 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di, __builtin_e2k_qppackdl (0x101010100f0e0d0cLL, 0x1010101007060504LL));
    dst.__v2di = __builtin_e2k_qpaddd (tmp0, tmp1);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* вычитание 8-ми пар соседних знаковых байт (8S) с получением знаковых шортов (16S) */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphsubbw (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = __builtin_e2k_psubh (__builtin_e2k_psrah (s.l.l0 << 8, 8), __builtin_e2k_psrah (s.l.l0, 8));
    dst.l.l1 = __builtin_e2k_psubh (__builtin_e2k_psrah (s.l.l1 << 8, 8), __builtin_e2k_psrah (s.l.l1, 8));
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pmaddubsh (0xff01ff01ff01ff01LL, s.l.l0 ^ 0x8080808080808080LL);
    dst.l.l1 = __builtin_e2k_pmaddubsh (0xff01ff01ff01ff01LL, s.l.l1 ^ 0x8080808080808080LL);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpxor (s.__v2di, __builtin_e2k_qppackdl (0x8080808080808080LL, 0x8080808080808080LL));
    dst.__v2di = __builtin_e2k_qpmaddubsh (__builtin_e2k_qppackdl (0xff01ff01ff01ff01LL, 0xff01ff01ff01ff01LL), tmp);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* вычитание 4-х пар соседних знаковых шортов (16S) с получением знаковых интов (32S) */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphsubwd (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pmaddh (s.l.l0, 0xffff0001ffff0001LL);
    dst.l.l1 = __builtin_e2k_pmaddh (s.l.l1, 0xffff0001ffff0001LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpmaddh (s.__v2di, __builtin_e2k_qppackdl (0xffff0001ffff0001LL, 0xffff0001ffff0001LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* вычитание 2-х пар соседних знаковых интов (32S) с получением знаковых лонгов (64S) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vphsubdq (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l0 = ((long long) (s.l.l0 << 32) >> 32) - ((long long) s.l.l0 >> 32);
    dst.l.l1 = ((long long) (s.l.l1 << 32) >> 32) - ((long long) s.l.l1 >> 32);
#else /* __iset__ <= 4 */
    __v2di tmp0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di, __builtin_e2k_qppackdl (0x8b8b8b8b0b0a0908LL, 0x8383838303020100LL));
    __v2di tmp1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di, __builtin_e2k_qppackdl (0x8f8f8f8f0f0e0d0cLL, 0x8787878707060504LL));
    dst.__v2di = __builtin_e2k_qpsubd (tmp0, tmp1);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* *****************************************************************************
 *                  Условные слияния и перестановки
 * *****************************************************************************/

/* выбор бит из src1 или src2 в зависимости от значения соответствующего бита в src3 */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcmov (__v2di src1, __v2di src2, __v2di src3)
{
    type_union_128 s1, s2, s3, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    s3.__v2di = src3;
#if __iset__ <= 4
    dst.l.l0 = (s1.l.l0 & s3.l.l0) | (s2.l.l0 & ~s3.l.l0);
    dst.l.l1 = (s1.l.l1 & s3.l.l1) | (s2.l.l1 & ~s3.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qplog (228, s1.__v2di, s2.__v2di, s3.__v2di); /* (s1 & s3) | (s2 & ~s3) */
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

#if __iset__ <= 3

#define VPPERM(src1h, src1l, src2h, src2l, src3, dst) {                                                 \
    __di src11, src22, mask, maski, maskz, maskr, masks, rev, sgn;                                      \
    mask = __builtin_e2k_pcmpgtb (0, src3 << 3);                                                        \
    src11 = __builtin_e2k_pshufb (src1h, src1l, src3 & 0x0f0f0f0f0f0f0f0fLL);                           \
    src22 = __builtin_e2k_pshufb (src2h, src2l, src3 & 0x0f0f0f0f0f0f0f0fLL);                           \
    dst = __builtin_e2k_pmerge (src11, src22, mask);      /* select between src1 & src2 */              \
    mask = src3 & 0xc0c0c0c0c0c0c0c0LL;                                                                 \
    maskz = __builtin_e2k_pcmpeqb (mask, 0x8080808080808080LL); /* zero mask */                         \
    maski = __builtin_e2k_pcmpeqb (src3 & 0x2020202020202020L, 0x2020202020202020LL); /* invert mask */ \
    maskr = __builtin_e2k_pcmpeqb (mask, 0x4040404040404040LL); /* bit reverse mask */                  \
    masks = __builtin_e2k_pcmpeqb (mask, 0xc0c0c0c0c0c0c0c0LL); /* sign bit mask */                     \
    dst &= ~maskz; /* zeroing bytes */                                                                  \
    dst ^= maski; /* invert bytes with 001 bit op */                                                    \
    rev = __builtin_e2k_pshufb (dst, __builtin_e2k_bitrevd (dst), 0x0001020304050607LL);                \
    sgn = __builtin_e2k_pcmpgtb (0, dst);                                                               \
    dst = __builtin_e2k_pmerge (dst, rev, maskr);      /* insert sign vals */                           \
    dst = __builtin_e2k_pmerge (dst, sgn, masks);      /* insert sign vals */                           \
}

#elif __iset__ <= 4

#define VPPERM(src1h, src1l, src2h, src2l, src3, dst) {                                                 \
    __di src11, src22, mask, maskz, masks;                                                              \
    mask = __builtin_e2k_pcmpgtb (0, src3 << 3);                                                        \
    src11 = __builtin_e2k_pshufb (src1h, src1l, src3 & 0x0f0f0f0f0f0f0f0fLL);                           \
    src22 = __builtin_e2k_pshufb (src2h, src2l, src3 & 0x0f0f0f0f0f0f0f0fLL);                           \
    dst = __builtin_e2k_pmerge (src11, src22, mask);      /* select between src1 & src2 */              \
    maskz = __builtin_e2k_pcmpgtb (0xc0c0c0c0c0c0c0c0LL, src3); /* zero mask */                         \
    dst &= ~maskz; /* zeroing bytes */                                                                  \
    masks = __builtin_e2k_pcmpeqb (src3 & 0xc0c0c0c0c0c0c0c0LL, 0xc0c0c0c0c0c0c0c0LL); /* sign bit mask */ \
    masks &= 0x6060606060606060LL;                                                                      \
    mask = (src3 >> 1) & 0x3030303030303030LL;                                                          \
    mask = (mask ^ masks) | 0x0706050403020100LL;                                                       \
    dst = __builtin_e2k_pshufb (dst, dst, mask);                                                        \
}

#else /* __iset__ <= 4 */

#define VPPERM(src1, src2, src3, dst) {                                                          \
    __v2di maskz, maskhi, masklo, masks;                                                         \
    maskz = __builtin_e2k_qpcmpgtb (__builtin_e2k_qppackdl (0xc0c0c0c0c0c0c0c0LL, 0xc0c0c0c0c0c0c0c0LL), src3); /* zero mask */ \
    masklo = __builtin_e2k_qpand (src3, __builtin_e2k_qppackdl (0x1f1f1f1f1f1f1f1fLL, 0x1f1f1f1f1f1f1f1fLL));  \
    maskhi = __builtin_e2k_qpandn (src3, __builtin_e2k_qppackdl (0x1f1f1f1f1f1f1f1fLL, 0x1f1f1f1f1f1f1f1fLL)); \
    dst = __builtin_e2k_qppermb (src2, src1, masklo); /* select between src1 & src2 */           \
    dst = __builtin_e2k_qpandn (dst, maskz);          /* zeroing bytes */                        \
    masks = __builtin_e2k_qpand (src3, __builtin_e2k_qppackdl (0xc0c0c0c0c0c0c0c0LL, 0xc0c0c0c0c0c0c0c0LL));   \
    masks = __builtin_e2k_qpcmpeqb (masks, __builtin_e2k_qppackdl (0xc0c0c0c0c0c0c0c0LL, 0xc0c0c0c0c0c0c0c0LL)); /* sign bit mask */ \
    masks = __builtin_e2k_qpand (masks, __builtin_e2k_qppackdl (0x4040404040404040LL, 0x4040404040404040LL));  \
    maskhi = __builtin_e2k_qplog (0xbe, maskhi, masks, /* [7:6] == 3 -> 2 */                     \
                                  (__builtin_e2k_qppackdl (0x0f0e0d0c0b0a0908LL, 0x0706050403020100LL))); /* (maskhi ^ masks) | const */ \
    dst = __builtin_e2k_qppermb (dst, dst, maskhi);   /* control bits applied */                 \
}

#endif /* __iset__ <= 4 */

/* перестановки байт из src1 и src2 и выполнение над ними логических операций в
 * зависимости от значений управляющих байт в src3. Поле [4:0] определяет номер байта,
 * а поле [7:5] - тип операции над выбранным байтом */
__E2K_INLINE __E2K_WARNING (__v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpperm (__v16qi src1, __v16qi src2, __v16qi src3))
{
    type_union_128 s1, s2, s3, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
    s3.__v16qi = src3;
#if __iset__ <= 4
    VPPERM (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, s3.l.l0, dst.l.l0);
    VPPERM (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, s3.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    VPPERM (s1.__v2di, s2.__v2di, s3.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* *****************************************************************************
 *                                 Cдвиги
 * *****************************************************************************/

#if __iset__ <= 4

#define __SCL_8U(src, shift, dst) {                                                      \
    __di mul, eve, odd;                                                                  \
    shift &= 0x0707070707070707LL;                                                       \
    mul = __builtin_e2k_pshufb (0, 0x8040201008040201LL, shift);                         \
    eve = __builtin_e2k_pmullh (src & 0x00ff00ff00ff00ffLL, mul & 0x00ff00ff00ff00ffLL); \
    odd = __builtin_e2k_pmulhuh (src & ~0x00ff00ff00ff00ffLL, mul & ~0x00ff00ff00ff00ffLL);\
    eve |= eve >> 8;                                                                     \
    odd |= odd << 8;                                                                     \
    dst = __builtin_e2k_pshufb (eve, odd, 0x070e050c030a0108LL);                         \
}

#define __SCL_16U(src, shift, dst) {                                                     \
    __di shiftl, mul, mask;                                                              \
    shiftl = (shift & 0x0007000700070007LL) | 0x8000800080008000LL;/* для вставки нулей */\
    mul = __builtin_e2k_pshufb (0, 0x8040201008040201LL, shiftl);                        \
    mask = __builtin_e2k_pcmpgth (0, shift << 12);                                       \
    mul = __builtin_e2k_pmerge (mul, mul << 8, mask);                                    \
    dst = __builtin_e2k_pmullh (src, mul) | __builtin_e2k_pmulhuh (src, mul);            \
}

#define __SCLI_8U(src, shift, dst) {                                                     \
    __di odd = (src & ~0x00ff00ff00ff00ffLL) >> (8 - shift);                             \
    __di eve = (src &  0x00ff00ff00ff00ffLL) << shift;                                   \
    eve |= eve >> 8;                                                                     \
    odd |= odd << 8;                                                                     \
    dst = __builtin_e2k_pshufb (eve, odd, 0x070e050c030a0108LL);                         \
}

#else /* __iset__ <= 4 */

#define __SCL_8U(src, shift, dst) {                                                                  \
    __v2di mul, eve, odd;                                                                            \
    shift = __builtin_e2k_qpand (shift, __builtin_e2k_qppackdl (0x0707070707070707LL, 0x0707070707070707LL));      \
    mul = __builtin_e2k_qppermb (mul, __builtin_e2k_qppackdl (0x8040201008040201LL, 0x8040201008040201LL), shift); \
    eve = __builtin_e2k_qpmullh (                                                                    \
              __builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)),      \
              __builtin_e2k_qpand (mul, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)));     \
    odd = __builtin_e2k_qpmulhuh (                                                                   \
              __builtin_e2k_qpandn (src, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)),     \
              __builtin_e2k_qpandn (mul, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)));    \
    eve = __builtin_e2k_qpor (eve, __builtin_e2k_qpsrld (eve, 8));                                   \
    odd = __builtin_e2k_qpor (odd, __builtin_e2k_qpslld (odd, 8));                                   \
    dst = __builtin_e2k_qppermb (eve, odd, __builtin_e2k_qppackdl (0x0f1e0d1c0b1a0918LL, 0x0716051403120110LL));   \
}

#define __SCL_16U(src, shift, dst) {                                                                 \
    __v2di shiftl, mul, mask;                                                                        \
    shiftl = __builtin_e2k_qplog (0xea, shift, (__builtin_e2k_qppackdl (0x0007000700070007LL, 0x0007000700070007LL)), /* для вставки нулей */\
                                  (__builtin_e2k_qppackdl (0x1000100010001000LL, 0x1000100010001000LL))); /* (shift & const1) | const2 */ \
    mul = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), __builtin_e2k_qppackdl (0x8040201008040201LL, 0x8040201008040201LL), shiftl); \
    mask = __builtin_e2k_qpcmpgth (__builtin_e2k_qppackdl (0, 0), __builtin_e2k_qpslld (shift, 12)); \
    mul = __builtin_e2k_qpmerge (mul, __builtin_e2k_qpslld (mul, 8), mask);                          \
    dst = __builtin_e2k_qpor (__builtin_e2k_qpmullh (src, mul), __builtin_e2k_qpmulhuh (src, mul));  \
}

#define __SCLI_8U(src, shift, dst) {                                                                 \
    __v2di odd = __builtin_e2k_qpandn (src, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)); \
    __v2di eve = __builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL));  \
    odd = __builtin_e2k_qpsrld (odd, 8 - shift);                                                     \
    eve = __builtin_e2k_qpslld (eve, shift);                                                         \
    eve = __builtin_e2k_qpor (eve, __builtin_e2k_qpsrld (eve, 8));                                   \
    odd = __builtin_e2k_qpor (odd, __builtin_e2k_qpslld (odd, 8));                                   \
    dst = __builtin_e2k_qppermb (eve, odd, __builtin_e2k_qppackdl (0x0f1e0d1c0b1a0918LL, 0x0716051403120110LL));  \
}

#endif /* __iset__ <= 4 */

/* циклический сдвиг каждого из 16-ти байт (8U) на свою величину. Величина сдвига в
 * соответствующем байте в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо */
__E2K_INLINE __E2K_WARNING (__v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotb (__v16qi src1, __v16qi src2))
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    __SCL_8U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SCL_8U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SCL_8U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* циклический сдвиг каждого из 8-ми шортов (16U) на свою величину. Величина сдвига в
 * младшем байте соответствующего шорта в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо */
__E2K_INLINE __E2K_WARNING (__v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotw (__v8hi src1, __v8hi src2))
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    __SCL_16U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SCL_16U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SCL_16U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* циклический сдвиг каждого из 4-х интов (32U) на свою величину. Величина сдвига в
 * младшем байте соответствующего инта в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotd (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.i.i0 = __builtin_e2k_scls (s1.i.i0, s2.i.i0);
    dst.i.i1 = __builtin_e2k_scls (s1.i.i1, s2.i.i1);
    dst.i.i2 = __builtin_e2k_scls (s1.i.i2, s2.i.i2);
    dst.i.i3 = __builtin_e2k_scls (s1.i.i3, s2.i.i3);
    return dst.__v4si;
}

/* циклический сдвиг каждого из 2-х лонгов (64U) на свою величину. Величина сдвига в
 * младшем байте соответствующего лонга в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    dst.l.l0 = __builtin_e2k_scld (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_scld (s1.l.l1, s2.l.l1);
    return dst.__v2di;
}

/* циклический сдвиг 16-ти байт (8U) на величину во 2-м аргументе
 * (положительное значение - сдвиг влево, отрицательное - сдвиг вправо */
__E2K_INLINE __E2K_WARNING (__v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotbi (__v16qi src, const int shift))
{
    type_union_128 s, dst;
    s.__v16qi = src;
    int sh = shift & 7;
#if __iset__ <= 4
    __SCLI_8U (s.l.l0, sh, dst.l.l0);
    __SCLI_8U (s.l.l1, sh, dst.l.l1);
#else /* __iset__ <= 4 */
    __SCLI_8U (s.__v2di, sh, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* циклический сдвиг 8-ми шортов (16U) на величину во 2-м аргументе
 * (положительное значение - сдвиг влево, отрицательное - сдвиг вправо */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotwi (__v8hi src, const int shift)
{
    type_union_128 s, dst;
    s.__v8hi = src;
    int sh = shift & 15;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_psllh (s.l.l0, sh) | __builtin_e2k_psrlh (s.l.l0, 16 - sh);
    dst.l.l1 = __builtin_e2k_psllh (s.l.l1, sh) | __builtin_e2k_psrlh (s.l.l1, 16 - sh);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpor (__builtin_e2k_qpsllh (s.__v2di, sh), __builtin_e2k_qpsrlh (s.__v2di, 16 - sh));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* циклический сдвиг 4-х интов (32U) на величину во 2-м аргументе
 * (положительное значение - сдвиг влево, отрицательное - сдвиг вправо */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotdi (__v4si src, const int shift)
{
    type_union_128 s, dst;
    s.__v4si = src;
    int sh = shift & 31;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_psllw (s.l.l0, sh) | __builtin_e2k_psrlw (s.l.l0, 32 - sh);
    dst.l.l1 = __builtin_e2k_psllw (s.l.l1, sh) | __builtin_e2k_psrlw (s.l.l1, 32 - sh);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsrcw (s.__v2di, 32 - sh);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* циклический сдвиг 2-х лонгов (64U) на величину во 2-м аргументе
 * (положительное значение - сдвиг влево, отрицательное - сдвиг вправо */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vprotqi (__v2di src, const int shift)
{
    type_union_128 s, dst;
    s.__v2di = src;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_scld (s.l.l0, shift);
    dst.l.l1 = __builtin_e2k_scld (s.l.l1, shift);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpsrcd (s.__v2di, 64 - shift);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

#if __iset__ <= 2

#define __SHL_8U(src, shift, dst) {                                                           \
    __di sh, mul, eve, odd;                                                                   \
    sh = shift ^ 0x8080808080808080LL;                                                        \
    sh = __builtin_e2k_pmaxub (sh, 0x7878787878787878LL);            /* min = -8 */           \
    sh = __builtin_e2k_pminub (sh, 0x8888888888888888LL);            /* max =  8 */           \
    mul = __builtin_e2k_pshufb (0x8040201008040200LL, 0x8040201008040201LL, sh & 0x0f0f0f0f0f0f0f0fLL); \
    eve = __builtin_e2k_pmullh  (src &  0x00ff00ff00ff00ffLL, mul &  0x00ff00ff00ff00ffLL);   \
    odd = __builtin_e2k_pmulhuh (src & ~0x00ff00ff00ff00ffLL, mul & ~0x00ff00ff00ff00ffLL);   \
    sh = __builtin_e2k_pmerge (0x060e040c020a0008LL, 0x070f050d030b0109LL, shift);            \
    dst = __builtin_e2k_pshufb (eve, odd, sh);                                                \
}

#elif __iset__ <= 4

#define __SHL_8U(src, shift, dst) {                                                           \
    __di sh, mul, eve, odd;                                                                   \
    sh = __builtin_e2k_pmaxsb (shift, 0xf8f8f8f8f8f8f8f8LL);         /* min = -8 */           \
    sh = __builtin_e2k_pminsb (sh,    0x0808080808080808LL);         /* max =  8 */           \
    mul = __builtin_e2k_pshufb (0x8040201008040200LL, 0x8040201008040201LL, sh & 0x0f0f0f0f0f0f0f0fLL); \
    eve = __builtin_e2k_pmullh  (src &  0x00ff00ff00ff00ffLL, mul &  0x00ff00ff00ff00ffLL);   \
    odd = __builtin_e2k_pmulhuh (src & ~0x00ff00ff00ff00ffLL, mul & ~0x00ff00ff00ff00ffLL);   \
    sh = __builtin_e2k_pmerge (0x060e040c020a0008LL, 0x070f050d030b0109LL, shift);            \
    dst = __builtin_e2k_pshufb (eve, odd, sh);                                                \
}

#else /* __iset__ <= 4 */

#define __SHL_8U(src, shift, dst) {                                                              \
    __v2di sh, mul, eve, odd;                                                                    \
    sh = __builtin_e2k_qpmaxsb (shift, __builtin_e2k_qppackdl (0xf8f8f8f8f8f8f8f8LL, 0xf8f8f8f8f8f8f8f8LL));/* min = -8 */\
    sh = __builtin_e2k_qpminsb (sh,    __builtin_e2k_qppackdl (0x0808080808080808LL, 0x0808080808080808LL));/* max =  8 */\
    sh = __builtin_e2k_qpand (sh, __builtin_e2k_qppackdl (0x0f0f0f0f0f0f0f0fLL, 0x0f0f0f0f0f0f0f0fLL));        \
    mul = __builtin_e2k_qppermb (sh, __builtin_e2k_qppackdl (0x8040201008040200LL, 0x8040201008040201LL), sh); \
    eve = __builtin_e2k_qpmullh (                                                                \
              __builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)),  \
              __builtin_e2k_qpand (mul, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL))); \
    odd = __builtin_e2k_qpmulhuh (                                                               \
              __builtin_e2k_qpandn (src, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)), \
              __builtin_e2k_qpandn (mul, __builtin_e2k_qppackdl (0x00ff00ff00ff00ffLL, 0x00ff00ff00ff00ffLL)));\
    sh = __builtin_e2k_qpmerge (__builtin_e2k_qppackdl (0x0e1e0c1c0a1a0818LL, 0x0616041402120010LL),           \
                                __builtin_e2k_qppackdl (0x0f1f0d1d0b1b0919LL, 0x0717051503130111LL), shift);   \
    dst = __builtin_e2k_qppermb (eve, odd, sh);                                                  \
}

#endif /* __iset__ <= 4 */

#if __iset__ <= 4

#define __SHL_16U(src, shift, dst) {                                                     \
    __di eve, odd;                                                                       \
    shift = __builtin_e2k_psrah (shift << 8, 8);                                         \
    shift = __builtin_e2k_pmaxsh (shift, 0xfff0fff0fff0fff0LL);      /* min = -16 */     \
    shift = __builtin_e2k_pminsh (shift, 0x0010001000100010LL);      /* max =  16 */     \
    eve = __builtin_e2k_scld (src & 0x000000000000ffffLL, shift      ) |                 \
          __builtin_e2k_scld (src & 0x0000ffff00000000LL, shift >> 32);                  \
    odd = __builtin_e2k_scld (src & 0x00000000ffff0000LL, shift >> 16) |                 \
          __builtin_e2k_scld (src & 0xffff000000000000LL, shift >> 48);                  \
    dst = __builtin_e2k_pshufb (eve, odd, 0x07060d0c03020908LL);                         \
}

#define __SHL_32U(src, shift, dst) {                                                     \
    __di eve, odd;                                                                       \
    shift = __builtin_e2k_psrah (shift << 8, 8);                                         \
    shift = __builtin_e2k_pmaxsh (shift, 0x0000ffe00000ffe0LL);      /* min = -32 */     \
    shift = __builtin_e2k_pminsh (shift, 0x0000002000000020LL);      /* max =  32 */     \
    eve = __builtin_e2k_scld (src & 0x00000000ffffffffLL, shift);                        \
    odd = __builtin_e2k_scld (src & 0xffffffff00000000LL, shift >> 32);                  \
    dst = __builtin_e2k_pshufw (eve, odd, 6); /* 12 */                                   \
}

#else /* __iset__ <= 4 */

#define __SHL_16U(src, shift, dst) {                                                                 \
    __v2di shiftl, mul, mask;                                                                        \
    shift = __builtin_e2k_qpsrah (__builtin_e2k_qpslld (shift, 8), 8);                               \
    shift = __builtin_e2k_qpmaxsh (shift, __builtin_e2k_qppackdl (0xfff0fff0fff0fff0LL, 0xfff0fff0fff0fff0LL));/* min = -16 */\
    shift = __builtin_e2k_qpminsh (shift, __builtin_e2k_qppackdl (0x0010001000100010LL, 0x0010001000100010LL));/* max =  16 */\
    shiftl = __builtin_e2k_qplog (0xea, shift, (__builtin_e2k_qppackdl (0x001f001f001f001fLL, 0x001f001f001f001fLL)), /* для вставки нулей */\
                                  (__builtin_e2k_qppackdl (0x1000100010001000LL, 0x1000100010001000LL))); /* (shift & const1) | const2 */ \
    mul = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0x8040201008040201LL, 0x8040201008040200LL),              \
                                 __builtin_e2k_qppackdl (0x8040201008040201LL, 0x8040201008040201LL), shiftl);     \
    mask = __builtin_e2k_qpcmpgth (__builtin_e2k_qppackdl (0, 0), __builtin_e2k_qpslld (shift, 12)); \
    mul = __builtin_e2k_qpmerge (mul, __builtin_e2k_qpslld (mul, 8), mask);                          \
    mask = __builtin_e2k_qpcmpgth (__builtin_e2k_qppackdl (0, 0), shift);                            \
    dst = __builtin_e2k_qpmerge (__builtin_e2k_qpmullh (src, mul), __builtin_e2k_qpmulhuh (src, mul), mask); \
}

#define __SHL_32U(src, shift, dst) {                                                                              \
    __v2di shiftl, eve0, eve1, odd0, odd1;                                                                        \
    shift = __builtin_e2k_qpsrah (__builtin_e2k_qpslld (shift, 8), 8);                                            \
    shift = __builtin_e2k_qpmaxsh (shift, __builtin_e2k_qppackdl (0x0000ffe00000ffe0LL, 0x0000ffe00000ffe0LL)); /* min = -32 */ \
    shift = __builtin_e2k_qpminsh (shift, __builtin_e2k_qppackdl (0x0000002000000020LL, 0x0000002000000020LL)); /* max =  32 */ \
    shift = __builtin_e2k_qpsubh (__builtin_e2k_qppackdl (0x0000004000000040LL, 0x0000004000000040LL), shift); /* 64 - shift */ \
    eve0 = __builtin_e2k_qpsrcd (__builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0x0000000000000000LL, 0x00000000ffffffffLL)), shift[0]); \
    eve1 = __builtin_e2k_qpsrcd (__builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0x00000000ffffffffLL, 0x0000000000000000LL)), shift[1]); \
    odd0 = __builtin_e2k_qpsrcd (__builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0x0000000000000000LL, 0xffffffff00000000LL)), shift[0] >> 32); \
    odd1 = __builtin_e2k_qpsrcd (__builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0xffffffff00000000LL, 0x0000000000000000LL)), shift[1] >> 32); \
    eve0 = __builtin_e2k_qpor (eve0, eve1);                                                                       \
    odd0 = __builtin_e2k_qpor (odd0, odd1);                                                                       \
    dst = __builtin_e2k_qppermb (eve0, odd0, __builtin_e2k_qppackdl (0x0f0e0d0c1b1a1918LL, 0x0706050413121110LL));\
}

#endif /* __iset__ <= 4 */

/* логический сдвиг каждого из 16-ти байт (8U) на свою величину. Величина сдвига в
 * соответствующем байте в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо, при сдвиге больше 7 результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshlb (__v16qi src1, __v16qi src2))
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    __SHL_8U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHL_8U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SHL_8U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* логический сдвиг каждого из 8-ми шортов (16U) на свою величину. Величина сдвига в
 * младшем байте соответствующего шорта в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо, при сдвиге больше 15 результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshlw (__v8hi src1, __v8hi src2))
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    __SHL_16U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHL_16U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SHL_16U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* логический сдвиг каждого из 4-х интов (32U) на свою величину. Величина сдвига в
 * младшем байте соответствующего инта в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо, при сдвиге больше 31 результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshld (__v4si src1, __v4si src2))
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    __SHL_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHL_32U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SHL_32U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* логический сдвиг каждого из 2-х лонгов (64U) на свою величину. Величина сдвига в
 * младшем байте соответствующего лонга в src2 (положительное значение - сдвиг влево,
 * отрицательное - сдвиг вправо, при сдвиге больше 63 результат равен 0 */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshlq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    signed char shift0 = (signed char) s2.l.l0;
    signed char shift1 = (signed char) s2.l.l1;
    dst.l.l0 = (shift0 < 0) ? __builtin_e2k_psrld (s1.l.l0, -shift0) : __builtin_e2k_pslld (s1.l.l0, shift0);
    dst.l.l1 = (shift1 < 0) ? __builtin_e2k_psrld (s1.l.l1, -shift1) : __builtin_e2k_pslld (s1.l.l1, shift1);
    return dst.__v2di;
}

#if __iset__ <= 2

#define __SHA_8U(src, shift, dst) {                                                      \
    __di sh, mulhi, mullo, eve, odd;                                                     \
    shift ^= 0x8080808080808080LL;                                                       \
    sh = __builtin_e2k_pmaxub (shift, 0x7979797979797979LL);      /* min = -7 */         \
    sh = __builtin_e2k_pminub (sh,    0x8888888888888888LL);      /* max =  8 */         \
    sh &= 0x0f0f0f0f0f0f0f0fLL;                                                          \
    mullo = __builtin_e2k_pshufb (0x8040201008040200LL, 0, sh);                          \
    mulhi = __builtin_e2k_pshufb (0, 0x8040201008040201LL, sh);                          \
    eve = __builtin_e2k_pshufb (mulhi, mullo, 0x0e060c040a020800LL);                     \
    odd = __builtin_e2k_pshufb (mulhi, mullo, 0x0f070d050b030901LL);                     \
    eve = __builtin_e2k_pmulhh ((src << 8) & 0xff00ff00ff00ff00LL, eve);                 \
    odd = __builtin_e2k_pmulhh ( src       & 0xff00ff00ff00ff00LL, odd);                 \
    dst = __builtin_e2k_pshufb (eve, odd, 0x060e040c020a0008LL);                         \
}

#elif __iset__ <= 4

#define __SHA_8U(src, shift, dst) {                                                      \
    __di sh, mulhi, mullo, eve, odd;                                                     \
    sh = __builtin_e2k_pmaxsb (shift, 0xf9f9f9f9f9f9f9f9LL);      /* min = -7 */         \
    sh = __builtin_e2k_pminsb (sh,    0x0808080808080808LL);      /* max =  8 */         \
    sh &= 0x0f0f0f0f0f0f0f0fLL;                                                          \
    mullo = __builtin_e2k_pshufb (0x8040201008040200LL, 0, sh);                          \
    mulhi = __builtin_e2k_pshufb (0, 0x8040201008040201LL, sh);                          \
    eve = __builtin_e2k_pshufb (mulhi, mullo, 0x0e060c040a020800LL);                     \
    odd = __builtin_e2k_pshufb (mulhi, mullo, 0x0f070d050b030901LL);                     \
    eve = __builtin_e2k_pmulhh ((src << 8) & 0xff00ff00ff00ff00LL, eve);                 \
    odd = __builtin_e2k_pmulhh ( src       & 0xff00ff00ff00ff00LL, odd);                 \
    dst = __builtin_e2k_pshufb (eve, odd, 0x060e040c020a0008LL);                         \
}

#else /* __iset__ <= 4 */

#define __SHA_8U(src, shift, dst) {                                                                    \
    __v2di sh, mulhi, mullo, eve, odd;                                                                 \
    sh = __builtin_e2k_qpmaxsb (shift, __builtin_e2k_qppackdl (0xf9f9f9f9f9f9f9f9LL, 0xf9f9f9f9f9f9f9f9LL));/* min = -7 */\
    sh = __builtin_e2k_qpminsb (sh,    __builtin_e2k_qppackdl (0x0808080808080808LL, 0x0808080808080808LL));/* max =  8 */\
    sh = __builtin_e2k_qpand (sh, __builtin_e2k_qppackdl (0x0f0f0f0f0f0f0f0fLL, 0x0f0f0f0f0f0f0f0fLL));              \
    mullo = __builtin_e2k_qppermb (sh, __builtin_e2k_qppackdl (0x8040201008040200LL, 0), sh);                        \
    mulhi = __builtin_e2k_qppermb (sh, __builtin_e2k_qppackdl (0, 0x8040201008040201LL), sh);                        \
    eve = __builtin_e2k_qppermb (mulhi, mullo, __builtin_e2k_qppackdl (0x1e0e1c0c1a0a1808LL, 0x1606140412021000LL)); \
    odd = __builtin_e2k_qppermb (mulhi, mullo, __builtin_e2k_qppackdl (0x1f0f1d0d1b0b1909LL, 0x1707150513031101LL)); \
    eve = __builtin_e2k_qpmulhh (__builtin_e2k_qpand (__builtin_e2k_qpslld (src, 8),                                 \
              __builtin_e2k_qppackdl (0xff00ff00ff00ff00LL, 0xff00ff00ff00ff00LL)), eve);                            \
    odd = __builtin_e2k_qpmulhh (__builtin_e2k_qpand (src,                                                           \
              __builtin_e2k_qppackdl (0xff00ff00ff00ff00LL, 0xff00ff00ff00ff00LL)), odd);                            \
    dst = __builtin_e2k_qppermb (eve, odd, __builtin_e2k_qppackdl (0x0e1e0c1c0a1a0818LL, 0x0616041402120010LL));     \
}

#endif /* __iset__ <= 4 */

#if __iset__ <= 4

#define __SHA_16U(src, shift, dst) {                                                     \
    __di eve, odd;                                                                       \
    shift = __builtin_e2k_psrah (shift << 8, 8);                                         \
    shift = __builtin_e2k_pmaxsh (shift, 0xfff1fff1fff1fff1LL);   /* min = -15 */        \
    shift = __builtin_e2k_pminsh (shift, 0x0010001000100010LL);   /* max =  16 */        \
    shift = __builtin_e2k_psubh (0x0010001000100010LL, shift);    /* 16 - shift */       \
    eve = (src << 16) & 0xffff0000ffff0000LL;                                            \
    odd =  src        & 0xffff0000ffff0000LL;                                            \
    eve = __builtin_e2k_pshufw (__builtin_e2k_psraw (eve, shift         & 0x1f),         \
                      (long long) eve >> (shift >> 32), 6); /* 12 */                     \
    odd = __builtin_e2k_pshufw (__builtin_e2k_psraw (odd, (shift >> 16) & 0x1f),         \
                      (long long) odd >> (shift >> 48), 6); /* 12 */                     \
    dst = __builtin_e2k_pshufb (eve, odd, 0x05040d0c01000908LL);                         \
}

#define __SHA_32U(src, shift, dst) {                                                     \
    __di eve, odd;                                                                       \
    shift = __builtin_e2k_psrah (shift << 8, 8);                                         \
    shift = __builtin_e2k_pmaxsh (shift, 0x0000ffe10000ffe1LL);   /* min = -31 */        \
    shift = __builtin_e2k_pminsh (shift, 0x0000002000000020LL);   /* max =  32 */        \
    shift = 0x8000002080000020LL - shift;               /* 32 - shift */                 \
    eve = (long long) (src << 32) >> shift;                                              \
    odd = (long long) (src & 0xffffffff00000000LL) >> (shift >> 32);                     \
    dst = __builtin_e2k_pshufw (eve, odd, 2); /* 02 */                                   \
}

#else /* __iset__ <= 4 */

#define __SHA_16U(src, shift, dst) {                                                                 \
    __v2di shiftl, mul, mask;                                                                        \
    shift = __builtin_e2k_qpsrah (__builtin_e2k_qpslld (shift, 8), 8);                               \
    shift = __builtin_e2k_qpmaxsh (shift, __builtin_e2k_qppackdl (0xfff1fff1fff1fff1LL, 0xfff1fff1fff1fff1LL));/* min = -15 */\
    shift = __builtin_e2k_qpminsh (shift, __builtin_e2k_qppackdl (0x0010001000100010LL, 0x0010001000100010LL));/* max =  16 */\
    shiftl = __builtin_e2k_qplog (0xea, shift, (__builtin_e2k_qppackdl (0x001f001f001f001fLL, 0x001f001f001f001fLL)), /* для вставки нулей */\
                                  (__builtin_e2k_qppackdl (0x1000100010001000LL, 0x1000100010001000LL))); /* (shift & const1) | const2 */ \
    mul = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0x8040201008040201LL, 0x8040201008040200LL),\
                                 __builtin_e2k_qppackdl (0x8040201008040201LL, 0x8040201008040201LL), shiftl);     \
    mask = __builtin_e2k_qpcmpgth (__builtin_e2k_qppackdl (0, 0), __builtin_e2k_qpslld (shift, 12)); \
    mul = __builtin_e2k_qpmerge (mul, __builtin_e2k_qpslld (mul, 8), mask);                          \
    mask = __builtin_e2k_qpcmpgth (__builtin_e2k_qppackdl (0, 0), shift);                            \
    dst = __builtin_e2k_qpmerge (__builtin_e2k_qpmullh (src, mul), __builtin_e2k_qpmulhh (src, mul), mask); \
    mask = __builtin_e2k_qpcmpeqh (shift, __builtin_e2k_qppackdl (-1LL, -1LL));/* shift = -1 */      \
    dst = __builtin_e2k_qpsubh (__builtin_e2k_qpxor (dst, mask), mask);                              \
}

#define __SHA_32U(src, shift, dst) {                                                                              \
    __v2di eve, odd;                                                                                              \
    shift = __builtin_e2k_qpsrah (__builtin_e2k_qpslld (shift, 8), 8);                                            \
    shift = __builtin_e2k_qpmaxsh (shift, __builtin_e2k_qppackdl (0x0000ffe10000ffe1LL, 0x0000ffe10000ffe1LL)); /* min = -31 */ \
    shift = __builtin_e2k_qpminsh (shift, __builtin_e2k_qppackdl (0x0000002000000020LL, 0x0000002000000020LL)); /* max =  32 */ \
    shift = __builtin_e2k_qpsubh (__builtin_e2k_qppackdl (0x0000002000000020LL, 0x0000002000000020LL), shift); /* 32 - shift */ \
    eve = __builtin_e2k_qpslld (src, 32);                                                                         \
    odd = __builtin_e2k_qpand (src, __builtin_e2k_qppackdl (0xffffffff00000000LL, 0xffffffff00000000LL));         \
    eve = __builtin_e2k_qppackdl ((long long) eve[1] >> shift[1], (long long) eve[0] >> shift[0]);                \
    odd = __builtin_e2k_qppackdl ((long long) odd[1] >> (shift[1] >> 32), (long long) odd[0] >> (shift[0] >> 32));\
    dst = __builtin_e2k_qppermb (eve, odd, __builtin_e2k_qppackdl (0x0b0a09081b1a1918LL, 0x0302010013121110LL));  \
}

#endif /* __iset__ <= 4 */

/* арифметический сдвиг каждого из 16-ти знаковых байт (8S) на свою величину.
 * Величина сдвига в соответствующем байте в src2 (положительное значение - сдвиг
 * влево, отрицательное - сдвиг вправо, при сдвиге больше 7 результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshab (__v16qi src1, __v16qi src2))
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    __SHA_8U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHA_8U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SHA_8U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* арифметический сдвиг каждого из 8-ми знаковых шортов (16S) на свою величину.
 * Величина сдвига в младшем байте соответствующего шорта в src2 (положительное
 * значение - сдвиг влево, отрицательное - сдвиг вправо, при сдвиге больше 15
 * результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshaw (__v8hi src1, __v8hi src2))
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    __SHA_16U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHA_16U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SHA_16U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* арифметический сдвиг каждого из 4-х знаковых интов (32S) на свою величину.
 * Величина сдвига в младшем байте соответствующего инта в src2 (положительное
 * значение - сдвиг влево, отрицательное - сдвиг вправо, при сдвиге больше 31
 * результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshad (__v4si src1, __v4si src2))
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    __SHA_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHA_32U (s1.l.l1, s2.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __SHA_32U (s1.__v2di, s2.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* арифметический сдвиг каждого из 2-х знаковых лонгов (64S) на свою величину.
 * Величина сдвига в младшем байте соответствующего лонга в src2 (положительное
 * значение - сдвиг влево, отрицательное - сдвиг вправо, при сдвиге больше 63
 * результат равен 0 */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpshaq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    signed char shift0 = (signed char) s2.l.l0;
    signed char shift1 = (signed char) s2.l.l1;
    dst.l.l0 = (shift0 < -63) ? 0 : ((shift0 < 0) ? (long long) s1.l.l0 >> -shift0
                                            : __builtin_e2k_pslld (s1.l.l0, shift0));
    dst.l.l1 = (shift1 < -63) ? 0 : ((shift1 < 0) ? (long long) s1.l.l1 >> -shift1
                                            : __builtin_e2k_pslld (s1.l.l1, shift1));
    return dst.__v2di;
}

/* *****************************************************************************
 *                            Cравнения беззнаковых
 * *****************************************************************************/

/* сравнение на "меньше" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltub (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtb (s2.l.l0 ^ 0x8080808080808080LL, s1.l.l0 ^ 0x8080808080808080LL);
    dst.l.l1 = __builtin_e2k_pcmpgtb (s2.l.l1 ^ 0x8080808080808080LL, s1.l.l1 ^ 0x8080808080808080LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtb (
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8080808080808080LL, 0x8080808080808080LL)),
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8080808080808080LL, 0x8080808080808080LL)));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "меньше или равно" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomleub (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtb (s1.l.l0 ^ 0x8080808080808080LL, s2.l.l0 ^ 0x8080808080808080LL);
    dst.l.l1 = ~__builtin_e2k_pcmpgtb (s1.l.l1 ^ 0x8080808080808080LL, s2.l.l1 ^ 0x8080808080808080LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqb (s1.__v2di, __builtin_e2k_qpminub (s1.__v2di, s2.__v2di));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "больше" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtub (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtb (s1.l.l0 ^ 0x8080808080808080LL, s2.l.l0 ^ 0x8080808080808080LL);
    dst.l.l1 = __builtin_e2k_pcmpgtb (s1.l.l1 ^ 0x8080808080808080LL, s2.l.l1 ^ 0x8080808080808080LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtb (
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8080808080808080LL, 0x8080808080808080LL)),
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8080808080808080LL, 0x8080808080808080LL)));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "больше или равно" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgeub (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtb (s2.l.l0 ^ 0x8080808080808080LL, s1.l.l0 ^ 0x8080808080808080LL);
    dst.l.l1 = ~__builtin_e2k_pcmpgtb (s2.l.l1 ^ 0x8080808080808080LL, s1.l.l1 ^ 0x8080808080808080LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqb (s1.__v2di, __builtin_e2k_qpmaxub (s1.__v2di, s2.__v2di));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "равно" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomequb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpeqb (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqb (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqb (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "не равно" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomnequb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpeqb (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqb (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqb (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "ложь" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalseub (__v16qi src1, __v16qi src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {0, 0};
    return dst.__v16qi;
}

/* сравнение на "истину" 16-ти беззнаковых байт (8U) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtrueub (__v16qi src1, __v16qi src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v16qi;
}

/* сравнение на "меньше" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltuw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgth (s2.l.l0 ^ 0x8000800080008000LL, s1.l.l0 ^ 0x8000800080008000LL);
    dst.l.l1 = __builtin_e2k_pcmpgth (s2.l.l1 ^ 0x8000800080008000LL, s1.l.l1 ^ 0x8000800080008000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgth (
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000800080008000LL, 0x8000800080008000LL)),
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000800080008000LL, 0x8000800080008000LL)));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "меньше или равно" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomleuw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgth (s1.l.l0 ^ 0x8000800080008000LL, s2.l.l0 ^ 0x8000800080008000LL);
    dst.l.l1 = ~__builtin_e2k_pcmpgth (s1.l.l1 ^ 0x8000800080008000LL, s2.l.l1 ^ 0x8000800080008000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqh (s1.__v2di, __builtin_e2k_qpminuh (s1.__v2di, s2.__v2di));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "больше" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtuw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgth (s1.l.l0 ^ 0x8000800080008000LL, s2.l.l0 ^ 0x8000800080008000LL);
    dst.l.l1 = __builtin_e2k_pcmpgth (s1.l.l1 ^ 0x8000800080008000LL, s2.l.l1 ^ 0x8000800080008000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgth (
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000800080008000LL, 0x8000800080008000LL)),
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000800080008000LL, 0x8000800080008000LL)));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "больше или равно" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgeuw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgth (s2.l.l0 ^ 0x8000800080008000LL, s1.l.l0 ^ 0x8000800080008000LL);
    dst.l.l1 = ~__builtin_e2k_pcmpgth (s2.l.l1 ^ 0x8000800080008000LL, s1.l.l1 ^ 0x8000800080008000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqh (s1.__v2di, __builtin_e2k_qpmaxuh (s1.__v2di, s2.__v2di));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "равно" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomequw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpeqh (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqh (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqh (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "не равно" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomnequw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpeqh (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqh (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqh (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "ложь" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalseuw (__v8hi src1, __v8hi src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {0, 0};
    return dst.__v8hi;
}

/* сравнение на "истину" 8-ми беззнаковых шортов (16U) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtrueuw (__v8hi src1, __v8hi src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v8hi;
}

/* сравнение на "меньше" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltud (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtw (s2.l.l0 ^ 0x8000000080000000LL, s1.l.l0 ^ 0x8000000080000000LL);
    dst.l.l1 = __builtin_e2k_pcmpgtw (s2.l.l1 ^ 0x8000000080000000LL, s1.l.l1 ^ 0x8000000080000000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtw (
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000000080000000LL, 0x8000000080000000LL)),
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000000080000000LL, 0x8000000080000000LL)));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "меньше или равно" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomleud (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtw (s1.l.l0 ^ 0x8000000080000000LL, s2.l.l0 ^ 0x8000000080000000LL);
    dst.l.l1 = ~__builtin_e2k_pcmpgtw (s1.l.l1 ^ 0x8000000080000000LL, s2.l.l1 ^ 0x8000000080000000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqw (s1.__v2di, __builtin_e2k_qpminuw (s1.__v2di, s2.__v2di));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "больше" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtud (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtw (s1.l.l0 ^ 0x8000000080000000LL, s2.l.l0 ^ 0x8000000080000000LL);
    dst.l.l1 = __builtin_e2k_pcmpgtw (s1.l.l1 ^ 0x8000000080000000LL, s2.l.l1 ^ 0x8000000080000000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtw (
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000000080000000LL, 0x8000000080000000LL)),
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000000080000000LL, 0x8000000080000000LL)));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "больше или равно" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgeud (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtw (s2.l.l0 ^ 0x8000000080000000LL, s1.l.l0 ^ 0x8000000080000000LL);
    dst.l.l1 = ~__builtin_e2k_pcmpgtw (s2.l.l1 ^ 0x8000000080000000LL, s1.l.l1 ^ 0x8000000080000000LL);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqw (s1.__v2di, __builtin_e2k_qpmaxuw (s1.__v2di, s2.__v2di));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "равно" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomequd (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpeqw (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqw (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqw (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "не равно" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomnequd (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpeqw (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqw (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqw (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "ложь" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalseud (__v4si src1, __v4si src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {0, 0};
    return dst.__v4si;
}

/* сравнение на "истину" 4-х беззнаковых интов (32U) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtrueud (__v4si src1, __v4si src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v4si;
}

/* сравнение на "меньше" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltuq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
    dst.l.l0 = (s1.l.l0 < s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 < s2.l.l1) ? -1LL : 0;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtd (
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)),
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "меньше или равно" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomleuq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
    dst.l.l0 = (s1.l.l0 <= s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 <= s2.l.l1) ? -1LL : 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtd (
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)),
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)));
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "больше" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtuq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
    dst.l.l0 = (s1.l.l0 > s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 > s2.l.l1) ? -1LL : 0;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtd (
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)),
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "больше или равно" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgeuq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
    dst.l.l0 = (s1.l.l0 >= s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 >= s2.l.l1) ? -1LL : 0;
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtd (
                     __builtin_e2k_qpxor (s2.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)),
                     __builtin_e2k_qpxor (s1.__v2di, __builtin_e2k_qppackdl (0x8000000000000000LL, 0x8000000000000000LL)));
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "равно" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomequq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = (s1.l.l0 == s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 == s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pcmpeqd (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqd (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "не равно" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomnequq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = (s1.l.l0 != s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 != s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = ~__builtin_e2k_pcmpeqd (s1.l.l0, s2.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqd (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "ложь" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalseuq (__v2di src1, __v2di src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {0, 0};
    return dst.__v2di;
}

/* сравнение на "истину" 2-х беззнаковых лонгов (64U) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtrueuq (__v2di src1, __v2di src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v2di;
}

/* *****************************************************************************
 *                            Cравнения знаковых
 * *****************************************************************************/

/* сравнение на "меньше" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtb (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgtb (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtb (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "меньше или равно" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomleb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtb (s1.l.l0, s2.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgtb (s1.l.l1, s2.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtb (s1.__v2di, s2.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "больше" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtb (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgtb (s1.l.l1, s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtb (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "больше или равно" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgeb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtb (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgtb (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtb (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "равно" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomeqb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpeqb (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqb (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqb (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "не равно" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomneqb (__v16qi src1, __v16qi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v16qi = src1;
    s2.__v16qi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpeqb (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqb (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqb (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* сравнение на "ложь" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalseb (__v16qi src1, __v16qi src2)
{
    type_union_128 dst;
    dst.__v2di =(__v2di) {0, 0};
    return dst.__v16qi;
}

/* сравнение на "истину" 16-ти знаковых байт (8S) c выработкой маски */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtrueb (__v16qi src1, __v16qi src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v16qi;
}

/* сравнение на "меньше" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgth (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgth (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgth (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "меньше или равно" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomlew (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgth (s1.l.l0, s2.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgth (s1.l.l1, s2.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgth (s1.__v2di, s2.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "больше" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgth (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgth (s1.l.l1, s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgth (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "больше или равно" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgew (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgth (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgth (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgth (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "равно" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomeqw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpeqh (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqh (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqh (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "не равно" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomneqw (__v8hi src1, __v8hi src2)
{
    type_union_128 s1, s2, dst;
    s1.__v8hi = src1;
    s2.__v8hi = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpeqh (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqh (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqh (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* сравнение на "ложь" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalsew (__v8hi src1, __v8hi src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {0, 0};
    return dst.__v8hi;
}

/* сравнение на "истину" 8-ми знаковых шортов (16S) c выработкой маски */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtruew (__v8hi src1, __v8hi src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v8hi;
}

/* сравнение на "меньше" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltd (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtw (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgtw (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtw (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "меньше или равно" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomled (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtw (s1.l.l0, s2.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgtw (s1.l.l1, s2.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtw (s1.__v2di, s2.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "больше" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtd (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpgtw (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgtw (s1.l.l1, s2.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtw (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "больше или равно" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomged (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpgtw (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgtw (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtw (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "равно" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomeqd (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_pcmpeqw (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqw (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqw (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "не равно" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomneqd (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.l.l0 = ~__builtin_e2k_pcmpeqw (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqw (s2.l.l1, s1.l.l1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqw (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v4si;
}

/* сравнение на "ложь" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalsed (__v4si src1, __v4si src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {0, 0};
    return dst.__v4si;
}

/* сравнение на "истину" 4-х знаковых интов (32S) c выработкой маски */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtrued (__v4si src1, __v4si src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v4si;
}

/* сравнение на "меньше" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomltq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = ((long long) s1.l.l0 < (long long) s2.l.l0) ? -1LL : 0;
    dst.l.l1 = ((long long) s1.l.l1 < (long long) s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pcmpgtd (s2.l.l0, s1.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgtd (s2.l.l1, s1.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtd (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "меньше или равно" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomleq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = ((long long) s1.l.l0 <= (long long) s2.l.l0) ? -1LL : 0;
    dst.l.l1 = ((long long) s1.l.l1 <= (long long) s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = ~__builtin_e2k_pcmpgtd (s1.l.l0, s2.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgtd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtd (s1.__v2di, s2.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "больше" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgtq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = ((long long) s1.l.l0 > (long long) s2.l.l0) ? -1LL : 0;
    dst.l.l1 = ((long long) s1.l.l1 > (long long) s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pcmpgtd (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpgtd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpgtd (s1.__v2di, s2.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "больше или равно" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomgeq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = ((long long) s1.l.l0 >= (long long) s2.l.l0) ? -1LL : 0;
    dst.l.l1 = ((long long) s1.l.l1 >= (long long) s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = ~__builtin_e2k_pcmpgtd (s2.l.l0, s1.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpgtd (s2.l.l1, s1.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpgtd (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "равно" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomeqq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = (s1.l.l0 == s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 == s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = __builtin_e2k_pcmpeqd (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pcmpeqd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qpcmpeqd (s2.__v2di, s1.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "не равно" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomneqq (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
#if __iset__ <= 4
 #if __iset__ <= 2
    dst.l.l0 = (s1.l.l0 != s2.l.l0) ? -1LL : 0;
    dst.l.l1 = (s1.l.l1 != s2.l.l1) ? -1LL : 0;
 #else /* __iset__ <= 2 */
    dst.l.l0 = ~__builtin_e2k_pcmpeqd (s1.l.l0, s2.l.l0);
    dst.l.l1 = ~__builtin_e2k_pcmpeqd (s1.l.l1, s2.l.l1);
 #endif /* __iset__ <= 2 */
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qpcmpeqd (s2.__v2di, s1.__v2di);
    dst.__v2di = __builtin_e2k_qpxor (tmp, __builtin_e2k_qppackdl (-1LL, -1LL));
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* сравнение на "ложь" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomfalseq (__v2di src1, __v2di src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {0, 0};
    return dst.__v2di;
}

/* сравнение на "истину" 2-х знаковых лонгов (64S) c выработкой маски */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpcomtrueq (__v2di src1, __v2di src2)
{
    type_union_128 dst;
    dst.__v2di = (__v2di) {-1LL, -1LL};
    return dst.__v2di;
}

/* *****************************************************************************
 *                            Выделение дробной части
 * *****************************************************************************/

#if __iset__ == 2

#define __VFRCZ_32F(src, dst) {                                                              \
    __di mask = __builtin_e2k_pfcmplts (src & ~0x8000000080000000LL, 0x4b0000004b000000LL); /* 2^23 */ \
    __di tmp = __builtin_e2k_pistofs (__builtin_e2k_pfstoistr (src));                        \
    tmp |= src & 0x8000000080000000LL;                                                       \
    tmp = __builtin_e2k_pmerge (src, tmp, mask);                                             \
    dst = __builtin_e2k_pfsubs (src, tmp);                                                   \
}

#define __VFRCZ_SINGLE_32F(src, dst) {                                                       \
    type_union_64 ddd;                                                                       \
    __di mask = __builtin_e2k_pfcmplts (src.l.l0 & ~0x80000000LL, 0x4b000000LL); /* 2^23 */  \
    __di tmp = __builtin_e2k_pistofs (__builtin_e2k_pfstoistr (src.l.l0));                   \
    tmp |= src.l.l0 & 0x8000000080000000LL;                                                  \
    tmp = __builtin_e2k_pmerge (src.l.l0, tmp, mask);                                        \
    ddd.l0 = tmp;                                                                            \
    dst.f.f0 = src.f.f0 - ddd.f.f0;                                                          \
}

#define __VFRCZ_64F(src, dst, ind) {                                                         \
    type_union_64 ddd;                                                                       \
    __di abs = src.l.l##ind & ~0x8000000000000000LL;                                         \
    __di mask = __builtin_e2k_pfcmpltd (abs, 0x4330000000000000LL); /* 2^52 */               \
    __di tmp = __builtin_e2k_idtofd (__builtin_e2k_fdtoidtr (src.l.l##ind));                 \
    tmp |= src.l.l##ind & 0x8000000000000000LL;                                              \
    tmp = __builtin_e2k_pmerge (src.l.l##ind, tmp, mask);                                    \
    ddd.l0 = tmp;                                                                            \
    dst.d.d##ind = src.d.d##ind - ddd.d0;                                                    \
}

#else /* __iset__ == 2 */

#define __VFRCZ_SINGLE_32F(src, dst) {                                                       \
    type_union_64 ddd;                                                                       \
    ddd.l0 = __builtin_e2k_pfstoifs (3, src.l.l0); /* округление к 0 */                      \
    dst.f.f0 = src.f.f0 - ddd.f.f0;                                                          \
}

 #if __iset__ <= 4

#define __VFRCZ_32F(src, dst) {                                                              \
    __di tmp = __builtin_e2k_pfstoifs (3, src); /* округление к 0 */                         \
    dst = __builtin_e2k_pfsubs (src, tmp);                                                   \
}

#define __VFRCZ_64F(src, dst, ind) {                                                         \
    type_union_64 ddd;                                                                       \
    ddd.l0 = __builtin_e2k_fdtoifd (3, src.l.l##ind); /* округление к 0 */                   \
    dst.d.d##ind = src.d.d##ind - ddd.d0;                                                    \
}

 #else /* __iset__ <= 4 */

#define __VFRCZ_32F(src, dst) {                                                              \
    __v2di __tmp = __builtin_e2k_qpfstoifs (3, src); /* округление к 0 */                    \
    dst = __builtin_e2k_qpfsubs (src, __tmp);                                                \
}

#define __VFRCZ_64F(src, dst) {                                                              \
    __v2di __tmp = __builtin_e2k_qpfdtoifd (3, src); /* округление к 0 */                    \
    dst = __builtin_e2k_qpfsubd (src, __tmp);                                                \
}

#define __VFRCZ_SINGLE_64F(src, dst) {                                                       \
    type_union_128 ddd;                                                                      \
    ddd.__v2di = __builtin_e2k_qpfdtoifd (3, src.__v2di); /* округление к 0 */               \
    dst.d.d0 = src.d.d0 - ddd.d.d0;                                                          \
}

 #endif /* __iset__ <= 4 */

#endif /* __iset__ == 2 */

/* выделение дробной части из 4-х флотов (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfrczps (__v4sf src)
{
    type_union_128 s, dst;
    s.__v4sf = src;
#if __iset__ <= 4
    __VFRCZ_32F (s.l.l0, dst.l.l0);
    __VFRCZ_32F (s.l.l1, dst.l.l1);
#else /* __iset__ <= 4 */
    __VFRCZ_32F (s.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v4sf;
}

/* выделение дробной части из 2-х даблов (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfrczpd (__v2df src)
{
    type_union_128 s, dst;
    s.__v2df = src;
#if __iset__ <= 4
    __VFRCZ_64F (s, dst, 0);
    __VFRCZ_64F (s, dst, 1);
#else /* __iset__ <= 4 */
    __VFRCZ_64F (s.__v2di, dst.__v2di);
#endif /* __iset__ <= 4 */
    return dst.__v2df;
}

/* выделение дробной части из младшего флота (32F) */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfrczss (__v4sf src)
{
    type_union_128 s;
    s.__v4sf = src;
    __VFRCZ_SINGLE_32F (s, s);
    return s.__v4sf;
}

/* выделение дробной части из младшего дабла (64F) */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfrczsd (__v2df src)
{
    type_union_128 s;
    s.__v2df = src;
#if __iset__ <= 4
    __VFRCZ_64F (s, s, 0);
#else /* __iset__ <= 4 */
    __VFRCZ_SINGLE_64F (s, s);
#endif /* __iset__ <= 4 */
    return s.__v2df;
}

/* выделение дробной части из 8-ми флотов (32F) */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfrczps256 (__v8sf src)
{
    type_union_256 s, dst;
    s.__v8sf = src;
#if __iset__ <= 4
    __VFRCZ_32F (s.l.l0, dst.l.l0);
    __VFRCZ_32F (s.l.l1, dst.l.l1);
    __VFRCZ_32F (s.l.l2, dst.l.l2);
    __VFRCZ_32F (s.l.l3, dst.l.l3);
#else /* __iset__ <= 4 */
    __VFRCZ_32F (s.u__v4di.v0, dst.u__v4di.v0);
    __VFRCZ_32F (s.u__v4di.v1, dst.u__v4di.v1);
#endif /* __iset__ <= 4 */
    return dst.__v8sf;
}

/* выделение дробной части из 4-х даблов (64F) */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vfrczpd256 (__v4df src)
{
    type_union_256 s, dst;
    s.__v4df = src;
#if __iset__ <= 4
    __VFRCZ_64F (s, dst, 0);
    __VFRCZ_64F (s, dst, 1);
    __VFRCZ_64F (s, dst, 2);
    __VFRCZ_64F (s, dst, 3);
#else /* __iset__ <= 4 */
    __VFRCZ_64F (s.u__v4di.v0, dst.u__v4di.v0);
    __VFRCZ_64F (s.u__v4di.v1, dst.u__v4di.v1);
#endif /* __iset__ <= 4 */
    return dst.__v4df;
}

/* *****************************************************************************
 *                            Перестановки
 * *****************************************************************************/

#define VPERMIL_64F(src11, src10, src21, src20, dst, selector) {           \
    dst = (selector & 4) ? ((selector & 2) ? src21 : src20)                \
                         : ((selector & 2) ? src11 : src10);               \
    if ((m2z == 2 && (selector & 8)) || (m2z == 3 && (selector & 8) == 0)) \
        dst = 0;                                                           \
}

#define VPERMIL_32F(src11, src10, src21, src20, dst, selector) {                    \
    __di mask = (selector & 0x300000003LL) * 0x04040404LL + 0x0302010003020100LL;   \
    __di __tmp0 = __builtin_e2k_pshufb (src11, src10, mask);                        \
    __di __tmp1 = __builtin_e2k_pshufb (src21, src20, mask);                        \
    mask = __builtin_e2k_pcmpeqw (selector & 0x400000004LL, 0x400000004LL);         \
    dst = __builtin_e2k_pmerge (__tmp0, __tmp1, mask);                              \
    __tmp0 = (m2z | ((__di) m2z << 32)) ^ ((selector >> 3) & 0x0000000100000001LL); \
    dst &= ~__builtin_e2k_pcmpeqw (__tmp0, 0x0000000300000003LL);                   \
}

/* перестановка 4-х даблов (64F) из src1 и src2 по значениям в selector и константе m2z */
__E2K_INLINE __E2K_WARNING (__v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermil2pd (__v2df src1, __v2df src2, __v2di selector, const int m2z))
{
    type_union_128 s1, s2, sel, dst;
    s1.__v2df = src1;
    s2.__v2df = src2;
    sel.__v2di = selector;
    VPERMIL_64F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l0, sel.l.l0);
    VPERMIL_64F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l1, sel.l.l1);
    return dst.__v2df;
}

/* перестановка 8-ми флотов (32F) из src1 и src2 по значениям в selector и константе m2z */
__E2K_INLINE __E2K_WARNING (__v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermil2ps (__v4sf src1, __v4sf src2, __v4si selector, const int m2z))
{
    type_union_128 s1, s2, sel, dst;
    s1.__v4sf = src1;
    s2.__v4sf = src2;
    sel.__v4si = selector;
    VPERMIL_32F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l0, sel.l.l0);
    VPERMIL_32F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l1, sel.l.l1);
    return dst.__v4sf;
}

/* перестановка 8-ми даблов (64F) из src1 и src2 по значениям в selector и константе m2z */
__E2K_INLINE __E2K_WARNING (__v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermil2pd256 (__v4df src1, __v4df src2, __v4di selector, const int m2z))
{
    type_union_256 s1, s2, sel, dst;
    s1.__v4df = src1;
    s2.__v4df = src2;
    sel.__v4di = selector;
    VPERMIL_64F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l0, sel.l.l0);
    VPERMIL_64F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l1, sel.l.l1);
    VPERMIL_64F (s1.l.l3, s1.l.l2, s2.l.l3, s2.l.l2, dst.l.l2, sel.l.l2);
    VPERMIL_64F (s1.l.l3, s1.l.l2, s2.l.l3, s2.l.l2, dst.l.l3, sel.l.l3);
    return dst.__v4df;
}

/* перестановка 16-ти флотов (32F) из src1 и src2 по значениям в selector и константе m2z */
__E2K_INLINE __E2K_WARNING (__v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vpermil2ps256 (__v8sf src1, __v8sf src2, __v8si selector, const int m2z))
{
    type_union_256 s1, s2, sel, dst;
    s1.__v8sf = src1;
    s2.__v8sf = src2;
    sel.__v8si = selector;
    VPERMIL_32F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l0, sel.l.l0);
    VPERMIL_32F (s1.l.l1, s1.l.l0, s2.l.l1, s2.l.l0, dst.l.l1, sel.l.l1);
    VPERMIL_32F (s1.l.l3, s1.l.l2, s2.l.l3, s2.l.l2, dst.l.l2, sel.l.l2);
    VPERMIL_32F (s1.l.l3, s1.l.l2, s2.l.l3, s2.l.l2, dst.l.l3, sel.l.l3);
    return dst.__v8sf;
}

#undef MULADD_SAT_16S
#undef MULADD_SAT_16S_32S
#undef MULADD_MOD_16S_32S
#undef MULADD_SAT_32S
#undef MULADD_MOD_32S
#undef MULADD_SAT_32S_64S
#undef MULADDHOR_SAT_16S_32S
#undef __PSHUFB32
#undef __BITREV_64U_INPLACE
#undef VPPERM
#undef __SCL_8U
#undef __SCL_16U
#undef __SCLI_8U
#undef __SHL_8U
#undef __SHL_16U
#undef __SHL_32U
#undef __SHA_8U
#undef __SHA_16U
#undef __SHA_32U
#undef __VFRCZ_32F
#undef __VFRCZ_SINGLE_32F
#undef __VFRCZ_64F
#undef __VFRCZ_SINGLE_64F
#undef VPERMIL_64F
#undef VPERMIL_32F

#endif /* __XOP__ */

#ifdef __RDRND__

/*******************************************************************************/
/****************************** RDRND builtins *********************************/
/*******************************************************************************/

#define IA32 0x5deece66dLL
#define IC32 11

static __di __seed = 0x974b5d38a8b1cd57LL;

/* генерация случайного шортового (16S) числа. Возвращает 1 в случае готовности случайного числа */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdrand16_step (unsigned short *p)
{
    __seed = __seed * IA32 + IC32;
    *p = __seed;
    return 1;
}

/* генерация случайного интового (32S) числа. Возвращает 1 в случае готовности случайного числа */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdrand32_step (unsigned int *p)
{
    __seed = __seed * IA32 + IC32;
    *p = __seed;
    return 1;
}

/* генерация случайного лонгового (64S) числа. Возвращает 1 в случае готовности случайного числа */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdrand64_step (__di *p)
{
    __seed = __seed * IA32 + IC32;
    *p = __seed;
    return 1;
}

#undef IA32
#undef IC32

#endif /* __RDRND__ */

#ifdef __RDSEED__

/*******************************************************************************/
/****************************** RDSEED builtins ********************************/
/*******************************************************************************/

#define IA32 0x5deece66dLL
#define IC32 11

static __di __seed1 = 0x75dc1b8a83d5b479LL;

/* генерация случайного шортового (16S) числа. Возвращает 1 в случае готовности случайного числа */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdseed_hi_step (unsigned short *p)
{
    __seed1 = __seed1 * IA32 + IC32;
    *p = __seed1;
    return 1;
}

/* генерация случайного интового (32S) числа. Возвращает 1 в случае готовности случайного числа */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdseed_si_step (unsigned int *p)
{
    __seed1 = __seed1 * IA32 + IC32;
    *p = __seed1;
    return 1;
}

/* генерация случайного лонгового (64S) числа. Возвращает 1 в случае готовности случайного числа */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdseed_di_step (__di *p)
{
    __seed1 = __seed1 * IA32 + IC32;
    *p = __seed1;
    return 1;
}

#undef IA32
#undef IC32

#endif /* __RDSEED__ */

#ifdef __F16C__

/*******************************************************************************/
/******************************* F16C builtins *********************************/
/*******************************************************************************/

#define K2IN37 7.2759576e-12f /* 2^-37 */

#define __16F_TO_32F(src, dst) {                                 \
    unsigned __x = src;                                          \
    unsigned __exp = __x & 0x7c00;                               \
    unsigned __mant = (__x & 0x3ff) << 13;                       \
    type_union_32 __res;                                         \
    if (__exp == 0) { /* денормализованные и 0 */                \
        __res.f = (float) __mant * K2IN37;                       \
    }                                                            \
    else if (__exp == 0x7c00) { /* inf/nan */                    \
        __res.i = 0x7f800000 | __mant;                           \
    }                                                            \
    else { /* нормальные */                                      \
        __res.i = ((__exp + ((127 - 15) << 10)) << 13) | __mant; \
    }                                                            \
    dst = __res.i | ((__x & 0x8000) << 16);                      \
}

#define __ROUND_32F_TO_16F(mant, shift, sign, rc, dst) {              \
    int addon2 = 1 << shift;                                          \
    int addon = addon2 >> 1;                                          \
    dst = mant;                                                       \
    if (rc == 0) { /* к ближайшему (rint) */                          \
        dst = mant + addon;                                           \
        if ((dst & (addon2 - 1)) == 0 && (dst & addon2)) {            \
            dst -= addon2;                                            \
        }                                                             \
    }                                                                 \
    else if (rc != 3) { /* округление не к 0 (trunc) */               \
        /* rc=1 ->округление к -inf (floor), rc=2 -> к +inf (ceil) */ \
        if ((sign && rc == 1) || (sign == 0 && rc == 2)) {            \
            dst = mant + (addon2 - 1);                                \
        }                                                             \
    }                                                                 \
    dst >>= shift;                                                    \
}

#define __32F_TO_16F(src, rc, dst) {                                      \
    unsigned __x = src;                                                   \
    unsigned __exp = __x & 0x7f800000;                                    \
    unsigned __mant = __x & 0x7fffff;                                     \
    unsigned __sign = __x & 0x80000000;                                   \
    int __res;                                                            \
    if (__exp == 0) { /* денормализованные и 0 */                         \
        if (__mant) { /* денормализованные */                             \
            __res = (__sign && rc == 1) || (__sign == 0 && rc == 2);      \
        }                                                                 \
        else __res = 0;                                                   \
    }                                                                     \
    else if (__exp == 0x7f800000) { /* inf/nan */                         \
        __res = 0x7c00 | (__mant >> 13);                                  \
    }                                                                     \
    else { /* нормальные */                                               \
        __mant |= 0x800000;                                               \
        __ROUND_32F_TO_16F (__mant, 13, __sign, rc, __res)                \
        __res += ((int)(__exp + ((15 - 128) << 23)) >> 13);               \
        if (__res < 0x400) { /* денормализованные и 0 в результате */     \
            int shift = - (__res >> 10);                                  \
            if (shift >= 11) { /* 0 или почти 0 */                        \
                __res = (__sign && rc == 1) || (__sign == 0 && rc == 2);  \
            }                                                             \
            else { /* округляем денормализованное */                      \
                __ROUND_32F_TO_16F (__mant, shift + 14, __sign, rc, __res)\
            }                                                             \
        }                                                                 \
        else if (__res >= 0x7c00) { /* результат больше максимального */  \
            __res = ((rc == 3) || (__sign == 0 && rc == 1)                \
                             || (__sign && rc == 2)) ? 0x7bff : 0x7c00;   \
        }                                                                 \
    }                                                                     \
    dst = __res | (__sign >> 16);                                         \
}

/* преобразование 4-х 16-ти разрядных плавающих числа в 4 флота (32F) */
__E2K_INLINE __E2K_WARNING (__v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vcvtph2ps (__v8hi src))
{
    type_union_128 s, dst;
    s.__v8hi = src;
    __16F_TO_32F (s.l.l0      , dst.i.i0);
    __16F_TO_32F (s.l.l0 >> 16, dst.i.i1);
    __16F_TO_32F (s.l.l0 >> 32, dst.i.i2);
    __16F_TO_32F (s.l.l0 >> 48, dst.i.i3);
    return dst.__v4sf;
}

/* преобразование 8-ми 16-ти разрядных плавающих (16F) в 8 флотов (32F) */
__E2K_INLINE __E2K_WARNING (__v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vcvtph2ps256 (__v8hi src))
{
    type_union_128 s;
    type_union_256 dst;
    s.__v8hi = src;
    __16F_TO_32F (s.l.l0      , dst.i.i0);
    __16F_TO_32F (s.l.l0 >> 16, dst.i.i1);
    __16F_TO_32F (s.l.l0 >> 32, dst.i.i2);
    __16F_TO_32F (s.l.l0 >> 48, dst.i.i3);
    __16F_TO_32F (s.l.l1      , dst.i.i4);
    __16F_TO_32F (s.l.l1 >> 16, dst.i.i5);
    __16F_TO_32F (s.l.l1 >> 32, dst.i.i6);
    __16F_TO_32F (s.l.l1 >> 48, dst.i.i7);
    return dst.__v8sf;
}

/* преобразование 4-х флотов (32F) в 4-ре 16-ти разрядных плавающих (16F)
 * в заданном режиме округления */
__E2K_INLINE __E2K_WARNING (__v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vcvtps2ph (__v4sf src, const int rc))
{
    type_union_128 s, dst;
    s.__v4sf = src;
    int round;
    if (rc & 4) {
        __GETPFPFR (round);
        round >>= 13;
    }
    else round = rc;
    round &= 3;
    __32F_TO_16F (s.l.l0      , round, dst.h.h0);
    __32F_TO_16F (s.l.l0 >> 32, round, dst.h.h1);
    __32F_TO_16F (s.l.l1      , round, dst.h.h2);
    __32F_TO_16F (s.l.l1 >> 32, round, dst.h.h3);
    dst.l.l1 = 0;
    return dst.__v8hi;
}

/* преобразование 8-ми флотов (32F) в 8 16-ти разрядных плавающих (16F)
 * в заданном режиме округления */
__E2K_INLINE __E2K_WARNING (__v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vcvtps2ph256 (__v8sf src, const int rc))
{
    type_union_256 s;
    type_union_128 dst;
    s.__v8sf = src;
    int round;
    if (rc & 4) {
        __GETPFPFR (round);
        round >>= 13;
    }
    else round = rc;
    round &= 3;
    __32F_TO_16F (s.l.l0      , round, dst.h.h0);
    __32F_TO_16F (s.l.l0 >> 32, round, dst.h.h1);
    __32F_TO_16F (s.l.l1      , round, dst.h.h2);
    __32F_TO_16F (s.l.l1 >> 32, round, dst.h.h3);
    __32F_TO_16F (s.l.l2      , round, dst.h.h4);
    __32F_TO_16F (s.l.l2 >> 32, round, dst.h.h5);
    __32F_TO_16F (s.l.l3      , round, dst.h.h6);
    __32F_TO_16F (s.l.l3 >> 32, round, dst.h.h7);
    return dst.__v8hi;
}

/*#undef K2IN37*/
/*#undef __16F_TO_32F*/
/*#undef __ROUND_32F_TO_16F*/
/*#undef __32F_TO_16F*/

#endif /* __F16C__ */

/*******************************************************************************/
/******************************* MISC builtins *********************************/
/*******************************************************************************/

/* номер старшей единицы в инте (32U). Для 0 результат не определен, но возвращается -1 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bsrsi (int src)
{
    int dst;
    __CLZ (dst, src); /* count leading zeros */
    return 31 - dst;
}

/* номер старшей единицы в лонге (64U). Для 0 результат не определен, но возвращается -1 */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bsrdi (long long src)
{
    int dst;
    __CLZD (dst, src); /* count leading zeros */
    return 63 - dst;
}

#undef __BITREV_16U
#undef INT_SIZE
#undef __BITS4
#undef __CLZH
#undef __CLZ
#undef __CLZD

/* *****************************************************************************
 *                            Чтение регистров мониторов
 * *****************************************************************************/

/* чтение регистров мониторов производительности по номеру.
 * FIXME: не будем поддерживать. */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdpmc (int ind)
{
    return 0;
}

/* чтение счетчика тактов */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdtsc ()
{
    __di dst;
#pragma asm_inline
    asm ("rrd %%clkr, %0" : "=r" (dst));
    return dst;
}

/* чтение счетчика тактов, последовательное с остальными инструкциями.
 * И возврашение в параметре по адресу IA32_TSC_AUX - обычно это номер ядра.
 * FIXME - будем возвращать 0 в id ядра */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdtscp (unsigned int *a)
{
    __di dst;
#pragma asm_inline
    asm ("rrd %%clkr, %0" : "=r" (dst));
    *a = 0;
    return dst;
}

/* чтение идентификатора процессора из IA32_TSC_AUX.
 * FIXME: не будем поддерживать. */
__E2K_INLINE unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rdpid (void)
{
    return 0;
}

/* *****************************************************************************
 *                            Сдвиги
 * *****************************************************************************/

/* сдвиг влево байта (8U) циклический на младшие 3 разряда 2-го аргумента */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rolqi (unsigned char src, int shift)
{
    int dst = src << (shift & 0x7);
    return dst | (dst >> 8);
}

/* сдвиг влево шорта (16U) циклический на младшие 4 разряда 2-го аргумента */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rolhi (unsigned short src, int shift)
{
    int dst = src << (shift & 0xf);
    return dst | (dst >> 16);
}

/* сдвиг вправо байта (8U) циклический на младшие 3 разряда 2-го аргумента */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rorqi (unsigned char src, int shift)
{
    int dst = __builtin_e2k_scrs (src, shift & 0x7);
    return dst | (dst >> 24);
}

/* сдвиг вправо шорта (16U) циклический на младшие 4 разряда 2-го аргумента */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_rorhi (unsigned short src, int shift)
{
    int dst = __builtin_e2k_scrs (src, shift & 0xf);
    return dst | (dst >> 16);
}

/* *****************************************************************************
 *                     Сложение/вычитание с переносом
 * *****************************************************************************/

/* вычитание с переносом с выработкой переноса */
__E2K_INLINE unsigned char __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sbb_u32 (unsigned char __CF, unsigned int __X,
                        unsigned int __Y, unsigned int *__P)
{
    __di dst = __X - (__di) __Y - __CF;
    *__P = dst;
    return dst >> 63;
}

/* сложение с переносом с выработкой переноса */
__E2K_INLINE unsigned char __DEFAULT_FUNCS_ATTRS
__builtin_ia32_addcarryx_u32 (unsigned char __CF, unsigned int __X,
                              unsigned int __Y, unsigned int *__P)
{
    __di dst = __X + (__di) __Y + __CF;
    *__P = dst;
    return dst >> 32;
}

/* вычитание с переносом с выработкой переноса */
__E2K_INLINE unsigned char __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sbb_u64 (unsigned char __CF, __di __X, __di __Y, __di *__P)
{
#if __iset__ < 5
    __Y += __CF;
    *__P = __X - __Y;
    return (__Y < __CF) || (__Y > __X);
#else /* __iset__ < 5 */
    *__P = __builtin_e2k_subcd (__X, __Y, __CF);
    return __builtin_e2k_subcd_c (__X, __Y, __CF);
#endif /* __iset__ < 5 */
}

/* сложение с переносом с выработкой переноса */
__E2K_INLINE unsigned char __DEFAULT_FUNCS_ATTRS
__builtin_ia32_addcarryx_u64 (unsigned char __CF, __di __X, __di __Y, __di *__P)
{
#if __iset__ < 5
    __Y += __CF;
    *__P = __X + __Y;
    return (__Y < __CF) || (*__P < __X);
#else /* __iset__ < 5 */
    *__P = __builtin_e2k_addcd (__X, __Y, __CF);
    return __builtin_e2k_addcd_c (__X, __Y, __CF);
#endif /* __iset__ < 5 */
}

#ifdef __TBM__

/*******************************************************************************/
/******************************* TBM builtins **********************************/
/*******************************************************************************/

/* выделение битового поля из инта (32U). Разряды [7:0] 2-го операнда - индекс
 * начального бита, разряды [15:8] - длина поля */
__E2K_INLINE unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bextri_u32 (unsigned int src, const unsigned int op)
{
    unsigned int start = op & 0xff;
    unsigned int len = (op >> 8) & 0xff;
    unsigned int dst = __builtin_e2k_psrld (src, start);
    if (len < 32) {
        dst &= (1 << len) - 1;
    }
    return dst;
}

/* выделение битового поля из лонга (64U). Разряды [7:0] 2-го операнда - индекс
 * начального бита, разряды [15:8] - длина поля */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bextri_u64 (__di src, const unsigned int op)
{
    unsigned int start = op & 0xff;
    unsigned int len = (op >> 8) & 0xff;
    __di dst = __builtin_e2k_psrld (src, start);
    if (len < 64) {
        dst &= (1LL << len) - 1;
    }
    return dst;
}

#endif /* __TBM__ */

#ifdef __BMI__

/*******************************************************************************/
/******************************* BMI builtins **********************************/
/*******************************************************************************/

/* выделение битового поля из инта (32U). Разряды [7:0] 2-го операнда - индекс
 * начального бита, разряды [15:8] - длина поля */
__E2K_INLINE unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bextr_u32 (unsigned int src, unsigned int op)
{
    unsigned int start = op & 0xff;
    unsigned int len = (op >> 8) & 0xff;
    unsigned int dst = __builtin_e2k_psrld (src, start);
    if (len < 32) {
        dst &= (1 << len) - 1;
    }
    return dst;
}

/* выделение битового поля из лонга (64U). Разряды [7:0] 2-го операнда - индекс
 * начального бита, разряды [15:8] - длина поля */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bextr_u64 (__di src, __di op)
{
    unsigned int start = op & 0xff;
    unsigned int len = (op >> 8) & 0xff;
    __di dst = __builtin_e2k_psrld (src, start);
    if (len < 64) {
        dst &= (1LL << len) - 1;
    }
    return dst;
}

#endif /* __BMI__ */

#ifdef __PCLMUL__

/*******************************************************************************/
/***************************** PCLMUL builtins *********************************/
/*******************************************************************************/

/* простая версия
__v2di pclmul (__di x, __di y)
{
    __v2di dst;
    int i, j;

    dst.l.l0 = (y & 1) ? x : 0;
    dst.l.l1 = 0;

    for (i = 1; i < 64; i++) {
        if (y & (1LL << i)) {
            dst.l.l0 ^= x << i;
            dst.l.l1 ^= x >> (64 - i);
        }
    }
    return dst;
} */


/* умножение без переноса двух 64-х разрядных лонгов (64U), выбираемых из
 * половинок 2-х входных операндов константой в 3-м аргументе */
#if __iset__ >= 6
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pclmulqdq128 (__v2di src1, __v2di src2, const int op)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    __di x = (op & 1) ? s1.l.l1 : s1.l.l0;
    __di y = (op & 16) ? s2.l.l1 : s2.l.l0;
    dst.l.l0 = __builtin_e2k_clmull (x, y);
    dst.l.l1 = __builtin_e2k_clmulh (x, y);
#else /* __iset__ >= 6 */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pclmulqdq128 (__v2di src1, __v2di src2, const int op))
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    __di x = (op & 1) ? s1.l.l1 : s1.l.l0;
    __di y = (op & 16) ? s2.l.l1 : s2.l.l0;
    __di tmp0, tmp1;
    __di hi[16], lo[16];

    /* заполнение 1-м аргументом таблицы на 16 элементов (53 операции) */
    lo[ 0] = 0;               hi[ 0] = 0;
    lo[ 1] = x;               hi[ 1] = 0;
    lo[ 2] = x << 1;          hi[ 2] = x >> 63;
    lo[ 3] = lo[ 2] ^ x;      hi[ 3] = hi[ 2];
    lo[ 4] = x << 2;          hi[ 4] = x >> 62;
    lo[ 5] = lo[ 4] ^ x;      hi[ 5] = hi[ 4];
    lo[ 6] = lo[ 4] ^ lo[ 2]; hi[ 6] = hi[ 4] ^ hi[ 2];
    lo[ 7] = lo[ 4] ^ lo[ 3]; hi[ 7] = hi[ 6];
    lo[ 8] = x << 3;          hi[ 8] = x >> 61;
    lo[ 9] = lo[ 8] ^ x;      hi[ 9] = hi[ 8];
    lo[10] = lo[ 8] ^ lo[ 2]; hi[10] = hi[ 8] ^ hi[ 2];
    lo[11] = lo[ 8] ^ lo[ 3]; hi[11] = hi[10];
    lo[12] = lo[ 8] ^ lo[ 4]; hi[12] = hi[ 8] ^ hi[ 4];
    lo[13] = lo[ 8] ^ lo[ 5]; hi[13] = hi[12];
    lo[14] = lo[ 8] ^ lo[ 6]; hi[14] = hi[ 8] ^ hi[ 6];
    lo[15] = lo[ 8] ^ lo[ 7]; hi[15] = hi[14];
    /* умножение по 4 разряда 2-го аргумента (168/154 операций) */
    tmp0  = lo[y & 0xf];       tmp1  =  hi[y & 0xf];                              y >>= 4;
    tmp0 ^= lo[y & 0xf] <<  4; tmp1 ^= (hi[y & 0xf] <<  4) | (lo[y & 0xf] >> 60); y >>= 4;
    tmp0 ^= lo[y & 0xf] <<  8; tmp1 ^= __builtin_e2k_pshufb (hi[y & 0xf], lo[y & 0xf],0x8080808080800807LL); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 12; tmp1 ^= (hi[y & 0xf] << 12) | (lo[y & 0xf] >> 52); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 16; tmp1 ^= __builtin_e2k_pshufb (hi[y & 0xf], lo[y & 0xf],0x8080808080080706LL); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 20; tmp1 ^= (hi[y & 0xf] << 20) | (lo[y & 0xf] >> 44); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 24; tmp1 ^= __builtin_e2k_pshufb (hi[y & 0xf], lo[y & 0xf],0x8080808008070605LL); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 28; tmp1 ^= (hi[y & 0xf] << 28) | (lo[y & 0xf] >> 36); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 32; tmp1 ^= __builtin_e2k_pshufb (hi[y & 0xf], lo[y & 0xf],0x8080800807060504LL); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 36; tmp1 ^= (hi[y & 0xf] << 36) | (lo[y & 0xf] >> 28); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 40; tmp1 ^= __builtin_e2k_pshufb (hi[y & 0xf], lo[y & 0xf],0x8080080706050403LL); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 44; tmp1 ^= (hi[y & 0xf] << 44) | (lo[y & 0xf] >> 20); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 48; tmp1 ^= __builtin_e2k_pshufb (hi[y & 0xf], lo[y & 0xf],0x8008070605040302LL); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 52; tmp1 ^= (hi[y & 0xf] << 52) | (lo[y & 0xf] >> 12); y >>= 4;
    tmp0 ^= lo[y & 0xf] << 56; tmp1 ^= __builtin_e2k_pshufb (hi[y & 0xf], lo[y & 0xf],0x0807060504030201LL); y >>= 4;
    tmp0 ^= lo[y      ] << 60; tmp1 ^= (hi[y      ] << 60) | (lo[y      ] >>  4);
    dst.l.l0 = tmp0;
    dst.l.l1 = tmp1;
#endif /* __iset__ >= 6 */
    return dst.__v2di;
}

#endif /* __PCLMUL__ */

#ifdef __AES__

/*******************************************************************************/
/******************************* AES builtins **********************************/
/*******************************************************************************/

/* see: https://polarssl.org/aes-source-code */

/* Forward S-box */
static const unsigned char FSb[256] = {
   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

/* Reverse S-box */
static const unsigned char RSb[256] = {
   0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
   0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
   0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
   0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
   0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
   0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
   0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
   0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
   0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
   0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
   0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
   0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
   0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
   0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
   0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
   0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

/* Forward tables */
#define FT \
    V(A5,63,63,C6), V(84,7C,7C,F8), V(99,77,77,EE), V(8D,7B,7B,F6), \
    V(0D,F2,F2,FF), V(BD,6B,6B,D6), V(B1,6F,6F,DE), V(54,C5,C5,91), \
    V(50,30,30,60), V(03,01,01,02), V(A9,67,67,CE), V(7D,2B,2B,56), \
    V(19,FE,FE,E7), V(62,D7,D7,B5), V(E6,AB,AB,4D), V(9A,76,76,EC), \
    V(45,CA,CA,8F), V(9D,82,82,1F), V(40,C9,C9,89), V(87,7D,7D,FA), \
    V(15,FA,FA,EF), V(EB,59,59,B2), V(C9,47,47,8E), V(0B,F0,F0,FB), \
    V(EC,AD,AD,41), V(67,D4,D4,B3), V(FD,A2,A2,5F), V(EA,AF,AF,45), \
    V(BF,9C,9C,23), V(F7,A4,A4,53), V(96,72,72,E4), V(5B,C0,C0,9B), \
    V(C2,B7,B7,75), V(1C,FD,FD,E1), V(AE,93,93,3D), V(6A,26,26,4C), \
    V(5A,36,36,6C), V(41,3F,3F,7E), V(02,F7,F7,F5), V(4F,CC,CC,83), \
    V(5C,34,34,68), V(F4,A5,A5,51), V(34,E5,E5,D1), V(08,F1,F1,F9), \
    V(93,71,71,E2), V(73,D8,D8,AB), V(53,31,31,62), V(3F,15,15,2A), \
    V(0C,04,04,08), V(52,C7,C7,95), V(65,23,23,46), V(5E,C3,C3,9D), \
    V(28,18,18,30), V(A1,96,96,37), V(0F,05,05,0A), V(B5,9A,9A,2F), \
    V(09,07,07,0E), V(36,12,12,24), V(9B,80,80,1B), V(3D,E2,E2,DF), \
    V(26,EB,EB,CD), V(69,27,27,4E), V(CD,B2,B2,7F), V(9F,75,75,EA), \
    V(1B,09,09,12), V(9E,83,83,1D), V(74,2C,2C,58), V(2E,1A,1A,34), \
    V(2D,1B,1B,36), V(B2,6E,6E,DC), V(EE,5A,5A,B4), V(FB,A0,A0,5B), \
    V(F6,52,52,A4), V(4D,3B,3B,76), V(61,D6,D6,B7), V(CE,B3,B3,7D), \
    V(7B,29,29,52), V(3E,E3,E3,DD), V(71,2F,2F,5E), V(97,84,84,13), \
    V(F5,53,53,A6), V(68,D1,D1,B9), V(00,00,00,00), V(2C,ED,ED,C1), \
    V(60,20,20,40), V(1F,FC,FC,E3), V(C8,B1,B1,79), V(ED,5B,5B,B6), \
    V(BE,6A,6A,D4), V(46,CB,CB,8D), V(D9,BE,BE,67), V(4B,39,39,72), \
    V(DE,4A,4A,94), V(D4,4C,4C,98), V(E8,58,58,B0), V(4A,CF,CF,85), \
    V(6B,D0,D0,BB), V(2A,EF,EF,C5), V(E5,AA,AA,4F), V(16,FB,FB,ED), \
    V(C5,43,43,86), V(D7,4D,4D,9A), V(55,33,33,66), V(94,85,85,11), \
    V(CF,45,45,8A), V(10,F9,F9,E9), V(06,02,02,04), V(81,7F,7F,FE), \
    V(F0,50,50,A0), V(44,3C,3C,78), V(BA,9F,9F,25), V(E3,A8,A8,4B), \
    V(F3,51,51,A2), V(FE,A3,A3,5D), V(C0,40,40,80), V(8A,8F,8F,05), \
    V(AD,92,92,3F), V(BC,9D,9D,21), V(48,38,38,70), V(04,F5,F5,F1), \
    V(DF,BC,BC,63), V(C1,B6,B6,77), V(75,DA,DA,AF), V(63,21,21,42), \
    V(30,10,10,20), V(1A,FF,FF,E5), V(0E,F3,F3,FD), V(6D,D2,D2,BF), \
    V(4C,CD,CD,81), V(14,0C,0C,18), V(35,13,13,26), V(2F,EC,EC,C3), \
    V(E1,5F,5F,BE), V(A2,97,97,35), V(CC,44,44,88), V(39,17,17,2E), \
    V(57,C4,C4,93), V(F2,A7,A7,55), V(82,7E,7E,FC), V(47,3D,3D,7A), \
    V(AC,64,64,C8), V(E7,5D,5D,BA), V(2B,19,19,32), V(95,73,73,E6), \
    V(A0,60,60,C0), V(98,81,81,19), V(D1,4F,4F,9E), V(7F,DC,DC,A3), \
    V(66,22,22,44), V(7E,2A,2A,54), V(AB,90,90,3B), V(83,88,88,0B), \
    V(CA,46,46,8C), V(29,EE,EE,C7), V(D3,B8,B8,6B), V(3C,14,14,28), \
    V(79,DE,DE,A7), V(E2,5E,5E,BC), V(1D,0B,0B,16), V(76,DB,DB,AD), \
    V(3B,E0,E0,DB), V(56,32,32,64), V(4E,3A,3A,74), V(1E,0A,0A,14), \
    V(DB,49,49,92), V(0A,06,06,0C), V(6C,24,24,48), V(E4,5C,5C,B8), \
    V(5D,C2,C2,9F), V(6E,D3,D3,BD), V(EF,AC,AC,43), V(A6,62,62,C4), \
    V(A8,91,91,39), V(A4,95,95,31), V(37,E4,E4,D3), V(8B,79,79,F2), \
    V(32,E7,E7,D5), V(43,C8,C8,8B), V(59,37,37,6E), V(B7,6D,6D,DA), \
    V(8C,8D,8D,01), V(64,D5,D5,B1), V(D2,4E,4E,9C), V(E0,A9,A9,49), \
    V(B4,6C,6C,D8), V(FA,56,56,AC), V(07,F4,F4,F3), V(25,EA,EA,CF), \
    V(AF,65,65,CA), V(8E,7A,7A,F4), V(E9,AE,AE,47), V(18,08,08,10), \
    V(D5,BA,BA,6F), V(88,78,78,F0), V(6F,25,25,4A), V(72,2E,2E,5C), \
    V(24,1C,1C,38), V(F1,A6,A6,57), V(C7,B4,B4,73), V(51,C6,C6,97), \
    V(23,E8,E8,CB), V(7C,DD,DD,A1), V(9C,74,74,E8), V(21,1F,1F,3E), \
    V(DD,4B,4B,96), V(DC,BD,BD,61), V(86,8B,8B,0D), V(85,8A,8A,0F), \
    V(90,70,70,E0), V(42,3E,3E,7C), V(C4,B5,B5,71), V(AA,66,66,CC), \
    V(D8,48,48,90), V(05,03,03,06), V(01,F6,F6,F7), V(12,0E,0E,1C), \
    V(A3,61,61,C2), V(5F,35,35,6A), V(F9,57,57,AE), V(D0,B9,B9,69), \
    V(91,86,86,17), V(58,C1,C1,99), V(27,1D,1D,3A), V(B9,9E,9E,27), \
    V(38,E1,E1,D9), V(13,F8,F8,EB), V(B3,98,98,2B), V(33,11,11,22), \
    V(BB,69,69,D2), V(70,D9,D9,A9), V(89,8E,8E,07), V(A7,94,94,33), \
    V(B6,9B,9B,2D), V(22,1E,1E,3C), V(92,87,87,15), V(20,E9,E9,C9), \
    V(49,CE,CE,87), V(FF,55,55,AA), V(78,28,28,50), V(7A,DF,DF,A5), \
    V(8F,8C,8C,03), V(F8,A1,A1,59), V(80,89,89,09), V(17,0D,0D,1A), \
    V(DA,BF,BF,65), V(31,E6,E6,D7), V(C6,42,42,84), V(B8,68,68,D0), \
    V(C3,41,41,82), V(B0,99,99,29), V(77,2D,2D,5A), V(11,0F,0F,1E), \
    V(CB,B0,B0,7B), V(FC,54,54,A8), V(D6,BB,BB,6D), V(3A,16,16,2C)

#define V(a,b,c,d) 0x##a##b##c##d
static const unsigned int FT0[256] = { FT };
#undef V

#define V(a,b,c,d) 0x##b##c##d##a
static const unsigned int FT1[256] = { FT };
#undef V

#define V(a,b,c,d) 0x##c##d##a##b
static const unsigned int FT2[256] = { FT };
#undef V

#define V(a,b,c,d) 0x##d##a##b##c
static const unsigned int FT3[256] = { FT };
#undef V

#undef FT

/* Reverse tables */
#define RT \
    V(50,A7,F4,51), V(53,65,41,7E), V(C3,A4,17,1A), V(96,5E,27,3A), \
    V(CB,6B,AB,3B), V(F1,45,9D,1F), V(AB,58,FA,AC), V(93,03,E3,4B), \
    V(55,FA,30,20), V(F6,6D,76,AD), V(91,76,CC,88), V(25,4C,02,F5), \
    V(FC,D7,E5,4F), V(D7,CB,2A,C5), V(80,44,35,26), V(8F,A3,62,B5), \
    V(49,5A,B1,DE), V(67,1B,BA,25), V(98,0E,EA,45), V(E1,C0,FE,5D), \
    V(02,75,2F,C3), V(12,F0,4C,81), V(A3,97,46,8D), V(C6,F9,D3,6B), \
    V(E7,5F,8F,03), V(95,9C,92,15), V(EB,7A,6D,BF), V(DA,59,52,95), \
    V(2D,83,BE,D4), V(D3,21,74,58), V(29,69,E0,49), V(44,C8,C9,8E), \
    V(6A,89,C2,75), V(78,79,8E,F4), V(6B,3E,58,99), V(DD,71,B9,27), \
    V(B6,4F,E1,BE), V(17,AD,88,F0), V(66,AC,20,C9), V(B4,3A,CE,7D), \
    V(18,4A,DF,63), V(82,31,1A,E5), V(60,33,51,97), V(45,7F,53,62), \
    V(E0,77,64,B1), V(84,AE,6B,BB), V(1C,A0,81,FE), V(94,2B,08,F9), \
    V(58,68,48,70), V(19,FD,45,8F), V(87,6C,DE,94), V(B7,F8,7B,52), \
    V(23,D3,73,AB), V(E2,02,4B,72), V(57,8F,1F,E3), V(2A,AB,55,66), \
    V(07,28,EB,B2), V(03,C2,B5,2F), V(9A,7B,C5,86), V(A5,08,37,D3), \
    V(F2,87,28,30), V(B2,A5,BF,23), V(BA,6A,03,02), V(5C,82,16,ED), \
    V(2B,1C,CF,8A), V(92,B4,79,A7), V(F0,F2,07,F3), V(A1,E2,69,4E), \
    V(CD,F4,DA,65), V(D5,BE,05,06), V(1F,62,34,D1), V(8A,FE,A6,C4), \
    V(9D,53,2E,34), V(A0,55,F3,A2), V(32,E1,8A,05), V(75,EB,F6,A4), \
    V(39,EC,83,0B), V(AA,EF,60,40), V(06,9F,71,5E), V(51,10,6E,BD), \
    V(F9,8A,21,3E), V(3D,06,DD,96), V(AE,05,3E,DD), V(46,BD,E6,4D), \
    V(B5,8D,54,91), V(05,5D,C4,71), V(6F,D4,06,04), V(FF,15,50,60), \
    V(24,FB,98,19), V(97,E9,BD,D6), V(CC,43,40,89), V(77,9E,D9,67), \
    V(BD,42,E8,B0), V(88,8B,89,07), V(38,5B,19,E7), V(DB,EE,C8,79), \
    V(47,0A,7C,A1), V(E9,0F,42,7C), V(C9,1E,84,F8), V(00,00,00,00), \
    V(83,86,80,09), V(48,ED,2B,32), V(AC,70,11,1E), V(4E,72,5A,6C), \
    V(FB,FF,0E,FD), V(56,38,85,0F), V(1E,D5,AE,3D), V(27,39,2D,36), \
    V(64,D9,0F,0A), V(21,A6,5C,68), V(D1,54,5B,9B), V(3A,2E,36,24), \
    V(B1,67,0A,0C), V(0F,E7,57,93), V(D2,96,EE,B4), V(9E,91,9B,1B), \
    V(4F,C5,C0,80), V(A2,20,DC,61), V(69,4B,77,5A), V(16,1A,12,1C), \
    V(0A,BA,93,E2), V(E5,2A,A0,C0), V(43,E0,22,3C), V(1D,17,1B,12), \
    V(0B,0D,09,0E), V(AD,C7,8B,F2), V(B9,A8,B6,2D), V(C8,A9,1E,14), \
    V(85,19,F1,57), V(4C,07,75,AF), V(BB,DD,99,EE), V(FD,60,7F,A3), \
    V(9F,26,01,F7), V(BC,F5,72,5C), V(C5,3B,66,44), V(34,7E,FB,5B), \
    V(76,29,43,8B), V(DC,C6,23,CB), V(68,FC,ED,B6), V(63,F1,E4,B8), \
    V(CA,DC,31,D7), V(10,85,63,42), V(40,22,97,13), V(20,11,C6,84), \
    V(7D,24,4A,85), V(F8,3D,BB,D2), V(11,32,F9,AE), V(6D,A1,29,C7), \
    V(4B,2F,9E,1D), V(F3,30,B2,DC), V(EC,52,86,0D), V(D0,E3,C1,77), \
    V(6C,16,B3,2B), V(99,B9,70,A9), V(FA,48,94,11), V(22,64,E9,47), \
    V(C4,8C,FC,A8), V(1A,3F,F0,A0), V(D8,2C,7D,56), V(EF,90,33,22), \
    V(C7,4E,49,87), V(C1,D1,38,D9), V(FE,A2,CA,8C), V(36,0B,D4,98), \
    V(CF,81,F5,A6), V(28,DE,7A,A5), V(26,8E,B7,DA), V(A4,BF,AD,3F), \
    V(E4,9D,3A,2C), V(0D,92,78,50), V(9B,CC,5F,6A), V(62,46,7E,54), \
    V(C2,13,8D,F6), V(E8,B8,D8,90), V(5E,F7,39,2E), V(F5,AF,C3,82), \
    V(BE,80,5D,9F), V(7C,93,D0,69), V(A9,2D,D5,6F), V(B3,12,25,CF), \
    V(3B,99,AC,C8), V(A7,7D,18,10), V(6E,63,9C,E8), V(7B,BB,3B,DB), \
    V(09,78,26,CD), V(F4,18,59,6E), V(01,B7,9A,EC), V(A8,9A,4F,83), \
    V(65,6E,95,E6), V(7E,E6,FF,AA), V(08,CF,BC,21), V(E6,E8,15,EF), \
    V(D9,9B,E7,BA), V(CE,36,6F,4A), V(D4,09,9F,EA), V(D6,7C,B0,29), \
    V(AF,B2,A4,31), V(31,23,3F,2A), V(30,94,A5,C6), V(C0,66,A2,35), \
    V(37,BC,4E,74), V(A6,CA,82,FC), V(B0,D0,90,E0), V(15,D8,A7,33), \
    V(4A,98,04,F1), V(F7,DA,EC,41), V(0E,50,CD,7F), V(2F,F6,91,17), \
    V(8D,D6,4D,76), V(4D,B0,EF,43), V(54,4D,AA,CC), V(DF,04,96,E4), \
    V(E3,B5,D1,9E), V(1B,88,6A,4C), V(B8,1F,2C,C1), V(7F,51,65,46), \
    V(04,EA,5E,9D), V(5D,35,8C,01), V(73,74,87,FA), V(2E,41,0B,FB), \
    V(5A,1D,67,B3), V(52,D2,DB,92), V(33,56,10,E9), V(13,47,D6,6D), \
    V(8C,61,D7,9A), V(7A,0C,A1,37), V(8E,14,F8,59), V(89,3C,13,EB), \
    V(EE,27,A9,CE), V(35,C9,61,B7), V(ED,E5,1C,E1), V(3C,B1,47,7A), \
    V(59,DF,D2,9C), V(3F,73,F2,55), V(79,CE,14,18), V(BF,37,C7,73), \
    V(EA,CD,F7,53), V(5B,AA,FD,5F), V(14,6F,3D,DF), V(86,DB,44,78), \
    V(81,F3,AF,CA), V(3E,C4,68,B9), V(2C,34,24,38), V(5F,40,A3,C2), \
    V(72,C3,1D,16), V(0C,25,E2,BC), V(8B,49,3C,28), V(41,95,0D,FF), \
    V(71,01,A8,39), V(DE,B3,0C,08), V(9C,E4,B4,D8), V(90,C1,56,64), \
    V(61,84,CB,7B), V(70,B6,32,D5), V(74,5C,6C,48), V(42,57,B8,D0)

#define V(a,b,c,d) 0x##a##b##c##d
static const unsigned int RT0[256] = { RT };
#undef V

#define V(a,b,c,d) 0x##b##c##d##a
static const unsigned int RT1[256] = { RT };
#undef V

#define V(a,b,c,d) 0x##c##d##a##b
static const unsigned int RT2[256] = { RT };
#undef V

#define V(a,b,c,d) 0x##d##a##b##c
static const unsigned int RT3[256] = { RT };
#undef V

#undef RT

/* InvMixColumn tables */
#define IMC \
    V(00,00,00,00), V(0B,0D,09,0E), V(16,1A,12,1C), V(1D,17,1B,12), \
    V(2C,34,24,38), V(27,39,2D,36), V(3A,2E,36,24), V(31,23,3F,2A), \
    V(58,68,48,70), V(53,65,41,7E), V(4E,72,5A,6C), V(45,7F,53,62), \
    V(74,5C,6C,48), V(7F,51,65,46), V(62,46,7E,54), V(69,4B,77,5A), \
    V(B0,D0,90,E0), V(BB,DD,99,EE), V(A6,CA,82,FC), V(AD,C7,8B,F2), \
    V(9C,E4,B4,D8), V(97,E9,BD,D6), V(8A,FE,A6,C4), V(81,F3,AF,CA), \
    V(E8,B8,D8,90), V(E3,B5,D1,9E), V(FE,A2,CA,8C), V(F5,AF,C3,82), \
    V(C4,8C,FC,A8), V(CF,81,F5,A6), V(D2,96,EE,B4), V(D9,9B,E7,BA), \
    V(7B,BB,3B,DB), V(70,B6,32,D5), V(6D,A1,29,C7), V(66,AC,20,C9), \
    V(57,8F,1F,E3), V(5C,82,16,ED), V(41,95,0D,FF), V(4A,98,04,F1), \
    V(23,D3,73,AB), V(28,DE,7A,A5), V(35,C9,61,B7), V(3E,C4,68,B9), \
    V(0F,E7,57,93), V(04,EA,5E,9D), V(19,FD,45,8F), V(12,F0,4C,81), \
    V(CB,6B,AB,3B), V(C0,66,A2,35), V(DD,71,B9,27), V(D6,7C,B0,29), \
    V(E7,5F,8F,03), V(EC,52,86,0D), V(F1,45,9D,1F), V(FA,48,94,11), \
    V(93,03,E3,4B), V(98,0E,EA,45), V(85,19,F1,57), V(8E,14,F8,59), \
    V(BF,37,C7,73), V(B4,3A,CE,7D), V(A9,2D,D5,6F), V(A2,20,DC,61), \
    V(F6,6D,76,AD), V(FD,60,7F,A3), V(E0,77,64,B1), V(EB,7A,6D,BF), \
    V(DA,59,52,95), V(D1,54,5B,9B), V(CC,43,40,89), V(C7,4E,49,87), \
    V(AE,05,3E,DD), V(A5,08,37,D3), V(B8,1F,2C,C1), V(B3,12,25,CF), \
    V(82,31,1A,E5), V(89,3C,13,EB), V(94,2B,08,F9), V(9F,26,01,F7), \
    V(46,BD,E6,4D), V(4D,B0,EF,43), V(50,A7,F4,51), V(5B,AA,FD,5F), \
    V(6A,89,C2,75), V(61,84,CB,7B), V(7C,93,D0,69), V(77,9E,D9,67), \
    V(1E,D5,AE,3D), V(15,D8,A7,33), V(08,CF,BC,21), V(03,C2,B5,2F), \
    V(32,E1,8A,05), V(39,EC,83,0B), V(24,FB,98,19), V(2F,F6,91,17), \
    V(8D,D6,4D,76), V(86,DB,44,78), V(9B,CC,5F,6A), V(90,C1,56,64), \
    V(A1,E2,69,4E), V(AA,EF,60,40), V(B7,F8,7B,52), V(BC,F5,72,5C), \
    V(D5,BE,05,06), V(DE,B3,0C,08), V(C3,A4,17,1A), V(C8,A9,1E,14), \
    V(F9,8A,21,3E), V(F2,87,28,30), V(EF,90,33,22), V(E4,9D,3A,2C), \
    V(3D,06,DD,96), V(36,0B,D4,98), V(2B,1C,CF,8A), V(20,11,C6,84), \
    V(11,32,F9,AE), V(1A,3F,F0,A0), V(07,28,EB,B2), V(0C,25,E2,BC), \
    V(65,6E,95,E6), V(6E,63,9C,E8), V(73,74,87,FA), V(78,79,8E,F4), \
    V(49,5A,B1,DE), V(42,57,B8,D0), V(5F,40,A3,C2), V(54,4D,AA,CC), \
    V(F7,DA,EC,41), V(FC,D7,E5,4F), V(E1,C0,FE,5D), V(EA,CD,F7,53), \
    V(DB,EE,C8,79), V(D0,E3,C1,77), V(CD,F4,DA,65), V(C6,F9,D3,6B), \
    V(AF,B2,A4,31), V(A4,BF,AD,3F), V(B9,A8,B6,2D), V(B2,A5,BF,23), \
    V(83,86,80,09), V(88,8B,89,07), V(95,9C,92,15), V(9E,91,9B,1B), \
    V(47,0A,7C,A1), V(4C,07,75,AF), V(51,10,6E,BD), V(5A,1D,67,B3), \
    V(6B,3E,58,99), V(60,33,51,97), V(7D,24,4A,85), V(76,29,43,8B), \
    V(1F,62,34,D1), V(14,6F,3D,DF), V(09,78,26,CD), V(02,75,2F,C3), \
    V(33,56,10,E9), V(38,5B,19,E7), V(25,4C,02,F5), V(2E,41,0B,FB), \
    V(8C,61,D7,9A), V(87,6C,DE,94), V(9A,7B,C5,86), V(91,76,CC,88), \
    V(A0,55,F3,A2), V(AB,58,FA,AC), V(B6,4F,E1,BE), V(BD,42,E8,B0), \
    V(D4,09,9F,EA), V(DF,04,96,E4), V(C2,13,8D,F6), V(C9,1E,84,F8), \
    V(F8,3D,BB,D2), V(F3,30,B2,DC), V(EE,27,A9,CE), V(E5,2A,A0,C0), \
    V(3C,B1,47,7A), V(37,BC,4E,74), V(2A,AB,55,66), V(21,A6,5C,68), \
    V(10,85,63,42), V(1B,88,6A,4C), V(06,9F,71,5E), V(0D,92,78,50), \
    V(64,D9,0F,0A), V(6F,D4,06,04), V(72,C3,1D,16), V(79,CE,14,18), \
    V(48,ED,2B,32), V(43,E0,22,3C), V(5E,F7,39,2E), V(55,FA,30,20), \
    V(01,B7,9A,EC), V(0A,BA,93,E2), V(17,AD,88,F0), V(1C,A0,81,FE), \
    V(2D,83,BE,D4), V(26,8E,B7,DA), V(3B,99,AC,C8), V(30,94,A5,C6), \
    V(59,DF,D2,9C), V(52,D2,DB,92), V(4F,C5,C0,80), V(44,C8,C9,8E), \
    V(75,EB,F6,A4), V(7E,E6,FF,AA), V(63,F1,E4,B8), V(68,FC,ED,B6), \
    V(B1,67,0A,0C), V(BA,6A,03,02), V(A7,7D,18,10), V(AC,70,11,1E), \
    V(9D,53,2E,34), V(96,5E,27,3A), V(8B,49,3C,28), V(80,44,35,26), \
    V(E9,0F,42,7C), V(E2,02,4B,72), V(FF,15,50,60), V(F4,18,59,6E), \
    V(C5,3B,66,44), V(CE,36,6F,4A), V(D3,21,74,58), V(D8,2C,7D,56), \
    V(7A,0C,A1,37), V(71,01,A8,39), V(6C,16,B3,2B), V(67,1B,BA,25), \
    V(56,38,85,0F), V(5D,35,8C,01), V(40,22,97,13), V(4B,2F,9E,1D), \
    V(22,64,E9,47), V(29,69,E0,49), V(34,7E,FB,5B), V(3F,73,F2,55), \
    V(0E,50,CD,7F), V(05,5D,C4,71), V(18,4A,DF,63), V(13,47,D6,6D), \
    V(CA,DC,31,D7), V(C1,D1,38,D9), V(DC,C6,23,CB), V(D7,CB,2A,C5), \
    V(E6,E8,15,EF), V(ED,E5,1C,E1), V(F0,F2,07,F3), V(FB,FF,0E,FD), \
    V(92,B4,79,A7), V(99,B9,70,A9), V(84,AE,6B,BB), V(8F,A3,62,B5), \
    V(BE,80,5D,9F), V(B5,8D,54,91), V(A8,9A,4F,83), V(A3,97,46,8D)

#define V(a,b,c,d) 0x##a##b##c##d
static const unsigned int IMC0[256] = { IMC };
#undef V

#define V(a,b,c,d) 0x##b##c##d##a
static const unsigned int IMC1[256] = { IMC };
#undef V

#define V(a,b,c,d) 0x##c##d##a##b
static const unsigned int IMC2[256] = { IMC };
#undef V

#define V(a,b,c,d) 0x##d##a##b##c
static const unsigned int IMC3[256] = { IMC };
#undef V

#undef IMC

/*#define AESLUT(tab, v, s)   tab [((v) >> (s)) & 0xFF]*/
#if __iset__ <= 4
static const __di mask00FF = 0x00FF00FF00FF00FFull;
#define AESLUT(tab, v, s) ( (__di) *(unsigned int *) ( (char *) (tab) \
    + __builtin_e2k_getfd ((v) & ((s & 8) ? ~mask00FF: mask00FF), (((s) - 2) & 63) | (10 << 6)) ) )
#else
#define AESLUT(tab, v, s) ( (__di) *(unsigned int *) ( (char *) (tab) \
    + __builtin_e2k_getfzd ((v), (((s) - 2) & 63) | (10 << 6) | 2 << 13) ) )
#endif

/* Выполняет одну сессию AES дешифрования, используя 1-й аргумент как данные,
 * а 2-й - как ключ */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_aesdec128 (__v2di src, __v2di key))
{
    type_union_128 s, k, dst;
    s.__v2di = src;
    k.__v2di = key;
    __di x0 = s.l.l0;
    __di x1 = s.l.l1;

    /* InvShiftRows & InvSubBytes & InvMixColumns */
    dst.l.l0 = AESLUT (RT0, x0,  0) ^ AESLUT (RT1, x1, 40) ^ AESLUT (RT2, x1, 16) ^ AESLUT (RT3, x0, 56)
            ^ (AESLUT (RT0, x0, 32) ^ AESLUT (RT1, x0,  8) ^ AESLUT (RT2, x1, 48) ^ AESLUT (RT3, x1, 24)) << 32;
    dst.l.l1 = AESLUT (RT0, x1,  0) ^ AESLUT (RT1, x0, 40) ^ AESLUT (RT2, x0, 16) ^ AESLUT (RT3, x1, 56)
            ^ (AESLUT (RT0, x1, 32) ^ AESLUT (RT1, x1,  8) ^ AESLUT (RT2, x0, 48) ^ AESLUT (RT3, x0, 24)) << 32;
    dst.l.l0 ^= k.l.l0;
    dst.l.l1 ^= k.l.l1;
    return dst.__v2di;
}

/* Выполняет последнюю сессию AES дешифрования, используя 1-й аргумент как данные,
 * а 2-й - как ключ */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_aesdeclast128 (__v2di src, __v2di key))
{
    type_union_128 s, k, dst;
    s.__v2di = src;
    k.__v2di = key;
    unsigned int x0 = s.i.i0;
    unsigned int x1 = s.i.i1;
    unsigned int x2 = s.i.i2;
    unsigned int x3 = s.i.i3;

    /* InvShiftRows & InvSubBytes */
    dst.i.i0 =  RSb[ x0        & 0xff]        | (RSb[(x3 >>  8) & 0xff] <<  8)
             | (RSb[(x2 >> 16) & 0xff] << 16) | (RSb[(x1 >> 24) & 0xff] << 24);
    dst.i.i1 =  RSb[ x1        & 0xff]        | (RSb[(x0 >>  8) & 0xff] <<  8)
             | (RSb[(x3 >> 16) & 0xff] << 16) | (RSb[(x2 >> 24) & 0xff] << 24);
    dst.i.i2 =  RSb[ x2        & 0xff]        | (RSb[(x1 >>  8) & 0xff] <<  8)
             | (RSb[(x0 >> 16) & 0xff] << 16) | (RSb[(x3 >> 24) & 0xff] << 24);
    dst.i.i3 =  RSb[ x3        & 0xff]        | (RSb[(x2 >>  8) & 0xff] <<  8)
             | (RSb[(x1 >> 16) & 0xff] << 16) | (RSb[(x0 >> 24) & 0xff] << 24);
    dst.l.l0 ^= k.l.l0;
    dst.l.l1 ^= k.l.l1;
    return dst.__v2di;
}

/* Выполняет одну сессию AES шифрования, используя 1-й аргумент как данные,
 * а 2-й - как ключ */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_aesenc128 (__v2di src, __v2di key))
{
    type_union_128 s, k, dst;
    s.__v2di = src;
    k.__v2di = key;
    __di x0 = s.l.l0;
    __di x1 = s.l.l1;

    /* ShiftRows & SubBytes & MixColumns */
    dst.l.l0 = AESLUT (FT0, x0,  0) ^ AESLUT (FT1, x0, 40) ^ AESLUT (FT2, x1, 16) ^ AESLUT (FT3, x1, 56)
            ^ (AESLUT (FT0, x0, 32) ^ AESLUT (FT1, x1,  8) ^ AESLUT (FT2, x1, 48) ^ AESLUT (FT3, x0, 24)) << 32;
    dst.l.l1 = AESLUT (FT0, x1,  0) ^ AESLUT (FT1, x1, 40) ^ AESLUT (FT2, x0, 16) ^ AESLUT (FT3, x0, 56)
            ^ (AESLUT (FT0, x1, 32) ^ AESLUT (FT1, x0,  8) ^ AESLUT (FT2, x0, 48) ^ AESLUT (FT3, x1, 24)) << 32;
    dst.l.l0 ^= k.l.l0;
    dst.l.l1 ^= k.l.l1;
    return dst.__v2di;
}

/* Выполняет последнюю сессию AES шифрования, используя 1-й аргумент как данные,
 * а 2-й - как ключ */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_aesenclast128 (__v2di src, __v2di key))
{
    type_union_128 s, k, dst;
    s.__v2di = src;
    k.__v2di = key;
    unsigned int x0 = s.i.i0;
    unsigned int x1 = s.i.i1;
    unsigned int x2 = s.i.i2;
    unsigned int x3 = s.i.i3;

    /* ShiftRows & SubBytes */
    dst.i.i0 =  FSb[ x0        & 0xff]        | (FSb[(x1 >>  8) & 0xff] <<  8)
             | (FSb[(x2 >> 16) & 0xff] << 16) | (FSb[(x3 >> 24) & 0xff] << 24);
    dst.i.i1 =  FSb[ x1        & 0xff]        | (FSb[(x2 >>  8) & 0xff] <<  8)
             | (FSb[(x3 >> 16) & 0xff] << 16) | (FSb[(x0 >> 24) & 0xff] << 24);
    dst.i.i2 =  FSb[ x2        & 0xff]        | (FSb[(x3 >>  8) & 0xff] <<  8)
             | (FSb[(x0 >> 16) & 0xff] << 16) | (FSb[(x1 >> 24) & 0xff] << 24);
    dst.i.i3 =  FSb[ x3        & 0xff]        | (FSb[(x0 >>  8) & 0xff] <<  8)
             | (FSb[(x1 >> 16) & 0xff] << 16) | (FSb[(x2 >> 24) & 0xff] << 24);
    dst.l.l0 ^= k.l.l0;
    dst.l.l1 ^= k.l.l1;
    return dst.__v2di;
}

/* Выполняет InverseMixColumn операцию */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_aesimc128 (__v2di src))
{
    type_union_128 s, dst;
    s.__v2di = src;
    __di x0 = s.l.l0;
    __di x1 = s.l.l1;

    /* InvMixColumn */
    dst.l.l0 = AESLUT (IMC0, x0,  0) ^ AESLUT (IMC1, x0,  8) ^ AESLUT (IMC2, x0, 16) ^ AESLUT (IMC3, x0, 24)
            ^ (AESLUT (IMC0, x0, 32) ^ AESLUT (IMC1, x0, 40) ^ AESLUT (IMC2, x0, 48) ^ AESLUT (IMC3, x0, 56)) << 32;
    dst.l.l1 = AESLUT (IMC0, x1,  0) ^ AESLUT (IMC1, x1,  8) ^ AESLUT (IMC2, x1, 16) ^ AESLUT (IMC3, x1, 24)
            ^ (AESLUT (IMC0, x1, 32) ^ AESLUT (IMC1, x1, 40) ^ AESLUT (IMC2, x1, 48) ^ AESLUT (IMC3, x1, 56)) << 32;
    return dst.__v2di;
}

#define SUBWORD(src, dst)                                                   \
    dst =  FSb[ src        & 0xff]        | (FSb[(src >>  8) & 0xff] <<  8) \
        | (FSb[(src >> 16) & 0xff] << 16) | (FSb[(src >> 24) & 0xff] << 24) \

#define ROTWORD(src, dst) dst = __builtin_e2k_scrs (src, 8)

/* Генерит ключ сессии для входного AES ключа шифрования и константы
 * сессии во втором аргументе */
__E2K_INLINE __E2K_WARNING (__v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_aeskeygenassist128 (__v2di key, const int round))
{
    type_union_128 k, dst;
    k.__v2di = key;
    unsigned int rcon = round & 0xff;
    unsigned int x0, x1 = k.i.i1;
    unsigned int x2, x3 = k.i.i3;

    SUBWORD (x1, x0);
    ROTWORD (x0, x1);
    SUBWORD (x3, x2);
    ROTWORD (x2, x3);
    dst.i.i0 = x0;
    dst.i.i1 = x1 ^ rcon;
    dst.i.i2 = x2;
    dst.i.i3 = x3 ^ rcon;
    return dst.__v2di;
}

#undef SUBWORD
#undef ROTWORD
#undef AESLUT

#endif /* __AES__ */

#ifdef __SHA__

/*******************************************************************************/
/************************** SHA1 & SHA256 builtins *****************************/
/*******************************************************************************/

/* Выполняет промежуточные вычисления для следующих 4-х SHA1 сообщений */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sha1msg1 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.l.l1 = s1.l.l0 ^ s1.l.l1;
    dst.l.l0 = s1.l.l0 ^ s2.l.l1;
    return dst.__v4si;
}

/* Выполняет последние вычисления для следующих 4-х SHA1 сообщений */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sha1msg2 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
#if __iset__ <= 4
    dst.i.i3 = __builtin_e2k_scls (s1.i.i3 ^ s2.i.i2, 1);
    dst.i.i2 = __builtin_e2k_scls (s1.i.i2 ^ s2.i.i1, 1);
    dst.i.i1 = __builtin_e2k_scls (s1.i.i1 ^ s2.i.i0, 1);
#else /* __iset__ <= 4 */
    __v2di tmp = __builtin_e2k_qppermb (s1.__v2di, s2.__v2di, /* s2 << 32 */
                                        __builtin_e2k_qppackdl (0x0b0a090807060504LL, 0x0302010013121110LL));
    dst.__v2di = __builtin_e2k_qpsrcw (__builtin_e2k_qpxor (s1.__v2di, tmp), 31);
#endif /* __iset__ <= 4 */
    dst.i.i0 = __builtin_e2k_scls (s1.i.i0 ^ dst.i.i3, 1);
    return dst.__v4si;
}

/* Вычисляет SHA1 переменную состояния E после 4-х раундов операции из текущего состояния
 * переменной A. Вычисленное значение переменной E добавляется к входному операнду,
 * который содержит слова состояния */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sha1nexte (__v4si src1, __v4si src2)
{
    type_union_128 s1, dst;
    s1.__v4si = src1;
    dst.__v4si = src2;
    dst.i.i3 += __builtin_e2k_scls (s1.i.i3, 30);
    return dst.__v4si;
}

#define SHA1_ROUND(N)                                            \
    A1 = F (B, C, D) + __builtin_e2k_scls (A, 5) + W##N + E + K; \
    E = D;                                                       \
    D = C;                                                       \
    C = __builtin_e2k_scls (B, 30);                              \
    B = A;                                                       \
    A = A1

/* Выполняет 4 раунда SHA1, используя начальное состояние (A,B,C,D) из 1-го операнда и
 * предвычисленную сумму следующих 4-х сообщений и переменную состояния E из 2-го операнда.
 * Обновленное состояние (A,B,C,D) после 4-х раундов записывается в результат */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sha1rnds4 (__v4si src1, __v4si src2, const int indx))
{
    int A, B, C, D, E, A1, W0, W1, W2, W3;
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    A = s1.i.i3;
    B = s1.i.i2;
    C = s1.i.i1;
    D = s1.i.i0;
    E = 0;
    W0 = s2.i.i3;
    W1 = s2.i.i2;
    W2 = s2.i.i1;
    W3 = s2.i.i0;

    if ((indx & 3) == 0) {
#if __iset__ < 5
#define F(x,y,z) ((x & y) | (~x & z))
#else /* __iset__ < 5 */
#define F(x,y,z) (int) __builtin_e2k_plog (0xca, x, y, z)
#endif /* __iset__ < 5 */
#define K 0x5A827999
        SHA1_ROUND (0);
        SHA1_ROUND (1);
        SHA1_ROUND (2);
        SHA1_ROUND (3);
#undef K
#undef F
    }
    else if ((indx & 3) == 1) {
#if __iset__ < 5
#define F(x,y,z) (x ^ y ^ z)
#else /* __iset__ < 5 */
#define F(x,y,z) (int) __builtin_e2k_plog (0x96, x, y, z)
#endif /* __iset__ < 5 */
#define K 0x6ED9EBA1
        SHA1_ROUND (0);
        SHA1_ROUND (1);
        SHA1_ROUND (2);
        SHA1_ROUND (3);
#undef K
#undef F
    }
    else if ((indx & 3) == 2) {
#if __iset__ < 5
#define F(x,y,z) ((x & y) | (z & (x | y)))
#else /* __iset__ < 5 */
#define F(x,y,z) (int) __builtin_e2k_plog (0xe8, x, y, z)
#endif /* __iset__ < 5 */
#define K 0x8F1BBCDC
        SHA1_ROUND (0);
        SHA1_ROUND (1);
        SHA1_ROUND (2);
        SHA1_ROUND (3);
#undef K
#undef F
    }
    else /* if ((indx & 3) == 3) */ {
#if __iset__ < 5
#define F(x,y,z) (x ^ y ^ z)
#else /* __iset__ < 5 */
#define F(x,y,z) (int) __builtin_e2k_plog (0x96, x, y, z)
#endif /* __iset__ < 5 */
#define K 0xCA62C1D6
        SHA1_ROUND (0);
        SHA1_ROUND (1);
        SHA1_ROUND (2);
        SHA1_ROUND (3);
#undef K
#undef F
    }
    dst.i.i3 = A;
    dst.i.i2 = B;
    dst.i.i1 = C;
    dst.i.i0 = D;
    return dst.__v4si;
}

#if __iset__ < 5
#define S0(A)                                                                       \
    (__builtin_e2k_scrs (A, 7) ^ __builtin_e2k_scrs (A, 18) ^ ((unsigned) A >> 3))
#define S1(A)                                                                       \
    (__builtin_e2k_scrs (A, 17) ^ __builtin_e2k_scrs (A, 19) ^ ((unsigned) A >> 10))
#else /* __iset__ < 5 */
#define S0(A)                                                                       \
    (int) __builtin_e2k_plog (0x96, __builtin_e2k_scrs (A, 7),                      \
        __builtin_e2k_scrs (A, 18), (unsigned) (A) >> 3)
#define S1(A)                                                                       \
    (int) __builtin_e2k_plog (0x96, __builtin_e2k_scrs (A, 17),                     \
        __builtin_e2k_scrs (A, 19), (unsigned) (A) >> 10)
#endif /* __iset__ < 5 */

/* Выполняет промежуточные вычисления для следующих 4-х SHA256 сообщений */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sha256msg1 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.i.i3 = s1.i.i3 + S0 (s2.i.i0);
    dst.i.i2 = s1.i.i2 + S0 (s1.i.i3);
    dst.i.i1 = s1.i.i1 + S0 (s1.i.i2);
    dst.i.i0 = s1.i.i0 + S0 (s1.i.i1);
    return dst.__v4si;
}

/* Выполняет последние вычисления для следующих 4-х SHA256 сообщений */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sha256msg2 (__v4si src1, __v4si src2)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.i.i0 = s1.i.i0 + S1 (s2.i.i2);
    dst.i.i1 = s1.i.i1 + S1 (s2.i.i3);
    dst.i.i2 = s1.i.i2 + S1 (dst.i.i0);
    dst.i.i3 = s1.i.i3 + S1 (dst.i.i1);
    return dst.__v4si;
}

#if __iset__ < 5
#define SIGMA0(A)                                                                        \
    (__builtin_e2k_scrs (A, 2) ^ __builtin_e2k_scrs (A, 13) ^ __builtin_e2k_scrs (A, 22))
#define SIGMA1(A)                                                                        \
    (__builtin_e2k_scrs (A, 6) ^ __builtin_e2k_scrs (A, 11) ^ __builtin_e2k_scrs (A, 25))
#define CH(x,y,z) ((x & y) | (~x & z))
#define MA(x,y,z) ((x & y) | (z & (x | y)))
#else /* __iset__ < 5 */
#define SIGMA0(A)                                                \
    (int) __builtin_e2k_plog (0x96, __builtin_e2k_scrs (A, 2),   \
        __builtin_e2k_scrs (A, 13), __builtin_e2k_scrs (A, 22))
#define SIGMA1(A)                                                \
    (int) __builtin_e2k_plog (0x96, __builtin_e2k_scrs (A, 6),   \
        __builtin_e2k_scrs (A, 11), __builtin_e2k_scrs (A, 25))
#define CH(x,y,z) (int) __builtin_e2k_plog (0xca, x, y, z)
#define MA(x,y,z) (int) __builtin_e2k_plog (0xe8, x, y, z)
#endif /* __iset__ < 5 */

#define SHA256_ROUND(N)                                          \
    T2 = SIGMA0 (A) + MA (A, B, C);                              \
    T1 = H + SIGMA1 (E) + CH (E, F, G) + WK##N;                  \
    H = G;                                                       \
    G = F;                                                       \
    F = E;                                                       \
    E = D + T1;                                                  \
    D = C;                                                       \
    C = B;                                                       \
    B = A;                                                       \
    A = T1 + T2

/* Выполняет 2 раунда SHA256, используя начальное состояние (C,D,G,H) из 1-го
 * операнда и начальное состояние SHA256 (A,B,E,F) из 2-го операнда, предвычисленную
 * сумму сообщений следующих 2-х раундов и соответствующие константы раундов
 * из 3-го операнда. Обновленное состояние (A,B,E,F) записывается в результат */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_sha256rnds2 (__v4si src1, __v4si src2, __v4si src3))
{
    int A, B, C, D, E, F, G, H, T1, T2, WK0, WK1;
    type_union_128 s1, s2, s3, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    s3.__v4si = src3;
    A = s2.i.i3;
    B = s2.i.i2;
    C = s1.i.i3;
    D = s1.i.i2;
    E = s2.i.i1;
    F = s2.i.i0;
    G = s1.i.i1;
    H = s1.i.i0;
    WK1 = s3.i.i1;
    WK0 = s3.i.i0;

    SHA256_ROUND (0);
    SHA256_ROUND (1);
    dst.i.i3 = A;
    dst.i.i2 = B;
    dst.i.i1 = E;
    dst.i.i0 = F;
    return dst.__v4si;
}

#undef S0
#undef S1
#undef CH
#undef MA
#undef SIGMA0
#undef SIGMA1
#undef SHA1_ROUND
#undef SHA256_ROUND

#endif /* __SHA__ */

#ifdef __MWAITX__

/*******************************************************************************/
/***************************** MWAITX builtins *********************************/
/*******************************************************************************/

/* Мониторы */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_monitorx (void const *p, unsigned int __E, unsigned int __H)
{
/* FIXME: */
}

__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_mwaitx (unsigned int __E, unsigned int __H, unsigned int __C)
{
/* FIXME: */
}

#endif /* __MWAITX__ */

#ifdef __CLZERO__

/*******************************************************************************/
/***************************** CLZERO builtins *********************************/
/*******************************************************************************/

/* Обнуление строки кеша */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_clzero (void *p)
{
    __v2di *qp = (__v2di *) E2K_ALIGN_PTR_BACK (p, 64);
#if __iset__ <= 5
    ((__di *) qp)[0] = ((__di *) qp)[1] = ((__di *) qp)[2] = ((__di *) qp)[3] =
    ((__di *) qp)[4] = ((__di *) qp)[5] = ((__di *) qp)[6] = ((__di *) qp)[7] = 0;
#else /* __iset__ <= 5 */
    qp[0] = qp[1] = qp[2] = qp[3] = __builtin_e2k_qppackdl (0, 0);
#endif /* __iset__ <= 5 */
}

#endif /* __CLZERO__ */

#ifdef __CLFLUSHOPT__

/*******************************************************************************/
/*************************** CLFLUSHOPT builtins *******************************/
/*******************************************************************************/

/* Cache line contining p is flushed and invalidated from all caches in the
 * coherency domain */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_clflushopt (void const *p)
{
    __builtin_e2k_clflush (p);
}

#endif /* __CLFLUSHOPT__ */

#ifdef __CLWB__

/*******************************************************************************/
/****************************** CLWB builtins **********************************/
/*******************************************************************************/

/* Writes back to memory the cache line (if modified) that contains the linear
 * address specified with the memory operand */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_clwb (void const *p)
{
/* FIXME: */
}

#endif /* __CLWB__ */

#ifdef __BMI2__

/*******************************************************************************/
/****************************** BMI2 builtins **********************************/
/*******************************************************************************/

/* обнуление старших бит, начиная с бита, заданного в [7:0] разрядах 2-го операнда */
__E2K_INLINE unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bzhi_si (unsigned int src, unsigned int index)
{
    if ((index & 0xff) < 32) {
        src &= (1 << index) - 1;
    }
    return src;
}

/* обнуление старших бит, начиная с бита, заданного в [7:0] разрядах 2-го операнда */
__E2K_INLINE __di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_bzhi_di (__di src, __di index)
{
    if ((index & 0xff) < 64) {
        src &= (1LL << index) - 1;
    }
    return src;
}

/* расстановка бит из src на позиции, определенные "1" в mask */
__E2K_INLINE __E2K_WARNING (unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pdep_si (unsigned int src, unsigned int mask))
{
    int i, n = __builtin_e2k_popcnts (mask);
    unsigned int dst = 0;
    unsigned int lowbit;

    mask = __builtin_e2k_bitrevs (mask);

#pragma loop count (8)
    for (i = 0; i < n; i++) {
        lowbit = __builtin_e2k_lzcnts (mask);
        dst |= (src & 1) << lowbit;
        mask ^= 0x80000000u >> lowbit;
        src >>= 1;
    }
    return dst;
}

/* расстановка бит из src на позиции, определенные "1" в mask */
__E2K_INLINE __E2K_WARNING (__di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pdep_di (__di src, __di mask))
{
    int i, n = __builtin_e2k_popcntd (mask);
    __di dst = 0;
    __di lowbit;

    mask = __builtin_e2k_bitrevd (mask);

#pragma loop count (16)
    for (i = 0; i < n; i++) {
        lowbit = __builtin_e2k_lzcntd (mask);
        dst |= (src & 1) << lowbit;
        mask ^= 0x8000000000000000ull >> lowbit;
        src >>= 1;
    }
    return dst;
}

/* сборка бит из src из позиций, определенных "1" в mask */
__E2K_INLINE __E2K_WARNING (unsigned int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pext_si (unsigned int src, unsigned int mask))
{
    int i, n = __builtin_e2k_popcnts (mask);
    unsigned int dst = 0;
    unsigned int lowbit;

    mask = __builtin_e2k_bitrevs (mask);

#pragma loop count (8)
    for (i = 0; i < n; i++) {
        lowbit = __builtin_e2k_lzcnts (mask);
        dst = __builtin_e2k_scrs (dst, 1) | ((src >> lowbit) & 1);
        mask ^= 0x80000000u >> lowbit;
    }
    return __builtin_e2k_scls (dst, n - 1);
}

/* сборка бит из src из позиций, определенных "1" в mask */
__E2K_INLINE __E2K_WARNING (__di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pext_di (__di src, __di mask))
{
    int i, n = __builtin_e2k_popcntd (mask);
    __di dst = 0;
    __di lowbit;

    mask = __builtin_e2k_bitrevd (mask);

#pragma loop count (16)
    for (i = 0; i < n; i++) {
        lowbit = __builtin_e2k_lzcntd (mask);
        dst = __builtin_e2k_scrd (dst, 1) | ((src >> lowbit) & 1);
        mask ^= 0x8000000000000000ull >> lowbit;
    }
    return __builtin_e2k_scld (dst, n - 1);
}

#endif /* __BMI2__ */

#ifdef __AVX2__

/*******************************************************************************/
/****************************** AVX2 builtins **********************************/
/*******************************************************************************/

#define THREE_OPERAND_AVX_BUILTINS_VIA_2SSE(name_avx,name_sse,src_type,dst_type)          \
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                               \
__builtin_ia32_##name_avx (src_type src1, src_type src2, src_type src3)                   \
{                                                                                         \
    type_union_256 s1, s2, s3, dst;                                                       \
    s1.src_type = src1;                                                                   \
    s2.src_type = src2;                                                                   \
    s3.src_type = src3;                                                                   \
    dst.u##dst_type.v0 = __builtin_ia32_##name_sse (s1.u##src_type.v0, s2.u##src_type.v0, \
                                                    s3.u##src_type.v0);                   \
    dst.u##dst_type.v1 = __builtin_ia32_##name_sse (s1.u##src_type.v1, s2.u##src_type.v1, \
                                                    s3.u##src_type.v1);                   \
    return dst.dst_type;                                                                  \
}

#define ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE(name_avx,name_sse,src1_type,src2_type,dst_type)\
__E2K_INLINE dst_type __DEFAULT_FUNCS_ATTRS                                               \
__builtin_ia32_##name_avx (src1_type src1, src2_type src2)                                \
{                                                                                         \
    type_union_256 s1, dst;                                                               \
    s1.src1_type = src1;                                                                  \
    dst.u##dst_type.v0 = __builtin_ia32_##name_sse (s1.u##src1_type.v0, src2);            \
    dst.u##dst_type.v1 = __builtin_ia32_##name_sse (s1.u##src1_type.v1, src2);            \
    return dst.dst_type;                                                                  \
}

/* *****************************************************************************
 *         Множественное сложение абсолютных разностей беззнаковых байт
 * *****************************************************************************/

/* 2 раза по 8 сумм абсолютных разностей 4-х беззнаковых байт (8U) со сдвигом операндов
 * первого аргумента и 4-х беззнаковых байт (8U) второго аргумента с формированием 8-ми
 * беззнаковых шортов (16U) */
__E2K_INLINE __v32qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_mpsadbw256 (__v32qi src1, __v32qi src2, const int indx)
{
    type_union_256 s1, s2, dst;
    s1.__v32qi = src1;
    s2.__v32qi = src2;
    dst.u__v16hi.v0 = __builtin_ia32_mpsadbw128 (s1.u__v32qi.v0, s2.u__v32qi.v0, indx & 7);
    dst.u__v16hi.v1 = __builtin_ia32_mpsadbw128 (s1.u__v32qi.v1, s2.u__v32qi.v1, (indx >> 3) & 7);
    return dst.__v32qi;
}

/* *****************************************************************************
 *                            Абсолютное значение
 * *****************************************************************************/

/* абсолютные значения 32-х знаковых байт (8S) */
ONE_OPERAND_AVX_BUILTINS_VIA_2SSE (pabsb256, pabsb128, __v32qi, __v32qi)

/* абсолютные значения 16-ти знаковых шортов (16S) */
ONE_OPERAND_AVX_BUILTINS_VIA_2SSE (pabsw256, pabsw128, __v16hi, __v16hi)

/* абсолютные значения 8-ми знаковых интов (32S) */
ONE_OPERAND_AVX_BUILTINS_VIA_2SSE (pabsd256, pabsd128, __v8si, __v8si)

/* *****************************************************************************
 *                                 Упаковка
 * *****************************************************************************/

/* упаковка 16-ти знаковых интов (32S) в знаковые шорты (16S) с насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (packssdw256, packssdw128, __v8si, __v16hi)

/* упаковка 32-х знаковых шортов (16S) в знаковые байты (8S) с насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (packsswb256, packsswb128, __v16hi, __v32qi)

/* упаковка 16-ти знаковых интов (32S) в беззнаковые шорты (16U) с насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (packusdw256, packusdw128, __v8si, __v16hi)

/* упаковка 32-х знаковых шортов (16S) в беззнаковые байты (8U) с насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (packuswb256, packuswb128, __v16hi, __v32qi)

/* *****************************************************************************
 *                         Сложение и вычитание по модулю
 * *****************************************************************************/

/* сложение 32-х байт (8S/8U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddb256, paddb128, __v32qi, __v32qi)

/* сложение 16-ти шортов (16S/16U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddw256, paddw128, __v16hi, __v16hi)

/* сложение 8-ми интов (32S/32U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddd256, paddd128, __v8si, __v8si)

/* сложение 4-х лонгов (64S/64U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddq256, paddq128, __v4di, __v4di)

/* вычитание 32-х байт (8S/8U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubb256, psubb128, __v32qi, __v32qi)

/* вычитание 16-ти шортов (16S/16U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubw256, psubw128, __v16hi, __v16hi)

/* вычитание 8-ми интов (32S/32U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubd256, psubd128, __v8si, __v8si)

/* вычитание 4-х лонгов (64S/64U) по модулю */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubq256, psubq128, __v4di, __v4di)

/* горизонтальное сложение 2-х частей по 8 пар шортов (16S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (phaddw256, phaddw128, __v16hi, __v16hi)

/* горизонтальное сложение 2-х частей по 4 пары интов (32S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (phaddd256, phaddd128, __v8si, __v8si)

/* горизонтальное вычитание 2-х частей по 8 пар шортов (16S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (phsubw256, phsubw128, __v16hi, __v16hi)

/* горизонтальное вычитание 2-х частей по 4 пары интов (32S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (phsubd256, phsubd128, __v8si, __v8si)

/* *****************************************************************************
 *                         Сложение и вычитание c насыщением
 * *****************************************************************************/

/* сложение 32-х знаковых байт (8S) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddsb256, paddsb128, __v32qi, __v32qi)

/* сложение 16-ти знаковых шортов (16S) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddsw256, paddsw128, __v16hi, __v16hi)

/* сложение 32-х беззнаковых байт (8U) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddusb256, paddusb128, __v32qi, __v32qi)

/* сложение 16-ти беззнаковых шортов (16U) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (paddusw256, paddusw128, __v16hi, __v16hi)

/* вычитание 32-х знаковых байт (8S) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubsb256, psubsb128, __v32qi, __v32qi)

/* вычитание 16-ти знаковых шортов (16S) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubsw256, psubsw128, __v16hi, __v16hi)

/* вычитание 32-х беззнаковых байт (8U) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubusb256, psubusb128, __v32qi, __v32qi)

/* вычитание 16-ти беззнаковых шортов (16U) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psubusw256, psubusw128, __v16hi, __v16hi)

/* горизонтальное сложение 2-х частей по 8 пар шортов (16S) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (phaddsw256, phaddsw128, __v16hi, __v16hi)

/* горизонтальное вычитание 2-х частей по 8 пар шортов (16S) c насыщением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (phsubsw256, phsubsw128, __v16hi, __v16hi)

/* *****************************************************************************
 *                            Выравнивание
 * *****************************************************************************/

/* логический сдвиг вправо 2-х частей по 32 байта (старшие и младшие половины сцепленных
 * первых 2 операндов) на число байт, равное константе в 3-м операнде (величина подается
 * в битах), и выдача 2-х частей из младших 16 байт */
#define __builtin_ia32_palignr256(src1, src2, shift) ({                                        \
    type_union_256 __ss1, __ss2, __ddst;                                                       \
    __ss1.__v4di = src1;                                                                       \
    __ss2.__v4di = src2;                                                                       \
    __ddst.u__v4di.v0 = __builtin_ia32_palignr128 (__ss1.u__v4di.v0, __ss2.u__v4di.v0, shift); \
    __ddst.u__v4di.v1 = __builtin_ia32_palignr128 (__ss1.u__v4di.v1, __ss2.u__v4di.v1, shift); \
    __ddst.__v4di;                                                                             \
})

/* *****************************************************************************
 *                           Логические операции
 * *****************************************************************************/

/* AND 4-х лонгов (64S) */
#define __builtin_ia32_andsi256(src1, src2) ({                          \
    type_union_256 __s1, __s2, __dst;                                   \
    __s1.__v4di = src1;                                                 \
    __s2.__v4di = src2;                                                 \
    __dst.__v4df = __builtin_ia32_andpd256 (__s1.__v4df, __s2.__v4df);  \
    __dst.__v4di;                                                       \
})

/* ANDNOT 4-х лонгов (64S) */
#define __builtin_ia32_andnotsi256(src1, src2) ({                       \
    type_union_256 __s1, __s2, __dst;                                   \
    __s1.__v4di = src1;                                                 \
    __s2.__v4di = src2;                                                 \
    __dst.__v4df = __builtin_ia32_andnpd256 (__s1.__v4df, __s2.__v4df); \
    __dst.__v4di;                                                       \
})

/* *****************************************************************************
 *                         Целочисленные операции
 * *****************************************************************************/

/* среднее 32-х беззнаковых байт (8U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pavgb256, pavgb128, __v32qi, __v32qi)

/* среднее 16-ти беззнаковых шортов (16U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pavgw256, pavgw128, __v16hi, __v16hi)

/* cложение абсолютных разностей 32-х беззнаковых байт (8U) в 4 суммы */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psadbw256, psadbw128, __v32qi, __v16hi)

/* Conditionally copy byte elements from the second source operand and the first
 * source operand depending on mask bits defined in the mask register operand. */
THREE_OPERAND_AVX_BUILTINS_VIA_2SSE (pblendvb256, pblendvb128, __v32qi, __v32qi)

/* Shorts from the second source operand are conditionally merged (in dependency
 * from mask bits) with values from the first source operand */
#define __builtin_ia32_pblendw256(src1, src2, mask) ({                                        \
    type_union_256 __s1, __s2, __dst;                                                         \
    __s1.__v16hi = src1;                                                                      \
    __s2.__v16hi = src2;                                                                      \
    __dst.u__v16hi.v0 = __builtin_ia32_pblendw128 (__s1.u__v16hi.v0, __s2.u__v16hi.v0, mask); \
    __dst.u__v16hi.v1 = __builtin_ia32_pblendw128 (__s1.u__v16hi.v1, __s2.u__v16hi.v1, mask); \
    __dst.__v16hi;                                                                            \
})

/* сравнение на "равно" 32-х байт (8S/8U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpeqb256, pcmpeqb128, __v32qi, __v32qi)

/* сравнение на "равно" 16-ти шортов (16S/16U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpeqw256, pcmpeqw128, __v16hi, __v16hi)

/* сравнение на "равно" 8-ми интов (32S/32U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpeqd256, pcmpeqd128, __v8si, __v8si)

/* сравнение на "равно" 4-х лонгов (64S/64U) c выработкой маски */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpeqq256, pcmpeqq, __v4di, __v4di)

/* сравнение на "больше" 32-х знаковых байт (8S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpgtb256, pcmpgtb128, __v32qi, __v32qi)

/* сравнение на "больше" 16-ти знаковых шортов (16S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpgtw256, pcmpgtw128, __v16hi, __v16hi)

/* сравнение на "больше" 8-ми знаковых интов (32S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpgtd256, pcmpgtd128, __v8si, __v8si)

/* сравнение на "больше" 4-х знаковых лонгов (64S) c выработкой маски */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pcmpgtq256, pcmpgtq, __v4di, __v4di)

/* максимум 32-х знаковых байт (8S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaxsb256, pmaxsb128, __v32qi, __v32qi)

/* максимум 16-ти знаковых шортов (16S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaxsw256, pmaxsw128, __v16hi, __v16hi)

/* максимум 8-ми знаковых интов (32S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaxsd256, pmaxsd128, __v8si, __v8si)

/* максимум 32-х беззнаковых байт (8U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaxub256, pmaxub128, __v32qi, __v32qi)

/* максимум 16-ти беззнаковых шортов (16U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaxuw256, pmaxuw128, __v16hi, __v16hi)

/* максимум 8-ми беззнаковых интов (32U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaxud256, pmaxud128, __v8si, __v8si)

/* минимум 32-х знаковых байт (8S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pminsb256, pminsb128, __v32qi, __v32qi)

/* минимум 16-ти знаковых шортов (16S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pminsw256, pminsw128, __v16hi, __v16hi)

/* минимум 8-ми знаковых интов (32S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pminsd256, pminsd128, __v8si, __v8si)

/* минимум 32-х беззнаковых байт (8U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pminub256, pminub128, __v32qi, __v32qi)

/* минимум 16-ти беззнаковых шортов (16U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pminuw256, pminuw128, __v16hi, __v16hi)

/* минимум 8-ми беззнаковых интов (32U) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pminud256, pminud128, __v8si, __v8si)

/* умножение 32-х знаковых байт (8S) на знаки 32-х байт (8S) второго аргумента */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psignb256, psignb128, __v32qi, __v32qi)

/* умножение 16-ти знаковых шортов (16S) на знаки 16-ти шортов (16S) второго аргумента */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psignw256, psignw128, __v16hi, __v16hi)

/* умножение 8-ми знаковых интов (32S) на знаки 8-ми интов (32S) второго аргумента */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (psignd256, psignd128, __v8si, __v8si)

/* сдвиг влево 2-х частей по 16 байт на число байт, равное константе во 2-м операнде */
#define __builtin_ia32_pslldqi256(src1, src2) ({                           \
    type_union_256 __s1, __dst;                                            \
    __s1.__v4di = src1;                                                    \
    __dst.l.l3 = __builtin_e2k_psllqh (__s1.l.l3, __s1.l.l2, (src2) >> 3); \
    __dst.l.l2 = ((src2) >= 64) ? 0 :                                      \
             __builtin_e2k_psllql (__s1.l.l3, __s1.l.l2, (src2) >> 3);     \
    __dst.l.l1 = __builtin_e2k_psllqh (__s1.l.l1, __s1.l.l0, (src2) >> 3); \
    __dst.l.l0 = ((src2) >= 64) ? 0 :                                      \
             __builtin_e2k_psllql (__s1.l.l1, __s1.l.l0, (src2) >> 3);     \
    __dst.__v4di;                                                          \
})

/* сдвиг вправо 2-х частей по 16 байт на число байт, равное константе во 2-м операнде */
#define __builtin_ia32_psrldqi256(src1, src2) ({                           \
    type_union_256 __s1, __dst;                                            \
    __s1.__v4di = src1;                                                    \
    __dst.l.l3 = ((src2) >= 64) ? 0 :                                      \
             __builtin_e2k_psrlqh (__s1.l.l3, __s1.l.l2, (src2) >> 3);     \
    __dst.l.l2 = __builtin_e2k_psrlql (__s1.l.l3, __s1.l.l2, (src2) >> 3); \
    __dst.l.l1 = ((src2) >= 64) ? 0 :                                      \
             __builtin_e2k_psrlqh (__s1.l.l1, __s1.l.l0, (src2) >> 3);     \
    __dst.l.l0 = __builtin_e2k_psrlql (__s1.l.l1, __s1.l.l0, (src2) >> 3); \
    __dst.__v4di;                                                          \
})

/* сдвиг влево 16-ти шортов (16S/16U) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psllwi256, psllwi128, __v16hi, int, __v16hi)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psllw256, psllw128, __v16hi, __v8hi, __v16hi)

/* сдвиг влево 8-ми интов (32S/32U) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (pslldi256, pslldi128, __v8si, int, __v8si)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (pslld256, pslld128, __v8si, __v4si, __v8si)

/* сдвиг влево 4-х лонгов (64S/64U) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psllqi256, psllqi128, __v4di, int, __v4di)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psllq256, psllq128, __v4di, __v2di, __v4di)

/* арифметический сдвиг вправо 16-ти знаковых шортов (16S) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrawi256, psrawi128, __v16hi, int, __v16hi)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psraw256, psraw128, __v16hi, __v8hi, __v16hi)

/* арифметический сдвиг вправо 8-ми знаковых интов (32S) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psradi256, psradi128, __v8si, int, __v8si)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrad256, psrad128, __v8si, __v4si, __v8si)

/* логический сдвиг вправо 16-ти шортов (16S/16U) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrlwi256, psrlwi128, __v16hi, int, __v16hi)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrlw256, psrlw128, __v16hi, __v8hi, __v16hi)

/* логический сдвиг вправо 8-ми интов (32S/32U) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrldi256, psrldi128, __v8si, int, __v8si)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrld256, psrld128, __v8si, __v4si, __v8si)

/* логический сдвиг вправо 4-х лонгов (64S/64U) */
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrlqi256, psrlqi128, __v4di, int, __v4di)
ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE (psrlq256, psrlq128, __v4di, __v2di, __v4di)

/* *****************************************************************************
 *                             Умножение
 * *****************************************************************************/

/* умножение 32-х беззнаковых байт (8U) на 32 знаковых байт (8S) и
 * попарное сложение смежных шортовых произведений с сатурацией */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaddubsw256, pmaddubsw128, __v32qi, __v16hi)

/* умножение 16-ти знаковых шортов (16S) и попарное сложение смежных интовых произведений */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmaddwd256, pmaddwd128, __v16hi, __v8si)

/* умножение 4-х знаковых интов (32S), расположенныхв младших половинах 64-х
 * разрядных значений с получением 4-х 64-х разрядных результатов. */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmuldq256, pmuldq128, __v8si, __v4di)

/* умножение 16-ти знаковых шортов (16S) c масштабированием (>> 15) и округлением */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmulhrsw256, pmulhrsw128, __v16hi, __v16hi)

/* умножение 16-ти беззнаковых шортов (16U) и выдача старших 16 разрядов произведений */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmulhuw256, pmulhuw128, __v16hi, __v16hi)

/* умножение 16-ти знаковых шортов (16S) и выдача старших 16 разрядов произведений */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmulhw256, pmulhw128, __v16hi, __v16hi)

/* умножение 16-ти знаковых шортов (16S) и выдача младших 16 разрядов произведений */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmullw256, pmullw128, __v16hi, __v16hi)

/* умножение 8-ми знаковых интов (32s) и выдача младших 32 разрядов произведения */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmulld256, pmulld128, __v8si, __v8si)

/* умножение 4-х интов (32S) с получением 4-х лонгов (64S) */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pmuludq256, pmuludq128, __v8si, __v4di)

/* *****************************************************************************
 *                               Выделение маски
 * *****************************************************************************/

/* формирование 32-х разрядной маски из знаков каждого байта (8S) */
__E2K_INLINE int __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovmskb256 (__v32qi src)
{
    type_union_256 s;
    s.__v32qi = src;
#if __iset__ <= 4
    return (__builtin_e2k_pmovmskb (s.l.l3, s.l.l2) << 16) |
            __builtin_e2k_pmovmskb (s.l.l1, s.l.l0);
#else /* __iset__ <= 4 */
    return (__builtin_e2k_qpsgn2mskb (s.u__v4di.v1) << 16) |
            __builtin_e2k_qpsgn2mskb (s.u__v4di.v0);
#endif /* __iset__ <= 4 */
}

/* *****************************************************************************
 *                            Распаковки
 * *****************************************************************************/

/* Распаковка 16-ти байт (8S) в шорты (16S) заполнением знаком. */
__E2K_INLINE __v16hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxbw256 (__v16qi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v16qi = src;
#if __iset__ <= 3
    __di tmp0 = __builtin_e2k_pcmpgtb (0, s.l.l0);
    __di tmp1 = __builtin_e2k_pcmpgtb (0, s.l.l1);
    dst.l.l3 = __builtin_e2k_punpckhbh (tmp1, s.l.l1);
    dst.l.l2 = __builtin_e2k_punpcklbh (tmp1, s.l.l1);
    dst.l.l1 = __builtin_e2k_punpckhbh (tmp0, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklbh (tmp0, s.l.l0);
#elif __iset__ <= 4
    dst.l.l3 = __builtin_e2k_pshufb (s.l.l1, s.l.l1, 0x4707460645054404LL);
    dst.l.l2 = __builtin_e2k_pshufb (s.l.l1, s.l.l1, 0x4303420241014000LL);
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4707460645054404LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4303420241014000LL);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8f0f8e0e8d0d8c0cLL, 0x8b0b8a0a89098808LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8707860685058404LL, 0x8303820281018000LL));
#endif /* __iset__ <= 4 */
    return dst.__v16hi;
}

/* Распаковка 8-ми младших байт (8S) в инты (32S) заполнением знаком. */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxbd256 (__v16qi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v16qi = src;
#if __iset__ <= 3
    __di tmp0 = __builtin_e2k_pcmpgtb (0, s.l.l0);
    dst.l.l3 = __builtin_e2k_pshufb (tmp0, s.l.l0, 0x0f0f0f070e0e0e06LL);
    dst.l.l2 = __builtin_e2k_pshufb (tmp0, s.l.l0, 0x0d0d0d050c0c0c04LL);
    dst.l.l1 = __builtin_e2k_pshufb (tmp0, s.l.l0, 0x0b0b0b030a0a0a02LL);
    dst.l.l0 = __builtin_e2k_pshufb (tmp0, s.l.l0, 0x0909090108080800LL);
#elif __iset__ <= 4
    dst.l.l3 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4747470746464606LL);
    dst.l.l2 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4545450544444404LL);
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343430342424202LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4141410140404000LL);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8787870786868606LL, 0x8585850584848404LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8383830382828202LL, 0x8181810180808000LL));
#endif /* __iset__ <= 4 */
    return dst.__v8si;
}

/* Распаковка 4-х младших байт (8S) в лонги (64S) заполнением знаком. */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxbq256 (__v16qi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v16qi = src;
#if __iset__ <= 3
    dst.l.l3 = ((long long) (s.l.l0 << 32)) >> 56;
    dst.l.l2 = ((long long) (s.l.l0 << 40)) >> 56;
    dst.l.l1 = ((long long) (s.l.l0 << 48)) >> 56;
    dst.l.l0 = ((long long) (s.l.l0 << 56)) >> 56;
#elif __iset__ <= 4
    dst.l.l3 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343434343434303LL);
    dst.l.l2 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4242424242424202LL);
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4141414141414101LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4040404040404000LL);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8383838383838303LL, 0x8282828282828202LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8181818181818101LL, 0x8080808080808000LL));
#endif /* __iset__ <= 4 */
    return dst.__v4di;
}

/* Распаковка 8-ми шортов (16S) в инты (32S) заполнением знаком. */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxwd256 (__v8hi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v8hi = src;
#if __iset__ <= 3
    __di tmp0 = __builtin_e2k_pcmpgth (0, s.l.l0);
    __di tmp1 = __builtin_e2k_pcmpgth (0, s.l.l1);
    dst.l.l3 = __builtin_e2k_punpckhhw (tmp1, s.l.l1);
    dst.l.l2 = __builtin_e2k_punpcklhw (tmp1, s.l.l1);
    dst.l.l1 = __builtin_e2k_punpckhhw (tmp0, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklhw (tmp0, s.l.l0);
#elif __iset__ <= 4
    dst.l.l3 = __builtin_e2k_pshufb (s.l.l1, s.l.l1, 0x4747070645450504LL);
    dst.l.l2 = __builtin_e2k_pshufb (s.l.l1, s.l.l1, 0x4343030241410100LL);
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4747070645450504LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343030241410100LL);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8f8f0f0e8d8d0d0cLL, 0x8b8b0b0a89890908LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8787070685850504LL, 0x8383030281810100LL));
#endif /* __iset__ <= 4 */
    return dst.__v8si;
}

/* Распаковка 4-х младших шортов (16S) в лонги (64S) заполнением знаком. */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxwq256 (__v8hi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v8hi = src;
#if __iset__ <= 3
    dst.l.l3 = ((long long) (s.l.l0      )) >> 48;
    dst.l.l2 = ((long long) (s.l.l0 << 16)) >> 48;
    dst.l.l1 = ((long long) (s.l.l0 << 32)) >> 48;
    dst.l.l0 = ((long long) (s.l.l0 << 48)) >> 48;
#elif __iset__ <= 4
    dst.l.l3 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4747474747470706LL);
    dst.l.l2 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4545454545450504LL);
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343434343430302LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4141414141410100LL);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8787878787870706LL, 0x8585858585850504LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8383838383830302LL, 0x8181818181810100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4di;
}

/* Распаковка 4-х интов (32S) в лонги (64S) заполнением знаком. */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovsxdq256 (__v4si src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l3 = ((long long) s.l.l1) >> 32;
    dst.l.l1 = ((long long) s.l.l0) >> 32;
 #if __iset__ <= 3
    dst.l.l2 = ((long long) (s.l.l1 << 32)) >> 32;
    dst.l.l0 = ((long long) (s.l.l0 << 32)) >> 32;
 #else /* __iset__ <= 3 */
    dst.l.l2 = __builtin_e2k_pshufb (s.l.l1, s.l.l1, 0x4343434303020100LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x4343434303020100LL);
 #endif /* __iset__ <= 3 */
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8f8f8f8f0f0e0d0cLL, 0x8b8b8b8b0b0a0908LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (s.__v2di, s.__v2di,
                                            __builtin_e2k_qppackdl (0x8787878707060504LL, 0x8383838303020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4di;
}

/* Распаковка 16-ти байт (8U) в беззнаковые шорты (16U) заполнением нулями. */
__E2K_INLINE __v16hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxbw256 (__v16qi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l3 = __builtin_e2k_punpckhbh (0, s.l.l1);
    dst.l.l2 = __builtin_e2k_punpcklbh (0, s.l.l1);
    dst.l.l1 = __builtin_e2k_punpckhbh (0, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklbh (0, s.l.l0);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x100f100e100d100cLL, 0x100b100a10091008LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1007100610051004LL, 0x1003100210011000LL));
#endif /* __iset__ <= 4 */
    return dst.__v16hi;
}

/* Распаковка 8-ми младших байт (8U) в беззнаковые инты (32U) заполнением нулями. */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxbd256 (__v16qi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l3 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x8080800780808006LL);
    dst.l.l2 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x8080800580808004LL);
    dst.l.l1 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x8080800380808002LL);
    dst.l.l0 = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0x8080800180808000LL);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010100710101006LL, 0x1010100510101004LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010100310101002LL, 0x1010100110101000LL));
#endif /* __iset__ <= 4 */
    return dst.__v8si;
}

/* Распаковка 4-х младших байт (8U) в беззнаковые лонги (64U) заполнением нулями. */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxbq256 (__v16qi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v16qi = src;
#if __iset__ <= 4
    dst.l.l3 = (s.l.l0 >> 24) & 0xff;
    dst.l.l2 = (s.l.l0 >> 16) & 0xff;
    dst.l.l1 = (s.l.l0 >>  8) & 0xff;
    dst.l.l0 = (s.l.l0      ) & 0xff;
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010101010101003LL, 0x1010101010101002LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010101010101001LL, 0x1010101010101000LL));
#endif /* __iset__ <= 4 */
    return dst.__v4di;
}

/* Распаковка 8-ми шортов (16U) в беззнаковые инты (32U) заполнением нулями. */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxwd256 (__v8hi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l3 = __builtin_e2k_punpckhhw (0, s.l.l1);
    dst.l.l2 = __builtin_e2k_punpcklhw (0, s.l.l1);
    dst.l.l1 = __builtin_e2k_punpckhhw (0, s.l.l0);
    dst.l.l0 = __builtin_e2k_punpcklhw (0, s.l.l0);
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x10100f0e10100d0cLL, 0x10100b0a10100908LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010070610100504LL, 0x1010030210100100LL));
#endif /* __iset__ <= 4 */
    return dst.__v8si;
}

/* Распаковка 4-х младших шортов (16U) в беззнаковые лонги (64U) заполнением нулями. */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxwq256 (__v8hi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v8hi = src;
#if __iset__ <= 4
    dst.l.l3 = (s.l.l0 >> 48);
    dst.l.l2 = (s.l.l0 >> 32) & 0xffff;
    dst.l.l1 = (s.l.l0 >> 16) & 0xffff;
    dst.l.l0 = (s.l.l0      ) & 0xffff;
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010101010100706LL, 0x1010101010100504LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010101010100302LL, 0x1010101010100100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4di;
}

/* Распаковка 4-х интов (32U) в беззнаковые лонги (64U) заполнением нулями. */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pmovzxdq256 (__v4si src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v4si = src;
#if __iset__ <= 4
    dst.l.l3 = s.l.l1 >> 32;
    dst.l.l2 = s.l.l1 & 0xffffffff;
    dst.l.l1 = s.l.l0 >> 32;
    dst.l.l0 = s.l.l0 & 0xffffffff;
#else /* __iset__ <= 4 */
    dst.u__v4di.v1 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x101010100f0e0d0cLL, 0x101010100b0a0908LL));
    dst.u__v4di.v0 = __builtin_e2k_qppermb (__builtin_e2k_qppackdl (0, 0), s.__v2di,
                                            __builtin_e2k_qppackdl (0x1010101007060504LL, 0x1010101003020100LL));
#endif /* __iset__ <= 4 */
    return dst.__v4di;
}

/* *****************************************************************************
 *                             Перестановки
 * *****************************************************************************/

/* перестановка 2-х частей по 16 входных байт, положение которых определяется значениями
 * в соответствующих байтах 2-го операнда. Либо заполнение 0 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (pshufb256, pshufb128, __v32qi, __v32qi)

/* перестановка 2-х частей по 4 входных инта (32S) в соответствии с размещением,
 * указанным в 8-ми младших разрядах константы 2-го операнда */
#define __builtin_ia32_pshufd256(src1, src2) ({                                   \
    type_union_256 __s1, __dst;                                                   \
    __s1.__v8si = src1;                                                           \
    __dst.l.l0 = __builtin_e2k_pshufw (__s1.l.l1, __s1.l.l0, (src2) & 15);        \
    __dst.l.l1 = __builtin_e2k_pshufw (__s1.l.l1, __s1.l.l0, ((src2) >> 4) & 15); \
    __dst.l.l2 = __builtin_e2k_pshufw (__s1.l.l3, __s1.l.l2, (src2) & 15);        \
    __dst.l.l3 = __builtin_e2k_pshufw (__s1.l.l3, __s1.l.l2, ((src2) >> 4) & 15); \
    __dst.__v8si;                                                                 \
})

/* перестановка 2-х частей по 4 старших шорта в соответствии с порядком,
 * определенным в 8-ми младших разрядах константы 2-го операнда */
#define __builtin_ia32_pshufhw256(src1, src2) ({                  \
    type_union_256 __s1;                                          \
    __s1.__v16hi = src1;                                          \
    __s1.l.l1 = __builtin_e2k_pshufh (__s1.l.l1, (src2) & 0xff);  \
    __s1.l.l3 = __builtin_e2k_pshufh (__s1.l.l3, (src2) & 0xff);  \
    __s1.__v16hi;                                                 \
})

/* перестановка 2-х частей по 4 младших шорта в соответствии с порядком,
 * определенным в 8-ми младших разрядах константы 2-го операнда */
#define __builtin_ia32_pshuflw256(src1, src2) ({                  \
    type_union_256 __s1;                                          \
    __s1.__v16hi = src1;                                          \
    __s1.l.l0 = __builtin_e2k_pshufh (__s1.l.l0, (src2) & 0xff);  \
    __s1.l.l2 = __builtin_e2k_pshufh (__s1.l.l2, (src2) & 0xff);  \
    __s1.__v16hi;                                                 \
})

/* *****************************************************************************
 *                                Распаковка
 * *****************************************************************************/

/* чередование 16-ти старших байт (8U) операнда 1 и 16-ти старших байт (8U) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpckhbw256, punpckhbw128, __v32qi, __v32qi)

/* чередование 8-ми старших шортов (16U) операнда 1 и 8-ми старших шортов (16U) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpckhwd256, punpckhwd128, __v16hi, __v16hi)

/* чередование 4-х старших интов (32U) операнда 1 и 4-х старших интов (32U) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpckhdq256, punpckhdq128, __v8si, __v8si)

/* чередование 2-х старших лонгов (64S) операнда 1 и 2-х старших лонгов (64S) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpckhqdq256, punpckhqdq128, __v4di, __v4di)

/* чередование 16-ти младших байт (8U) операнда 1 и 16-ти младших байт (8U) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpcklbw256, punpcklbw128, __v32qi, __v32qi)

/* чередование 8-ми младших шортов (16U) операнда 1 и 8-ми младших шортов (16U) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpcklwd256, punpcklwd128, __v16hi, __v16hi)

/* чередование 4-х младших интов (32U) операнда 1 и 4-х младших интов (32U) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpckldq256, punpckldq128, __v8si, __v8si)

/* чередование 2-х младших лонгов (64S) операнда 1 и 2-х младших лонгов (64S) операнда 2 */
TWO_OPERAND_AVX_BUILTINS_VIA_2SSE (punpcklqdq256, punpcklqdq128, __v4di, __v4di)

/* *****************************************************************************
 *                            Чтения
 * *****************************************************************************/

/* Load 4 quadwords using non-temporal aligned hint */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_movntdqa256 (const __v4di *p)
{
    type_union_256 dst;
#if __iset__ <= 4
    dst.l.l0 = __builtin_e2k_ld_64s_nta (p);
    dst.l.l1 = __builtin_e2k_ld_64s_nta ((double *) p + 1);
    dst.l.l2 = __builtin_e2k_ld_64s_nta ((double *) p + 2);
    dst.l.l3 = __builtin_e2k_ld_64s_nta ((double *) p + 3);
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = __builtin_e2k_ld_128_nta (p);
    dst.u__v4di.v1 = __builtin_e2k_ld_128_nta ((__v2di *) p + 1);
#endif /* __iset__ <= 4 */
    return dst.__v4di;
}

/* *****************************************************************************
 *                             Перестановки
 * *****************************************************************************/

/* размножение младшего флота (32F) в четыре */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastss_ps (__v4sf src)
{
    return __builtin_ia32_vbroadcastss ((float const *) & src);
}

/* размножение младшего флота (32F) в восемь */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastss_ps256 (__v4sf src)
{
    return __builtin_ia32_vbroadcastss256 ((float const *) & src);
}

/* размножение младшего дабла (64F) в четыре */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastsd_pd256 (__v2df src)
{
    return __builtin_ia32_vbroadcastsd256 ((double const *) & src);
}

/* размножение младшего 128-битного значения в два */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_vbroadcastsi256 (__v2di src)
{
    type_union_256 dst;
    dst.__v4df = __builtin_ia32_vbroadcastf128_pd256 ((__v2df const *) & src);
    return dst.__v4di;
}

/* размножение младшего байта (8U/8S) в тридцать два */
__E2K_INLINE __v32qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastb256 (__v16qi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v16qi = src;
    __di tmp = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0);
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = dst.l.l2 = dst.l.l3 = tmp;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = dst.u__v4di.v1 = __builtin_e2k_qppackdl (tmp, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v32qi;
}

/* размножение младшего шорта (16U/16S) в шестнадцать */
__E2K_INLINE __v16hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastw256 (__v8hi src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v8hi = src;
    __di tmp = __builtin_e2k_pshufh (s.l.l0, 0);
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = dst.l.l2 = dst.l.l3 = tmp;
#else /* __iset__ <= 4 */
    dst.u__v4di.v0 = dst.u__v4di.v1 = __builtin_e2k_qppackdl (tmp, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v16hi;
}

/* размножение младшего инта (32U/32S) в восемь */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastd256 (__v4si src)
{
    type_union_128 s;
    type_union_256 dst;
    s.__v4si = src;
    dst.__v8sf = __builtin_ia32_vbroadcastss_ps256 (s.__v4sf);
    return dst.__v8si;
}

/* размножение младшего лонга (64U/64S) в четыре */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastq256 (__v2di src)
{
    type_union_256 dst;
    dst.__v4df = __builtin_ia32_vbroadcastsd256 ((double const *) & src);
    return dst.__v4di;
}

/* размножение младшего байта (8U/8S) в шестнадцать */
__E2K_INLINE __v16qi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastb128 (__v16qi src)
{
    type_union_128 s, dst;
    s.__v16qi = src;
    __di tmp = __builtin_e2k_pshufb (s.l.l0, s.l.l0, 0);
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = tmp;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppackdl (tmp, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v16qi;
}

/* размножение младшего шорта (16U/16S) в восемь */
__E2K_INLINE __v8hi __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastw128 (__v8hi src)
{
    type_union_128 s, dst;
    s.__v8hi = src;
    __di tmp = __builtin_e2k_pshufh (s.l.l0, 0);
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = tmp;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppackdl (tmp, tmp);
#endif /* __iset__ <= 4 */
    return dst.__v8hi;
}

/* размножение младшего инта (32U/32S) в четыре */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastd128 (__v4si src)
{
    type_union_128 s, dst;
    s.__v4si = src;
    dst.__v4sf = __builtin_ia32_vbroadcastss_ps (s.__v4sf);
    return dst.__v4si;
}

/* размножение младшего лонга (64U/64S) в два */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pbroadcastq128 (__v2di src)
{
    type_union_128 s, dst;
    s.__v2di = src;
#if __iset__ <= 4
    dst.l.l0 = dst.l.l1 = s.l.l0;
#else /* __iset__ <= 4 */
    dst.__v2di = __builtin_e2k_qppackdl (s.l.l0, s.l.l0);
#endif /* __iset__ <= 4 */
    return dst.__v2di;
}

/* смешивание (выбор) 4-х интов (32S) по битовой маске */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pblendd128 (__v4si src1, __v4si src2, const int mask)
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    dst.__v4sf = __builtin_ia32_blendps (s1.__v4sf, s2.__v4sf, mask);
    return dst.__v4si;
}

/* смешивание (выбор) 8-ми интов (32S) по битовой маске */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_pblendd256 (__v8si src1, __v8si src2, const int mask)
{
    type_union_256 s1, s2, dst;
    s1.__v8si = src1;
    s2.__v8si = src2;
    dst.__v8sf = __builtin_ia32_blendps256 (s1.__v8sf, s2.__v8sf, mask);
    return dst.__v8si;
}

/* смешивание (выбор) 8-ми интов (32S) по индексам, лежащим в младших
 * 3-х битах каждого инта 2-го аргумента */
__E2K_INLINE __E2K_WARNING (__v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_permvarsi256 (__v8si src, __v8si indx))
{
    type_union_256 i, dst;
    i.__v8si = indx;
    dst.i.i0 = ((int *) & src)[i.i.i0 & 7];
    dst.i.i1 = ((int *) & src)[i.i.i1 & 7];
    dst.i.i2 = ((int *) & src)[i.i.i2 & 7];
    dst.i.i3 = ((int *) & src)[i.i.i3 & 7];
    dst.i.i4 = ((int *) & src)[i.i.i4 & 7];
    dst.i.i5 = ((int *) & src)[i.i.i5 & 7];
    dst.i.i6 = ((int *) & src)[i.i.i6 & 7];
    dst.i.i7 = ((int *) & src)[i.i.i7 & 7];
    return dst.__v8si;
}

/* смешивание (выбор) 4-х даблов (64F) по индексам, лежащим в младших
 * 8-ми битах 2-го аргумента (по 2 бита на каждый дабл) */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_permdf256 (__v4df src, const int indx)
{
    type_union_256 s, dst;
    s.__v4df = src;
    dst.l.l0 = (indx & 2) ? ((indx & 1) ? s.l.l3 : s.l.l2) : ((indx & 1) ? s.l.l1 : s.l.l0);
    dst.l.l1 = (indx & 8) ? ((indx & 4) ? s.l.l3 : s.l.l2) : ((indx & 4) ? s.l.l1 : s.l.l0);
    dst.l.l2 = (indx & 32) ? ((indx & 16) ? s.l.l3 : s.l.l2) : ((indx & 16) ? s.l.l1 : s.l.l0);
    dst.l.l3 = (indx & 128) ? ((indx & 64) ? s.l.l3 : s.l.l2) : ((indx & 64) ? s.l.l1 : s.l.l0);
    return dst.__v4df;
}

/* смешивание (выбор) 8-ми флотов (32F) по индексам, лежащим в младших
 * 3-х битах каждого инта 2-го аргумента */
__E2K_INLINE __E2K_WARNING (__v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_permvarsf256 (__v8sf src, __v8si indx))
{
    type_union_256 s, dst;
    s.__v8sf = src;
    dst.__v8si = __builtin_ia32_permvarsi256 (s.__v8si, indx);
    return dst.__v8sf;
}

/* смешивание (выбор) 4-х лонгов (64S) по индексам, лежащим в младших
 * 8-ми битах 2-го аргумента (по 2 бита на каждый лонг) */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_permdi256 (__v4di src, const int indx)
{
    type_union_256 s, dst;
    s.__v4di = src;
    dst.__v4df = __builtin_ia32_permdf256 (s.__v4df, indx);
    return dst.__v4di;
}

/* перестановка 128-ми бит из первых 2-х операндов в зависимости от 8-ми младших бит
 * третьего операнда */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_permti256 (__v4di src1, __v4di src2, const int indx)
{
    type_union_256 s1, s2, dst;
    s1.__v4di = src1;
    s2.__v4di = src2;
    dst.__v4df = __builtin_ia32_vperm2f128_pd256 (s1.__v4df, s2.__v4df, indx);
    return dst.__v4di;
}

/* *****************************************************************************
 *                            Вставка/выделение
 * *****************************************************************************/

/* выделение старшей или младшей половины из 4-х лонгов (64S) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_extract128i256 (__v4di src, const int indx)
{
    type_union_256 s;
    type_union_128 dst;
    s.__v4di = src;
    dst.__v2df = __builtin_ia32_vextractf128_pd256 (s.__v4df, indx);
    return dst.__v2di;
}

/* Вставка 2-х лонгов (64S) в старшую или младшую половины src1 в зависимости
 * от младшего бита индекса */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_insert128i256 (__v4di src1, __v2di src2, const int indx)
{
    type_union_256 s1, dst;
    type_union_128 s2;
    s1.__v4di = src1;
    s2.__v2di = src2;
    dst.__v4df = __builtin_ia32_vinsertf128_pd256 (s1.__v4df, s2.__v2df, indx);
    return dst.__v4di;
}

/* *****************************************************************************
 *                        Чтения / Записи по маске
 * *****************************************************************************/

/* чтение 8-ми интов (32S) по маске */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadd256 (const __v8si *p, __v8si mask)
{
    type_union_256 dst;
    dst.__v8sf = __builtin_ia32_maskloadps256 ((const __v8sf *) p, mask);
    return dst.__v8si;
}

/* чтение 4-х лонгов (64S) по маске */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadq256 (const __v4di *p, __v4di mask)
{
    type_union_256 dst;
    dst.__v4df = __builtin_ia32_maskloadpd256 ((const __v4df *) p, mask);
    return dst.__v4di;
}

/* чтение 4-х интов (32S) по маске */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadd (const __v4si *p, __v4si mask)
{
    type_union_128 dst;
    dst.__v4sf = __builtin_ia32_maskloadps ((const __v4sf *) p, mask);
    return dst.__v4si;
}

/* чтение 2-х лонгов (64S) по маске */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskloadq (const __v2di *p, __v2di mask)
{
    type_union_128 dst;
    dst.__v2df = __builtin_ia32_maskloadpd ((const __v2df *) p, mask);
    return dst.__v2di;
}

/* запись 8-ми интов (32S) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstored256 (__v8si *p, __v8si mask, __v8si src)
{
    type_union_256 s;
    s.__v8si = src;
    __builtin_ia32_maskstoreps256 ((__v8sf *) p, mask, s.__v8sf);
}

/* запись 4-х лонгов (64S) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstoreq256 (__v4di *p, __v4di mask, __v4di src)
{
    type_union_256 s;
    s.__v4di = src;
    __builtin_ia32_maskstorepd256 ((__v4df *) p, mask, s.__v4df);
}

/* запись 4-х интов (32S) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstored (__v4si *p, __v4si mask, __v4si src)
{
    type_union_128 s;
    s.__v4si = src;
    __builtin_ia32_maskstoreps ((__v4sf *) p, mask, s.__v4sf);
}

/* запись 2-х лонгов (64S) по маске */
__E2K_INLINE void __DEFAULT_FUNCS_ATTRS
__builtin_ia32_maskstoreq (__v2di *p, __v2di mask, __v2di src)
{
    type_union_128 s;
    s.__v2di = src;
    __builtin_ia32_maskstorepd ((__v2df *) p, mask, s.__v2df);
}

/* *****************************************************************************
 *                             Cдвиги векторные
 * *****************************************************************************/

#define __SHLL_32U(src, shift, dst) {                                                    \
    __di eve = __builtin_e2k_psllw (src, shift & 0xffffffff);                            \
    __di odd = __builtin_e2k_psllw (src, shift >> 32);                                   \
    dst = __builtin_e2k_pshufw (eve, odd, 6); /* 12 */                                   \
}

#define __SHRA_32U(src, shift, dst) {                                                    \
    __di eve = __builtin_e2k_psraw (src, shift & 0xffffffff);                            \
    __di odd = __builtin_e2k_psraw (src, shift >> 32);                                   \
    dst = __builtin_e2k_pshufw (eve, odd, 6); /* 12 */                                   \
}

#define __SHRL_32U(src, shift, dst) {                                                    \
    __di eve = __builtin_e2k_psrlw (src, shift & 0xffffffff);                            \
    __di odd = __builtin_e2k_psrlw (src, shift >> 32);                                   \
    dst = __builtin_e2k_pshufw (eve, odd, 6); /* 12 */                                   \
}

/* сдвиг влево каждого из 8-ми интов (32U) на свою величину. Величина сдвига в
 * соответствующем инте в src2 (при сдвиге больше 31 результат равен 0) */
__E2K_INLINE __E2K_WARNING (__v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psllv8si (__v8si src1, __v8si src2))
{
    type_union_256 s1, s2, dst;
    s1.__v8si = src1;
    s2.__v8si = src2;
    __SHLL_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHLL_32U (s1.l.l1, s2.l.l1, dst.l.l1);
    __SHLL_32U (s1.l.l2, s2.l.l2, dst.l.l2);
    __SHLL_32U (s1.l.l3, s2.l.l3, dst.l.l3);
    return dst.__v8si;
}

/* сдвиг влево каждого из 4-х интов (32U) на свою величину. Величина сдвига в
 * соответствующем инте в src2 (при сдвиге больше 31 результат равен 0) */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psllv4si (__v4si src1, __v4si src2))
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    __SHLL_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHLL_32U (s1.l.l1, s2.l.l1, dst.l.l1);
    return dst.__v4si;
}

/* сдвиг влево каждого из 4-х лонгов (64U) на свою величину. Величина сдвига в
 * соответствующем лонгe в src2 (при сдвиге больше 63 результат равен 0) */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psllv4di (__v4di src1, __v4di src2)
{
    type_union_256 s1, s2, dst;
    s1.__v4di = src1;
    s2.__v4di = src2;
    dst.l.l0 = __builtin_e2k_pslld (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pslld (s1.l.l1, s2.l.l1);
    dst.l.l2 = __builtin_e2k_pslld (s1.l.l2, s2.l.l2);
    dst.l.l3 = __builtin_e2k_pslld (s1.l.l3, s2.l.l3);
    return dst.__v4di;
}

/* сдвиг влево каждого из 2-х лонгов (64U) на свою величину. Величина сдвига в
 * соответствующем лонгe в src2 (при сдвиге больше 63 результат равен 0) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psllv2di (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    dst.l.l0 = __builtin_e2k_pslld (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_pslld (s1.l.l1, s2.l.l1);
    return dst.__v2di;
}

/* арифметический сдвиг вправо каждого из 8-ми знаковых интов (32S) на свою величину.
 * Величина сдвига в соответствующем инте в src2 (при сдвиге больше 31
 * результат равен знаку */
__E2K_INLINE __E2K_WARNING (__v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psrav8si (__v8si src1, __v8si src2))
{
    type_union_256 s1, s2, dst;
    s1.__v8si = src1;
    s2.__v8si = src2;
    __SHRA_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHRA_32U (s1.l.l1, s2.l.l1, dst.l.l1);
    __SHRA_32U (s1.l.l2, s2.l.l2, dst.l.l2);
    __SHRA_32U (s1.l.l3, s2.l.l3, dst.l.l3);
    return dst.__v8si;
}

/* арифметический сдвиг вправо каждого из 4-х знаковых интов (32S) на свою величину.
 * Величина сдвига в соответствующем инте в src2 (при сдвиге больше 31
 * результат равен знаку */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psrav4si (__v4si src1, __v4si src2))
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    __SHRA_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHRA_32U (s1.l.l1, s2.l.l1, dst.l.l1);
    return dst.__v4si;
}

/* логический сдвиг вправо каждого из 8-ми знаковых интов (32S) на свою величину.
 * Величина сдвига в соответствующем инте в src2 (при сдвиге больше 31
 * результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psrlv8si (__v8si src1, __v8si src2))
{
    type_union_256 s1, s2, dst;
    s1.__v8si = src1;
    s2.__v8si = src2;
    __SHRL_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHRL_32U (s1.l.l1, s2.l.l1, dst.l.l1);
    __SHRL_32U (s1.l.l2, s2.l.l2, dst.l.l2);
    __SHRL_32U (s1.l.l3, s2.l.l3, dst.l.l3);
    return dst.__v8si;
}

/* логический сдвиг вправо каждого из 4-х знаковых интов (32S) на свою величину.
 * Величина сдвига в соответствующем инте в src2 (при сдвиге больше 31
 * результат равен 0 */
__E2K_INLINE __E2K_WARNING (__v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psrlv4si (__v4si src1, __v4si src2))
{
    type_union_128 s1, s2, dst;
    s1.__v4si = src1;
    s2.__v4si = src2;
    __SHRL_32U (s1.l.l0, s2.l.l0, dst.l.l0);
    __SHRL_32U (s1.l.l1, s2.l.l1, dst.l.l1);
    return dst.__v4si;
}

/* логический сдвиг вправо каждого из 4-х лонгов (64U) на свою величину. Величина сдвига в
 * соответствующем лонгe в src2 (при сдвиге больше 63 результат равен 0) */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psrlv4di (__v4di src1, __v4di src2)
{
    type_union_256 s1, s2, dst;
    s1.__v4di = src1;
    s2.__v4di = src2;
    dst.l.l0 = __builtin_e2k_psrld (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_psrld (s1.l.l1, s2.l.l1);
    dst.l.l2 = __builtin_e2k_psrld (s1.l.l2, s2.l.l2);
    dst.l.l3 = __builtin_e2k_psrld (s1.l.l3, s2.l.l3);
    return dst.__v4di;
}

/* логический сдвиг вправо каждого из 2-х лонгов (64U) на свою величину. Величина сдвига в
 * соответствующем лонгe в src2 (при сдвиге больше 63 результат равен 0) */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_psrlv2di (__v2di src1, __v2di src2)
{
    type_union_128 s1, s2, dst;
    s1.__v2di = src1;
    s2.__v2di = src2;
    dst.l.l0 = __builtin_e2k_psrld (s1.l.l0, s2.l.l0);
    dst.l.l1 = __builtin_e2k_psrld (s1.l.l1, s2.l.l1);
    return dst.__v2di;
}

/* *****************************************************************************
 *                        Условные чтения со сборкой
 * *****************************************************************************/

/* условное чтение 2-х даблов (64F) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv2df (__v2df src, double const *p, __v4si indx, __v2df mask, const int scale)
{
    type_union_128 ind, m, dst;
    ind.__v4si = indx;
    m.__v2df = mask;
    dst.__v2df = src;
    if ((long long) m.l.l0 < 0) dst.d.d0 = *(double const *)((char *) p + ind.i.i0 * scale);
    if ((long long) m.l.l1 < 0) dst.d.d1 = *(double const *)((char *) p + ind.i.i1 * scale);
    return dst.__v2df;
}

/* условное чтение 4-х даблов (64F) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv4df (__v4df src, double const *p, __v4si indx, __v4df mask, const int scale)
{
    type_union_128 ind;
    type_union_256 m, dst;
    ind.__v4si = indx;
    m.__v4df = mask;
    dst.__v4df = src;
    if ((long long) m.l.l0 < 0) dst.d.d0 = *(double const *)((char *) p + ind.i.i0 * scale);
    if ((long long) m.l.l1 < 0) dst.d.d1 = *(double const *)((char *) p + ind.i.i1 * scale);
    if ((long long) m.l.l2 < 0) dst.d.d2 = *(double const *)((char *) p + ind.i.i2 * scale);
    if ((long long) m.l.l3 < 0) dst.d.d3 = *(double const *)((char *) p + ind.i.i3 * scale);
    return dst.__v4df;
}

/* условное чтение 2-х даблов (64F) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v2df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv2df (__v2df src, double const *p, __v2di indx, __v2df mask, const int scale)
{
    type_union_128 ind, m, dst;
    ind.__v2di = indx;
    m.__v2df = mask;
    dst.__v2df = src;
    if ((long long) m.l.l0 < 0) dst.d.d0 = *(double const *)((char *) p + ind.l.l0 * scale);
    if ((long long) m.l.l1 < 0) dst.d.d1 = *(double const *)((char *) p + ind.l.l1 * scale);
    return dst.__v2df;
}

/* условное чтение 4-х даблов (64F) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v4df __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv4df (__v4df src, double const *p, __v4di indx, __v4df mask, const int scale)
{
    type_union_256 ind, m, dst;
    ind.__v4di = indx;
    m.__v4df = mask;
    dst.__v4df = src;
    if ((long long) m.l.l0 < 0) dst.d.d0 = *(double const *)((char *) p + ind.l.l0 * scale);
    if ((long long) m.l.l1 < 0) dst.d.d1 = *(double const *)((char *) p + ind.l.l1 * scale);
    if ((long long) m.l.l2 < 0) dst.d.d2 = *(double const *)((char *) p + ind.l.l2 * scale);
    if ((long long) m.l.l3 < 0) dst.d.d3 = *(double const *)((char *) p + ind.l.l3 * scale);
    return dst.__v4df;
}

/* условное чтение 4-х флотов (32F) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv4sf (__v4sf src, float const *p, __v4si indx, __v4sf mask, const int scale)
{
    type_union_128 ind, m, dst;
    ind.__v4si = indx;
    m.__v4sf = mask;
    dst.__v4sf = src;
    if (m.i.i0 < 0) dst.f.f0 = *(float const *)((char *) p + ind.i.i0 * scale);
    if (m.i.i1 < 0) dst.f.f1 = *(float const *)((char *) p + ind.i.i1 * scale);
    if (m.i.i2 < 0) dst.f.f2 = *(float const *)((char *) p + ind.i.i2 * scale);
    if (m.i.i3 < 0) dst.f.f3 = *(float const *)((char *) p + ind.i.i3 * scale);
    return dst.__v4sf;
}

/* условное чтение 8-ми флотов (32F) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v8sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv8sf (__v8sf src, float const *p, __v8si indx, __v8sf mask, const int scale)
{
    type_union_256 ind, m, dst;
    ind.__v8si = indx;
    m.__v8sf = mask;
    dst.__v8sf = src;
    if (m.i.i0 < 0) dst.f.f0 = *(float const *)((char *) p + ind.i.i0 * scale);
    if (m.i.i1 < 0) dst.f.f1 = *(float const *)((char *) p + ind.i.i1 * scale);
    if (m.i.i2 < 0) dst.f.f2 = *(float const *)((char *) p + ind.i.i2 * scale);
    if (m.i.i3 < 0) dst.f.f3 = *(float const *)((char *) p + ind.i.i3 * scale);
    if (m.i.i4 < 0) dst.f.f4 = *(float const *)((char *) p + ind.i.i4 * scale);
    if (m.i.i5 < 0) dst.f.f5 = *(float const *)((char *) p + ind.i.i5 * scale);
    if (m.i.i6 < 0) dst.f.f6 = *(float const *)((char *) p + ind.i.i6 * scale);
    if (m.i.i7 < 0) dst.f.f7 = *(float const *)((char *) p + ind.i.i7 * scale);
    return dst.__v8sf;
}

/* условное чтение 2-х флотов (32F) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv4sf (__v4sf src, float const *p, __v2di indx, __v4sf mask, const int scale)
{
    type_union_128 ind, m, dst;
    ind.__v2di = indx;
    m.__v4sf = mask;
    dst.__v4sf = src;
    dst.l.l1 = 0;
    if (m.i.i0 < 0) dst.f.f0 = *(float const *)((char *) p + ind.l.l0 * scale);
    if (m.i.i1 < 0) dst.f.f1 = *(float const *)((char *) p + ind.l.l1 * scale);
    return dst.__v4sf;
}

/* условное чтение 4-х флотов (32F) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v4sf __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv4sf256 (__v4sf src, float const *p, __v4di indx, __v4sf mask, const int scale)
{
    type_union_128 m, dst;
    type_union_256 ind;
    ind.__v4di = indx;
    m.__v4sf = mask;
    dst.__v4sf = src;
    if (m.i.i0 < 0) dst.f.f0 = *(float const *)((char *) p + ind.l.l0 * scale);
    if (m.i.i1 < 0) dst.f.f1 = *(float const *)((char *) p + ind.l.l1 * scale);
    if (m.i.i2 < 0) dst.f.f2 = *(float const *)((char *) p + ind.l.l2 * scale);
    if (m.i.i3 < 0) dst.f.f3 = *(float const *)((char *) p + ind.l.l3 * scale);
    return dst.__v4sf;
}

/* условное чтение 2-х лонгов (64S) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv2di (__v2di src, long long const *p, __v4si indx, __v2di mask, const int scale)
{
    type_union_128 s, m, dst;
    s.__v2di = src;
    m.__v2di = mask;
    dst.__v2df = __builtin_ia32_gathersiv2df (s.__v2df, (double const *) p, indx, m.__v2df, scale);
    return dst.__v2di;
}

/* условное чтение 4-х лонгов (64S) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv4di (__v4di src, long long const *p, __v4si indx, __v4di mask, const int scale)
{
    type_union_256 s, m, dst;
    s.__v4di = src;
    m.__v4di = mask;
    dst.__v4df = __builtin_ia32_gathersiv4df (s.__v4df, (double const *) p, indx, m.__v4df, scale);
    return dst.__v4di;
}

/* условное чтение 2-х лонгов (64S) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v2di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv2di (__v2di src, long long const *p, __v2di indx, __v2di mask, const int scale)
{
    type_union_128 s, m, dst;
    s.__v2di = src;
    m.__v2di = mask;
    dst.__v2df = __builtin_ia32_gatherdiv2df (s.__v2df, (double const *) p, indx, m.__v2df, scale);
    return dst.__v2di;
}

/* условное чтение 4-х лонгов (64S) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v4di __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv4di (__v4di src, long long const *p, __v4di indx, __v4di mask, const int scale)
{
    type_union_256 s, m, dst;
    s.__v4di = src;
    m.__v4di = mask;
    dst.__v4df = __builtin_ia32_gatherdiv4df (s.__v4df, (double const *) p, indx, m.__v4df, scale);
    return dst.__v4di;
}

/* условное чтение 4-х интов (32S) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv4si (__v4si src, int const *p, __v4si indx, __v4si mask, const int scale)
{
    type_union_128 s, m, dst;
    s.__v4si = src;
    m.__v4si = mask;
    dst.__v4sf = __builtin_ia32_gathersiv4sf (s.__v4sf, (float const *) p, indx, m.__v4sf, scale);
    return dst.__v4si;
}

/* условное чтение 8-ми интов (32S) по маске по векторным интовым (32S) индексам */
__E2K_INLINE __v8si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gathersiv8si (__v8si src, int const *p, __v8si indx, __v8si mask, const int scale)
{
    type_union_256 s, m, dst;
    s.__v8si = src;
    m.__v8si = mask;
    dst.__v8sf = __builtin_ia32_gathersiv8sf (s.__v8sf, (float const *) p, indx, m.__v8sf, scale);
    return dst.__v8si;
}

/* условное чтение 2-х интов (32S) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv4si (__v4si src, int const *p, __v2di indx, __v4si mask, const int scale)
{
    type_union_128 s, m, dst;
    s.__v4si = src;
    m.__v4si = mask;
    dst.__v4sf = __builtin_ia32_gatherdiv4sf (s.__v4sf, (float const *) p, indx, m.__v4sf, scale);
    return dst.__v4si;
}

/* условное чтение 4-х интов (32S) по маске по векторным лонговым (64S) индексам */
__E2K_INLINE __v4si __DEFAULT_FUNCS_ATTRS
__builtin_ia32_gatherdiv4si256 (__v4si src, int const *p, __v4di indx, __v4si mask, const int scale)
{
    type_union_128 s, m, dst;
    s.__v4si = src;
    m.__v4si = mask;
    dst.__v4sf = __builtin_ia32_gatherdiv4sf256 (s.__v4sf, (float const *) p, indx, m.__v4sf, scale);
    return dst.__v4si;
}

#undef ONE_OPERAND_AVX_BUILTINS_VIA_2SSE
#undef TWO_OPERAND_AVX_BUILTINS_VIA_2SSE
#undef THREE_OPERAND_AVX_BUILTINS_VIA_2SSE
#undef ONE_OPERAND_AND_LITERAL_AVX_BUILTINS_VIA_2SSE
#undef __SHLL_32U
#undef __SHRA_32U
#undef __SHRL_32U

#endif /* __AVX2__ */

#undef __E2K_WARNING
#undef __DEFAULT_FUNCS_ATTRS

#ifdef __cplusplus
}
#endif

#endif /* _E2KBUILTIN_H */
