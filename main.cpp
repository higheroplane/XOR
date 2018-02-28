#include "nn.h"

int main ()
{
    float W [MAT_SIZE][MAT_SIZE] = {};

    W[2][0] = 0.45;
    W[3][0] = 0.78;
    W[2][1] = -0.12;
    W[3][1] = 0.13;
    W[4][2] = 1.5;
    W[4][3] = -2.3;

    nn XOR(W, sigm);

    printf ("10 is %lf\n", XOR.compute(1, 0, MAT_SIZE - 1));
    /*printf ("01 is %lf\n", XOR.compute(0, 1, MAT_SIZE - 1));
    printf ("11 is %lf\n", XOR.compute(1, 1, MAT_SIZE - 1));
    printf ("00 is %lf\n", XOR.compute(0, 0, MAT_SIZE - 1));

    printf ("err is %lf \n\n", XOR.GetError());

    for (int i = 0; i < 10; i ++)
    {
        XOR.bp (1, 0);
        XOR.bp (0, 1);
        XOR.bp (1, 1);
        XOR.bp (0, 0);
    }

    printf ("10 is %lf\n", XOR.compute(1, 0, MAT_SIZE - 1));
    printf ("01 is %lf\n", XOR.compute(0, 1, MAT_SIZE - 1));
    printf ("11 is %lf\n", XOR.compute(1, 1, MAT_SIZE - 1));
    printf ("00 is %lf\n", XOR.compute(0, 0, MAT_SIZE - 1));

    printf ("err is %lf \n\n", XOR.GetError());    */

    return 0;
}


