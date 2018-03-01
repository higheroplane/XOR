#include "nn.h"

float epsilon = 2, alpha = 0.4;

int main ()
{
    FILE * out = fopen ("stats.txt", "w");
        
    for (int i = 0; i < 20; i ++)
    {
        for (int j = 0; j < 20; j ++)
        {
            epsilon += 0.12;            
            float W [MAT_SIZE][MAT_SIZE] = {};

            W[4][0] = 0.45;
            W[5][0] = 0.78;
            W[4][1] = -0.12;
            W[5][1] = 0.13;
            W[4][2] = 0.05;
            W[5][2] = 0.03;
            W[6][2] = 0.05;
            W[6][4] = 1.5;
            W[6][5] = -2.3;
            

            nn XOR(W, sigm);
            //XOR.PrintWeights();
            /*printf ("00 is %lf\n", XOR.compute(0, 0, MAT_SIZE - 1));
            printf ("01 is %lf\n", XOR.compute(0, 1, MAT_SIZE - 1));
            printf ("11 is %lf\n", XOR.compute(1, 1, MAT_SIZE - 1));
            printf ("00 is %lf\n", XOR.compute(0, 0, MAT_SIZE - 1));*/

            //printf ("err is %lf \n\n", XOR.GetError());

            for (int i = 0; i < 10000; i ++)
            {
                
                XOR.bp (1, 0);
                XOR.bp (0, 0);
                XOR.bp (0, 1);   
                XOR.bp (1, 1);
            }

           // XOR.PrintWeights();

            /*printf ("10 is %lf\n", XOR.compute(1, 0, MAT_SIZE - 1));
            printf ("01 is %lf\n", XOR.compute(0, 1, MAT_SIZE - 1));
            printf ("11 is %lf\n", XOR.compute(1, 1, MAT_SIZE - 1));
            printf ("00 is %lf\n", XOR.compute(0, 0, MAT_SIZE - 1));*/

            fprintf (out, "%lf %lf %e \n", epsilon, alpha,  XOR.GetError());    
        }
        alpha += 0.67/25;
        epsilon = 2;
    }
    return 0;
}


