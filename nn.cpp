#include "nn.h"

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
    else if (vertex_num == 2) return 1.0;
    else if (vertex_num == 3) return 1.0;
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
            error += pow (compute (i, j, MAT_SIZE - 1) - (i binop j), 2);

    return error/4;
}

void nn:: bp (int i0, int i1)
{
    float delta [MAT_SIZE] = {};

    float res = compute (i0, i1, MAT_SIZE - 1);
    int ideal = (i1 binop i0);
    //printf ("=%d=\n", ideal);
    delta [MAT_SIZE - 1]  =  (ideal - res) * (1 - res) * res;
   // printf ("delta out = %lf\n\n", delta [MAT_SIZE - 1] ); 

    for (int i = MAT_SIZE - 2; i >= 0; i --)
    {
        res = compute (i0, i1, i);
        delta [i] = (1 - res) * res;
        float w_delta = 0;
        float grad [MAT_SIZE] = {};

        for (int j = 0; j < MAT_SIZE; j ++)
        {
            if (fabs (W[j][i]) > 1e-10)
            {
                w_delta += W [j][i] * delta [j];
                //printf ("deltaj %d = %lf\n", j, w_delta); 
                grad [j] = delta[j] * res;
                dW [j][i] = epsilon*grad[j] + alpha*dW [j][i];
                W [j][i] += dW [j][i];
                //printf ("for sin %d to %d: grad = %lf, dW = %lf\n", i, j, grad[j], dW [j][i]);
            }

        }
        //printf ("delta %d = %lf\n\n", i, w_delta * delta[i]);
        delta [i] *= w_delta;

    }
}

void nn:: PrintWeights ()
{
    for (int i = 0; i < MAT_SIZE; i ++)
    {
        for (int j = 0; j < MAT_SIZE; j ++)
            printf ("%lf ", W [j][i]);

        printf ("\n");
    }
}

float sigm (float x)
{
    return (1.0/(1 + exp (-x)));
}
