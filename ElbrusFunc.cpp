#include "headers/Func.h"
#include "headers/e2kbuiltin.h"
#include "headers/e2kintrin.h"


void MultiplyCore(float* a, float* b, float* c, int M, int N, int K) 
{
    __v2di
        vA1, vA2, vA3, vA4, vA5, vA6,
        vB1, vB2, vB3, vB4, vB5, vB6, vB7, vB8,

        p_sum11, p_sum12, p_sum13, p_sum14, p_sum15, p_sum16, p_sum17, p_sum18,
        p_sum21, p_sum22, p_sum23, p_sum24, p_sum25, p_sum26, p_sum27, p_sum28,
        p_sum31, p_sum32, p_sum33, p_sum34, p_sum35, p_sum36, p_sum37, p_sum38,
        p_sum41, p_sum42, p_sum43, p_sum44, p_sum45, p_sum46, p_sum47, p_sum48,
        p_sum51, p_sum52, p_sum53, p_sum54, p_sum55, p_sum56, p_sum57, p_sum58,
        p_sum61, p_sum62, p_sum63, p_sum64, p_sum65, p_sum66, p_sum67, p_sum68,

        sum11, sum12, 
        sum21, sum22, 
        sum31, sum32, 
        sum41, sum42, 
        sum51, sum52, 
        sum61, sum62,
        zerosreg = zeros;
    ZerCore6x8();

    for(long i = 0; i < K; i += 4)
    {
        vA1 =  *((__v2di*)(a + i));
        vA2 =  *((__v2di*)(a + i + K));
        vA3 =  *((__v2di*)(a + i + K * 2));
        vA4 =  *((__v2di*)(a + i + K * 3));
        vA5 =  *((__v2di*)(a + i + K * 4));
        vA6 =  *((__v2di*)(a + i + K * 5));

        vB1 =  *((__v2di*)(b + i));
        vB2 =  *((__v2di*)(b + i + K));
        vB3 =  *((__v2di*)(b + i + K * 2));
        vB4 =  *((__v2di*)(b + i + K * 3));
        vB5 =  *((__v2di*)(b + i + K * 4));
        vB6 =  *((__v2di*)(b + i + K * 5));
        vB7 =  *((__v2di*)(b + i + K * 6));
        vB8 =  *((__v2di*)(b + i + K * 7));

        p_sum11 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB1), p_sum11);
        p_sum12 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB2), p_sum12);
        p_sum13 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB3), p_sum13);
        p_sum14 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB4), p_sum14);
        p_sum15 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB5), p_sum15);
        p_sum16 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB6), p_sum16);
        p_sum17 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB7), p_sum17);
        p_sum18 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA1, vB8), p_sum18);

        p_sum21 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB1), p_sum21);
        p_sum22 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB2), p_sum22);
        p_sum23 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB3), p_sum23);
        p_sum24 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB4), p_sum24);
        p_sum25 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB5), p_sum25);
        p_sum26 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB6), p_sum26);
        p_sum27 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB7), p_sum27);
        p_sum28 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA2, vB8), p_sum28);

        p_sum31 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB1), p_sum31);
        p_sum32 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB2), p_sum32);
        p_sum33 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB3), p_sum33);
        p_sum34 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB4), p_sum34);
        p_sum35 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB5), p_sum35);
        p_sum36 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB6), p_sum36);
        p_sum37 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB7), p_sum37);
        p_sum38 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA3, vB8), p_sum38);

        p_sum41 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB1), p_sum41);
        p_sum42 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB2), p_sum42);
        p_sum43 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB3), p_sum43);
        p_sum44 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB4), p_sum44);
        p_sum45 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB5), p_sum45);
        p_sum46 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB6), p_sum46);
        p_sum47 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB7), p_sum47);
        p_sum48 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA4, vB8), p_sum48);

        p_sum51 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB1), p_sum51);
        p_sum52 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB2), p_sum52);
        p_sum53 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB3), p_sum53);
        p_sum54 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB4), p_sum54);
        p_sum55 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB5), p_sum55);
        p_sum56 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB6), p_sum56);
        p_sum57 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB7), p_sum57);
        p_sum58 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA5, vB8), p_sum58);

        p_sum61 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB1), p_sum61);
        p_sum62 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB2), p_sum62);
        p_sum63 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB3), p_sum63);
        p_sum64 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB4), p_sum64);
        p_sum65 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB5), p_sum65);
        p_sum66 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB6), p_sum66);
        p_sum67 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB7), p_sum67);
        p_sum68 = __builtin_e2k_qpfadds(__builtin_e2k_qpfmuls(vA6, vB8), p_sum68);
    }

    sum11 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum11,  p_sum12),__builtin_e2k_qpfhadds(p_sum13,  p_sum14));
    sum12 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum15,  p_sum16),__builtin_e2k_qpfhadds(p_sum17,  p_sum18));

    sum21 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum21,  p_sum22),__builtin_e2k_qpfhadds(p_sum23,  p_sum24));
    sum22 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum25,  p_sum26),__builtin_e2k_qpfhadds(p_sum27,  p_sum28));

    sum31 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum31,  p_sum32),__builtin_e2k_qpfhadds(p_sum33,  p_sum34));
    sum32 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum35,  p_sum36),__builtin_e2k_qpfhadds(p_sum37,  p_sum38));

    sum41 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum41,  p_sum42),__builtin_e2k_qpfhadds(p_sum43,  p_sum44));
    sum42 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum45,  p_sum46),__builtin_e2k_qpfhadds(p_sum47,  p_sum48));

    sum51 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum51,  p_sum52),__builtin_e2k_qpfhadds(p_sum53,  p_sum54));
    sum52 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum55,  p_sum56),__builtin_e2k_qpfhadds(p_sum57,  p_sum58));

    sum61 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum61,  p_sum62),__builtin_e2k_qpfhadds(p_sum63,  p_sum64));
    sum62 = __builtin_e2k_qpfhadds(__builtin_e2k_qpfhadds(p_sum65,  p_sum66),__builtin_e2k_qpfhadds(p_sum67,  p_sum68));

    *((__v2di*)(c)) = sum11;
    *((__v2di*)(c + 4)) = sum12;

    *((__v2di*)(c + N)) = sum21;
    *((__v2di*)(c + N + 4)) = sum22;

    *((__v2di*)(c + N * 2)) = sum31;
    *((__v2di*)(c + N * 2 + 4)) = sum32;

    *((__v2di*)(c + N * 3)) = sum41;
    *((__v2di*)(c + N * 3 + 4)) = sum42;

    *((__v2di*)(c + N * 4)) = sum51;
    *((__v2di*)(c + N * 4 + 4)) = sum52;

    *((__v2di*)(c + N * 5)) = sum61;
    *((__v2di*)(c + N * 5 + 4)) = sum62;
}

void MultiplyIntrin(float* a, float* b, float* c, int M, int N, int K)
{
    long m_i, n_i;
    unsigned int start_time, end_time; 
    double proc = 0;
    double time = 0;
    int clk = 0;

    start_time =  clock();

    for (m_i = 0; m_i < M; m_i += 6)
    {

        for (n_i = 0; n_i < N; n_i += 8)
        {
            MultiplyCore(a + m_i * K, b + n_i * K, c + n_i + m_i * N, M, N, K);

        }
    }
    
    end_time = clock (); 
    time = static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC; 
    double tic = 1.0 * M * N * K / 24.0;
    proc = (tic / (1.5e7 * time));
    
    //cout << time << endl;
}

void MultiplyIntrin_Paralell(float* a, float* b, float* c, int M, int N, int K)
{
    unsigned long m_i, n_i;
    long double start_time, end_time; 
    long double proc = 0;
    long double time = 0;

    int thread = 0;
    omp_set_num_threads(16);

    if (M >= N)
    {
        start_time =  omp_get_wtime();;
        //#pragma omp parallel private (m_i, n_i)
        #pragma omp parallel for private (n_i)
        {
            for (m_i = 0; m_i < M; m_i += 6)
                for (n_i = 0; n_i < N; n_i += 8)
                {
                    //thread = omp_get_thread_num();
                    //printf("%d\n", thread);  
                    MultiplyCore(a + m_i * K, b + n_i * K, c + n_i + m_i * N, M, N, K);
                }
        }
        end_time = omp_get_wtime();
    }   
    
    else if (N > M)
    {
       start_time =  omp_get_wtime();
        // #pragma omp parallel private (m_i, n_i)
        #pragma omp parallel for private (m_i)
        {
            for (n_i = 0; n_i < N; n_i += 8)
                for (m_i = 0; m_i < M; m_i += 6)
                {
                    //thread = omp_get_thread_num();
                    //printf("%d\n", thread);  
                    MultiplyCore(a + m_i * K, b + n_i * K, c + n_i + m_i * N, M, N, K);
                }
        }
        end_time = omp_get_wtime();
    }
      
    time = (end_time - start_time); 
    long double tic = static_cast<double>(M * N * K) / 24.0;
    proc = (tic / (1.5 * GHz * time)) * 100;
    
    //cout << time << endl;
    //cout << 1.5 * GHz * time << endl;
    //cout << tic << endl;
    cout << proc << endl;
    //cout << endl;
    //cout << endl;
}


///////////////////////////// не мое ///////////////////////////////////////


/*
void MulKernel48(float *inp, float *wts, float *out, int L, int F) {
    // timespec start, end, tdiff;
    // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);

    __v2di vinp1, vinp2, vinp3, vinp4, vinp5, vinp6,

           vwts1, vwts2, vwts3, vwts4, vwts5, vwts6, vwts7, vwts8,

           sum11, sum12, 
           sum21, sum22, 
           sum31, sum32,
           sum41, sum42, 
           sum51, sum52, 
           sum61, sum62,

           partsum11, partsum12, partsum13, partsum14, partsum15, partsum16, partsum17, partsum18,
           partsum21, partsum22, partsum23, partsum24, partsum25, partsum26, partsum27, partsum28,
           partsum31, partsum32, partsum33, partsum34, partsum35, partsum36, partsum37, partsum38,
           partsum41, partsum42, partsum43, partsum44, partsum45, partsum46, partsum47, partsum48,
           partsum51, partsum52, partsum53, partsum54, partsum55, partsum56, partsum57, partsum58,
           partsum61, partsum62, partsum63, partsum64, partsum65, partsum66, partsum67, partsum68,
           
           zerosreg;

    zerosreg = zeros;
    clrpartsums6x8();

    for (long l = 0; l < L; l += 4) {
        vinp1 = addr(inp + l        );
        vinp2 = addr(inp + l + L    );
        vinp3 = addr(inp + l + L * 2);
        vinp4 = addr(inp + l + L * 3);
        vinp5 = addr(inp + l + L * 4);
        vinp6 = addr(inp + l + L * 5);

        vwts1 = addr(wts + l        );
        vwts2 = addr(wts + l + L    );
        vwts3 = addr(wts + l + L * 2);
        vwts4 = addr(wts + l + L * 3);
        vwts5 = addr(wts + l + L * 4);
        vwts6 = addr(wts + l + L * 5);
        vwts7 = addr(wts + l + L * 6);
        vwts8 = addr(wts + l + L * 7);

        partsum11 = muladds(vinp1, vwts1, partsum11);
        partsum12 = muladds(vinp1, vwts2, partsum12);
        partsum13 = muladds(vinp1, vwts3, partsum13);
        partsum14 = muladds(vinp1, vwts4, partsum14);
        partsum15 = muladds(vinp1, vwts5, partsum15);
        partsum16 = muladds(vinp1, vwts6, partsum16);
        partsum17 = muladds(vinp1, vwts7, partsum17);
        partsum18 = muladds(vinp1, vwts8, partsum18);

        partsum21 = muladds(vinp2, vwts1, partsum21);
        partsum22 = muladds(vinp2, vwts2, partsum22);
        partsum23 = muladds(vinp2, vwts3, partsum23);
        partsum24 = muladds(vinp2, vwts4, partsum24);
        partsum25 = muladds(vinp2, vwts5, partsum25);
        partsum26 = muladds(vinp2, vwts6, partsum26);
        partsum27 = muladds(vinp2, vwts7, partsum27);
        partsum28 = muladds(vinp2, vwts8, partsum28);

        partsum31 = muladds(vinp3, vwts1, partsum31);
        partsum32 = muladds(vinp3, vwts2, partsum32);
        partsum33 = muladds(vinp3, vwts3, partsum33);
        partsum34 = muladds(vinp3, vwts4, partsum34);
        partsum35 = muladds(vinp3, vwts5, partsum35);
        partsum36 = muladds(vinp3, vwts6, partsum36);
        partsum37 = muladds(vinp3, vwts7, partsum37);
        partsum38 = muladds(vinp3, vwts8, partsum38);

        partsum41 = muladds(vinp4, vwts1, partsum41);
        partsum42 = muladds(vinp4, vwts2, partsum42);
        partsum43 = muladds(vinp4, vwts3, partsum43);
        partsum44 = muladds(vinp4, vwts4, partsum44);
        partsum45 = muladds(vinp4, vwts5, partsum45);
        partsum46 = muladds(vinp4, vwts6, partsum46);
        partsum47 = muladds(vinp4, vwts7, partsum47);
        partsum48 = muladds(vinp4, vwts8, partsum48);

        partsum51 = muladds(vinp5, vwts1, partsum51);
        partsum52 = muladds(vinp5, vwts2, partsum52);
        partsum53 = muladds(vinp5, vwts3, partsum53);
        partsum54 = muladds(vinp5, vwts4, partsum54);
        partsum55 = muladds(vinp5, vwts5, partsum55);
        partsum56 = muladds(vinp5, vwts6, partsum56);
        partsum57 = muladds(vinp5, vwts7, partsum57);
        partsum58 = muladds(vinp5, vwts8, partsum58);

        partsum61 = muladds(vinp6, vwts1, partsum61);
        partsum62 = muladds(vinp6, vwts2, partsum62);
        partsum63 = muladds(vinp6, vwts3, partsum63);
        partsum64 = muladds(vinp6, vwts4, partsum64);
        partsum65 = muladds(vinp6, vwts5, partsum65);
        partsum66 = muladds(vinp6, vwts6, partsum66);
        partsum67 = muladds(vinp6, vwts7, partsum67);
        partsum68 = muladds(vinp6, vwts8, partsum68);
    }

    sum11 = hadds4(partsum11, partsum12, partsum13, partsum14);
    sum12 = hadds4(partsum15, partsum16, partsum17, partsum18);

    sum21 = hadds4(partsum21, partsum22, partsum23, partsum24);
    sum22 = hadds4(partsum25, partsum26, partsum27, partsum28);

    sum31 = hadds4(partsum31, partsum32, partsum33, partsum34);
    sum32 = hadds4(partsum35, partsum36, partsum37, partsum38);

    sum41 = hadds4(partsum41, partsum42, partsum43, partsum44);
    sum42 = hadds4(partsum45, partsum46, partsum47, partsum48);

    sum51 = hadds4(partsum51, partsum52, partsum53, partsum54);
    sum52 = hadds4(partsum55, partsum56, partsum57, partsum58);

    sum61 = hadds4(partsum61, partsum62, partsum63, partsum64);
    sum62 = hadds4(partsum65, partsum66, partsum67, partsum68);

    addr(out            ) = sum11;
    addr(out         + 4) = sum12;
    addr(out + F        ) = sum21;
    addr(out + F     + 4) = sum22;
    addr(out + F * 2    ) = sum31;
    addr(out + F * 2 + 4) = sum32;
    addr(out + F * 3    ) = sum41;
    addr(out + F * 3 + 4) = sum42;
    addr(out + F * 4    ) = sum51;
    addr(out + F * 4 + 4) = sum52;
    addr(out + F * 5    ) = sum61;
    addr(out + F * 5 + 4) = sum62;

    // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    // tdiff = diff(start, end);
    // double t_real = static_cast<double>(tdiff.tv_sec) + static_cast<double>(tdiff.tv_nsec) / 1.0e9,
    //        t_ideal = (6 * L * 8) / (24 * 1.5 * 1.0e9);
    // printf("t ideal = %f\n", t_ideal);
    // printf("t real = %f\n", t_real);
    // printf("p = %f%%\n", (t_ideal / t_real) * 100);
}





int ElbrusMatrixMulParallel(float *inp, float *wts, float *out, long Q, long L, long F) {
    timespec start, end, tdiff;
    omp_set_num_threads(16);
    if (Q >= F) {
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        #pragma omp parallel for
        {
            for (long q = 0; q < Q; q += 6)
                for (long f = 0; f < F; f += 8)
                    MulKernel48(inp + q * L, wts + f * L, out + f + q * F, L, F);
        }
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    }
    else {
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        #pragma omp parallel for
        {
            for (long f = 0; f < F; f += 8)
                for (long q = 0; q < Q; q += 6)
                    Marallel for
        {
            for (long q = 0; q < Q; q += 6)
                for (long f = 0; f < F; f += 8)
                    MulKernel48(inp + q * L, wts + f * L, out + f + q * F, L, F);
        }
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    }
    else {
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        #pragma omp parallel for
        {
            for (long f = 0; f < F; f += 8)
                for (long q = 0; q < Q; q += 6)
                    MulKernel48(inp + q * L, wts + f * L, out + f + q * F, L, F);
        }
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    }
    //tdiff = diff(start, end);
    //double t_real = ToDouble(tdiff.tv_sec) + ToDouble(tdiff.tv_nsec) * nsec,
    //       t_ideal = (Q * L * F) / (24 * 1.5 * GHz);
    // printf("t ideal = %f\n", t_ideal);
    // printf("t real = %f\n", t_real);
    // printf("p = %f%%\n", (t_ideal / t_real) * 100);
    //printf("mul = ");
    //printf("%f%\n", (t_ideal / t_real) * 100);
    return 0;
}
*/
