#include <stdio.h>
#include <cmath>
#include <string.h>

#define binop ==

const int MAT_SIZE = 7;
extern float epsilon, alpha;

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
    void PrintWeights ();
};

float sigm (float in);
