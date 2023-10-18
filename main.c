#include "cec.h"
#include "interfaces.h"
#include "utils.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

CecData cd = {
    .dataLoaded = 0,
    .prevFunction = 0,
    .prevDimension = 0,
    .M = NULL,
    .OShift = NULL,
    .bias = NULL,
    .SS = NULL,
};

int main()
{
    int nx = 10;
    int version = 2022;
    int func_num = 6;
  //   char *output = "../results/exp_data/F4_core.txt";
    char *data_path = "../data/cec2022";
    loadMatrixData(&cd, data_path, nx, func_num, version);
    loadOShiftData(&cd, data_path, nx, func_num, version);
    loadShuffleData(&cd, data_path, nx, func_num, version);
    cd.prevFunction = func_num;
    cd.prevDimension = nx;
    cd.dataLoaded = 1;
    
    for (double num = -100.; num <= 100.; num += 10.)
    {
        double *f = calloc(1, sizeof(double));
        double *x = calloc(nx, sizeof(double));
        for (int i = 0; i < 10; i++)
        {
            x[i] = num;
        }
        cec2022_hf01(&x[0], &f[0], nx, cd.OShift, cd.M, cd.SS, 1, 1);
        printf("%f\n", f[0]);
    }
    // FILE *fp = fopen(output, "w");

    // for (double x1 = -100.0; x1 <= 100.0; x1 += 0.5)
    // {
    //     for (double x2 = -100.0; x2 <= 100.0; x2 += 0.5)
    //     {
    //         double *f = calloc(1, sizeof(double));
    //         double *x = calloc(nx, sizeof(double));
    //         x[0] = x1;
    //         x[1] = x2;
    //         step_rastrigin_func(&x[0], &f[0], nx, cd.OShift, cd.M, 1, 1);
    //         fprintf(fp, "%f %f %f\n", x[0], x[1], f[0]);
    //     }
    // }
    return 0;
}
