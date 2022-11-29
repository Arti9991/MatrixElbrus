#include "headers/Func.h"

void MultiplyIntrin(float* a, float* b, float* c, int M, int N, int K);

int main(int argc, char* argv[]) 
{   
    unsigned int m, n, k;
    int def;
//Чтение аргументов n,m,k размеров матриц из командной строки, при условии их наличия
    if (argc == 4)
    {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        k = atoi(argv[3]);
        def = 10;
    }
    else if (argc == 5)
    {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        k = atoi(argv[3]);
        def = atoi(argv[4]);

    }
     else
    {
        m = 48;
        n = 48;
        k = 48;
        def = 10;
    }

////////////////////billet for bloks////////////////////////////

    int blockM = 48;
    int blockN = 48; 
    int blockK = 48; 



    if (k % blockK != 0) 
    {
        k = blockK * ceil (k / float(blockK));
    }  
    if (n % blockN != 0) 
    {
        n = blockN * ceil (n / float(blockN));
    }
    if (m % blockM != 0) 
    {
        m = blockM * ceil (m / float(blockM));
    } 
/////////////////////////////////////////////////////////////////

//Выделение памяти под масиивы и заполнение случайными числами от 0 до 100
    float* a = new float[m * k];
    for (long i = 0; i < m * k; i++)
        a[i] = static_cast <float>(rand()%100) / 10.0;

    float* b = new float[k * n];
    for (long i = 0; i < k * n; i++)
        b[i] = static_cast <float> (rand()%100) / 10.0;

    float* c = new float[m * n];
    for (long i = 0; i < m * n; i++)
        c[i] = 0.0;

    float* c_m = new float[m * n];
    for (long i = 0; i < m * n; i++)
        c_m[i] = 0.0; 

//выделение памяти под транспонированную матрицу А и транспонирование её

    
    float* t_b = new float[n* k];
    for (long i = 0; i < n * k; i++)
        t_b[i] = 0.0;
    
    Transpond(b, t_b, k, n);
    
    //Multiply(a, b, c_m, m, n, k);
            
    MultiplyIntrin_Paralell(a, t_b, c, m, n, k);


    /*
     float* c_b = new float[m * n];
    for (int i = 0; i < n * m; i++)
        c_b[i] = 0.0;
    
    Transpond(c, c_b, n, m);
    */

    //AvgDeffect(c_m, c, m, n, def);

    //for (int i = 16000; i < 16384; i++)
        //cout << c_m[i]<< " = " << c[i] << ' ';

    return 0;
}
