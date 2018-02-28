#include <stdio.h>
#include <cmath>
#include <string.h>

const int MAT_SIZE = 5;
const float epsilon = 0.7, alpha = 0.3;

class nn
{
    float W [MAT_SIZE][MAT_SIZE];
    float dW [MAT_SIZE][MAT_SIZE];
    float (*activation) (float input);

    public:
    //nn ();
    nn (float _W[MAT_SIZE][MAT_SIZE], float (*act) (float));
    float compute (int i0, int i1, int vertex_num);
    float GetError ();
    void bp (int i0, int i1);
};

float sigm (float in);

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

nn::nn (float _W[MAT_SIZE][MAT_SIZE], float (*_activation) (float))
{
    activation = _activation;
    memcpy (W, _W, MAT_SIZE*MAT_SIZE*sizeof(float));
    memset (dW, 0, MAT_SIZE*MAT_SIZE*sizeof(float));
}

float nn::compute (int i0, int i1, int vertex_num)
{
    float sum = 0;
    if      (vertex_num == 0) return (float) i0;
    else if (vertex_num == 1) return (float) i1;
    else
    {
        for (int i = 0; i < MAT_SIZE; i ++)
        {
            if (W [vertex_num][i]) sum += W [vertex_num][i] * compute (i0, i1, i);
        }
        /*for (int i = 0; i < MAT_SIZE; i ++)
            printf ("comp %d = %lf\n", i, compute (i0, i1, i)); */

        return activation (sum);
    }
}

float nn::GetError ()
{
    float error = 0;

    for (int i = 0; i < 2; i ++)
        for (int j = 0; j < 2; j ++)
            error += pow (compute (i, j, MAT_SIZE - 1) - (i xor j), 2);

    return error/4;
}

void nn:: bp (int i0, int i1)
{
    float delta [MAT_SIZE] = {};

    float res = compute (i0, i1, MAT_SIZE - 1);
    delta [MAT_SIZE - 1]  = std::abs ((i1 xor i0) - res) * (1 - res) * res;

    for (int i = MAT_SIZE - 2; i > 1; i --)
    {
        res = compute (i0, i1, i);
        delta [i] = (1 - res) * res;
        int w_delta = 0;
        float grad [MAT_SIZE] = {};

        for (int j = 0; j < MAT_SIZE; j ++)
        {
            if (W[j][i])
            {
                w_delta += W [j][i] * delta [j];
                grad [j] = delta[j] * res;
                dW [j][i] = epsilon*grad[j] + alpha*dW [j][i];
                W [j][i] += dW [j][i];
            }

        }

        delta [i] *= w_delta;

    }
}

float sigm (float x)
{
    return (1.0/(1 + exp (-x)));
}
