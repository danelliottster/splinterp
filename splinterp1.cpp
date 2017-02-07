//
// Created by Alan Pryor on 2/2/17.
//
#include <vector>
#include "mex.h"
#include "splinter.h"
using namespace splinter;

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]) {
    if (mxIsComplex(prhs[0])){
        double const *Matrix_r; 
        double const *Matrix_i;
        double const *x;
        double *result_r;
        double *result_i;
        
        size_t nrows   = mxGetM(prhs[0]);
        
        const mwSize ndims  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims; ++i) npoints*=dims[i];
        plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxCOMPLEX);

        Matrix_r = mxGetPr(prhs[0]);
        Matrix_i = mxGetPi(prhs[0]);
        x        = mxGetPr(prhs[1]);
        result_r = mxGetPr(plhs[0]);
        result_i = mxGetPi(plhs[0]);
        
//         interp1_F_cx<double>(Matrix_r,Matrix_i, nrows, x, npoints, result_r, result_i,(long long) 1);
        parallel_interp1_cx(interp1_F_cx<double>, Matrix_r,Matrix_i, nrows, x, npoints, result_r, result_i, 1);

    } else {
        double const *Matrix; 
        double const *x;
        double *result;
        
        size_t nrows   = mxGetM(prhs[0]);
        
        const mwSize ndims  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims; ++i) npoints*=dims[i];
        plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);

        Matrix = mxGetPr(prhs[0]);
        x      = mxGetPr(prhs[1]);
        result = mxGetPr(plhs[0]);
        
//         interp1_F<double>(Matrix, nrows, x, npoints, result, 1);
        parallel_interp1(interp1_F<double>, Matrix, nrows, x, npoints, result, 1);

    }
}
